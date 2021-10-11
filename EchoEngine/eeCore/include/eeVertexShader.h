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
  compileFromFile(const String& fileName){};
  virtual bool
  compileFromString(const String& shaderString){};

 private:
  String m_shaderString;
};
}
