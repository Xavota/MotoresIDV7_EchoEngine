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

  SamplerStateDesc samDesc;
  memset(&samDesc, 0, sizeof(samDesc));
  samDesc.filter = eFILTER::kMIN_MAG_MIP_LINEAR;
  samDesc.addressU = eTEXTURE_ADDRESS_MODE::WRAP;
  samDesc.addressV = eTEXTURE_ADDRESS_MODE::WRAP;
  samDesc.addressW = eTEXTURE_ADDRESS_MODE::WRAP;
  samDesc.comparisonFunc = eCOMPARISON_FUNC::NEVER;
  samDesc.minLOD = 0;
  samDesc.maxLOD = Math::kMAX_FLOAT;

  m_samplerLinear = memoryManager.newPtr<SamplerState>();
  m_samplerLinear->create(samDesc);

  
  
  resourceManager.loadVertexShaderFromFile("Shaders/TestVShader.hlsl",
                                           "TestVS");
  resourceManager.loadPixelShaderFromFile("Shaders/TestPShader.hlsl",
                                          "TestPS");

  resourceManager.loadVertexShaderFromFile("Shaders/TestVSAnimShader.hlsl",
                                           "TestVSAnim");
  resourceManager.loadPixelShaderFromFile("Shaders/TestPSAnimShader.hlsl",
                                          "TestPSAnim");
  
  
  resourceManager.loadVertexShaderFromFile("Shaders/TestVSSAQ.hlsl",
                                           "TestSAQVS");
  resourceManager.loadPixelShaderFromFile("Shaders/TestPSSAQ.hlsl",
                                          "TestSAQPS");
  
  m_viewMatrixBuffer = graphicsApi.createConstantBufferPtr();
  m_projectionMatrixBuffer = graphicsApi.createConstantBufferPtr();
  m_viewMatrixBuffer->initData(sizeof(Matrix4f), sizeof(Matrix4f), nullptr);
  m_projectionMatrixBuffer->initData(sizeof(Matrix4f), sizeof(Matrix4f), nullptr);
  
  
  RasteraizerDesc rasDesc;
  memset(&rasDesc, 0, sizeof(rasDesc));
  rasDesc.cullMode = eeEngineSDK::eCULL_MODE::FRONT;
  rasDesc.fillMode = eeEngineSDK::eFILL_MODE::SOLID;
  rasDesc.frontCounterClockwise = true;
  
  m_solidCCWRasterizer = graphicsApi.createRasterizerStatePtr();
  m_solidCCWRasterizer->create(rasDesc);
  
  
  memset(&rasDesc, 0, sizeof(rasDesc));
  rasDesc.cullMode = eeEngineSDK::eCULL_MODE::FRONT;
  rasDesc.fillMode = eeEngineSDK::eFILL_MODE::SOLID;
  rasDesc.frontCounterClockwise = true;
  
  m_rasterizer2 = graphicsApi.createRasterizerStatePtr();
  m_rasterizer2->create(rasDesc);



  m_viewPosBuffer = graphicsApi.createConstantBufferPtr();
  m_viewPosBuffer->initData(sizeof(Vector4f), sizeof(Vector4f), nullptr);

  
  /* GBuffer Resources */
  
  resourceManager.loadVertexShaderFromFile("Shaders/GBufferVS.hlsl",
                                           "GBufferVS");
  resourceManager.loadPixelShaderFromFile("Shaders/GBufferPS.hlsl",
                                          "GBufferPS");

  resourceManager.loadVertexShaderFromFile("Shaders/GBufferVSAnim.hlsl",
                                           "GBufferVSAnim");
  resourceManager.loadPixelShaderFromFile("Shaders/GBufferPSAnim.hlsl",
                                          "GBufferPSAnim");

  m_GBufferDepthStencil = GraphicsApi::instance().createTexturePtr();
  m_GBufferDepthStencil->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kDepthStencil,
                                  Point2D{ screenWidth, screenHeight });

  m_GBufferPositionTexture = GraphicsApi::instance().createTexturePtr();
  m_GBufferPositionTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                                   | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                                     Point2D{ screenWidth, screenHeight });

  m_GBufferColorTexture = GraphicsApi::instance().createTexturePtr();
  m_GBufferColorTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                                | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                                  Point2D{ screenWidth, screenHeight });

  m_GBufferNormalTexture = GraphicsApi::instance().createTexturePtr();
  m_GBufferNormalTexture->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                                 | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                                   Point2D{ screenWidth, screenHeight });


  /* Lights Resources */
  
  resourceManager.loadVertexShaderFromFile("Shaders/LightsVS.hlsl",
                                           "LightsVS");
  resourceManager.loadPixelShaderFromFile("Shaders/LightsPS.hlsl",
                                          "LightsPS");

  m_rtv = GraphicsApi::instance().createTexturePtr();
  m_rtv->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                  Point2D{ screenWidth, screenHeight });

  m_dsv = GraphicsApi::instance().createTexturePtr();
  m_dsv->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kDepthStencil,
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


  static SPtr<ConstantBuffer> modelMatrixBuff = nullptr;
  if (!modelMatrixBuff) {
    modelMatrixBuff = GraphicsApi::instance().createConstantBufferPtr();
    modelMatrixBuff->initData(sizeof(Matrix4f), sizeof(Matrix4f), nullptr);
  }

  Vector<Pair<Mesh, SPtr<Material>>> meshes;
  SIZE_T meshesCount = 0;

  Color color{ 0.3f, 0.5f, 0.8f, 1.0f };


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
      modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMatrix));
      graphicsApi.setVSConstantBuffers({ modelMatrixBuff }, 0u);


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
        texs.clear();
   
        if (skeleton) {
          skeleton->use(j);
        }


        // Draw mesh
        graphicsApi.drawMesh(meshes[j].first);


        // Unbind buffers
        graphicsApi.unsetTextures(2u, 0u);
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
      modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMatrix));
      graphicsApi.setVSConstantBuffers({ modelMatrixBuff }, 0u);


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
        texs.clear();


        // Draw mesh
        graphicsApi.drawMesh(meshes[j].first);


        // Unbind buffers
        graphicsApi.unsetTextures(1u, 0u);
      }
      // Unbind buffers
      graphicsApi.unsetVSConstantBuffers(1u, 0u);
    }
  }

  /* Lights */

  // Clear and set render targets
  graphicsApi.clearRenderTargets({ m_rtv }, color);
  graphicsApi.cleanDepthStencils({ m_dsv });
  graphicsApi.setRenderTargets({ m_rtv }, m_dsv);


  // Set constant buffers
  graphicsApi.setVSConstantBuffers
  ({ m_viewPosBuffer }, 3u );


  // Load shaders
  resourceManager.getResourceVertexShader("LightsVS")->use();
  resourceManager.getResourcePixelShader("LightsPS")->use();


  // Draw using a SAQ
  graphicsApi.drawOnSAQ({ make_pair(0, m_GBufferPositionTexture),
                          make_pair(1, m_GBufferColorTexture),
                          make_pair(2, m_GBufferNormalTexture) });



  // Unbind buffers
  graphicsApi.unsetRenderTargets();
  graphicsApi.unsetVSConstantBuffers(2u, 1u);


  /* Copy */

  // Set Back Buffer
  SPtr<Window> mainWin = graphicsApi.getMainWindow();
  graphicsApi.clearRenderTargets({ mainWin->getRenderTarget() }, color);
  graphicsApi.cleanDepthStencils({ mainWin->getDepthStencil() });
  graphicsApi.setRenderTargets({ mainWin->getRenderTarget() },
                               mainWin->getDepthStencil());


  // Load shaders
  resourceManager.getResourceVertexShader("TestSAQVS")->use();
  resourceManager.getResourcePixelShader("TestSAQPS")->use();


  // Draw using a SAQ
  m_rasterizer2->use();
  graphicsApi.drawOnSAQ({ make_pair(0, m_rtv) });


  // Unbind buffers
  graphicsApi.unsetRenderTargets();
}



EE_EXTERN EE_PLUGIN_EXPORT void
initPlugin()
{
  Renderer::startUp<DeferredRenderer>();
}
}