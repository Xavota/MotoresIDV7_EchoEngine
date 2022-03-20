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

namespace eeEngineSDK {
/**
 * @brief
 * The model to be rendered, contains meshes and textures.
 */
/*template<typename V, typename I>*/
class EE_CORE_EXPORT StaticMesh
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
   * @param name
   * The name of the staticMesh resource.
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
  //template<typename V, typename I>
  StaticMesh(const Vector<Mesh/*<V,I>*/>& meshes,
             const String& name,
             const Vector3f& furtherVertexPosition,
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
   * @param name
   * The name of the staticMesh resource.
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
  //template<typename V, typename I>
  StaticMesh(const Vector<Pair<Mesh/*<V, I>*/, SPtr<Material>>>& meshes,
             const String& name,
             const Vector3f& furtherVertexPosition,
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
   * @param name
   * The name of the staticMesh resource.
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
  //template<typename V, typename I>
  bool
  loadFromMeshes(const Vector<Mesh/*<V,I>*/>& meshes,
                 const String& name,
                 const Vector3f& furtherVertexPosition,
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
   * @param name
   * The name of the staticMesh resource.
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
  //template<typename V, typename I>
  bool
  loadFromMeshes(const Vector<Pair<Mesh/*<V,I>*/, SPtr<Material>>>& meshes,
                 const String& name,
                 const Vector3f& furtherVertexPosition,
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
  //template<typename V, typename I>
  Vector<Pair<Mesh/*<V,I>*/, SPtr<Material>>>
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
  virtual Vector<SPtr<Material>>
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
  setTexture(SPtr<Material> texture, SIZE_T index);

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
  static SPtr<StaticMesh> cube;
  /**
   * A pre-charged tetrahedron model
   */
  static SPtr<StaticMesh> tetrahedron;
  /**
   * A pre-charged cone model
   */
  static SPtr<StaticMesh> cone;
  /**
   * A pre-charged cylinder model
   */
  static SPtr<StaticMesh> cylinder;
  /**
   * A pre-charged sphere model
   */
  static SPtr<StaticMesh> sphere;
  /**
   * A pre-charged capsule model
   */
  static SPtr<StaticMesh> capsule;
  /**
   * A pre-charged SAQ model
   */
  static SPtr<StaticMesh> SAQ;

 private:
  /**
   * The vector of pairs of meshes and texture indices.
   */
  Vector<Pair<Mesh, SPtr<Material>>> m_meshes;
  /**
   * The resource name.
   */
  String m_name;

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
