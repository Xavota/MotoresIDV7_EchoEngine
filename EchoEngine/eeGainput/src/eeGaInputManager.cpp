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
  m_devices[mouseIndex]
  = memoryMan.newPtr<MouseDevice>();

  m_inputMap = memoryMan.newPtr<gainput::InputMap>(m_manager);

  m_boolKeysMap[keyboardIndex] = Map<uint8, gainput::Key>();

  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kA] = gainput::KeyA;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kB] = gainput::KeyB;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kC] = gainput::KeyC;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kD] = gainput::KeyD;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kE] = gainput::KeyE;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kF] = gainput::KeyF;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kG] = gainput::KeyG;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kH] = gainput::KeyH;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kI] = gainput::KeyI;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kJ] = gainput::KeyJ;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kK] = gainput::KeyK;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kL] = gainput::KeyL;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kM] = gainput::KeyM;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kN] = gainput::KeyN;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kO] = gainput::KeyO;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kP] = gainput::KeyP;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kQ] = gainput::KeyQ;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kR] = gainput::KeyR;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kS] = gainput::KeyS;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kT] = gainput::KeyT;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kU] = gainput::KeyU;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kV] = gainput::KeyV;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kW] = gainput::KeyW;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kX] = gainput::KeyX;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kY] = gainput::KeyY;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kZ] = gainput::KeyZ;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNum0] = gainput::Key0;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNum1] = gainput::Key1;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNum2] = gainput::Key2;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNum3] = gainput::Key3;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNum4] = gainput::Key4;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNum5] = gainput::Key5;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNum6] = gainput::Key6;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNum7] = gainput::Key7;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNum8] = gainput::Key8;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNum9] = gainput::Key9;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kEscape] = gainput::KeyEscape;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kLControl] = gainput::KeyCtrlL;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kLShift] = gainput::KeyShiftL;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kLAlt] = gainput::KeyAltL;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kRControl] = gainput::KeyCtrlR;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kRShift] = gainput::KeyShiftR;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kRAlt] = gainput::KeyAltR;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kMenu] = gainput::KeyMenu;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kLBracket] = gainput::KeyBracketLeft;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kRBracket] = gainput::KeyBracketRight;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kSemicolon] = gainput::KeySemicolon;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kComma] = gainput::KeyComma;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kPeriod] = gainput::KeyPeriod;
//m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kQuote] = gainput::KeyQuote;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kSlash] = gainput::KeySlash;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kBackslash] = gainput::KeyBackslash;
//m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kTilde] = gainput::KeyTilde;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kEqual] = gainput::KeyEqual;
//m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kHyphen] = gainput::KeyDash;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kSpace] = gainput::KeySpace;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kEnter] = gainput::KeyReturn;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kBackspace] = gainput::KeyBackSpace;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kTab] = gainput::KeyTab;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kPageUp] = gainput::KeyPageUp;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kPageDown] = gainput::KeyPageDown;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kHome] = gainput::KeyHome;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kInsert] = gainput::KeyInsert;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kDelete] = gainput::KeyDelete;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kAdd] = gainput::KeyKpAdd;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kSubtract] = gainput::KeyKpSubtract;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kMultiply] = gainput::KeyKpMultiply;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kDivide] = gainput::KeyKpDivide;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kLeft] = gainput::KeyLeft;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kRight] = gainput::KeyRight;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kUp] = gainput::KeyUp;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kDown] = gainput::KeyDown;
//m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNumpad0] = gainput::KeyNumpad0;
//m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNumpad1] = gainput::KeyNumpad1;
//m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNumpad2] = gainput::KeyNumpad2;
//m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNumpad3] = gainput::KeyNumpad3;
//m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNumpad4] = gainput::KeyNumpad4;
//m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNumpad5] = gainput::KeyNumpad5;
//m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNumpad6] = gainput::KeyNumpad6;
//m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNumpad7] = gainput::KeyNumpad7;
//m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNumpad8] = gainput::KeyNumpad8;
//m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kNumpad9] = gainput::KeyNumpad9;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kF1] = gainput::KeyF1;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kF2] = gainput::KeyF2;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kF3] = gainput::KeyF3;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kF4] = gainput::KeyF4;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kF5] = gainput::KeyF5;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kF6] = gainput::KeyF6;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kF7] = gainput::KeyF7;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kF8] = gainput::KeyF8;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kF9] = gainput::KeyF9;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kF10] = gainput::KeyF10;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kF11] = gainput::KeyF11;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kF12] = gainput::KeyF12;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kF13] = gainput::KeyF13;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kF14] = gainput::KeyF14;
  m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kF15] = gainput::KeyF15;
//m_boolKeysMap[keyboardIndex][eKEYBOARD_KEYS::kPause] = gainput::KeyPause;


  for (auto& bkm : m_boolKeysMap) {
    for (auto& bk : bkm.second) {
      m_inputMap->MapBool(bk.first, bkm.first, bk.second);
    }
  }

  m_manager.SetDisplaySize(screenSize.x, screenSize.y);
}
void
GaInputManager::update(float dt)
{
  m_manager.Update();

  for (auto& bkm : m_boolKeysMap) {
    for (auto& bk : bkm.second) {
      m_devices[bkm.first]->setKeyPressed(bk.first, m_inputMap->GetBool(bk.first));
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