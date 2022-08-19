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

#include "eeResource.h"

namespace eeEngineSDK {
/**
 * @brief
 * A node for the animation graph.
 */
struct Node 
{
  /**
   * The name of the node.
   */
  String m_name;
  /**
   * The transformation of the node.
   */
  Matrix4f m_transformation;
  /**
   * The parent of the node.
   */
  WPtr<Node> m_pParent;
  /**
   * The number of children of the node.
   */
  uint32 m_childrenCount = 0;
  /**
   * The children of the node.
   */
  Vector<SPtr<Node>> m_pChildren;
};

/**
 * @brief
 * Vector key frame, for position and scale key frames.
 */
struct VectorKeyFrame
{
  /**
   * The time that the key frame is on.
   */
  float m_time = 0.0f;
  /**
   * The value of the key frame.
   */
  Vector3f m_value = Vector3f(0.0f, 0.0f, 0.0f);
};

/**
 * @brief
 * Quaternion key frame, for rotation key frames.
 */
struct QuatKeyFrame
{
  /**
   * The time that the key frame is on.
   */
  float m_time = 0.0f;
  /**
   * The value of the key frame.
   */
  Quaternion m_value = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
};

/**
 * @brief
 * Animation node, with it's key frames.
 */
struct AnimNode
{
  /**
   * The name of the node.
   */
  String m_name;

  /**
   * The number of position keys.
   */
  uint32 m_positionKeysCount;
  /**
   * The number of position keys.
   */
  uint32 m_rotationKeysCount;
  /**
   * The number of position keys.
   */
  uint32 m_scalingKeysCount;

  /**
   * The position key frames.
   */
  Vector<VectorKeyFrame> m_positionKeys;
  /**
   * The rotation key frames.
   */
  Vector<QuatKeyFrame> m_rotationKeys;
  /**
   * The scaling key frames.
   */
  Vector<VectorKeyFrame> m_scalingKeys;
};

/**
 * @brief
 * The animation resource. Contains the bones transformations.
 */
class EE_CORE_EXPORT Animation : public Resource
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  Animation() = default;
  /**
   * @brief
   * Loads an animation.
   *
   * @description
   * Loads the animation from a file.
   *
   * @param ticksPerSecond
   * The number of frames per second the animation is gonna run. 1 over the
   * seconds each frame last.
   * @param duration
   * The total time of the animation.
   * @param channels
   * The key frames of all the nodes on the animation.
   * @param rootNode
   * The root of the nodes tree of the animation.
   *
   * @return
   * If it succeeded to load.
   */
  Animation(float ticksPerSecond,
            float duration,
            const Vector<AnimNode>& channels,
            SPtr<Node> pRootNode);
  /**
   * @brief
   * Default destructor.
   */
  ~Animation() = default;

  /**
   * @brief
   * Loads an animation.
   *
   * @description
   * Loads the animation from a file.
   *
   * @param ticksPerSecond
   * The number of frames per second the animation is gonna run. 1 over the
   * seconds each frame last.
   * @param duration
   * The total time of the animation.
   * @param channels
   * The key frames of all the nodes on the animation.
   * @param rootNode
   * The root of the nodes tree of the animation.
   *
   * @return
   * If it succeeded to load.
   */
  bool
  loadFromData(float ticksPerSecond,
               float duration,
               const Vector<AnimNode>& channels,
               SPtr<Node> pRootNode);

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
  boneTransform(SIZE_T meshIndex,
                WPtr<Skeletal> pSkMesh,
                float time);
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
                    const WPtr<Node> pNode,
                    const Matrix4f& parentTransform,
                    SIZE_T meshIndex,
                    WPtr<Skeletal> pSkMesh);

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
   * True if it found the animation node.
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
   * Getter for the ticks per second.
   *
   * @description
   * Returns the value of ticks per second of the animation.
   *
   * @return
   * The value of ticks per second of the animation.
   */
  FORCEINLINE float
  getTicksPerSecond() const
  {
    return m_ticksPerSecond;
  }
  /**
   * @brief
   * Getter for the duration.
   *
   * @description
   * Returns the value of the duration of the animation.
   *
   * @return
   * The value of the duration of the animation.
   */
  FORCEINLINE float
  getDuration() const
  {
    return m_duration;
  }
  /**
   * @brief
   * Getter for the channels.
   *
   * @description
   * Returns the channels of the animation.
   *
   * @return
   * The channels of the animation.
   */
  FORCEINLINE const Vector<AnimNode>&
  getChannels() const
  {
    return m_channels;
  }
  /**
   * @brief
   * Getter for the root node.
   *
   * @description
   * Returns the root node of the animation.
   *
   * @return
   * The root node of the animation.
   */
  FORCEINLINE SPtr<Node>
  getRootNode() const
  {
    return m_pRootNode;
  }

 private:
  /**
   * Animation frame rate.
   */
  float m_ticksPerSecond = 0.0f;
  /**
   * Total duration in time of the animation.
   */
  float m_duration = 0.0f;

  /**
   * The number of animation channels.
   */
  SIZE_T m_channelsCount = 0u;
  /**
   * The animation channels.
   */
  Vector<AnimNode> m_channels;

  /**
   * The root node of the animation.
   */
  SPtr<Node> m_pRootNode = nullptr;
};
}
