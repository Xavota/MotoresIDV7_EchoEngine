/************************************************************************/
/**
 * @file eeInputDeviceEvent.h
 * @author Diego Castellanos
 * @date 26/05/22
 * @brief The event struct for the input devices. Stores an event occurred on
 * an input device.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
/**
 * @brief
 * The event struct for the input devices. Stores an event occurred on an
 * input device.
 */
struct InputDeviceEvent
{
  /**
   * The id of the device of the event stored.
   */
  uint32 m_deviceID = 0;
  /**
   * The id of the input on the device of the event stored.
   */
  uint32 m_inputID = 0;
  /**
   * The value of the input on the device of the event stored.
   */
  float m_value = 0.0f;
  /**
   * If the input on the device is being pressed on the event stored.
   */
  bool m_isPressed = false;
};
}
