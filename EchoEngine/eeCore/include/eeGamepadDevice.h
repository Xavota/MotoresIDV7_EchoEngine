/************************************************************************/
/**
 * @file eeGamepadDevice.h
 * @author Diego Castellanos
 * @date 05/06/22
 * @brief The game pad device for the inputs api.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include "eeInputDevice.h"

namespace eeEngineSDK {
/**
 * @brief
 * The keyboard device for the inputs api.
 */
class GamepadDevice : public InputDevice
{
 public:
  /**
   * @brief
   * Default constructor
   */
   GamepadDevice();
  /**
   * @brief
   * Default destructor
   */
  ~GamepadDevice() = default;

 private:
};
}
