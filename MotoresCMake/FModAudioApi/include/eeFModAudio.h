#pragma once
class FModAudio
{
};

/************************************************************************/
/**
 * @file eeSound.h
 * @author Diego Castellanos
 * @date 16/06/22
 * @brief
 * The sound resource. It's a long audio and it's loaded by parts in memory
 * while playing in a loop. It's used by the Audio manager to play it with the
 * other sounds and audios.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesFMod.h"
#include <eeAudio.h>

#include <fmod.hpp>

namespace eeEngineSDK {
/**
 * @brief
 * The sound resource. It's a long audio and it's loaded by parts in memory
 * while playing in a loop. It's used by the Audio manager to play it with the
 * other sounds and audios.
 */
class EE_FMOD_EXPORT FModAudio : public Audio
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  FModAudio() = default;
  /**
   * @brief
   * Default destructor.
   */
  virtual
  ~FModAudio() = default;


  /**
   * The audio fmod resource.
   */
  FMOD::Sound* soundResource = nullptr;
  /**
   * The channel the sound is playing. Creo
   */
  FMOD::Channel* channel = nullptr;
  /**
   * The number of sounds that the audio is divided to load one at a time.
   */
  int32 numSubSounds = 0;
};
}
