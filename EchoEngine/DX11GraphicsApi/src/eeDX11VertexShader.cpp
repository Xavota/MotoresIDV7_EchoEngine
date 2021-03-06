#include "eeDX11VertexShader.h"
#include "eeDX11GraphicsApi.h"
#pragma warning(push, 0)   
#include <d3dcompiler.h>
#pragma warning(pop)   

#include <eeMatrix4.h>

namespace eeEngineSDK {
DX11VertexShader::~DX11VertexShader()
{
  release();
}

bool 
DX11VertexShader::compileFromFile(const WString& fileName,
                                  const String& functionName,
                                  const Vector<ShaderMacro>& macroDefinitions)
{
  const auto* basics =
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

  // Compile the vertex shader
  ID3DBlob* pVSBlob = nullptr;
  ID3DBlob* pErrorBlob = nullptr;

  auto shaderMacros = new D3D_SHADER_MACRO[macroDefinitions.size() + 1];
  int32 index = 0;
  for (auto& macro : macroDefinitions) {
    shaderMacros[index].Name = macro.Name.c_str();
    shaderMacros[index].Definition = macro.Definition.c_str();
    ++index;
  }
  shaderMacros[index].Name = nullptr;
  shaderMacros[index].Definition = nullptr;
  hr = D3DCompileFromFile(fileName.c_str(),
                          shaderMacros,
                          nullptr,
                          functionName.c_str(),
                          "vs_4_0",
                          dwShaderFlags,
                          0,
                          &pVSBlob,
                          &pErrorBlob);
  if (FAILED(hr)) {
    if (pVSBlob) {
      DX11SAFE_RELEASE(pVSBlob);
    }
    if (pErrorBlob != nullptr) {
      OutputDebugString((char*)pErrorBlob->GetBufferPointer());
    }
    DX11SAFE_RELEASE(pErrorBlob);

    MessageBox(nullptr,
               "The FX file cannot be compiled. Please run this "
                 "executable from the directory that contains the FX file.",
               "Error",
               MB_OK);

    return false;
  }
  DX11SAFE_RELEASE(pErrorBlob);

  // Create the vertex shader
  hr = basics->m_device->CreateVertexShader(pVSBlob->GetBufferPointer(),
                                            pVSBlob->GetBufferSize(),
                                            nullptr,
                                            &m_shader);
  if (FAILED(hr)) {
    DX11SAFE_RELEASE(pVSBlob);
    return false;
  }

  hr = createInputLayout(pVSBlob);
  DX11SAFE_RELEASE(pVSBlob);
  if (FAILED(hr)) {
    return false;
  }

  return true;
}

bool 
DX11VertexShader::compileFromString(const String& /*shaderString*/,
                                    const String& /*functionName*/,
                                    const Vector<ShaderMacro>& /*macroDefinitions*/)
{
  return false;
}

void DX11VertexShader::use()
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  basics->m_deviceContext->IASetInputLayout(m_inputLayout);
  basics->m_deviceContext->VSSetShader(m_shader, nullptr, 0);
}

void DX11VertexShader::release()
{
  VertexShader::release();
  DX11SAFE_RELEASE(m_shader);
  DX11SAFE_RELEASE(m_inputLayout);
}

HRESULT 
DX11VertexShader::createInputLayout(ID3DBlob* pShaderBlob)
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  // Reflect shader info
  ID3D11ShaderReflection* pVertexShaderReflection = nullptr;
  if (FAILED(D3DReflect(pShaderBlob->GetBufferPointer(), 
                        pShaderBlob->GetBufferSize(), 
                        IID_ID3D11ShaderReflection, 
                        reinterpret_cast<void**>(&pVertexShaderReflection)))) {
    return S_FALSE;
  }

  // Get shader info
  D3D11_SHADER_DESC shaderDesc;
  pVertexShaderReflection->GetDesc(&shaderDesc);

  // Read input layout description from shader info
  Vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
  for (uint32 i = 0; i < shaderDesc.InputParameters; i++) {
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
    if (paramDesc.Mask == 1) {
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) {
        elementDesc.Format = DXGI_FORMAT_R32_UINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) {
        elementDesc.Format = DXGI_FORMAT_R32_SINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) {
        elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
      }
    }
    else if (paramDesc.Mask <= 3) {
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) {
        elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) {
       elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) {
        elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
      }
    }
    else if (paramDesc.Mask <= 7) {
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) {
        elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) {
        elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) {
        elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
      }
    }
    else if (paramDesc.Mask <= 15) {
      if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) {
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) {
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
      }
      else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) {
        elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
      }
    }

    //save element desc
    inputLayoutDesc.push_back(elementDesc);
  }

  // Try to create Input Layout
  HRESULT hr = basics->m_device->CreateInputLayout(&inputLayoutDesc[0],
                                                   static_cast<UINT>(
                                                   inputLayoutDesc.size()),
                                                   pShaderBlob->GetBufferPointer(),
                                                   pShaderBlob->GetBufferSize(),
                                                   &m_inputLayout);

  //Free allocation shader reflection memory
  DX11SAFE_RELEASE(pVertexShaderReflection);
  return hr;
}
}