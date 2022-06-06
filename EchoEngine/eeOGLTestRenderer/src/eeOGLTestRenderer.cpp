#include "eeOGLTestRenderer.h"

#include <eeGraficsApi.h>
#include <eeResourceManager.h>
#include <eeSceneManager.h>
#include <eeLogger.h>

#include <eeActor.h>
#include <eeCCamera.h>
#include <eeCLight.h>
#include <eeCSkeletalMesh.h>
#include <eeCStaticMesh.h>
#include <eeCTransform.h>

#include <eeStaticMesh.h>
#include <eeSkeletalMesh.h>
#include <eeSkeletal.h>

#include <eeMaterial.h>

//#include <eeMath.h>

#include <eeColor.h>
#include <eeVertex.h>

#include <eeImage.h>

namespace eeEngineSDK {
OGLTestRenderer::OGLTestRenderer()
{
  static auto& graphicsApi = GraphicsApi::instance();
  static auto& resourceManager = ResourceManager::instance();
  static auto& memoryManager = MemoryManager::instance();
  
  
  //const uint32 screenWidth = graphicsApi.getMainWindow()->getWidth();
  //const uint32 screenHeight = graphicsApi.getMainWindow()->getHeight();
  
  Vector<ComplexVertex> vertices = {
    ComplexVertex
    { 
      Vector4f{ 0.5f,  0.5f, 0.0f, 1.0f},
      Vector4f{ 1.0f,  1.0f, 0.0f, 0.0f},
      Vector4f{ 0.0f,  0.0f, 0.0f, 0.0f},
      Vector4f{ 0.0f,  0.0f, 0.0f, 0.0f},
      Vector4f{ 0.0f,  0.0f, 0.0f, 0.0f}
    },
    ComplexVertex
    { 
      Vector4f{ 0.5f, -0.5f, 0.0f, 1.0f},
      Vector4f{ 1.0f,  0.0f, 0.0f, 0.0f},
      Vector4f{ 0.0f,  0.0f, 0.0f, 0.0f},
      Vector4f{ 0.0f,  0.0f, 0.0f, 0.0f},
      Vector4f{ 0.0f,  0.0f, 0.0f, 0.0f}
    },
    ComplexVertex
    { 
      Vector4f{-0.5f, -0.5f, 0.0f, 1.0f},
      Vector4f{ 0.0f,  0.0f, 0.0f, 0.0f},
      Vector4f{ 0.0f,  0.0f, 0.0f, 0.0f},
      Vector4f{ 0.0f,  0.0f, 0.0f, 0.0f},
      Vector4f{ 0.0f,  0.0f, 0.0f, 0.0f}
    },
    ComplexVertex
    { 
      Vector4f{-0.5f,  0.5f, 0.0f, 1.0f},
      Vector4f{ 0.0f,  1.0f, 0.0f, 0.0f},
      Vector4f{ 0.0f,  0.0f, 0.0f, 0.0f},
      Vector4f{ 0.0f,  0.0f, 0.0f, 0.0f},
      Vector4f{ 0.0f,  0.0f, 0.0f, 0.0f}
    }
  };
  Vector<uint32> indices =
  {
      0, 1, 3,
      1, 2, 3
  };
  
  m_testMesh.loadFromVertexArray(vertices, indices);
  vertices.clear();
  indices.clear();


  m_samLinear = graphicsApi.createSamplerStatePtr();
  m_samLinear->create(eSAMPLER_FILTER::kMinMagMipPoint);
  
  
  resourceManager.loadVertexShaderFromFile("D:/GitHub/MotoresIDV7_EchoEngine/EchoEngine/bin/Shaders/OGLTestShaderVS.glsl",
                                           "TestVS");
  resourceManager.loadPixelShaderFromFile("D:/GitHub/MotoresIDV7_EchoEngine/EchoEngine/bin/Shaders/OGLTestShaderPS.glsl",
                                          "TestPS");



  resourceManager.loadTextureFromFile("D:/GitHub/MotoresIDV7_EchoEngine/EchoEngine/bin/Textures/steve.png",
                                      "TestTexture");
}
void
OGLTestRenderer::onUpdate(float deltaTime)
{
  //m_testTexture->generateMipmaps();
}
void
OGLTestRenderer::onRender()
{
  auto& graphicsApi = GraphicsApi::instance();
  auto& resourceManager = ResourceManager::instance();
  auto& sceneManager = SceneManager::instance();

  m_samLinear->use();

  graphicsApi.setShaderPrograms(resourceManager.getResourceVertexShader("TestVS"),
                                resourceManager.getResourcePixelShader("TestPS"));

  graphicsApi.setTextures({ resourceManager.getResourceTexture("TestTexture") }, 0);

  graphicsApi.drawMesh(m_testMesh);
}



EE_EXTERN EE_PLUGIN_EXPORT void
initPlugin()
{
  Renderer::startUp<OGLTestRenderer>();
}
}