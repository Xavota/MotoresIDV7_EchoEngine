#include "eeDX11RasterizerState.h"
#include "eeDX11GraphicsApi.h"

namespace eeEngineSDK {
DX11RasterizerState::DX11RasterizerState(eFILL_MODE::E fillMode,
                                         eCULL_MODE::E cullMode,
                                         bool frontCounterClockwise)
{
  create(fillMode, cullMode, frontCounterClockwise);
}
DX11RasterizerState::~DX11RasterizerState()
{
  release();
}
bool
DX11RasterizerState::create(eFILL_MODE::E fillMode,
                            eCULL_MODE::E cullMode,
                            bool frontCounterClockwise)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  D3D11_RASTERIZER_DESC rasDesc;
  memset(&rasDesc, 0, sizeof(rasDesc));
  rasDesc.CullMode = static_cast<D3D11_CULL_MODE>(cullMode);
  rasDesc.FillMode = static_cast<D3D11_FILL_MODE>(fillMode);
  rasDesc.FrontCounterClockwise = frontCounterClockwise;

  HRESULT hr = basics->m_device->CreateRasterizerState(&rasDesc, &m_rasterizer);
  if (FAILED(hr)) {
    return false;
  }
  return true;
}
void
DX11RasterizerState::use()
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  basics->m_deviceContext->RSSetState(m_rasterizer);
}
void
DX11RasterizerState::release()
{
  RasterizerState::release();
  DX11SAFE_RELEASE(m_rasterizer);
}
}