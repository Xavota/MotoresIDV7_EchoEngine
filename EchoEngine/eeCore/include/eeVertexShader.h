#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
class EE_CORE_EXPORT VertexShader
{
public:
  VertexShader() = default;
  virtual
  ~VertexShader() = default;

  virtual bool
  compileFromFile(const String& /*fileName*/){return true;}
  virtual bool
  compileFromString(const String& /*shaderString*/){return true;}

 private:
  String m_shaderString;
};
}
