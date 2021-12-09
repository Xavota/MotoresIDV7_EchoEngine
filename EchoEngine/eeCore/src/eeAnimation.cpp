#include "eeAnimation.h"
#include <eeMath.h>
#include "eeSkeletalMesh.h"

namespace eeEngineSDK {
void
Animation::addTotalTime(float dt)
{
  m_totalTime += dt;
}
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
    eeOut << importer->GetErrorString() << eeEndl;
    return false;
  }

  if (!scene->HasAnimations())
  {
    return false;
  }


  m_anim = scene->mAnimations[0];
  m_root = scene->mRootNode;

  m_ticksPerSecond = m_anim->mTicksPerSecond != 0.0 ?
                     static_cast<float>(m_anim->mTicksPerSecond) :
                     25.0f;
  m_name = m_anim->mName.C_Str();

  m_duration = static_cast<float>(m_anim->mDuration);

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

  for (uint32 i = 0; i < storage->m_childrenCount; i++)
  {
    storage->m_children.push_back(new Node());
    storeNodes(current->mChildren[i], storage->m_children[i]);
    storage->m_children[i]->m_parent = storage;
  }
}
void
Animation::boneTransform(int32 meshIndex,
                         SPtr<SkeletalMesh> skMesh)
{
  Matrix4f Identity;

  float TimeInTicks = m_totalTime * m_ticksPerSecond;
  float AnimationTime = Math::fmod(TimeInTicks, m_duration);

  readNodeHeirarchy(AnimationTime,
                    m_root,
                    Matrix4f::IDENTITY,
                    meshIndex,
                    skMesh);
}
void
Animation::readNodeHeirarchy(float animationTime,
                             const aiNode* pNode,
                             const Matrix4f& parentTransform,
                             int32 meshIndex,
                             SPtr<SkeletalMesh> skMesh)
{

  String NodeName(pNode->mName.data);

  //trans
  float m[16];
  memcpy(m, &pNode->mTransformation.a1, 16 * sizeof(float));
  Matrix4f NodeTransformation = Matrix4f(m);

  const aiNodeAnim* pNodeAnim = findNodeAnim(m_anim, NodeName);

  if (pNodeAnim)
  {
    // Interpolate scaling and generate scaling transformation matrix
    aiVector3D Scaling;
    calcInterpolatedScaling(animationTime, pNodeAnim, Scaling);
    Matrix4f ScalingM =
    Matrix4f::scaleMatrix(Vector3f(Scaling.x, Scaling.y, Scaling.z));

    // Interpolate rotation and generate rotation transformation matrix
    aiQuaternion RotationQ;
    calcInterpolatedRotation(animationTime, pNodeAnim, RotationQ);
    aiMatrix3x3 quat = RotationQ.GetMatrix();
    Matrix4f RotationM = Matrix4f(quat.a1, quat.a2, quat.a3, 0,
                                  quat.b1, quat.b2, quat.b3, 0,
                                  quat.c1, quat.c2, quat.c3, 0,
                                        0,       0,       0, 1);

    // Interpolate translation and generate translation transformation matrix
    aiVector3D Translation;
    calcInterpolatedPosition(animationTime, pNodeAnim, Translation);
    Matrix4f TranslationM =
    Matrix4f::translationMatrix
    (
      Vector3f(Translation.x, Translation.y, Translation.z)
    );

    // Combine the above transformations
    NodeTransformation = TranslationM * RotationM * ScalingM;
  }

  Matrix4f GlobalTransformation = parentTransform * NodeTransformation;

  Vector<Vector<Bone>>& bonesPerMesh = skMesh->getBonesData();
  Vector<Map<String, int32>>& boneMappings = skMesh->getBoneMapping();
  const Vector<Matrix4f>& globalInverseTransforms =
                                           skMesh->getGlobalInverseTransforms();

  if (boneMappings[meshIndex].find(NodeName) != boneMappings[meshIndex].end())
  {
    uint32 BoneIndex = boneMappings[meshIndex][NodeName];
    bonesPerMesh[meshIndex][BoneIndex].m_finalTransformation =
                          globalInverseTransforms[meshIndex] *
                          GlobalTransformation               *
                          bonesPerMesh[meshIndex][BoneIndex].m_offsetMatrix;
  }

  for (uint32 i = 0; i < pNode->mNumChildren; ++i)
  {
    readNodeHeirarchy(animationTime,
                      pNode->mChildren[i],
                      GlobalTransformation,
                      meshIndex,
                      skMesh);
  }
}
aiNodeAnim*
Animation::findNodeAnim(aiAnimation* anim, String name)
{
  for (uint32 i = 0; i < anim->mNumChannels; i++)
  {
    if (anim->mChannels[i]->mNodeName.C_Str() == name)
    {
      return anim->mChannels[i];
    }
  }
  return nullptr;
}
void
Animation::calcInterpolatedScaling(float animationTime,
                                   const aiNodeAnim* pNodeAnim, 
                                   aiVector3D& out)
{
  // we need at least two values to interpolate...
  if (pNodeAnim->mNumScalingKeys == 1)
  {
    out = pNodeAnim->mScalingKeys[0].mValue;
    return;
  }

  uint32 ScalingIndex = findScaling(animationTime, pNodeAnim);
  uint32 NextScalingIndex = (ScalingIndex + 1);
  //assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
  float DeltaTime =
  static_cast<float>(pNodeAnim->mScalingKeys[NextScalingIndex].mTime -
  pNodeAnim->mScalingKeys[ScalingIndex].mTime);
  float Factor =
  (animationTime -
  static_cast<float>(pNodeAnim->mScalingKeys[ScalingIndex].mTime)) /
  DeltaTime;
  //assert(Factor >= 0.0f && Factor <= 1.0f);
  const aiVector3D& StartScaling =
  pNodeAnim->mScalingKeys[ScalingIndex].mValue;
  const aiVector3D& EndScaling =
  pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
  out = EndScaling - StartScaling;
  out = StartScaling + out * Factor;
}
void
Animation::calcInterpolatedRotation(float animationTime,
                                    const aiNodeAnim* pNodeAnim, 
                                    aiQuaternion& out)
{
  // we need at least two values to interpolate...
  if (pNodeAnim->mNumRotationKeys == 1)
  {
    out = pNodeAnim->mRotationKeys[0].mValue;
    return;
  }

  uint32 RotationIndex = findRotation(animationTime, pNodeAnim);
  uint32 NextRotationIndex = (RotationIndex + 1);
  //assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
  float DeltaTime =
  static_cast<float>(pNodeAnim->mRotationKeys[NextRotationIndex].mTime -
                     pNodeAnim->mRotationKeys[RotationIndex].mTime);
  float Factor =
  (animationTime -
  static_cast<float>(pNodeAnim->mRotationKeys[RotationIndex].mTime)) /
  DeltaTime;
  //assert(Factor >= 0.0f && Factor <= 1.0f);
  const aiQuaternion& StartRotationQ =
  pNodeAnim->mRotationKeys[RotationIndex].mValue;
  const aiQuaternion& EndRotationQ =
  pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
  aiQuaternion::Interpolate(out, StartRotationQ, EndRotationQ, Factor);
  out = out.Normalize();
}
void
Animation::calcInterpolatedPosition(float animationTime,
                                    const aiNodeAnim* pNodeAnim, 
                                    aiVector3D& out)
{
  // we need at least two values to interpolate...
  if (pNodeAnim->mNumPositionKeys == 1)
  {
    out = pNodeAnim->mPositionKeys[0].mValue;
    return;
  }

  uint32 PositionIndex = findPosition(animationTime, pNodeAnim);
  uint32 NextPositionIndex = (PositionIndex + 1);
  //assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
  float DeltaTime =
  static_cast<float>(pNodeAnim->mPositionKeys[NextPositionIndex].mTime -
                     pNodeAnim->mPositionKeys[PositionIndex].mTime);
  float Factor =
  (animationTime -
  static_cast<float>(pNodeAnim->mPositionKeys[PositionIndex].mTime)) /
  DeltaTime;
  //assert(Factor >= 0.0f && Factor <= 1.0f);
  const aiVector3D& StartPosition =
  pNodeAnim->mPositionKeys[PositionIndex].mValue;
  const aiVector3D& EndPosition =
  pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
  out = EndPosition - StartPosition;
  out = StartPosition + out * Factor;
}
uint32
Animation::findScaling(float animationTime, const aiNodeAnim* pNodeAnim)
{
  //assert(pNodeAnim->mNumScalingKeys > 0);

  for (uint32 i = 0; i < pNodeAnim->mNumScalingKeys - 1; ++i)
  {
    if (animationTime < static_cast<float>(pNodeAnim->mScalingKeys[i + 1].mTime))
    {
      return i;
    }
  }

  //assert(0);
  return 0;
}
uint32
Animation::findRotation(float animationTime, const aiNodeAnim* pNodeAnim)
{
  //assert(pNodeAnim->mNumRotationKeys > 0);

  for (uint32 i = 0; i < pNodeAnim->mNumRotationKeys - 1; ++i) 
  {
    if (animationTime < static_cast<float>(pNodeAnim->mRotationKeys[i + 1].mTime))
    {
      return i;
    }
  }

  //assert(0);
  return 0;
}
uint32
Animation::findPosition(float animationTime, const aiNodeAnim* pNodeAnim)
{
  //assert(pNodeAnim->mNumPositionKeys > 0);

  for (uint32 i = 0; i < pNodeAnim->mNumPositionKeys - 1; ++i)
  {
    if (animationTime < static_cast<float>(pNodeAnim->mPositionKeys[i + 1].mTime))
    {
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