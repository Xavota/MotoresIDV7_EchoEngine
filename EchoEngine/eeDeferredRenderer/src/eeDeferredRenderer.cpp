#include "eeDeferredRenderer.h"

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

namespace eeEngineSDK {
DeferredRenderer::DeferredRenderer()
{
  auto& graphicsApi = GraphicsApi::instance();
  auto& resourceManager = ResourceManager::instance();
  //auto& memoryManager = MemoryManager::instance();

  
  const uint32 screenWidth = graphicsApi.getMainWindow()->getWidth();
  const uint32 screenHeight = graphicsApi.getMainWindow()->getHeight();

  /* Load resources */
  m_samplerLinear = graphicsApi.createSamplerStatePtr();
  m_samplerLinear->create(eSAMPLER_FILTER::kMinMagMipLinear,
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
                                 
  m_diffLightsTexture = graphicsApi.createTexturePtr();
  m_diffLightsTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                              | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                                Point2D{ screenWidth, screenHeight },
                                eTEXTURE_FORMAT::kR8G8B8A8_Unorm);
  m_tempDiffLightsTexture = graphicsApi.createTexturePtr();
  m_tempDiffLightsTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                                  | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                                    Point2D{ screenWidth, screenHeight },
                                    eTEXTURE_FORMAT::kR8G8B8A8_Unorm);
  m_specLightsTexture = graphicsApi.createTexturePtr();
  m_specLightsTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                              | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                                Point2D{ screenWidth, screenHeight },
                                eTEXTURE_FORMAT::kR8G8B8A8_Unorm);
  m_tempSpecLightsTexture = graphicsApi.createTexturePtr();
  m_tempSpecLightsTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                                  | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                                    Point2D{ screenWidth, screenHeight },
                                    eTEXTURE_FORMAT::kR8G8B8A8_Unorm);
  m_lightTexture = graphicsApi.createTexturePtr();
  m_lightTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                         | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                           Point2D{ screenWidth, screenHeight },
                           eTEXTURE_FORMAT::kR8G8B8A8_Unorm);


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

  resourceManager.loadVertexShaderFromFile("Shaders/DirectionalDiffuseLightsVS.hlsl",
                                           "DirectionalDiffuseLightsVS");
  resourceManager.loadPixelShaderFromFile("Shaders/DirectionalDiffuseLightsPS.hlsl",
                                          "DirectionalDiffuseLightsPS");
  resourceManager.loadVertexShaderFromFile("Shaders/DirectionalSpecularLightsVS.hlsl",
                                           "DirectionalSpecularLightsVS");
  resourceManager.loadPixelShaderFromFile("Shaders/DirectionalSpecularLightsPS.hlsl",
                                          "DirectionalSpecularLightsPS");
  resourceManager.loadVertexShaderFromFile("Shaders/PointDiffuseLightsVS.hlsl",
                                           "PointDiffuseLightsVS");
  resourceManager.loadPixelShaderFromFile("Shaders/PointDiffuseLightsPS.hlsl",
                                          "PointDiffuseLightsPS");
  resourceManager.loadVertexShaderFromFile("Shaders/PointSpecularLightsVS.hlsl",
                                           "PointSpecularLightsVS");
  resourceManager.loadPixelShaderFromFile("Shaders/PointSpecularLightsPS.hlsl",
                                          "PointSpecularLightsPS");
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
                                          
  resourceManager.loadVertexShaderFromFile("Shaders/CopyVS.hlsl",
                                           "CopyVS");
  resourceManager.loadPixelShaderFromFile("Shaders/CopyPS.hlsl",
                                          "CopyPS");


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

  m_dirLightBuffer = graphicsApi.createConstantBufferPtr();
  m_dirLightBuffer->initData(sizeof(float) * 8, sizeof(float), nullptr);

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

  Color colorBlack{ 0.0f, 0.0f, 0.0f, 1.0f };
  
  
  // Get main camera
  Vector<SPtr<Actor>> actorCameras =
  sceneManager.getAllActorsByComponentFlags(eCOMPONENT_TYPE::kCamera);
  Vector<SPtr<CCamera>> activeCams;
  for (const auto& act : actorCameras) {
    activeCams.emplace_back(act->getComponent<CCamera>());
  }
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
  graphicsApi.clearRenderTargets({ m_GBufferNormalTexture },
                                 (colorBlack + 1.0f) * 0.5f);
  graphicsApi.clearRenderTargets({ m_GBufferPositionTexture,
                                   m_GBufferColorTexture },
                                 colorBlack);
  graphicsApi.cleanDepthStencils({ m_GBufferDepthStencil });
  graphicsApi.setRenderTargets({ m_GBufferPositionTexture,
                                 m_GBufferColorTexture,
                                 m_GBufferNormalTexture },
                               m_GBufferDepthStencil);
  
  
  // Load shaders
  graphicsApi.setShaderPrograms(resourceManager.getResourceVertexShader("GBufferVSAnim"),
                                resourceManager.getResourcePixelShader("GBufferPSAnim"));
  
  
  // Set constant buffers
  graphicsApi.setVSConstantBuffers
  (
    { m_viewMatrixBuffer, m_projectionMatrixBuffer },
    1u
  );
  
  
  // Draw in-cam actors with skeletal mesh
  Vector<SPtr<Actor>> rActors;
  if (mainCam) {
    rActors =
    sceneManager.getAllRenderableActorsInside(mainCam,
                                              RENDER_ACTOR_FLAGS::kSkeletalMesh);
  }
  
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
  graphicsApi.setShaderPrograms(resourceManager.getResourceVertexShader("GBufferVS"),
                                resourceManager.getResourcePixelShader("GBufferPS"));
  
  
  // Draw in-cam actors with static mesh
  if (mainCam) {
    rActors =
    sceneManager.getAllRenderableActorsInside(mainCam,
                                              RENDER_ACTOR_FLAGS::kStaticMesh);
  }
  
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
  
  // Set model buffer
  Matrix4f modelMatrix = Matrix4f::kIDENTITY;
  m_modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMatrix));
  graphicsApi.setVSConstantBuffers({ m_modelMatrixBuff }, 0u);
  
  for (const auto& staticMesh : partitionMeshes) {
    meshes = staticMesh->getMeshes();
    meshesCount = meshes.size();
  
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
  }
  // Unbind buffers
  graphicsApi.unsetVSConstantBuffers(3u, 0u);
  
  
  /* SSAO */
  
  // Clear and set render targets
  graphicsApi.clearRenderTargets({ m_SSAOTexture }, colorBlack);
  graphicsApi.setRenderTargets({ m_SSAOTexture }, nullptr);
  
   
  // Set constant buffers
  graphicsApi.setPSConstantBuffers
  ({ m_ssaoDataBuffer }, 0u );
  
  
  // Load shaders
  graphicsApi.setShaderPrograms(resourceManager.getResourceVertexShader("SSAOVS"),
                                resourceManager.getResourcePixelShader("SSAOPS"));
  
  
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
  
  // Get all lights
  Vector<SPtr<Actor>> actorLights =
  sceneManager.getAllActorsByComponentFlags(eCOMPONENT_TYPE::kLight);
  Vector<SPtr<CLight>> lights;
  for (const auto& act : actorLights) {
    lights.emplace_back(act->getComponent<CLight>());
  }
  Vector<float> dirLightBufferData;
  
  
  SPtr<VertexShader> copyVS =
  resourceManager.getResourceVertexShader("CopyVS");
  SPtr<PixelShader> copyPS =
  resourceManager.getResourcePixelShader("CopyPS");
  
  
  
  //
  // Diffuse
  // 
  
  // Store shaders
  SPtr<VertexShader> dirDiffLightVS =
  resourceManager.getResourceVertexShader("DirectionalDiffuseLightsVS");
  SPtr<PixelShader> dirDiffLightPS =
  resourceManager.getResourcePixelShader("DirectionalDiffuseLightsPS");
  SPtr<VertexShader> pointDiffLightVS =
  resourceManager.getResourceVertexShader("PointDiffuseLightsVS");
  SPtr<PixelShader> pointDiffLightPS =
  resourceManager.getResourcePixelShader("PointDiffuseLightsPS");
  
  
  graphicsApi.clearRenderTargets({ m_tempDiffLightsTexture }, colorBlack);
  for (const auto& light : lights) {
    //
    // Add light
    //
  
    // Clear and set render targets
    graphicsApi.clearRenderTargets({ m_diffLightsTexture }, colorBlack);
    graphicsApi.setRenderTargets({ m_diffLightsTexture }, nullptr);
  
  
    // Set textures
    graphicsApi.setTextures({ m_GBufferPositionTexture,
                              m_GBufferNormalTexture,
                              m_tempDiffLightsTexture },
                            0u);
  
  
    if (light->getLightType() == eLIGHT_TYPE::kDirectional) {
      // Load shaders
      graphicsApi.setShaderPrograms(dirDiffLightVS, dirDiffLightPS);
  
  
      // Set constant buffers
      Vector3f lightDir = light->getDirection();
      Color lightColor = light->getColor();
      dirLightBufferData =
      {
        lightDir.x, lightDir.y, lightDir.z, light->getIntensity(),
        lightColor.r, lightColor.g, lightColor.b, lightColor.a
      };
      m_dirLightBuffer->updateData(reinterpret_cast<Byte*>(dirLightBufferData.data()));
      graphicsApi.setPSConstantBuffers({ m_dirLightBuffer }, 0u);
    }
    else if (light->getLightType() == eLIGHT_TYPE::kPoint) {
      // Load shaders
      graphicsApi.setShaderPrograms(pointDiffLightVS, pointDiffLightPS);
  
  
      // Set light constant buffer
      Vector3f lightPos = light->getPosition();
      Color lightColor = light->getColor();
      dirLightBufferData =
      {
        lightPos.x, lightPos.y, lightPos.z, light->getIntensity(),
        lightColor.r, lightColor.g, lightColor.b, lightColor.a
      };
      m_dirLightBuffer->updateData(reinterpret_cast<Byte*>(dirLightBufferData.data()));
      graphicsApi.setPSConstantBuffers({ m_dirLightBuffer }, 0u);
    }
    
    
    // Draw using a SAQ
    graphicsApi.drawOnSAQ();
    
    
    // Unbind buffers
    graphicsApi.unsetRenderTargets();
    graphicsApi.unsetPSConstantBuffers(1u, 0u);
    graphicsApi.unsetTextures(3u, 0u);
  
  
    //
    // Copy
    //
  
    // Clear and set render targets
    graphicsApi.clearRenderTargets({ m_tempDiffLightsTexture }, colorBlack);
    graphicsApi.setRenderTargets({ m_tempDiffLightsTexture }, nullptr);
  
  
    // Load shaders
    graphicsApi.setShaderPrograms(copyVS, copyPS);
  
  
    // Set textures
    graphicsApi.setTextures({ m_diffLightsTexture }, 0u);
  
  
    // Draw using a SAQ
    graphicsApi.drawOnSAQ();
  
  
    // Unbind buffers
    graphicsApi.unsetRenderTargets();
    graphicsApi.unsetTextures(1u, 0u);
  }
  
  
  //
  // Specular
  // 
  
  // Store shaders
  SPtr<VertexShader> dirSpecLightVS =
  resourceManager.getResourceVertexShader("DirectionalSpecularLightsVS");
  SPtr<PixelShader> dirSpecLightPS =
  resourceManager.getResourcePixelShader("DirectionalSpecularLightsPS");
  SPtr<VertexShader> pointSpecLightVS =
  resourceManager.getResourceVertexShader("PointSpecularLightsVS");
  SPtr<PixelShader> pointSpecLightPS =
  resourceManager.getResourcePixelShader("PointSpecularLightsPS");
  
  
  graphicsApi.clearRenderTargets({ m_tempSpecLightsTexture }, colorBlack);
  for (const auto& light : lights) {
    //
    // Add light
    //
  
    // Clear and set render targets
    graphicsApi.clearRenderTargets({ m_specLightsTexture }, colorBlack);
    graphicsApi.setRenderTargets({ m_specLightsTexture }, nullptr);
  
  
    // Set view position constant buffer
    graphicsApi.setVSConstantBuffers
    ({ m_viewPosBuffer }, 0u);
  
  
    if (light->getLightType() == eLIGHT_TYPE::kDirectional) {
      // Load shaders
      graphicsApi.setShaderPrograms(dirSpecLightVS, dirSpecLightPS);
      
  
      // Set light constant buffer
      Vector3f lightDir = light->getDirection();
      Color lightColor = light->getColor();
      dirLightBufferData =
      {
        lightDir.x, lightDir.y, lightDir.z, light->getIntensity(),
        lightColor.r, lightColor.g, lightColor.b, lightColor.a
      };
      m_dirLightBuffer->updateData(reinterpret_cast<Byte*>(dirLightBufferData.data()));
      graphicsApi.setPSConstantBuffers({ m_dirLightBuffer }, 0u);
    }
    else if (light->getLightType() == eLIGHT_TYPE::kPoint) {
      // Load shaders
      graphicsApi.setShaderPrograms(pointSpecLightVS, pointSpecLightPS);
  
  
      // Set light constant buffer
      Vector3f lightPos = light->getPosition();
      Color lightColor = light->getColor();
      dirLightBufferData =
      {
        lightPos.x, lightPos.y, lightPos.z, light->getIntensity(),
        lightColor.r, lightColor.g, lightColor.b, lightColor.a
      };
      m_dirLightBuffer->updateData(reinterpret_cast<Byte*>(dirLightBufferData.data()));
      graphicsApi.setPSConstantBuffers({ m_dirLightBuffer }, 0u);
    }
  
  
    // Set textures
    graphicsApi.setTextures({ m_GBufferPositionTexture,
                              m_GBufferNormalTexture,
                              m_tempSpecLightsTexture },
                            0u);
  
    
    // Draw using a SAQ
    graphicsApi.drawOnSAQ();
    
    
    // Unbind buffers
    graphicsApi.unsetRenderTargets();
    graphicsApi.unsetVSConstantBuffers(1u, 0u);
    graphicsApi.unsetPSConstantBuffers(1u, 0u);
    graphicsApi.unsetTextures(3u, 0u);
  
  
    //
    // Copy
    //
  
    // Clear and set render targets
    graphicsApi.clearRenderTargets({ m_tempSpecLightsTexture }, colorBlack);
    graphicsApi.setRenderTargets({ m_tempSpecLightsTexture }, nullptr);
  
  
    // Load shaders
    graphicsApi.setShaderPrograms(copyVS, copyPS);
  
  
    // Set textures
    graphicsApi.setTextures({ m_specLightsTexture }, 0u);
  
  
    // Draw using a SAQ
    graphicsApi.drawOnSAQ();
  
  
    // Unbind buffers
    graphicsApi.unsetRenderTargets();
    graphicsApi.unsetTextures(1u, 0u);
  }
  
  
  //
  // Final
  //
  
  // Clear and set render targets
  graphicsApi.clearRenderTargets({ m_lightTexture }, colorBlack);
  graphicsApi.setRenderTargets({ m_lightTexture }, nullptr);
  
  
  // Load shaders
  graphicsApi.setShaderPrograms(resourceManager.getResourceVertexShader("LightsVS"),
                                resourceManager.getResourcePixelShader("LightsPS"));
  
  
  // Set textures
  graphicsApi.setTextures({ m_GBufferPositionTexture,
                            m_GBufferColorTexture,
                            m_GBufferNormalTexture,
                            m_SSAOTexture,
                            m_diffLightsTexture,
                            m_specLightsTexture },
                          0u);
  
  
  // Draw using a SAQ
  graphicsApi.drawOnSAQ();
  
  
  // Unbind buffers
  graphicsApi.unsetRenderTargets();
  graphicsApi.unsetTextures(6u, 0u);
  
  
  /* HDR Luminance */
  
  
  ViewportDesc vp(512.0f, 512.0f);
  graphicsApi.setViewports({ vp });
  
  // Clear and set render targets
  graphicsApi.setRenderTargets({ m_HDRLuminanceTexture }, nullptr);
  graphicsApi.clearRenderTargets({ m_HDRLuminanceTexture }, colorBlack);
  
  // Set constant buffers
  graphicsApi.setVSConstantBuffers
  ({ m_viewportRectDataBuffer }, 0u );
  
  // Load shaders
  graphicsApi.setShaderPrograms(resourceManager.getResourceVertexShader("HDRLuminanceVS"),
                                resourceManager.getResourcePixelShader("HDRLuminancePS"));
  
  
  // Set textures
  //graphicsApi.setTextures({ resourceManager.getResourceTexture("DefaultDiffuse") },
  graphicsApi.setTextures({ m_lightTexture },
                          0u);
  
  
  // Draw using a SAQ
  m_samplerLinear->use();
  graphicsApi.drawOnSAQ();
  
  
  // Unbind buffers
  graphicsApi.unsetRenderTargets();
  graphicsApi.unsetVSConstantBuffers(1u, 0u);
  graphicsApi.unsetTextures(1u, 0u);
  
  
  /* Copy */
  
  vp.width = static_cast<float>(graphicsApi.getMainWindow()->getWidth());
  vp.height = static_cast<float>(graphicsApi.getMainWindow()->getHeight());
  graphicsApi.setViewports({ vp });
  
  // Set Back Buffer
  SPtr<Window> mainWin = graphicsApi.getMainWindow();
  graphicsApi.clearRenderTargets({ mainWin->getRenderTarget() }, colorBlack);
  graphicsApi.setRenderTargets({ mainWin->getRenderTarget() }, nullptr);
  
  
  // Load shaders
  graphicsApi.setShaderPrograms(copyVS, copyPS);
  
  
  // Set textures
  graphicsApi.setTextures({ m_lightTexture },
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