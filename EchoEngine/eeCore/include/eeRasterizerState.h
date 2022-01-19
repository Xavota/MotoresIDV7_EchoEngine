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
   * @param desc
   * The descriptor for the rasterizer state.
   *
   * @return
   * Whether it succeeded to create or not.
   */
  virtual bool
  create(RasteraizerDesc /*desc*/) { return true; }

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
