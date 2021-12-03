#include "eeAnimation.h"
#include <eeMath.h>
#include "eeSkeletalMesh.h"

namespace eeEngineSDK {
bool
Animation::loadFromFile(String fileName)
{
  Assimp::Importer* importer = nullptr;
  const aiScene* scene = nullptr;

  importer = new Assimp::Importer();
  scene = importer->ReadFile
  (
    fileName,
    aiProcessPreset_TargetRealtime_MaxQuality
    | aiProcess_ConvertToLeftHanded
  );
  if (!scene)
  {
    std::cout << importer->GetErrorString() << std::endl;
    return false;
  }

  if (!scene->HasAnimations())
  {
    return false;
  }


  m_anim = scene->mAnimations[0];
  m_root = scene->mRootNode;

  m_ticksPerSecond = m_anim->mTicksPerSecond != 0 ? m_anim->mTicksPerSecond : 25.0f;
  m_name = m_anim->mName.C_Str();

  m_duration = m_anim->mDuration;

  return true;
}
void
Animation::storeNodes(aiNode* current, Node* storage)
{
  storage->m_name = current->mName.C_Str();
  float m[16];
  memcpy(m, &current->mTransformation.a1, 16 * sizeof(float));
  storage->m_transformation = Matrix4f(m);

  storage->m_childrenCount = current->mNumChildren;

  for (int i = 0; i < storage->m_childrenCount; i++)
  {
    storage->m_children.push_back(new Node());
    storeNodes(current->mChildren[i], storage->m_children[i]);
    storage->m_children[i]->m_parent = storage;
  }
}
void
Animation::boneTransform(float TimeInSeconds,
                         int32 meshIndex,
                         SPtr<SkeletalMesh> skMesh)
{
  m_totalTime += TimeInSeconds;

  Matrix4f Identity;

  float TimeInTicks = m_totalTime * m_ticksPerSecond;
  float AnimationTime = Math::fmod(TimeInTicks, m_duration);

  //std::cout << AnimationTime << std::endl;

  readNodeHeirarchy(AnimationTime,
                    m_root,
                    Matrix4f::IDENTITY,
                    meshIndex,
                    skMesh);
}
void
Animation::readNodeHeirarchy(float AnimationTime,
                             const aiNode* pNode,
                             const Matrix4f& ParentTransform,
                             int32 meshIndex,
                             SPtr<SkeletalMesh> skMesh)
{

  String NodeName(pNode->mName.data);

  //trans
  float m[16];
  memcpy(m, &pNode->mTransformation.a1, 16 * sizeof(float));
  Matrix4f NodeTransformation = Matrix4f(m);

  const aiNodeAnim* pNodeAnim = findNodeAnim(m_anim, NodeName);

  if (pNodeAnim) {
    // Interpolate scaling and generate scaling transformation matrix
    aiVector3D Scaling;
    calcInterpolatedScaling(&Scaling, AnimationTime, pNodeAnim);
    Matrix4f ScalingM =
    Matrix4f::scaleMatrix(Vector3f(Scaling.x, Scaling.y, Scaling.z)).getTranspose();

    // Interpolate rotation and generate rotation transformation matrix
    aiQuaternion RotationQ;
    calcInterpolatedRotation(&RotationQ, AnimationTime, pNodeAnim);
    aiMatrix3x3 quat = RotationQ.GetMatrix();
    Matrix4f RotationM = Matrix4f(quat.a1, quat.a2, quat.a3, 0,
                                  quat.b1, quat.b2, quat.b3, 0,
                                  quat.c1, quat.c2, quat.c3, 0,
                                  0,       0,       0,       1);

    // Interpolate translation and generate translation transformation matrix
    aiVector3D Translation;
    calcInterpolatedPosition(&Translation, AnimationTime, pNodeAnim);
    Matrix4f TranslationM =
    Matrix4f::translationMatrix
    (
      Vector3f(Translation.x, Translation.y, Translation.z)
    )
    .getTranspose();

    // Combine the above transformations
    NodeTransformation = TranslationM * RotationM * ScalingM;
  }

  Matrix4f GlobalTransformation = ParentTransform * NodeTransformation;

  Vector<Vector<Bone>>& bonesPerMesh = skMesh->getBonesData();
  Vector<Map<String, int32>>& boneMappings = skMesh->getBoneMapping();
  const Vector<Matrix4f>& globalInverseTransforms =
                                           skMesh->getGlobalInverseTransforms();

  if (boneMappings[meshIndex].find(NodeName) != boneMappings[meshIndex].end())
  {
    uint32 BoneIndex = boneMappings[meshIndex][NodeName];
    bonesPerMesh[meshIndex][BoneIndex].m_finalTransformation =
    globalInverseTransforms[meshIndex] *
    GlobalTransformation                         *
    bonesPerMesh[meshIndex][BoneIndex].m_offsetMatrix;
  }

  for (int i = 0; i < pNode->mNumChildren; i++) {
    readNodeHeirarchy(AnimationTime,
                      pNode->mChildren[i],
                      GlobalTransformation,
                      meshIndex,
                      skMesh);
  }
}
aiNodeAnim*
Animation::findNodeAnim(aiAnimation* anim, String name)
{
  for (int i = 0; i < anim->mNumChannels; i++)
  {
    if (anim->mChannels[i]->mNodeName.C_Str() == name)
    {
      return anim->mChannels[i];
    }
  }
  return nullptr;
}
void
Animation::calcInterpolatedScaling(aiVector3D* Out,
                                   float AnimationTime,
                                   const aiNodeAnim* pNodeAnim)
{
  // we need at least two values to interpolate...
  if (pNodeAnim->mNumScalingKeys == 1) {
    *Out = pNodeAnim->mScalingKeys[0].mValue;
    return;
  }

  unsigned int ScalingIndex = findScaling(AnimationTime, pNodeAnim);
  unsigned int NextScalingIndex = (ScalingIndex + 1);
  //assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
  float DeltaTime = pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime;
  float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
  //assert(Factor >= 0.0f && Factor <= 1.0f);
  const aiVector3D& StartScaling = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
  const aiVector3D& EndScaling = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
  *Out = EndScaling - StartScaling;
  *Out = StartScaling + *Out * Factor;
}
void
Animation::calcInterpolatedRotation(aiQuaternion* Out,
                                    float AnimationTime,
                                    const aiNodeAnim* pNodeAnim)
{
  // we need at least two values to interpolate...
  if (pNodeAnim->mNumRotationKeys == 1) {
    *Out = pNodeAnim->mRotationKeys[0].mValue;
    return;
  }

  unsigned int RotationIndex = findRotation(AnimationTime, pNodeAnim);
  unsigned int NextRotationIndex = (RotationIndex + 1);
  //assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
  float DeltaTime = pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime;
  float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
  //assert(Factor >= 0.0f && Factor <= 1.0f);
  const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
  const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
  aiQuaternion::Interpolate(*Out, StartRotationQ, EndRotationQ, Factor);
  *Out = Out->Normalize();
}
void
Animation::calcInterpolatedPosition(aiVector3D* Out,
                                    float AnimationTime,
                                    const aiNodeAnim* pNodeAnim)
{
  // we need at least two values to interpolate...
  if (pNodeAnim->mNumPositionKeys == 1) {
    *Out = pNodeAnim->mPositionKeys[0].mValue;
    return;
  }

  unsigned int PositionIndex = findPosition(AnimationTime, pNodeAnim);
  unsigned int NextPositionIndex = (PositionIndex + 1);
  //assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
  float DeltaTime = pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime;
  float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
  //assert(Factor >= 0.0f && Factor <= 1.0f);
  const aiVector3D& StartPosition = pNodeAnim->mPositionKeys[PositionIndex].mValue;
  const aiVector3D& EndPosition = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
  *Out = EndPosition - StartPosition;
  *Out = StartPosition + *Out * Factor;
}
uint32
Animation::findScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
  //assert(pNodeAnim->mNumScalingKeys > 0);

  for (int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
    if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
      return i;
    }
  }

  //assert(0);
  return 0;
}
uint32
Animation::findRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
  //assert(pNodeAnim->mNumRotationKeys > 0);

  for (int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
    if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
      return i;
    }
  }

  //assert(0);
  return 0;
}
uint32
Animation::findPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
  //assert(pNodeAnim->mNumPositionKeys > 0);

  for (int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
    if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
      return i;
    }
  }

  //assert(0);
  return 0;
}
String
Animation::getName()
{
  return m_name;
}
}