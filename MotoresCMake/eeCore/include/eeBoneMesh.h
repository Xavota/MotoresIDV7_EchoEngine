/************************************************************************/
/**
 * @file eeBoneMesh.h
 * @author Diego Castellanos
 * @date 29/03/22
 * @brief
 * The meshes for the skeletal mesh to be rendered, described by vertices
 * indices and bone id and weights.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

#include <eeLogger.h>

#include <eeVertex.h>

#include <eeTriangle.h>
#include "eeVertexBuffer.h"
#include "eeIndexBuffer.h"
#include "eeGraficsApi.h"

namespace eeEngineSDK {
/**
 * @brief
 * The meshes for the skeletal mesh to be rendered, described by vertices
 * indices and bone id and weights.
 */
class EE_CORE_EXPORT BoneMesh
{
 public:
  /**
   * @brief
   * Default constructor
   */
  BoneMesh() = default;
  /**
   * @brief
   * Copy constructor
   */
  BoneMesh(const BoneMesh& other);
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
  template<typename V, typename I>
  BoneMesh(const Vector<V>& vertices,
           const Vector<I>& indices);
  /**
   * @brief
   * Default destructor
   */
  virtual
  ~BoneMesh();

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
  template<typename V, typename I>
  bool
  loadFromArray(const Vector<V>& vertices,
                const Vector<I>& indices);

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
   * Getter for the vertex data.
   *
   * @description
   * Returns the pointer to the vertex buffer.
   *
   * @return
   * Pointer to the vertex buffer.
   */
  virtual const SPtr<VertexBuffer>
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
  virtual const SPtr<IndexBuffer>
  getIndexData() const;

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
   * The vertices stored.
   */
  Vector<Vector4f> m_vertexArray;
  /**
   * The indices stored.
   */
  Vector<uint32> m_indexArray;

  /**
   * The number of indices.
   */
  SIZE_T m_indexCount = 0;
};

template<typename V, typename I>
inline BoneMesh::BoneMesh(const Vector<V>& vertices, const Vector<I>& indices)
{
  loadFromArray(vertices, indices);
}

template<typename V, typename I>
bool 
BoneMesh::loadFromArray(const Vector<V>& vertices,
                                  const Vector<I>& indices)
{
  auto& graphicsApi = GraphicsApi::instance();

  if (vertices.empty() || indices.empty()) {
    Logger::instance().ConsoleLog("Empty info loading mesh");
    return false;
  }

  if (!m_vertexData) {
    m_vertexData = graphicsApi.createVertexBufferPtr();
  }
  if (!m_indexData) {
    m_indexData = graphicsApi.createIndexBufferPtr();
  }
  m_vertexData->initData(vertices.size() * sizeof(V),
                         sizeof(V),
                         reinterpret_cast<const Byte*>(vertices.data()));
  m_indexData->initData(indices.size() * sizeof(I),
                        sizeof(I),
                        reinterpret_cast<const Byte*>(indices.data()));

  for (V ver : vertices) {
    m_vertexArray.push_back(ver.position);
  }

  m_indexCount = indices.size();

  return true;
}
}
