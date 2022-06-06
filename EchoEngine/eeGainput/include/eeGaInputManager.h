/************************************************************************/
/**
 * @file eeGaInputManager.h
 * @author Diego Castellanos
 * @date 03/03/22
 * @brief The input manager, for input devices managing.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesGainput.h"
#include <eeInputManager.h>

#include <gainput/gainput.h>

namespace eeEngineSDK {
/**
 * @brief
 * The input manager, for input devices managing.
 */
class GaInputManager : public InputManager
{
 public:
  /**
   * @brief
   * Default constructor
   */
  GaInputManager() = default;
  /**
   * @brief
   * Default destructor
   */
  ~GaInputManager() = default;


  void
  Init(int32 displayWidth, int32 displayHeight);

  /**
   * @brief
   * Updates the inputs.
   *
   * @description
   * Updates the events on the devices, delete old events and add new ones.
   */
  void
  Update() override;

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
  uint32
  getPluggedDevicesCount() override;
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
  SPtr<InputDevice>
  getDevice(uint32 id) override;

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
  SPtr<InputDevice>
  getEvents() override;

 private:
  gainput::InputManager m_manager;
};
}
