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

/**
 * @brief
 * A node for the animation graph.
 */
struct Node
{
  String m_name;
  Matrix4f m_transformation;
  Node* m_parent = nullptr;
  uint32 m_childrenCount = 0;
  Vector<Node*> m_children;
};

/**
 * @brief
 * Vector key frame, for position and scale key frames.
 */
struct VectorKeyFrame
{
  double m_time;
  Vector3f m_value;
};

/**
 * @brief
 * Quaternion key frame, for rotation key frames.
 */
struct QuatKeyFrame
{
  double m_time;
  aiQuaternion* m_value;  // TODO: CAMBIAR A MI CUATERNION
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
  loadFromFile(String fileName);
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
  storeNodes(aiNode* current, Node* storage);

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
                    const aiNode* pNode,
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
  *
  * @return
  * The node that is been looking, nullptr if not found.
  */
  aiNodeAnim*
  findNodeAnim(aiAnimation* anim, String name);

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
                          const aiNodeAnim* pNodeAnim,
                          aiVector3D& out);
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
                           const aiNodeAnim* pNodeAnim,
                           aiQuaternion& out);
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
                           const aiNodeAnim* pNodeAnim,
                           aiVector3D& out);
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
  findScaling(float animationTime, const aiNodeAnim* pNodeAnim);
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
  findRotation(float animationTime, const aiNodeAnim* pNodeAnim);
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
  findPosition(float animationTime, const aiNodeAnim* pNodeAnim);

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
  * The global time of the animation.
  */
  float m_totalTime = 0.0f;
  /**
  * Animation frame rate.
  */
  float m_ticksPerSecond = 0.0f;
  /**
  * Total duration in time of the animation.
  */
  float m_duration = 0.0f;
  /**
  * The animation name
  */
  String m_name;

  /**
  * The animation node of Assimp // TODO: CHANGE IT TO MY OWN ANIMATION TYPES.
  */
  aiAnimation* m_anim = nullptr;
  /**
  * The root of the animation graph.
  */
  aiNode* m_root = nullptr;

  //Vector<AnimNode> m_channels;
  //Node* m_rootNode = nullptr;
};
}
