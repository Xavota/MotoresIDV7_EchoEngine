#include "eeBaseAppTest1.h"
#include <eeVertexShader.h>
#include <eePixelShader.h>
#include <eeGraficsApi.h>
#include <eeResourceManager.h>
#include <eeSceneManager.h>
#include <eeScene.h>
#include <eeObject.h>
#include <eeCoreConfiguration.h>
#include <eeRenderTarget.h>
#include <eeDepthStencil.h>
#include <eeRasterizerState.h>
#include <eeActor.h>
#include <eeCTransform.h>
#include <eeCModel.h>
#include <eeCRender.h>
#include <eeCCamera.h>
#include <eeCSkeletalMesh.h>
#include <eeCAnimation.h>

#include <eeMath.h>
#include <eeInput.h>
#include <eeMemoryManager.h>
#include <eeTime.h>

#include <windows.h>
#include <windowsx.h>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include <eeDX11GraphicsApi.h>


using eeEngineSDK::eeConfigurations::screenWidth;
using eeEngineSDK::eeConfigurations::screenHeight;


using eeEngineSDK::GraphicsApi;
using eeEngineSDK::ResourceManager;
using eeEngineSDK::SceneManager;
using eeEngineSDK::Scene;
using eeEngineSDK::Vector4f;
using eeEngineSDK::Vector3f;
using eeEngineSDK::Vector2f;
using eeEngineSDK::Matrix4f;
using eeEngineSDK::Quaternion;
using eeEngineSDK::SimplexVertex;
using eeEngineSDK::SimpleVertex;
using eeEngineSDK::Object;
using eeEngineSDK::Model;
using eeEngineSDK::Mesh;
using eeEngineSDK::SkeletalMesh;
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



extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  // Handle UI inputs
  if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
    return 1;

  PAINTSTRUCT ps;
  HDC hdc;

  switch (message)
  {
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  case WM_KEYDOWN:
    if (wParam == 'Q')
    {
      Input::instance().setKeyboardInputPressed(Input::eKEYBOARD::Q, true);
    }
    else if (wParam == 'W')
    {
      Input::instance().setKeyboardInputPressed(Input::eKEYBOARD::W, true);
    }
    else if (wParam == 'E')
    {
      Input::instance().setKeyboardInputPressed(Input::eKEYBOARD::E, true);
    }
    else if (wParam == 'A')
    {
      Input::instance().setKeyboardInputPressed(Input::eKEYBOARD::A, true);
    }
    else if (wParam == 'S')
    {
      Input::instance().setKeyboardInputPressed(Input::eKEYBOARD::S, true);
    }
    else if (wParam == 'D')
    {
      Input::instance().setKeyboardInputPressed(Input::eKEYBOARD::D, true);
    }
    else if (wParam == 9) // TAB
    {
      Input::instance().setKeyboardInputPressed(Input::eKEYBOARD::TAB, true);
    }
    break;

  case WM_KEYUP:
    if (wParam == 'Q')
    {
      Input::instance().setKeyboardInputPressed(Input::eKEYBOARD::Q, false);
    }
    else if (wParam == 'W')
    {
      Input::instance().setKeyboardInputPressed(Input::eKEYBOARD::W, false);
    }
    else if (wParam == 'E')
    {
      Input::instance().setKeyboardInputPressed(Input::eKEYBOARD::E, false);
    }
    else if (wParam == 'A')
    {
      Input::instance().setKeyboardInputPressed(Input::eKEYBOARD::A, false);
    }
    else if (wParam == 'S')
    {
      Input::instance().setKeyboardInputPressed(Input::eKEYBOARD::S, false);
    }
    else if (wParam == 'D')
    {
      Input::instance().setKeyboardInputPressed(Input::eKEYBOARD::D, false);
    }
    else if (wParam == 9) // TAB
    {
      Input::instance().setKeyboardInputPressed(Input::eKEYBOARD::TAB, false);
    }
    break;

  case WM_LBUTTONDOWN:
    Input::instance().setMouseClickInputPressed(Input::eMOUSE_CLICK::LEFT_CLICK, true);
    break;

  case WM_RBUTTONDOWN:
    Input::instance().setMouseClickInputPressed(Input::eMOUSE_CLICK::RIGHT_CLICK, true);
    break;

  case WM_LBUTTONUP:
    Input::instance().setMouseClickInputPressed(Input::eMOUSE_CLICK::LEFT_CLICK, false);
    break;

  case WM_RBUTTONUP:
    Input::instance().setMouseClickInputPressed(Input::eMOUSE_CLICK::RIGHT_CLICK, false);
    break;

  case WM_MOUSEMOVE:
    Input::instance().setMousePosition({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) });
    break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
}

