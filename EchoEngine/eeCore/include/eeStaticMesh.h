/************************************************************************/
/**
 * @file eeModel.h
 * @author Diego Castellanos
 * @date 07/10/21
 * @brief
 * The model to be rendered, contains meshes and textures.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeSphere.h>
#include <eeBox.h>

#include "eeMesh.h"

#include "eeResource.h"

namespace eeEngineSDK {
/**
 * @brief
 * The model to be rendered, contains meshes and textures.
 */
class EE_CORE_EXPORT StaticMesh : public Resource
{
 public: 
  /**
   * @brief
   * Default constructor
   */
  StaticMesh() = default;
  /**
   * @brief
   * Initializes the model.
   *
   * @description
   * Initializes the model from an array of meshes.
   *
   * @param meshes
   * The array of meshes.
   * @param furtherDist
   * The distance to the vertex most far away from the origin.
   * @param maxCoordinate
   * The max coordinate of all vertex positions.
   * @param minCoordinate
   * The min coordinate of all vertex positions.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  StaticMesh(const Vector<Mesh>& meshes,
             float furtherDist,
             const Vector3f& maxCoordinate,
             const Vector3f& minCoordinate);
  /**
   * @brief
   * Initializes the model.
   *
   * @description
   * Initializes the model from an array of pairs of meshes and textures.
   *
   * @param meshes
   * The array of pair of meshes and textures.
   * @param furtherDist
   * The distance to the vertex most far away from the origin.
   * @param maxCoordinate
   * The max coordinate of all vertex positions.
   * @param minCoordinate
   * The min coordinate of all vertex positions.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  StaticMesh(const Vector<Pair<Mesh, WPtr<Material>>>& meshes,
             float furtherDist,
             const Vector3f& maxCoordinate,
             const Vector3f& minCoordinate);
  /**
   * @brief
   * Default destructor
   */
  virtual 
  ~StaticMesh() = default;

  /**
   * @brief
   * Initializes the model.
   *
   * @description
   * Initializes the model from an array of meshes.
   *
   * @param meshes
   * The array of meshes.
   * @param furtherDist
   * The distance to the vertex most far away from the origin.
   * @param maxCoordinate
   * The max coordinate of all vertex positions.
   * @param minCoordinate
   * The min coordinate of all vertex positions.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  bool
  loadFromMeshes(const Vector<Mesh>& meshes,
                 float furtherDist,
                 const Vector3f& maxCoordinate,
                 const Vector3f& minCoordinate);
  /**
   * @brief
   * Initializes the model.
   *
   * @description
   * Initializes the model from an array of pairs of meshes and textures.
   *
   * @param meshes
   * The array of pair of meshes and textures.
   * @param furtherDist
   * The distance to the vertex most far away from the origin.
   * @param maxCoordinate
   * The max coordinate of all vertex positions.
   * @param minCoordinate
   * The min coordinate of all vertex positions.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  bool
  loadFromMeshes(const Vector<Pair<Mesh, WPtr<Material>>>& meshes,
                 float furtherDist,
                 const Vector3f& maxCoordinate,
                 const Vector3f& minCoordinate);

  /**
   * @brief
   * Getter for the meshes data.
   *
   * @description
   * Returns the vector of pairs of meshes and texture indices.
   *
   * @return
   * The vector of pairs of meshes and texture.
   */
  Vector<Pair<Mesh, WPtr<Material>>>
  getMeshes();
  /**
   * @brief
   * Getter for the meshes data.
   *
   * @description
   * Returns the vector of pairs of meshes and texture indices.
   *
   * @param outMeshes
   * The vector of pairs of meshes and texture.
   */
  void
  getMeshes(Vector<Pair<Mesh, WPtr<Material>>>& outMeshes);
  /**
   * @brief
   * Getter for the texture data.
   *
   * @description
   * Returns the vector of textures.
   *
   * @return
   * The vector of textures.
   */
  virtual Vector<WPtr<Material>>
  getTextures();
  /**
   * @brief
   * Setter for a texture.
   *
   * @description
   * Sets a new texture in the given index.
   *
   * @param texture
   * The new texture.
   * @param index
   * The index of the texture.
   */
  virtual void
  setTexture(WPtr<Material> texture, SIZE_T index);

  /**
   * @brief
   * Gets the bounding sphere for the model.
   *
   * @description
   * Returns a bounding sphere, with a radius of the furthest vertex to the
   * origin.
   *
   * @return
   * A bounding sphere, with a radius of the furthest vertex to the origin.
   */
  const Sphere&
  getBoundingSphere();
  /**
   * @brief
   * Gets the bounding box for the model.
   *
   * @description
   * Returns a bounding box, with corners on the furthest x, y, z coordinates.
   *
   * @return
   * A bounding box, with corners on the furthest x, y, z coordinates.
   */
  const BoxAAB&
  getBoundingBox();

 private:
  /**
   * The vector of pairs of meshes and texture indices.
   */
  Vector<Pair<Mesh, WPtr<Material>>> m_meshes;

  /**
   * A sphere bounding all the model.
   */
  Sphere m_boundSphere;
  /**
   * A cube bounding all the model.
   */
  BoxAAB m_boundCube;
};
}
