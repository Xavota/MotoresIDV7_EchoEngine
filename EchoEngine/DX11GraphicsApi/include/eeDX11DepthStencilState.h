/************************************************************************/
/**
 * @file eeDX11DepthStencil.h
 * @author Diego Castellanos
 * @date 27/10/21
 * @brief
 * The Depth Stencil for the graphics module.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesDX11.h"
#include <eeDepthStencilState.h>

namespace eeEngineSDK{
/**
 * @brief
 * The Depth Stencil for the graphics module.
 */
class EE_PLUGINDX11_EXPORT DX11DepthStencilState : public DepthStencilState
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  DX11DepthStencilState() = default;
  /**
   * @brief
   * Creates a depth stencil.
   *
   * @description
   * Creates the depth stencil resource with a width and height screen.
   *
   * @param width
   * The width of the screen.
   * @param height
   * The height of the screen.
   */
  DX11DepthStencilState(DepthStencilDesc desc);
  /**
   * @brief
   * Default destructor.
   */
  ~DX11DepthStencilState();

  /**
   * @brief
   * Creates a depth stencil.
   *
   * @description
   * Creates the depth stencil resource with a width and height screen.
   *
   * @param width
   * The width of the screen.
   * @param height
   * The height of the screen.
   *
   * @return
   * Whether it succeeded to create or not.
   */
  bool
  create(DepthStencilDesc desc) override;

  /**
   * @brief
   * Set to graphics api.
   *
   * @description
   * Sets the rasterizer state for the graphic memory to use, only for override
   * in graphics api specializations.
   */
  void
  use(uint32 stencilRef) override;

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
   * The buffer from DX11.
   */
  ID3D11DepthStencilState* m_depthStencil = nullptr;
};
}