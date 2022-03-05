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
  /**
   * The width of the screen.
   */
  const uint32 screenWidth = 1280u;
  /**
   * The height of the screen.
   */
  const uint32 screenHeight = 720u;

  /* Buffers */
  /*
  * The buffer for the view matrix.
  */
  SPtr<ConstantBuffer> m_viewMatrixBuffer = nullptr;
  /*
  * The buffer for the projection matrix.
  */
  SPtr<ConstantBuffer> m_projectionMatrixBuffer = nullptr;
  /*
  * A test buffer for the view position.
  */
  SPtr<ConstantBuffer> m_viewPosBuffer = nullptr;

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

  /*
  * A Screen Align Quad, used for rendering textures of a render target on
  * another
  */
  SPtr<Object> m_SAQ = nullptr;

  /* Pases */
  // GBuffer
  /*
  * The depth stencil of the back buffer
  */
  SPtr<Texture> m_GBufferDepthStencil;
  /*
  * The back buffer.
  */
  SPtr<Texture> m_GBufferPositionTexture;
  /*
  * The back buffer.
  */
  SPtr<Texture> m_GBufferColorTexture;
  /*
  * The back buffer.
  */
  SPtr<Texture> m_GBufferNormalTexture;

  /* Luces */
  /*
  * The back buffer.
  */
  SPtr<Texture> m_rtv;
  /*
  * The depth stencil of the back buffer
  */
  SPtr<Texture> m_dsv;
};
}
