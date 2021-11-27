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

#include <eeMath.h>
#include <eeInput.h>

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
using eeEngineSDK::Vector;
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
using eeEngineSDK::Input;
using eeEngineSDK::CameraDesc;
using eeEngineSDK::String;
using eeEngineSDK::eCAMERA_PROJECTION_TYPE;


using eeEngineSDK::eFILTER;
using eeEngineSDK::eTEXTURE_ADDRESS_MODE;
using eeEngineSDK::eCOMPARISON_FUNC;
using eeEngineSDK::ePRIMITIVE_TOPOLOGY;

using eeEngineSDK::SamplerStateDesc;
using eeEngineSDK::ViewportDesc;
using eeEngineSDK::RasteraizerDesc;

BaseAppTest1::BaseAppTest1()
{
}

BaseAppTest1::~BaseAppTest1()
{
}

bool BaseAppTest1::initResources()
{
  SamplerStateDesc samDesc;
  memset(&samDesc, 0, sizeof(samDesc));
  samDesc.filter = eFILTER::MIN_MAG_MIP_LINEAR;
  samDesc.addressU = eTEXTURE_ADDRESS_MODE::WRAP;
  samDesc.addressV = eTEXTURE_ADDRESS_MODE::WRAP;
  samDesc.addressW = eTEXTURE_ADDRESS_MODE::WRAP;
  samDesc.comparisonFunc = eCOMPARISON_FUNC::NEVER;
  samDesc.minLOD = 0;
  samDesc.maxLOD = Math::kMAX_FLOAT;

  ResourceManager::instance().loadTextureFromFile("Textures/Default.png", "Default", samDesc);

  Model::initPrimitives();





  m_rtv = GraphicsApi::instance().createRenderTragetPtr();
  m_rtv->createAsBackBuffer();

  m_dsv = GraphicsApi::instance().createDepthStencilPtr();
  m_dsv->create(screenWidth, screenHeight);

  m_rtv2 = GraphicsApi::instance().createRenderTragetPtr();
  m_rtv2->createAsIOTexture();

  m_dsv2 = GraphicsApi::instance().createDepthStencilPtr();
  m_dsv2->create(screenWidth, screenHeight);

  ViewportDesc desc;
  memset(&desc, 0, sizeof(desc));
  desc.width = screenWidth;
  desc.height = screenHeight;
  desc.maxDepth = 0;
  desc.minDepth = 0;
  desc.topLeftX = 0;
  desc.topLeftY = 0;
  GraphicsApi::instance().setViewports({ desc });



  GraphicsApi::instance().setPrimitiveTopology(ePRIMITIVE_TOPOLOGY::TRIANGLELIST);



  m_SAQ = std::make_shared<Object>();
  m_SAQ->loadFromModel
  (
    ResourceManager::instance().loadModelFromMeshesArray
    (
      Vector<Pair<SPtr<Mesh>, uint8>>
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
          1u
        )
      },
      Vector<SPtr<Texture>>
      {
        m_rtv2->getAsTexture()
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


  
  CameraDesc camDesc;

  camDesc.projectionType = eCAMERA_PROJECTION_TYPE::PERSPECTIVE;
  camDesc.fovAngleY = 0.785398163f;
  camDesc.viewSize = { static_cast<float>(screenWidth),
                       static_cast<float>(screenHeight) };
  camDesc.nearZ = 0.01f;
  camDesc.farZ = 100.0f;

  SPtr<Actor> actor = scene->addActor("Player");
  actor->getComponent<CTransform>()->setPosition({ 0.0f, 3.0f, -6.0f });
  actor->getComponent<CTransform>()->setScale({ 0.1f, 0.1f, 0.1f });
  actor->addComponent<CCamera>();
  actor->getComponent<CCamera>()->init(camDesc);
  actor->getComponent<CCamera>()->setMain(true);
  actor->addComponent<CModel>();
  actor->getComponent<CModel>()->setModel
  (
    Model::cube
  );
  actor->addComponent<CRender>();



  actor = scene->addActor("Test");
  actor->getComponent<CTransform>()->setScale({ 0.1f, 0.1f, 0.1f });
  actor->addComponent<CModel>();
  actor->getComponent<CModel>()->setModel
  (
    ResourceManager::instance().loadModelFromFile
    (
      "Models/steve.fbx",
      "ActorTest1"
    )
  );
  actor->addComponent<CRender>();
  


  actor = scene->addActor("AtatchToActor");
  actor->AttachTo(scene->getActor("Player"));
  actor->getComponent<CTransform>()->setPosition({ 0.0f, 0.0f, 30.0f });
  actor->addComponent<CModel>();
  actor->getComponent<CModel>()->setModel
  (
    Model::cube
  );
  actor->addComponent<CRender>();


  actor = scene->addActor("Player2");
  actor->getComponent<CTransform>()->setPosition({ 5.0f, 3.0f, -6.0f });
  actor->getComponent<CTransform>()->setScale({ 0.1f, 0.1f, 0.1f });
  actor->addComponent<CCamera>();
  actor->getComponent<CCamera>()->init(camDesc);
  actor->addComponent<CModel>();
  actor->getComponent<CModel>()->setModel
  (
    Model::cube
  );
  actor->addComponent<CRender>();

  return true;
}

void BaseAppTest1::update(float deltaTime)
{
  BaseApp::update(deltaTime);


  SPtr<Scene> scene = SceneManager::instance().getScene("Main");

  static String activePlayerName = "Player";
  if (Input::instance().getKeyboardInputPressed(eeEngineSDK::Input::eKEYBOARD::TAB))
  {
    scene->getActor(activePlayerName)->getComponent<CCamera>()->setMain(false);

    if (activePlayerName == "Player")
    {
      activePlayerName = "Player2";
    }
    else
    {
      activePlayerName = "Player";
    }

    scene->getActor(activePlayerName)->getComponent<CCamera>()->setMain(true);
  }




  SPtr<Actor> actor = scene->getActor("Test");
  static Quaternion rot1(Vector3f(0.0f, 0.0f, 0.0f));
  rot1 = Quaternion((rot1.getEuclidean() + Vector3f(deltaTime * .5f, 0.0f, 0.0f)));
  actor->getComponent<CTransform>()->setRotation(rot1);



  actor = scene->getActor(activePlayerName);
  SPtr<CTransform> trans = nullptr;
  if (actor)
    trans = actor->getComponent<CTransform>();

  Quaternion rot;
  if (trans)
    rot = trans->getRotation();

  Vector3f cameraMovement = { 0.0f, 0.0f, 0.0f };
  if (Input::instance().getKeyboardInputIsPressed(eeEngineSDK::Input::eKEYBOARD::W))
  {
    cameraMovement += rot.getFrontVector();
  }
  if (Input::instance().getKeyboardInputIsPressed(eeEngineSDK::Input::eKEYBOARD::S))
  {
    cameraMovement -= rot.getFrontVector();
  }
  if (Input::instance().getKeyboardInputIsPressed(eeEngineSDK::Input::eKEYBOARD::A))
  {
    cameraMovement -= rot.getRightVector();
  }
  if (Input::instance().getKeyboardInputIsPressed(eeEngineSDK::Input::eKEYBOARD::D))
  {
    cameraMovement += rot.getRightVector();
  }
  if (Input::instance().getKeyboardInputIsPressed(eeEngineSDK::Input::eKEYBOARD::Q))
  {
    cameraMovement += rot.getUpVector();
  }
  if (Input::instance().getKeyboardInputIsPressed(eeEngineSDK::Input::eKEYBOARD::E))
  {
    cameraMovement -= rot.getUpVector();
  }
  trans->setPosition(trans->getPosition() + cameraMovement * deltaTime * 10.0f);
  
  if (Input::instance().getMouseClickInputIsPressed(eeEngineSDK::Input::eMOUSE_CLICK::RIGHT_CLICK))
  {
    Quaternion rot2 = trans->getRotation();
    rot2 = Quaternion((rot2.getEuclidean() + Vector3f(Input::instance().getMouseMovement().y * deltaTime * 1.0f, Input::instance().getMouseMovement().x * deltaTime * 1.0f, 0.0f)));
    trans->setRotation(rot2);
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
  vs->use();

  SPtr<PixelShader> ps =
    ResourceManager::instance().getResourcePixelShader("TestPS");
  ps->use();

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

    m_rasterizer->use();



    //Draw in-cam actors
    Vector<SPtr<Actor>> rActors =
     SceneManager::instance().getAllRenderableActorsInside(activeCams[0]);
    int32 rActorsCount = rActors.size();
    for (int32 i = 0; i < rActorsCount; ++i)
    {
      GraphicsApi::instance().drawObject(rActors[i].get());
    }



    //Unbind buffers
    GraphicsApi::instance().unsetRenderTargets();
    GraphicsApi::instance().unsetTextures(1u, 0u);
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
      m_SAQ->getModel()->setTexture(cam->getRenderTarget()->getAsTexture(), 1);
      break;
    }
  }
  GraphicsApi::instance().drawObject(m_SAQ);


  GraphicsApi::instance().present(0u, 0u);
}

void BaseAppTest1::destroy()
{
  eeEngineSDK::BaseApp::destroy();
}
