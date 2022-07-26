/******************************************************************************/
/**
 * @file eeOctreeNode.h
 * @author Diego Castellanos
 * @date 30/03/22
 * @brief
 * The Octree node, for the Octree. Each node has a model or 8 nodes below.
 *
 * @bug Not bug Known.
 */
 /*****************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeBox.h>

namespace eeEngineSDK {
/**
 * @brief
 * The Octree node, for the Octree. Each node has a model or 8 nodes below.
 */
class EE_CORE_EXPORT OctreeNode
{
 public:
  /**
   * @brief
   * Default constructor
   */
   OctreeNode() = default;
  /**
   * @brief
   * Default destructor
   */
  ~OctreeNode() = default;

  /**
   * @brief
   * Calculates the tree node.
   *
   * @description
   * Gets its static mesh, with all the meshes in the node, if it has more
   * triangles that allowed, it split the space in a new 8 nodes.
   *
   * @param space
   * The space the node will cover.
   * @param sMesh
   * The static mesh with all the meshes in the node.
   */
  void
  CalculateTree(const BoxAAB& space, WPtr<StaticMesh> sMesh);

  /**
   * @brief
   * Divides a mesh, into 2 meshes by a plane.
   *
   * @description
   * Divides a mesh, into 2 new static meshes using a plane.
   *
   * @param plane
   * The plane dividing the mesh.
   * @param sMesh
   * The static mesh with all the meshes to be divided.
   * 
   * @return
   * 2 new static meshes. that result from the division.
   */
  Vector<SPtr<StaticMesh>>
  DivideMesh(const Plane& plane,
             WPtr<StaticMesh> sMesh);

  /**
   * @brief
   * Getter for the meshes on this subtree.
   *
   * @description
   * Returns the meshes that are stored on this branch of the tree.
   *
   * @param meshesVec
   * The output vector of meshes.
   */
  void
  getMeshes(Vector<WPtr<StaticMesh>>& outMeshesVec);

 private:
  /**
   * The static mesh with all the meshes in the node.
   */
  SPtr<StaticMesh> m_nodeMesh;
  /**
   * The space the node will cover.
   */
  BoxAAB m_nodeSpace;

  /**
   * The children of this tree node.
   */
  Vector<SPtr<OctreeNode>> m_childNodes;
};
}
