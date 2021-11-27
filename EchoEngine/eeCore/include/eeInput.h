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
#include <windows.h>
#include <eeModule.h>
#include "eeVector2.h"

namespace eeEngineSDK {


/**
 * @brief
 * The input manager for the api.
 */
class EE_CORE_EXPORT Input : public Module<Input>
{
public:
  enum class eKEYBOARD
  {
    NONE = -1,
    Q,
    W,
    E,
    A,
    S,
    D,
    TAB,
    COUNT
  };

  enum class eMOUSE_CLICK
  {
    NONE = -1,
    LEFT_CLICK,
    RIGHT_CLICK,
    COUNT
  };



  void
  update();


  void
  setKeyboardInputPressed(eKEYBOARD key, bool pressed);
  void
  setMouseClickInputPressed(eMOUSE_CLICK key, bool pressed);

  bool
  getKeyboardInputPressed(eKEYBOARD key);
  bool
  getKeyboardInputIsPressed(eKEYBOARD key);
  bool
  getKeyboardInputReleased(eKEYBOARD key);

  bool
  getMouseClickInputPressed(eMOUSE_CLICK key);
  bool
  getMouseClickInputIsPressed(eMOUSE_CLICK key);
  bool
  getMouseClickInputReleased(eMOUSE_CLICK key);

  void
  setMousePosition(Vector2i pos);

  Vector2i
  getMousePosition();
  Vector2i
  getMouseMovement();

  Input() = default;
  ~Input() = default;

 private:
  struct InputInfo
  {
    bool isPressed = false;
    bool wasPressed = false;
  };


  Map<eKEYBOARD, InputInfo> m_keyboardInputMap;
  Map<eMOUSE_CLICK, InputInfo> m_mouseClicksInputMap;
  Vector2i m_mousePosition;
  Vector2i m_mouseLastPosition;
};
}