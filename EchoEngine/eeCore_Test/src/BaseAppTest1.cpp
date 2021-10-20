#include "BaseAppTest1.h"
#include <eeGraficsApi.h>
#include <eeResourceManager.h>
#include <eeObject.h>

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
            SimplexVertex{Vector3f(-0.5f, 0.0f, 0.0f)},
            SimplexVertex{Vector3f(0.0f, 0.5f, 0.0f)},
            SimplexVertex{Vector3f(0.5f, 0.0f, 0.0f)}
          },
          Vector<uint16>
          {
            0u,
            1u,
            2u
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

  return false;
}

void BaseAppTest1::update(float deltaTime)
{
}

void BaseAppTest1::render()
{
  GraphicsApi::instance().clearScreen(0.0f, 0.0f, 0.0f);

  GraphicsApi::instance().drawObject(m_triangle);

  GraphicsApi::instance().present();
}

void BaseAppTest1::destroy()
{
}
