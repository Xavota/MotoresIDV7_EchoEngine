#include "eeMouseDevice.h"

namespace eeEngineSDK {
MouseDevice::MouseDevice()
{
  m_keysStates.resize((static_cast<int32>(eBUTTONS_KEYS::kMouseCount) >> 3) + 1, 0);
  m_keysLastStates.resize((static_cast<int32>(eBUTTONS_KEYS::kMouseCount) >> 3) + 1, 0);

  m_keysValues[eBUTTONS_KEYS::kMouseAxisPositionX] = 0.0f;
  m_keysValues[eBUTTONS_KEYS::kMouseAxisPositionY] = 0.0f;
  m_keysValues[eBUTTONS_KEYS::kMouseAxisX] = 0.0f;
  m_keysValues[eBUTTONS_KEYS::kMouseAxisY] = 0.0f;
  m_keysValues[eBUTTONS_KEYS::kMouseAxisWheel] = 0.0f;

  m_minKeyCode = eBUTTONS_KEYS::kMouseFirts;
  m_maxKeyCode = eBUTTONS_KEYS::kMouseLast;
}
void
MouseDevice::update()
{
  InputDevice::update();

  setKeyValue(eBUTTONS_KEYS::kMouseAxisWheel,
              getButton(eBUTTONS_KEYS::kMouseButtonWheelUp) ? 1.0f
            : getButton(eBUTTONS_KEYS::kMouseButtonWheelDown) ? -1.0f
            : 0.0f);

  m_keysValues[eBUTTONS_KEYS::kMouseAxisX] =
  m_keysValues[eBUTTONS_KEYS::kMouseAxisPositionX] - m_lastPosition.x;
  m_keysValues[eBUTTONS_KEYS::kMouseAxisY] = 
  m_keysValues[eBUTTONS_KEYS::kMouseAxisPositionY] - m_lastPosition.y;

  m_lastPosition.x = m_keysValues[eBUTTONS_KEYS::kMouseAxisPositionX];
  m_lastPosition.y = m_keysValues[eBUTTONS_KEYS::kMouseAxisPositionY];
}
}