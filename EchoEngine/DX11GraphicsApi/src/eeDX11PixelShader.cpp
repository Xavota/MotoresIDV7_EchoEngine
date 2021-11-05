#include "eeDX11PixelShader.h"
#include "eeDX11GraphicsApi.h"
#pragma warning(push, 0)   
#include <d3dcompiler.h>
#include <D3DX11async.h>
#pragma warning(pop)   

eeEngineSDK::DX11PixelShader::~DX11PixelShader()
{
  if (m_shader)
  {
    m_shader->Release();
  }
}

bool eeEngineSDK::DX11PixelShader::compileFromFile(const String& fileName)
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  HRESULT hr = S_OK;


  DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
  // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
  // Setting this flag improves the shader debugging experience, but still allows
  // the shaders to be optimized and to run exactly the way they will run in
  // the release configuration of this program.
  dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

  // Compile the pixel shader
  ID3DBlob* pPSBlob = NULL;
  ID3DBlob* pErrorBlob;

  hr = D3DX11CompileFromFileA(fileName.c_str(), NULL, NULL, "main", "ps_4_0",
    dwShaderFlags, 0, NULL, &pPSBlob, &pErrorBlob, NULL);
  if (FAILED(hr))
  {
    if (pErrorBlob != NULL)
      OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
    if (pErrorBlob) pErrorBlob->Release();

    MessageBox(NULL,
      "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);

    return false;
  }
  if (pErrorBlob) pErrorBlob->Release();


  // Create the pixel shader
  hr = basics->m_device->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &m_shader);
  pPSBlob->Release();
  if (FAILED(hr))
    return false;

  return true;
}

bool eeEngineSDK::DX11PixelShader::compileFromString(const String& /*shaderString*/)
{
  return false;
}

void eeEngineSDK::DX11PixelShader::use()
{
  const DX11Basics* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  basics->m_deviceContext->PSSetShader(m_shader, NULL, 0);
}
