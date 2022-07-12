#include "eeDX11HullShader.h"
#include "eeDX11GraphicsApi.h"
#pragma warning(push, 0)   
#include <d3dcompiler.h>
#include <D3DX11async.h>
#pragma warning(pop)

namespace eeEngineSDK {
bool
DX11HullShader::compileFromFile(const String& fileName,
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

  // Compile the pixel shader
  ID3DBlob* pPSBlob = nullptr;
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
  hr = D3DX11CompileFromFile(fileName.c_str(),
                             shaderMacros,
                             nullptr,
                             functionName.c_str(),
                             "hs_5_0",
                             dwShaderFlags,
                             0,
                             nullptr,
                             &pPSBlob,
                             &pErrorBlob,
                             nullptr);
  if (FAILED(hr)) {
    if (pErrorBlob != nullptr) {
      OutputDebugString((char*)pErrorBlob->GetBufferPointer());
    }
    DX11SAFE_RELEASE(pErrorBlob);

    MessageBox(nullptr,
               "The FX file cannot be compiled.  Please run this executable"
                 " from the directory that contains the FX file.",
               "Error",
               MB_OK);

    return false;
  }
  DX11SAFE_RELEASE(pErrorBlob);


  // Create the pixel shader
  hr = basics->m_device->CreateHullShader(pPSBlob->GetBufferPointer(),
                                          pPSBlob->GetBufferSize(),
                                          nullptr,
                                          &m_shader);
  DX11SAFE_RELEASE(pPSBlob);
  if (FAILED(hr)) {
    return false;
  }

  return true;
}
bool
DX11HullShader::compileFromString(const String& shaderString,
                                  const String& functionName,
                                  const Vector<ShaderMacro>& macroDefinitions)
{
  return false;
}
void
DX11HullShader::use()
{
  const auto* basics =
  reinterpret_cast<const DX11Basics*>(DX11GraphicsApi::instance().getBasics());

  basics->m_deviceContext->HSSetShader(m_shader, nullptr, 0);
}
void
DX11HullShader::release()
{
  HullShader::release();
  DX11SAFE_RELEASE(m_shader);
}
}