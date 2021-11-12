#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {

class SamplerState
{
 public:
  SamplerState() = default;
  virtual
  ~SamplerState() = default;

  virtual bool
  create(SamplerStateDesc desc) { return true; }

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
