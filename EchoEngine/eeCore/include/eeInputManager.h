/************************************************************************/
/**
 * @file eeInputDevice.h
 * @author Diego Castellanos
 * @date 26/05/22
 * @brief The input manager, for input devices managing.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeModule.h>

namespace eeEngineSDK {
/**
 * @brief
 * The input manager, for input devices managing.
 */
class InputManager : public Module<InputManager>
{
 public:
  /**
   * @brief
   * Default constructor
   */
  InputManager() = default;
  /**
   * @brief
   * Default destructor
   */
  virtual
  ~InputManager() = default;


  /**
   * @brief
   * Updates the inputs.
   *
   * @description
   * Updates the events on the devices, delete old events and add new ones.
   */
  virtual void
  Update();

  /**
   * @brief
   * Get the detected devices count.
   *
   * @description
   * Get the number of devices plugged to the hardware.
   *
   * @return
   * The number of devices plugged to the hardware.
   */
  virtual uint32
  getPluggedDevicesCount();
  /**
   * @brief
   * Get a device ptr.
   *
   * @description
   * Returns the device ptr with the given id, nullptr if the id doesn't exist.
   *
   * @param id
   * The id of the device asked.
   *
   * @return
   * The device ptr with the given id, nullptr if the id doesn't exist.
   */
  virtual SPtr<InputDevice>
  getDevice(uint32 id);

  /**
   * @brief
   * Get a device ptr.
   *
   * @description
   * Returns the device ptr with the given id, nullptr if the id doesn't exist.
   *
   * @param id
   * The id of the device asked.
   *
   * @return
   * The device ptr with the given id, nullptr if the id doesn't exist.
   */
  virtual SPtr<InputDevice>
  getEvents();

 protected:
  /**
   * The devices stored.
   */
  Map<uint32, SPtr<InputDevice>> m_devices;
};
}