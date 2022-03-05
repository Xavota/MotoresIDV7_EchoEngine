#include "eeMesh.h"

namespace eeEngineSDK {
/*template<typename V, typename I>*/
Mesh/*<V,I>*/::Mesh(const Mesh& other)
{
  if (other.m_vertexData && other.m_vertexData->isValid()
   && other.m_indexData  && other.m_indexData->isValid()) {
    auto& graphicsApi = GraphicsApi::instance();
    if (!m_vertexData) {
      m_vertexData = graphicsApi.createVertexBufferPtr();
    }
    if (!m_indexData) {
      m_indexData = graphicsApi.createIndexBufferPtr();
    }

    m_vertexData->initData(other.m_vertexData->getDataSize(),
                           other.m_vertexData->getBatchSize(),
                           other.m_vertexData->getData().data());
    m_indexData->initData(other.m_indexData->getDataSize(),
                          other.m_indexData->getBatchSize(),
                          other.m_indexData->getData().data());
    
    m_indexCount = other.m_indexCount;
  }
}
/*template<typename V, typename I>*/
Mesh/*<V, I>*/::~Mesh()
{
  MemoryManager::instance().safeRelease(m_vertexData);
  MemoryManager::instance().safeRelease(m_indexData);
}
/*template<typename V, typename I>*/
void
Mesh/*<V, I>*/::set()
{
  m_vertexData->set();
  m_indexData->set();
}
/*template<typename V, typename I>*/
const SPtr<VertexBuffer>
Mesh/*<V, I>*/::getVertexData() const
{
  return m_vertexData;
}
/*template<typename V, typename I>*/
const SPtr<IndexBuffer> 
Mesh/*<V, I>*/::getIndexData() const
{
  return m_indexData;
}
}