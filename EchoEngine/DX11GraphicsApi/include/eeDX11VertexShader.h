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
  createInputLayout(ID3DBlob* pShaderBlob);

  void
  setModelMatrix(const Matrix4f& model) override;
  void
  setViewMatrix(const Matrix4f& view) override;
  void
  setProjectionMatrix(const Matrix4f& proj) override;

 private:
  ID3D11VertexShader* m_shader;
  ID3D11InputLayout* m_inputLayout;

  ID3D11Buffer* m_matrixBuffer;
};
}
