/************************************************************************/
/**
 * @file eeMesh.h
 * @author Diego Castellanos
 * @date 06/10/21
 * @brief
 * The meshes to be renderized, described by vertices and indices.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include "eeVertex.h"
#include "eeVertexBuffer.h"
#include "eeIndexBuffer.h"
#include "eeGraficsApi.h"

namespace eeEngineSDK {
/**
 * @brief
 * The meshes to be renderized, described by vertices and indices. 
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
  * Default destructor
  */
  virtual
  ~Mesh();

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
  template<class V, class I>
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
  set();

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
  FORCEINLINE uint32
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
  * The vertex index stored.
  */
  SPtr<IndexBuffer> m_indexData;

  /**
  * The number of indices.
  */
  uint32 m_indexCount = 0u;
};

template<class V, class I>
bool 
Mesh::loadFromArray(const Vector<V>& vertices, 
                    const Vector<I>& indices)
{
  if (vertices.empty() || indices.empty())
  {
    std::cout << "Empty info loading mesh" << std::endl;
    return false;
  }

  if (!m_vertexData)
    m_vertexData = GraphicsApi::instance().getVertexBufferPtr();
  if (!m_indexData)
    m_indexData = GraphicsApi::instance().getIndexBufferPtr();
  m_vertexData->initData(static_cast<uint32>(vertices.size()) * sizeof(V),
    sizeof(V),
    reinterpret_cast<const Byte*>(vertices.data()));
  m_indexData->initData(static_cast<uint32>(indices.size()) * sizeof(I),
    sizeof(I),
    reinterpret_cast<const Byte*>(indices.data()));

  m_indexCount = static_cast<uint32>(indices.size());

  return true;
}
}
