#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
class EE_CORE_EXPORT PixelShader
{
 public:
  PixelShader() = default;
  virtual
  ~PixelShader() = default;

  virtual bool
  compileFromFile(const String& fileName){};
  virtual bool
  compileFromString(const String& shaderString){};

 private:
  String m_shaderString;
};
}
