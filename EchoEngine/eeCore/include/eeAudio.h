/************************************************************************/
/**
 * @file eeAudio.h
 * @author Diego Castellanos
 * @date 20/06/22
 * @brief
 * The sound resource. It's a long audio and it's loaded by parts in memory
 * while playing in a loop. It's used by the Audio manager to play it with the
 * other sounds and audios.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
/**
 * @brief
 * The sound resource. It's a long audio and it's loaded by parts in memory
 * while playing in a loop. It's used by the Audio manager to play it with the
 * other sounds and audios.
 */
class Audio
{
public:
  /**
   * @brief
   * Default constructor.
   */
  Audio() = default;
  /**
   * @brief
   * Default destructor.
   */
  virtual
  ~Audio() = default;

private:

};
}
