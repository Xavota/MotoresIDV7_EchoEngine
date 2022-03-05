#include "eeDeferredRenderer.h"

#include <eeGraficsApi.h>
#include <eeResourceManager.h>
#include <eeSceneManager.h>
#include <eeLogger.h>

#include <eeObject.h>
#include <eeActor.h>
#include <eeCTransform.h>
#include <eeCCamera.h>
#include <eeCSkeletalMesh.h>

#include <eeMaterial.h>

#include <eeMath.h>

#include <eeColor.h>

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

  m_sampler = memoryManager.newPtr<SamplerState>();
  m_sampler->create(samDesc);

  Mesh SAQ;
  SAQ.loadFromArray<SimpleVertex, uint32>(
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
    }
  );

  resourceManager.loadMaterialFromTextures(m_rtv, nullptr, "SAQ_mat");

  m_SAQ = memoryManager.newPtr<Object>();
  m_SAQ->loadFromModel
  (
    resourceManager.loadStaticMeshFromMeshesArray
    (
      //Vector<Pair<Mesh, SPtr<Texture>>>
      Vector<Pair<Mesh, SPtr<Material>>>
      {
        //Pair<Mesh, SPtr<Texture>>
        Pair<Mesh, SPtr<Material>>
        (
          SAQ,
          nullptr
        )
      },
      "SAQ",
      Vector3f(1.0f, 1.0f, 0.0f),
      Vector3f(1.0f, 1.0f, 0.0f),
      Vector3f(-1.0f, -1.0f, 0.0f)
    ),
    Vector3f(0.0f, 0.0f, 0.0f),
    Quaternion(Vector3f(0.0f, 0.0f, 0.0f)),
    Vector3f(1.0f, 1.0f, 1.0f)
  );
  m_SAQ->getModel()->setTexture
  (
    resourceManager.getResourceMaterial
    (
      "SAQ_mat"
    ),
    0
  );

  
  
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
  
  m_rasterizer = graphicsApi.createRasterizerStatePtr();
  m_rasterizer->create(rasDesc);
  
  
  memset(&rasDesc, 0, sizeof(rasDesc));
  rasDesc.cullMode = eeEngineSDK::eCULL_MODE::FRONT;
  rasDesc.fillMode = eeEngineSDK::eFILL_MODE::SOLID;
  rasDesc.frontCounterClockwise = true;
  
  m_rasterizer2 = graphicsApi.createRasterizerStatePtr();
  m_rasterizer2->create(rasDesc);



  m_viewPosBuffer = graphicsApi.createConstantBufferPtr();
  m_viewPosBuffer->initData(sizeof(Vector4f), sizeof(Vector4f), nullptr);


  m_rtv = GraphicsApi::instance().createTexturePtr();
  m_rtv->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kRenderTarget
                | eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                  { screenWidth, screenHeight });

  m_dsv = GraphicsApi::instance().createTexturePtr();
  m_dsv->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kDepthStencil,
                  { screenWidth, screenHeight });
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


  Vector<SPtr<CCamera>> activeCams = graphicsApi.getActiveCameras();
  Color color{ 0.3f, 0.5f, 0.8f, 1.0f };


  // Load shaders
  SPtr<VertexShader> vs =
  resourceManager.getResourceVertexShader("TestVS");
  SPtr<VertexShader> animVS =
  resourceManager.getResourceVertexShader("TestVSAnim");

  SPtr<PixelShader> ps =
  resourceManager.getResourcePixelShader("TestPS");
  SPtr<PixelShader> animPS =
  resourceManager.getResourcePixelShader("TestPSAnim");

  m_sampler->use();

  m_rasterizer->use();

  SPtr<CCamera> mainCam = nullptr;
  for (auto& cam : activeCams) {
    if (cam->isMain())
    {
      mainCam = cam;
    }
  }

  if (mainCam)
  {
    // Updates buffers
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


    /* First Pass */

    // Clean and set back buffer and depth stencil
    graphicsApi.clearRenderTargets({ m_rtv }, color);
    graphicsApi.cleanDepthStencils({ m_dsv });
    graphicsApi.setRenderTargets({ m_rtv }, m_dsv);


    // Set buffers
    graphicsApi.setVSConstantBuffers
    (
      { m_viewMatrixBuffer, m_projectionMatrixBuffer, m_viewPosBuffer },
      1u
    );

    Vector<SPtr<Actor>> rActors =
      sceneManager.getAllRenderableActorsInside(activeCams[0]);
    SIZE_T rActorsCount = rActors.size();


    animVS->use();
    animPS->use();

    //Draw in-cam skeletal actors
    for (SIZE_T i = 0; i < rActorsCount; ++i) {
      if (rActors[i]->getComponent<CSkeletalMesh>())
        graphicsApi.drawObject(rActors[i]);
    }

    vs->use();
    ps->use();

    //Draw in-cam actors
    for (SIZE_T i = 0; i < rActorsCount; ++i) {
      if (!rActors[i]->getComponent<CSkeletalMesh>()) {
        graphicsApi.drawObject(rActors[i]);
      }
    }



    //Unbind buffers
    graphicsApi.unsetRenderTargets();
    graphicsApi.unsetVSConstantBuffers(3u, 0u);
  }


  //Set Back Buffer
  SPtr<Window> mainWin = graphicsApi.getMainWindow();
  graphicsApi.clearRenderTargets({ mainWin->getRenderTarget() }, color);
  graphicsApi.cleanDepthStencils({ mainWin->getDepthStencil() });
  graphicsApi.setRenderTargets({ mainWin->getRenderTarget() }, mainWin->getDepthStencil());



  // Load shaders
  resourceManager.getResourceVertexShader("TestSAQVS")->use();

  resourceManager.getResourcePixelShader("TestSAQPS")->use();



  //Set the main camera render target texture to the SAQ and renders it to the
  //back buffer
  m_rasterizer2->use();
  resourceManager.getResourceMaterial("SAQ_mat")->m_diffuse = m_rtv;
  m_SAQ->getModel()->setTexture(resourceManager.getResourceMaterial("SAQ_mat"), 0);
  graphicsApi.drawObject(m_SAQ);
}



EE_EXTERN EE_PLUGIN_EXPORT void
initPlugin()
{
  Renderer::startUp<DeferredRenderer>();
}
}