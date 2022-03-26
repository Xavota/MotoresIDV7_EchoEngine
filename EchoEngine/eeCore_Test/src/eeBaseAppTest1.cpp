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

#include <eeDX11GraphicsApi.h>
#include <eeCoreConfiguration.h>

#include <eeMemoryManager.h>
#include <eeResourceManager.h>
#include <eeSceneManager.h>
#include <eeLogger.h>
#include <eeMath.h>
#include <eeInput.h>
#include <eeTime.h>

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

#include <eeActor.h>
#include <eeCTransform.h>
#include <eeCStaticMesh.h>
#include <eeCRender.h>
#include <eeCCamera.h>
#include <eeCSkeletalMesh.h>
#include <eeCAnimation.h>
#include <eeCBounds.h>

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
using eeEngineSDK::Quaternion;
using eeEngineSDK::SimplexVertex;
using eeEngineSDK::SimpleVertex;
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
using eeEngineSDK::Math;
using eeEngineSDK::VertexShader;
using eeEngineSDK::PixelShader;
using eeEngineSDK::Byte;
using eeEngineSDK::Texture;
using eeEngineSDK::Component;

using eeEngineSDK::CTransform;
using eeEngineSDK::CStaticMesh;
using eeEngineSDK::CRender;
using eeEngineSDK::CSkeletalMesh;
using eeEngineSDK::CAnimation;
using eeEngineSDK::CBounds;

using eeEngineSDK::Input;
using eeEngineSDK::CameraDesc;
using eeEngineSDK::String;
using eeEngineSDK::CAMERA_PROJECTION_TYPE;

using eeEngineSDK::MemoryManager;
using eeEngineSDK::Time;


using eeEngineSDK::ViewportDesc;

using eeEngineSDK::Window;



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
      GetClientRect(reinterpret_cast<HWND>(GraphicsApi::instance().getMainWindow()->getWindowPtr()), &rc);
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

  return 0;
}

String
loadFileDialog()
{
  // common dialog box structure, setting all fields to 0 is important
  OPENFILENAME ofn = { 0 };
  TCHAR szFile[260] = { 0 };

  // Initialize remaining fields of OPENFILENAME structure
  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = nullptr;
  ofn.lpstrFile = szFile;
  ofn.nMaxFile = sizeof(szFile);
  ofn.lpstrFilter = ("All\0*.*");
  ofn.nFilterIndex = 1;
  ofn.lpstrFileTitle = nullptr;
  ofn.nMaxFileTitle = 0;
  ofn.lpstrInitialDir = nullptr;
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

  if (GetOpenFileName(&ofn) == TRUE) {
    return szFile;
  }

  return "";
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
  ImGui_ImplWin32_Init(graphicsApi.getMainWindow()->getWindowPtr());

  return S_OK;
}

void
DrawTransformCmp(SPtr<CTransform> trans, int32& uniqueId)
{
  ImGui::PushID(uniqueId++);
  Vector3f actPos = trans->getPosition();
  float pos[3] = { actPos.x, actPos.y, actPos.z };
  if (ImGui::DragFloat3("Position", pos, 0.01f, -1000.0f, 1000.0f)) {
    trans->setPosition(Vector3f(pos[0], pos[1], pos[2]));
  }
  ImGui::PopID();
  ImGui::PushID(uniqueId++);
  Vector3f actRot = trans->getRotation().getEuclidean();
  float rot[3] = { actRot.x, actRot.y, actRot.z };
  if (ImGui::DragFloat3("Rotation", rot, 0.01f, -1000.0f, 1000.0f)) {
    trans->setRotation(Quaternion(Vector3f(rot[0], rot[1], rot[2])));
  }
  ImGui::PopID();
  ImGui::PushID(uniqueId++);
  Vector3f actScale = trans->getScale();
  float scale[3] = { actScale.x, actScale.y, actScale.z };
  if (ImGui::DragFloat3("Scale", scale, 0.01f, -1000.0f, 1000.0f)) {
    trans->setScale(Vector3f(scale[0], scale[1], scale[2]));
  }
  ImGui::PopID();
}

void
DrawAnimationCmp(SPtr<CAnimation> anim, int32& uniqueId)
{
  ImGui::PushID(uniqueId++);
  String animName = anim->getAnimation()->getName();
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
    anim->setAnimation(ResourceManager::instance().getResourceAnimation(names[animIndex]));
  }
  ImGui::PopID();
}

