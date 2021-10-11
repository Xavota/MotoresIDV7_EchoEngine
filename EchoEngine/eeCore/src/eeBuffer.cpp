#include "eeBuffer.h"

namespace eeEngineSDK {
void Buffer::InitData(uint32 dataSize, uint32 batchSize, Byte* data)
{
  m_data.resize(dataSize);
  m_data.insert(m_data.begin(), data, data + dataSize - 1);
  m_batchSize = batchSize;
}
}