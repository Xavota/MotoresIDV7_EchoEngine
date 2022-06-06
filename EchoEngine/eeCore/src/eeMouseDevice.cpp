#include "eeMouseDevice.h"

namespace eeEngineSDK {
MouseDevice::MouseDevice()
{
  m_keysStates.resize(static_cast<int32>(eMOUSE_KEYS::kKeyCount) >> 3, 0);

  m_keysValues[eMOUSE_KEYS::kWheel] = 0.0f;
  m_keysValues[eMOUSE_KEYS::kXAxis] = 0.0f;
  m_keysValues[eMOUSE_KEYS::kYAxis] = 0.0f;
}
}