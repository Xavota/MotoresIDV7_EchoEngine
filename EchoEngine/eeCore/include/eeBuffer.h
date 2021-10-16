#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
class EE_CORE_EXPORT Buffer
{
 public:
  Buffer() = default;
  virtual
  ~Buffer() = default;

  virtual void
  InitData(uint32 dataSize, uint32 batchSize, Byte* data);

  virtual void 
  Release(){};

 private:
  Vector<Byte> m_data;
  int32 m_batchSize = 0;
};
}
  