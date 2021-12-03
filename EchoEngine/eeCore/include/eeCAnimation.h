/************************************************************************/
/**
 * @file eeBaseApp.h
 * @author Diego Castellanos
 * @date 02/12/21
 * @brief
 * The Base app for the program. Initializes, destroy, and run all the
 * application.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eeComponent.h"

namespace eeEngineSDK {
class EE_CORE_EXPORT CAnimation : public Component
{
 public:
  enum { CmpType = eCOMPONENT_TYPE::ANIMATION };

  virtual int32
  getType() override
  {
    return CmpType;
  }

  CAnimation() = default;
  ~CAnimation() = default;

  void
  update(SPtr<Actor> actor) override;

  SPtr<Animation>
  getAnimation();
  void
  setAnimation(SPtr<Animation> anim);

 private:
  SPtr<Animation> m_anim;
};
}

