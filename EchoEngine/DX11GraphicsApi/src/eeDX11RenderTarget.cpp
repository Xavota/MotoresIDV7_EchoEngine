#include "eeDX11RenderTarget.h"
#include "eeDX11GraphicsApi.h"
#include "eeDX11Texture.h"
#include "DX11DepthStencil.h"

namespace eeEngineSDK {
DX11RenderTarget::~DX11RenderTarget()
{
  release();
}

bool
DX11RenderTarget::createAsBackBuffer()
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  ID3D11Resource* pBackBuffer = nullptr;
  basics->m_swapChain->GetBuffer(0, __uuidof(ID3D11Resource),
                                reinterpret_cast<void**>(&pBackBuffer));

  basics->m_device->CreateRenderTargetView(pBackBuffer,
                                          nullptr,
                                          &m_renderTarget);
  pBackBuffer->Release();


  return true;
}

bool
DX11RenderTarget::createAsIOTexture()
{
  //TODO: Areglar
  Texture2D Tex;
  TEXTURE2D_DESC descTextRT;
  ZeroMemory(&descTextRT, sizeof(descTextRT));
  descTextRT.Width = 1264;
  descTextRT.Height = 681;
  descTextRT.MipLevels = 1;
  descTextRT.ArraySize = 1;
  descTextRT.Format = FORMAT_R8G8B8A8_UNORM;
  descTextRT.SampleDesc.Count = 1;
  descTextRT.SampleDesc.Quality = 0;
  descTextRT.Usage = USAGE_DEFAULT;
  descTextRT.BindFlags = BIND_SHADER_RESOURCE | BIND_RENDER_TARGET;
  descTextRT.CPUAccessFlags = 0;
  descTextRT.MiscFlags = 0;
  if (FAILED(GetManager()->CreateTexture2D(&descTextRT, NULL, Tex)))
  {
    Tex.Release();
    return;
  }

  if (FAILED(GetManager()->CreateRenderTargetView(Tex, NULL, m_rtv)))
  {
    Tex.Release();
    return;
  }

  if (m_tex.CreateTextureFromBuffer(Tex))
  {
    Tex.Release();
    return;
  }

  Tex.Release();
  return false;
}

const SPtr<const Texture>
DX11RenderTarget::getAsTexture() const
{
  return m_inTexture;
}

void
DX11RenderTarget::set(SPtr<DepthStencil> stencil)
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  ID3D11DepthStencilView* depthStencilView = nullptr;
  if (stencil)
  {
    SPtr<DX11DepthStencil> ds =
    std::reinterpret_pointer_cast<DX11DepthStencil>(stencil);
    depthStencilView = ds->getResource();
  }

  if (depthStencilView)
  {
    basics->m_deviceContext->OMSetRenderTargets(1,
                                                &m_renderTarget,
                                                depthStencilView);
  }
}

void
DX11RenderTarget::clean(float r, float g, float b, float a)
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  float clearColor[4] = { r,g,b,1.0f };
  basics->m_deviceContext->ClearRenderTargetView(m_renderTarget, clearColor);
}

void
DX11RenderTarget::release()
{
  if (m_renderTarget)
  {
    m_renderTarget->Release();
  }
  if (m_inTexture)
  {
    m_inTexture->release();
  }
}
}