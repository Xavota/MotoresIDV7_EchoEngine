#include "eeInputDevice.h"

namespace eeEngineSDK {
bool
InputDevice::isKeyPressed(int8 keyCode)
{
  if (keyCode >= 0 && keyCode < eKEYBOARD_KEYS::kKeyCount) {
    auto byteIndex = static_cast<int32>(keyCode >> 3);
    if (byteIndex < static_cast<int32>(m_keysStates.size())) {
      auto bitIndex = static_cast<Byte>(keyCode & 7);

      Byte opByte = (1 << bitIndex);
      return m_keysStates[byteIndex] & opByte;
    }
  }
  return false;
}
float
InputDevice::getKeyValue(int8 keyCode)
{
  if (m_keysValues.find(keyCode) != m_keysValues.end()) {
    return m_keysValues[keyCode];
  }
  return isKeyPressed(keyCode) ? 1.0f : 0.0f;
}
void
InputDevice::setKeyPressed(int8 keyCode, bool pressed)
{
  if (keyCode >= 0 && keyCode < eKEYBOARD_KEYS::kKeyCount) {
    auto byteIndex = static_cast<int32>(keyCode >> 3);
    if (byteIndex < static_cast<int32>(m_keysStates.size())) {
      auto bitIndex = static_cast<Byte>(keyCode & 7);

      Byte opByte = (1 << bitIndex);
      m_keysStates[byteIndex] =
      (m_keysStates[byteIndex] & (!opByte)) | (opByte * (pressed ? 1 : 0));
    }
  }
}
void
InputDevice::setKeyValue(int8 keyCode, float value)
{
  if (m_keysValues.find(keyCode) != m_keysValues.end()) {
    m_keysValues[keyCode] = value;
    return;
  }
  setKeyPressed(keyCode, value == 0.0f ? false : true);
}
}