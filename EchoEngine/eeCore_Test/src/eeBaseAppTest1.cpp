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

#include <eeVertexShader.h>
#include <eePixelShader.h>
#include <eeRenderTarget.h>
#include <eeDepthStencil.h>
#include <eeRasterizerState.h>

#include <eeObject.h>
#include <eeAnimation.h>
#include <eeSkeletalMesh.h>
#include <eeModel.h>
#include <eeColor.h>

#include <eeActor.h>
#include <eeCTransform.h>
#include <eeCModel.h>
#include <eeCRender.h>
#include <eeCCamera.h>
#include <eeCSkeletalMesh.h>
#include <eeCAnimation.h>
#include <eeCBounds.h>


using eeEngineSDK::eeConfigurations::screenWidth;
using eeEngineSDK::eeConfigurations::screenHeight;

using eeEngineSDK::Logger;
using eeEngineSDK::GraphicsApi;
using eeEngineSDK::ResourceManager;
using eeEngineSDK::SceneManager;
using eeEngineSDK::Scene;
using eeEngineSDK::Vector4f;
using eeEngineSDK::Vector3f;
using eeEngineSDK::Vector2f;
using eeEngineSDK::Vector2i;
using eeEngineSDK::Color;
using eeEngineSDK::Matrix4f;
using eeEngineSDK::Quaternion;
using eeEngineSDK::SimplexVertex;
using eeEngineSDK::SimpleVertex;
using eeEngineSDK::Object;
using eeEngineSDK::Model;
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
using eeEngineSDK::CModel;
using eeEngineSDK::CRender;
using eeEngineSDK::CSkeletalMesh;
using eeEngineSDK::CAnimation;
using eeEngineSDK::CBounds;

using eeEngineSDK::Input;
using eeEngineSDK::CameraDesc;
using eeEngineSDK::String;
using eeEngineSDK::eCAMERA_PROJECTION_TYPE;

using eeEngineSDK::MemoryManager;
using eeEngineSDK::Time;


using eeEngineSDK::eFILTER;
using eeEngineSDK::eTEXTURE_ADDRESS_MODE;
using eeEngineSDK::eCOMPARISON_FUNC;
using eeEngineSDK::ePRIMITIVE_TOPOLOGY;

