#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
class DepthStencil
{
 public:
  DepthStencil() = default;
  virtual
  ~DepthStencil() = default;

  virtual bool
  create(int32 width, int32 height) { return true; }

  virtual void
  use() {}
  virtual void
  clean() {}

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