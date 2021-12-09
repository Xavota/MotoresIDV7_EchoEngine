/************************************************************************/
/**
 * @file eeInput.h
 * @author Diego Castellanos
 * @date 20/11/21
 * @brief
 * The Blend state class.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
/**
 * @brief
 * The Blend state class.
 */
class EE_CORE_EXPORT BlendState
{
public:
  /**
  * @brief
  * Default constructor
  */
  BlendState() = default;
  /**
  * @brief
  * Default destructor
  */
  virtual
  ~BlendState() = default;

  /**
  * @brief
  * Creates a blend state.
  *
  * @description
  * Creates a blend state using a descriptor.
  *
  * @param desc
  * The descriptor of the blend state.
  *
  * @return
  * True if it succeeded to create the state.
  */
  virtual bool
  create(BlendDesc /*desc*/) { return true; }

  /**
  * @brief
  * Set to graphics api.
  *
  * @description
  * Sets the depth stencil state for the graphic memory to use, only for
  * override in graphics api specializations.
  * 
  * @param blendFactor
  * Blend factor.
  * @param sampleMask
  * Sample Mask.
  */
  virtual void
  use(float /*blendFactor*/[4], uint32 /*sampleMask*/) {}

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

