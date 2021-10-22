#pragma once
#include "eePrerequisitesDX11.h"
#include <eePixelShader.h>
#include <d3d11.h>

namespace eeEngineSDK {
class DX11PixelShader : public PixelShader
{
public:
  DX11PixelShader() = default;
  ~DX11PixelShader();

  bool
  compileFromFile(const String& fileName) override;
  bool
  compileFromString(const String& shaderString) override;

  void
  use() override;

private:
  ID3D11PixelShader* m_shader;
};
}