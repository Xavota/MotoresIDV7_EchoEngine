#include "eeMesh.h"

namespace eeEngineSDK {
Mesh::~Mesh()
{
  m_vertexData->Release();
  m_indexData->Release();
}
bool
Mesh::loadFromFile(String fileName)
{
  return false;
}
bool
Mesh::loadFromArray(Vector<SimpleVertex>& vertices, 
                    Vector<uint16>& indices)
{
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(SimpleVertex),
                         sizeof(SimpleVertex), 
                         reinterpret_cast<Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint16),
                        sizeof(uint16),
                        reinterpret_cast<Byte*>(indices.data()));

  return true;
}
bool
Mesh::loadFromArray(Vector<ComplexVertex>& vertices,
                    Vector<uint16>& indices)
{
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(ComplexVertex),
                         sizeof(ComplexVertex),
                         reinterpret_cast<Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint16),
                         sizeof(uint16),
                         reinterpret_cast<Byte*>(indices.data()));
  return true;
}
bool
Mesh::loadFromArray(Vector<SimpleAnimVertex>& vertices,
                    Vector<uint16>& indices)
{
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(SimpleAnimVertex),
                         sizeof(SimpleAnimVertex),
                         reinterpret_cast<Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint16),
                        sizeof(uint16),
                        reinterpret_cast<Byte*>(indices.data()));
  return true;
}
bool
Mesh::loadFromArray(Vector<ComplexAnimVertex>& vertices,
                    Vector<uint16>& indices)
{
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(ComplexAnimVertex),
                         sizeof(ComplexAnimVertex),
                         reinterpret_cast<Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint16),
                        sizeof(uint16),
                        reinterpret_cast<Byte*>(indices.data()));
  return true;
}
bool
Mesh::loadFromArray(Vector<SimpleVertex>& vertices,
                    Vector<uint32>& indices)
{
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(SimpleVertex),
                         sizeof(SimpleVertex),
                         reinterpret_cast<Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint32),
                        sizeof(uint32),
                        reinterpret_cast<Byte*>(indices.data()));

  return true;
}
bool
Mesh::loadFromArray(Vector<ComplexVertex>& vertices,
                    Vector<uint32>& indices)
{
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(ComplexVertex),
                         sizeof(ComplexVertex),
                         reinterpret_cast<Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint32),
                        sizeof(uint32),
                        reinterpret_cast<Byte*>(indices.data()));
  return true;
}
bool
Mesh::loadFromArray(Vector<SimpleAnimVertex>& vertices,
                    Vector<uint32>& indices)
{
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(SimpleAnimVertex),
                         sizeof(SimpleAnimVertex),
                         reinterpret_cast<Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint32),
                        sizeof(uint32),
                        reinterpret_cast<Byte*>(indices.data()));
  return true;
}
bool
Mesh::loadFromArray(Vector<ComplexAnimVertex>& vertices,
                    Vector<uint32>& indices)
{
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * sizeof(ComplexAnimVertex),
                         sizeof(ComplexAnimVertex),
                         reinterpret_cast<Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint32),
                        sizeof(uint32),
                        reinterpret_cast<Byte*>(indices.data()));
  return true;
}
}