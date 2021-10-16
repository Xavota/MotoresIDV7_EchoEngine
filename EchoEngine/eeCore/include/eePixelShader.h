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
  compileFromFile(const String&/*fileName*/) { return true; }
  virtual bool
  compileFromString(const String& /*shaderString*/){return true;}

 private:
  String m_shaderString;
};
}
