#include "eeBaseAppTest1.h"

#pragma comment(lib, "ComDlg32.lib")

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <windowsx.h>
#include <commdlg.h>

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

#define DX11
#define DEFERRED_RENDERING
#include <eeCoreConfiguration.h>
#include <eeDX11GraphicsApi.h>

#include <eeMemoryManager.h>
#include <eeResourceManager.h>
#include <eeSceneManager.h>
#include <eeLogger.h>
#include <eeMath.h>
#include <eeInput.h>
#include <eeTime.h>
#include <eeInputManager.h>
#include <eeAudioManager.h>
#include <eeOmniverseManager.h>

#include <eeScene.h>

#include <eeWindow.h>

#include <eeVertexShader.h>
#include <eePixelShader.h>
#include <eeRasterizerState.h>
#include <eeTexture.h>

#include <eeAnimation.h>
#include <eeSkeletalMesh.h>
#include <eeStaticMesh.h>
#include <eeMesh.h>
#include <eeColor.h>
#include <eeImage.h>
#include <eeMaterial.h>
#include <eeSound.h>
#include <eeAudio.h>

#include <eeActor.h>
#include <eeCAnimation.h>
#include <eeCBounds.h>
#include <eeCCamera.h>
#include <eeCLight.h>
#include <eeCRender.h>
#include <eeCSkeletalMesh.h>
#include <eeCStaticMesh.h>
#include <eeCTransform.h>

#include <eeInputDevice.h>
#include <eeGamepadDevice.h>
#include <eeKeyboardDevice.h>
#include <eeMouseDevice.h>

#include <eeTransform.h>

using eeEngineSDK::Logger;
using eeEngineSDK::GraphicsApi;
using eeEngineSDK::ResourceManager;
using eeEngineSDK::SceneManager;
using eeEngineSDK::Scene;
using eeEngineSDK::Vector4f;
using eeEngineSDK::Vector3f;
using eeEngineSDK::Vector2f;
using eeEngineSDK::Vector2i;
using eeEngineSDK::Point2D;
using eeEngineSDK::Color;
using eeEngineSDK::ColorI;
using eeEngineSDK::Image;
using eeEngineSDK::Material;
using eeEngineSDK::Matrix4f;
using eeEngineSDK::Transform;
using eeEngineSDK::Quaternion;
using eeEngineSDK::SimplexVertex;
using eeEngineSDK::StaticMesh;
using eeEngineSDK::Mesh;
using eeEngineSDK::SkeletalMesh;
using eeEngineSDK::Skeletal;
using eeEngineSDK::Animation;
using eeEngineSDK::Vector;
using eeEngineSDK::Map;
using eeEngineSDK::Pair;
using eeEngineSDK::uint8;
using eeEngineSDK::uint16;
using eeEngineSDK::uint32;
using eeEngineSDK::SPtr;
using eeEngineSDK::WPtr;
using eeEngineSDK::Math;
using eeEngineSDK::VertexShader;
using eeEngineSDK::PixelShader;
using eeEngineSDK::Byte;
using eeEngineSDK::Texture;
using eeEngineSDK::ConstantBuffer;
using eeEngineSDK::RasterizerState;
using eeEngineSDK::SamplerState;
using eeEngineSDK::Sound;
using eeEngineSDK::Audio;

using eeEngineSDK::Actor;
using eeEngineSDK::ActorNode;
using eeEngineSDK::Component;
using eeEngineSDK::CAnimation;
using eeEngineSDK::CBounds;
using eeEngineSDK::CCamera;
using eeEngineSDK::CLight;
using eeEngineSDK::CRender;
using eeEngineSDK::CSkeletalMesh;
using eeEngineSDK::CStaticMesh;
using eeEngineSDK::CTransform;

using eeEngineSDK::Input;
using eeEngineSDK::CameraDesc;
using eeEngineSDK::String;
using eeEngineSDK::WString;

using eeEngineSDK::MemoryManager;
using eeEngineSDK::Time;
using eeEngineSDK::InputManager;
using eeEngineSDK::AudioManager;
using eeEngineSDK::OmniverseManager;

using eeEngineSDK::systemMSG;

using eeEngineSDK::ViewportDesc;

using eeEngineSDK::Window;

using eeEngineSDK::InputDevice;
using eeEngineSDK::GamepadDevice;
using eeEngineSDK::KeyboardDevice;
using eeEngineSDK::MouseDevice;



extern IMGUI_IMPL_API LRESULT
ImGui_ImplWin32_WndProcHandler(HWND _hwnd,
                               UINT _msg,
                               WPARAM _wParam,
                               LPARAM _lParam);

