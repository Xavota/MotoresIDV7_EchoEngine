#include "eeGaInputManager.h"

#include <eeMemoryManager.h>

#include <eeKeyboardDevice.h>
#include <eeMouseDevice.h>
#include <eeGamepadDevice.h>

namespace eeEngineSDK {
void
GaInputManager::Init(int32 displayWidth, int32 displayHeight)
{
  auto& memoryMan = MemoryManager::instance();

  m_devices[m_manager.CreateDevice<gainput::InputDeviceKeyboard>()]
  = memoryMan.newPtr<KeyboardDevice>();
  m_devices[m_manager.CreateDevice<gainput::InputDeviceMouse>()]
  = memoryMan.newPtr<MouseDevice>();

  m_manager.SetDisplaySize(displayWidth, displayHeight);
}
void
GaInputManager::Update()
{
}
uint32
GaInputManager::getPluggedDevicesCount()
{
  return m_devices.size();
}
SPtr<InputDevice>
GaInputManager::getDevice(uint32 id)
{
  return m_devices[id];
}
SPtr<InputDevice>
GaInputManager::getEvents()
{
  return SPtr<InputDevice>();
}
}