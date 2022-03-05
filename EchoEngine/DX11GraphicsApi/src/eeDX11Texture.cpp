#include "eeDX11Texture.h"

#pragma warning(push, 0)   
#include <d3dx11.h>
#pragma warning(pop)   

#include <eeMemoryManager.h>

#include <eeImage.h>

#include "eeDX11GraphicsApi.h"
#include "eeDX11SamplerState.h"

namespace eeEngineSDK {
DX11Texture::DX11Texture(uint32 bindFlags,
                         const Vector2u& texSize,
                         uint32 mipLevels)
{
  create2D(bindFlags, texSize, mipLevels);
}
DX11Texture::~DX11Texture()
{
  release();
}

bool
DX11Texture::create2D(uint32 bindFlags,
                      const Vector2u& texSize,
                      uint32 mipLevels)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  HRESULT hr = S_OK;

  m_bindFlags = bindFlags;

  D3D11_TEXTURE2D_DESC descText;
  memset(&descText, 0, sizeof(descText));
  descText.Width = texSize.x;
  descText.Height = texSize.y;
  descText.MipLevels = mipLevels;
  descText.ArraySize = 1;
  if ((m_bindFlags & eTEXTURE_BIND_FLAGS::kDepthStencil)
                  == eTEXTURE_BIND_FLAGS::kDepthStencil) {
    descText.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  }
  else {
    descText.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  }
  descText.SampleDesc.Count = 1;
  descText.SampleDesc.Quality = 0;
  descText.Usage = D3D11_USAGE_DEFAULT;
  if ((m_bindFlags & eTEXTURE_BIND_FLAGS::kShaderResource)
                == eTEXTURE_BIND_FLAGS::kShaderResource) {
    descText.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
  }
  if ((m_bindFlags & eTEXTURE_BIND_FLAGS::kRenderTarget)
                == eTEXTURE_BIND_FLAGS::kRenderTarget) {
    descText.BindFlags |= D3D11_BIND_RENDER_TARGET;
  }
  if ((m_bindFlags & eTEXTURE_BIND_FLAGS::kDepthStencil)
                == eTEXTURE_BIND_FLAGS::kDepthStencil) {
    descText.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
  }
  descText.CPUAccessFlags = 0;
  descText.MiscFlags = 0;
  hr = basics->m_device->CreateTexture2D(&descText, nullptr, &m_textureResource);
  if (FAILED(hr)) {
    DX11SAFE_RELEASE(m_textureResource);
    return false;
  }


  if ((m_bindFlags & eTEXTURE_BIND_FLAGS::kShaderResource)
                  == eTEXTURE_BIND_FLAGS::kShaderResource) {
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    memset(&srvDesc, 0, sizeof(srvDesc));
    srvDesc.Format = descText.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = static_cast<uint32>(-1); // same as orig texture
    hr = basics->m_device->CreateShaderResourceView(m_textureResource, &srvDesc, &m_shaderResource);
    if (FAILED(hr)) {
      DX11SAFE_RELEASE(m_textureResource);
      DX11SAFE_RELEASE(m_shaderResource);
      return false;
    }
  }
  if ((m_bindFlags & eTEXTURE_BIND_FLAGS::kRenderTarget)
                  == eTEXTURE_BIND_FLAGS::kRenderTarget) {
    hr = basics->m_device->CreateRenderTargetView(m_textureResource,
                                                  nullptr,
                                                  &m_renderTarget);
    if (FAILED(hr)) {
      DX11SAFE_RELEASE(m_textureResource);
      DX11SAFE_RELEASE(m_shaderResource);
      DX11SAFE_RELEASE(m_renderTarget);
      return false;
    }
  }
  if ((m_bindFlags & eTEXTURE_BIND_FLAGS::kDepthStencil)
                  == eTEXTURE_BIND_FLAGS::kDepthStencil) {
    // Create the depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    memset(&descDSV, 0, sizeof(descDSV));
    descDSV.Format = descText.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;
    hr = basics->m_device->CreateDepthStencilView(m_textureResource,
                                                  &descDSV,
                                                  &m_depthStencilView);
    if (FAILED(hr)) {
      DX11SAFE_RELEASE(m_textureResource);
      DX11SAFE_RELEASE(m_shaderResource);
      DX11SAFE_RELEASE(m_renderTarget);
      DX11SAFE_RELEASE(m_depthStencilView);
      return false;
    }
  }

