#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
class VertexShader
{
public:
  VertexShader();
  virtual
  ~VertexShader();

  virtual bool
  compileFromFile(const String& fileName) = 0;
  virtual bool
  compileFromString(const String& shaderString) = 0;
};
}
