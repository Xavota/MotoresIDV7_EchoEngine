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
class EE_CORE_EXPORT CModel : public Component
{
 public:
  enum { CmpType = eCOMPONENT_TYPE::MODEL };

  virtual int32
  getType() override
  {
    return CmpType;
  }

  CModel();
  ~CModel() = default;

  virtual void
  setModel(SPtr<Model> model);

  virtual SPtr<Model>
  getModel();

 private:
  SPtr<Model> m_model;
};
}
