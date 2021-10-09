#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
class Buffer
{
 public:
  Buffer() = default;
  Buffer(void* data) : m_data(data){};
  virtual
  ~Buffer() = default;

  virtual void 
  Release() = 0;

 private:
  SPtr<void> m_data;
};
}
  