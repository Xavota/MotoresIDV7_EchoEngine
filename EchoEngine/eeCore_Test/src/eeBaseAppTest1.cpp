#include "eeBaseAppTest1.h"
#include <eeVertexShader.h>
#include <eePixelShader.h>
#include <eeGraficsApi.h>
#include <eeResourceManager.h>
#include <eeObject.h>
#include <eeCoreConfiguration.h>

#include <eeMath.h>

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
using eeEngineSDK::SPtr;
using eeEngineSDK::Math;
using eeEngineSDK::VertexShader;
using eeEngineSDK::PixelShader;
using eeEngineSDK::Byte;

BaseAppTest1::BaseAppTest1()
{
}

BaseAppTest1::~BaseAppTest1()
{
}

bool BaseAppTest1::initResources()
{

  ResourceManager::instance().loadTextureFromFile("Textures/Default.png", "Default");


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
          <SimpleVertex, uint16>
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
            Vector<uint16>
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
          "TestTexture"
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
    "Models/Rammer 225 (Large).obj.obj",
    Vector3f(0.0f, 0.0f, 0.0f),
    Quaternion(Vector3f(0.0f, 0.0f, 0.0f)),
    Vector3f(0.1f, 0.10f, 0.10f)
  );



  if (!ResourceManager::instance().loadVertexShaderFromFile("TestVShader.hlsl",
                                                            "TestVS"))
  {
    return false;
  }
  if (!ResourceManager::instance().loadPixelShaderFromFile("TestPShader.hlsl",
                                                           "TestPS"))
  {
    return false;
  }

  m_viewMatrixBuffer = GraphicsApi::instance().getConstantBufferPtr();
  m_projectionMatrixBuffer = GraphicsApi::instance().getConstantBufferPtr();
  m_viewMatrixBuffer->initData(sizeof(Matrix4f), sizeof(Matrix4f), nullptr);
  m_projectionMatrixBuffer->initData(sizeof(Matrix4f), sizeof(Matrix4f), nullptr);


  return true;
}

void BaseAppTest1::update(float deltaTime)
{
  static Quaternion rot(Vector3f(0.0f, 0.0f, 0.0f));
  rot = Quaternion((rot.getEuclidean() + Vector3f(deltaTime, 0.0f, 0.0f)));
  m_model->setRotation(rot);
}

void BaseAppTest1::render()
{
  GraphicsApi::instance().clearScreen(0.3f, 0.5f, 0.8f);

  SPtr<VertexShader> vs =
  ResourceManager::instance().getResourceVertexShader("TestVS");
  vs->use();

  SPtr<PixelShader> ps =
  ResourceManager::instance().getResourcePixelShader("TestPS");
  ps->use();

  Matrix4f view = Matrix4f::IDENTITY;
  view = Matrix4f::viewMatrix(Vector3f(0.0f, 3.0f, -6.0f),
                              Vector3f(0.0f, 1.0f, 0.0f),
                              Vector3f(0.0f, 1.0f, 0.0f)).getTranspose();
  m_viewMatrixBuffer->updateData(reinterpret_cast<Byte*>(&view));
  m_viewMatrixBuffer->setInVertex(1u);
  //vs->setViewMatrix(view.getTranspose());

  Matrix4f proj = Matrix4f::IDENTITY;
  proj = Matrix4f::perspectiveMatrix(0.785398163f,
                                     static_cast<float>(eeEngineSDK::screenWidth) /
                                     static_cast<float>(720),
                                     0.01f,
                                     100.0f).getTranspose();
  m_projectionMatrixBuffer->updateData(reinterpret_cast<Byte*>(&proj));
  m_projectionMatrixBuffer->setInVertex(2u);
  //vs->setProjectionMatrix(proj.getTranspose());

  //GraphicsApi::instance().drawObject(m_triangle);
  //GraphicsApi::instance().drawObject(m_cube);
  GraphicsApi::instance().drawObject(m_model);

  GraphicsApi::instance().present();
}

void BaseAppTest1::destroy()
{
}
