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

    m_vertexArray = other.m_vertexArray;
    m_indexArray = other.m_indexArray;
    
    m_indexCount = other.m_indexCount;
  }
}

BoneMesh::BoneMesh(const Vector<ComplexBigAnimVertex<4>>& vertices,
                   const Vector<uint32>& indices)
{
  loadFromArray(vertices, indices);
}
BoneMesh::~BoneMesh()
{
  MemoryManager::instance().safeRelease(m_vertexData);
  MemoryManager::instance().safeRelease(m_indexData);
}

bool 
BoneMesh::loadFromArray(const Vector<ComplexBigAnimVertex<4>>& vertices,
                        const Vector<uint32>& indices)
{
  auto& graphicsApi = GraphicsApi::instance();

  if (vertices.empty() || indices.empty()) {
    Logger::instance().consoleLog("Empty info loading mesh");
    return false;
  }

  if (!m_vertexData) {
    m_vertexData = graphicsApi.createVertexBufferPtr();
  }
  if (!m_indexData) {
    m_indexData = graphicsApi.createIndexBufferPtr();
  }
  m_vertexData->initData(vertices.size() * sizeof(ComplexBigAnimVertex<4>),
                         sizeof(ComplexBigAnimVertex<4>),
                         reinterpret_cast<const Byte*>(vertices.data()));
  m_indexData->initData(indices.size() * sizeof(uint32),
                        sizeof(uint32),
                        reinterpret_cast<const Byte*>(indices.data()));

  m_vertexArray = vertices;
  m_indexArray = indices;

  m_indexCount = m_indexArray.size();

  return true;
}
void
BoneMesh::set() const
{
  m_vertexData->set();
  m_indexData->set();
}
}