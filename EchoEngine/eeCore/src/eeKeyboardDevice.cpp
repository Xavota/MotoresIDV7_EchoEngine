#include "eeKeyboardDevice.h"

namespace eeEngineSDK {
KeyboardDevice::KeyboardDevice()
{
  m_keysStates.resize((static_cast<int32>(eBUTTONS_KEYS::kKeyboardCount) >> 3) + 1, 0);
  m_keysLastStates.resize((static_cast<int32>(eBUTTONS_KEYS::kKeyboardCount) >> 3) + 1, 0);

  m_minKeyCode = eBUTTONS_KEYS::kKeyboardFirts;
  m_maxKeyCode = eBUTTONS_KEYS::kKeyboardLast;
}
}