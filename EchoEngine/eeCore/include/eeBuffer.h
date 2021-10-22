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
  InitData(uint32 dataSize, uint32 batchSize, const Byte* data);

  virtual void 
  Release(){};

  FORCEINLINE virtual int32
  getDataSize()
  {
    return m_data.size();
  }
  FORCEINLINE virtual const Vector<Byte>&
  getData()
  {
    return m_data;
  }
  FORCEINLINE virtual int32
  getBatchSize()
  {
    return m_batchSize;
  }

 private:
  Vector<Byte> m_data;
  uint32 m_batchSize = 0;
};
}
  