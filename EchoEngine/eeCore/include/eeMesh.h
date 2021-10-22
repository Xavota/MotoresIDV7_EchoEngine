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
  loadFromArray(const Vector<SimplexVertex>& vertices,
                const Vector<uint16>& indices);
  bool
  loadFromArray(const Vector<SimpleVertex>& vertices,
                const Vector<uint16>& indices);
  bool
  loadFromArray(const Vector<ComplexVertex>& vertices,
                const Vector<uint16>& indices);
  bool
  loadFromArray(const Vector<SimpleAnimVertex>& vertices,
                const Vector<uint16>& indices);
  template<uint32 Size = 4>
  FORCEINLINE bool
  loadFromArray(const Vector<SimpleBigAnimVertex<Size>>& vertices,
                const Vector<uint16>& indices);
  bool
  loadFromArray(const Vector<ComplexAnimVertex>& vertices,
                const Vector<uint16>& indices);
  template<uint32 Size = 4>
  FORCEINLINE bool
  loadFromArray(const Vector<ComplexBigAnimVertex<Size>>& vertices,
                const Vector<uint16>& indices);
  bool
  loadFromArray(const Vector<SimplexVertex>& vertices,
                const Vector<uint32>& indices);
  bool
  loadFromArray(const Vector<SimpleVertex>& vertices,
                const Vector<uint32>& indices);
  bool
  loadFromArray(const Vector<ComplexVertex>& vertices,
                const Vector<uint32>& indices);
  bool
  loadFromArray(const Vector<SimpleAnimVertex>& vertices,
                const Vector<uint32>& indices);
  template<uint32 Size = 4>
  FORCEINLINE bool
  loadFromArray(const Vector<SimpleBigAnimVertex<Size>>& vertices,
                const Vector<uint32>& indices);
  bool
  loadFromArray(const Vector<ComplexAnimVertex>& vertices,
                const Vector<uint32>& indices);
  template<uint32 Size = 4>
  FORCEINLINE bool
  loadFromArray(const Vector<ComplexBigAnimVertex<Size>>& vertices,
                const Vector<uint32>& indices);

  virtual bool
  constructBuffers(){ return true; }

  virtual const SPtr<Buffer>
  getVertexData() const;
  virtual const SPtr<Buffer>
  getIndexData() const;

 protected:
  SPtr<Buffer> m_vertexData;
  SPtr<Buffer> m_indexData;
};
template<uint32 Size>
FORCEINLINE bool 
Mesh::loadFromArray(const Vector<SimpleBigAnimVertex<Size>>& vertices, 
                    const Vector<uint16>& indices)
{
  if (vertices.empty() || indices.empty())
  {
    std::cout << "Empty info loading mesh" << std::endl;
    return false;
  }

  m_vertexData = std::make_shared<Buffer>();
  m_indexData = std::make_shared<Buffer>();
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * 
                         sizeof(SimpleBigAnimVertex<Size>),
                         sizeof(SimpleBigAnimVertex<Size>),
                         reinterpret_cast<const Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint16),
                        sizeof(uint16),
                        reinterpret_cast<const Byte*>(indices.data()));

  constructBuffers();
  return true;
}
template<uint32 Size>
FORCEINLINE bool
Mesh::loadFromArray(const Vector<ComplexBigAnimVertex<Size>>& vertices,
                    const Vector<uint16>& indices)
{
  if (vertices.empty() || indices.empty())
  {
    std::cout << "Empty info loading mesh" << std::endl;
    return false;
  }

  m_vertexData = std::make_shared<Buffer>();
  m_indexData = std::make_shared<Buffer>();
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * 
                         sizeof(ComplexBigAnimVertex<Size>),
                         sizeof(ComplexBigAnimVertex<Size>),
                         reinterpret_cast<const Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint16),
                        sizeof(uint16),
                        reinterpret_cast<const Byte*>(indices.data()));

  constructBuffers();
  return true;
}
template<uint32 Size>
FORCEINLINE bool
Mesh::loadFromArray(const Vector<SimpleBigAnimVertex<Size>>& vertices,
                    const Vector<uint32>& indices)
{
  if (vertices.empty() || indices.empty())
  {
    std::cout << "Empty info loading mesh" << std::endl;
    return false;
  }

  m_vertexData = std::make_shared<Buffer>();
  m_indexData = std::make_shared<Buffer>();
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * 
                         sizeof(SimpleBigAnimVertex<Size>),
                         sizeof(SimpleBigAnimVertex<Size>),
                         reinterpret_cast<const Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint32),
                        sizeof(uint32),
                        reinterpret_cast<const Byte*>(indices.data()));

  constructBuffers();
  return true;
}
template<uint32 Size>
FORCEINLINE bool
Mesh::loadFromArray(const Vector<ComplexBigAnimVertex<Size>>& vertices,
                    const Vector<uint32>& indices)
{
  if (vertices.empty() || indices.empty())
  {
    std::cout << "Empty info loading mesh" << std::endl;
    return false;
  }

  m_vertexData = std::make_shared<Buffer>();
  m_indexData = std::make_shared<Buffer>();
  m_vertexData->InitData(static_cast<uint32>(vertices.size()) * 
                         sizeof(ComplexBigAnimVertex<Size>),
                         sizeof(ComplexBigAnimVertex<Size>),
                         reinterpret_cast<const Byte*>(vertices.data()));
  m_indexData->InitData(static_cast<uint32>(indices.size()) * sizeof(uint32),
                        sizeof(uint32),
                        reinterpret_cast<const Byte*>(indices.data()));

  constructBuffers();
  return true;
}
}
