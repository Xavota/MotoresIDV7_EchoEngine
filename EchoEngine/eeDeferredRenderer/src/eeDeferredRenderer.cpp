#include "eeDeferredRenderer.h"

#include <eeGraficsApi.h>
#include <eeResourceManager.h>
#include <eeSceneManager.h>
#include <eeLogger.h>

#include <eeActor.h>
#include <eeCTransform.h>
#include <eeCCamera.h>
#include <eeCStaticMesh.h>
#include <eeCSkeletalMesh.h>

#include <eeStaticMesh.h>
#include <eeSkeletalMesh.h>
#include <eeSkeletal.h>

#include <eeMaterial.h>

#include <eeMath.h>

#include <eeColor.h>
#include <eeVertex.h>

namespace eeEngineSDK {
DeferredRenderer::DeferredRenderer()
{
  auto& graphicsApi = GraphicsApi::instance();
  auto& resourceManager = ResourceManager::instance();
  auto& memoryManager = MemoryManager::instance();


  m_samplerLinear = memoryManager.newPtr<SamplerState>();
  m_samplerLinear->create(eFILTER::kMIN_MAG_MIP_LINEAR,
                          eTEXTURE_ADDRESS_MODE::kWrap,
                          eTEXTURE_ADDRESS_MODE::kWrap,
                          eTEXTURE_ADDRESS_MODE::kWrap);

  
  
  resourceManager.loadVertexShaderFromFile("Shaders/TestVSSAQ.hlsl",
                                           "TestSAQVS");
  resourceManager.loadPixelShaderFromFile("Shaders/TestPSSAQ.hlsl",
                                          "TestSAQPS");


  m_modelMatrixBuff = GraphicsApi::instance().createConstantBufferPtr();
  m_modelMatrixBuff->initData(sizeof(Matrix4f), sizeof(Matrix4f), nullptr);
  m_viewMatrixBuffer = graphicsApi.createConstantBufferPtr();
  m_viewMatrixBuffer->initData(sizeof(Matrix4f), sizeof(Matrix4f), nullptr);
  m_projectionMatrixBuffer = graphicsApi.createConstantBufferPtr();
  m_projectionMatrixBuffer->initData(sizeof(Matrix4f), sizeof(Matrix4f), nullptr);
  m_viewPosBuffer = graphicsApi.createConstantBufferPtr();
  m_viewPosBuffer->initData(sizeof(Vector4f), sizeof(Vector4f), nullptr);
  m_bonesBuffer = graphicsApi.createConstantBufferPtr();
  m_bonesBuffer->initData(100 * sizeof(Matrix4f), sizeof(Matrix4f), nullptr);
  Vector<float> ssaoData =
  {
    1.0f, // sample_rad
    2.0f, // intensity
    0.01f, // scale
    0.08f // bias
  };
  m_ssaoDataBuffer = graphicsApi.createConstantBufferPtr();
  m_ssaoDataBuffer->initData(sizeof(float) * 4, sizeof(float),
                             reinterpret_cast<Byte*>(ssaoData.data()));
  
  
  RasteraizerDesc rasDesc;
  memset(&rasDesc, 0, sizeof(rasDesc));
  rasDesc.cullMode = eeEngineSDK::eCULL_MODE::kFront;
  rasDesc.fillMode = eeEngineSDK::eFILL_MODE::kSolid;
  rasDesc.frontCounterClockwise = true;
  
  m_solidCCWRasterizer = graphicsApi.createRasterizerStatePtr();
  m_solidCCWRasterizer->create(rasDesc);
  
  
  memset(&rasDesc, 0, sizeof(rasDesc));
  rasDesc.cullMode = eeEngineSDK::eCULL_MODE::kFront;
  rasDesc.fillMode = eeEngineSDK::eFILL_MODE::kSolid;
  rasDesc.frontCounterClockwise = true;
  
  m_rasterizer2 = graphicsApi.createRasterizerStatePtr();
  m_rasterizer2->create(rasDesc);






  
  /* GBuffer Resources */
  
  resourceManager.loadVertexShaderFromFile("Shaders/GBufferVS.hlsl",
                                           "GBufferVS");
  resourceManager.loadPixelShaderFromFile("Shaders/GBufferPS.hlsl",
                                          "GBufferPS");

  resourceManager.loadVertexShaderFromFile("Shaders/GBufferVSAnim.hlsl",
                                           "GBufferVSAnim");
  resourceManager.loadPixelShaderFromFile("Shaders/GBufferPSAnim.hlsl",
                                          "GBufferPSAnim");

  resourceManager.loadVertexShaderFromFile("Shaders/LightsVS.hlsl",
                                           "LightsVS");
  resourceManager.loadPixelShaderFromFile("Shaders/LightsPS.hlsl",
                                          "LightsPS");

  resourceManager.loadVertexShaderFromFile("Shaders/SSAOVS.hlsl",
                                           "SSAOVS");
  resourceManager.loadPixelShaderFromFile("Shaders/SSAOPS.hlsl",
                                          "SSAOPS");

  m_GBufferDepthStencil = GraphicsApi::instance().createTexturePtr();
  m_GBufferDepthStencil->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kDepthStencil,
                                  Point2D{ screenWidth, screenHeight });

