#include "eeDX11Texture.h"
//#include <eeMath.h>
#include "eeDX11GraphicsApi.h"
#include "eeDX11SamplerState.h"
#pragma warning(push, 0)   
#include <d3dx11.h>
#pragma warning(pop)   

namespace eeEngineSDK {
DX11Texture::~DX11Texture()
{
  release();
}

bool DX11Texture::loadFromFile(const String fileName, SamplerStateDesc desc)
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  HRESULT hr = D3DX11CreateShaderResourceViewFromFile(basics->m_device,
                                                      fileName.c_str(),
                                                      NULL,
                                                      NULL,
                                                      &m_tex,
                                                      NULL);
  if (FAILED(hr))
    return false;


  m_sampler = std::make_shared<DX11SamplerState>();
  m_sampler->create(desc);

  return true;
}

bool DX11Texture::loadFromBuffer(void* buffer, SamplerStateDesc desc)
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());


  ID3D11Texture2D* texBuff = reinterpret_cast<ID3D11Texture2D*>(buffer);

  D3D11_TEXTURE2D_DESC tempDesc;
  texBuff->GetDesc(&tempDesc);

  D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
  ZeroMemory(&srvDesc, sizeof(srvDesc));
  srvDesc.Format = tempDesc.Format;
  srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  srvDesc.Texture2D.MostDetailedMip = 0;
  srvDesc.Texture2D.MipLevels = -1; // same as orig texture
  HRESULT hr = basics->m_device->CreateShaderResourceView(texBuff, &srvDesc, &m_tex);
  if (FAILED(hr))
    return false;

  m_sampler = std::make_shared<DX11SamplerState>();
  m_sampler->create(desc);

  return true;
}

void DX11Texture::use()
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  basics->m_deviceContext->PSSetShaderResources(0, 1, &m_tex);

  m_sampler->use();
}

void DX11Texture::release()
{
  DX11SAFE_RELEASE(m_tex);
  m_sampler->release();
}
}