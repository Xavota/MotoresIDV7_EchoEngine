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
struct BezierData
{
  Matrix4f viewProj;
  Vector3f camPos;
  float tess = 0.0f;
};
DeferredRenderer::DeferredRenderer()
{
  auto& graphicsApi = GraphicsApi::instance();
  auto& resourceManager = ResourceManager::instance();
  //auto& memoryManager = MemoryManager::instance();

  
  const uint32 screenWidth = graphicsApi.getMainWindow().lock()->getWidth();
  const uint32 screenHeight = graphicsApi.getMainWindow().lock()->getHeight();

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
                                  Point2D{ screenWidth, screenHeight },
                                  eTEXTURE_FORMAT::kD24_Unorm_S8_Uint);

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
  resourceManager.loadVertexShaderFromFile(L"Shaders/GBufferVS.hlsl",
                                           "main", {},
                                           "GBufferVS");
  resourceManager.loadPixelShaderFromFile(L"Shaders/GBufferPS.hlsl",
                                          "main", {},
                                          "GBufferPS");

  resourceManager.loadVertexShaderFromFile(L"Shaders/GBufferVSAnim.hlsl",
                                           "main", {},
                                           "GBufferVSAnim");
  resourceManager.loadPixelShaderFromFile(L"Shaders/GBufferPSAnim.hlsl",
                                          "main", {},
                                          "GBufferPSAnim");

  resourceManager.loadVertexShaderFromFile(L"Shaders/DirectionalDiffuseLightsVS.hlsl",
                                           "main", {},
                                           "DirectionalDiffuseLightsVS");
  resourceManager.loadPixelShaderFromFile(L"Shaders/DirectionalDiffuseLightsPS.hlsl",
                                          "main", {},
                                          "DirectionalDiffuseLightsPS");
  resourceManager.loadVertexShaderFromFile(L"Shaders/DirectionalSpecularLightsVS.hlsl",
                                           "main", {},
                                           "DirectionalSpecularLightsVS");
  resourceManager.loadPixelShaderFromFile(L"Shaders/DirectionalSpecularLightsPS.hlsl",
                                          "main", {},
                                          "DirectionalSpecularLightsPS");
  resourceManager.loadVertexShaderFromFile(L"Shaders/PointDiffuseLightsVS.hlsl",
                                           "main", {},
                                           "PointDiffuseLightsVS");
  resourceManager.loadPixelShaderFromFile(L"Shaders/PointDiffuseLightsPS.hlsl",
                                          "main", {},
                                          "PointDiffuseLightsPS");
  resourceManager.loadVertexShaderFromFile(L"Shaders/PointSpecularLightsVS.hlsl",
                                           "main", {},
                                           "PointSpecularLightsVS");
  resourceManager.loadPixelShaderFromFile(L"Shaders/PointSpecularLightsPS.hlsl",
                                          "main", {},
                                          "PointSpecularLightsPS");
  resourceManager.loadVertexShaderFromFile(L"Shaders/LightsVS.hlsl",
                                           "main", {},
                                           "LightsVS");
  resourceManager.loadPixelShaderFromFile(L"Shaders/LightsPS.hlsl",
                                          "main", {},
                                          "LightsPS");

  resourceManager.loadVertexShaderFromFile(L"Shaders/SSAOVS.hlsl",
                                           "main", {},
                                           "SSAOVS");
  resourceManager.loadPixelShaderFromFile(L"Shaders/SSAOPS.hlsl",
                                          "main", {},
                                          "SSAOPS");

  resourceManager.loadVertexShaderFromFile(L"Shaders/HDRLuminanceVS.hlsl",
                                           "main", {},
                                           "HDRLuminanceVS");
  resourceManager.loadPixelShaderFromFile(L"Shaders/HDRLuminancePS.hlsl",
                                          "main", {},
                                          "HDRLuminancePS");
                                          
  resourceManager.loadVertexShaderFromFile(L"Shaders/CopyVS.hlsl",
                                           "main", {},
                                           "CopyVS");
  resourceManager.loadPixelShaderFromFile(L"Shaders/CopyPS.hlsl",
                                          "main", {},
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




                                     


  resourceManager.loadVertexShaderFromFile(L"Shaders/SimpleBezier11.hlsl",
                                           "BezierVS", {},
                                           "TestVS");
  resourceManager.loadHullShaderFromFile(L"Shaders/SimpleBezier11.hlsl",
                                         "BezierHS",
                                         {{"BEZIER_HS_PARTITION", "\"integer\""}},
                                         "TestHS");
  resourceManager.loadDomainShaderFromFile(L"Shaders/SimpleBezier11.hlsl",
                                           "BezierDS", {},
                                           "TestDS");
  resourceManager.loadPixelShaderFromFile(L"Shaders/SimpleBezier11.hlsl",
                                          "SolidColorPS", {},
                                          "TestPS");

  Vector<ComplexVertex> morbiusStripVertices = {
    ComplexVertex{ Vector4f{ 1.0f, -0.5f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 1.0f, -0.5f, 0.5f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.5f, -0.3536f, 1.354f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.0f, -0.3536f, 1.354f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 1.0f, -0.1667f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 1.0f, -0.1667f, 0.5f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.5f, -0.1179f, 1.118f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.0f, -0.1179f, 1.118f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 1.0f, 0.1667f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 1.0f, 0.1667f, 0.5f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.5f, 0.1179f, 0.8821f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.0f, 0.1179f, 0.8821f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 1.0f, 0.5f, 0.0f, 1.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 1.0f, 0.5f, 0.5f, 1.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.5f, 0.3536f, 0.6464f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.0f, 0.3536f, 0.6464f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.0f, -0.3536f, 1.354f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -0.5f, -0.3536f, 1.354f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -1.5f, 0.0f, 0.5f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -1.5f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.0f, -0.1179f, 1.118f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -0.5f, -0.1179f, 1.118f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -1.167f, 0.0f, 0.5f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -1.167f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f } },
    ComplexVertex{ Vector4f{ 0.0f, 0.1179f, 0.8821f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -0.5f, 0.1179f, 0.8821f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -0.8333f, 0.0f, 0.5f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -0.8333f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.0f, 0.3536f, 0.6464f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -0.5f, 0.3536f, 0.6464f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -0.5f, 0.0f, 0.5f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -0.5f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -1.5f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -1.5f, 0.0f, -0.5f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -0.5f, 0.3536f, -1.354f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.0f, 0.3536f, -1.354f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -1.167f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -1.167f, 0.0f, -0.5f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -0.5f, 0.1179f, -1.118f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.0f, 0.1179f, -1.118f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -0.8333f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -0.8333f, 0.0f, -0.5f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -0.5f, -0.1179f, -0.8821f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.0f, -0.1179f, -0.8821f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -0.5f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -0.5f, 0.0f, -0.5f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ -0.5f, -0.3536f, -0.6464f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.0f, -0.3536f, -0.6464f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.0f, 0.3536f, -1.354f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.5f, 0.3536f, -1.354f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 1.0f, 0.5f, -0.5f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 1.0f, 0.5f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.0f, 0.1179f, -1.118f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.5f, 0.1179f, -1.118f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 1.0f, 0.1667f, -0.5f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 1.0f, 0.1667f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.0f, -0.1179f, -0.8821f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.5f, -0.1179f, -0.8821f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 1.0f, -0.1667f, -0.5f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 1.0f, -0.1667f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.0f, -0.3536f, -0.6464f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 0.5f, -0.3536f, -0.6464f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 1.0f, -0.5f, -0.5f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }},
    ComplexVertex{ Vector4f{ 1.0f, -0.5f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f },
                   Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f }}
  };
  SIZE_T verticesSize = morbiusStripVertices.size();
  Vector4f maxCoord4 = morbiusStripVertices[0].position;
  Vector3f maxCoord = Vector3f{ maxCoord4.x, maxCoord4.y, maxCoord4.z };
  Vector3f minCoord = maxCoord;
  Vector3f furtherPos = Vector3f{};
  float maxDistance = 0.0f;
  for (SIZE_T i = 0; i < verticesSize; ++i) {
    Vector3f pos = Vector3f{ morbiusStripVertices[0].position.x, 
                             morbiusStripVertices[0].position.y,
                             morbiusStripVertices[0].position.z };
    auto dist =
    static_cast<float>(pow(pow(pos.x, 2) + pow(pos.y, 2) + pow(pos.z, 2), 0.5f));
    if (dist > maxDistance) {
      maxDistance = dist;
      furtherPos = pos;
    }
    maxCoord.x = pos.x > maxCoord.x ? pos.x : maxCoord.x;
    maxCoord.y = pos.y > maxCoord.y ? pos.y : maxCoord.y;
    maxCoord.z = pos.z > maxCoord.z ? pos.z : maxCoord.z;

    minCoord.x = pos.x < minCoord.x ? pos.x : minCoord.x;
    minCoord.y = pos.y < minCoord.y ? pos.y : minCoord.y;
    minCoord.z = pos.z < minCoord.z ? pos.z : minCoord.z;
  }

  Mesh morbStrip;
  morbStrip.loadFromControlPoints(morbiusStripVertices);

  resourceManager.loadStaticMeshFromMeshesArray({ morbStrip }, "MorbiusStripMesh", maxDistance, maxCoord, minCoord);

  BezierData bdata{};
  bdata.viewProj = Matrix4f::kIDENTITY;
  bdata.camPos = Vector3f{0.0f, 0.0f, 0.0f};
  bdata.tess = 8.0f;

  m_bezierBuffer = graphicsApi.createConstantBufferPtr();
  m_bezierBuffer->initData(sizeof(BezierData),
                           sizeof(BezierData),
                           reinterpret_cast<Byte*>(&bdata));

                           

  m_rasterizerBezier = graphicsApi.createRasterizerStatePtr();
  m_rasterizerBezier->create(eeEngineSDK::eFILL_MODE::kSolid,
                             eeEngineSDK::eCULL_MODE::kNone,
                             true, true);

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


  WPtr<Texture> nullTexturWPtr = WPtr<Texture>();




  Vector<Pair<Mesh, WPtr<Material>>> meshes;
  Vector<Pair<BoneMesh, WPtr<Material>>> boneMeshes;
  SIZE_T meshesCount = 0;
  
  Color colorBlack{ 0.0f, 0.0f, 0.0f, 1.0f };
  
  
  // Get main camera
  Vector<SPtr<Actor>> actorCameras =
  sceneManager.getAllActorsByComponentFlags(eCOMPONENT_TYPE::kCamera);
  Vector<WPtr<CCamera>> activeCams;
  for (const auto& act : actorCameras) {
    activeCams.emplace_back(act->getComponent<CCamera>());
  }
  WPtr<CCamera> mainCam;
  for (auto& cam : activeCams) {
    if (cam.lock()->isMain()) {
      mainCam = cam;
    }
  }
  
  
  // Updates buffers
  auto sMainCam = mainCam.lock();
  if (!mainCam.expired()) {
    Vector3f pos = sMainCam->getActor().lock()->getTransform().lock()->getPosition();
    Vector4f vp = Vector4f(pos.x, pos.y, pos.z, 1.0f);
    m_viewPosBuffer->updateData(reinterpret_cast<Byte*>(&vp));
  
    // Create view/proj matrices
    Matrix4f view = Matrix4f::kIDENTITY;
    view = sMainCam->getViewMatrix().getTranspose();
    m_viewMatrixBuffer->updateData(reinterpret_cast<Byte*>(&view));
  
    Matrix4f proj = Matrix4f::kIDENTITY;
    proj = sMainCam->getProjectionMatrix().getTranspose();
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
  graphicsApi.setPrimitiveTopology(ePRIMITIVE_TOPOLOGY::kTrianglelist);
  
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
                                {}, {},
                                resourceManager.getResourcePixelShader("GBufferPSAnim"));
  
  
  // Set constant buffers
  graphicsApi.setVSConstantBuffers
  (
    { m_viewMatrixBuffer, m_projectionMatrixBuffer },
    1u
  );
  
  
  // Draw in-cam actors with skeletal mesh
  Vector<WPtr<Actor>> rActors;
  if (!mainCam.expired()) {
    rActors =
    sceneManager.getAllRenderableActorsInside(sMainCam,
                                              eRENDER_ACTOR_FLAGS::kSkeletalMesh);
  }
  
  for (const auto& act : rActors) {
    auto sAct = act.lock();
    auto skMesh = sAct->getComponent<CSkeletalMesh>().lock();
   
    const auto skModel = skMesh->getModel().lock();
    if (skMesh && skModel) {
      boneMeshes = skModel->getMeshes();
      meshesCount = boneMeshes.size();
  
  
      // Set model buffer
      auto transform = sAct->getTransform().lock();
      Matrix4f modelMatrix = transform->getModelMatrix();
      m_modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMatrix));
      graphicsApi.setVSConstantBuffers({ m_modelMatrixBuff }, 0u);
  
  
      // Set textures
      Vector<WPtr<Texture>> texs;
      Map<uint32, WPtr<Texture>> texturesMap;
      const auto skeleton = skModel->getSkeletal().lock();
      for (SIZE_T j = 0; j < meshesCount; ++j) {
        texturesMap = boneMeshes[j].second.lock()->getTexturesMap();
   
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
                                {}, {},
                                resourceManager.getResourcePixelShader("GBufferPS"));
  
  
  // Draw in-cam actors with static mesh
  if (!mainCam.expired()) {
    rActors =
    sceneManager.getAllRenderableActorsInside(sMainCam,
                                              eRENDER_ACTOR_FLAGS::kStaticMesh);
  }
  else {
    return;
  }
  
  for (const auto& act : rActors) {
    auto sAct = act.lock();
    const auto staticMesh = sAct->getComponent<CStaticMesh>().lock();
    if (staticMesh
     && staticMesh->getMobilityType() != eMOBILITY_TYPE::kStatic
     && !staticMesh->getStaticMesh().expired()) {
      meshes = staticMesh->getStaticMesh().lock()->getMeshes();
      meshesCount = meshes.size();
  
  
      // Set model buffer
      auto transform = sAct->getTransform().lock();
      Matrix4f modelMatrix = transform->getModelMatrix();
      m_modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMatrix));
      graphicsApi.setVSConstantBuffers({ m_modelMatrixBuff }, 0u);
  
  
      // Set textures
      Vector<WPtr<Texture>> texs;
      Map<uint32, WPtr<Texture>> texturesMap;
      for (SIZE_T j = 0; j < meshesCount; ++j) {
        if (!meshes[j].second.expired()) {
          texturesMap = meshes[j].second.lock()->getTexturesMap();
        }
  
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
  
  Vector<WPtr<StaticMesh>> partitionMeshes;
  sceneManager.getPartitionedSceneMeshes(partitionMeshes);
  
  // Set model buffer
  Matrix4f modelMatrix = Matrix4f::kIDENTITY;
  m_modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMatrix));
  graphicsApi.setVSConstantBuffers({ m_modelMatrixBuff }, 0u);
  
  for (const auto& staticMesh : partitionMeshes) {
    meshes = staticMesh.lock()->getMeshes();
    meshesCount = meshes.size();
  
    // Set textures
    Vector<WPtr<Texture>> texs;
    Map<uint32, WPtr<Texture>> texturesMap;
    for (SIZE_T j = 0; j < meshesCount; ++j) {
      texturesMap = meshes[j].second.lock()->getTexturesMap();
  
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
  
  
  // Load shaders
  graphicsApi.setShaderPrograms(resourceManager.getResourceVertexShader("TestVS"),
                                resourceManager.getResourceHullShader("TestHS"),
                                resourceManager.getResourceDomainShader("TestDS"),
                                resourceManager.getResourcePixelShader("TestPS"));
  
  m_rasterizerBezier->use();
  graphicsApi.setPrimitiveTopology(ePRIMITIVE_TOPOLOGY::ControlPontPatchlist16);
  
  
  Matrix4f view = Matrix4f::kIDENTITY;
  view = sMainCam->getViewMatrix().getTranspose();
  Matrix4f proj = Matrix4f::kIDENTITY;
  proj = sMainCam->getProjectionMatrix().getTranspose();
  Matrix4f modl = Matrix4f::translationMatrix(Vector3f{2.0f, 0.0f, 0.0f});
  Matrix4f viewProj = proj * view;
  Vector3f camPos = sMainCam->getEyePosition();
  
  BezierData bdata{};
  bdata.viewProj = viewProj;
  bdata.camPos = camPos;
  bdata.tess = 8.0f;
  
  m_bezierBuffer->updateData(reinterpret_cast<Byte*>(&bdata));
  
  // Set constant buffers
  graphicsApi.setHSConstantBuffers
  (
    { m_bezierBuffer },
    0u
  );
  graphicsApi.setDSConstantBuffers
  (
    { m_bezierBuffer },
    0u
  );
  graphicsApi.setPSConstantBuffers
  (
    { m_bezierBuffer },
    0u
  );
  
  graphicsApi.drawMeshControlPoints(
  resourceManager.getResourceStaticMesh("MorbiusStripMesh").lock()->getMeshes()[0].first);
  
  
  graphicsApi.unsetHSConstantBuffers(1u, 0u);
  graphicsApi.unsetDSConstantBuffers(1u, 0u);
  graphicsApi.unsetPSConstantBuffers(1u, 0u);
  
  
  graphicsApi.setPrimitiveTopology(ePRIMITIVE_TOPOLOGY::kTrianglelist);
  m_solidCCWRasterizer->use();

  graphicsApi.unsetRenderTargets();

  /* SSAO */
  
  // Clear and set render targets
  graphicsApi.clearRenderTargets({ m_SSAOTexture }, colorBlack);
  graphicsApi.setRenderTargets({ m_SSAOTexture }, nullTexturWPtr);
  
   
  // Set constant buffers
  graphicsApi.setPSConstantBuffers
  ({ m_ssaoDataBuffer }, 0u );
  
  
  // Load shaders
  graphicsApi.setShaderPrograms(resourceManager.getResourceVertexShader("SSAOVS"),
                                {}, {},
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
  Vector<WPtr<CLight>> lights;
  for (const auto& act : actorLights) {
    lights.emplace_back(act->getComponent<CLight>());
  }
  Vector<float> dirLightBufferData;
  
  
  WPtr<VertexShader> copyVS =
  resourceManager.getResourceVertexShader("CopyVS");
  WPtr<PixelShader> copyPS =
  resourceManager.getResourcePixelShader("CopyPS");
  
  
  
  //
  // Diffuse
  // 
  
  // Store shaders
  WPtr<VertexShader> dirDiffLightVS =
  resourceManager.getResourceVertexShader("DirectionalDiffuseLightsVS");
  WPtr<PixelShader> dirDiffLightPS =
  resourceManager.getResourcePixelShader("DirectionalDiffuseLightsPS");
  WPtr<VertexShader> pointDiffLightVS =
  resourceManager.getResourceVertexShader("PointDiffuseLightsVS");
  WPtr<PixelShader> pointDiffLightPS =
  resourceManager.getResourcePixelShader("PointDiffuseLightsPS");
  
  
  graphicsApi.clearRenderTargets({ m_tempDiffLightsTexture }, colorBlack);
  for (const auto& light : lights) {
    //
    // Add light
    //
    auto sLight = light.lock();
  
    // Clear and set render targets
    graphicsApi.clearRenderTargets({ m_diffLightsTexture }, colorBlack);
    graphicsApi.setRenderTargets({ m_diffLightsTexture }, nullTexturWPtr);
  
  
    // Set textures
    graphicsApi.setTextures({ m_GBufferPositionTexture,
                              m_GBufferNormalTexture,
                              m_tempDiffLightsTexture },
                            0u);
  
  
    if (sLight->getLightType() == eLIGHT_TYPE::kDirectional) {
      // Load shaders
      graphicsApi.setShaderPrograms(dirDiffLightVS,
                                    {}, {},
                                    dirDiffLightPS);
  
  
      // Set constant buffers
      Vector3f lightDir = sLight->getDirection();
      Color lightColor = sLight->getColor();
      dirLightBufferData =
      {
        lightDir.x, lightDir.y, lightDir.z, sLight->getIntensity(),
        lightColor.r, lightColor.g, lightColor.b, lightColor.a
      };
      m_dirLightBuffer->updateData(reinterpret_cast<Byte*>(dirLightBufferData.data()));
      graphicsApi.setPSConstantBuffers({ m_dirLightBuffer }, 0u);
    }
    else if (sLight->getLightType() == eLIGHT_TYPE::kPoint) {
      // Load shaders
      graphicsApi.setShaderPrograms(pointDiffLightVS,
                                    {}, {},
                                    pointDiffLightPS);
  
  
      // Set light constant buffer
      Vector3f lightPos = sLight->getPosition();
      Color lightColor = sLight->getColor();
      dirLightBufferData =
      {
        lightPos.x, lightPos.y, lightPos.z, sLight->getIntensity(),
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
    graphicsApi.setRenderTargets({ m_tempDiffLightsTexture }, nullTexturWPtr);
  
  
    // Load shaders
    graphicsApi.setShaderPrograms(copyVS, {}, {}, copyPS);
  
  
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
  WPtr<VertexShader> dirSpecLightVS =
  resourceManager.getResourceVertexShader("DirectionalSpecularLightsVS");
  WPtr<PixelShader> dirSpecLightPS =
  resourceManager.getResourcePixelShader("DirectionalSpecularLightsPS");
  WPtr<VertexShader> pointSpecLightVS =
  resourceManager.getResourceVertexShader("PointSpecularLightsVS");
  WPtr<PixelShader> pointSpecLightPS =
  resourceManager.getResourcePixelShader("PointSpecularLightsPS");
  
  
  graphicsApi.clearRenderTargets({ m_tempSpecLightsTexture }, colorBlack);
  for (const auto& light : lights) {
    //
    // Add light
    //
    auto sLight = light.lock();
  
    // Clear and set render targets
    graphicsApi.clearRenderTargets({ m_specLightsTexture }, colorBlack);
    graphicsApi.setRenderTargets({ m_specLightsTexture }, nullTexturWPtr);
  
  
    // Set view position constant buffer
    graphicsApi.setVSConstantBuffers
    ({ m_viewPosBuffer }, 0u);
  
  
    if (sLight->getLightType() == eLIGHT_TYPE::kDirectional) {
      // Load shaders
      graphicsApi.setShaderPrograms(dirSpecLightVS, {}, {}, dirSpecLightPS);
      
  
      // Set light constant buffer
      Vector3f lightDir = sLight->getDirection();
      Color lightColor = sLight->getColor();
      dirLightBufferData =
      {
        lightDir.x, lightDir.y, lightDir.z, sLight->getIntensity(),
        lightColor.r, lightColor.g, lightColor.b, lightColor.a
      };
      m_dirLightBuffer->updateData(reinterpret_cast<Byte*>(dirLightBufferData.data()));
      graphicsApi.setPSConstantBuffers({ m_dirLightBuffer }, 0u);
    }
    else if (sLight->getLightType() == eLIGHT_TYPE::kPoint) {
      // Load shaders
      graphicsApi.setShaderPrograms(pointSpecLightVS, {}, {}, pointSpecLightPS);
  
  
      // Set light constant buffer
      Vector3f lightPos = sLight->getPosition();
      Color lightColor = sLight->getColor();
      dirLightBufferData =
      {
        lightPos.x, lightPos.y, lightPos.z, sLight->getIntensity(),
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
    graphicsApi.setRenderTargets({ m_tempSpecLightsTexture }, nullTexturWPtr);
  
  
    // Load shaders
    graphicsApi.setShaderPrograms(copyVS, {}, {}, copyPS);
  
  
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
  graphicsApi.setRenderTargets({ m_lightTexture }, nullTexturWPtr);
  
  
  // Load shaders
  graphicsApi.setShaderPrograms(resourceManager.getResourceVertexShader("LightsVS"),
                                {}, {},
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
  graphicsApi.setRenderTargets({ m_HDRLuminanceTexture }, nullTexturWPtr);
  graphicsApi.clearRenderTargets({ m_HDRLuminanceTexture }, colorBlack);
  
  // Set constant buffers
  graphicsApi.setVSConstantBuffers
  ({ m_viewportRectDataBuffer }, 0u );
  
  // Load shaders
  graphicsApi.setShaderPrograms(resourceManager.getResourceVertexShader("HDRLuminanceVS"),
                                {}, {},
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
  auto mainWin = graphicsApi.getMainWindow().lock();
  
  vp.width = static_cast<float>(mainWin->getWidth());
  vp.height = static_cast<float>(mainWin->getHeight());
  graphicsApi.setViewports({ vp });
  
  // Set Back Buffer
  graphicsApi.clearRenderTargets({ mainWin->getRenderTarget() }, colorBlack);
  graphicsApi.setRenderTargets({ mainWin->getRenderTarget() }, nullTexturWPtr);
  
  
  // Load shaders
  graphicsApi.setShaderPrograms(copyVS, {}, {}, copyPS);
  
  
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