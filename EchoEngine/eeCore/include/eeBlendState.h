#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
class EE_CORE_EXPORT BlendState
{
public:
  BlendState() = default;
  virtual
  ~BlendState() = default;

  virtual bool
  create(BlendDesc desc) { return true; }

  /**
  * @brief
  * Set to graphics api.
  *
  * @description
  * Sets the depth stencil state for the graphic memory to use, only for
  * override in graphics api specializations.
  */
  virtual void
  use(float blendFactor[4], uint32 sampleMask) {}

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

