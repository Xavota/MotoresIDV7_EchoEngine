#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
class Mesh
{
 public:
  Mesh() = default;
  virtual
  ~Mesh();

  virtual bool
  loadFromFile(String fileName) = 0;
  virtual bool
  loadFromArray(const Vector<SimpleVertex>& vertices,
                const Vector<uint16>& indices) = 0;
  virtual bool
  loadFromArray(const Vector<ComplexVertex>& vertices,
                const Vector<uint16>& indices) = 0;
  virtual bool
  loadFromArray(const Vector<SimpleAnimVertex>& vertices,
                const Vector<uint16>& indices) = 0;
  virtual bool
  loadFromArray(const Vector<ComplexAnimVertex>& vertices,
                const Vector<uint16>& indices) = 0;
  virtual bool
  loadFromArray(const Vector<SimpleVertex>& vertices,
                const Vector<uint32>& indices) = 0;
  virtual bool
  loadFromArray(const Vector<ComplexVertex>& vertices,
                const Vector<uint32>& indices) = 0;
  virtual bool
  loadFromArray(const Vector<SimpleAnimVertex>& vertices,
                const Vector<uint32>& indices) = 0;
  virtual bool
  loadFromArray(const Vector<ComplexAnimVertex>& vertices,
                const Vector<uint32>& indices) = 0;

 private:
  Buffer* m_verticesData;
  Buffer* m_indicesData;
};
}
