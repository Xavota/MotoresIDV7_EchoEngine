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
#include <eeSphere.h>
#include <eeBox.h>

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

  void
  update(SPtr<Actor> actor) override;

  virtual void
  setModel(SPtr<Model> model);

  virtual SPtr<Model>
  getModel();

  
  const Sphere&
  getBoundingSphere();
  const BoxAAB&
  getBoundingBox();

 private:
  SPtr<Model> m_model;

  Sphere m_boundSphere;
  float m_originRadious = 0.0f;
  BoxAAB m_boundBox;
};
}
