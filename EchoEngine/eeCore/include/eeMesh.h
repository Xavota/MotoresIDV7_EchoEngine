#pragma once
#include "eePrerequisitesCore.h"
#include "eeBuffer.h"
#include "eeVertex.h"

namespace eeEngineSDK {
class EE_CORE_EXPORT Mesh
{
 public:
  Mesh() = default;
  virtual
  ~Mesh();

  bool
  loadFromFile(String fileName);
  bool
  loadFromArray(Vector<SimpleVertex>& vertices,
                Vector<uint16>& indices);
  bool
  loadFromArray(Vector<ComplexVertex>& vertices,
                Vector<uint16>& indices);
  bool
  loadFromArray(Vector<SimpleAnimVertex>& vertices,
                Vector<uint16>& indices);
  template<int32 Size = 4>
  FORCEINLINE bool
  loadFromArray(Vector<SimpleBigAnimVertex<Size>>& vertices,
                Vector<uint16>& indices,
                const int32 size);
  bool
  loadFromArray(Vector<ComplexAnimVertex>& vertices,
                Vector<uint16>& indices);
  template<int32 Size = 4>
  FORCEINLINE bool
  loadFromArray(Vector<ComplexBigAnimVertex<Size>>& vertices,
                Vector<uint16>& indices,
                const int32 size);
  bool
  loadFromArray(Vector<SimpleVertex>& vertices,
                Vector<uint32>& indices);
  bool
  loadFromArray(Vector<ComplexVertex>& vertices,
                Vector<uint32>& indices);
  bool
  loadFromArray(Vector<SimpleAnimVertex>& vertices,
                Vector<uint32>& indices);
  template<int32 Size = 4>
  FORCEINLINE bool
  loadFromArray(Vector<SimpleBigAnimVertex<Size>>& vertices,
                Vector<uint32>& indices,
                const int32 size);
  bool
  loadFromArray(Vector<ComplexAnimVertex>& vertices,
                Vector<uint32>& indices);
  template<int32 Size = 4>
  FORCEINLINE bool
  loadFromArray(Vector<ComplexBigAnimVertex<Size>>& vertices,
                Vector<uint32>& indices,
                const int32 size);

 private:
  Buffer* m_vertexData;
  Buffer* m_indexData;
};
template<int32 Size>
FORCEINLINE bool 
Mesh::loadFromArray(Vector<SimpleBigAnimVertex<Size>>& vertices, 
                    Vector<uint16>& indices, 
                    const int32 size)
{
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * 
                         sizeof(SimpleBigAnimVertex<Size>),
                         sizeof(SimpleBigAnimVertex<Size>),
                         reinterpret_cast<Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint16),
                        sizeof(uint16),
                        reinterpret_cast<Byte*>(indices.data()));
  return true;
}
template<int32 Size>
FORCEINLINE bool
Mesh::loadFromArray(Vector<ComplexBigAnimVertex<Size>>& vertices,
                    Vector<uint16>& indices,
                    const int32 size)
{
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * 
                         sizeof(ComplexBigAnimVertex<Size>),
                         sizeof(ComplexBigAnimVertex<Size>),
                         reinterpret_cast<Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint16),
                        sizeof(uint16),
                        reinterpret_cast<Byte*>(indices.data()));
  return true;
}
template<int32 Size>
FORCEINLINE bool
Mesh::loadFromArray(Vector<SimpleBigAnimVertex<Size>>& vertices,
                    Vector<uint32>& indices,
                    const int32 size)
{
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * 
                         sizeof(SimpleBigAnimVertex<Size>),
                         sizeof(SimpleBigAnimVertex<Size>),
                         reinterpret_cast<Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint32),
                        sizeof(uint32),
                        reinterpret_cast<Byte*>(indices.data()));
  return true;
}
template<int32 Size>
FORCEINLINE bool
Mesh::loadFromArray(Vector<ComplexBigAnimVertex<Size>>& vertices,
                    Vector<uint32>& indices,
                    const int32 size)
{
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * 
                         sizeof(ComplexBigAnimVertex<Size>),
                         sizeof(ComplexBigAnimVertex<Size>),
                         reinterpret_cast<Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint32),
                        sizeof(uint32),
                        reinterpret_cast<Byte*>(indices.data()));
  return true;
}
}
