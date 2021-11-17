#include "eeBaseAppTest1.h"
#include <eeVertexShader.h>
#include <eePixelShader.h>
#include <eeGraficsApi.h>
#include <eeResourceManager.h>
#include <eeObject.h>
#include <eeCoreConfiguration.h>
#include <eeRenderTarget.h>
#include <eeDepthStencil.h>
#include <eeRasterizerState.h>

#include <eeMath.h>

using eeEngineSDK::eeConfigurations::screenWidth;
using eeEngineSDK::eeConfigurations::screenHeight;


using eeEngineSDK::GraphicsApi;
using eeEngineSDK::ResourceManager;
using eeEngineSDK::Vector4f;
using eeEngineSDK::Vector3f;
using eeEngineSDK::Vector2f;
using eeEngineSDK::Matrix4f;
using eeEngineSDK::Quaternion;
using eeEngineSDK::SimplexVertex;
using eeEngineSDK::SimpleVertex;
using eeEngineSDK::Object;
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


  m_cube = std::make_shared<Object>();
  m_cube->loadFromModel
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
                Vector4f(-1.0f,  1.0f, -1.0f, 1.0f),
                Vector4f(0.0f,  0.0f,  0.0f, 0.0f),
                Vector4f(0.0f,  1.0f,  0.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(1.0f,  1.0f, -1.0f, 1.0f),
                Vector4f(1.0f,  0.0f,  0.0f, 0.0f),
                Vector4f(0.0f,  1.0f,  0.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(1.0f,  1.0f,  1.0f, 1.0f),
                Vector4f(1.0f,  1.0f,  0.0f, 0.0f),
                Vector4f(0.0f,  1.0f,  0.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(-1.0f,  1.0f,  1.0f, 1.0f),
                Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
                Vector4f(0.0f,  1.0f,  0.0f, 0.0f)
              },
              
              SimpleVertex
              {
                Vector4f(-1.0f, -1.0f, -1.0f, 1.0f),
                Vector4f(0.0f,  0.0f,  0.0f, 0.0f),
                Vector4f(0.0f, -1.0f,  0.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(1.0f, -1.0f, -1.0f, 1.0f),
                Vector4f(1.0f,  0.0f,  0.0f, 0.0f),
                Vector4f(0.0f, -1.0f,  0.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(1.0f, -1.0f,  1.0f, 1.0f),
                Vector4f(1.0f,  1.0f,  0.0f, 0.0f),
                Vector4f(0.0f, -1.0f,  0.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(-1.0f, -1.0f,  1.0f, 1.0f),
                Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
                Vector4f(0.0f, -1.0f,  0.0f, 0.0f)
              },
              
              SimpleVertex
              {
                Vector4f(-1.0f, -1.0f,  1.0f, 1.0f),
                Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
                Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(-1.0f, -1.0f, -1.0f, 1.0f),
                Vector4f(0.0f,  0.0f,  0.0f, 0.0f),
                Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(-1.0f,  1.0f, -1.0f, 1.0f),
                Vector4f(1.0f,  0.0f,  0.0f, 0.0f),
                Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(-1.0f,  1.0f,  1.0f, 1.0f),
                Vector4f(1.0f,  1.0f,  0.0f, 0.0f),
                Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
              },
              
              SimpleVertex
              {
                Vector4f(1.0f, -1.0f,  1.0f, 1.0f),
                Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
                Vector4f(1.0f,  0.0f,  0.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(1.0f, -1.0f, -1.0f, 1.0f),
                Vector4f(0.0f,  0.0f,  0.0f, 0.0f),
                Vector4f(1.0f,  0.0f,  0.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(1.0f,  1.0f, -1.0f, 1.0f),
                Vector4f(1.0f,  0.0f,  0.0f, 0.0f),
                Vector4f(1.0f,  0.0f,  0.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(1.0f,  1.0f,  1.0f, 1.0f),
                Vector4f(1.0f,  1.0f,  0.0f, 0.0f),
                Vector4f(1.0f,  0.0f,  0.0f, 0.0f)
              },
              
              SimpleVertex
              {
                Vector4f(-1.0f, -1.0f, -1.0f, 1.0f),
                Vector4f(0.0f,  0.0f,  0.0f, 0.0f),
                Vector4f(0.0f,  0.0f, -1.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(1.0f, -1.0f, -1.0f, 1.0f),
                Vector4f(1.0f,  0.0f,  0.0f, 0.0f),
                Vector4f(0.0f,  0.0f, -1.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(1.0f,  1.0f, -1.0f, 1.0f),
                Vector4f(1.0f,  1.0f,  0.0f, 0.0f),
                Vector4f(0.0f,  0.0f, -1.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(-1.0f,  1.0f, -1.0f, 1.0f),
                Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
                Vector4f(0.0f,  0.0f, -1.0f, 0.0f)
              },
              
              SimpleVertex
              {
                Vector4f(-1.0f, -1.0f,  1.0f, 1.0f),
                Vector4f(0.0f,  0.0f,  0.0f, 0.0f),
                Vector4f(0.0f,  0.0f,  1.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(1.0f, -1.0f,  1.0f, 1.0f),
                Vector4f(1.0f,  0.0f,  0.0f, 0.0f),
                Vector4f(0.0f,  0.0f, -1.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(1.0f,  1.0f,  1.0f, 1.0f),
                Vector4f(1.0f,  1.0f,  0.0f, 0.0f),
                Vector4f(0.0f,  0.0f, -1.0f, 0.0f)
              },
              SimpleVertex
              {
                Vector4f(-1.0f,  1.0f,  1.0f, 1.0f),
                Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
                Vector4f(0.0f,  0.0f, -1.0f, 0.0f)
              }
            },
            Vector<uint32>
            {
              3, 1, 0,
              2, 1, 3,
              
              6, 4, 5,
              7, 4, 6,
              
              11, 9, 8,
              10, 9, 11,
              
              14, 12, 13,
              15, 12, 14,
              
              19, 17, 16,
              18, 17, 19,
              
              22, 20, 21,
              23, 20, 22
            },
            "TestCubeMesh1"
          ),
          1u
        )
      },
      {
        ResourceManager::instance().loadTextureFromFile
        (
          "pepe.png",
          "TestTexture",
          samDesc
        )
      },
      "TestCube"
    ),
    Vector3f(0.0f, 0.0f, 0.0f),
    Quaternion(Vector3f(0.0f, 0.0f, 0.0f)),
    Vector3f(1.0f, 1.0f, 1.0f)
  );

  m_model = std::make_shared<Object>();
  m_model->loadFromFile
  (
    "Models/plant.obj",

    Vector3f(0.0f, 0.0f, 0.0f),
    Quaternion(Vector3f(0.0f, 0.0f, 0.0f)),
    Vector3f(0.1f, 0.10f, 0.10f)
  );

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

  return true;
}

void BaseAppTest1::update(float deltaTime)
{
  static Quaternion rot(Vector3f(0.0f, 0.0f, 0.0f));
  rot = Quaternion((rot.getEuclidean() + Vector3f(deltaTime * .5f, 0.0f, 0.0f)));
  m_cube->setRotation(rot);
}

void BaseAppTest1::render()
{
  // Clean and set back buffer and depth stencil
  float color[4] = {0.3f, 0.5f, 0.8f, 1.0f};
  GraphicsApi::instance().clearRenderTargets({m_rtv2}, color);
  GraphicsApi::instance().cleanDepthStencils({m_dsv2});
  GraphicsApi::instance().setRenderTargets({m_rtv2}, m_dsv2);



  // Load shaders
  SPtr<VertexShader> vs =
  ResourceManager::instance().getResourceVertexShader("TestVS");
  vs->use();

  SPtr<PixelShader> ps =
  ResourceManager::instance().getResourcePixelShader("TestPS");
  ps->use();



  // Create view/proj matrices
  Matrix4f view = Matrix4f::IDENTITY;
  view = Matrix4f::viewMatrix(Vector3f(0.0f, 3.0f, -6.0f),
                              Vector3f(0.0f, 1.0f, 0.0f),
                              Vector3f(0.0f, 1.0f, 0.0f)).getTranspose();
  m_viewMatrixBuffer->updateData(reinterpret_cast<Byte*>(&view));

  Matrix4f proj = Matrix4f::IDENTITY;
  proj = Matrix4f::perspectiveMatrix(0.785398163f,
                                     static_cast<float>(screenWidth) /
                                     static_cast<float>(screenHeight),
                                     0.01f,
                                     100.0f).getTranspose();
  m_projectionMatrixBuffer->updateData(reinterpret_cast<Byte*>(&proj));



  // Set buffers
  GraphicsApi::instance().setVSConstantBuffers
  (
    { m_viewMatrixBuffer, m_projectionMatrixBuffer },
    1u
  );


  m_rasterizer->use();
  // Draws the object
  //GraphicsApi::instance().drawObject(m_triangle);
  GraphicsApi::instance().drawObject(m_cube);
  //GraphicsApi::instance().drawObject(m_model);


  GraphicsApi::instance().unsetRenderTargets();
  GraphicsApi::instance().unsetTextures(1u, 0u);
  GraphicsApi::instance().unsetVSConstantBuffers(3u, 0u);



  GraphicsApi::instance().clearRenderTargets({ m_rtv }, color);
  GraphicsApi::instance().cleanDepthStencils({ m_dsv });
  GraphicsApi::instance().setRenderTargets({ m_rtv }, m_dsv);



  // Load shaders
  vs = ResourceManager::instance().getResourceVertexShader("TestSAQVS");
  vs->use();

  ps = ResourceManager::instance().getResourcePixelShader("TestSAQPS");
  ps->use();


  m_rasterizer2->use();
  GraphicsApi::instance().drawObject(m_SAQ);


  GraphicsApi::instance().present(0u, 0u);
}

void BaseAppTest1::destroy()
{
  eeEngineSDK::BaseApp::destroy();
}
