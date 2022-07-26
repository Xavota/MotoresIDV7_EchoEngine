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

  uint32 keyboardIndex = m_manager.CreateDevice<gainput::InputDeviceKeyboard>();
  m_devices[keyboardIndex] = memoryMan.newPtr<KeyboardDevice>();
  uint32 mouseIndex = m_manager.CreateDevice<gainput::InputDeviceMouse>();
  m_devices[mouseIndex] = memoryMan.newPtr<MouseDevice>();

  m_inputMap = memoryMan.newPtr<gainput::InputMap>(m_manager);

  m_boolKeysMap[keyboardIndex] = Map<uint8, uint32>();

  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonA] = gainput::KeyA;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonB] = gainput::KeyB;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonC] = gainput::KeyC;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonD] = gainput::KeyD;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonE] = gainput::KeyE;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonF] = gainput::KeyF;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonG] = gainput::KeyG;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonH] = gainput::KeyH;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonI] = gainput::KeyI;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonJ] = gainput::KeyJ;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonK] = gainput::KeyK;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonL] = gainput::KeyL;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonM] = gainput::KeyM;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonN] = gainput::KeyN;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonO] = gainput::KeyO;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonP] = gainput::KeyP;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonQ] = gainput::KeyQ;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonR] = gainput::KeyR;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonS] = gainput::KeyS;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonT] = gainput::KeyT;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonU] = gainput::KeyU;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonV] = gainput::KeyV;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonW] = gainput::KeyW;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonX] = gainput::KeyX;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonY] = gainput::KeyY;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonZ] = gainput::KeyZ;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNum0] = gainput::Key0;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNum1] = gainput::Key1;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNum2] = gainput::Key2;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNum3] = gainput::Key3;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNum4] = gainput::Key4;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNum5] = gainput::Key5;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNum6] = gainput::Key6;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNum7] = gainput::Key7;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNum8] = gainput::Key8;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNum9] = gainput::Key9;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonEscape] = gainput::KeyEscape;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonLControl] = gainput::KeyCtrlL;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonLShift] = gainput::KeyShiftL;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonLAlt] = gainput::KeyAltL;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonRControl] = gainput::KeyCtrlR;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonRShift] = gainput::KeyShiftR;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonRAlt] = gainput::KeyAltR;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonMenu] = gainput::KeyMenu;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonLBracket] = gainput::KeyBracketLeft;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonRBracket] = gainput::KeyBracketRight;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonSemicolon] = gainput::KeySemicolon;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonComma] = gainput::KeyComma;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonPeriod] = gainput::KeyPeriod;
//m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonQuote] = gainput::KeyQuote;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonSlash] = gainput::KeySlash;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonBackslash] = gainput::KeyBackslash;
//m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonTilde] = gainput::KeyTilde;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonEqual] = gainput::KeyEqual;
//m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonHyphen] = gainput::KeyDash;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonSpace] = gainput::KeySpace;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonEnter] = gainput::KeyReturn;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonBackspace] = gainput::KeyBackSpace;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonTab] = gainput::KeyTab;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonPageUp] = gainput::KeyPageUp;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonPageDown] = gainput::KeyPageDown;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonHome] = gainput::KeyHome;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonInsert] = gainput::KeyInsert;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonDelete] = gainput::KeyDelete;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonAdd] = gainput::KeyKpAdd;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonSubtract] = gainput::KeyKpSubtract;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonMultiply] = gainput::KeyKpMultiply;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonDivide] = gainput::KeyKpDivide;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonLeft] = gainput::KeyLeft;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonRight] = gainput::KeyRight;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonUp] = gainput::KeyUp;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonDown] = gainput::KeyDown;
//m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNumpad0] = gainput::KeyNumpad0;
//m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNumpad1] = gainput::KeyNumpad1;
//m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNumpad2] = gainput::KeyNumpad2;
//m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNumpad3] = gainput::KeyNumpad3;
//m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNumpad4] = gainput::KeyNumpad4;
//m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNumpad5] = gainput::KeyNumpad5;
//m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNumpad6] = gainput::KeyNumpad6;
//m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNumpad7] = gainput::KeyNumpad7;
//m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNumpad8] = gainput::KeyNumpad8;
//m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonNumpad9] = gainput::KeyNumpad9;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonF1] = gainput::KeyF1;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonF2] = gainput::KeyF2;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonF3] = gainput::KeyF3;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonF4] = gainput::KeyF4;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonF5] = gainput::KeyF5;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonF6] = gainput::KeyF6;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonF7] = gainput::KeyF7;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonF8] = gainput::KeyF8;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonF9] = gainput::KeyF9;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonF10] = gainput::KeyF10;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonF11] = gainput::KeyF11;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonF12] = gainput::KeyF12;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonF13] = gainput::KeyF13;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonF14] = gainput::KeyF14;
  m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonF15] = gainput::KeyF15;
