#pragma once
#include "eePrerequisitesCore.h"
#include "eeBuffer.h"

namespace eeEngineSDK {
class EE_CORE_EXPORT Texture
{
 public:
  Texture() = default;
  virtual ~Texture() = default;

  virtual bool
  loadFromFile(){return true;};

  virtual bool
  loadFromBuffer(SPtr<void> buffer){return true;};



 private:
};
}
