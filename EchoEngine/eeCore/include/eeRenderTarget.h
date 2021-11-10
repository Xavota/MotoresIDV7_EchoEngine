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

namespace eeEngineSDK {
/**
 * @brief
 * The Render target for the graphic memory to paint on.
 * It can be used as an input texture to.
 */
class EE_CORE_EXPORT RenderTarget
{
 public:
  RenderTarget() = default;
  virtual
  ~RenderTarget() = default;

  virtual bool
  createAsBackBuffer() { return true; }
  virtual bool
  createAsIOTexture() { return true; }

  virtual const SPtr<const Texture>
  getAsTexture() const { return m_inTexture; }


  virtual void
  set(SPtr<DepthStencil> /*stencil*/) {}
  virtual void
  clean(float r, float g, float b, float a) {}

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
  SPtr<Texture> m_inTexture = nullptr;
};
}