//m_boolKeysMap[keyboardIndex][eBUTTONS_KEYS::kKeyboardButtonPause] = gainput::KeyPause;


  m_boolKeysMap[mouseIndex] = Map<uint8, uint32>();
  m_floatKeysMap[mouseIndex] = Map<uint8, uint32>();

  m_boolKeysMap[mouseIndex][eBUTTONS_KEYS::kMouseButtonLeft] = gainput::MouseButtonLeft;
  m_boolKeysMap[mouseIndex][eBUTTONS_KEYS::kMouseButtonRight] = gainput::MouseButtonRight;
  m_boolKeysMap[mouseIndex][eBUTTONS_KEYS::kMouseButtonMiddle] = gainput::MouseButtonMiddle;
  m_boolKeysMap[mouseIndex][eBUTTONS_KEYS::kMouseButton3] = gainput::MouseButton5;
  m_boolKeysMap[mouseIndex][eBUTTONS_KEYS::kMouseButton4] = gainput::MouseButton6;
  m_boolKeysMap[mouseIndex][eBUTTONS_KEYS::kMouseButton5] = gainput::MouseButton7;
  m_boolKeysMap[mouseIndex][eBUTTONS_KEYS::kMouseButton6] = gainput::MouseButton8;
  m_boolKeysMap[mouseIndex][eBUTTONS_KEYS::kMouseButton7] = gainput::MouseButton9;
  m_boolKeysMap[mouseIndex][eBUTTONS_KEYS::kMouseButton8] = gainput::MouseButton10;
  m_boolKeysMap[mouseIndex][eBUTTONS_KEYS::kMouseButton9] = gainput::MouseButton11;
  m_boolKeysMap[mouseIndex][eBUTTONS_KEYS::kMouseButtonWheelUp] = gainput::MouseButtonWheelUp;
  m_boolKeysMap[mouseIndex][eBUTTONS_KEYS::kMouseButtonWheelDown] = gainput::MouseButtonWheelDown;

  m_floatKeysMap[mouseIndex][eBUTTONS_KEYS::kMouseAxisPositionX] = gainput::MouseAxisX;
  m_floatKeysMap[mouseIndex][eBUTTONS_KEYS::kMouseAxisPositionY] = gainput::MouseAxisY;



  for (auto& bkm : m_boolKeysMap) {
    for (auto& bk : bkm.second) {
      m_inputMap->MapBool(bk.first, bkm.first, bk.second);
    }
  }
  for (auto& fkm : m_floatKeysMap) {
    for (auto& fk : fkm.second) {
      m_inputMap->MapFloat(fk.first, fkm.first, fk.second);
    }
  }

  m_manager.SetDisplaySize(screenSize.x, screenSize.y);
}
void
GaInputManager::update(float /*dt*/)
{
  m_manager.Update();
  for (auto& d : m_devices) {
    d.second->update();
  }

  for (auto& bkm : m_boolKeysMap) {
    for (auto& bk : bkm.second) {
      m_devices[bkm.first]->setKeyPressed(bk.first, m_inputMap->GetBool(bk.first));
    }
  }
  for (auto& fkm : m_floatKeysMap) {
    for (auto& fk : fkm.second) {
      m_devices[fkm.first]->setKeyValue(fk.first, m_inputMap->GetFloat(fk.first));
    }
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
WPtr<InputDevice>
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