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

#pragma warning(push)
#pragma warning(disable: 4267)
#include <gainput/gainput.h>
#pragma warning(pop)

#include <eeVector2.h>

namespace eeEngineSDK {
/**
 * @brief
 * The input manager, for input devices managing.
 */
class EE_GAINPUT_EXPORT GaInputManager : public InputManager
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


  /**
   * @brief
   * Initializes the input manager.
   *
   * @description
   * Initializes the manager with the sizes of the screen and everything inside.
   *
   * @param screenSize
   * The size of the current screen.
   */
  void
  init(Vector2i screenSize) override;

  /**
   * @brief
   * Updates the inputs.
   *
   * @description
   * Updates the events on the devices, delete old events and add new ones.
   * 
   * @param dt
   * Time elapsed since las frame in seconds.
   */
  void
  update(float dt) override;

  /**
   * @brief
   * Handles the messages given by the system.
   *
   * @description
   * Sends the messages given to the input handler, only in specific platforms.
   *
   * @param sysMsg
   * The struct containing the message.
   */
  void
  handleSystemMessage(systemMSG sysMsg) override;

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
   * Get a list of events.
   *
   * @description
   * Returns a list of the last events occurred on the devices.
   *
   * @return
   * A list of the last events occurred on the devices.
   */
  Vector<InputDeviceEvent>
  getEvents() override;

 private:
  gainput::InputManager m_manager;
  SPtr<gainput::InputMap> m_inputMap;

  Map<uint32, Map<uint8, gainput::Key>> m_boolKeysMap;
  Map<uint32, Map<uint8, gainput::Key>> m_floatKeysMap;
};
}
