#include "BaseAppTest1.h"
#include <eeGraficsApi.h>
#include <eeResourceManager.h>
#include <eeObject.h>

#include <eeMath.h>

using eeEngineSDK::GraphicsApi;
using eeEngineSDK::ResourceManager;
using eeEngineSDK::Vector3f;
using eeEngineSDK::Vector2f;
using eeEngineSDK::Quaternion;
using eeEngineSDK::SimplexVertex;
using eeEngineSDK::Object;
using eeEngineSDK::Mesh;
using eeEngineSDK::Vector;
using eeEngineSDK::uint16;
using eeEngineSDK::SPtr;
using eeEngineSDK::Math;

BaseAppTest1::BaseAppTest1()
{
}

BaseAppTest1::~BaseAppTest1()
{
}

bool BaseAppTest1::init()
{
  if (!BaseApp::init())
  {
    return false;
  }
  
  m_triangle = std::make_shared<Object>();
  m_triangle->loadFromModel(
    ResourceManager::instance().loadModelFromMeshesArray
    (
      Vector<SPtr<Mesh>>
      {
        ResourceManager::instance().loadMeshFromVertexArray
        (
          Vector<SimplexVertex>
          {
            SimplexVertex{Vector3f(-1.0f,  0.5f,  0.0f)},
            SimplexVertex{Vector3f(-0.01f,  0.5f,  0.0f)},
            SimplexVertex{Vector3f(-0.01f, -0.5f,  0.0f)}
          },
          Vector<uint16>
          {
            0u, 1u, 2u
          },
          "TestTriangleMesh1"
        )
      },
      "TestTriangle"
    ),
    Vector3f(0.0f, 0.0f, 0.0f),
    Quaternion(Vector3f(0.0f, 0.0f, 0.0f)),
    Vector3f(1.0f, 1.0f, 1.0f)
  );

  m_cube = std::make_shared<Object>();
  m_cube->loadFromModel(
    ResourceManager::instance().loadModelFromMeshesArray
    (
      Vector<SPtr<Mesh>>
      {
        ResourceManager::instance().loadMeshFromVertexArray
        (
          Vector<SimplexVertex>
          {
            SimplexVertex{Vector3f(-0.5f,  0.5f,  0.5f)},
            SimplexVertex{Vector3f( 0.5f,  0.5f,  0.5f)},
            SimplexVertex{Vector3f( 0.5f, -0.5f,  0.5f)},
            SimplexVertex{Vector3f(-0.5f, -0.5f,  0.5f)},
            SimplexVertex{Vector3f(-0.5f,  0.5f, -0.5f)},
            SimplexVertex{Vector3f( 0.5f,  0.5f, -0.5f)},
            SimplexVertex{Vector3f( 0.5f, -0.5f, -0.5f)},
            SimplexVertex{Vector3f(-0.5f, -0.5f, -0.5f)}
          },
          Vector<uint16>
          {
            0u, 1u, 2u, 
            0u, 2u, 3u,
            
            1u, 5u, 6u,
            1u, 6u, 2u,

            5u, 4u, 7u,
            5u, 7u, 6u,

            4u, 0u, 3u,
            4u, 3u, 7u,

            4u, 5u, 1u,
            4u, 1u, 0u,

            3u, 2u, 6u,
            3u, 6u, 7u
          },
          "TestCubeMesh1"
        )
      },
      "TestCube"
    ),
    Vector3f(0.5f, 0.0f, 0.0f),
    Quaternion(Vector3f(0.0f, 0.0f, 0.0f)),
    Vector3f(0.5f, 0.5f, 0.5f)
  );

  return true;
}

void BaseAppTest1::update(float deltaTime)
{
  static Quaternion rot(Vector3f(0.0f, 0.0f, 0.0f));
  rot = Quaternion((rot.getEuclidean() + Vector3f(deltaTime, 0.0f, deltaTime)));
  m_cube->setRotation(rot);
}

void BaseAppTest1::render()
{
  GraphicsApi::instance().clearScreen(1.0f, 0.0f, 1.0f);

  GraphicsApi::instance().drawObject(m_triangle);
  GraphicsApi::instance().drawObject(m_cube);

  GraphicsApi::instance().present();
}

void BaseAppTest1::destroy()
{
}