  return false;
}

bool
DX11Texture::createAsBackBuffer()
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  HRESULT hr;

  hr = basics->m_swapChain->GetBuffer(0,
                                      __uuidof(ID3D11Texture2D),
                                      reinterpret_cast<LPVOID*>(&m_textureResource));
  if (FAILED(hr)) {
    DX11SAFE_RELEASE(m_textureResource);
    return false;
  }

  hr = basics->m_device->CreateRenderTargetView(m_textureResource,
                                                nullptr,
                                                &m_renderTarget);
  if (FAILED(hr)) {
    DX11SAFE_RELEASE(m_textureResource);
    DX11SAFE_RELEASE(m_renderTarget);
    return false;
  }

  m_bindFlags = eTEXTURE_BIND_FLAGS::kRenderTarget;

  return true;
}

void
DX11Texture::useAsShaderResource()
{
  if (m_shaderResource) {
    const auto* basics =
    reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());
    
    basics->m_deviceContext->PSSetShaderResources(0, 1, &m_shaderResource);
  }
}

void
DX11Texture::loadImages(Vector<SPtr<Image>> images)
{
  Texture::loadImages(images);

  if (!images.empty() && images[0] && m_shaderResource)
  {
    const auto* basics =
    reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

    HRESULT hr = S_OK;

    D3D11_TEXTURE2D_DESC image_texture_desc;
    m_textureResource->GetDesc(&image_texture_desc);
    
    DX11SAFE_RELEASE(m_textureResource);
    
    image_texture_desc.Width = images[0]->getWidth();
    image_texture_desc.Height = images[0]->getHeight();
    image_texture_desc.MipLevels = 1;
    
    D3D11_SUBRESOURCE_DATA image_subresource_data = {};
    
    image_subresource_data.pSysMem = images[0]->getData();
    image_subresource_data.SysMemPitch = images[0]->getDataSize();
    
    hr = basics->m_device->CreateTexture2D(&image_texture_desc,
                                                   &image_subresource_data,
                                                   &m_textureResource);

    if (FAILED(hr)) {
      DX11SAFE_RELEASE(m_textureResource);
      return;
    }

    DX11SAFE_RELEASE(m_shaderResource);
    hr = basics->m_device->CreateShaderResourceView(m_textureResource,
                                                    nullptr,
                                                    &m_shaderResource);
    if (FAILED(hr)) {
      DX11SAFE_RELEASE(m_textureResource);
      DX11SAFE_RELEASE(m_shaderResource);
    }
  }
}

void
DX11Texture::clean(Color screenColor)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  if ((m_bindFlags & eTEXTURE_BIND_FLAGS::kRenderTarget)
                  == eTEXTURE_BIND_FLAGS::kRenderTarget) {
    basics->m_deviceContext->ClearRenderTargetView(m_renderTarget, screenColor.rgba);
  }
  if ((m_bindFlags & eTEXTURE_BIND_FLAGS::kDepthStencil)
                  == eTEXTURE_BIND_FLAGS::kDepthStencil) {
    basics->m_deviceContext->ClearDepthStencilView(m_depthStencilView,
                                                   D3D11_CLEAR_DEPTH,
                                                   1.0f,
                                                   0);
  }
}

void
DX11Texture::release()
{
  Texture::release();
  DX11SAFE_RELEASE(m_shaderResource);
  DX11SAFE_RELEASE(m_renderTarget);
  DX11SAFE_RELEASE(m_depthStencilView);
  DX11SAFE_RELEASE(m_textureResource);
}
}