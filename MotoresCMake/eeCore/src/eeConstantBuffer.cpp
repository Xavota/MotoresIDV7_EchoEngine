#include "eeConstantBuffer.h"

namespace eeEngineSDK {
ConstantBuffer::~ConstantBuffer()
{
  release();
}
}