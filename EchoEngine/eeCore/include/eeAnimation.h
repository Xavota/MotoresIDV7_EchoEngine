/************************************************************************/
/**
 * @file eeAnimation.h
 * @author Diego Castellanos
 * @date 02/12/21
 * @brief
 * The animation resource. Contains the bones transformations.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeMatrix4.h>
#include <eeVector3.h>
#include <eeQuaternion.h>

class aiNode;
class aiAnimation;

namespace eeEngineSDK {
class SkeletalMesh;

/**
 * @brief
 * A node for the animation graph.
 */
struct Node
{
  String m_name;
  Matrix4f m_transformation;
  SPtr<Node> m_parent = nullptr;
  uint32 m_childrenCount = 0;
  Vector<SPtr<Node>> m_children;
};

/**
 * @brief
 * Vector key frame, for position and scale key frames.
 */
struct VectorKeyFrame
{
  float m_time = 0.0f;
  Vector3f m_value;
};

/**
 * @brief
 * Quaternion key frame, for rotation key frames.
 */
struct QuatKeyFrame
{
  float m_time = 0.0f;
  Quaternion m_value;
};

/**
 * @brief
 * Animation node, with it's key frames.
 */
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

/**
 * @brief
 * The animation resource. Contains the bones transformations.
 */
class Animation
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  Animation() = default;
  /**
   * @brief
   * Default destructor.
   */
  ~Animation() = default;

  /**
   * @brief
   * Adds delta time.
   *
   * @description
   * Adds delta time to its global animation time.
   *
   * @param dt
   * Global delta time.
   */
  void
  addTotalTime(float dt);

  /**
   * @brief
   * Loads an animation.
   *
   * @description
   * Loads the animation from a file.
   *
   * @param fileName
   * The file path.
   *
   * @return
   * If it succeeded to load.
   */
  bool
  loadFromFile(const String& fileName);

  /**
   * @brief
   * Modify the bone data on the skeletal mesh.
   *
   * @description
   * Modify the bone data on the skeletal mesh for a specific mesh using the
   * animation.
   *
   * @param meshIndex
   * The index of the mesh to modify.
   * @param skMesh
   * The skeletal mesh to change the bone data.
   */
  void
  boneTransform(int32 meshIndex,
                SPtr<SkeletalMesh> skMesh);
  /**
   * @brief
   * Reads the animation graph.
   *
   * @description
   * Pass through the animation graph to modify the bone data of the skeletal mesh.
   *
   * @param animationTime
   * The current time of the animation.
   * @param pNode
   * Current node of the graph.
   * @param parentTransform
   * Transform of the parent node of this node.
   * @param meshIndex
   * The index of the mesh to modify.
   * @param skMesh
   * The skeletal mesh to change the bone data.
   */
  void
  readNodeHeirarchy(float animationTime,
                    const SPtr<Node> pNode,
                    const Matrix4f& parentTransform,
                    int32 meshIndex,
                    SPtr<SkeletalMesh> skMesh);

  /**
   * @brief
   * Find animation node by name.
   *
   * @description
   * Find the animation node from the graph by its name.
   *
   * @param anim
   * The animation that the node is in.
   * @param name
   * The name of the node.
   * @param outAnimNode
   * The found animation node, if it is one.
   *
   * @return
   * True if it found the anim node.
   */
  bool
  findNodeAnim(const String& name, AnimNode& outAnimNode);

  /**
   * @brief
   * Calculates the interpolated scaling.
   *
   * @description
   * Calculates the interpolated scaling from the animation node in the current
   * animation time.
   *
   * @param animationTime
   * The current animation global time.
   * @param pNodeAnim
   * The animation node to extract the interpolation.
   * @param out
   * The scale result of the interpolation.
   */
  void
  calcInterpolatedScaling(float animationTime,
                          const AnimNode& pNodeAnim,
                          Vector3f& out);
  /**
   * @brief
   * Calculates the interpolated rotation.
   *
   * @description
   * Calculates the interpolated rotation from the animation node in the current
   * animation time.
   *
   * @param animationTime
   * The current animation global time.
   * @param pNodeAnim
   * The animation node to extract the interpolation.
   * @param out
   * The rotation result of the interpolation.
   */
  void
  calcInterpolatedRotation(float animationTime,
                           const AnimNode& pNodeAnim,
                           Quaternion& out);
  /**
   * @brief
   * Calculates the interpolated position.
   *
   * @description
   * Calculates the interpolated position from the animation node in the current
   * animation time.
   *
   * @param animationTime
   * The current animation global time.
   * @param pNodeAnim
   * The animation node to extract the interpolation.
   * @param out
   * The position result of the interpolation.
   */
  void
  calcInterpolatedPosition(float animationTime,
                           const AnimNode& pNodeAnim,
                           Vector3f& out);
  /**
   * @brief
   * Find scaling key frame index.
   *
   * @description
   * Find the nearest lower scaling key frame index for the interpolation
   * calculation, depending on the global time.
   *
   * @param animationTime
   * The global animation time.
   * @param pNodeAnim
   * The animation node it's on.
   *
   * @return
   * The key frame index for the scale.
   */
  uint32
  findScaling(float animationTime, const AnimNode& pNodeAnim);
  /**
   * @brief
   * Find rotation key frame index.
   *
   * @description
   * Find the nearest lower rotation key frame index for the interpolation
   * calculation, depending on the global time.
   *
   * @param animationTime
   * The global animation time.
   * @param pNodeAnim
   * The animation node it's on.
   *
   * @return
   * The key frame index for the rotation.
   */
  uint32
  findRotation(float animationTime, const AnimNode& pNodeAnim);
  /**
   * @brief
   * Find position key frame index.
   *
   * @description
   * Find the nearest lower position key frame index for the interpolation
   * calculation, depending on the global time.
   *
   * @param animationTime
   * The global animation time.
   * @param pNodeAnim
   * The animation node it's on.
   *
   * @return
   * The key frame position for the scale.
   */
  uint32
  findPosition(float animationTime, const AnimNode& pNodeAnim);

  /**
   * @brief
   * Getter for the animation name.
   *
   * @description
   * Returns the animation name.
   *
   * @return
   * The animation name.
   */
  String
  getName();

 private:
  /**
   * @brief
   * Stores the animation graph.
   *
   * @description
   * Stores the Assimp animation graph to my own nodes.
   *
   * @param current
   * Current node to store.
   * @param storage
   * Current storage node to save.
   */
  void
  storeNodes(aiNode* current, SPtr<Node> storage);
  /**
   * @brief
   * Stores the animation info.
   *
   * @description
   * Stores the Assimp animation info to my own.
   *
   * @param anim
   * The hole animation info.
   */
  void
  storeAnim(aiAnimation* anim);

  /**
   * The global time of the animation.
   */
  float m_totalTime = 0.0f; // TODO Remove this. The mesh ask for its specific total time
  /**
   * Animation frame rate.
   */
  float m_ticksPerSecond = 0.0f;
  /**
   * Total duration in time of the animation.
   */
  float m_duration = 0.0f;
  /**
   * The animation name.
   */
  String m_name;

  /**
   * The number of animation channels.
   */
  uint32 m_channelsCount;
  /**
   * The animation channels
   */
  Vector<AnimNode> m_channels;

  SPtr<Node> m_rootNode = nullptr;
};
}
