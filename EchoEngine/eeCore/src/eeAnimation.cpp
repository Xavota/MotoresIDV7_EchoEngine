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
Animation::Animation(float ticksPerSecond,
                     float duration,
                     const Vector<AnimNode>& channels,
                     SPtr<Node> pRootNode,
                     const String& name)
{
  loadFromData(ticksPerSecond , duration, channels, pRootNode, name);
}
bool
Animation::loadFromData(float ticksPerSecond,
                        float duration,
                        const Vector<AnimNode>& channels,
                        SPtr<Node> pRootNode,
                        const String& name)
{
  m_ticksPerSecond = ticksPerSecond;
  m_duration = duration;
  m_channels = channels;
  m_channelsCount = m_channels.size();
  m_pRootNode = pRootNode;
  m_name = name;

  return true;
}
void
Animation::boneTransform(SIZE_T meshIndex,
                         WPtr<Skeletal> pSkMesh,
                         float time)
{
  float TimeInTicks = time * m_ticksPerSecond;
  float AnimationTime = Math::fmod(TimeInTicks, m_duration);

  readNodeHeirarchy(AnimationTime,
                    m_pRootNode,
                    Matrix4f::kIDENTITY,
                    meshIndex,
                    pSkMesh);
}
void
Animation::readNodeHeirarchy(float animationTime,
                             const WPtr<Node> pNode,
                             const Matrix4f& parentTransform,
                             SIZE_T meshIndex,
                             WPtr<Skeletal> pSkMesh)
{
  auto spNode = pNode.lock();
  auto spSkMesh = pSkMesh.lock();

  String NodeName(spNode->m_name);

  //trans
  Matrix4f NodeTransformation = spNode->m_transformation;

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

  Vector<Vector<Bone>>& bonesPerMesh = spSkMesh->getBonesData();
  Vector<Map<String, uint32>>& boneMappings = spSkMesh->getBoneMapping();
  const Vector<Matrix4f>& globalInverseTransforms =
                                         spSkMesh->getGlobalInverseTransforms();

  if (boneMappings[meshIndex].find(NodeName) != boneMappings[meshIndex].end()) {
    uint32 BoneIndex = boneMappings[meshIndex][NodeName];
    bonesPerMesh[meshIndex][BoneIndex].m_finalTransformation =
                              globalInverseTransforms[meshIndex]
                            * GlobalTransformation
                            * bonesPerMesh[meshIndex][BoneIndex].m_offsetMatrix;
  }

  for (uint32 i = 0; i < spNode->m_childrenCount; ++i) {
    readNodeHeirarchy(animationTime,
                      spNode->m_pChildren[i],
                      GlobalTransformation,
                      meshIndex,
                      pSkMesh);
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