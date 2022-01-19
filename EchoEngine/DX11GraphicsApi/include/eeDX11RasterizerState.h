/************************************************************************/
/**
 * @file eeDepthStencil.h
 * @author Diego Castellanos
 * @date 15/10/21
 * @brief
 * Rasterizer state, to describe how to interpret pixels.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesDX11.h"
#include <eeRasterizerState.h>
#pragma warning(push, 0)   
#include <d3d11.h>
#pragma warning(pop)   

namespace eeEngineSDK{
/**
 * @brief
 * Rasterizer state, to describe how to interpret pixels.
 */
class DX11RasterizerState : public RasterizerState
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  DX11RasterizerState() = default;
  /**
   * @brief
   * Default destructor.
   */
  ~DX11RasterizerState() = default;

  /**
   * @brief
   * Creates a rasterizer stencil state.
   *
   * @description
   * Creates the rasterizer stencil state with a descriptor.
   *
   * @param desc
   * The descriptor for the rasterizer state.
   *
   * @return
   * Whether it succeeded to create or not.
   */
  bool
  create(RasteraizerDesc desc) override;

  /**
   * @brief
   * Set to graphics api.
   *
   * @description
   * Sets the rasterizer state for the graphic memory to use, only for override
   * in graphics api specializations.
   */
  void
  use() override;

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
   * The rasterizer resource data.
   */
  ID3D11RasterizerState* m_rasterizer = nullptr;
};
}
