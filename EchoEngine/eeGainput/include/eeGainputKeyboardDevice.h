/************************************************************************/
/**
 * @file eeGainputKeyboardDevice.h
 * @author Diego Castellanos
 * @date 05/06/22
 * @brief The keyboard device for the inputs api.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesGainput.h"
#include <eeKeyboardDevice.h>

namespace eeEngineSDK {
/**
 * @brief
 * The keyboard device for the inputs api.
 */
class EE_GAINPUT_EXPORT GainputKeyboardDevice : public KeyboardDevice
{
 public:
  /**
   * @brief
   * Default constructor
   */
  GainputKeyboardDevice();
  /**
   * @brief
   * Default destructor
   */
  ~GainputKeyboardDevice() = default;
};
}
