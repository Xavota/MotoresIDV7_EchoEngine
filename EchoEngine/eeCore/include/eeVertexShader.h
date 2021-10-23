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

  virtual void
  use() {}

  virtual void
  setModelMatrix(const Matrix4f& /*model*/) {}
  virtual void
  setViewMatrix(const Matrix4f& /*view*/) {}
  virtual void
  setProjectionMatrix(const Matrix4f& /*proj*/) {}


 private:
  String m_shaderString;
};
}
