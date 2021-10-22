#include "eeDX11Mesh.h"
#include "eeDX11GraphicsApi.h"

namespace eeEngineSDK {
bool
DX11Mesh::constructBuffers()
{
  DX11Basics* basics =
  reinterpret_cast<DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  D3D11_BUFFER_DESC bd = {};
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.CPUAccessFlags = 0u;
  bd.MiscFlags = 0u;
  bd.ByteWidth = m_vertexData->getDataSize();
  bd.StructureByteStride = m_vertexData->getBatchSize();
  D3D11_SUBRESOURCE_DATA sd = {};
  sd.pSysMem = m_vertexData->getData().data();
  HRESULT hr = basics->m_device->CreateBuffer(&bd, &sd, &m_vertexBuffer);
  if (FAILED(hr))
  {
    return false;
  }
}
ID3D11Buffer* 
DX11Mesh::getVertexBuffer()
{
  return m_vertexBuffer;
}
ID3D11Buffer* 
DX11Mesh::getIndexBuffer()
{
  return m_indexBuffer;
}
}