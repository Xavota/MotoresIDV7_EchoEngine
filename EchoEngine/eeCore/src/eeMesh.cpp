#include "eeMesh.h"

namespace eeEngineSDK {
/*template<class V, class I>*/
Mesh/*<V,I>*/::Mesh(const Mesh& other)
{
  auto& graphicsApi = GraphicsApi::instance();
  if (!m_vertexData) {
    m_vertexData = graphicsApi.createVertexBufferPtr();
  }
  if (!m_indexData) {
    m_indexData = graphicsApi.createIndexBufferPtr();
  }

  if (other.m_vertexData) {
    m_vertexData->initData(other.m_vertexData->getDataSize(),
                           other.m_vertexData->getBatchSize(),
                           other.m_vertexData->getData().data());
  }
  if (other.m_indexData) {
    m_indexData->initData(other.m_indexData->getDataSize(),
                          other.m_indexData->getBatchSize(),
                          other.m_indexData->getData().data());
  }

  m_indexCount = other.m_indexCount;
}
/*template<class V, class I>*/
Mesh/*<V, I>*/::~Mesh()
{
  MemoryManager::instance().safeRelease(m_vertexData);
  MemoryManager::instance().safeRelease(m_indexData);
}
/*template<class V, class I>*/
void
Mesh/*<V, I>*/::set()
{
  m_vertexData->set();
  m_indexData->set();
}
/*template<class V, class I>*/
const SPtr<VertexBuffer>
Mesh/*<V, I>*/::getVertexData() const
{
  return m_vertexData;
}
/*template<class V, class I>*/
const SPtr<IndexBuffer> 
Mesh/*<V, I>*/::getIndexData() const
{
  return m_indexData;
}
}