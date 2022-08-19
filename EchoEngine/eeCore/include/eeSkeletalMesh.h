/************************************************************************/
/**
 * @file eeSkeletalMesh.h
 * @author Diego Castellanos
 * @date 27/11/21
 * @brief
 * The skeletal mesh resource, contains meshes with bones data and a skeletal.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeSphere.h>
#include <eeBox.h>

#include "eeBoneMesh.h"

#include "eeResource.h"

namespace eeEngineSDK {
/**
 * @brief
 * The skeletal mesh resource, contains meshes with bones data and a skeletal.
 */
class EE_CORE_EXPORT SkeletalMesh : public Resource
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  SkeletalMesh() = default;

  /**
   * @brief
   * Initializes the model.
   *
   * @description
   * Initializes the model from an array of meshes.
   *
   * @param meshes
   * The array of meshes.
   * @param skeleton
   * The skeleton resource for the skeletal mesh.
   * @param furtherVertexPosition
   * The position of the vertex most far away from the origin.
   * @param maxCoordinate
   * The max coordinate of all vertex positions.
   * @param minCoordinate
   * The min coordinate of all vertex positions.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  SkeletalMesh(const Vector<BoneMesh>& meshes,
               WPtr<Skeletal> skeleton,
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
   * @param skeleton
   * The skeleton resource for the skeletal mesh.
   * @param furtherVertexPosition
   * The position of the vertex most far away from the origin.
   * @param maxCoordinate
   * The max coordinate of all vertex positions.
   * @param minCoordinate
   * The min coordinate of all vertex positions.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  SkeletalMesh(const Vector<Pair<BoneMesh, WPtr<Material>>>& meshes,
               WPtr<Skeletal> skeleton,
               float furtherDist,
               const Vector3f& maxCoordinate,
               const Vector3f& minCoordinate);
  /**
   * @brief
   * Default destructor.
   */
  ~SkeletalMesh() = default;

  /**
   * @brief
   * Initializes the model.
   *
   * @description
   * Initializes the model from an array of meshes.
   *
   * @param meshes
   * The array of meshes.
   * @param skeleton
   * The skeleton resource for the skeletal mesh.
   * @param furtherVertexPosition
   * The position of the vertex most far away from the origin.
   * @param maxCoordinate
   * The max coordinate of all vertex positions.
   * @param minCoordinate
   * The min coordinate of all vertex positions.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  virtual bool
  loadFromMeshes(const Vector<BoneMesh>& meshes,
                 WPtr<Skeletal> skeleton,
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
   * @param skeleton
   * The skeleton resource for the skeletal mesh.
   * @param furtherVertexPosition
   * The position of the vertex most far away from the origin.
   * @param maxCoordinate
   * The max coordinate of all vertex positions.
   * @param minCoordinate
   * The min coordinate of all vertex positions.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  virtual bool
  loadFromMeshes(const Vector<Pair<BoneMesh, WPtr<Material>>>& meshes,
                 WPtr<Skeletal> skeleton,
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
  virtual Vector<Pair<BoneMesh, WPtr<Material>>>
  getMeshes();
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
  setTexture(WPtr<Material> texture, uint32 index);

  /**
   * @brief
   * Getter of the skeletal resource.
   *
   * @return
   * The skeletal mesh resource to store the bone data.
   */
  FORCEINLINE WPtr<Skeletal>
  getSkeletal()
  {
    return m_skeleton;
  }

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
   * Gets the bound sphere distance in space for the model.
   *
   * @description
   * Returns the furthest distance to the origin of the model.
   *
   * @return
   * The furthest distance to the origin of the model.
   */
  const Vector3f&
  getFurtherPosition();
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
  Vector<Pair<BoneMesh, WPtr<Material>>> m_meshes;

  /**
   * The skeletal with the bone data.
   */
  WPtr<Skeletal> m_skeleton;

  /**
   * A sphere bounding all the model.
   */
  Sphere m_boundSphere;
  /**
   * The bound sphere distance in space.
   */
  Vector3f m_furtherPosition = Vector3f(0.0f, 0.0f, 0.0f);
  /**
   * A cube bounding all the model.
   */
  BoxAAB m_boundCube;
};
}
