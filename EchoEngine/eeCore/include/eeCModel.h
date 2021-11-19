#pragma once
#include "eePrerequisitesCore.h"
#include "eeComponent.h"

namespace eeEngineSDK{
class EE_CORE_EXPORT CModel : public Component
{
 public:
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
