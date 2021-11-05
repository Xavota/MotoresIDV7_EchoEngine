#include "eeMesh.h"

namespace eeEngineSDK {
Mesh::~Mesh()
{
  m_vertexData->release();
  m_indexData->release();
}
void Mesh::set()
{
  m_vertexData->set();
  m_indexData->set();
}
const SPtr<VertexBuffer>
Mesh::getVertexData() const
{
  return m_vertexData;
}
const SPtr<IndexBuffer> 
Mesh::getIndexData() const
{
  return m_indexData;
}
}