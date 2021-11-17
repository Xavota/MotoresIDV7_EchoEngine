#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK{
class DepthStencilState
{
 public:
  DepthStencilState() = default;
  virtual
  ~DepthStencilState() = default;

  virtual bool
  create(DepthStencilDesc desc) { return true; }

  /**
  * @brief
  * Set to graphics api.
  *
  * @description
  * Sets the depth stencil state for the graphic memory to use, only for
  * override in graphics api specializations.
  */
  virtual void
  use(uint32 stencilRef) {}

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
