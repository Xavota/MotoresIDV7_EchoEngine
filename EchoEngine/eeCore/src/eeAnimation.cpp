#include "eeAnimation.h"

#pragma warning(push, 0)
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)

#include <eeLogger.h>
#include <eeMemoryManager.h>
#include <eeMath.h>

#include "eeSkeletalMesh.h"
#include "eeSkeletal.h"



namespace eeEngineSDK {
bool
Animation::loadFromFile(const String& fileName, int32 animIndex, const String& name)
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
  if (!scene) {
    Logger::instance().ConsoleLog(importer->GetErrorString());
    delete importer;
    return false;
  }

  if (!scene->HasAnimations()) {
    return false;
  }

  m_name = name;

  m_rootNode = MemoryManager::instance().newPtr<Node>();
  storeNodes(scene->mRootNode, m_rootNode);

  storeAnim(scene->mAnimations[animIndex]);

  delete importer;
  return true;
}
void
Animation::storeNodes(aiNode* current, SPtr<Node> storage)
{
  auto& memoryMan = MemoryManager::instance();

  storage->m_name = current->mName.C_Str();
  float m[16];
  memcpy(m, &current->mTransformation.a1, 16 * sizeof(float));
  storage->m_transformation = Matrix4f(m);

  storage->m_childrenCount = current->mNumChildren;

  for (uint32 i = 0; i < storage->m_childrenCount; ++i) {
    storage->m_children.push_back(memoryMan.newPtr<Node>());
    storeNodes(current->mChildren[i], storage->m_children[i]);
    storage->m_children[i]->m_parent = storage;
  }
}
void Animation::storeAnim(aiAnimation* anim)
{
  //m_name = anim->mName.C_Str();
  m_duration = static_cast<float>(anim->mDuration);
  m_ticksPerSecond = anim->mTicksPerSecond != 0.0
                   ? static_cast<float>(anim->mTicksPerSecond)
                   : 25.0f;

  m_channelsCount = anim->mNumChannels;
  for (uint32 i = 0; i < m_channelsCount; ++i)
  {
    m_channels.emplace_back(AnimNode());
    AnimNode& an = m_channels[i];
    const aiNodeAnim* aina = anim->mChannels[i];

    an.m_name = aina->mNodeName.C_Str();
    an.m_positionKeysCount = aina->mNumPositionKeys;
    an.m_rotationKeysCount = aina->mNumRotationKeys;
    an.m_scalingKeysCount = aina->mNumScalingKeys;

    for (uint32 j = 0; j < an.m_positionKeysCount; ++j)
    {
      an.m_positionKeys.emplace_back(VectorKeyFrame());
      VectorKeyFrame& vkf = an.m_positionKeys[j];
      const aiVectorKey& aiVkf = aina->mPositionKeys[j];

      vkf.m_time = static_cast<float>(aiVkf.mTime);
      vkf.m_value.x = aiVkf.mValue.x;
      vkf.m_value.y = aiVkf.mValue.y;
      vkf.m_value.z = aiVkf.mValue.z;
    }

    for (uint32 j = 0; j < an.m_rotationKeysCount; ++j)
    {
      an.m_rotationKeys.emplace_back(QuatKeyFrame());
      QuatKeyFrame& qkf = an.m_rotationKeys[j];
      const aiQuatKey& aiQkf = aina->mRotationKeys[j];

      qkf.m_time = static_cast<float>(aiQkf.mTime);
      qkf.m_value.w = aiQkf.mValue.w;
      qkf.m_value.x = aiQkf.mValue.x;
      qkf.m_value.y = aiQkf.mValue.y;
      qkf.m_value.z = aiQkf.mValue.z;
    }

    for (uint32 j = 0; j < an.m_scalingKeysCount; ++j)
    {
      an.m_scalingKeys.emplace_back(VectorKeyFrame());
      VectorKeyFrame& vkf = an.m_scalingKeys[j];
      const aiVectorKey& aiVkf = aina->mScalingKeys[j];

      vkf.m_time = static_cast<float>(aiVkf.mTime);
      vkf.m_value.x = aiVkf.mValue.x;
      vkf.m_value.y = aiVkf.mValue.y;
      vkf.m_value.z = aiVkf.mValue.z;
    }
  }
}
void
Animation::boneTransform(int32 meshIndex,
                         SPtr<Skeletal> skMesh,
                         float time)
{
  Matrix4f Identity;

  float TimeInTicks = time * m_ticksPerSecond;
  float AnimationTime = Math::fmod(TimeInTicks, m_duration);

  readNodeHeirarchy(AnimationTime,
                    m_rootNode,
                    Matrix4f::kIDENTITY,
                    meshIndex,
                    skMesh);
}
void
Animation::readNodeHeirarchy(float animationTime,
                             const SPtr<Node> pNode,
                             const Matrix4f& parentTransform,
                             int32 meshIndex,
                             SPtr<Skeletal> skMesh)
{

  String NodeName(pNode->m_name);

  //trans
  Matrix4f NodeTransformation = pNode->m_transformation;

  AnimNode animNode;
  bool existsNode = findNodeAnim(NodeName, animNode);

  if (existsNode) {
    // Interpolate scaling and generate scaling transformation matrix
    Vector3f Scaling;
    calcInterpolatedScaling(animationTime, animNode, Scaling);
    Matrix4f ScalingM =
    Matrix4f::scaleMatrix(Scaling);
  
    // Interpolate rotation and generate rotation transformation matrix
    Quaternion RotationQ;
    calcInterpolatedRotation(animationTime, animNode, RotationQ);
    Matrix4f RotationM = RotationQ.getRotationMatrix();
  
    // Interpolate translation and generate translation transformation matrix
    Vector3f Translation;
    calcInterpolatedPosition(animationTime, animNode, Translation);
    Matrix4f TranslationM =
    Matrix4f::translationMatrix(Translation);
  
    // Combine the above transformations
    NodeTransformation = TranslationM * RotationM * ScalingM;
  }

  Matrix4f GlobalTransformation = parentTransform * NodeTransformation;

  Vector<Vector<Bone>>& bonesPerMesh = skMesh->getBonesData();
  Vector<Map<String, int32>>& boneMappings = skMesh->getBoneMapping();
  const Vector<Matrix4f>& globalInverseTransforms =
                                           skMesh->getGlobalInverseTransforms();

  if (boneMappings[meshIndex].find(NodeName) != boneMappings[meshIndex].end()) {
    uint32 BoneIndex = boneMappings[meshIndex][NodeName];
    bonesPerMesh[meshIndex][BoneIndex].m_finalTransformation =
                              globalInverseTransforms[meshIndex]
                            * GlobalTransformation
                            * bonesPerMesh[meshIndex][BoneIndex].m_offsetMatrix;
  }

  for (uint32 i = 0; i < pNode->m_childrenCount; ++i) {
    readNodeHeirarchy(animationTime,
                      pNode->m_children[i],
                      GlobalTransformation,
                      meshIndex,
                      skMesh);
  }
}
bool
Animation::findNodeAnim(const String& name,
                        AnimNode& outAnimNode)
{
  for (uint32 i = 0; i < m_channelsCount; i++) {
    if (m_channels[i].m_name == name) {
      outAnimNode = m_channels[i];
      return true;
    }
  }
  return false;
}
void
Animation::calcInterpolatedScaling(float animationTime,
                                   const AnimNode& pNodeAnim,
                                   Vector3f& out)
{
  // we need at least two values to interpolate...
  if (pNodeAnim.m_scalingKeysCount == 1) {
    out = pNodeAnim.m_scalingKeys[0].m_value;
    return;
  }

  uint32 ScalingIndex = findScaling(animationTime, pNodeAnim);
  uint32 NextScalingIndex = (ScalingIndex + 1);
  //assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
  auto DeltaTime = pNodeAnim.m_scalingKeys[NextScalingIndex].m_time
                 - pNodeAnim.m_scalingKeys[ScalingIndex].m_time;
  auto Factor = (animationTime
               - pNodeAnim.m_scalingKeys[ScalingIndex].m_time)
               / DeltaTime;
  //assert(Factor >= 0.0f && Factor <= 1.0f);
  const Vector3f& StartScale =
  pNodeAnim.m_scalingKeys[ScalingIndex].m_value;
  const Vector3f& EndScale =
  pNodeAnim.m_scalingKeys[NextScalingIndex].m_value;
  out = EndScale - StartScale;
  out = StartScale + out * Factor;
}
void
Animation::calcInterpolatedRotation(float animationTime,
                                    const AnimNode& pNodeAnim,
                                    Quaternion& out)
{
  // we need at least two values to interpolate...
  if (pNodeAnim.m_rotationKeysCount == 1) {
    out = pNodeAnim.m_rotationKeys[0].m_value;
    return;
  }

  uint32 RotationIndex = findRotation(animationTime, pNodeAnim);
  uint32 NextRotationIndex = (RotationIndex + 1);
  //assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
  auto DeltaTime = pNodeAnim.m_rotationKeys[NextRotationIndex].m_time
                 - pNodeAnim.m_rotationKeys[RotationIndex].m_time;
  auto Factor = (animationTime
               - pNodeAnim.m_rotationKeys[RotationIndex].m_time)
               / DeltaTime;
  //assert(Factor >= 0.0f && Factor <= 1.0f);
  const Quaternion& StartRotationQ =
  pNodeAnim.m_rotationKeys[RotationIndex].m_value;
  const Quaternion& EndRotationQ =
  pNodeAnim.m_rotationKeys[NextRotationIndex].m_value;
  
  out =
  Quaternion::interpolate(StartRotationQ, EndRotationQ, Factor).getNormalize();
}
void
Animation::calcInterpolatedPosition(float animationTime,
                                    const AnimNode& pNodeAnim,
                                    Vector3f& out)
{
  // we need at least two values to interpolate...
  if (pNodeAnim.m_positionKeysCount == 1) {
    out = pNodeAnim.m_positionKeys[0].m_value;
    return;
  }

  uint32 PositionIndex = findPosition(animationTime, pNodeAnim);
  uint32 NextPositionIndex = (PositionIndex + 1);
  //assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
  auto DeltaTime = pNodeAnim.m_positionKeys[NextPositionIndex].m_time
                 - pNodeAnim.m_positionKeys[PositionIndex].m_time;
  auto Factor = (animationTime
               - pNodeAnim.m_positionKeys[PositionIndex].m_time)
               / DeltaTime;
  //assert(Factor >= 0.0f && Factor <= 1.0f);
  const Vector3f& StartPosition =
  pNodeAnim.m_positionKeys[PositionIndex].m_value;
  const Vector3f& EndPosition =
  pNodeAnim.m_positionKeys[NextPositionIndex].m_value;
  out = EndPosition - StartPosition;
  out = StartPosition + out * Factor;
}
uint32
Animation::findScaling(float animationTime, const AnimNode& pNodeAnim)
{
  //assert(pNodeAnim->mNumScalingKeys > 0);

  for (uint32 i = 0; i < pNodeAnim.m_scalingKeysCount - 1; ++i) {
    if (animationTime < pNodeAnim.m_scalingKeys[i + 1u].m_time) {
      return i;
    }
  }

  //assert(0);
  return 0;
}
uint32
Animation::findRotation(float animationTime, const AnimNode& pNodeAnim)
{
  //assert(pNodeAnim->mNumRotationKeys > 0);

  for (uint32 i = 0; i < pNodeAnim.m_rotationKeysCount - 1; ++i) {
    if (animationTime < pNodeAnim.m_rotationKeys[i + 1u].m_time) {
      return i;
    }
  }

  //assert(0);
  return 0;
}
uint32
Animation::findPosition(float animationTime, const AnimNode& pNodeAnim)
{
  //assert(pNodeAnim->mNumPositionKeys > 0);

  for (uint32 i = 0; i < pNodeAnim.m_positionKeysCount - 1; ++i) {
    if (animationTime < pNodeAnim.m_positionKeys[i + 1u].m_time) {
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