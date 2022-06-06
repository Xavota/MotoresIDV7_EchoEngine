/************************************************************************/
/**
 * @file eeDeferredRenderer.h
 * @author Diego Castellanos
 * @date 03/03/22
 * @brief
 * The Main class of the renderer. Defines the things on the interface.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesDeferredRenderer.h"
#include <eeRenderer.h>

namespace eeEngineSDK {
/**
 * @brief
 * The Main class of the renderer. Defines the things on the interface.
 */
class EE_DEFERRED_RENDERER_EXPORT DeferredRenderer : public Renderer
{
 public:
  /**
   * @brief
   * Default constructor
   */
  DeferredRenderer();
  /**
   * @brief
   * Copy constructor
   */
  ~DeferredRenderer() = default;

  /**
  * @brief
  * The update method.
  *
  * @description
  * Updates everything in the app every frame.
  *
  * @param deltaTime
  * The time elapsed since the last frame.
  */
  void
  onUpdate(float deltaTime) override;

  /**
   * @brief
   * Executes the render pipeline.
   *
   * @description
   * Obtains the info of the base app to do the render pass.
   */
  void
  onRender() override;

private:
  /* Resources */
  /**
   * sampler state. The sampler of the texture.
   */
  SPtr<SamplerState> m_samplerLinear = nullptr;
  /*
  * A rasterizer for on world objects rendering.
  */
  SPtr<RasterizerState> m_solidCCWRasterizer = nullptr;
  /*
  * A rasterizer for on screen rendering.
  */
  SPtr<RasterizerState> m_rasterizer2 = nullptr;

  /* Buffers */
  /*
  * The buffer for the model matrix.
  */
  SPtr<ConstantBuffer> m_modelMatrixBuff = nullptr;
  /*
  * The buffer for the view matrix.
  */
  SPtr<ConstantBuffer> m_viewMatrixBuffer = nullptr;
  /*
  * The buffer for the projection matrix.
  */
  SPtr<ConstantBuffer> m_projectionMatrixBuffer = nullptr;
  /*
  * The buffer for the view position.
  */
  SPtr<ConstantBuffer> m_viewPosBuffer = nullptr;
  /*
  * The buffer for the bones of a skeletal mesh.
  */
  SPtr<ConstantBuffer> m_bonesBuffer = nullptr;
  /*
  * The buffer for the SSAO data.
  */
  SPtr<ConstantBuffer> m_ssaoDataBuffer = nullptr;
  /*
  * The buffer for the directional light data.
  */
  SPtr<ConstantBuffer> m_dirLightBuffer = nullptr;
  /*
  * The buffer for the SSAO data.
  */
  SPtr<ConstantBuffer> m_viewportRectDataBuffer = nullptr;

  /* Render Targets and Depth Stencils */
  /*
  * The depth stencil of the back buffer
  */
  SPtr<Texture> m_GBufferDepthStencil;
  /*
  * The render target for the position texture.
  */
  SPtr<Texture> m_GBufferPositionTexture;
  /*
  * The render target for the color texture.
  */
  SPtr<Texture> m_GBufferColorTexture;
  /*
  * The render target for the normal texture.
  */
  SPtr<Texture> m_GBufferNormalTexture;

  /*
  * The render target for the SSAO texture.
  */
  SPtr<Texture> m_SSAOTexture;

  /*
  * The render target for the diffuse lights accumulation.
  */
  SPtr<Texture> m_diffLightsTexture;
  /*
  * The render target for the diffuse lights accumulation.
  */
  SPtr<Texture> m_tempDiffLightsTexture;
  /*
  * The render target for the specular lights accumulation.
  */
  SPtr<Texture> m_specLightsTexture;
  /*
  * The render target for the specular lights accumulation.
  */
  SPtr<Texture> m_tempSpecLightsTexture;
  /*
  * The render target for the lights texture.
  */
  SPtr<Texture> m_lightTexture;

  /*
  * The render targets for the luminance pass.
  */
  SPtr<Texture> m_HDRLuminanceTexture;
};
}
