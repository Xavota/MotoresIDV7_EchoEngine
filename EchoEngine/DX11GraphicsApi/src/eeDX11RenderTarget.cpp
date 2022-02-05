#include "eeDX11RenderTarget.h"
#include "eeDX11GraphicsApi.h"
#include "eeDX11Texture.h"
#include "eeDX11DepthStencil.h"

namespace eeEngineSDK {
DX11RenderTarget::~DX11RenderTarget()
{
  release();
}

bool
DX11RenderTarget::createAsBackBuffer()
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  HRESULT hr;

  ID3D11Texture2D* pBackBuffer = nullptr;
  hr = basics->m_swapChain->GetBuffer(0,
                                      __uuidof(ID3D11Texture2D),
                                      reinterpret_cast<LPVOID*>(&pBackBuffer));
  if (FAILED(hr)) {
    return false;
  }

  hr = basics->m_device->CreateRenderTargetView(pBackBuffer,
                                                nullptr,
                                                &m_renderTarget);
  DX11SAFE_RELEASE(pBackBuffer);
  if (FAILED(hr)) {
    return false;
  }

  return true;
}

bool
DX11RenderTarget::createAsIOTexture()
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  //TODO: Areglar
  ID3D11Texture2D* Tex;
  D3D11_TEXTURE2D_DESC descTextRT;
  ZeroMemory(&descTextRT, sizeof(descTextRT));
  descTextRT.Width = 1264;
  descTextRT.Height = 681;
  descTextRT.MipLevels = 1;
  descTextRT.ArraySize = 1;
  descTextRT.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  descTextRT.SampleDesc.Count = 1;
  descTextRT.SampleDesc.Quality = 0;
  descTextRT.Usage = D3D11_USAGE_DEFAULT;
  descTextRT.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
  descTextRT.CPUAccessFlags = 0;
  descTextRT.MiscFlags = 0;
  if (FAILED(basics->m_device->CreateTexture2D(&descTextRT, nullptr, &Tex))) {
    DX11SAFE_RELEASE(Tex);
    return false;
  }

  if (FAILED(basics->m_device->CreateRenderTargetView(Tex,
                                                      nullptr,
                                                      &m_renderTarget)))  {
    DX11SAFE_RELEASE(Tex);
    return false;
  }


  SamplerStateDesc samDesc;
  memset(&samDesc, 0, sizeof(samDesc));
  samDesc.filter = eFILTER::kMIN_MAG_MIP_LINEAR;
  samDesc.addressU = eTEXTURE_ADDRESS_MODE::WRAP;
  samDesc.addressV = eTEXTURE_ADDRESS_MODE::WRAP;
  samDesc.addressW = eTEXTURE_ADDRESS_MODE::WRAP;
  samDesc.comparisonFunc = eCOMPARISON_FUNC::NEVER;
  samDesc.minLOD = 0;
  samDesc.maxLOD = D3D11_FLOAT32_MAX;

  m_inTexture = MemoryManager::instance().newPtr<DX11Texture>();
  if (m_inTexture->loadFromBuffer(reinterpret_cast<void*>(Tex), samDesc)) {
    DX11SAFE_RELEASE(Tex);
    return false;
  }

  DX11SAFE_RELEASE(Tex);
  return true;
}

const SPtr<Texture>
DX11RenderTarget::getAsTexture() const
{
  return m_inTexture;
}

void
DX11RenderTarget::set(SPtr<DepthStencil> stencil)
{
  EE_NO_EXIST_RETURN(stencil);

  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  SPtr<DX11DepthStencil> ds =
           MemoryManager::instance().reinterpretPtr<DX11DepthStencil>(stencil);
  ID3D11DepthStencilView* depthStencilView = ds->getResource();

  EE_NO_EXIST_RETURN(depthStencilView);

  basics->m_deviceContext->OMSetRenderTargets(1,
                                              &m_renderTarget,
                                              depthStencilView);
}

void
DX11RenderTarget::clean(Color screenColor)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  basics->m_deviceContext->ClearRenderTargetView(m_renderTarget, screenColor.rgba);
}

void
DX11RenderTarget::release()
{
  DX11SAFE_RELEASE(m_renderTarget);
  MemoryManager::instance().safeRelease<Texture>(m_inTexture);
}
}