LRESULT CALLBACK
WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  auto& inputMan = Input::instance();

  // Handle UI inputs
  if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) {
    return 1;
  }

  PAINTSTRUCT ps;
  HDC hdc;

  switch (message) {
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  case WM_KEYDOWN:
    if (wParam == 'Q') {
      inputMan.setKeyboardInputPressed(eeEngineSDK::KEYBOARD_INPUT::kQ, true);
    }
    else if (wParam == 'W') {
      inputMan.setKeyboardInputPressed(eeEngineSDK::KEYBOARD_INPUT::kW, true);
    }
    else if (wParam == 'E') {
      inputMan.setKeyboardInputPressed(eeEngineSDK::KEYBOARD_INPUT::kE, true);
    }
    else if (wParam == 'A') {
      inputMan.setKeyboardInputPressed(eeEngineSDK::KEYBOARD_INPUT::kA, true);
    }
    else if (wParam == 'S') {
      inputMan.setKeyboardInputPressed(eeEngineSDK::KEYBOARD_INPUT::kS, true);
    }
    else if (wParam == 'D') {
      inputMan.setKeyboardInputPressed(eeEngineSDK::KEYBOARD_INPUT::kD, true);
    }
    else if (wParam == 9) { // TAB
      inputMan.setKeyboardInputPressed(eeEngineSDK::KEYBOARD_INPUT::kTab, true);
    }
    break;

  case WM_KEYUP:
    if (wParam == 'Q') {
      inputMan.setKeyboardInputPressed(eeEngineSDK::KEYBOARD_INPUT::kQ, false);
    }
    else if (wParam == 'W') {
      inputMan.setKeyboardInputPressed(eeEngineSDK::KEYBOARD_INPUT::kW, false);
    }
    else if (wParam == 'E') {
      inputMan.setKeyboardInputPressed(eeEngineSDK::KEYBOARD_INPUT::kE, false);
    }
    else if (wParam == 'A') {
      inputMan.setKeyboardInputPressed(eeEngineSDK::KEYBOARD_INPUT::kA, false);
    }
    else if (wParam == 'S') {
      inputMan.setKeyboardInputPressed(eeEngineSDK::KEYBOARD_INPUT::kS, false);
    }
    else if (wParam == 'D') {
      inputMan.setKeyboardInputPressed(eeEngineSDK::KEYBOARD_INPUT::kD, false);
    }
    else if (wParam == 9) { // TAB
      inputMan.setKeyboardInputPressed(eeEngineSDK::KEYBOARD_INPUT::kTab, false);
    }
    break;

  case WM_LBUTTONDOWN:
    inputMan.setMouseClickInputPressed(eeEngineSDK::MOUSE_INPUT::kLeftClick, true);
    break;

  case WM_RBUTTONDOWN:
    inputMan.setMouseClickInputPressed(eeEngineSDK::MOUSE_INPUT::kRightClick, true);
    break;

  case WM_LBUTTONUP:
    inputMan.setMouseClickInputPressed(eeEngineSDK::MOUSE_INPUT::kLeftClick, false);
    break;

  case WM_RBUTTONUP:
    inputMan.setMouseClickInputPressed(eeEngineSDK::MOUSE_INPUT::kRightClick, false);
    break;

  case WM_MOUSEMOVE:
    inputMan.setMousePosition(Vector2i{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) });
    break;

  case WM_SIZE:
  {
    static bool _first = true;
    if (!_first) {
      int width = 0, height = 0;
      RECT rc;
      GetClientRect(reinterpret_cast<HWND>(GraphicsApi::instance().getMainWindow().lock()->getWindowPtr()), &rc);
      width = rc.right - rc.left;
      height = rc.bottom - rc.top;
      GraphicsApi::instance().resizeWindow(Point2D{ static_cast<uint32>(width),
                                                    static_cast<uint32>(height) });
    }
    _first = false;
  }
  break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }


  if (InputManager::isStarted()) {
    systemMSG sysMsg;
    memset(&sysMsg, 0, sizeof(systemMSG));
    sysMsg.winPtr = hWnd;
    sysMsg.message = message;
    sysMsg.wParam = reinterpret_cast<eeEngineSDK::SIZE_T*>(wParam);
    sysMsg.lParam = reinterpret_cast<eeEngineSDK::SIZE_T*>(lParam);
    sysMsg.time = 0;
    sysMsg.pt = Vector2i{0, 0};
    InputManager::instance().handleSystemMessage(sysMsg);
  }

  return 0;
}

WString
loadFileDialog()
{
  // common dialog box structure, setting all fields to 0 is important
  OPENFILENAMEW ofn = { 0 };
  wchar_t szFile[260] = { 0 };

  // Initialize remaining fields of OPENFILENAME structure
  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = nullptr;
  ofn.lpstrFile = szFile;
  ofn.nMaxFile = sizeof(szFile);
  ofn.lpstrFilter = (L"All\0*.*");
  ofn.nFilterIndex = 1;
  ofn.lpstrFileTitle = nullptr;
  ofn.nMaxFileTitle = 0;
  ofn.lpstrInitialDir = nullptr;
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

  if (GetOpenFileNameW(&ofn) == TRUE) {
    return szFile;
  }

  return L"";
}

HRESULT
InitImgUI()
{
  auto& graphicsApi = GraphicsApi::instance();

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  const auto* basics =
  reinterpret_cast<const eeEngineSDK::DX11Basics*>(graphicsApi.getBasics());

  // Setup Platform/Renderer back ends
  ImGui_ImplDX11_Init(basics->m_device, basics->m_deviceContext);
  ImGui_ImplWin32_Init(graphicsApi.getMainWindow().lock()->getWindowPtr());

  return S_OK;
}

void
DrawLightCmp(WPtr<CLight> light, int32& uniqueId)
{
  auto sLight = light.lock();
  auto lightTypeIndex = static_cast<int32>(sLight->getLightType());
  Vector<const char*> lightTypeNames =
  {
    "Directional",
    "Point",
    "Spot"
  };
  ImGui::PushID(uniqueId++);
  if (ImGui::Combo("Light Type",
    &lightTypeIndex,
    lightTypeNames.data(),
    static_cast<uint32>(lightTypeNames.size()))) {
    sLight->setLightType(
      static_cast<eeEngineSDK::eLIGHT_TYPE::E>(lightTypeIndex));
  }
  ImGui::PopID();

  Color color = sLight->getColor();
  ImGui::PushID(uniqueId++);
  if (ImGui::ColorPicker4("Color", (float*)&color, 0, nullptr)) {
    sLight->setColor(color);
  }
  ImGui::PopID();

  float intensity = sLight->getIntensity();
  ImGui::PushID(uniqueId++);
  if (ImGui::DragFloat("Intensity", &intensity, 0.01f, 0.0f, 100.0f)) {
    sLight->setIntensity(intensity);
  }
  ImGui::PopID();

  if (sLight->getLightType() == eeEngineSDK::eLIGHT_TYPE::kSpot) {
    float innerAngle = sLight->getInnerAngle();
    float outerAngle = sLight->getOuterAngle();
    ImGui::PushID(uniqueId++);
    if (ImGui::DragFloat("Inner Angle",
      &innerAngle,
      0.01f,
      0.0f,
      outerAngle)) {
      sLight->setInnerAngle(innerAngle);
    }
    ImGui::PopID();
    ImGui::PushID(uniqueId++);
    if (ImGui::DragFloat("Outer Angle",
      &outerAngle,
      0.01f,
      innerAngle,
      Math::kPI - 0.001f)) {
      sLight->setOuterAngle(outerAngle);
    }
    ImGui::PopID();
  }
}

