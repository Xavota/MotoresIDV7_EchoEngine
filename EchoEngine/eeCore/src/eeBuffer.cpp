#include "eeBuffer.h"

namespace eeEngineSDK {
void Buffer::InitData(uint32 dataSize, uint32 batchSize, const Byte* data)
{
  if (!data)
  {
    return;
  }
  m_data.resize(dataSize);
  //m_data.insert(m_data.begin(), data, data + dataSize - 1);
  memcpy(m_data.data(), data, dataSize);
  m_batchSize = batchSize;
}
}