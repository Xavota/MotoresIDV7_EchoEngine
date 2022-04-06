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


  /* Load resources */
  m_samplerLinear = graphicsApi.createSamplerStatePtr();
  m_samplerLinear->create(eFILTER::kMIN_MAG_MIP_LINEAR,
                          eTEXTURE_ADDRESS_MODE::kWrap,
                          eTEXTURE_ADDRESS_MODE::kWrap,
                          eTEXTURE_ADDRESS_MODE::kWrap);
  
  m_solidCCWRasterizer = graphicsApi.createRasterizerStatePtr();
  m_solidCCWRasterizer->create(eeEngineSDK::eFILL_MODE::kSolid,
                               eeEngineSDK::eCULL_MODE::kFront,
                               true);
  
  m_rasterizer2 = graphicsApi.createRasterizerStatePtr();
  m_rasterizer2->create(eeEngineSDK::eFILL_MODE::kSolid,
                        eeEngineSDK::eCULL_MODE::kFront,
                        true);


  /* Load render targets and depth stencils */
  m_GBufferDepthStencil = graphicsApi.createTexturePtr();
  m_GBufferDepthStencil->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kDepthStencil,
                                  Point2D{ screenWidth, screenHeight });

  m_GBufferPositionTexture = graphicsApi.createTexturePtr();
  m_GBufferPositionTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                                   | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                                     Point2D{ screenWidth, screenHeight },
                                     eTEXTURE_FORMAT::kR16G16B16A16_Float);

  m_GBufferColorTexture = graphicsApi.createTexturePtr();
  m_GBufferColorTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                                | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                                  Point2D{ screenWidth, screenHeight },
                                  eTEXTURE_FORMAT::kR8G8B8A8_Unorm);

  m_GBufferNormalTexture = graphicsApi.createTexturePtr();
  m_GBufferNormalTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                                 | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                                   Point2D{ screenWidth, screenHeight },
                                   eTEXTURE_FORMAT::kR8G8B8A8_Unorm);
                                   
  m_SSAOTexture = graphicsApi.createTexturePtr();
  m_SSAOTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                        | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                          Point2D{ screenWidth, screenHeight },
                          eTEXTURE_FORMAT::kR16_Float);
                                 
  m_lightShaderTexture = graphicsApi.createTexturePtr();
  m_lightShaderTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                               | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                                 Point2D{ screenWidth, screenHeight });


  m_HDRLuminanceTexture = graphicsApi.createTexturePtr();
  m_HDRLuminanceTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                                | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                                  Point2D{ 512, 512 },
                                  eTEXTURE_FORMAT::kR16_Float);


  /* Load shaders */
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

  resourceManager.loadVertexShaderFromFile("Shaders/HDRLuminanceVS.hlsl",
                                           "HDRLuminanceVS");
  resourceManager.loadPixelShaderFromFile("Shaders/HDRLuminancePS.hlsl",
                                          "HDRLuminancePS");
                                          
  resourceManager.loadVertexShaderFromFile("Shaders/SAQVS.hlsl",
                                           "SAQVS");
  resourceManager.loadPixelShaderFromFile("Shaders/SAQPS.hlsl",
                                          "SAQPS");


  /* Load constant buffers */
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
  Vector<float> vieportRect =
  {
    512.0f, // viewport width
    512.0f, // viewport height
    static_cast<float>(screenWidth), // screen width
    static_cast<float>(screenHeight) // screen height
  };
  m_viewportRectDataBuffer = graphicsApi.createConstantBufferPtr();
  m_viewportRectDataBuffer->initData(sizeof(float) * 4, sizeof(float) * 2,
                                     reinterpret_cast<Byte*>(vieportRect.data()));
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
  Vector<Pair<BoneMesh, SPtr<Material>>> boneMeshes;
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

  for (const auto& act : rActors) {
    SPtr<CSkeletalMesh> skMesh = act->getComponent<CSkeletalMesh>();
   
    const SPtr<SkeletalMesh> skModel = skMesh->getModel();
    if (skMesh && skModel) {
      boneMeshes = skModel->getMeshes();
      meshesCount = boneMeshes.size();


      // Set model buffer
      SPtr<CTransform> transform = act->getTransform();
      Matrix4f modelMatrix = transform->getModelMatrix();
      m_modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMatrix));
      graphicsApi.setVSConstantBuffers({ m_modelMatrixBuff }, 0u);


      // Set textures
      Vector<SPtr<Texture>> texs;
      Map<uint32, SPtr<Texture>> texturesMap;
      const SPtr<Skeletal> skeleton = skModel->getSkeletal();
      for (SIZE_T j = 0; j < meshesCount; ++j) {
        texturesMap = boneMeshes[j].second->getTexturesMap();
   
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
        graphicsApi.drawMesh(boneMeshes[j].first);


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

  for (const auto& act : rActors) {
    const SPtr<CStaticMesh> staticMesh = act->getComponent<CStaticMesh>();
    if (staticMesh
     && staticMesh->getMobilityType() != eMOBILITY_TYPE::kStatic
     && staticMesh->getStaticMesh()) {
      meshes = staticMesh->getStaticMesh()->getMeshes();
      meshesCount = meshes.size();


      // Set model buffer
      SPtr<CTransform> transform = act->getTransform();
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

  Vector<SPtr<StaticMesh>> partitionMeshes;
  sceneManager.getPartitionedSceneMeshes(partitionMeshes);
  
  for (const auto& staticMesh : partitionMeshes) {
    meshes = staticMesh->getMeshes();
    meshesCount = meshes.size();
  
    // Set model buffer
    Matrix4f modelMatrix = Matrix4f::kIDENTITY;
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
  // Unbind buffers
  graphicsApi.unsetVSConstantBuffers(2u, 1u);


  /* SSAO */

  // Clear and set render targets
  graphicsApi.clearRenderTargets({ m_SSAOTexture }, color);
  graphicsApi.setRenderTargets({ m_SSAOTexture }, nullptr);
  
   
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
  graphicsApi.clearRenderTargets({ m_lightShaderTexture }, color);
  graphicsApi.setRenderTargets({ m_lightShaderTexture }, nullptr);
  
  
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
                            m_SSAOTexture },
                          0u);
  
  
  // Draw using a SAQ
  graphicsApi.drawOnSAQ();
  
  
  // Unbind buffers
  graphicsApi.unsetRenderTargets();
  graphicsApi.unsetVSConstantBuffers(1u, 0u);
  graphicsApi.unsetTextures(4u, 0u);


  /* HDR Luminance */
  

  ViewportDesc vp(512.0f, 512.0f);
  graphicsApi.setViewports({ vp });

  // Clear and set render targets
  graphicsApi.setRenderTargets({ m_HDRLuminanceTexture }, nullptr);
  graphicsApi.clearRenderTargets({ m_HDRLuminanceTexture }, color);
  
  // Set constant buffers
  graphicsApi.setVSConstantBuffers
  ({ m_viewportRectDataBuffer }, 0u );
  
  // Load shaders
  resourceManager.getResourceVertexShader("HDRLuminanceVS")->use();
  resourceManager.getResourcePixelShader("HDRLuminancePS")->use();


  // Set textures
  //graphicsApi.setTextures({ resourceManager.getResourceTexture("DefaultDiffuse") },
  graphicsApi.setTextures({ m_lightShaderTexture },
                          0u);


  // Draw using a SAQ
  m_samplerLinear->use();
  graphicsApi.drawOnSAQ();
  
  
  // Unbind buffers
  graphicsApi.unsetRenderTargets();
  graphicsApi.unsetVSConstantBuffers(1u, 0u);
  graphicsApi.unsetTextures(1u, 0u);


  /* Copy */

  vp.height = screenHeight;
  vp.width = screenWidth;
  graphicsApi.setViewports({ vp });

  // Set Back Buffer
  SPtr<Window> mainWin = graphicsApi.getMainWindow();
  graphicsApi.clearRenderTargets({ mainWin->getRenderTarget() }, color);
  graphicsApi.setRenderTargets({ mainWin->getRenderTarget() }, nullptr);


  // Load shaders
  resourceManager.getResourceVertexShader("SAQVS")->use();
  resourceManager.getResourcePixelShader("SAQPS")->use();


  // Set textures
  graphicsApi.setTextures({ m_lightShaderTexture },
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