void
DrawTransformCmp(WPtr<CTransform> trans, int32& uniqueId)
{
  auto sTrans = trans.lock();
  ImGui::PushID(uniqueId++);
  Vector3f actPos = sTrans->getPosition();
  float pos[3] = { actPos.x, actPos.y, actPos.z };
  if (ImGui::DragFloat3("Position", pos, 0.01f, -1000.0f, 1000.0f)) {
    sTrans->setPosition(Vector3f(pos[0], pos[1], pos[2]));
  }
  ImGui::PopID();
  ImGui::PushID(uniqueId++);
  Vector3f actRot = sTrans->getRotation().getEuclidean();
  float rot[3] = { actRot.x, actRot.y, actRot.z };
  if (ImGui::DragFloat3("Rotation", rot, 0.01f, -1000.0f, 1000.0f)) {
    sTrans->setRotation(Quaternion(Vector3f(rot[0], rot[1], rot[2])));
  }
  ImGui::PopID();
  ImGui::PushID(uniqueId++);
  Vector3f actScale = sTrans->getScale();
  float scale[3] = { actScale.x, actScale.y, actScale.z };
  if (ImGui::DragFloat3("Scale", scale, 0.01f, -1000.0f, 1000.0f)) {
    sTrans->setScale(Vector3f(scale[0], scale[1], scale[2]));
  }
  ImGui::PopID();
}

void
DrawAnimationCmp(WPtr<CAnimation> anim, int32& uniqueId)
{
  auto sAnim = anim.lock();
  ImGui::PushID(uniqueId++);
  auto sAnimRes = sAnim->getAnimation();
  String animName;
  if (!sAnimRes.expired()) {
    animName = sAnimRes.lock()->getResourceName();
  }
  Map<String, SPtr<Animation>> anims =
  ResourceManager::instance().getAllAnimationResources();
  int animIndex = 0;
  int tempIndex = 0;
  Vector<const char*> names;
  for (auto& a : anims) {
    names.push_back(a.first.c_str());
    if (a.first == animName) {
      animIndex = tempIndex;
    }
    tempIndex++;
  }
  if (ImGui::Combo("Animation Resource",
                   &animIndex,
                   names.data(),
                   static_cast<int32>(names.size()))) {
    sAnim->setAnimation(ResourceManager::instance().getResourceAnimation(names[animIndex]));
  }
  ImGui::PopID();
}

void
DrawCameraCmp(WPtr<CCamera> cam, int32& uniqueId)
{
  auto sCam = cam.lock();
  ImGui::PushID(uniqueId++);
  eeEngineSDK::eCAMERA_PROJECTION_TYPE::E pt = sCam->getProjectionType();
  auto projIndex = static_cast<int>(pt);
  const char* projTypes[] = { "Orthographic", "Perspective" };
  if (ImGui::Combo("Projection Types", &projIndex, projTypes, 2)) {
    sCam->setProjectionType(
    static_cast<eeEngineSDK::eCAMERA_PROJECTION_TYPE::E>(projIndex));
  }
  ImGui::PopID();
  ImGui::PushID(uniqueId++);
  float fov = sCam->getFovAngle() * Math::k180_OVER_PI;
  if (ImGui::DragFloat("FOV", &fov, 0.1f, 10.0f, 89.0f)) {
    sCam->setFovAngle(fov * Math::kPI_OVER_180);
  }
  ImGui::PopID();
  ImGui::PushID(uniqueId++);
  float nearDist = sCam->getNearPlane();
  if (ImGui::DragFloat("Near", &nearDist, 0.01f, .01f, 200.0f)) {
    sCam->setNearPlane(nearDist);
  }
  ImGui::PopID();
  ImGui::PushID(uniqueId++);
  float farDist = sCam->getFarPlane();
  if (ImGui::DragFloat("Far", &farDist, 0.01f, .01f, 200.0f)) {
    sCam->setFarPlane(farDist);
  }
  ImGui::PopID();
  ImGui::PushID(uniqueId++);
  bool isMain = sCam->isMain();
  if (ImGui::Checkbox("Main Camera", &isMain)) {
    sCam->setMain(isMain);
  }
  ImGui::PopID();
}

void
DrawStaticMeshCmp(WPtr<CStaticMesh> staticMesh, int32& uniqueId)
{
  auto sStaticMesh = staticMesh.lock();
  auto mobTypeIndex = static_cast<int32>(sStaticMesh->getMobilityType());
  Vector<const char*> mobTypeNames =
  {
    "Dynamic",
    "Static"
  };
  ImGui::PushID(uniqueId++);
  if (ImGui::Combo("Mobility Type",
                   &mobTypeIndex,
                   mobTypeNames.data(),
                   static_cast<uint32>(mobTypeNames.size()))) {
    sStaticMesh->setMobilityType(
    static_cast<eeEngineSDK::eMOBILITY_TYPE::E>(mobTypeIndex));
  }
  ImGui::PopID();

  String staticMeshName = sStaticMesh->getStaticMesh().lock()->getResourceName();
  Map<String, SPtr<StaticMesh>> staticMeshes =
  ResourceManager::instance().getAllStaticMeshResources();
  int32 staticMeshIndex = 0;
  int32 tempIndex = 0;
  Vector<const char*> names;
  for (auto& m : staticMeshes) {
    names.push_back(m.first.c_str());
    if (m.first == staticMeshName) {
      staticMeshIndex = tempIndex;
    }
    tempIndex++;
  }
  ImGui::PushID(uniqueId++);
  if (ImGui::Combo("Static Mesh Resource",
                   &staticMeshIndex,
                   names.data(),
                   static_cast<uint32>(names.size()))) {
    sStaticMesh->setStaticMesh(
    ResourceManager::instance().getResourceStaticMesh(names[staticMeshIndex]));
  }
  ImGui::PopID();
}

void
DrawSkeletalMeshCmp(WPtr<CSkeletalMesh> skMesh, int32& uniqueId)
{
  auto sSkMesh = skMesh.lock();
  ImGui::PushID(uniqueId++);
  String modelName = sSkMesh->getModel().lock()->getResourceName();
  Map<String, SPtr<SkeletalMesh>> skMeshes =
  ResourceManager::instance().getAllSkeletalMeshResources();
  int modelIndex = 0;
  int tempIndex = 0;
  Vector<const char*> names;
  for (auto& skm : skMeshes) {
    names.push_back(skm.first.c_str());
    if (skm.first == modelName) {
      modelIndex = tempIndex;
    }
    tempIndex++;
  }
  if (ImGui::Combo("Skeletal Mesh Resource",
                   &modelIndex,
                   names.data(),
                   static_cast<int32>(names.size()))) {
    sSkMesh->setModel(ResourceManager::instance().getResourceSkeletalMesh(names[modelIndex]));
  }
  ImGui::PopID();
}

