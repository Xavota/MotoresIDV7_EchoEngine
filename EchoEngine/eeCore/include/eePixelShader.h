#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
class PixelShader
{
 public:
  PixelShader();
  virtual
  ~PixelShader();

  virtual bool
  compileFromFile(const String& fileName) = 0;
  virtual bool
  compileFromString(const String& shaderString) = 0;

 private:
  
};
}