  m_GBufferPositionTexture = GraphicsApi::instance().createTexturePtr();
  m_GBufferPositionTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                                   | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                                     Point2D{ screenWidth, screenHeight },
                                     eTEXTURE_FORMAT::kR16G16B16A16_Float);

  m_GBufferColorTexture = GraphicsApi::instance().createTexturePtr();
  m_GBufferColorTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                                | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                                  Point2D{ screenWidth, screenHeight },
                                  eTEXTURE_FORMAT::kR8G8B8A8_Unorm);

  m_GBufferNormalTexture = GraphicsApi::instance().createTexturePtr();
  m_GBufferNormalTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                                 | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                                   Point2D{ screenWidth, screenHeight },
                                   eTEXTURE_FORMAT::kR8G8B8A8_Unorm);
                                   
  m_GBufferSSAOTexture = GraphicsApi::instance().createTexturePtr();
  m_GBufferSSAOTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                               | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                                 Point2D{ screenWidth, screenHeight },
                                 eTEXTURE_FORMAT::kR16_Float);


  /* Lights Resources */
  

  m_copyShaderRenderTarget = GraphicsApi::instance().createTexturePtr();
  m_copyShaderRenderTarget->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                  Point2D{ screenWidth, screenHeight });
}
void
DeferredRenderer::onUpdate(float /*deltaTime*/)
{
}
void
DeferredRenderer::onRender()
{
  auto& graphicsApi = GraphicsApi::instance();
  auto& resourceManager = ResourceManager::instance();
  auto& sceneManager = SceneManager::instance();


  Vector<Pair<Mesh, SPtr<Material>>> meshes;
  SIZE_T meshesCount = 0;

  Color color{ 0.0f, 0.0f, 0.0f, 1.0f };


  // Get main camera
  Vector<SPtr<CCamera>> activeCams = graphicsApi.getActiveCameras();
  SPtr<CCamera> mainCam = nullptr;
  for (auto& cam : activeCams) {
    if (cam->isMain()) {
      mainCam = cam;
    }
  }


  // Updates buffers
  if (mainCam) {
    Vector3f pos = mainCam->getActor()->getTransform()->getPosition();
    Vector4f vp = Vector4f(pos.x, pos.y, pos.z, 1.0f);
    m_viewPosBuffer->updateData(reinterpret_cast<Byte*>(&vp));

    // Create view/proj matrices
    Matrix4f view = Matrix4f::kIDENTITY;
    view = mainCam->getViewMatrix().getTranspose();
    m_viewMatrixBuffer->updateData(reinterpret_cast<Byte*>(&view));

    Matrix4f proj = Matrix4f::kIDENTITY;
    proj = mainCam->getProjectionMatrix().getTranspose();
    m_projectionMatrixBuffer->updateData(reinterpret_cast<Byte*>(&proj));
  }
  else {
    Vector4f vp = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
    m_viewPosBuffer->updateData(reinterpret_cast<Byte*>(&vp));

    // Create view/proj matrices
    Matrix4f view = Matrix4f::kIDENTITY;
    m_viewMatrixBuffer->updateData(reinterpret_cast<Byte*>(&view));

    Matrix4f proj = Matrix4f::kIDENTITY;
    m_projectionMatrixBuffer->updateData(reinterpret_cast<Byte*>(&proj));
  }


  // Load resources

  m_samplerLinear->use();


  /* GBuffer */

  // Set rasterizer
  m_solidCCWRasterizer->use();

  // Clear and set render targets
  graphicsApi.clearRenderTargets({ m_GBufferPositionTexture,
                                   m_GBufferColorTexture,
                                   m_GBufferNormalTexture },
                                 Color(0.5f, 0.5f, 0.5f, 1.0f));
  graphicsApi.cleanDepthStencils({ m_GBufferDepthStencil });
  graphicsApi.setRenderTargets({ m_GBufferPositionTexture,
                                 m_GBufferColorTexture,
                                 m_GBufferNormalTexture },
                               m_GBufferDepthStencil);


  // Load shaders
  resourceManager.getResourceVertexShader("GBufferVSAnim")->use();
  resourceManager.getResourcePixelShader("GBufferPSAnim")->use();


  // Set constant buffers
  graphicsApi.setVSConstantBuffers
  (
    { m_viewMatrixBuffer, m_projectionMatrixBuffer },
    1u
  );


  // Draw in-cam actors with skeletal mesh
  Vector<SPtr<Actor>> rActors =
  sceneManager.getAllRenderableActorsInside(activeCams[0],
                                            RENDER_ACTOR_FLAGS::kSkeletalMesh);
  SIZE_T rActorsCount = rActors.size();

  for (SIZE_T i = 0; i < rActorsCount; ++i) {
    SPtr<CSkeletalMesh> skMesh = rActors[i]->getComponent<CSkeletalMesh>();
   
    const SPtr<SkeletalMesh> skModel = skMesh->getModel();
    if (skMesh && skModel) {
      meshes = skModel->getMeshes();
      meshesCount = meshes.size();


      // Set model buffer
      SPtr<CTransform> transform = rActors[i]->getTransform();
      Matrix4f modelMatrix = transform->getModelMatrix();
      m_modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMatrix));
      graphicsApi.setVSConstantBuffers({ m_modelMatrixBuff }, 0u);


      // Set textures
      Vector<SPtr<Texture>> texs;
      Map<uint32, SPtr<Texture>> texturesMap;
      const SPtr<Skeletal> skeleton = skModel->getSkeletal();
      for (SIZE_T j = 0; j < meshesCount; ++j) {
        texturesMap = meshes[j].second->getTexturesMap();
   
        if (texturesMap.find(TEXTURE_TYPE_INDEX::kDiffuse) != texturesMap.end()) {
          texs.push_back(texturesMap.find(TEXTURE_TYPE_INDEX::kDiffuse)->second);
        }
        else {
          texs.push_back(resourceManager.getResourceTexture("DefaultDiffuse"));
        }
        if (texturesMap.find(TEXTURE_TYPE_INDEX::kNormal) != texturesMap.end()) {
          texs.push_back(texturesMap.find(TEXTURE_TYPE_INDEX::kNormal)->second);
        }
        else {
          texs.push_back(resourceManager.getResourceTexture("DefaultNormalMap"));
        }
        graphicsApi.setTextures(texs, 0u);
   
        if (skeleton) {
          Vector<Matrix4f> mats = skeleton->getBonesMatrices(j);
          m_bonesBuffer->updateData(reinterpret_cast<Byte*>(mats.data()));
          graphicsApi.setVSConstantBuffers({ m_bonesBuffer }, 3u);
        }


        // Draw mesh
        graphicsApi.drawMesh(meshes[j].first);


        // Unbind buffers
        graphicsApi.unsetTextures(static_cast<uint32>(texs.size()), 0u);
        texs.clear();
        if (skeleton) {
          graphicsApi.unsetVSConstantBuffers(1u, 3u);
        }
      }
      // Unbind buffers
      graphicsApi.unsetVSConstantBuffers(1u, 0u);
    }
  }


  // Load shaders
  resourceManager.getResourceVertexShader("GBufferVS")->use();
  resourceManager.getResourcePixelShader("GBufferPS")->use();


  // Draw in-cam actors with static mesh
  rActors =
  sceneManager.getAllRenderableActorsInside(activeCams[0],
                                            RENDER_ACTOR_FLAGS::kStaticMesh);
  rActorsCount = rActors.size();

  for (SIZE_T i = 0; i < rActorsCount; ++i) {
    const SPtr<CStaticMesh> staticMesh = rActors[i]->getComponent<CStaticMesh>();
    if (staticMesh && staticMesh->getStaticMesh()) {
      meshes = staticMesh->getStaticMesh()->getMeshes();
      meshesCount = meshes.size();


      // Set model buffer
      SPtr<CTransform> transform = rActors[i]->getTransform();
      Matrix4f modelMatrix = transform->getModelMatrix();
      m_modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMatrix));
      graphicsApi.setVSConstantBuffers({ m_modelMatrixBuff }, 0u);


      // Set textures
      Vector<SPtr<Texture>> texs;
      Map<uint32, SPtr<Texture>> texturesMap;
      for (SIZE_T j = 0; j < meshesCount; ++j) {
        texturesMap = meshes[j].second->getTexturesMap();

        if (texturesMap.find(TEXTURE_TYPE_INDEX::kDiffuse) != texturesMap.end()) {
          texs.push_back(texturesMap.find(TEXTURE_TYPE_INDEX::kDiffuse)->second);
        }
        else {
          texs.push_back(resourceManager.getResourceTexture("DefaultDiffuse"));
        }
        if (texturesMap.find(TEXTURE_TYPE_INDEX::kNormal) != texturesMap.end()) {
          texs.push_back(texturesMap.find(TEXTURE_TYPE_INDEX::kNormal)->second);
        }
        else {
          texs.push_back(resourceManager.getResourceTexture("DefaultNormalMap"));
        }
        graphicsApi.setTextures(texs, 0u);


        // Draw mesh
        graphicsApi.drawMesh(meshes[j].first);


        // Unbind buffers
        graphicsApi.unsetTextures(static_cast<uint32>(texs.size()), 0u);
        texs.clear();
      }
      // Unbind buffers
      graphicsApi.unsetVSConstantBuffers(1u, 0u);
    }
  }
  // Unbind buffers
  graphicsApi.unsetVSConstantBuffers(2u, 1u);


  /* SSAO */

  // Clear and set render targets
  graphicsApi.clearRenderTargets({ m_GBufferSSAOTexture }, color);
  graphicsApi.setRenderTargets({ m_GBufferSSAOTexture }, nullptr);
  
   
  // Set constant buffers
  graphicsApi.setPSConstantBuffers
  ({ m_ssaoDataBuffer }, 0u );


  // Load shaders
  resourceManager.getResourceVertexShader("SSAOVS")->use();
  resourceManager.getResourcePixelShader("SSAOPS")->use();


  // Set textures
  graphicsApi.setTextures({ m_GBufferPositionTexture,
                            m_GBufferNormalTexture },
                          0u);


  // Draw using a SAQ
  graphicsApi.drawOnSAQ();


  // Unbind buffers
  graphicsApi.unsetRenderTargets();
  graphicsApi.unsetPSConstantBuffers(1u, 0u);
  graphicsApi.unsetTextures(2u, 0u);


  /* Lights */
  
  // Clear and set render targets
  graphicsApi.clearRenderTargets({ m_copyShaderRenderTarget }, color);
  graphicsApi.setRenderTargets({ m_copyShaderRenderTarget }, nullptr);
  
  
  // Set constant buffers
  graphicsApi.setVSConstantBuffers
  ({ m_viewPosBuffer }, 0u );
  
  
  // Load shaders
  resourceManager.getResourceVertexShader("LightsVS")->use();
  resourceManager.getResourcePixelShader("LightsPS")->use();


  // Set textures
  graphicsApi.setTextures({ m_GBufferPositionTexture,
                            m_GBufferColorTexture,
                            m_GBufferNormalTexture,
                            m_GBufferSSAOTexture },
                          0u);
  
  
  // Draw using a SAQ
  graphicsApi.drawOnSAQ();
  
  
  // Unbind buffers
  graphicsApi.unsetRenderTargets();
  graphicsApi.unsetVSConstantBuffers(1u, 0u);
  graphicsApi.unsetTextures(4u, 0u);


  /* Copy */

  // Set Back Buffer
  SPtr<Window> mainWin = graphicsApi.getMainWindow();
  graphicsApi.clearRenderTargets({ mainWin->getRenderTarget() }, color);
  graphicsApi.setRenderTargets({ mainWin->getRenderTarget() }, nullptr);


  // Load shaders
  resourceManager.getResourceVertexShader("TestSAQVS")->use();
  resourceManager.getResourcePixelShader("TestSAQPS")->use();


  // Set textures
  graphicsApi.setTextures({ m_copyShaderRenderTarget },
                          0u);


  // Draw using a SAQ
  m_rasterizer2->use();
  graphicsApi.drawOnSAQ();


  // Unbind buffers
  graphicsApi.unsetRenderTargets();
  graphicsApi.unsetTextures(1u, 0u);
}



EE_EXTERN EE_PLUGIN_EXPORT void
initPlugin()
{
  Renderer::startUp<DeferredRenderer>();
}
}