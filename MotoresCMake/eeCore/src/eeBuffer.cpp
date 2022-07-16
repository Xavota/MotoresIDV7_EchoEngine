#include "eeBuffer.h"

namespace eeEngineSDK {
bool
Buffer::initData(SIZE_T dataSize, uint32 batchSize, const Byte* data)
{
  m_data.resize(dataSize);
  m_batchSize = batchSize;
  if (data) {
    memcpy(m_data.data(), data, dataSize);
    return true;
  }

  return true;
}
void
Buffer::updateData(const Byte* data)
{
  if (data) {
    memcpy(m_data.data(), data, m_data.size());
  }
  else {
    memset(m_data.data(), 0, m_data.size());
  }
}
}