void
DrawCameraCmp(SPtr<CCamera> cam, int32& uniqueId)
{
  ImGui::PushID(uniqueId++);
  CAMERA_PROJECTION_TYPE pt = cam->getProjectionType();
  auto projIndex = static_cast<int>(pt);
  const char* projTypes[] = { "Orthographic", "Perspective" };
  if (ImGui::Combo("Projection Types", &projIndex, projTypes, 2)) {
    cam->setProjectionType(static_cast<CAMERA_PROJECTION_TYPE>(projIndex));
  }
  ImGui::PopID();
  ImGui::PushID(uniqueId++);
  float fov = cam->getFovAngle() * Math::k180_OVER_PI;
  if (ImGui::DragFloat("FOV", &fov, 0.1f, 10.0f, 89.0f)) {
    cam->setFovAngle(fov * Math::kPI_OVER_180);
  }
  ImGui::PopID();
  ImGui::PushID(uniqueId++);
  float nearDist = cam->getNearPlane();
  if (ImGui::DragFloat("Near", &nearDist, 0.01f, .01f, 200.0f)) {
    cam->setNearPlane(nearDist);
  }
  ImGui::PopID();
  ImGui::PushID(uniqueId++);
  float farDist = cam->getFarPlane();
  if (ImGui::DragFloat("Far", &farDist, 0.01f, .01f, 200.0f)) {
    cam->setFarPlane(farDist);
  }
  ImGui::PopID();
  ImGui::PushID(uniqueId++);
  bool isMain = cam->isMain();
  if (ImGui::Checkbox("Main Camera", &isMain)) {
    cam->setMain(isMain);
  }
  ImGui::PopID();
}

void
DrawStaticMeshCmp(SPtr<CStaticMesh> staticMesh, int32& uniqueId)
{
  String staticMeshName = staticMesh->getStaticMesh()->getName();
  Map<String, SPtr<StaticMesh>> staticMeshes =
  ResourceManager::instance().getAllStaticMeshResources();
  int staticMeshIndex = 0;
  int tempIndex = 0;
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
    staticMesh->setStaticMesh(
    ResourceManager::instance().getResourceStaticMesh(names[staticMeshIndex]));
  }
  ImGui::PopID();
}

void
DrawSkeletalMeshCmp(SPtr<CSkeletalMesh> skMesh, int32& uniqueId)
{
  ImGui::PushID(uniqueId++);
  String modelName = skMesh->getModel()->getName();
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
    skMesh->setModel(ResourceManager::instance().getResourceSkeletalMesh(names[modelIndex]));
  }
  ImGui::PopID();
}

