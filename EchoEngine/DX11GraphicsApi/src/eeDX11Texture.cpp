#include "eeDX11Texture.h"
#include "eeDX11GraphicsApi.h"
#include "eeDX11SamplerState.h"
//#include <eeMath.h>
#pragma warning(push, 0)   
#include <d3dx11.h>
#pragma warning(pop)   

namespace eeEngineSDK {
DX11Texture::~DX11Texture()
{
  release();
}

bool DX11Texture::loadFromFile(const String fileName)
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


  SamplerStateDesc desc;
  memset(&desc, 0, sizeof(desc));
  desc.filter = FILTER::MIN_MAG_MIP_LINEAR;
  desc.addressU = TEXTURE_ADDRESS_MODE::WRAP;
  desc.addressV = TEXTURE_ADDRESS_MODE::WRAP;
  desc.addressW = TEXTURE_ADDRESS_MODE::WRAP;
  desc.comparisonFunc = COMPARISON_FUNC::NEVER;
  desc.minLOD = 0;
  desc.maxLOD = D3D11_FLOAT32_MAX;
  m_sampler = std::make_shared<DX11SamplerState>();
  m_sampler->create(desc);

  return true;
}

bool DX11Texture::loadFromBuffer(SPtr<void> /*buffer*/)
{
  return false;
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