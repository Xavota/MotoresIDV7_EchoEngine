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

#include <eeVector2.h>

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
  FORCEINLINE uint8
  getDeviceType() override
  {
    return eINPUT_DEVICE_TYPE::kMouse;
  }

  /**
   * @brief
   * Updates the device.
   *
   * @description
   * Updates the internal data of the device.
   */
  void
  update() override;

 private:
  /**
   * Last mouse position in screen
   */
  Vector2f m_lastPosition;
};
}