SPtr<Actor> g_actorAddingCmp;
bool g_addingCmp = false;
void
showActorData(SPtr<Actor> act, int32& uniqueId)
{
  ImGui::PushID(uniqueId++);
  bool actActive = act->isActive();
  if (ImGui::Checkbox("Active", &actActive)) {
    act->setActive(actActive);
  }
  ImGui::PopID();


  ImGui::Separator();
  ImGui::Text("Transform");
  DrawTransformCmp(act->getTransform(), uniqueId);
  ImGui::Separator();
  SPtr<CAnimation> animC = act->getComponent<CAnimation>();
  if (animC) {
    if (ImGui::TreeNode("Animation")) {
      DrawAnimationCmp(animC, uniqueId);
      ImGui::TreePop();
    }
    ImGui::Separator();
  }
  SPtr<CBounds> boundsC = act->getComponent<CBounds>();
  if (boundsC) {
    ImGui::Text("Bounds");
    ImGui::Separator();
  }
  SPtr<CCamera> camC = act->getComponent<CCamera>();
  if (camC) {
    if (ImGui::TreeNode("Camera")) {
      DrawCameraCmp(camC, uniqueId);
      ImGui::TreePop();
    }
    ImGui::Separator();
  }
  SPtr<CRender> renderC = act->getComponent<CRender>();
  if (renderC) {
    ImGui::Text("Render");
    ImGui::Separator();
  }
  SPtr<CSkeletalMesh> skMeshC = act->getComponent<CSkeletalMesh>();
  if (skMeshC) {
    if (ImGui::TreeNode("Skeletal Mesh")) {
      DrawSkeletalMeshCmp(skMeshC, uniqueId);
      ImGui::TreePop();
    }
    ImGui::Separator();
  }
  SPtr<CStaticMesh> staticMeshC = act->getComponent<CStaticMesh>();
  if (staticMeshC) {
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
MakeActorsTree(Vector<SPtr<Actor>> actors,
               SPtr<Actor>& ActorOnInspector,
               int32& n,
               int32& uniqueId)
{
  static int selected = -1;
  for (auto& act : actors) {
    ImGui::PushID(uniqueId++);
    if (ImGui::Selectable(act->getName().c_str(), selected == n)) {
      selected = n;
      ActorOnInspector = act;
    }
    ImGui::PopID();

    Vector<SPtr<Actor>> childs = act->getChildren();
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
  static bool AddingActor = false;
  static String AddingActorScene;

  static SPtr<Actor> ActorOnInspector = nullptr;

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
  if (AddingActor) {
    bool added = false;
    static char name[255];
    if (NewSceneWindow(added, name)) {
      if (added) {
        sceneManager.getScene(AddingActorScene)->addActor(name);
      }
      AddingScene = false;
    }
  }


  int32 uniqueId = 0;

  if (ImGui::Begin("Scene graph", nullptr, ImGuiWindowFlags_MenuBar)) {
    if (ImGui::BeginMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Add Scene", nullptr, nullptr)) {
          AddingScene = true;
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

        Vector<SPtr<Actor>> actors;
        sc.second->getAllActorsVector(actors);
        int32 n = 0;
        MakeActorsTree(actors, ActorOnInspector, n, uniqueId);
        ImGui::TreePop();
      }
      ImGui::PopID();
    }
  }
  ImGui::End();

  if (ImGui::Begin("Inspector")) {
    if (ActorOnInspector) {
      showActorData(ActorOnInspector, uniqueId);
    }
  }
  ImGui::End();

  if (ImGui::Begin("Resources")) {
    if (ImGui::Button("Import Resource")) {
      String fileName = loadFileDialog();

      if (!fileName.empty()) {
        resourceMan.importResourceFromFile(fileName);
      }
    }


    ImGui::Text("Animations");
    Map<String, SPtr<Animation>> anims = resourceMan.getAllAnimationResources();
    for (auto& a : anims) {
      ImGui::Text(("  " + a.first).c_str());
    }

    ImGui::Text("Models");
    Map<String, SPtr<StaticMesh>> models = resourceMan.getAllStaticMeshResources();
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
    Map<String, SPtr<Texture>> texs = resourceMan.getAllTextureResources();
    for (auto& t : texs) {
      ImGui::Text(("  " + t.first).c_str());
    }
  }
  ImGui::End();

  if (g_addingCmp && g_actorAddingCmp) {
    if (ImGui::Begin("Add Component")) {
      static int cmpIndex = 0;
      const char* componentNames[] = { "Animation", "Camera", "Model", "Render", "Skeletal Mesh" };
      if (ImGui::Combo("", &cmpIndex, componentNames, 1)) {

      }
    }
    ImGui::End();
  }

  ImGui::ShowDemoWindow();
  
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

  Map<uint32, SPtr<Texture>> texturesMap;

  resourceManager.loadTextureFromFile("Textures/Defaults/DefaultDiffuse.png",
                                      "DefaultDiffuse");
  resourceManager.loadTextureFromFile("Textures/Defaults/DefaultNormalMap.jpg",
                                      "DefaultNormalMap");
  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kDiffuse] =
  resourceManager.getResourceTexture("DefaultDiffuse");
  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kNormal] =
  resourceManager.getResourceTexture("DefaultNormalMap");
  resourceManager.loadMaterialFromTextures(texturesMap, "Default_mat");

  StaticMesh::initPrimitives();



  graphicsApi.setPrimitiveTopology(eeEngineSDK::ePRIMITIVE_TOPOLOGY::E::kTrianglelist);
  


  SPtr<Scene> pScene = sceneManager.addScene("Main");
  pScene->setActive(true);



  SPtr<Actor> pTempActor;


  
  resourceManager.loadStaticMeshFromMeshesArray({ Mesh::cube },
                                                "Cube",
                                                Vector3f{ 1.0f, 1.0f, 1.0f },
                                                Vector3f{ 1.0f, 1.0f, 1.0f },
                                                Vector3f{ -1.0f, -1.0f, -1.f });
  resourceManager.loadStaticMeshFromMeshesArray({ Mesh::tetrahedron },
                                                "Tetrahedron",
                                                Vector3f{ 1.0f, -0.54f, -0.58f },
                                                Vector3f{ 1.0f, 1.09f, 1.15f },
                                                Vector3f{ -1.0f, -0.54f, -0.58f });



  CameraDesc camDesc;
  camDesc.projectionType = CAMERA_PROJECTION_TYPE::kPerspective;
  camDesc.fovAngleY = Math::kPI / 4.0f;
  camDesc.viewSize = Vector2f{ static_cast<float>(screenWidth),
                               static_cast<float>(screenHeight) };
  camDesc.nearZ = 0.01f;
  camDesc.farZ = 100.0f;

  pTempActor = pScene->addActor("Player");
  pTempActor->getTransform()->setPosition(Vector3f{ 0.0f, 3.0f, -6.0f });
  //actor->getTransform()->setScale({ 0.1f, 0.1f, 0.1f });
  pTempActor->addComponent<CCamera>();
  pTempActor->getComponent<CCamera>()->init(camDesc);
  pTempActor->getComponent<CCamera>()->setMain(true);
  pTempActor->addComponent<CStaticMesh>();
  pTempActor->getComponent<CStaticMesh>()->setStaticMesh
  (
    resourceManager.getResourceStaticMesh("Cube")
  );
  pTempActor->addComponent<CBounds>();
  pTempActor->addComponent<CRender>();



  pTempActor = pScene->addActor("AtatchToActor");
  //pTempActor->attachTo(pScene->getActor("Player"));
  pScene->setActorChild("Player", "AtatchToActor");
  pTempActor->getTransform()->setPosition(Vector3f{ 0.0f, 0.0f, 30.0f });
  pTempActor->addComponent<CStaticMesh>();
  pTempActor->getComponent<CStaticMesh>()->setStaticMesh
  (
    resourceManager.getResourceStaticMesh("Tetrahedron")
  );
  pTempActor->addComponent<CBounds>();
  pTempActor->addComponent<CRender>();



  pTempActor = pScene->addActor("Player2");
  pTempActor->getTransform()->setPosition(Vector3f{ 5.0f, 3.0f, -6.0f });
  pTempActor->getTransform()->setScale(Vector3f{ 0.1f, 0.1f, 0.1f });
  pTempActor->addComponent<CCamera>();
  pTempActor->getComponent<CCamera>()->init(camDesc);
  pTempActor->addComponent<CStaticMesh>();
  pTempActor->getComponent<CStaticMesh>()->setStaticMesh
  (
    StaticMesh::cube
  );
  pTempActor->addComponent<CBounds>();
  pTempActor->addComponent<CRender>();


  resourceManager.importResourceFromFile("Models/arcane_jinx_sketchfab.fbx",
  eeEngineSDK::IMPORT_FLAGS::kImportStaticMeshes);

  resourceManager.importResourceFromFile("Textures/Jinx/F_MED_UproarBraids_Body_baseColor.png");
  resourceManager.importResourceFromFile("Textures/Jinx/F_MED_UproarBraids_Body_normal.png");
  resourceManager.importResourceFromFile("Textures/Jinx/F_MED_UproarBraids_FaceAcc_baseColor.png");
  resourceManager.importResourceFromFile("Textures/Jinx/F_MED_UproarBraids_FaceAcc_normal.png");
  resourceManager.importResourceFromFile("Textures/Jinx/FACE_-_TEST.png");
  resourceManager.importResourceFromFile("Textures/Jinx/F_MED_UproarBraids_Head_normal.png");

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
  pTempActor->getTransform()->setScale(Vector3f{ 2.0f, 2.0f, 2.0f });
  pTempActor->getTransform()->setPosition(Vector3f{ 3.0f, 0.0f, 0.0f });
  pTempActor->getTransform()->setRotation(Quaternion(Vector3f{1.5707f, 0.0f, 0.0f} ));
  pTempActor->addComponent<CStaticMesh>();
  pTempActor->getComponent<CStaticMesh>()->setStaticMesh
  (
    resourceManager.getResourceStaticMesh("arcane_jinx_sketchfab_sm")
  );
  pTempActor->getComponent<CStaticMesh>()->getStaticMesh()->setTexture
  (
    resourceManager.getResourceMaterial
    (
      "F_MED_UproarBraids_Body_baseColor_mat"
    ),
    0
  );
  pTempActor->getComponent<CStaticMesh>()->getStaticMesh()->setTexture
  (
    resourceManager.getResourceMaterial
    (
      "F_MED_UproarBraids_FaceAcc_baseColor_mat"
    ),
    1
  );
  pTempActor->getComponent<CStaticMesh>()->getStaticMesh()->setTexture
  (
    resourceManager.getResourceMaterial
    (
      "FACE_-_TEST_mat"
    ),
    2
  );
  pTempActor->addComponent<CBounds>();
  pTempActor->addComponent<CRender>();


  resourceManager.importResourceFromFile("Models/boblampclean.md5mesh");

  resourceManager.importResourceFromFile("Textures/guard1_body.jpg");
  texturesMap.clear();
  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kDiffuse] =
  resourceManager.getResourceTexture("guard1_body_tex");
  resourceManager.loadMaterialFromTextures(texturesMap,
                                           "guard1_body_mat");
  resourceManager.importResourceFromFile("Textures/guard1_face.jpg");
  texturesMap.clear();
  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kDiffuse] =
  resourceManager.getResourceTexture("guard1_face_tex");
  resourceManager.loadMaterialFromTextures(texturesMap,
                                           "guard1_face_mat");
  resourceManager.importResourceFromFile("Textures/guard1_helmet.jpg");
  texturesMap.clear();
  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kDiffuse] =
  resourceManager.getResourceTexture("guard1_helmet_tex");
  resourceManager.loadMaterialFromTextures(texturesMap,
                                           "guard1_helmet_mat");
  resourceManager.importResourceFromFile("Textures/iron_grill.jpg");
  texturesMap.clear();
  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kDiffuse] =
  resourceManager.getResourceTexture("iron_grill_tex");
  resourceManager.loadMaterialFromTextures(texturesMap,
                                           "iron_grill_mat");
  resourceManager.importResourceFromFile("Textures/round_grill.jpg");
  texturesMap.clear();
  texturesMap[eeEngineSDK::TEXTURE_TYPE_INDEX::kDiffuse] =
  resourceManager.getResourceTexture("round_grill_tex");
  resourceManager.loadMaterialFromTextures(texturesMap,
                                           "round_grill_mat");

  SPtr<Image> tempImg = memoryManager.newPtr<Image>();
  tempImg->loadFromFile("Textures/guard1_body.jpg");

  SPtr<Texture> tempTex = graphicsApi.createTexturePtr();
  tempTex->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                    Point2D{ tempImg->getWidth(), tempImg->getHeight() });

  tempTex->loadImages({ tempImg });


  pTempActor = pScene->addActor("AnimTest");
  pTempActor->getTransform()->setScale(Vector3f{ 0.03f, 0.03f, 0.03f });
  pTempActor->getTransform()->setRotation(Quaternion(Vector3f{ Math::kPI * 0.5f,
                                                                           0.0f,
                                                                           0.0f }));
  pTempActor->addComponent<CSkeletalMesh>();
  pTempActor->getComponent<CSkeletalMesh>()->setModel
  (
    resourceManager.getResourceSkeletalMesh("boblampclean_skm")
  );
  pTempActor->getComponent<CSkeletalMesh>()->getModel()->setTexture
  (
    resourceManager.getResourceMaterial("guard1_body_mat"),
    0
  );
  pTempActor->getComponent<CSkeletalMesh>()->getModel()->setTexture
  (
    resourceManager.getResourceMaterial("guard1_face_mat"),
    1
  );
  pTempActor->getComponent<CSkeletalMesh>()->getModel()->setTexture
  (
    resourceManager.getResourceMaterial("guard1_helmet_mat"),
    2
  );
  pTempActor->getComponent<CSkeletalMesh>()->getModel()->setTexture
  (
    resourceManager.getResourceMaterial("iron_grill_mat"),
    3
  );
  pTempActor->getComponent<CSkeletalMesh>()->getModel()->setTexture
  (
    resourceManager.getResourceMaterial("round_grill_mat"),
    4
  );
  pTempActor->getComponent<CSkeletalMesh>()->getModel()->setTexture
  (
    resourceManager.getResourceMaterial("guard1_body_mat"),
    5
  );
  pTempActor->addComponent<CAnimation>();
  pTempActor->getComponent<CAnimation>()->setAnimation
  (
    resourceManager.getResourceAnimation("boblampclean_anim_")
  );
  pTempActor->addComponent<CBounds>();
  pTempActor->addComponent<CRender>();


  resourceManager.importResourceFromFile("Models/Scary_Clown_Walk.fbx");
  
  pTempActor = pScene->addActor("AnimTest2");
  pTempActor->getTransform()->setScale(Vector3f{ 0.01f, 0.01f, 0.01f });
  pTempActor->getTransform()->setPosition(Vector3f{ -3.0f, 2.5f, 0.0f });
  pTempActor->addComponent<CSkeletalMesh>();
  pTempActor->getComponent<CSkeletalMesh>()->setModel
  (
    resourceManager.getResourceSkeletalMesh("Scary_Clown_Walk_skm")
  );
  pTempActor->addComponent<CAnimation>();
  pTempActor->getComponent<CAnimation>()->setAnimation
  (
    resourceManager.getResourceAnimation("Scary_Clown_Walk_anim_mixamo.com")
  );
  pTempActor->addComponent<CBounds>();
  pTempActor->addComponent<CRender>();
}

