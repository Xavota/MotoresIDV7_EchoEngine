/************************************************************************/
/**
 * @file eeClock.h
 * @author Diego Castellanos
 * @date 25/10/22
 * @brief
 * A clock object for managing time periods.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK {
/**
 * @brief
 * A clock object for managing time periods.
 */
class EE_UTILITY_EXPORT Clock
{
 public:
  /**
   * @brief
   * Default constructor.
   */
   Clock();
  /**
   * @brief
   * Default destructor.
   */
  ~Clock() = default;

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
  geTimeElapsed();

  /**
   * @brief
   * Updates to change deltaTime.
   *
   * @description
   * Updates every frame to calculate time elapsed.
   */
  void
  update();
  /**
   * @brief
   * Restarts the clock.
   *
   * @description
   * Restarts the time of the clock to zero and returns the last time.
   * 
   * @return
   * The last time elapsed from the clock.
   */
  float
  restart();

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
