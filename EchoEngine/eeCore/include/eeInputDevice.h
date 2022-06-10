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
  FORCEINLINE virtual int8
  getDeviceType()
  {
    return eINPUT_DEVICE_TYPE::kNone;
  }

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
  isKeyPressed(int8 keyCode);

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
  getKeyValue(int8 keyCode);

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
  setKeyPressed(int8 keyCode, bool pressed);
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
  setKeyValue(int8 keyCode, float value);



  /**
   * The states of every key
   */
  Vector<Byte> m_keysStates;
  /**
   * Array of values for certain keys
   */
  Map<int8, float> m_keysValues;
  /**
   * The type of device it is
   */
  eINPUT_DEVICE_TYPE::E m_deviceType;
};
}