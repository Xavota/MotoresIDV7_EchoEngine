/************************************************************************/
/**
 * @file eeKeyboardDevice.h
 * @author Diego Castellanos
 * @date 31/05/22
 * @brief The keyboard device for the inputs api.
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
class KeyboardDevice : public InputDevice
{
 public:
  /**
   * @brief
   * Default constructor
   */
  KeyboardDevice();
  /**
   * @brief
   * Default destructor
   */
  ~KeyboardDevice() = default;

 private:
};
}
