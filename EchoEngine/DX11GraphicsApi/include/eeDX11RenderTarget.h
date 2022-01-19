/************************************************************************/
/**
 * @file eeDepthStencil.h
 * @author Diego Castellanos
 * @date 21/10/21
 * @brief
 * The Render target for the graphic memory to paint on.
 * It can be used as an input texture to.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesDX11.h"
#include <eeRenderTarget.h>
#pragma warning(push, 0)   
#include <d3d11.h>
#pragma warning(pop)  


namespace eeEngineSDK {
/**
 * @brief
 * The Render target for the graphic memory to paint on.
 * It can be used as an input texture to.
 */
class DX11RenderTarget : public RenderTarget
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  DX11RenderTarget() = default;
  /**
   * @brief
   * Default destructor.
   */
  ~DX11RenderTarget();

  /**
   * @brief
   * Creates the render target.
   *
   * @description
   * Creates the render target as a back buffer to render on the screen.
   *
   * @return
   * Whether it succeeded to create or not.
   */
  bool
  createAsBackBuffer() override;
  /**
   * @brief
   * Creates the render target.
   *
   * @description
   * Creates the render target as a back buffer to render on the screen.
   *
   * @return
   * Whether it succeeded to create or not.
   */
  bool
  createAsIOTexture() override;

  /**
   * @brief
   * Gets as a texture.
   *
   * @description
   * Gets the resource as an input texture.
   *
   * @return
   * The texture, with all of it painted on.
   */
  const SPtr<Texture>
  getAsTexture() const override;

  /**
   * @brief
   * Loads it to the graphic memory.
   *
   * @description
   * Tells the graphic api to load this render target to paint on it.
   *
   * @param stencil
   * The depth stencil needed to calculate depth.
   */
  void
  set(SPtr<DepthStencil> stencil) override;
  /**
   * @brief
   * Clear render target.
   *
   * @description
   * Cleans the render target with a background color.
   *
   * @parm r
   * R component of the background color.
   * @param g
   * G component of the background color.
   * @param b
   * B component of the background color.
   * @param a
   * A component of the background color.
   */
  void
  clean(float r, float g, float b, float a) override;

  /**
   * @brief
   * Gets the resource data.
   *
   * @description
   * Returns the low level graphic api data of the resource.
   *
   * @return
   * Low level graphic api data of the resource.
   */
  ID3D11RenderTargetView*
  getResource() { return m_renderTarget; }

  /**
   * @brief
   * Releases the data.
   *
   * @description
   * Deletes the memory of all data allocated.
   */
  void
  release() override;

 private:
  /**
   * The dx11 render target.
   */
  ID3D11RenderTargetView* m_renderTarget = nullptr;
};
}
