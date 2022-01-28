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
#include "eeMesh.h"
#include <eeSphere.h>
#include <eeBox.h>

namespace eeEngineSDK {
/**
 * @brief
 * The model to be rendered, contains meshes and textures.
 */
class EE_CORE_EXPORT Model
{
 public: 
  /**
   * @brief
   * Default constructor
   */
  Model() = default;
  /**
   * @brief
   * Default destructor
   */
  virtual 
  ~Model() = default;

  /**
   * @brief
   * Initializes the model.
   *
   * @description
   * Initializes the model from a file.
   *
   * @param fileName
   * The name of the file containing the model.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  virtual bool
  loadFromFile(const String& fileName,
               const String& name,
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
  loadFromMeshes(Vector<SPtr<Mesh>> meshes,
                 const String& name);
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
  loadFromMeshes(const Vector<Pair<SPtr<Mesh>, SPtr<Texture>>>& meshes,
                 const String& name);

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
   * Getter for the resource name.
   *
   * @description
   * Returns the resource name.
   *
   * @return
   * The resource name.
   */
  virtual String
  getName();

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

  /**
   * @brief
   * Initializes the primitive models.
   *
   * @description
   * Initializes the primitive pre-charged models.
   */
  static void
  initPrimitives();

  /**
   * A pre-charged cube model
   */
  static SPtr<Model> cube;
  /**
   * A pre-charged tetrahedron model
   */
  static SPtr<Model> tetrahedron;
  /**
   * A pre-charged cone model
   */
  static SPtr<Model> cone;
  /**
   * A pre-charged cylinder model
   */
  static SPtr<Model> cylinder;
  /**
   * A pre-charged sphere model
   */
  static SPtr<Model> sphere;
  /**
   * A pre-charged capsule model
   */
  static SPtr<Model> capsule;
  /**
   * A pre-charged SAQ model
   */
  static SPtr<Model> SAQ;

 private:
  /**
   * The vector of pairs of meshes and texture indices.
   */
  Vector<Pair<SPtr<Mesh>, SPtr<Texture>>> m_meshes;
  /**
   * The resource name.
   */
  String m_name;

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