WPtr<Actor> g_actorAddingCmp;
bool g_addingCmp = false;
void
showActorData(WPtr<Actor> act, int32& uniqueId)
{
  auto sAct = act.lock();
  ImGui::PushID(uniqueId++);
  bool actActive = sAct->isActive();
  if (ImGui::Checkbox("Active", &actActive)) {
    sAct->setActive(actActive);
  }
  ImGui::PopID();


  ImGui::Separator();
  ImGui::Text("Transform");
  DrawTransformCmp(sAct->getTransform(), uniqueId);
  ImGui::Separator();
  WPtr<CAnimation> animC = sAct->getComponent<CAnimation>();
  if (!animC.expired()) {
    if (ImGui::TreeNode("Animation")) {
      DrawAnimationCmp(animC, uniqueId);
      ImGui::TreePop();
    }
    ImGui::Separator();
  }
  WPtr<CBounds> boundsC = sAct->getComponent<CBounds>();
  if (!boundsC.expired()) {
    ImGui::Text("Bounds");
    ImGui::Separator();
  }
  WPtr<CCamera> camC = sAct->getComponent<CCamera>();
  if (!camC.expired()) {
    if (ImGui::TreeNode("Camera")) {
      DrawCameraCmp(camC, uniqueId);
      ImGui::TreePop();
    }
    ImGui::Separator();
  }
  WPtr<CLight> lightC = sAct->getComponent<CLight>();
  if (!lightC.expired()) {
    if (ImGui::TreeNode("Light")) {
      DrawLightCmp(lightC, uniqueId);
      ImGui::TreePop();
    }
    ImGui::Separator();
  }
  WPtr<CRender> renderC = sAct->getComponent<CRender>();
  if (!renderC.expired()) {
    ImGui::Text("Render");
    ImGui::Separator();
  }
  WPtr<CSkeletalMesh> skMeshC = sAct->getComponent<CSkeletalMesh>();
  if (!skMeshC.expired()) {
    if (ImGui::TreeNode("Skeletal Mesh")) {
      DrawSkeletalMeshCmp(skMeshC, uniqueId);
      ImGui::TreePop();
    }
    ImGui::Separator();
  }
  WPtr<CStaticMesh> staticMeshC = sAct->getComponent<CStaticMesh>();
  if (!staticMeshC.expired()) {
    if (ImGui::TreeNode("Static Mesh")) {
      DrawStaticMeshCmp(staticMeshC, uniqueId);
      ImGui::TreePop();
    }
    ImGui::Separator();
  }


  ImGui::PushID(uniqueId++);
  if (ImGui::Button("AddComponent")) {
    g_addingCmp = true;
    g_actorAddingCmp = act;
  }
  ImGui::PopID();
}

bool
NewSceneWindow(bool& added, char* name)
{
  if (ImGui::Begin("New Scene")) {
    ImGui::InputText("Name", name, 255);

    if (ImGui::Button("Create")) {
      added = true;
      ImGui::End();
      return true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel")) {
      added = false;
      ImGui::End();
      return true;
    }
  }
  ImGui::End();
  return false;
}

bool
NewActorWindow(bool& added, char* name)
{
  if (ImGui::Begin("New Actor")) {
    ImGui::InputText("Name", name, 255);

    if (ImGui::Button("Create")) {
      added = true;
      ImGui::End();
      return true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel")) {
      added = false;
      ImGui::End();
      return true;
    }
  }
  ImGui::End();
  return false;
}

void 
MakeActorsTree(const Vector<SPtr<ActorNode>>& actors,
               WPtr<Actor>& ActorOnInspector,
               int32& n,
               int32& uniqueId)
{
  static int selected = -1;
  for (auto& act : actors) {
    auto sAct = act->actorValue.lock();
    ImGui::PushID(uniqueId++);
    if (ImGui::Selectable(sAct->getName().c_str(), selected == n)) {
      selected = n;
      ActorOnInspector = act->actorValue;
    }
    ImGui::PopID();

    Vector<SPtr<ActorNode>> childs = act->childrenNode;
    if (!childs.empty()) {
      if (ImGui::TreeNode("Children")) {
        MakeActorsTree(childs, ActorOnInspector, n, uniqueId);
        ImGui::TreePop();
      }
    }

    ++n;
  }
}

