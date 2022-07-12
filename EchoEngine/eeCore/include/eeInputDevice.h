/************************************************************************/
/**
 * @file eeInputDevice.h
 * @author Diego Castellanos
 * @date 26/05/22
 * @brief The input device class, to store the devices data.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
/**
 * @brief
 * The input device class, to store the devices data.
 */
namespace eINPUT_DEVICE_TYPE {
enum E : int8 {
  kNone = -1,
  kKeyboard,
  kMouse,
  kGamepad
};
}
/**
 * @brief
 * The input device class, to store the devices data.
 */
class EE_CORE_EXPORT InputDevice
{
 public:
  /**
   * @brief
   * Default constructor
   */
  InputDevice() = default;
  /**
   * @brief
   * Default destructor
   */
  ~InputDevice() = default;

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
  FORCEINLINE virtual uint8
  getDeviceType()
  {
    return eINPUT_DEVICE_TYPE::kNone;
  }

  /**
   * @brief
   * Updates the device.
   *
   * @description
   * Updates the internal data of the device.
   */
  virtual void
  update();

  /**
   * @brief
   * Gets if a key is just pressed.
   *
   * @description
   * Returns true if that key is being pressed this frame, but not last frame.
   *
   * @param keyCode
   * The code of the key for the device.
   *
   * @return
   * True if that key is being pressed this frame, but not last frame.
   */
  virtual bool
  getButtonDown(uint8 keyCode);
  /**
   * @brief
   * Gets if a key is pressed.
   *
   * @description
   * Returns true if that key is being pressed.
   *
   * @param keyCode
   * The code of the key for the device.
   *
   * @return
   * True if that key is being pressed.
   */
  virtual bool
  getButton(uint8 keyCode);
  /**
   * @brief
   * Gets if a key is just released.
   *
   * @description
   * Returns true if that key is not being pressed this frame, but was pressed 
   * last frame.
   *
   * @param keyCode
   * The code of the key for the device.
   *
   * @return
   * True if that key is being pressed this frame, but not last frame.
   */
  virtual bool
  getButtonUp(uint8 keyCode);

  /**
   * @brief
   * Gets the current value of a key.
   *
   * @description
   * Returns how much of the key is being used.
   *
   * @param keyCode
   * The code of the key for the device.
   *
   * @return
   * How much of the key is being used.
   */
  virtual float
  getAxis(uint8 keyCode);

// protected:
  /**
   * @brief
   * Sets if a key is pressed.
   *
   * @description
   * Change the state of a key.
   *
   * @param keyCode
   * The code of the key for the device.
   * @param pressed
   * The new state of the key.
   */
  virtual void
  setKeyPressed(uint8 keyCode, bool pressed);
  /**
   * @brief
   * Sets the current value of a key.
   *
   * @description
   * Changes how much of the key is being used.
   *
   * @param keyCode
   * The code of the key for the device.
   * @param value
   * How much of the key is being used.
   */
  virtual void
  setKeyValue(uint8 keyCode, float value);



protected:
  /**
   * The states of every key
   */
  Vector<Byte> m_keysStates;
  /**
   * The last frame states of every key
   */
  Vector<Byte> m_keysLastStates;
  /**
   * Array of values for certain keys
   */
  Map<uint8, float> m_keysValues;
  /**
   * The type of device it is
   */
  eINPUT_DEVICE_TYPE::E m_deviceType;

  /**
   * The minimum key code of this device.
   */
   uint8 m_minKeyCode = 0;
  /**
   * The maximum key code of this device.
   */
   uint8 m_maxKeyCode = eBUTTONS_KEYS::kTotalCount;
};
}