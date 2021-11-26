/************************************************************************/
/**
 * @file eeInput.h
 * @author Diego Castellanos
 * @date 18/11/21
 * @brief
 * The input manager for the api.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include "eeComponent.h"

namespace eeEngineSDK{
class EE_CORE_EXPORT CRender : public Component
{
 public:
  enum { CmpType = eCOMPONENT_TYPE::RENDER };

  virtual int32
  getType() override
  {
    return CmpType;
  }

  CRender();
  ~CRender() = default;

  virtual void
  update(SPtr<Actor> actor) override;
};
}
