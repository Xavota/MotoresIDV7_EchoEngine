/************************************************************************/
/**
 * @file eeRasterizerState.h
 * @author Diego Castellanos
 * @date 13/11/21
 * @brief
 * Rasterizer state, to describe how to interpret pixels.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK{
/**
 * @brief
 * Rasterizer state, to describe how to interpret pixels.
 */
class EE_CORE_EXPORT RasterizerState
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  RasterizerState() = default;
  /**
   * @brief
   * Default destructor.
   */
  virtual
  ~RasterizerState() { release(); }

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
   * @param depthClipEnable
   * The depth clip enabled.
   *
   * @return
   * Whether it succeeded to create or not.
   */
  virtual bool
  create(eFILL_MODE::E /*fillMode*/,
         eCULL_MODE::E /*cullMode*/,
         bool /*frontCounterClockwise*/,
         bool /*depthClipEnable*/ = false) { return true; }

  /**
   * @brief
   * Set to graphics api.
   *
   * @description
   * Sets the rasterizer state for the graphic memory to use, only for override
   * in graphics api specializations.
   */
  virtual void
  use() {}

  /**
   * @brief
   * Releases the data.
   *
   * @description
   * Deletes the memory of all data allocated.
   */
  virtual void
  release() {}

 protected:
};
}
