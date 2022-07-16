#include "eeInputDevice.h"

namespace eeEngineSDK {
bool
getBitState(const Vector<Byte>& keysStates, uint8 keyCode)
{
  auto byteIndex = static_cast<uint32>(keyCode >> 3);
  if (byteIndex < static_cast<uint32>(keysStates.size())) {
    auto bitIndex = static_cast<Byte>(keyCode & 7);

    Byte opByte = (1 << bitIndex);
    return keysStates[byteIndex] & opByte;
  }
  return false;
}

void
InputDevice::update()
{
  memcpy(m_keysLastStates.data(),
         m_keysStates.data(),
         m_keysLastStates.size() * sizeof(Byte));
}
bool
InputDevice::getButtonDown(uint8 keyCode)
{
  if (keyCode >= m_minKeyCode && keyCode <= m_maxKeyCode) {
    uint8 realKeyCode = keyCode - m_minKeyCode;
    return getBitState(m_keysStates, realKeyCode)
        && !getBitState(m_keysLastStates, realKeyCode);
  }
  return false;
}
bool
InputDevice::getButton(uint8 keyCode)
{
  if (keyCode >= m_minKeyCode && keyCode <= m_maxKeyCode) {
    uint8 realKeyCode = keyCode - m_minKeyCode;
    return getBitState(m_keysStates, realKeyCode);
  }
  return false;
}
bool
InputDevice::getButtonUp(uint8 keyCode)
{
  if (keyCode >= m_minKeyCode && keyCode <= m_maxKeyCode) {
    uint8 realKeyCode = keyCode - m_minKeyCode;
    return !getBitState(m_keysStates, realKeyCode)
        && getBitState(m_keysLastStates, realKeyCode);
  }
  return false;
}
float
InputDevice::getAxis(uint8 keyCode)
{
  if (m_keysValues.find(keyCode) != m_keysValues.end()) {
    return m_keysValues[keyCode];
  }
  return getButton(keyCode) ? 1.0f : 0.0f;
}
void
InputDevice::setKeyPressed(uint8 keyCode, bool pressed)
{
  if (keyCode >= m_minKeyCode && keyCode <= m_maxKeyCode) {
    uint8 realKeyCode = keyCode - m_minKeyCode;
    auto byteIndex = static_cast<uint32>(realKeyCode >> 3);
    if (byteIndex < static_cast<uint32>(m_keysStates.size())) {
      auto bitIndex = static_cast<Byte>(realKeyCode & 7);

      Byte opByte = (1 << bitIndex);
      Byte negOpByte = ~opByte;
      Byte orOpByte = opByte * (pressed ? 1 : 0);

      m_keysStates[byteIndex] &= negOpByte;
      m_keysStates[byteIndex] |= orOpByte;
    }
  }
}
void
InputDevice::setKeyValue(uint8 keyCode, float value)
{
  if (m_keysValues.find(keyCode) != m_keysValues.end()) {
    m_keysValues[keyCode] = value;
    return;
  }
  setKeyPressed(keyCode, value == 0.0f ? false : true);
}
}