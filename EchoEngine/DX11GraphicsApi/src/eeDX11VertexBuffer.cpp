#include "eeDX11VertexBuffer.h"
#include "eeDX11GraphicsApi.h"

namespace eeEngineSDK {
DX11VertexBuffer::DX11VertexBuffer(SIZE_T dataSize, uint32 batchSize, const Byte* data)
{
  initData(dataSize, batchSize, data);
}
DX11VertexBuffer::~DX11VertexBuffer()
{
  release();
}
bool
DX11VertexBuffer::initData(SIZE_T dataSize, uint32 batchSize, const Byte* data)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  if (!VertexBuffer::initData(dataSize, batchSize, data)) {
    return false;
  }

  D3D11_BUFFER_DESC bd = {};
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.CPUAccessFlags = 0u;
  bd.MiscFlags = 0u;
  bd.ByteWidth = static_cast<uint32>(m_data.size());
  bd.StructureByteStride = m_batchSize;
  D3D11_SUBRESOURCE_DATA sd = {};
  sd.pSysMem = m_data.data();
  HRESULT hr = basics->m_device->CreateBuffer(&bd, &sd, &m_buffer);
  if (FAILED(hr)) {
    return false;
  }

  return true;
}
void
DX11VertexBuffer::updateData(const Byte* data)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  VertexBuffer::updateData(data);

  basics->m_deviceContext->UpdateSubresource(m_buffer,
                                             0u,
                                             nullptr,
                                             data,
                                             0u,
                                             0u);
}
void
DX11VertexBuffer::release()
{
  VertexBuffer::release();
  DX11SAFE_RELEASE(m_buffer);
}
void
DX11VertexBuffer::set()
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  const uint32 stride = m_batchSize;
  const uint32 offset = 0u;

  basics->m_deviceContext->IASetVertexBuffers(0u, 1u,
                                              &m_buffer, &stride, &offset);
}
}