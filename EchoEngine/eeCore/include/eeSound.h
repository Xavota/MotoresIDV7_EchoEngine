/************************************************************************/
/**
 * @file eeSound.h
 * @author Diego Castellanos
 * @date 16/06/22
 * @brief
 * The sound resource. It's a short sound and it's loaded all in memory while
 * playing it.It's used by the Audio manager to play it with the other sounds
 * and audios.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
/**
 * @brief
 * The sound resource. It's a short sound and it's loaded all in memory while
 * playing it.It's used by the Audio manager to play it with the other sounds
 * and audios.
 */
class EE_CORE_EXPORT Sound
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  Sound() = default;
  /**
   * @brief
   * Default destructor.
   */
  virtual
  ~Sound() = default;

 private:
  
};
}
