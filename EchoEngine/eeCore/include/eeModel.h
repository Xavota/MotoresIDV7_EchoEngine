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




  static void initPrimitives();

  static SPtr<Model> cube;
  static SPtr<Model> tetrahedron;
  static SPtr<Model> cone;
  static SPtr<Model> cylinder;
  static SPtr<Model> sphere;
  static SPtr<Model> capsule;

 private:
  /**
  * The vector of pairs of meshes and texture indices.
  */
  Vector<Pair<SPtr<Mesh>, uint8>> m_meshes;
  /**
  * The vector of textures for the meshes.
  */
  Vector<SPtr<Texture>> m_textures;
};
}
