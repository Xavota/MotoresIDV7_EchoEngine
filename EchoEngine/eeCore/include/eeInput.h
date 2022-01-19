/************************************************************************/
/**
 * @file eeInput.h
 * @author Diego Castellanos
 * @date 25/10/21
 * @brief
 * The input manager for the api.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeModule.h>
#include "eeVector2.h"

namespace eeEngineSDK {
/**
 * @brief
 * The input manager for the api. 
 * // TODO: NEEDS TO REFACTOR TO USE AN EXTERN INPUT LIBRARY
 */
class EE_CORE_EXPORT Input : public Module<Input>
{
public:
  /**
   * @brief
   * Keyboard input types.
   */
  enum class eKEYBOARD
  {
    kNONE = -1,
    kQ,
    kW,
    kE,
    kA,
    kS,
    kD,
    kTAB,
    kCOUNT
  };

  /**
   * @brief
   * Mouse input types.
   */
  enum class eMOUSE_CLICK
  {
    kNONE = -1,
    kLEFT_CLICK,
    kRIGHT_CLICK,
    kCOUNT
  };


  /**
   * @brief
   * Updates the inputs.
   *
   * @description
   * Updates the state of the current inputs.
   */
  void
  update();


  /**
   * @brief
   * Set the state of a keyboard input.
   *
   * @description
   * Set the current state of a keyboard input, if it's pressed or not.
   *
   * @param key
   * The keyboard input.
   * @param pressed
   * If it's pressed or not.
   */
  void
  setKeyboardInputPressed(eKEYBOARD key, bool pressed);
  /**
   * @brief
   * Set the state of a mouse input.
   *
   * @description
   * Set the current state of a mouse input, if it's pressed or not.
   *
   * @param key
   * The mouse input.
   * @param pressed
   * If it's pressed or not.
   */
  void
  setMouseClickInputPressed(eMOUSE_CLICK key, bool pressed);

  /**
   * @brief
   * Get if the keyboard input is pressed one time.
   *
   * @description
   * Return if the keyboard input is pressed for the first time.
   *
   * @param key
   * The key that is being asked.
   *
   * @return
   * True if it's pressed for the first time.
   */
  bool
  getKeyboardInputPressed(eKEYBOARD key);
  /**
   * @brief
   * Get if the keyboard input is pressed.
   *
   * @description
   * Return if the keyboard input is currently being pressed.
   *
   * @param key
   * The key that is being asked.
   *
   * @return
   * True if it's currently being pressed.
   */
  bool
  getKeyboardInputIsPressed(eKEYBOARD key);
  /**
   * @brief
   * Get if the keyboard input is released.
   *
   * @description
   * Return if the keyboard input is released for the first time.
   *
   * @param key
   * The key that is being asked.
   *
   * @return
   * True if it's released for the first time.
   */
  bool
  getKeyboardInputReleased(eKEYBOARD key);

  /**
   * @brief
   * Get if the mouse input is pressed one time.
   *
   * @description
   * Return if the mouse input is pressed for the first time.
   *
   * @param key
   * The key that is being asked.
   *
   * @return
   * True if it's pressed for the first time.
   */
  bool
  getMouseClickInputPressed(eMOUSE_CLICK key);
  /**
   * @brief
   * Get if the mouse input is pressed.
   *
   * @description
   * Return if the mouse input is currently being pressed.
   *
   * @param key
   * The key that is being asked.
   *
   * @return
   * True if it's currently being pressed.
   */
  bool
  getMouseClickInputIsPressed(eMOUSE_CLICK key);
  /**
   * @brief
   * Get if the mouse input is released.
   *
   * @description
   * Return if the mouse input is released for the first time.
   *
   * @param key
   * The key that is being asked.
   *
   * @return
   * True if it's released for the first time.
   */
  bool
  getMouseClickInputReleased(eMOUSE_CLICK key);

  /**
   * @brief
   * Sets the mouse current position.
   *
   * @description
   * Updates the mouse current position on screen, and the movement value.
   *
   * @param pos
   * The new position of the mouse.
   */
  void
  setMousePosition(Vector2i pos);

  /**
   * @brief
   * Gets the mouse current position.
   *
   * @description
   * Returns the mouse current position on screen.
   *
   * @return
   * The mouse current position on screen.
   */
  Vector2i
  getMousePosition();
  /**
   * @brief
   * Gets the mouse last frame movement.
   *
   * @description
   * Returns the mouse last frame movement on screen.
   *
   * @return
   * The mouse last frame movement on screen.
   */
  Vector2i
  getMouseMovement();

  /**
   * @brief
   * Default constructor.
   */
  Input() = default;
  /**
   * @brief
   * Default destructor.
   */
  ~Input() = default;

 private:
  /**
   * @brief
   * A struct to store the inputs info.
   */
  struct InputInfo
  {
    bool isPressed = false;
    bool wasPressed = false;
  };


  /**
   * Map of keyboard inputs info
   */
  Map<eKEYBOARD, InputInfo> m_keyboardInputMap;
  /**
   * Map of mouse inputs info
   */
  Map<eMOUSE_CLICK, InputInfo> m_mouseClicksInputMap;
  /**
   * The mouse current position on screen.
   */
  Vector2i m_mousePosition;
  /**
   * The mouse last position on screen, for movement calculation.
   */
  Vector2i m_mouseLastPosition;
};
}