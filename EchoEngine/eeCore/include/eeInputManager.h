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

#include <eeVector2.h>

#include "eeInputDeviceEvent.h"

namespace eeEngineSDK {
/**
 * @brief
 * The struct for system messages.
 */
struct systemMSG {
  void* winPtr;
  uint32 message;
  SIZE_T* wParam;
  SIZE_T* lParam;
  uint32 time;
  Vector2i pt;
};

/**
 * @brief
 * The input manager, for input devices managing.
 */
class EE_CORE_EXPORT InputManager : public Module<InputManager>
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
   * Initializes the input manager.
   *
   * @description
   * Initializes the manager with the sizes of the screen and everything inside.
   *
   * @param screenSize
   * The size of the current screen.
   */
  virtual void
  init(Vector2i /*screenSize*/) {}

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
  virtual void
  update(float /*dt*/) {}

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
  virtual void
  handleSystemMessage(systemMSG /*sysMsg*/) {}

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
  getPluggedDevicesCount() { return 0; }
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
  virtual WPtr<InputDevice>
  getDevice(uint32 /*id*/) { return {}; }

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
  virtual Vector<InputDeviceEvent>
  getEvents() { return {}; }

 protected:
  /**
   * The devices stored.
   */
  Map<uint32, SPtr<InputDevice>> m_devices;
};
}