#pragma once
#include "eePrerequisitesDX11.h"
#include <eeVertexShader.h>
#include <d3d11.h>

namespace eeEngineSDK {
class DX11VertexShader : public VertexShader
{
public:
  DX11VertexShader() = default;
  ~DX11VertexShader();

  bool
  compileFromFile(const String& fileName) override;
  bool
  compileFromString(const String& shaderString) override;

  void
  use() override;

  HRESULT 
  CreateInputLayout(ID3DBlob* pShaderBlob);

 private:
  ID3D11VertexShader* m_shader;
  ID3D11InputLayout* m_inputLayout;
};
}
