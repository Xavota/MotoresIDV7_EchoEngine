#include "eeInput.h"
#if EE_PLATFORM == EE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace eeEngineSDK {
void
Input::update()
{
  for (auto& i : m_keyboardInputMap) {
    i.second.wasPressed = i.second.isPressed;
  }
  for (auto& i : m_mouseClicksInputMap) {
    i.second.wasPressed = i.second.isPressed;
  }

  m_mouseLastPosition = m_mousePosition;
}
void
Input::setKeyboardInputPressed(KEYBOARD_INPUT::E key, bool pressed)
{
  if (m_keyboardInputMap.find(key) != m_keyboardInputMap.end()) {
    m_keyboardInputMap[key].isPressed = pressed;
    return;
  }
  m_keyboardInputMap[key] = InputInfo{false, pressed};
}
void
Input::setMouseClickInputPressed(MOUSE_INPUT::E key, bool pressed)
{
  if (m_mouseClicksInputMap.find(key) != m_mouseClicksInputMap.end()) {
    m_mouseClicksInputMap[key].isPressed = pressed;
    return;
  }
  m_mouseClicksInputMap[key] = InputInfo{ false, pressed };
}
bool
Input::getKeyboardInputPressed(KEYBOARD_INPUT::E key)
{
  if (m_keyboardInputMap.find(key) != m_keyboardInputMap.end()) {
    return m_keyboardInputMap[key].isPressed
       && !m_keyboardInputMap[key].wasPressed;
  }
  return false;
}
bool
Input::getKeyboardInputIsPressed(KEYBOARD_INPUT::E key)
{
  if (m_keyboardInputMap.find(key) != m_keyboardInputMap.end()) {
    return m_keyboardInputMap[key].isPressed;
  }
  return false;
}
bool
Input::getKeyboardInputReleased(KEYBOARD_INPUT::E key)
{
  if (m_keyboardInputMap.find(key) != m_keyboardInputMap.end()) {
    return !m_keyboardInputMap[key].isPressed
         && m_keyboardInputMap[key].wasPressed;
  }
  return false;
}
bool
Input::getMouseClickInputPressed(MOUSE_INPUT::E key)
{
  if (m_mouseClicksInputMap.find(key) != m_mouseClicksInputMap.end()) {
    return m_mouseClicksInputMap[key].isPressed
       && !m_mouseClicksInputMap[key].wasPressed;
  }
  return false;
}
bool
Input::getMouseClickInputIsPressed(MOUSE_INPUT::E key)
{
  if (m_mouseClicksInputMap.find(key) != m_mouseClicksInputMap.end()) {
    return m_mouseClicksInputMap[key].isPressed;
  }
  return false;
}
bool
Input::getMouseClickInputReleased(MOUSE_INPUT::E key)
{
  if (m_mouseClicksInputMap.find(key) != m_mouseClicksInputMap.end()) {
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