#pragma once
#include "eePrerequisitesCore.h"
#include "eeBuffer.h"

namespace eeEngineSDK {
class Texture
{
 public:
  Texture() = default;
  virtual ~Texture() = default;

  virtual bool
  loadFromFile() = 0;

  virtual bool
  loadFromBuffer(void* buffer) = 0;



 private:
  Buffer* m_buffer;
};
}
