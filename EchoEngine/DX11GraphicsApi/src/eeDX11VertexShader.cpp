#include "eeDX11VertexShader.h"
#include "eeDX11GraphicsApi.h"
#include <d3dcompiler.h>
#include <D3DX11async.h>

namespace eeEngineSDK {
DX11VertexShader::~DX11VertexShader()
{
  if (m_shader)
  {
    m_shader->Release();
  }
}

bool 
DX11VertexShader::compileFromFile(const String& fileName)
{
  DX11Basics* basics =
  reinterpret_cast<DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  HRESULT hr = S_OK;


  DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
  // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
  // Setting this flag improves the shader debugging experience, but still allows
  // the shaders to be optimized and to run exactly the way they will run in
  // the release configuration of this program.
  dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

  // Compile the vertex shader
  ID3DBlob* pVSBlob = NULL;
  ID3DBlob* pErrorBlob = NULL;

  hr = D3DX11CompileFromFileA(fileName.c_str(),
                              NULL,
                              NULL,
                              "main",
                              "vs_4_0",
                              dwShaderFlags,
                              0,
                              NULL,
                              &pVSBlob,
                              &pErrorBlob,
                              NULL);
  if (FAILED(hr))
  {
    if (pVSBlob)
      pVSBlob->Release();
    if (pErrorBlob != NULL)
      OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
    if (pErrorBlob) pErrorBlob->Release();

    String msg = "The FX file cannot be compiled. Please run this ";
    msg.append("executable from the directory that contains the FX file.");

    MessageBox(NULL, msg.c_str(), "Error", MB_OK);

    return false;
  }
  if (pErrorBlob) pErrorBlob->Release();


  // Create the vertex shader
  hr = basics->m_device->CreateVertexShader(pVSBlob->GetBufferPointer(),
                                            pVSBlob->GetBufferSize(),
                                            NULL,
                                            &m_shader);
  if (FAILED(hr))
  {
    if (pVSBlob)
      pVSBlob->Release();
    return false;
  }


  hr = CreateInputLayout(pVSBlob);
  if (pVSBlob)
    pVSBlob->Release();
  if (FAILED(hr))
  {
    return false;
  }

  return true;
}

bool 
DX11VertexShader::compileFromString(const String& shaderString)
{
  return false;
}

void DX11VertexShader::use()
{
  DX11Basics* basics =
  reinterpret_cast<DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  basics->m_deviceContext->IASetInputLayout(m_inputLayout);
  basics->m_deviceContext->VSSetShader(m_shader, NULL, 0);
}

HRESULT 
DX11VertexShader::CreateInputLayout(ID3DBlob* pShaderBlob)
{
  DX11Basics* basics =
  reinterpret_cast<DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  // Reflect shader info
  ID3D11ShaderReflection* pVertexShaderReflection = NULL;
  if (FAILED(D3DReflect(pShaderBlob->GetBufferPointer(), 
                        pShaderBlob->GetBufferSize(), 
                        IID_ID3D11ShaderReflection, 
                        reinterpret_cast<void**>(&pVertexShaderReflection))))
  {
    return S_FALSE;
  }

  // Get shader info
  D3D11_SHADER_DESC shaderDesc;
  pVertexShaderReflection->GetDesc(&shaderDesc);

  // Read input layout description from shader info
  std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
  for (uint32 i = 0; i < shaderDesc.InputParameters; i++)
  {
    D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
    pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

    // fill out input element desc
    D3D11_INPUT_ELEMENT_DESC elementDesc;
    elementDesc.SemanticName = paramDesc.SemanticName;
    elementDesc.SemanticIndex = paramDesc.SemanticIndex;
    elementDesc.InputSlot = 0;
    elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    elementDesc.InstanceDataStepRate = 0;

    // determine DXGI format
    if (paramDesc.Mask == 1)
    {
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
        elementDesc.Format = DXGI_FORMAT_R32_UINT;
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
        elementDesc.Format = DXGI_FORMAT_R32_SINT;
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
        elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
    }
    else if (paramDesc.Mask <= 3)
    {
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
        elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
       elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
        elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
    }
    else if (paramDesc.Mask <= 7)
    {
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
        elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
        elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
        elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    }
    else if (paramDesc.Mask <= 15)
    {
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    }

    //save element desc
    inputLayoutDesc.push_back(elementDesc);
  }

  // Try to create Input Layout
  HRESULT hr = basics->m_device->CreateInputLayout(&inputLayoutDesc[0],
                                                   inputLayoutDesc.size(),
                                                   pShaderBlob->GetBufferPointer(),
                                                   pShaderBlob->GetBufferSize(),
                                                   &m_inputLayout);

  //Free allocation shader reflection memory
  pVertexShaderReflection->Release();
  return hr;
}
}