void
BaseAppTest1::onUpdate(float deltaTime)
{
  auto& inputMan = Input::instance();
  auto& sceneManager = SceneManager::instance();


  SPtr<Scene> scene = sceneManager.getScene("Main");
  EE_NO_EXIST_RETURN(scene);

  static String activePlayerName = "Player";
  if (inputMan.getKeyboardInputPressed(eeEngineSDK::KEYBOARD_INPUT::kTab)) {
    if (scene->getActor(activePlayerName)
     && scene->getActor(activePlayerName)->getComponent<CCamera>()) {
      scene->getActor(activePlayerName)->getComponent<CCamera>()->setMain(false);
    }

    if (activePlayerName == "Player") {
      activePlayerName = "Player2";
    }
    else {
      activePlayerName = "Player";
    }

    if (scene->getActor(activePlayerName)
     && scene->getActor(activePlayerName)->getComponent<CCamera>()) {
      scene->getActor(activePlayerName)->getComponent<CCamera>()->setMain(true);
    }
  }




  SPtr<Actor> actor = scene->getActor("Test");



  actor = scene->getActor(activePlayerName);

  SPtr<CTransform> trans = nullptr;
  if (actor) {
    trans = actor->getTransform();
  }

  Quaternion rot;
  if (trans) {
    rot = trans->getRotation();

    Vector3f cameraMovement = Vector3f{ 0.0f, 0.0f, 0.0f };
    if (inputMan.getKeyboardInputIsPressed(eeEngineSDK::KEYBOARD_INPUT::kW)) {
      cameraMovement += rot.getFrontVector();
    }
    if (inputMan.getKeyboardInputIsPressed(eeEngineSDK::KEYBOARD_INPUT::kS)) {
      cameraMovement -= rot.getFrontVector();
    }
    if (inputMan.getKeyboardInputIsPressed(eeEngineSDK::KEYBOARD_INPUT::kA)) {
      cameraMovement -= rot.getRightVector();
    }
    if (inputMan.getKeyboardInputIsPressed(eeEngineSDK::KEYBOARD_INPUT::kD)) {
      cameraMovement += rot.getRightVector();
    }
    if (inputMan.getKeyboardInputIsPressed(eeEngineSDK::KEYBOARD_INPUT::kQ)) {
      cameraMovement += rot.getUpVector();
    }
    if (inputMan.getKeyboardInputIsPressed(eeEngineSDK::KEYBOARD_INPUT::kE)) {
      cameraMovement -= rot.getUpVector();
    }
    trans->setPosition(trans->getPosition() +
      cameraMovement * deltaTime * 10.0f);

    if (inputMan.getMouseClickInputIsPressed(
                              eeEngineSDK::MOUSE_INPUT::kRightClick)) {
      //auto rot2 = Quaternion(rot.getEuclidean() +
      //                       Vector3f
      //                       (
      //                         inputMan.getMouseMovement().y *
      //                         timeManager.getDeltaTime() *
      //                         1.0f,
      //                         inputMan.getMouseMovement().x *
      //                         timeManager.getDeltaTime() *
      //                         1.0f,
      //                         0.0f
      //                       ));
      //trans->setRotation(rot2);
      Vector2i mouseMove = inputMan.getMouseMovement();
      Quaternion rot2 =
      Quaternion::createFromAxisAngle(rot.getUpVector(),
                                      mouseMove.x
                                    * deltaTime
                                    * 1.0f);
      rot2 =
      Quaternion::createFromAxisAngle(rot.getRightVector(),
                                      mouseMove.y
                                    * deltaTime
                                    * 1.0f)
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

  SPtr<Window> mainWin = graphicsApi.getMainWindow();
  graphicsApi.setRenderTargets({ mainWin->getRenderTarget() },
                               mainWin->getDepthStencil());

  UIRender();

  graphicsApi.unsetRenderTargets();
}

void
BaseAppTest1::onDestroy()
{
}
