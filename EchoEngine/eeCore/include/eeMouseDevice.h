/************************************************************************/
/**
 * @file eeMouseDecide.h
 * @author Diego Castellanos
 * @date 04/06/22
 * @brief The mouse device for the inputs api.
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
class EE_CORE_EXPORT MouseDevice : public InputDevice
{
 public:
  /**
   * @brief
   * Default constructor
   */
   MouseDevice();
  /**
   * @brief
   * Default destructor
   */
  ~MouseDevice() = default;

  /**
   * @brief
   * Gets the type of device.
   *
   * @description
   * Returns the enum of the device type.
   *
   * @return
   * The enum of the device type.
   */
  FORCEINLINE int8
  getDeviceType() override
  {
    return eINPUT_DEVICE_TYPE::kMouse;
  }

 private:
};
}
