#include "eeGaInputManager.h"

#include <eeMemoryManager.h>
#include <eeLogger.h>

#include <eeStringUtilities.h>

#include <eeKeyboardDevice.h>
#include <eeMouseDevice.h>
#include <eeGamepadDevice.h>

namespace eeEngineSDK {
void
GaInputManager::init(Vector2i screenSize)
{
  auto& memoryMan = MemoryManager::instance();

  m_devices[m_manager.CreateDevice<gainput::InputDeviceKeyboard>()]
  = memoryMan.newPtr<KeyboardDevice>();
  m_devices[m_manager.CreateDevice<gainput::InputDeviceMouse>()]
  = memoryMan.newPtr<MouseDevice>();

  m_inputMap = memoryMan.newPtr<gainput::InputMap>(m_manager);

  m_inputMap->MapBool(0, 0, gainput::KeyReturn);

  m_manager.SetDisplaySize(screenSize.x, screenSize.y);
}
void
GaInputManager::update(float dt)
{
  m_manager.Update(static_cast<uint64>(dt) * 1000);

  if (m_inputMap->GetBoolWasDown(0)) {
    m_devices[0]->setKeyPressed(eKEYBOARD_KEYS::kEnter, true);
  }
  else {
    m_devices[0]->setKeyPressed(eKEYBOARD_KEYS::kEnter, false);
  }
}
void
GaInputManager::handleSystemMessage(systemMSG sysMsg)
{
  m_manager.HandleMessage(*reinterpret_cast<MSG*>(&sysMsg));
}
uint32
GaInputManager::getPluggedDevicesCount()
{
  return static_cast<uint32>(m_devices.size());
}
SPtr<InputDevice>
GaInputManager::getDevice(uint32 id)
{
  return m_devices[id];
}
Vector<InputDeviceEvent>
GaInputManager::getEvents()
{
  return {};
}


EE_EXTERN EE_PLUGIN_EXPORT void
initPlugin()
{
  InputManager::startUp<GaInputManager>();
}
}