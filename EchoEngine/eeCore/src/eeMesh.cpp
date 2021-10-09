#include "eeMesh.h"
#include "eeBuffer.h"

namespace eeEngineSDK {
Mesh::~Mesh()
{
  m_verticesData->Release();
  m_indicesData->Release();
}
}