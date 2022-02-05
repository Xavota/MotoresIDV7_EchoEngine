/************************************************************************/
/**
 * @file eeRenderTarget.h
 * @author Diego Castellanos
 * @date 23/10/21
 * @brief
 * The Render target for the graphic memory to paint on.
 * It can be used as an input texture to.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

#include "eeColor.h"

namespace eeEngineSDK {
/**
 * @brief
 * The Render target for the graphic memory to paint on.
 * It can be used as an input texture to.
 */
class EE_CORE_EXPORT RenderTarget
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  RenderTarget() = default;
  /**
   * @brief
   * Default destructor.
   */  
  virtual
  ~RenderTarget() = default;

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
  virtual bool
  createAsBackBuffer() { return true; }
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
  virtual bool
  createAsIOTexture() { return true; }

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
  virtual const SPtr<Texture>
  getAsTexture() const { return m_inTexture; }


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
  virtual void
  set(SPtr<DepthStencil> /*stencil*/) {}
  /**
   * @brief
   * Clear render target.
   *
   * @description
   * Cleans the render target with a background color.
   *
   * @parm screenColor
   * The background color.
   */
  virtual void
  clean(Color /*screenColor*/) {}

  /**
   * @brief
   * Releases the data.
   *
   * @description
   * Deletes the memory of all data allocated.
   */
  virtual void
  release() {};

 protected:
  /**
   * The input texture that is binded to the render target.
   */
  SPtr<Texture> m_inTexture = nullptr;
};
}
