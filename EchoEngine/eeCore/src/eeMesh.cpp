#include "eeMesh.h"

namespace eeEngineSDK {
Mesh::~Mesh()
{
  MemoryManager::instance().safeRelease(m_vertexData);
  MemoryManager::instance().safeRelease(m_indexData);
}
void
Mesh::set()
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