void
UIRender()
{
  auto& sceneManager = SceneManager::instance();
  auto& resourceMan = ResourceManager::instance();

  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();

  ImGui::NewFrame();

  static bool AddingScene = false;
  static bool LoadingScene = false;
  static bool AddingActor = false;
  static String AddingActorScene;

  static WPtr<Actor> ActorOnInspector;

  // Popup menus
  if (AddingScene) {
    bool added = false;
    static char name[255];
    if (NewSceneWindow(added, name)) {
      if (added) {
        sceneManager.addScene(name);
      }
      AddingScene = false;
    }
  }
  if (LoadingScene) {
    bool added = false;
    static char name[255];
    if (NewSceneWindow(added, name)) {
      if (added) {
        sceneManager.addScene(name);
      }
      AddingScene = false;
    }
  }
  if (AddingActor) {
    bool added = false;
    static char name[255];
    if (NewSceneWindow(added, name)) {
      if (added) {
        sceneManager.getScene(AddingActorScene).lock()->addActor(name);
      }
      AddingScene = false;
    }
  }


  int32 uniqueId = 0;

  if (ImGui::Begin("Scene graph", nullptr, ImGuiWindowFlags_MenuBar)) {
    if (ImGui::BeginMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("New Scene", nullptr, nullptr)) {
          AddingScene = true;
        }
        if (ImGui::MenuItem("Save Scene", nullptr, nullptr)) {
          sceneManager.saveActiveScenes();
        }
        if (ImGui::MenuItem("Load Scene", nullptr, nullptr)) {
          LoadingScene = true;
          WString fileName = loadFileDialog();

          if (!fileName.empty()) {
            sceneManager.loadScene(fileName);
          }
        }
        ImGui::EndMenu();
      }
    }
    ImGui::EndMenuBar();


    const Map<String, SPtr<Scene>>& scenes = 
    sceneManager.getAllScenes();

    for (auto& sc : scenes) {
      ImGui::PushID(uniqueId++);
      if (ImGui::TreeNode(sc.first.c_str())) {
        ImGui::PushID(uniqueId++);
        if (ImGui::Button("Add Actor")) {
          AddingActor = true;
          AddingActorScene = sc.first;
        }
        ImGui::PopID();
        ImGui::PushID(uniqueId++);
        bool active = sc.second->isActive();
        if (ImGui::Checkbox("Active", &active)) {
          sc.second->setActive(active);
        }
        ImGui::PopID();
        ImGui::PushID(uniqueId++);
        bool offActive = sc.second->isOffActive();
        if (ImGui::Checkbox("Off Active", &offActive)) {
          sc.second->setOffActive(offActive);
        }
        ImGui::PopID();

        Vector<SPtr<ActorNode>> actors = sc.second->getActorsTree();
        int32 n = 0;
        MakeActorsTree(actors, ActorOnInspector, n, uniqueId);
        ImGui::TreePop();
      }
      ImGui::PopID();
    }
  }
  ImGui::End();

  if (ImGui::Begin("Inspector")) {
    if (!ActorOnInspector.expired()) {
      showActorData(ActorOnInspector, uniqueId);
    }
  }
  ImGui::End();

  if (ImGui::Begin("Resources")) {
    if (ImGui::Button("Import Resource")) {
      WString fileName = loadFileDialog();

      if (!fileName.empty()) {
        resourceMan.importResourceFromFile(fileName);
      }
    }


    ImGui::Text("Animations");
    Map<String, SPtr<Animation>> anims =
    resourceMan.getAllAnimationResources();
    for (auto& a : anims) {
      ImGui::Text(("  " + a.first).c_str());
    }

    ImGui::Text("Models");
    Map<String, SPtr<StaticMesh>> models =
    resourceMan.getAllStaticMeshResources();
    for (auto& m : models) {
      ImGui::Text(("  " + m.first).c_str());
    }

    ImGui::Text("Skeletal Meshes");
    Map<String, SPtr<SkeletalMesh>> skMeshes =
    resourceMan.getAllSkeletalMeshResources();
    for (auto& skm : skMeshes) {
      ImGui::Text(("  " + skm.first).c_str());
    }

    ImGui::Text("Skeletons");
    Map<String, SPtr<Skeletal>> skeletons =
    resourceMan.getAllSkeletalResources();
    for (auto& sk : skeletons) {
      ImGui::Text(("  " + sk.first).c_str());
    }

    ImGui::Text("Textures");
    Map<String, SPtr<Texture>> texs =
    resourceMan.getAllTextureResources();
    for (auto& t : texs) {
      ImGui::Text(("  " + t.first).c_str());
    }
  }
  ImGui::End();

  if (g_addingCmp && !g_actorAddingCmp.expired()) {
    if (ImGui::Begin("Add Component")) {
      static int cmpIndex = 0;
      const char* componentNames[] = { "Animation",
                                       "Bounds",
                                       "Camera",
                                       "Light",
                                       "Render",
                                       "Skeletal Mesh",
                                       "Static Mesh" };
      ImGui::Combo("", &cmpIndex, componentNames, 7);

      if (ImGui::Button("Add Component")) {
        g_addingCmp = false;
        if (cmpIndex == 0) {
          g_actorAddingCmp.lock()->addComponent<CAnimation>();
        }
        if (cmpIndex == 1) {
          g_actorAddingCmp.lock()->addComponent<CBounds>();
        }
        if (cmpIndex == 2) {
          g_actorAddingCmp.lock()->addComponent<CCamera>();
        }
        if (cmpIndex == 3) {
          g_actorAddingCmp.lock()->addComponent<CLight>();
        }
        if (cmpIndex == 4) {
          g_actorAddingCmp.lock()->addComponent<CRender>();
        }
        if (cmpIndex == 5) {
          g_actorAddingCmp.lock()->addComponent<CSkeletalMesh>();
        }
        if (cmpIndex == 6) {
          g_actorAddingCmp.lock()->addComponent<CStaticMesh>();
        }
      }
    }
    ImGui::End();
  }


  if (eeEngineSDK::OmniverseManager::isStarted()) {
    static auto& omniverseMan = OmniverseManager::instance();
    if (ImGui::Begin("Omniverse Manager")) {
      if (ImGui::Button("Save stage")) {
        omniverseMan.saveStage();
      }
      if (ImGui::Button("Update stage")) {
        omniverseMan.getScenegraphFromStage(SceneManager::instance().getActiveScene());
      }
    }
    ImGui::End();
  }


  //ImGui::ShowDemoWindow();
  
  ImGui::Render();

  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}



int32
BaseAppTest1::run(void* /*callback*/)
{
  return BaseApp::run(WndProc);
}

