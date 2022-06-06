#include "eeKeyboardDevice.h"

namespace eeEngineSDK {
KeyboardDevice::KeyboardDevice()
{
  m_keysStates.resize(static_cast<int32>(eKEYBOARD_KEYS::kKeyCount) >> 3, 0);
}
}