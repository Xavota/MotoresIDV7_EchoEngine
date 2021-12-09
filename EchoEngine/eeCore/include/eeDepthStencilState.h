/************************************************************************/
/**
 * @file eeDepthStencilState.h
 * @author Diego Castellanos
 * @date 25/10/21
 * @brief
 * Depth stencil state, to describe stencil state to the graphic memory.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK{
/**
 * @brief
 * Depth stencil state, to describe stencil state to the graphic memory.
 */
class EE_CORE_EXPORT DepthStencilState
{
 public:
  /**
  * @brief
  * Default constructor.
  */
  DepthStencilState() = default;
  /**
  * @brief
  * Default destructor.
  */
  virtual
  ~DepthStencilState() = default;

  /**
  * @brief
  * Creates a depth stencil state.
  *
  * @description
  * Creates the depth stencil state with a descriptor.
  *
  * @param desc
  * The descriptor for the stencil state.
  *
  * @return
  * Whether it succeeded to create or not.
  */
  virtual bool
  create(DepthStencilDesc /*desc*/) { return true; }

  /**
  * @brief
  * Set to graphics api.
  *
  * @description
  * Sets the depth stencil state for the graphic memory to use, only for
  * override in graphics api specializations.
  */
  virtual void
  use(uint32 /*stencilRef*/) {}

  /**
  * @brief
  * Releases the data.
  *
  * @description
  * Deletes the memory of all data allocated.
  */
  virtual void
  release() {}
};
}
