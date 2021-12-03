/************************************************************************/
/**
 * @file eeInput.h
 * @author Diego Castellanos
 * @date 17/11/21
 * @brief
 * The input manager for the api.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeModule.h>

namespace eeEngineSDK {
class EE_CORE_EXPORT Time : public Module<Time>
{
 public:
  Time() = default;
  ~Time() = default;

  float
  getDeltaTime();

 private:
  friend class BaseApp;

  void
  updateDeltaTime(float dt);

  float m_deltaTime = 0.0f;
};
}