HRESULT InitImgUI()
{
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  const eeEngineSDK::DX11Basics* basics =
  reinterpret_cast<const eeEngineSDK::DX11Basics*>(GraphicsApi::instance().getBasics());

  // Setup Platform/Renderer back ends
  ImGui_ImplDX11_Init(basics->m_device, basics->m_deviceContext);
  ImGui_ImplWin32_Init(GraphicsApi::instance().getWindow());

  return S_OK;
}

void
AddChildActorsToUI(SPtr<Actor> act, int32& uniqueId);

void
showActorData(SPtr<Actor> act, int32& uniqueId)
{
  ImGui::PushID(uniqueId++);
  if (ImGui::TreeNode(act->getName().c_str()))
  {
    ImGui::PushID(uniqueId++);
    bool actActive = act->isActive();
    if (ImGui::Checkbox("Active", &actActive))
    {
      act->setActive(actActive);
    }
    ImGui::PopID();

    ImGui::PushID(uniqueId++);
    Vector3f actPos = act->getTransform()->getPosition();
    float pos[3] = { actPos.x, actPos.y, actPos.z };
    if (ImGui::DragFloat3("Position", pos, 0.01f, -1000.0f, 1000.0f))
    {
      act->getTransform()->setPosition(Vector3f(pos[0], pos[1], pos[2]));
    }
    ImGui::PopID();
    ImGui::PushID(uniqueId++);
    Vector3f actRot = act->getTransform()->getRotation().getEuclidean();
    float rot[3] = { actRot.x, actRot.y, actRot.z };
    if (ImGui::DragFloat3("Rotation", rot, 0.01f, -1000.0f, 1000.0f))
    {
      act->getTransform()->setRotation(Quaternion(Vector3f(rot[0], rot[1], rot[2])));
    }
    ImGui::PopID();
    ImGui::PushID(uniqueId++);
    Vector3f actScale = act->getTransform()->getScale();
    float scale[3] = { actScale.x, actScale.y, actScale.z };
    if (ImGui::DragFloat3("Scale", scale, 0.01f, -1000.0f, 1000.0f))
    {
      act->getTransform()->setScale(Vector3f(scale[0], scale[1], scale[2]));
    }
    ImGui::PopID();


    ImGui::PushID(uniqueId++);
    if (ImGui::TreeNode("Children"))
    {
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
  for (auto& child : act->getChildren())
  {
    showActorData(child, uniqueId);
  }
}

bool
NewSceneWindow(bool& added, char* name)
{
  if (ImGui::Begin("New Scene"))
  {
    ImGui::InputText("Name", name, 255);

    if (ImGui::Button("Create"))
    {
      added = true;
      ImGui::End();
      return true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel"))
    {
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
  if (ImGui::Begin("New Scene"))
  {
    ImGui::InputText("Name", name, 255);

    if (ImGui::Button("Create"))
    {
      added = true;
      ImGui::End();
      return true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel"))
    {
      added = false;
      ImGui::End();
      return true;
    }
  }
  ImGui::End();
  return false;
}

void
UIRender()
{
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();

  ImGui::NewFrame();

  static bool AddingScene = false;
  static bool AddingActor = false;
  static String AddingActorScene = "";

  if (AddingScene)
  {
    bool added = false;
    static char name[255];
    if (NewSceneWindow(added, name))
    {
      if (added)
      {
        SceneManager::instance().addScene(name);
      }
      AddingScene = false;
    }
  }
  if (AddingActor)
  {
    bool added = false;
    static char name[255];
    if (NewSceneWindow(added, name))
    {
      if (added)
      {
        SceneManager::instance().getScene(AddingActorScene)->addActor(name);
      }
      AddingScene = false;
    }
  }

  int32 uniqueId = 0;

  if (ImGui::Begin("Scene graph", nullptr, ImGuiWindowFlags_MenuBar))
  {
    if (ImGui::BeginMenuBar())
    {
      if (ImGui::BeginMenu("File"))
      {
        if (ImGui::MenuItem("Add Scene", NULL, nullptr))
        {
          AddingScene = true;
        }
        ImGui::EndMenu();
      }
    }
    ImGui::EndMenuBar();


    const Map<String, SPtr<Scene>>& scenes = 
    SceneManager::instance().getAllScenes();

    for (auto& sc : scenes)
    {
      ImGui::PushID(uniqueId++);
      if (ImGui::TreeNode(sc.first.c_str()))
      {
        ImGui::PushID(uniqueId++);
        if (ImGui::Button("Add Actor"))
        {
          AddingActor = true;
          AddingActorScene = sc.first;
        }
        ImGui::PopID();
        ImGui::PushID(uniqueId++);
        bool active = sc.second->isActive();
        if (ImGui::Checkbox("Active", &active))
        {
          sc.second->setActive(active);
        }
        ImGui::PopID();
        ImGui::PushID(uniqueId++);
        bool offActive = sc.second->isOffActive();
        if (ImGui::Checkbox("Off Active", &offActive))
        {
          sc.second->setOffActive(offActive);
        }
        ImGui::PopID();


        const Map<String, SPtr<Actor>>& actors =
          sc.second->getAllActors();

        for (auto& act : actors)
        {
          if (!act.second->getParent())
            showActorData(act.second, uniqueId);
        }
        ImGui::TreePop();
      }
      ImGui::PopID();
    }


  }
  ImGui::End();

  ImGui::ShowDemoWindow();
  
  ImGui::Render();

  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}



int32 BaseAppTest1::run(void* callback)
{
  return BaseApp::run(WndProc);
}

bool BaseAppTest1::initResources()
{
  if (FAILED(InitImgUI()))
  {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    return false;
  }

  SamplerStateDesc samDesc;
  memset(&samDesc, 0, sizeof(samDesc));
  samDesc.filter = eFILTER::MIN_MAG_MIP_LINEAR;
  samDesc.addressU = eTEXTURE_ADDRESS_MODE::WRAP;
  samDesc.addressV = eTEXTURE_ADDRESS_MODE::WRAP;
  samDesc.addressW = eTEXTURE_ADDRESS_MODE::WRAP;
  samDesc.comparisonFunc = eCOMPARISON_FUNC::NEVER;
  samDesc.minLOD = 0;
  samDesc.maxLOD = Math::kMAX_FLOAT;

  ResourceManager::instance().loadTextureFromFile("Textures/Default.png",
                                                  "Default",
                                                  samDesc);

  Model::initPrimitives();





  m_rtv = GraphicsApi::instance().createRenderTragetPtr();
  m_rtv->createAsBackBuffer();

  m_dsv = GraphicsApi::instance().createDepthStencilPtr();
  m_dsv->create(screenWidth, screenHeight);

  ViewportDesc desc;
  memset(&desc, 0, sizeof(desc));
  desc.width = static_cast<float>(screenWidth);
  desc.height = static_cast<float>(screenHeight);
  desc.maxDepth = 0;
  desc.minDepth = 0;
  desc.topLeftX = 0;
  desc.topLeftY = 0;
  GraphicsApi::instance().setViewports({ desc });



  GraphicsApi::instance().setPrimitiveTopology(ePRIMITIVE_TOPOLOGY::TRIANGLELIST);



  m_SAQ = MemoryManager::instance().newPtr<Object>();
  m_SAQ->loadFromModel
  (
    ResourceManager::instance().loadModelFromMeshesArray
    (
      Vector<Pair<SPtr<Mesh>, SPtr<Texture>>>
      {
        make_pair
        (
          ResourceManager::instance().loadMeshFromVertexArray
          <SimpleVertex, uint32>
          (
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
            },
            "MeshSAQ1"
          ),
          nullptr
        )
      },
      "SAQ"
    ),
    Vector3f(0.0f, 0.0f, 0.0f),
    Quaternion(Vector3f(0.0f, 0.0f, 0.0f)),
    Vector3f(1.0f, 1.0f, 1.0f)
  );
  
  
  
  if (!ResourceManager::instance().loadVertexShaderFromFile("Shaders/TestVShader.hlsl",
    "TestVS"))
  {
    return false;
  }
  if (!ResourceManager::instance().loadPixelShaderFromFile("Shaders/TestPShader.hlsl",
    "TestPS"))
  {
    return false;
  }

  if (!ResourceManager::instance().loadVertexShaderFromFile("Shaders/TestVSAnimShader.hlsl",
    "TestVSAnim"))
  {
    return false;
  }
  if (!ResourceManager::instance().loadPixelShaderFromFile("Shaders/TestPSAnimShader.hlsl",
    "TestPSAnim"))
  {
    return false;
  }
  
  
  if (!ResourceManager::instance().loadVertexShaderFromFile("Shaders/TestVSSAQ.hlsl",
    "TestSAQVS"))
  {
    return false;
  }
  if (!ResourceManager::instance().loadPixelShaderFromFile("Shaders/TestPSSAQ.hlsl",
    "TestSAQPS"))
  {
    return false;
  }
  
  m_viewMatrixBuffer = GraphicsApi::instance().createConstantBufferPtr();
  m_projectionMatrixBuffer = GraphicsApi::instance().createConstantBufferPtr();
  m_viewMatrixBuffer->initData(sizeof(Matrix4f), sizeof(Matrix4f), nullptr);
  m_projectionMatrixBuffer->initData(sizeof(Matrix4f), sizeof(Matrix4f), nullptr);
  
  
  RasteraizerDesc rasDesc;
  memset(&rasDesc, 0, sizeof(rasDesc));
  rasDesc.cullMode = eeEngineSDK::eCULL_MODE::FRONT;
  rasDesc.fillMode = eeEngineSDK::eFILL_MODE::SOLID;
  rasDesc.frontCounterClockwise = true;
  
  m_rasterizer = GraphicsApi::instance().createRasterizerStatePtr();
  if (!m_rasterizer->create(rasDesc))
  {
    return false;
  }
  
  
  memset(&rasDesc, 0, sizeof(rasDesc));
  rasDesc.cullMode = eeEngineSDK::eCULL_MODE::FRONT;
  rasDesc.fillMode = eeEngineSDK::eFILL_MODE::SOLID;
  rasDesc.frontCounterClockwise = true;
  
  m_rasterizer2 = GraphicsApi::instance().createRasterizerStatePtr();
  if (!m_rasterizer2->create(rasDesc))
  {
    return false;
  }
  


  SPtr<Scene> scene = SceneManager::instance().addScene("Main");
  scene->setActive(true);



  SPtr<Actor> actor;



  CameraDesc camDesc;
  camDesc.projectionType = eCAMERA_PROJECTION_TYPE::PERSPECTIVE;
  camDesc.fovAngleY = 0.785398163f;
  camDesc.viewSize = { static_cast<float>(screenWidth),
                       static_cast<float>(screenHeight) };
  camDesc.nearZ = 0.01f;
  camDesc.farZ = 100.0f;

  actor = scene->addActor("Player");
  actor->getTransform()->setPosition({ 0.0f, 3.0f, -6.0f });
  actor->getTransform()->setScale({ 0.1f, 0.1f, 0.1f });
  actor->addComponent<CCamera>();
  actor->getComponent<CCamera>()->init(camDesc);
  actor->getComponent<CCamera>()->setMain(true);
  actor->addComponent<CModel>();
  actor->getComponent<CModel>()->setModel
  (
    Model::cube
  );
  actor->addComponent<CRender>();



  actor = scene->addActor("AtatchToActor");
  actor->attachTo(scene->getActor("Player"));
  actor->getTransform()->setPosition({ 0.0f, 0.0f, 30.0f });
  actor->addComponent<CModel>();
  actor->getComponent<CModel>()->setModel
  (
    Model::cube
  );
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
  actor->addComponent<CRender>();



  actor = scene->addActor("Test");
  actor->getTransform()->setScale({ 0.1f, 0.1f, 0.1f });
  actor->getTransform()->setPosition({ 3.0f, 0.0f, 0.0f });
  actor->addComponent<CModel>();
  actor->getComponent<CModel>()->setModel
  (
    ResourceManager::instance().loadModelFromFile
    (
      "Models/steve.fbx",
      "ActorTest1"
    )
  );
  actor->getComponent<CModel>()->getModel()->setTexture
  (
    ResourceManager::instance().loadTextureFromFile
    (
      "Textures/steve.png",
      "SteveTex",
      samDesc
    ),
    0
  );
  actor->addComponent<CRender>();



  actor = scene->addActor("AnimTest");
  actor->getTransform()->setScale({ 0.03f, 0.03f, 0.03f });
  actor->getTransform()->setRotation(Quaternion({ Math::kPI * 0.5f,
                                                              0.0f,
                                                              0.0f }));
  actor->addComponent<CModel>();
  actor->getComponent<CModel>()->setModel
  (
    ResourceManager::instance().loadModelFromFile
    (
      "Models/boblampclean.md5mesh",
      "ActorTest2"
    )
  );
  actor->getComponent<CModel>()->getModel()->setTexture
  (
    ResourceManager::instance().loadTextureFromFile
    (
      "Textures/guard1_body.jpg",
      "ActorTest2_T1",
      samDesc
    ),
    0
  );
  actor->getComponent<CModel>()->getModel()->setTexture
  (
    ResourceManager::instance().loadTextureFromFile
    (
      "Textures/guard1_face.jpg",
      "ActorTest2_T2",
      samDesc
    ),
    1
  );
  actor->getComponent<CModel>()->getModel()->setTexture
  (
    ResourceManager::instance().loadTextureFromFile
    (
      "Textures/guard1_helmet.jpg",
      "ActorTest2_T3",
      samDesc
    ),
    2
  );
  actor->getComponent<CModel>()->getModel()->setTexture
  (
    ResourceManager::instance().loadTextureFromFile
    (
      "Textures/iron_grill.jpg",
      "ActorTest2_T4",
      samDesc
    ),
    3
  );
  actor->getComponent<CModel>()->getModel()->setTexture
  (
    ResourceManager::instance().loadTextureFromFile
    (
      "Textures/round_grill.jpg",
      "ActorTest2_T5",
      samDesc
    ),
    4
  );
  actor->getComponent<CModel>()->getModel()->setTexture
  (
    ResourceManager::instance().loadTextureFromFile
    (
      "Textures/guard1_body.jpg",
      "ActorTest2_T6",
      samDesc
    ),
    5
  );
  actor->addComponent<CSkeletalMesh>();
  actor->getComponent<CSkeletalMesh>()->setSkeletal
  (
    ResourceManager::instance().getResourceSkeletalMesh("ActorTest2_sk")
  );
  actor->addComponent<CAnimation>();
  actor->getComponent<CAnimation>()->setAnimation
  (
    ResourceManager::instance().loadAnimationFromFile
    (
      "Models/boblampclean.md5anim",
      "AnimationTest1"
    )
  );
  actor->addComponent<CRender>();



  actor = scene->addActor("AnimTest2");
  actor->getTransform()->setScale({ 0.01f, 0.01f, 0.01f });
  actor->getTransform()->setPosition({ -3.0f, 0.0f, 0.0f });
  actor->addComponent<CModel>();
  actor->getComponent<CModel>()->setModel
  (
    ResourceManager::instance().loadModelFromFile
    (
      "Models/Scary_Clown_Walk.fbx",
      "ActorTest3"
    )
  );
  actor->addComponent<CSkeletalMesh>();
  actor->getComponent<CSkeletalMesh>()->setSkeletal
  (
    ResourceManager::instance().getResourceSkeletalMesh("ActorTest3_sk")
  );
  actor->addComponent<CAnimation>();
  actor->getComponent<CAnimation>()->setAnimation
  (
    ResourceManager::instance().loadAnimationFromFile
    (
      "Models/Scary_Clown_Walk.fbx",
      "AnimationTest2"
    )
  );
  actor->addComponent<CRender>();

  return true;
}

void BaseAppTest1::update()
{
  BaseApp::update();


  SPtr<Scene> scene = SceneManager::instance().getScene("Main");
  EE_NO_EXIST_RETURN(scene);

  static String activePlayerName = "Player";
  if (Input::instance().getKeyboardInputPressed(eeEngineSDK::Input::eKEYBOARD::TAB))
  {
    if (scene->getActor(activePlayerName)
     && scene->getActor(activePlayerName)->getComponent<CCamera>())
      scene->getActor(activePlayerName)->getComponent<CCamera>()->setMain(false);

    if (activePlayerName == "Player")
    {
      activePlayerName = "Player2";
    }
    else
    {
      activePlayerName = "Player";
    }

    if (scene->getActor(activePlayerName)
     && scene->getActor(activePlayerName)->getComponent<CCamera>())
      scene->getActor(activePlayerName)->getComponent<CCamera>()->setMain(true);
  }




  SPtr<Actor> actor = scene->getActor("Test");
  if (actor)
  {
    static Quaternion rot1(Vector3f(0.0f, 0.0f, 0.0f));
    rot1 = Quaternion((rot1.getEuclidean() +
                    Vector3f(Time::instance().getDeltaTime() * .5f, 0.0f, 0.0f)));
    actor->getTransform()->setRotation(rot1);
  }



  actor = scene->getActor(activePlayerName);

  SPtr<CTransform> trans = nullptr;
  if (actor)
    trans = actor->getTransform();

  Quaternion rot;
  if (trans)
  {
    rot = trans->getRotation();

    Vector3f cameraMovement = { 0.0f, 0.0f, 0.0f };
    if (Input::instance().getKeyboardInputIsPressed(
                                              eeEngineSDK::Input::eKEYBOARD::W))
    {
      cameraMovement += rot.getFrontVector();
    }
    if (Input::instance().getKeyboardInputIsPressed(
                                              eeEngineSDK::Input::eKEYBOARD::S))
    {
      cameraMovement -= rot.getFrontVector();
    }
    if (Input::instance().getKeyboardInputIsPressed(
                                              eeEngineSDK::Input::eKEYBOARD::A))
    {
      cameraMovement -= rot.getRightVector();
    }
    if (Input::instance().getKeyboardInputIsPressed(
                                              eeEngineSDK::Input::eKEYBOARD::D))
    {
      cameraMovement += rot.getRightVector();
    }
    if (Input::instance().getKeyboardInputIsPressed(
                                              eeEngineSDK::Input::eKEYBOARD::Q))
    {
      cameraMovement += rot.getUpVector();
    }
    if (Input::instance().getKeyboardInputIsPressed(
                                              eeEngineSDK::Input::eKEYBOARD::E))
    {
      cameraMovement -= rot.getUpVector();
    }
    trans->setPosition(trans->getPosition() +
      cameraMovement * Time::instance().getDeltaTime() * 10.0f);

    if (Input::instance().getMouseClickInputIsPressed(
                                 eeEngineSDK::Input::eMOUSE_CLICK::RIGHT_CLICK))
    {
      Quaternion rot2 = trans->getRotation();
      rot2 = Quaternion
      (
        (
          rot2.getEuclidean() +
          Vector3f
          (
            Input::instance().getMouseMovement().y *
            Time::instance().getDeltaTime() *
            1.0f,
            Input::instance().getMouseMovement().x *
            Time::instance().getDeltaTime() *
            1.0f,
            0.0f
          )
        )
      );
      trans->setRotation(rot2);
    }
  }


  SceneManager::instance().update();
}

void BaseAppTest1::render()
{
  Vector<SPtr<CCamera>> activeCams = GraphicsApi::instance().getActiveCameras();
  float color[4] = { 0.3f, 0.5f, 0.8f, 1.0f };



  // Load shaders
  SPtr<VertexShader> vs =
    ResourceManager::instance().getResourceVertexShader("TestVS");
  SPtr<VertexShader> animVS =
    ResourceManager::instance().getResourceVertexShader("TestVSAnim");

  SPtr<PixelShader> ps =
    ResourceManager::instance().getResourcePixelShader("TestPS");
  SPtr<PixelShader> animPS =
    ResourceManager::instance().getResourcePixelShader("TestPSAnim");

  m_rasterizer->use();

  for (auto& cam : activeCams)
  {
    // Clean and set back buffer and depth stencil
    GraphicsApi::instance().clearRenderTargets({ cam->getRenderTarget() }, color);
    GraphicsApi::instance().cleanDepthStencils({ cam->getDepthStencil() });
    GraphicsApi::instance().setRenderTargets({ cam->getRenderTarget() }, cam->getDepthStencil());



    // Create view/proj matrices
    Matrix4f view = Matrix4f::IDENTITY;
    if (cam)
      view = cam->getViewMatrix().getTranspose();
    m_viewMatrixBuffer->updateData(reinterpret_cast<Byte*>(&view));

    Matrix4f proj = Matrix4f::IDENTITY;
    if (cam)
      proj = cam->getProjectionMatrix().getTranspose();
    m_projectionMatrixBuffer->updateData(reinterpret_cast<Byte*>(&proj));



    // Set buffers
    GraphicsApi::instance().setVSConstantBuffers
    (
      { m_viewMatrixBuffer, m_projectionMatrixBuffer },
      1u
    );



    Vector<SPtr<Actor>> rActors =
      SceneManager::instance().getAllRenderableActorsInside(activeCams[0]);
    int32 rActorsCount = static_cast<int32>(rActors.size());

    animVS->use();
    animPS->use();

    //Draw in-cam skeletal actors
    for (int32 i = 0; i < rActorsCount; ++i)
    {
      if (rActors[i]->getComponent<CSkeletalMesh>())
        GraphicsApi::instance().drawObject(rActors[i]);
    }

    vs->use();
    ps->use();

    //Draw in-cam actors
    for (int32 i = 0; i < rActorsCount; ++i)
    {
      if (!rActors[i]->getComponent<CSkeletalMesh>())
        GraphicsApi::instance().drawObject(rActors[i]);
    }



    //Unbind buffers
    GraphicsApi::instance().unsetRenderTargets();
    GraphicsApi::instance().unsetVSConstantBuffers(3u, 0u);
  }


  //Set Back Buffer
  GraphicsApi::instance().clearRenderTargets({ m_rtv }, color);
  GraphicsApi::instance().cleanDepthStencils({ m_dsv });
  GraphicsApi::instance().setRenderTargets({ m_rtv }, m_dsv);



  // Load shaders
  ResourceManager::instance().getResourceVertexShader("TestSAQVS")->use();

  ResourceManager::instance().getResourcePixelShader("TestSAQPS")->use();



  //Set the main camera render target texture to the SAQ and renders it to the
  //back buffer
  m_rasterizer2->use();
  for (auto& cam : activeCams)
  {
    if (cam->isMain())
    {
      m_SAQ->getModel()->setTexture(cam->getRenderTarget()->getAsTexture(), 0);
      break;
    }
  }
  GraphicsApi::instance().drawObject(m_SAQ);


  UIRender();


  GraphicsApi::instance().present(0u, 0u);
}

void BaseAppTest1::destroy()
{
  eeEngineSDK::BaseApp::destroy();
}
