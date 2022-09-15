/************************************************************************/
/**
 * @file eeMesh.h
 * @author Diego Castellanos
 * @date 06/10/21
 * @brief
 * The meshes to be rendered, described by vertices and indices.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

#include <eeLogger.h>

#include <eeVertex.h>
#include <eeTriangle.h>

#include <eeTriangle.h>
#include "eeVertexBuffer.h"
#include "eeIndexBuffer.h"
#include "eeGraficsApi.h"

namespace eeEngineSDK {
/**
 * @brief
 * The meshes to be rendered, described by vertices and indices. 
 */
namespace eVertexType {
enum E : uint8
{
  kNone = 0,
  kSimple,
  kComplex,
  kControlPoints
};
}
/**
 * @brief
 * The meshes to be rendered, described by vertices and indices. 
 */
class EE_CORE_EXPORT Mesh
{
 public:
  /**
   * @brief
   * Default constructor
   */
  Mesh() = default;
  /**
   * @brief
   * Initializes the mesh.
   *
   * @description
   * Initializes the mesh from an array of vertex and index.
   *
   * @param vertices
   * The vertex data.
   * @param indices
   * The index data.
   */
  Mesh(const Vector<ComplexVertex>& vertices,
       const Vector<uint32>& indices);
  /**
   * @brief
   * Default destructor
   */
  virtual
  ~Mesh() = default;

  /**
   * @brief
   * Initializes the mesh.
   *
   * @description
   * Initializes the mesh from an array of vertex and index.
   *
   * @param vertices
   * The vertex data.
   * @param indices
   * The index data.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  bool
  loadFromVertexArray(const Vector<ComplexVertex>& vertices,
                      const Vector<uint32>& indices);
  /**
   * @brief
   * Initializes the mesh.
   *
   * @description
   * Initializes the mesh from an array of triangles.
   *
   * @param triangles
   * The triangles array.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  bool
  loadFromTrianglesArray(const Vector<Triangle>& triangles,
                         const Vector<uint32>& indices = {});
  
  /**
   * @brief
   * Initializes the mesh.
   *
   * @description
   * Initializes the mesh from an array of vertex and index.
   *
   * @param vertices
   * The vertex data.
   * @param indices
   * The index data.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  bool
  loadFromControlPoints(const Vector<ComplexVertex>& vertices);

  /**
   * @brief
   * Getter for the vertex data.
   *
   * @description
   * Returns the pointer to the vertex buffer.
   *
   * @return
   * Pointer to the vertex buffer.
   */
  virtual const WPtr<VertexBuffer>
  getVertexData() const;
  /**
   * @brief
   * Getter for the index data.
   *
   * @description
   * Returns the pointer to the index buffer.
   *
   * @return
   * Pointer to the index buffer.
   */
  virtual const WPtr<IndexBuffer>
  getIndexData() const;
  
  /**
   * @brief
   * Getter for the vertex type.
   *
   * @description
   * Returns the type of vertices that are stored.
   *
   * @return
   * The type of vertices that are stored.
   */
  FORCEINLINE eVertexType::E
  getVertexType() const
  {
    return m_vertexType;
  }
  /**
   * @brief
   * Getter for the vertex count.
   *
   * @description
   * Returns the number of vertices stored.
   *
   * @return
   * The number of vertices stored.
   */
  FORCEINLINE SIZE_T
  getVertexCount() const
  {
    return m_vertexArray.size() * 3;
  }
  /**
   * @brief
   * Getter for the triangles count.
   *
   * @description
   * Returns the number of triangles stored.
   *
   * @return
   * The number of triangles stored.
   */
  FORCEINLINE SIZE_T
  getTrianglesCount() const
  {
    return m_vertexArray.size();
  }
  /**
   * @brief
   * Getter for the control points count.
   *
   * @description
   * Returns the number of control points stored.
   *
   * @return
   * The number of control points stored.
   */
  FORCEINLINE SIZE_T
  getControlPointsCount() const
  {
    return m_controlPoints.size();
  }

  /**
   * @brief
   * Getter for the index count.
   *
   * @description
   * Returns the number of indices stored.
   *
   * @return
   * The number of indices stored.
   */
  FORCEINLINE SIZE_T
  getIndexCount() const
  {
    return m_indexCount;
  }
  
  /**
   * @brief
   * Getter for the triangles array.
   *
   * @description
   * Returns the array of triangles that form this mesh.
   *
   * @return
   * The array of triangles that form this mesh.
   */
  FORCEINLINE const Vector<Triangle>&
  getTrianglesArray() const
  {
    return m_vertexArray;
  }
  /**
   * @brief
   * Getter for the control points array.
   *
   * @description
   * Returns the control points array of the mesh.
   *
   * @return
   * The control points array of the mesh.
   */
  FORCEINLINE const Vector<ComplexVertex>&
  getControlPointsArray() const
  {
    return m_controlPoints;
  }

  /**
   * @brief
   * Getter for the indices array.
   *
   * @description
   * Returns the indices array of the mesh.
   *
   * @return
   * The indices array of the mesh.
   */
  FORCEINLINE const Vector<uint32>&
  getIndicesArray() const
  {
    return m_indexArray;
  }

  /**
   * @brief
   * Set to graphics api.
   *
   * @description
   * Sets the mesh for the graphic memory to use, only for override in graphics
   * api specializations.
   */
  virtual void
  set() const;


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
   * @brief
   * Creates a sphere primitive.
   *
   * @description
   * Creates a sphere primitive mesh, divided in parts in vertical and
   * horizontal axis.
   * 
   * @param verticalParts
   * The number of parts in the vertical axis.
   * @param horizontalParts
   * The number of parts in the horizontal axis.
   * @param outMesh
   * The output mesh.
   * 
   * @return
   * Returns a sphere mesh.
   */
  static bool
  getSpherePrimitive(float radius,
                     uint32 verticalParts,
                     uint32 horizontalParts,
                     Mesh& outMesh);
  
  /**
   * @brief
   * Copies a mesh.
   *
   * @description
   * Returns the given mesh but with its vertices transformed with using the
   * given model matrix.
   * 
   * @param meshToCopy
   * The mesh to copy.
   * @param horizontalParts
   * The transform matrix to transform the new mesh.
   * 
   * @return
   * The copy of the mesh, transformed with the matrix.
   */
  static void
  copyMeshTransformed(const Mesh& meshToCopy,
                     const Matrix4f& transformMatrix,
                     Mesh& outNewMesh);


  
  /**
   * A pre-charged cube model
   */
  static Mesh cube;
  /**
   * A pre-charged tetrahedron model
   */
  static Mesh tetrahedron;
  /**
   * A pre-charged cone model
   */
  static Mesh cone;
  /**
   * A pre-charged cylinder model
   */
  static Mesh cylinder;
  /**
   * A pre-charged sphere model
   */
  static Mesh sphere;
  /**
   * A pre-charged capsule model
   */
  static Mesh capsule;

 protected:
  /**
   * The vertex buffer stored.
   */
  SPtr<VertexBuffer> m_vertexData;
  /**
   * The index buffer stored.
   */
  SPtr<IndexBuffer> m_indexData;

  /**
   * The vertex type.
   */
  eVertexType::E m_vertexType = eVertexType::kNone;
  /**
   * The vertices stored.
   */
  Vector<Triangle> m_vertexArray;
  /**
   * The control points for tessellation.
   */
  Vector<ComplexVertex> m_controlPoints;

  /**
   * The indices stored.
   */
  Vector<uint32> m_indexArray;
  /**
   * The number of indices.
   */
  SIZE_T m_indexCount = 0;
};
}
