#include "eeDX11IndexBuffer.h"
#include "eeDX11GraphicsApi.h"

namespace eeEngineSDK {
DX11IndexBuffer::DX11IndexBuffer(SIZE_T dataSize,
                                 uint32 batchSize,
                                 const Byte* data)
{
  initData(dataSize, batchSize, data);
}
DX11IndexBuffer::~DX11IndexBuffer()
{
  release();
}
bool
DX11IndexBuffer::initData(SIZE_T dataSize,
                          uint32 batchSize,
                          const Byte* data)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  if (!IndexBuffer::initData(dataSize, batchSize, data)) {
    return false;
  }

  D3D11_BUFFER_DESC bd = {};
  bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.CPUAccessFlags = 0u;
  bd.MiscFlags = 0u;
  bd.ByteWidth = static_cast<uint32>(m_data.size());
  bd.StructureByteStride = m_batchSize;
  D3D11_SUBRESOURCE_DATA sd = {};
  sd.pSysMem = m_data.data();
  HRESULT hr = basics->m_device->CreateBuffer(&bd, &sd, &m_buffer);
  if (FAILED(hr)) {
    DX11SAFE_RELEASE(m_buffer);
    return false;
  }

  return true;
}
void
DX11IndexBuffer::updateData(const Byte* data)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  IndexBuffer::updateData(data);

  basics->m_deviceContext->UpdateSubresource(m_buffer,
                                             0u,
                                             nullptr,
                                             data,
                                             0u,
                                             0u);
}

void
DX11IndexBuffer::release()
{
  IndexBuffer::release();
  DX11SAFE_RELEASE(m_buffer);
}

void
DX11IndexBuffer::set()
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  const uint32 offset = 0u;

  if (m_batchSize == 2) {
    basics->m_deviceContext->IASetIndexBuffer(m_buffer, DXGI_FORMAT_R16_UINT, offset);
  }
  else if (m_batchSize == 4) {
    basics->m_deviceContext->IASetIndexBuffer(m_buffer, DXGI_FORMAT_R32_UINT, offset);
  }
}
}