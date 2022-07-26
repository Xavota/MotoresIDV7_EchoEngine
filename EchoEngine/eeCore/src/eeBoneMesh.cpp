#include "eeBoneMesh.h"

#include <eeMath.h>

#include <eeVertex.h>

namespace eeEngineSDK {
BoneMesh::BoneMesh(const BoneMesh& other)
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
BoneMesh::~BoneMesh()
{
  MemoryManager::instance().safeRelease(m_vertexData);
  MemoryManager::instance().safeRelease(m_indexData);
}
void
BoneMesh::set() const
{
  m_vertexData->set();
  m_indexData->set();
}
const WPtr<VertexBuffer>
BoneMesh::getVertexData() const
{
  return m_vertexData;
}
const WPtr<IndexBuffer> 
BoneMesh::getIndexData() const
{
  return m_indexData;
}
}