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
  loadFromFile(){};

  virtual bool
  loadFromBuffer(SPtr<void> buffer){};



 private:
};
}
