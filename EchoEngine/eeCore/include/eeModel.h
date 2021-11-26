/************************************************************************/
/**
 * @file eeModel.h
 * @author Diego Castellanos
 * @date 07/10/21
 * @brief
 * The model to be renderized, contains meshes and textures.
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
 * The model to be renderized, contains meshes and textures.
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
  * @param boundSphere
  * A resulting bounding sphere with the max distance to the center.
  * @param fileName
  * A resulting bounding box with the max points to the center.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  virtual bool
  loadFromFile(const String& fileName);
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
  loadFromMeshes(Vector<SPtr<Mesh>> meshes);
  /**
  * @brief
  * Initializes the model.
  *
  * @description
  * Initializes the model from an array of pairs of meshes and texture indices
  * and its respective textures.
  *
  * @param meshes
  * The array of pair of meshes and texture indices, indicating with texture it
  * will use.
  * @param textures
  * The array of textures for the model.
  * @param boundSphere
  * A resulting bounding sphere with the max distance to the center.
  * @param fileName
  * A resulting bounding box with the max points to the center.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  virtual bool
  loadFromMeshes(const Vector<Pair<SPtr<Mesh>, uint8>>& meshes,
                 const Vector<SPtr<Texture>>& textures);

  /**
  * @brief
  * Getter for the meshes data.
  *
  * @description
  * Returns the vector of pairs of meshes and texture indices.
  *
  * @return
  * The vector of pairs of meshes and texture indices.
  */
  virtual Vector<Pair<SPtr<Mesh>, uint8>>
  getMeshes();
  /**
  * @brief
  * Setter for the meshes data.
  *
  * @description
  * Sets a new array of meshes.
  *
  * @param meshes
  * The new array of meshes.
  */
  virtual void
  setMeshes(Vector<SPtr<Mesh>> meshes);
  /**
  * @brief
  * Setter for the meshes data.
  *
  * @description
  * Sets a new array of meshes.
  *
  * @param meshes
  * The new array of meshes with its texture indices.
  */
  virtual void
  setMeshes(Vector<Pair<SPtr<Mesh>, uint8>> meshes);
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
  * Setter for the textures.
  *
  * @description
  * Sets a new array of textures.
  *
  * @param textures
  * The new array of textures.
  */
  virtual void
  setTextures(Vector<SPtr<Texture>> textures);
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

  const Sphere&
  getBoundingSphere();
  const BoxAAB&
  getBoundingBox();


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
  Vector<Pair<SPtr<Mesh>, uint8>> m_meshes;
  /**
  * The vector of textures for the meshes.
  */
  Vector<SPtr<Texture>> m_textures;

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
