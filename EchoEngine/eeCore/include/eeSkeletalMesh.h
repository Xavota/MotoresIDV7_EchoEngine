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

namespace eeEngineSDK {
/**
 * @brief
 * The skeletal mesh resource, contains meshes with bones data and a skeletal.
 */
class EE_CORE_EXPORT SkeletalMesh
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  SkeletalMesh() = default;
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
   * Initializes the model from a file and a skeletal mesh.
   *
   * @param fileName
   * The name of the file containing the model.
   * @param skMesh
   * The skeletal mesh from where it's gonna get the bone data.
   * @param textures
   * The textures for the meshes.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  virtual bool
  loadFromFile(const String& fileName,
               SPtr<Skeletal> skMesh,
               const Vector<SPtr<Texture>>& textures = {});
  /**
   * @brief
   * Initializes the model.
   *
   * @description
   * Initializes the model from an array of meshes.
   *
   * @param meshes
   * The array of meshes.
   * @param boundSphere
   * A resulting bounding sphere with the max distance to the center.
   * @param fileName
   * A resulting bounding box with the max points to the center.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  virtual bool
  loadFromMeshes(const Vector<SPtr<Mesh>>& meshes);
  /**
   * @brief
   * Initializes the model.
   *
   * @description
   * Initializes the model from an array of pairs of meshes and textures.
   *
   * @param meshes
   * The array of pair of meshes and textures.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  virtual bool
  loadFromMeshes(const Vector<Pair<SPtr<Mesh>, SPtr<Texture>>>& meshes);

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
  virtual Vector<Pair<SPtr<Mesh>, SPtr<Texture>>>
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
  virtual Vector<SPtr<Texture>>
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
  setTexture(SPtr<Texture> texture, int32 index);

  /**
   * @brief
   * Getter of the skeletal resource.
   *
   * @return
   * The skeletal mesh resource to store the bone data.
   */
  FORCEINLINE SPtr<Skeletal>
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
  Vector<Pair<SPtr<Mesh>, SPtr<Texture>>> m_meshes;

  /**
   * The skeletal with the bone data.
   */
  SPtr<Skeletal> m_skeleton;

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
