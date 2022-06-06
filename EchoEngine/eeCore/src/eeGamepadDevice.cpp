#include "eeGamepadDevice.h"

namespace eeEngineSDK {
GamepadDevice::GamepadDevice()
{
  m_keysStates.resize(static_cast<int32>(eGAMEPAD_KEYS::kKeyCount) >> 3, 0);

  m_keysValues[eGAMEPAD_KEYS::kLeftJoystickXAxis] = 0.0f;
  m_keysValues[eGAMEPAD_KEYS::kLeftJoystickYAxis] = 0.0f;
  m_keysValues[eGAMEPAD_KEYS::kRightJoystickXAxis] = 0.0f;
  m_keysValues[eGAMEPAD_KEYS::kRightJoystickYAxis] = 0.0f;
}
}