void
BaseAppTest1::onInit()
{
  auto& graphicsApi = GraphicsApi::instance();
  auto& resourceManager = ResourceManager::instance();
  auto& sceneManager = SceneManager::instance();
  auto& memoryManager = MemoryManager::instance();

  if (FAILED(InitImgUI())) {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
  }

  Map<uint32, WPtr<Texture>> texturesMap;

  resourceManager.loadTextureFromFile(L"Textures/Defaults/DefaultDiffuse.png",
                                 eeEngineSDK::localizeString("DefaultDiffuse"));
  resourceManager.loadTextureFromFile(L"Textures/Defaults/DefaultNormalMap.jpg",
                               eeEngineSDK::localizeString("DefaultNormalMap"));
  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kDiffuse] =
  resourceManager.getResourceTexture("DefaultDiffuse");
  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kNormal] =
  resourceManager.getResourceTexture("DefaultNormalMap");
  resourceManager.loadMaterialFromTextures(texturesMap, "Default_mat");

  Mesh::initPrimitives();



  auto pScene = sceneManager.addScene("Main").lock();
  pScene->setActive(true);



  WPtr<Actor> pTempActor;



  resourceManager.loadStaticMeshFromMeshesArray({ Mesh::cube },
                                                "Cube",
                                                Math::sqrt(3),
                                                Vector3f{ 1.0f, 1.0f, 1.0f },
                                                Vector3f{ -1.0f, -1.0f, -1.f });
  resourceManager.loadStaticMeshFromMeshesArray({ Mesh::sphere },
                                                "Sphere",
                                                1.0f,
                                                Vector3f{ 1.0f, 1.0f, 1.0f },
                                                Vector3f{ -1.0f, -1.0f, -1.f });
  //resourceManager.loadStaticMeshFromMeshesArray({ Mesh::tetrahedron },
  //                                              "Tetrahedron",
  //                                              Vector3f{ 1.0f, -0.54f, -0.58f },
  //                                              Vector3f{ 1.0f, 1.09f, 1.15f },
  //                                              Vector3f{ -1.0f, -0.54f, -0.58f });
  
  
  
  CameraDesc camDesc;
  camDesc.projectionType = eeEngineSDK::eCAMERA_PROJECTION_TYPE::kPerspective;
  camDesc.fovAngleY = Math::kPI / 4.0f;
  camDesc.viewSize = Vector2f{ static_cast<float>(screenWidth),
                               static_cast<float>(screenHeight) };
  camDesc.nearZ = 0.01f;
  camDesc.farZ = 100.0f;
  
  pTempActor = pScene->addActor("Player");
  auto spTempActor = pTempActor.lock();
  spTempActor->getTransform().lock()->setPosition(Vector3f{ 0.0f, 3.0f, -6.0f });
  spTempActor->addComponent<CCamera>();
  spTempActor->getComponent<CCamera>().lock()->init(camDesc);
  spTempActor->getComponent<CCamera>().lock()->setMain(true);



  pTempActor = pScene->addActor("AtatchToActor");
  spTempActor = pTempActor.lock();
  pScene->setActorChild("Player", "AtatchToActor");
  spTempActor->getTransform().lock()->setPosition(Vector3f{ 0.0f, 0.0f, 30.0f });
  spTempActor->addComponent<CStaticMesh>();
  spTempActor->getComponent<CStaticMesh>().lock()->setStaticMesh
  (
    resourceManager.getResourceStaticMesh("Cube")
  );
  spTempActor->addComponent<CBounds>();
  spTempActor->addComponent<CRender>();



  pTempActor = pScene->addActor("Player2");
  spTempActor = pTempActor.lock();
  spTempActor->getTransform().lock()->setPosition(Vector3f{ 5.0f, 3.0f, -6.0f });
  spTempActor->getTransform().lock()->setScale(Vector3f{ 0.1f, 0.1f, 0.1f });
  spTempActor->addComponent<CCamera>();
  spTempActor->getComponent<CCamera>().lock()->init(camDesc);


  resourceManager.importResourceFromFile(L"Models/arcane_jinx_sketchfab.fbx",
    eeEngineSDK::IMPORT_FLAGS::kImportStaticMeshes);

  resourceManager.importResourceFromFile(L"Textures/Jinx/F_MED_UproarBraids_Body_baseColor.png");
  resourceManager.importResourceFromFile(L"Textures/Jinx/F_MED_UproarBraids_Body_normal.png");
  resourceManager.importResourceFromFile(L"Textures/Jinx/F_MED_UproarBraids_FaceAcc_baseColor.png");
  resourceManager.importResourceFromFile(L"Textures/Jinx/F_MED_UproarBraids_FaceAcc_normal.png");
  resourceManager.importResourceFromFile(L"Textures/Jinx/FACE_-_TEST.png");
  resourceManager.importResourceFromFile(L"Textures/Jinx/F_MED_UproarBraids_Head_normal.png");

  texturesMap.clear();

  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kDiffuse] =
    resourceManager.getResourceTexture("F_MED_UproarBraids_Body_baseColor_tex");
  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kNormal] =
    resourceManager.getResourceTexture("F_MED_UproarBraids_Body_normal_tex");
  resourceManager.loadMaterialFromTextures(texturesMap,
    "F_MED_UproarBraids_Body_baseColor_mat");

  texturesMap.clear();

  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kDiffuse] =
    resourceManager.getResourceTexture("F_MED_UproarBraids_FaceAcc_baseColor_tex");
  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kNormal] =
    resourceManager.getResourceTexture("F_MED_UproarBraids_FaceAcc_normal_tex");
  resourceManager.loadMaterialFromTextures(texturesMap,
    "F_MED_UproarBraids_FaceAcc_baseColor_mat");

  texturesMap.clear();

  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kDiffuse] =
    resourceManager.getResourceTexture("FACE_-_TEST_tex");
  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kNormal] =
    resourceManager.getResourceTexture("F_MED_UproarBraids_Head_normal_tex");
  resourceManager.loadMaterialFromTextures(texturesMap,
    "FACE_-_TEST_mat");

  pTempActor = pScene->addActor("Test");
  spTempActor = pTempActor.lock();
  spTempActor->getTransform().lock()->setScale(Vector3f{ 2.0f, 2.0f, 2.0f });
  spTempActor->getTransform().lock()->setPosition(Vector3f{ 3.0f, 0.0f, 0.0f });
  spTempActor->getTransform().lock()->setRotation(Quaternion(Vector3f{ 1.5707f, 0.0f, 0.0f }));
  spTempActor->addComponent<CStaticMesh>();
  spTempActor->getComponent<CStaticMesh>().lock()->setMobilityType(
    eeEngineSDK::eMOBILITY_TYPE::kStatic);
  spTempActor->getComponent<CStaticMesh>().lock()->setStaticMesh
  (
    resourceManager.getResourceStaticMesh("arcane_jinx_sketchfab_sm")
  );
  spTempActor->getComponent<CStaticMesh>().lock()->getStaticMesh().lock()->setTexture
  (
    resourceManager.getResourceMaterial
    (
      "F_MED_UproarBraids_Body_baseColor_mat"
    ),
    0
  );
  spTempActor->getComponent<CStaticMesh>().lock()->getStaticMesh().lock()->setTexture
  (
    resourceManager.getResourceMaterial
    (
      "F_MED_UproarBraids_FaceAcc_baseColor_mat"
    ),
    1
  );
  spTempActor->getComponent<CStaticMesh>().lock()->getStaticMesh().lock()->setTexture
  (
    resourceManager.getResourceMaterial
    (
      "FACE_-_TEST_mat"
    ),
    2
  );
  spTempActor->addComponent<CBounds>();
  spTempActor->addComponent<CRender>();


  resourceManager.importResourceFromFile(L"Models/boblampclean.md5mesh");

  resourceManager.importResourceFromFile(L"Textures/guard1_body.jpg");
  texturesMap.clear();
  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kDiffuse] =
    resourceManager.getResourceTexture("guard1_body_tex");
  resourceManager.loadMaterialFromTextures(texturesMap,
    "guard1_body_mat");
  resourceManager.importResourceFromFile(L"Textures/guard1_face.jpg");
  texturesMap.clear();
  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kDiffuse] =
    resourceManager.getResourceTexture("guard1_face_tex");
  resourceManager.loadMaterialFromTextures(texturesMap,
    "guard1_face_mat");
  resourceManager.importResourceFromFile(L"Textures/guard1_helmet.jpg");
  texturesMap.clear();
  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kDiffuse] =
    resourceManager.getResourceTexture("guard1_helmet_tex");
  resourceManager.loadMaterialFromTextures(texturesMap,
    "guard1_helmet_mat");
  resourceManager.importResourceFromFile(L"Textures/iron_grill.jpg");
  texturesMap.clear();
  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kDiffuse] =
    resourceManager.getResourceTexture("iron_grill_tex");
  resourceManager.loadMaterialFromTextures(texturesMap,
    "iron_grill_mat");
  resourceManager.importResourceFromFile(L"Textures/round_grill.jpg");
  texturesMap.clear();
  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kDiffuse] =
    resourceManager.getResourceTexture("round_grill_tex");
  resourceManager.loadMaterialFromTextures(texturesMap,
    "round_grill_mat");

  SPtr<Image> tempImg = memoryManager.newPtr<Image>();
  tempImg->loadFromFile(L"Textures/guard1_body.jpg");

  SPtr<Texture> tempTex = graphicsApi.createTexturePtr();
  tempTex->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
    Point2D{ tempImg->getWidth(), tempImg->getHeight() });

  tempTex->loadImages({ tempImg });


  pTempActor = pScene->addActor("AnimTest");
  spTempActor = pTempActor.lock();
  spTempActor->getTransform().lock()->setScale(Vector3f{ 0.03f, 0.03f, 0.03f });
  spTempActor->getTransform().lock()->setRotation(Quaternion(Vector3f{ Math::kPI * 0.5f,
                                                                       0.0f,
                                                                       0.0f }));
  spTempActor->addComponent<CSkeletalMesh>();
  spTempActor->getComponent<CSkeletalMesh>().lock()->setModel
  (
    resourceManager.getResourceSkeletalMesh("boblampclean_skm")
  );
  spTempActor->getComponent<CSkeletalMesh>().lock()->getModel().lock()->setTexture
  (
    resourceManager.getResourceMaterial("guard1_body_mat"),
    0
  );
  spTempActor->getComponent<CSkeletalMesh>().lock()->getModel().lock()->setTexture
  (
    resourceManager.getResourceMaterial("guard1_face_mat"),
    1
  );
  spTempActor->getComponent<CSkeletalMesh>().lock()->getModel().lock()->setTexture
  (
    resourceManager.getResourceMaterial("guard1_helmet_mat"),
    2
  );
  spTempActor->getComponent<CSkeletalMesh>().lock()->getModel().lock()->setTexture
  (
    resourceManager.getResourceMaterial("iron_grill_mat"),
    3
  );
  spTempActor->getComponent<CSkeletalMesh>().lock()->getModel().lock()->setTexture
  (
    resourceManager.getResourceMaterial("round_grill_mat"),
    4
  );
  spTempActor->getComponent<CSkeletalMesh>().lock()->getModel().lock()->setTexture
  (
    resourceManager.getResourceMaterial("guard1_body_mat"),
    5
  );
  spTempActor->addComponent<CAnimation>();
  spTempActor->getComponent<CAnimation>().lock()->setAnimation
  (
    resourceManager.getResourceAnimation("boblampclean_anim_")
  );
  spTempActor->addComponent<CBounds>();
  spTempActor->addComponent<CRender>();


  resourceManager.importResourceFromFile(L"Models/Scary_Clown_Walk.fbx");

  pTempActor = pScene->addActor("AnimTest2");
  spTempActor = pTempActor.lock();
  spTempActor->getTransform().lock()->setScale(Vector3f{ 0.01f, 0.01f, 0.01f });
  spTempActor->getTransform().lock()->setPosition(Vector3f{ -3.0f, 2.5f, 0.0f });
  spTempActor->addComponent<CSkeletalMesh>();
  spTempActor->getComponent<CSkeletalMesh>().lock()->setModel
  (
    resourceManager.getResourceSkeletalMesh("Scary_Clown_Walk_skm")
  );
  spTempActor->addComponent<CAnimation>();
  spTempActor->getComponent<CAnimation>().lock()->setAnimation
  (
    resourceManager.getResourceAnimation("Scary_Clown_Walk_anim_mixamo.com")
  );
  spTempActor->addComponent<CBounds>();
  spTempActor->addComponent<CRender>();


  resourceManager.importResourceFromFile(L"Models/simpleCube.fbx",
    eeEngineSDK::IMPORT_FLAGS::kImportStaticMeshes);

  pTempActor = pScene->addActor("DownWall");
  spTempActor = pTempActor.lock();
  spTempActor->getTransform().lock()->setScale(Vector3f{ 10.0f, 0.5f, 10.0f });
  spTempActor->getTransform().lock()->setPosition(Vector3f{ 0.0f, -1.0f, 0.0f });
  spTempActor->addComponent<CStaticMesh>();
  spTempActor->getComponent<CStaticMesh>().lock()->setMobilityType(
    eeEngineSDK::eMOBILITY_TYPE::kStatic);
  spTempActor->getComponent<CStaticMesh>().lock()->setStaticMesh
  (
    resourceManager.getResourceStaticMesh("simpleCube_sm")
  );
  spTempActor->addComponent<CBounds>();
  spTempActor->addComponent<CRender>();



  pTempActor = pScene->addActor("DirLight");
  spTempActor = pTempActor.lock();
  spTempActor->addComponent<CLight>();
  spTempActor->getComponent<CLight>().lock()->setColor(Color{ 1.0f, 0.0f, 0.0f, 1.0f });
  spTempActor->getTransform().lock()->setRotation(
    Quaternion::createFromAxisAngle(Vector3f(0.0f, 1.0f, 0.0f), -Math::kPI * 0.5f));
  
  pTempActor = pScene->addActor("DirLight2");
  spTempActor = pTempActor.lock();
  spTempActor->addComponent<CLight>();
  spTempActor->getComponent<CLight>().lock()->setColor(Color{ 0.0f, 1.0f, 0.0f, 1.0f });
  spTempActor->getTransform().lock()->setRotation(
    Quaternion::createFromAxisAngle(Vector3f(0.0f, 1.0f, 0.0f), Math::kPI * 0.5f));
  
  pTempActor = pScene->addActor("PointLight1");
  spTempActor = pTempActor.lock();
  spTempActor->getTransform().lock()->setScale(Vector3f{ 0.2f, 0.2f, 0.2f });
  spTempActor->addComponent<CLight>();
  spTempActor->getComponent<CLight>().lock()->setLightType(eeEngineSDK::eLIGHT_TYPE::kPoint);
  spTempActor->getComponent<CLight>().lock()->setColor(Color{ 0.0f, 0.0f, 1.0f, 1.0f });
  spTempActor->getComponent<CLight>().lock()->setIntensity(1.0f);
  spTempActor->addComponent<CStaticMesh>();
  spTempActor->getComponent<CStaticMesh>().lock()->setStaticMesh
  (
    resourceManager.getResourceStaticMesh("Sphere")
  );
  spTempActor->addComponent<CBounds>();
  spTempActor->addComponent<CRender>();
  
  
  sceneManager.partitionAllScenes();



  if (OmniverseManager::isStarted()) {
    auto& omniverseMan = OmniverseManager::instance();
    String localPath = omniverseMan.getUserLocalPath();
    omniverseMan.createStage(localPath + "/Main.usd");
    omniverseMan.setScenegraphOnStage(pScene);
    //omniverseMan.openStage(localPath + "/Main.usd");
    //omniverseMan.getScenegraphFromStage(pScene);
  }



  auto& audioMan = AudioManager::instance();
  audioMan.createSound("Sounds/DeactivateLeverSound.wav", testSound);
  audioMan.createAudio("Sounds/LITTLE MISS PERFECT.wav", testAudio);
  //audioMan.playAudio(testAudio);
}

