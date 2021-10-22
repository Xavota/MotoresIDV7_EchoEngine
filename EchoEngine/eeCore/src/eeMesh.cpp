#include "eeMesh.h"

namespace eeEngineSDK {
Mesh::~Mesh()
{
  m_vertexData->Release();
  m_indexData->Release();
}
bool
Mesh::loadFromArray(const Vector<SimplexVertex>& vertices, 
                    const Vector<uint16>& indices)
{
  if (vertices.empty() || indices.empty())
  {
    std::cout << "Empty info loading mesh" << std::endl;
    return false;
  }

  m_vertexData = std::make_shared<Buffer>();
  m_indexData = std::make_shared<Buffer>();
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(SimplexVertex),
                         sizeof(SimplexVertex), 
                         reinterpret_cast<const Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint16),
                        sizeof(uint16),
                        reinterpret_cast<const Byte*>(indices.data()));

  constructBuffers();

  return true;
}
bool
Mesh::loadFromArray(const Vector<SimpleVertex>& vertices, 
                    const Vector<uint16>& indices)
{
  if (vertices.empty() || indices.empty())
  {
    std::cout << "Empty info loading mesh" << std::endl;
    return false;
  }

  m_vertexData = std::make_shared<Buffer>();
  m_indexData = std::make_shared<Buffer>();
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(SimpleVertex),
                         sizeof(SimpleVertex), 
                         reinterpret_cast<const Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint16),
                        sizeof(uint16),
                        reinterpret_cast<const Byte*>(indices.data()));

  constructBuffers();

  return true;
}
bool
Mesh::loadFromArray(const Vector<ComplexVertex>& vertices,
                    const Vector<uint16>& indices)
{
  if (vertices.empty() || indices.empty())
  {
    std::cout << "Empty info loading mesh" << std::endl;
    return false;
  }

  m_vertexData = std::make_shared<Buffer>();
  m_indexData = std::make_shared<Buffer>();
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(ComplexVertex),
                         sizeof(ComplexVertex),
                         reinterpret_cast<const Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint16),
                         sizeof(uint16),
                         reinterpret_cast<const Byte*>(indices.data()));

  constructBuffers();
  return true;
}
bool
Mesh::loadFromArray(const Vector<SimpleAnimVertex>& vertices,
                    const Vector<uint16>& indices)
{
  if (vertices.empty() || indices.empty())
  {
    std::cout << "Empty info loading mesh" << std::endl;
    return false;
  }

  m_vertexData = std::make_shared<Buffer>();
  m_indexData = std::make_shared<Buffer>();
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(SimpleAnimVertex),
                         sizeof(SimpleAnimVertex),
                         reinterpret_cast<const Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint16),
                        sizeof(uint16),
                        reinterpret_cast<const Byte*>(indices.data()));

  constructBuffers();
  return true;
}
bool
Mesh::loadFromArray(const Vector<ComplexAnimVertex>& vertices,
                    const Vector<uint16>& indices)
{
  if (vertices.empty() || indices.empty())
  {
    std::cout << "Empty info loading mesh" << std::endl;
    return false;
  }

  m_vertexData = std::make_shared<Buffer>();
  m_indexData = std::make_shared<Buffer>();
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(ComplexAnimVertex),
                         sizeof(ComplexAnimVertex),
                         reinterpret_cast<const Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint16),
                        sizeof(uint16),
                        reinterpret_cast<const Byte*>(indices.data()));

  constructBuffers();
  return true;
}
bool
Mesh::loadFromArray(const Vector<SimplexVertex>& vertices,
                    const Vector<uint32>& indices)
{
  if (vertices.empty() || indices.empty())
  {
    std::cout << "Empty info loading mesh" << std::endl;
    return false;
  }

  m_vertexData = std::make_shared<Buffer>();
  m_indexData = std::make_shared<Buffer>();
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(SimplexVertex),
                         sizeof(SimplexVertex),
                         reinterpret_cast<const Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint32),
                        sizeof(uint32),
                        reinterpret_cast<const Byte*>(indices.data()));

  constructBuffers();

  return true;
}
bool
Mesh::loadFromArray(const Vector<SimpleVertex>& vertices,
                    const Vector<uint32>& indices)
{
  if (vertices.empty() || indices.empty())
  {
    std::cout << "Empty info loading mesh" << std::endl;
    return false;
  }

  m_vertexData = std::make_shared<Buffer>();
  m_indexData = std::make_shared<Buffer>();
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(SimpleVertex),
                         sizeof(SimpleVertex),
                         reinterpret_cast<const Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint32),
                        sizeof(uint32),
                        reinterpret_cast<const Byte*>(indices.data()));

  constructBuffers();

  return true;
}
bool
Mesh::loadFromArray(const Vector<ComplexVertex>& vertices,
                    const Vector<uint32>& indices)
{
  if (vertices.empty() || indices.empty())
  {
    std::cout << "Empty info loading mesh" << std::endl;
    return false;
  }

  m_vertexData = std::make_shared<Buffer>();
  m_indexData = std::make_shared<Buffer>();
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(ComplexVertex),
                         sizeof(ComplexVertex),
                         reinterpret_cast<const Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint32),
                        sizeof(uint32),
                        reinterpret_cast<const Byte*>(indices.data()));

  constructBuffers();
  return true;
}
bool
Mesh::loadFromArray(const Vector<SimpleAnimVertex>& vertices,
                    const Vector<uint32>& indices)
{
  if (vertices.empty() || indices.empty())
  {
    std::cout << "Empty info loading mesh" << std::endl;
    return false;
  }

  m_vertexData = std::make_shared<Buffer>();
  m_indexData = std::make_shared<Buffer>();
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(SimpleAnimVertex),
                         sizeof(SimpleAnimVertex),
                         reinterpret_cast<const Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint32),
                        sizeof(uint32),
                        reinterpret_cast<const Byte*>(indices.data()));

  constructBuffers();
  return true;
}
bool
Mesh::loadFromArray(const Vector<ComplexAnimVertex>& vertices,
                    const Vector<uint32>& indices)
{
  if (vertices.empty() || indices.empty())
  {
    std::cout << "Empty info loading mesh" << std::endl;
    return false;
  }

  m_vertexData = std::make_shared<Buffer>();
  m_indexData = std::make_shared<Buffer>();
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(ComplexAnimVertex),
                         sizeof(ComplexAnimVertex),
                         reinterpret_cast<const Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint32),
                        sizeof(uint32),
                        reinterpret_cast<const Byte*>(indices.data()));

  constructBuffers();
  return true;
}
const SPtr<Buffer> 
Mesh::getVertexData() const
{
  return m_vertexData;
}
const SPtr<Buffer> 
Mesh::getIndexData() const
{
  return m_indexData;
}
}