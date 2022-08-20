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
struct EE_CORE_EXPORT Audio
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  Audio() = default;
  /**
   * @brief
   * Default constructor.
   */
  Audio(const char* path);
  /**
   * @brief
   * Default destructor.
   */
  virtual
  ~Audio();


  /**
   * The number of samples per second the audio is going to play.
   */
  uint32 samplingRate;
  /**
   * The number of audio channels the audio has.
   */
  uint16 numChannels;
  /**
   * The data of the audio.
   */
  float* data;
  /**
   * The total number of samples in the data.
   */
  uint32 count;
};
}
