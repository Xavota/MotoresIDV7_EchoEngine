/************************************************************************/
/**
 * @file eeTime.h
 * @author Diego Castellanos
 * @date 02/12/21
 * @brief
 * The Time module for all time managing.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesUtilities.h"
#include <eeModule.h>

namespace eeEngineSDK {
/**
 * @brief
 * The Time module for all time managing.
 */
class EE_UTILITY_EXPORT Time : public Module<Time>
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  Time();
  /**
   * @brief
   * Default destructor.
   */
  ~Time() = default;

  /**
   * @brief
   * Returns deltaTime.
   *
   * @description
   * Returns the time elapsed since last update.
   *
   * @return
   * The time elapsed since last update.
   */
  float
  getDeltaTime();

  /**
   * @brief
   * Updates to change deltaTime.
   *
   * @description
   * Updates every frame to calculate time elapsed.
   */
  void
  update();

 private:
  /**
   * Times at the start of each frame.
   */
  std::chrono::steady_clock::time_point m_start;
  /**
   * Time elapsed since last frame.
   */
  float m_deltaTime = 0.0f;
};
}