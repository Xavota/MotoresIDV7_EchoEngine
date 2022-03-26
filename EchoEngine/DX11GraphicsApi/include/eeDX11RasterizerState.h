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

namespace eeEngineSDK{
/**
 * @brief
 * Rasterizer state, to describe how to interpret pixels.
 */
class EE_PLUGINDX11_EXPORT DX11RasterizerState : public RasterizerState
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  DX11RasterizerState() = default;

  /**
   * @brief
   * Creates a rasterizer stencil state.
   *
   * @description
   * Creates the rasterizer stencil state with a descriptor.
   *
   * @param fillMode
   * The mode for filling the triangles.
   * @param cullMode
   * The mode for the order of rendering of the triangles.
   * @param frontCounterClockwise
   * If the triangles front is in counter clock wise order of its vertices.
   */
  DX11RasterizerState(eFILL_MODE::E fillMode,
                      eCULL_MODE::E cullMode,
                      bool frontCounterClockwise);
  /**
   * @brief
   * Default destructor.
   */
  ~DX11RasterizerState();

  /**
   * @brief
   * Creates a rasterizer stencil state.
   *
   * @description
   * Creates the rasterizer stencil state with a descriptor.
   *
   * @param fillMode
   * The mode for filling the triangles.
   * @param cullMode
   * The mode for the order of rendering of the triangles.
   * @param frontCounterClockwise
   * If the triangles front is in counter clock wise order of its vertices.
   *
   * @return
   * Whether it succeeded to create or not.
   */
  bool
  create(eFILL_MODE::E fillMode,
         eCULL_MODE::E cullMode,
         bool frontCounterClockwise) override;

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
