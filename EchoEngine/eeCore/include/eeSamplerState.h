/************************************************************************/
/**
 * @file eeSamplerState.h
 * @author Diego Castellanos
 * @date 12/11/21
 * @brief
 * Sampler state, to describe how to read texture info.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
/**
 * @brief
 * Sampler state, to describe how to read texture info.
 */
class EE_CORE_EXPORT SamplerState
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  SamplerState() = default;
  /**
   * @brief
   * Default destructor.
   */
  virtual
  ~SamplerState() = default;

  /**
   * @brief
   * Creates a sampler stencil state.
   *
   * @description
   * Creates the sampler stencil state with a descriptor.
   *
   * @param desc
   * The descriptor for the sampler state.
   *
   * @return
   * Whether it succeeded to create or not.
   */
  virtual bool
  create(SamplerStateDesc /*desc*/) { return true; }

  /**
   * @brief
   * Set to graphics api.
   *
   * @description
   * Sets the sampler state for the graphic memory to use, only for override in
   * graphics api specializations.
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
