#include "eeInput.h"
#include <windows.h>

namespace eeEngineSDK {
void Input::update()
{
  for (Pair<eKEYBOARD, InputInfo> i : m_keyboardInputMap)
  {
    i.second.wasPressed = i.second.isPressed;
  }
  for (Pair<eMOUSE_CLICK, InputInfo> i : m_mouseClicksInputMap)
  {
    i.second.wasPressed = i.second.isPressed;
  }

  m_mouseLastPosition = m_mousePosition;
}
void
Input::setKeyboardInputPressed(eKEYBOARD key, bool pressed)
{
  if (m_keyboardInputMap.find(key) != m_keyboardInputMap.end())
  {
    m_keyboardInputMap[key].isPressed = pressed;
    return;
  }
  m_keyboardInputMap[key] = InputInfo{false, pressed};
}
void
Input::setMouseClickInputPressed(eMOUSE_CLICK key, bool pressed)
{
  if (m_mouseClicksInputMap.find(key) != m_mouseClicksInputMap.end())
  {
    m_mouseClicksInputMap[key].isPressed = pressed;
    return;
  }
  m_mouseClicksInputMap[key] = InputInfo{ false, pressed };
}
bool
Input::getKeyboardInputPressed(eKEYBOARD key)
{
  if (m_keyboardInputMap.find(key) != m_keyboardInputMap.end())
  {
    return m_keyboardInputMap[key].isPressed
       && !m_keyboardInputMap[key].wasPressed;
  }
  return false;
}
bool
Input::getKeyboardInputIsPressed(eKEYBOARD key)
{
  if (m_keyboardInputMap.find(key) != m_keyboardInputMap.end())
  {
    return m_keyboardInputMap[key].isPressed;
  }
  return false;
}
bool
Input::getKeyboardInputReleased(eKEYBOARD key)
{
  if (m_keyboardInputMap.find(key) != m_keyboardInputMap.end())
  {
    return !m_keyboardInputMap[key].isPressed
         && m_keyboardInputMap[key].wasPressed;
  }
  return false;
}
bool
Input::getMouseClickInputPressed(eMOUSE_CLICK key)
{
  if (m_mouseClicksInputMap.find(key) != m_mouseClicksInputMap.end())
  {
    return m_mouseClicksInputMap[key].isPressed
       && !m_mouseClicksInputMap[key].wasPressed;
  }
  return false;
}
bool
Input::getMouseClickInputIsPressed(eMOUSE_CLICK key)
{
  if (m_mouseClicksInputMap.find(key) != m_mouseClicksInputMap.end())
  {
    return m_mouseClicksInputMap[key].isPressed;
  }
  return false;
}
bool
Input::getMouseClickInputReleased(eMOUSE_CLICK key)
{
  if (m_mouseClicksInputMap.find(key) != m_mouseClicksInputMap.end())
  {
    return !m_mouseClicksInputMap[key].isPressed
         && m_mouseClicksInputMap[key].wasPressed;
  }
  return false;
}
void
Input::setMousePosition(Vector2i pos)
{
  m_mousePosition = pos;
}
Vector2i
Input::getMousePosition()
{
  return m_mousePosition;
}
Vector2i
Input::getMouseMovement()
{
  return m_mousePosition - m_mouseLastPosition;
}
}