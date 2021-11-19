#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK{
class EE_CORE_EXPORT RasterizerState
{
 public:
  RasterizerState() = default;
  virtual
  ~RasterizerState() { release(); }

  virtual bool
  create(RasteraizerDesc desc) { return true; }

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