void
BaseAppTest1::onUpdate(float deltaTime)
{
  auto& inputMan = InputManager::instance();
  auto& sceneManager = SceneManager::instance();
  auto& audioMan = AudioManager::instance();


  auto scene = sceneManager.getScene("Main").lock();
  EE_NO_EXIST_RETURN(scene);

  static String activePlayerName = "Player";
  if (inputMan.getDevice(0).lock()->getButtonDown(eeEngineSDK::KEYBOARD_INPUT::kTab)) {
    if (!scene->getActor(activePlayerName).expired()
     && !scene->getActor(activePlayerName).lock()->getComponent<CCamera>().expired()) {
      scene->getActor(activePlayerName).lock()->getComponent<CCamera>().lock()->setMain(false);
    }

    if (activePlayerName == "Player") {
      activePlayerName = "Player2";
    }
    else {
      activePlayerName = "Player";
    }

    if (!scene->getActor(activePlayerName).expired()
     && !scene->getActor(activePlayerName).lock()->getComponent<CCamera>().expired()) {
      scene->getActor(activePlayerName).lock()->getComponent<CCamera>().lock()->setMain(true);
    }
  }



  auto actor = scene->getActor("Test").lock();



  actor = scene->getActor(activePlayerName).lock();

  SPtr<CTransform> trans = nullptr;
  if (actor) {
    trans = actor->getTransform().lock();
  }

  Quaternion rot;
  if (trans) {
    rot = trans->getRotation();

    Vector3f cameraMovement = Vector3f{ 0.0f, 0.0f, 0.0f };
    auto keyboardDevice = inputMan.getDevice(0).lock();
    if (keyboardDevice->getButton(eeEngineSDK::eBUTTONS_KEYS::kKeyboardButtonW)) {
      cameraMovement += rot.getFrontVector();
    }
    if (keyboardDevice->getButton(eeEngineSDK::eBUTTONS_KEYS::kKeyboardButtonS)) {
      cameraMovement -= rot.getFrontVector();
    }
    if (keyboardDevice->getButton(eeEngineSDK::eBUTTONS_KEYS::kKeyboardButtonA)) {
      cameraMovement -= rot.getRightVector();
    }
    if (keyboardDevice->getButton(eeEngineSDK::eBUTTONS_KEYS::kKeyboardButtonD)) {
      cameraMovement += rot.getRightVector();
    }
    if (keyboardDevice->getButton(eeEngineSDK::eBUTTONS_KEYS::kKeyboardButtonQ)) {
      cameraMovement += rot.getUpVector();
    }
    if (keyboardDevice->getButton(eeEngineSDK::eBUTTONS_KEYS::kKeyboardButtonE)) {
      cameraMovement -= rot.getUpVector();
    }
    trans->setPosition(trans->getPosition() + cameraMovement * deltaTime * 10.0f);

    if (inputMan.getDevice(0).lock()->getButtonUp(eeEngineSDK::eBUTTONS_KEYS::kKeyboardButtonEnter)) {
      audioMan.playSound(testSound);
    }

    auto mouseDevice = inputMan.getDevice(1).lock();
    if (mouseDevice->getButton(eeEngineSDK::eBUTTONS_KEYS::kMouseButtonRight)) {
      float mouseMoveX =
      mouseDevice->getAxis(eeEngineSDK::eBUTTONS_KEYS::kMouseAxisX);
      float mouseMoveY =
      mouseDevice->getAxis(eeEngineSDK::eBUTTONS_KEYS::kMouseAxisY);

      Quaternion rot2 =
      Quaternion::createFromAxisAngle(rot.getUpVector(),
                                      mouseMoveX
                                    * deltaTime
                                    * 200.0f);
      rot2 =
      Quaternion::createFromAxisAngle(rot.getRightVector(),
                                      mouseMoveY
                                    * deltaTime
                                    * 200.0f)
                                    * rot2;
      trans->setRotation(rot2 * rot);
    }
  }


  sceneManager.update();
}

void
BaseAppTest1::onRender()
{
  auto& graphicsApi = GraphicsApi::instance();

  auto mainWin = graphicsApi.getMainWindow().lock();
  graphicsApi.setRenderTargets({ mainWin->getRenderTarget() },
                               mainWin->getDepthStencil());

  UIRender();

  graphicsApi.unsetRenderTargets();
}

void
BaseAppTest1::onDestroy()
{
}
