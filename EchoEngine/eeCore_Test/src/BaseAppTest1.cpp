#include "BaseAppTest1.h"
#include <eeGraficsApi.h>
#include <eeResourceManager.h>
#include <eeObject.h>

#include <eeMath.h>

using eeEngineSDK::GraphicsApi;
using eeEngineSDK::ResourceManager;
using eeEngineSDK::Vector4f;
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
            SimplexVertex{Vector4f(-1.0f ,  0.5f,  0.0f, 0.0f)},
            SimplexVertex{Vector4f(-0.01f,  0.5f,  0.0f, 0.0f)},
            SimplexVertex{Vector4f(-0.01f, -0.5f,  0.0f, 0.0f)}
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
            SimplexVertex{Vector4f(-1.0f,  1.0f, -1.0f, 1.0f)},
            SimplexVertex{Vector4f( 1.0f,  1.0f, -1.0f, 1.0f)},
            SimplexVertex{Vector4f( 1.0f,  1.0f,  1.0f, 1.0f)},
            SimplexVertex{Vector4f(-1.0f,  1.0f,  1.0f, 1.0f)},

            SimplexVertex{Vector4f(-1.0f, -1.0f, -1.0f, 1.0f)},
            SimplexVertex{Vector4f( 1.0f, -1.0f, -1.0f, 1.0f)},
            SimplexVertex{Vector4f( 1.0f, -1.0f,  1.0f, 1.0f)},
            SimplexVertex{Vector4f(-1.0f, -1.0f,  1.0f, 1.0f)},

            SimplexVertex{Vector4f(-1.0f, -1.0f,  1.0f, 1.0f)},
            SimplexVertex{Vector4f(-1.0f, -1.0f, -1.0f, 1.0f)},
            SimplexVertex{Vector4f(-1.0f,  1.0f, -1.0f, 1.0f)},
            SimplexVertex{Vector4f(-1.0f,  1.0f,  1.0f, 1.0f)},

            SimplexVertex{Vector4f( 1.0f, -1.0f,  1.0f, 1.0f)},
            SimplexVertex{Vector4f( 1.0f, -1.0f, -1.0f, 1.0f)},
            SimplexVertex{Vector4f( 1.0f,  1.0f, -1.0f, 1.0f)},
            SimplexVertex{Vector4f( 1.0f,  1.0f,  1.0f, 1.0f)},

            SimplexVertex{Vector4f(-1.0f, -1.0f, -1.0f, 1.0f)},
            SimplexVertex{Vector4f( 1.0f, -1.0f, -1.0f, 1.0f)},
            SimplexVertex{Vector4f( 1.0f,  1.0f, -1.0f, 1.0f)},
            SimplexVertex{Vector4f(-1.0f,  1.0f, -1.0f, 1.0f)},

            SimplexVertex{Vector4f(-1.0f, -1.0f,  1.0f, 1.0f)},
            SimplexVertex{Vector4f( 1.0f, -1.0f,  1.0f, 1.0f)},
            SimplexVertex{Vector4f( 1.0f,  1.0f,  1.0f, 1.0f)},
            SimplexVertex{Vector4f(-1.0f,  1.0f,  1.0f, 1.0f)}
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
        )
      },
      "TestCube"
    ),
    Vector3f(0.0f, 0.0f, 0.0f),
    Quaternion(Vector3f(0.0f, 0.0f, 0.0f)),
    Vector3f(1.0f, 1.0f, 1.0f)
  );

  return true;
}

void BaseAppTest1::update(float deltaTime)
{
  static Quaternion rot(Vector3f(0.0f, 0.0f, 0.0f));
  rot = Quaternion((rot.getEuclidean() + Vector3f(deltaTime, 0.0f, 0.0f)));
  m_cube->setRotation(rot);
}

void BaseAppTest1::render()
{
  GraphicsApi::instance().clearScreen(1.0f, 0.0f, 1.0f);

  //GraphicsApi::instance().drawObject(m_triangle);
  GraphicsApi::instance().drawObject(m_cube);

  GraphicsApi::instance().present();
}

void BaseAppTest1::destroy()
{
}
