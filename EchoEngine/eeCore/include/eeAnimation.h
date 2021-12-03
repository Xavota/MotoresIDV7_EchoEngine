/************************************************************************/
/**
 * @file eeInput.h
 * @author Diego Castellanos
 * @date 02/12/21
 * @brief
 * The input manager for the api.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeMatrix4.h>
#include <eeVector3.h>
#pragma warning(push, 0)   
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)

//class aiNode;
//class aiNodeAnim;
//class aiAnimation;
//class aiQuaternion;
//class aiVector3D;

namespace eeEngineSDK {
class SkeletalMesh;

struct Node
{
  String m_name;
  Matrix4f m_transformation;
  Node* m_parent = nullptr;
  uint32 m_childrenCount;
  Vector<Node*> m_children;
};
struct VectorKeyFrame
{
  double m_time;
  Vector3f m_value;
};

struct QuatKeyFrame
{
  double m_time;
  aiQuaternion* m_value;  // TODO: CAMBIAR A MI CUATERNION
};

struct AnimNode
{
  String m_name;

  uint32 m_positionKeysCount;
  uint32 m_rotationKeysCount;
  uint32 m_scalingKeysCount;

  Vector<VectorKeyFrame> m_positionKeys;
  Vector<QuatKeyFrame> m_rotationKeys;
  Vector<VectorKeyFrame> m_scalingKeys;
};
class Animation
{
 public:
  Animation() = default;
  ~Animation() = default;

  bool
  loadFromFile(String fileName);
  void
  storeNodes(aiNode* current, Node* storage);

  void
  boneTransform(float TimeInSeconds,
                int32 meshIndex,
                SPtr<SkeletalMesh> skMesh);
  void
  readNodeHeirarchy(float AnimationTime,
                    const aiNode* pNode,
                    const Matrix4f& ParentTransform,
                    int32 meshIndex,
                    SPtr<SkeletalMesh> skMesh);

  aiNodeAnim*
  findNodeAnim(aiAnimation* anim, String name);

  void
  calcInterpolatedScaling(aiVector3D* Out,
                          float AnimationTime,
                          const aiNodeAnim* pNodeAnim);
  void
  calcInterpolatedRotation(aiQuaternion* Out,
                           float AnimationTime,
                           const aiNodeAnim* pNodeAnim);
  void
  calcInterpolatedPosition(aiVector3D* Out,
                           float AnimationTime,
                           const aiNodeAnim* pNodeAnim);

  uint32
  findScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
  uint32
  findRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
  uint32
  findPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);

  String
  getName();

private:
  float m_totalTime = 0.0f;
  float m_ticksPerSecond = 0.0f;
  float m_duration = 0.0f;
  String m_name;

  aiAnimation* m_anim = nullptr;
  aiNode* m_root = nullptr;

  //Vector<AnimNode> m_channels;
  //Node* m_rootNode = nullptr;
};
}
