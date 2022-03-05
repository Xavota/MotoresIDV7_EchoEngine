#include "eeDX11ConstantBuffer.h"
#include "eeDX11GraphicsApi.h"

#include <eeMatrix4.h>

namespace eeEngineSDK {
DX11ConstantBuffer::DX11ConstantBuffer(SIZE_T dataSize,
                                       uint32 batchSize,
                                       const Byte* data)
{
  initData(dataSize, batchSize, data);
}
DX11ConstantBuffer::~DX11ConstantBuffer()
{
  release();
}
bool
DX11ConstantBuffer::initData(SIZE_T dataSize,
                             uint32 batchSize,
                             const Byte* data)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  if (!ConstantBuffer::initData(dataSize, batchSize, data)) {
    return false;
  }

  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(bd));
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = static_cast<UINT>(dataSize);
  bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  bd.CPUAccessFlags = 0;
  HRESULT hr = basics->m_device->CreateBuffer(&bd, nullptr, &m_buffer);
  if (FAILED(hr)) {
    DX11SAFE_RELEASE(m_buffer);
    return false;
  }

  return true;
}
void
DX11ConstantBuffer::updateData(const Byte* data)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  ConstantBuffer::updateData(data);

  basics->m_deviceContext->UpdateSubresource(m_buffer,
                                             0u,
                                             nullptr,
                                             data,
                                             0u,
                                             0u);
}
void
DX11ConstantBuffer::release()
{
  ConstantBuffer::release();
  DX11SAFE_RELEASE(m_buffer);
}
void
DX11ConstantBuffer::setInVertex(uint32 index)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  basics->m_deviceContext->UpdateSubresource(m_buffer,
                                             0u,
                                             nullptr,
                                             m_data.data(),
                                             0u,
                                             0u);
  basics->m_deviceContext->VSSetConstantBuffers(index,
                                                1u,
                                                &m_buffer);
}
void
DX11ConstantBuffer::setInPixel(uint32 index)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  basics->m_deviceContext->PSSetConstantBuffers(index,
                                                1u,
                                                &m_buffer);
}
}