using eeEngineSDK::SamplerStateDesc;
using eeEngineSDK::ViewportDesc;
using eeEngineSDK::RasteraizerDesc;



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
      inputMan.setKeyboardInputPressed(Input::eKEYBOARD::kQ, true);
    }
    else if (wParam == 'W') {
      inputMan.setKeyboardInputPressed(Input::eKEYBOARD::kW, true);
    }
    else if (wParam == 'E') {
      inputMan.setKeyboardInputPressed(Input::eKEYBOARD::kE, true);
    }
    else if (wParam == 'A') {
      inputMan.setKeyboardInputPressed(Input::eKEYBOARD::kA, true);
    }
    else if (wParam == 'S') {
      inputMan.setKeyboardInputPressed(Input::eKEYBOARD::kS, true);
    }
    else if (wParam == 'D') {
      inputMan.setKeyboardInputPressed(Input::eKEYBOARD::kD, true);
    }
    else if (wParam == 9) { // TAB
      inputMan.setKeyboardInputPressed(Input::eKEYBOARD::kTAB, true);
    }
    break;

  case WM_KEYUP:
    if (wParam == 'Q') {
      inputMan.setKeyboardInputPressed(Input::eKEYBOARD::kQ, false);
    }
    else if (wParam == 'W') {
      inputMan.setKeyboardInputPressed(Input::eKEYBOARD::kW, false);
    }
    else if (wParam == 'E') {
      inputMan.setKeyboardInputPressed(Input::eKEYBOARD::kE, false);
    }
    else if (wParam == 'A') {
      inputMan.setKeyboardInputPressed(Input::eKEYBOARD::kA, false);
    }
    else if (wParam == 'S') {
      inputMan.setKeyboardInputPressed(Input::eKEYBOARD::kS, false);
    }
    else if (wParam == 'D') {
      inputMan.setKeyboardInputPressed(Input::eKEYBOARD::kD, false);
    }
    else if (wParam == 9) { // TAB
      inputMan.setKeyboardInputPressed(Input::eKEYBOARD::kTAB, false);
    }
    break;

  case WM_LBUTTONDOWN:
    inputMan.setMouseClickInputPressed(Input::eMOUSE_CLICK::kLEFT_CLICK, true);
    break;

  case WM_RBUTTONDOWN:
    inputMan.setMouseClickInputPressed(Input::eMOUSE_CLICK::kRIGHT_CLICK, true);
    break;

  case WM_LBUTTONUP:
    inputMan.setMouseClickInputPressed(Input::eMOUSE_CLICK::kLEFT_CLICK, false);
    break;

  case WM_RBUTTONUP:
    inputMan.setMouseClickInputPressed(Input::eMOUSE_CLICK::kRIGHT_CLICK, false);
    break;

  case WM_MOUSEMOVE:
    inputMan.setMousePosition({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) });
    break;

  case WM_SIZE:
  {
    static bool _first = true;
    if (!_first) {
      int width = 0, height = 0;
      RECT rc;
      GetClientRect(reinterpret_cast<HWND>(GraphicsApi::instance().getWindow()), &rc);
      width = rc.right - rc.left;
      height = rc.bottom - rc.top;
      GraphicsApi::instance().resizeWindow({ width, height });
    }
    _first = false;
  }
  break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
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
  ImGui_ImplWin32_Init(graphicsApi.getWindow());

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
  eCAMERA_PROJECTION_TYPE pt = cam->getProjectionType();
  auto projIndex = static_cast<int>(pt);
  const char* projTypes[] = { "Orthographic", "Perspective" };
  if (ImGui::Combo("Projection Types", &projIndex, projTypes, 2)) {
    cam->setProjectionType(static_cast<eCAMERA_PROJECTION_TYPE>(projIndex));
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
DrawModelCmp(SPtr<CModel> model, int32& uniqueId)
{
  ImGui::PushID(uniqueId++);
  String modelName = model->getModel()->getName();
  Map<String, SPtr<Model>> models =
  ResourceManager::instance().getAllModelResources();
  int modelIndex = 0;
  int tempIndex = 0;
  Vector<const char*> names;
  for (auto& m : models) {
    names.push_back(m.first.c_str());
    if (m.first == modelName) {
      modelIndex = tempIndex;
    }
    tempIndex++;
  }
  if (ImGui::Combo("Model Resource",
                   &modelIndex,
                   names.data(),
                   static_cast<uint32>(names.size()))) {
    model->setModel(ResourceManager::instance().getResourceModel(names[modelIndex]));
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

void
AddChildActorsToUI(SPtr<Actor> act, int32& uniqueId);

SPtr<Actor> g_actorAddingCmp;
bool g_addingCmp = false;
void
showActorData(SPtr<Actor> act, int32& uniqueId)
{
  ImGui::PushID(uniqueId++);
  if (ImGui::TreeNode(act->getName().c_str())) {
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
      ImGui::Text("Animation");
      DrawAnimationCmp(animC, uniqueId);
      ImGui::Separator();
    }
    SPtr<CCamera> camC = act->getComponent<CCamera>();
    if (camC) {
      ImGui::Text("Camera");
      DrawCameraCmp(camC, uniqueId);
      ImGui::Separator();
    }
    SPtr<CModel> modelC = act->getComponent<CModel>();
    if (modelC) {
      ImGui::Text("Model");
      DrawModelCmp(modelC, uniqueId);
      ImGui::Separator();
    }
    SPtr<CRender> renderC = act->getComponent<CRender>();
    if (renderC) {
      ImGui::Text("Render");
      ImGui::Separator();
    }
    SPtr<CSkeletalMesh> skMeshC = act->getComponent<CSkeletalMesh>();
    if (skMeshC) {
      ImGui::Text("Skeletal Mesh");
      DrawSkeletalMeshCmp(skMeshC, uniqueId);
      ImGui::Separator();
    }

    ImGui::PushID(uniqueId++);
    if (ImGui::Button("AddComponent")) {
      g_addingCmp = true;
      g_actorAddingCmp = act;
    }
    ImGui::PopID();

    ImGui::PushID(uniqueId++);
    if (ImGui::TreeNode("Children")) {
      AddChildActorsToUI(act, uniqueId);
      ImGui::TreePop();
    }
    ImGui::PopID();
    ImGui::TreePop();
  }
  ImGui::PopID();
}

void
AddChildActorsToUI(SPtr<Actor> act, int32& uniqueId)
{
  for (auto& child : act->getChildren()) {
    showActorData(child, uniqueId);
  }
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
  static String AddingActorScene  ;

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


        const Map<String, SPtr<Actor>>& actors =
          sc.second->getAllActors();

        for (auto& act : actors) {
          if (!act.second->getParent()) {
            showActorData(act.second, uniqueId);
          }
        }
        ImGui::TreePop();
      }
      ImGui::PopID();
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
    Map<String, SPtr<Model>> models = resourceMan.getAllModelResources();
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

bool
BaseAppTest1::initResources()
{
  auto& graphicsApi = GraphicsApi::instance();
  auto& resourceManager = ResourceManager::instance();
  auto& sceneManager = SceneManager::instance();
  auto& memoryManager = MemoryManager::instance();

  if (FAILED(InitImgUI())) {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    return false;
  }

  SamplerStateDesc samDesc;
  memset(&samDesc, 0, sizeof(samDesc));
  samDesc.filter = eFILTER::kMIN_MAG_MIP_LINEAR;
  samDesc.addressU = eTEXTURE_ADDRESS_MODE::WRAP;
  samDesc.addressV = eTEXTURE_ADDRESS_MODE::WRAP;
  samDesc.addressW = eTEXTURE_ADDRESS_MODE::WRAP;
  samDesc.comparisonFunc = eCOMPARISON_FUNC::NEVER;
  samDesc.minLOD = 0;
  samDesc.maxLOD = Math::kMAX_FLOAT;

  resourceManager.loadTextureFromFile("Textures/Default.png",
                                                  "Default",
                                                  samDesc);

  Model::initPrimitives();


  /*m_rtv = graphicsApi.createRenderTragetPtr();
  m_rtv->createAsBackBuffer();

  m_dsv = graphicsApi.createDepthStencilPtr();
  m_dsv->create(screenWidth, screenHeight);*/


  graphicsApi.setPrimitiveTopology(ePRIMITIVE_TOPOLOGY::TRIANGLELIST);

  SPtr<Mesh> SAQ = memoryManager.newPtr<Mesh>();
  SAQ->loadFromArray<SimpleVertex, uint32>(
  Vector<SimpleVertex>
    {
      SimpleVertex
      {
        Vector4f(-1.0f,  1.0f, 0.0f, 1.0f),
        Vector4f( 0.0f,  0.0f, 0.0f, 0.0f),
        Vector4f( 0.0f,  0.0f, 0.0f, 0.0f)
      },
      SimpleVertex
      {
        Vector4f( 1.0f,  1.0f, 0.0f, 1.0f),
        Vector4f( 1.0f,  0.0f, 0.0f, 0.0f),
        Vector4f( 0.0f,  0.0f, 0.0f, 0.0f)
      },
      SimpleVertex
      {
        Vector4f( 1.0f, -1.0f,  0.0f, 1.0f),
        Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
        Vector4f( 0.0f,  0.0f,  0.0f, 0.0f)
      },
      SimpleVertex
      {
        Vector4f(-1.0f, -1.0f,  0.0f, 1.0f),
        Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
        Vector4f( 0.0f,  0.0f,  0.0f, 0.0f)
      }
    },
    Vector<uint32>
    {
      0, 1, 2, 
      0, 2, 3
    }
  );

  m_SAQ = memoryManager.newPtr<Object>();
  m_SAQ->loadFromModel
  (
    resourceManager.loadModelFromMeshesArray
    (
      Vector<Pair<SPtr<Mesh>, SPtr<Texture>>>
      {
        make_pair
        (
          SAQ,
          nullptr
        )
      },
      "SAQ"
    ),
    Vector3f(0.0f, 0.0f, 0.0f),
    Quaternion(Vector3f(0.0f, 0.0f, 0.0f)),
    Vector3f(1.0f, 1.0f, 1.0f)
  );
  
  
  if (!resourceManager.loadVertexShaderFromFile("Shaders/TestVShader.hlsl",
                                                "TestVS")) {
    return false;
  }
  if (!resourceManager.loadPixelShaderFromFile("Shaders/TestPShader.hlsl",
                                               "TestPS")) {
    return false;
  }

  if (!resourceManager.loadVertexShaderFromFile("Shaders/TestVSAnimShader.hlsl",
                                                "TestVSAnim")) {
    return false;
  }
  if (!resourceManager.loadPixelShaderFromFile("Shaders/TestPSAnimShader.hlsl",
                                               "TestPSAnim")) {
    return false;
  }
  
  
  if (!resourceManager.loadVertexShaderFromFile("Shaders/TestVSSAQ.hlsl",
                                                "TestSAQVS")) {
    return false;
  }
  if (!resourceManager.loadPixelShaderFromFile("Shaders/TestPSSAQ.hlsl",
                                               "TestSAQPS")) {
    return false;
  }
  
  m_viewMatrixBuffer = graphicsApi.createConstantBufferPtr();
  m_projectionMatrixBuffer = graphicsApi.createConstantBufferPtr();
  m_viewMatrixBuffer->initData(sizeof(Matrix4f), sizeof(Matrix4f), nullptr);
  m_projectionMatrixBuffer->initData(sizeof(Matrix4f), sizeof(Matrix4f), nullptr);
  
  
  RasteraizerDesc rasDesc;
  memset(&rasDesc, 0, sizeof(rasDesc));
  rasDesc.cullMode = eeEngineSDK::eCULL_MODE::FRONT;
  rasDesc.fillMode = eeEngineSDK::eFILL_MODE::SOLID;
  rasDesc.frontCounterClockwise = true;
  
  m_rasterizer = graphicsApi.createRasterizerStatePtr();
  if (!m_rasterizer->create(rasDesc)) {
    return false;
  }
  
  
  memset(&rasDesc, 0, sizeof(rasDesc));
  rasDesc.cullMode = eeEngineSDK::eCULL_MODE::FRONT;
  rasDesc.fillMode = eeEngineSDK::eFILL_MODE::SOLID;
  rasDesc.frontCounterClockwise = true;
  
  m_rasterizer2 = graphicsApi.createRasterizerStatePtr();
  if (!m_rasterizer2->create(rasDesc)) {
    return false;
  }
  


  SPtr<Scene> scene = sceneManager.addScene("Main");
  scene->setActive(true);



  SPtr<Actor> actor;



  CameraDesc camDesc;
  camDesc.projectionType = eCAMERA_PROJECTION_TYPE::kPerspective;
  camDesc.fovAngleY = Math::kPI / 4.0f;
  camDesc.viewSize = { static_cast<float>(screenWidth),
                       static_cast<float>(screenHeight) };
  camDesc.nearZ = 0.01f;
  camDesc.farZ = 100.0f;

  actor = scene->addActor("Player");
  actor->getTransform()->setPosition({ 0.0f, 3.0f, -6.0f });
  //actor->getTransform()->setScale({ 0.1f, 0.1f, 0.1f });
  actor->addComponent<CCamera>();
  actor->getComponent<CCamera>()->init(camDesc);
  actor->getComponent<CCamera>()->setMain(true);
  actor->addComponent<CModel>();
  actor->getComponent<CModel>()->setModel
  (
    Model::cube
  );
  actor->addComponent<CBounds>();
  actor->addComponent<CRender>();



  actor = scene->addActor("AtatchToActor");
  actor->attachTo(scene->getActor("Player"));
  actor->getTransform()->setPosition({ 0.0f, 0.0f, 30.0f });
  actor->addComponent<CModel>();
  actor->getComponent<CModel>()->setModel
  (
    Model::cube
  );
  actor->addComponent<CBounds>();
  actor->addComponent<CRender>();



  actor = scene->addActor("Player2");
  actor->getTransform()->setPosition({ 5.0f, 3.0f, -6.0f });
  actor->getTransform()->setScale({ 0.1f, 0.1f, 0.1f });
  actor->addComponent<CCamera>();
  actor->getComponent<CCamera>()->init(camDesc);
  actor->addComponent<CModel>();
  actor->getComponent<CModel>()->setModel
  (
    Model::cube
  );
  actor->addComponent<CBounds>();
  actor->addComponent<CRender>();



  actor = scene->addActor("Test");
  actor->getTransform()->setScale({ 2.0f, 2.0f, 2.0f });
  actor->getTransform()->setPosition({ 3.0f, 0.0f, 0.0f });
  actor->getTransform()->setRotation(Quaternion( {1.5707f, 0.0f, 0.0f} ));
  actor->addComponent<CModel>();
  actor->getComponent<CModel>()->setModel
  (
    resourceManager.loadModelFromFile
    (
      "C:/Users/Mara May/Desktop/Extras/Clases/Octavo/Motores/Modelos/Jinx/source/arcane_jinx_sketchfab.fbx",
      "ActorTest1"
    )
  );
  actor->getComponent<CModel>()->getModel()->setTexture
  (
    resourceManager.loadTextureFromFile
    (
      "C:/Users/Mara May/Desktop/Extras/Clases/Octavo/Motores/Modelos/Jinx/textures/F_MED_UproarBraids_Body_baseColor.png",
      "JinxBody_tex",
      samDesc
    ),
    0
  );
  actor->getComponent<CModel>()->getModel()->setTexture
  (
    resourceManager.loadTextureFromFile
    (
      "C:/Users/Mara May/Desktop/Extras/Clases/Octavo/Motores/Modelos/Jinx/textures/F_MED_UproarBraids_FaceAcc_baseColor.png",
      "JinxHair_tex",
      samDesc
    ),
    1
  );
  actor->getComponent<CModel>()->getModel()->setTexture
  (
    resourceManager.loadTextureFromFile
    (
      "C:/Users/Mara May/Desktop/Extras/Clases/Octavo/Motores/Modelos/Jinx/textures/FACE_-_TEST.png",
      "JinxFace_tex",
      samDesc
    ),
    2
  );
  actor->addComponent<CBounds>();
  actor->addComponent<CRender>();

  resourceManager.loadTextureFromFile
  (
    "C:/Users/Mara May/Desktop/Extras/Clases/Octavo/Motores/Modelos/Jinx/textures/F_MED_UproarBraids_Body_normal.png",
    "JinxNormal_tex",
    samDesc
  );


  resourceManager.importResourceFromFile("Models/boblampclean.md5mesh");
  resourceManager.importResourceFromFile("Models/boblampclean.md5anim");

  resourceManager.importResourceFromFile("Textures/guard1_body.jpg");
  resourceManager.importResourceFromFile("Textures/guard1_face.jpg");
  resourceManager.importResourceFromFile("Textures/guard1_helmet.jpg");
  resourceManager.importResourceFromFile("Textures/iron_grill.jpg");
  resourceManager.importResourceFromFile("Textures/round_grill.jpg");



  actor = scene->addActor("AnimTest");
  actor->getTransform()->setScale({ 0.03f, 0.03f, 0.03f });
  actor->getTransform()->setRotation(Quaternion({ Math::kPI * 0.5f,
                                                              0.0f,
                                                              0.0f }));
  actor->addComponent<CSkeletalMesh>();
  actor->getComponent<CSkeletalMesh>()->setModel
  (
    resourceManager.getResourceSkeletalMesh("boblampclean_skm")
  );
  actor->getComponent<CSkeletalMesh>()->getModel()->setTexture
  (
    resourceManager.getResourceTexture("guard1_body_tex"),
    0
  );
  actor->getComponent<CSkeletalMesh>()->getModel()->setTexture
  (
    resourceManager.getResourceTexture("guard1_face_tex"),
    1
  );
  actor->getComponent<CSkeletalMesh>()->getModel()->setTexture
  (
    resourceManager.getResourceTexture("guard1_helmet_tex"),
    2
  );
  actor->getComponent<CSkeletalMesh>()->getModel()->setTexture
  (
    resourceManager.getResourceTexture("iron_grill_tex"),
    3
  );
  actor->getComponent<CSkeletalMesh>()->getModel()->setTexture
  (
    resourceManager.getResourceTexture("round_grill_tex"),
    4
  );
  actor->getComponent<CSkeletalMesh>()->getModel()->setTexture
  (
    resourceManager.getResourceTexture("guard1_body_tex"),
    5
  );
  actor->addComponent<CAnimation>();
  actor->getComponent<CAnimation>()->setAnimation
  (
    resourceManager.getResourceAnimation("boblampclean_anim_")
  );
  actor->addComponent<CBounds>();
  actor->addComponent<CRender>();


  resourceManager.importResourceFromFile("Models/Scary_Clown_Walk.fbx");
  
  actor = scene->addActor("AnimTest2");
  actor->getTransform()->setScale({ 0.01f, 0.01f, 0.01f });
  actor->getTransform()->setPosition({ -3.0f, 0.0f, 0.0f });
  actor->addComponent<CSkeletalMesh>();
  actor->getComponent<CSkeletalMesh>()->setModel
  (
    resourceManager.getResourceSkeletalMesh("Scary_Clown_Walk_skm")
  );
  actor->addComponent<CAnimation>();
  actor->getComponent<CAnimation>()->setAnimation
  (
    resourceManager.getResourceAnimation("Scary_Clown_Walk_anim_mixamo.com")
  );
  actor->addComponent<CBounds>();
  actor->addComponent<CRender>();



  m_viewPosBuffer = graphicsApi.createConstantBufferPtr();
  m_viewPosBuffer->initData(sizeof(Vector4f), sizeof(Vector4f), nullptr);

  return true;
}

void
BaseAppTest1::update()
{
  auto& inputMan = Input::instance();
  auto& sceneManager = SceneManager::instance();
  auto& timeManager = Time::instance();

  Logger::instance().FileLog(EE_FORMAT_LOG(String("Test log")),
  "C:/Users/Mara May/Documents/GitHub/MotoresIDV7_EchoEngine/EchoEngine/bin/log"
    "s/testLog.txt", eeEngineSDK::WarningLevel::kDebug);


  BaseApp::update();


  SPtr<Scene> scene = sceneManager.getScene("Main");
  EE_NO_EXIST_RETURN(scene);

  static String activePlayerName = "Player";
  if (inputMan.getKeyboardInputPressed(eeEngineSDK::Input::eKEYBOARD::kTAB)) {
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
  //if (actor) {
  //  static Quaternion rot1(Vector3f(0.0f, 0.0f, 0.0f));
  //  rot1 = Quaternion((rot1.getEuclidean() +
  //                  Vector3f(timeManager.getDeltaTime() * .5f, 0.0f, 0.0f)));
  //  actor->getTransform()->setRotation(rot1);
  //}



  actor = scene->getActor(activePlayerName);

  SPtr<CTransform> trans = nullptr;
  if (actor) {
    trans = actor->getTransform();
  }

  Quaternion rot;
  if (trans) {
    rot = trans->getRotation();

    Vector3f cameraMovement = { 0.0f, 0.0f, 0.0f };
    if (inputMan.getKeyboardInputIsPressed(eeEngineSDK::Input::eKEYBOARD::kW)) {
      cameraMovement += rot.getFrontVector();
    }
    if (inputMan.getKeyboardInputIsPressed(eeEngineSDK::Input::eKEYBOARD::kS)) {
      cameraMovement -= rot.getFrontVector();
    }
    if (inputMan.getKeyboardInputIsPressed(eeEngineSDK::Input::eKEYBOARD::kA)) {
      cameraMovement -= rot.getRightVector();
    }
    if (inputMan.getKeyboardInputIsPressed(eeEngineSDK::Input::eKEYBOARD::kD)) {
      cameraMovement += rot.getRightVector();
    }
    if (inputMan.getKeyboardInputIsPressed(eeEngineSDK::Input::eKEYBOARD::kQ)) {
      cameraMovement += rot.getUpVector();
    }
    if (inputMan.getKeyboardInputIsPressed(eeEngineSDK::Input::eKEYBOARD::kE)) {
      cameraMovement -= rot.getUpVector();
    }
    trans->setPosition(trans->getPosition() +
      cameraMovement * timeManager.getDeltaTime() * 10.0f);

    if (inputMan.getMouseClickInputIsPressed(
                              eeEngineSDK::Input::eMOUSE_CLICK::kRIGHT_CLICK)) {
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
                                    * timeManager.getDeltaTime()
                                    * 1.0f);
      rot2 =
      Quaternion::createFromAxisAngle(rot.getRightVector(),
                                      mouseMove.y
                                    * timeManager.getDeltaTime()
                                    * 1.0f)
                                    * rot2;
      trans->setRotation(rot2 * rot);
    }
  }

  Vector3f pos = trans->getPosition();
  Vector4f vp = Vector4f(pos.x, pos.y, pos.z, 1.0f);
  //Logger::instance().ConsoleLog("x: " + eeEngineSDK::eeToString(pos.x)
  //                            + "y: " + eeEngineSDK::eeToString(pos.y)
  //                            + "z: " + eeEngineSDK::eeToString(pos.z));
  m_viewPosBuffer->updateData(reinterpret_cast<Byte*>(&vp));


  sceneManager.update();
}

void
BaseAppTest1::render()
{
  auto& graphicsApi = GraphicsApi::instance();
  auto& resourceManager = ResourceManager::instance();
  auto& sceneManager = SceneManager::instance();


  Vector<SPtr<CCamera>> activeCams = graphicsApi.getActiveCameras();
  Color color{ 0.3f, 0.5f, 0.8f, 1.0f };


  // Load shaders
  SPtr<VertexShader> vs =
    resourceManager.getResourceVertexShader("TestVS");
  SPtr<VertexShader> animVS =
    resourceManager.getResourceVertexShader("TestVSAnim");

  SPtr<PixelShader> ps =
    resourceManager.getResourcePixelShader("TestPS");
  SPtr<PixelShader> animPS =
    resourceManager.getResourcePixelShader("TestPSAnim");

  m_rasterizer->use();

  for (auto& cam : activeCams) {
    // Clean and set back buffer and depth stencil
    graphicsApi.clearRenderTargets({ cam->getRenderTarget() }, color);
    graphicsApi.cleanDepthStencils({ cam->getDepthStencil() });
    graphicsApi.setRenderTargets({ cam->getRenderTarget() }, cam->getDepthStencil());



    // Create view/proj matrices
    Matrix4f view = Matrix4f::kIDENTITY;
    view = cam->getViewMatrix().getTranspose();
    m_viewMatrixBuffer->updateData(reinterpret_cast<Byte*>(&view));

    Matrix4f proj = Matrix4f::kIDENTITY;
    proj = cam->getProjectionMatrix().getTranspose();
    m_projectionMatrixBuffer->updateData(reinterpret_cast<Byte*>(&proj));



    // Set buffers
    graphicsApi.setVSConstantBuffers
    (
      { m_viewMatrixBuffer, m_projectionMatrixBuffer },
      1u
    );



    Vector<SPtr<Actor>> rActors =
      sceneManager.getAllRenderableActorsInside(activeCams[0]);
    auto rActorsCount = static_cast<int32>(rActors.size());

    animVS->use();
    animPS->use();


    //Draw in-cam skeletal actors
    for (int32 i = 0; i < rActorsCount; ++i) {
      if (rActors[i]->getComponent<CSkeletalMesh>())
        graphicsApi.drawObject(rActors[i]);
    }

    vs->use();
    ps->use();

    m_viewPosBuffer->setInVertex(3u);

    //Draw in-cam actors
    for (int32 i = 0; i < rActorsCount; ++i) {
      if (!rActors[i]->getComponent<CSkeletalMesh>()) {
        graphicsApi.drawObject(rActors[i]);
      }
    }



    //Unbind buffers
    graphicsApi.unsetRenderTargets();
    graphicsApi.unsetVSConstantBuffers(3u, 0u);
  }


  //Set Back Buffer
  graphicsApi.clearRenderTargets({ graphicsApi.getBackBuffer() }, color);
  graphicsApi.cleanDepthStencils({ graphicsApi.getDepthStencil() });
  graphicsApi.setRenderTargets({ graphicsApi.getBackBuffer() }, graphicsApi.getDepthStencil());



  // Load shaders
  resourceManager.getResourceVertexShader("TestSAQVS")->use();

  resourceManager.getResourcePixelShader("TestSAQPS")->use();



  //Set the main camera render target texture to the SAQ and renders it to the
  //back buffer
  m_rasterizer2->use();
  for (auto& cam : activeCams) {
    if (cam->isMain()) {
      m_SAQ->getModel()->setTexture(cam->getRenderTarget()->getAsTexture(), 0);
      break;
    }
  }
  graphicsApi.drawObject(m_SAQ);


  UIRender();


  graphicsApi.present(0u, 0u);
}

void
BaseAppTest1::destroy()
{
  eeEngineSDK::BaseApp::destroy();
}
