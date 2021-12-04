/************************************************************************/
/**
 * @file eeInput.h
 * @author Diego Castellanos
 * @date 02/12/21
 * @brief
 * The input manager for the api.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesUtilities.h"
#include <eeModule.h>

namespace eeEngineSDK {
class EE_UTILITY_EXPORT Time : public Module<Time>
{
public:
  Time();
  ~Time() = default;

  float
    getDeltaTime();

private:
  friend class BaseApp;

  void
    update();

  std::chrono::steady_clock::time_point m_start;
  float m_deltaTime = 0.0f;
};
}