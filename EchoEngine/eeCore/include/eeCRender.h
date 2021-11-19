#pragma once
#include "eePrerequisitesCore.h"
#include "eeComponent.h"

namespace eeEngineSDK{
class EE_CORE_EXPORT CRender : public Component
{
 public:
  CRender();
  ~CRender() = default;

  virtual void
  update(Actor* actor) override;
};
}
