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
#include "eePrerequisitesFMod.h"
#include <eeSound.h>

#include <fmod.hpp>

namespace eeEngineSDK {
/**
 * @brief
 * The sound resource. It's a short sound and it's loaded all in memory while
 * playing it.It's used by the Audio manager to play it with the other sounds
 * and audios.
 */
class EE_FMOD_EXPORT FModSound : public Sound
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  FModSound() = default;
  /**
   * @brief
   * Default destructor.
   */
  virtual
  ~FModSound() = default;

  
  /**
   * @brief
   * Getter of the sound resource.
   *
   * @description
   * Returns the fmod sound resource.
   *
   * @return
   * The fmod sound resource.
   */
  FORCEINLINE FMOD::Sound**
  getResource()
  {
    return &m_tempSound;
  }
  /**
   * @brief
   * Getter of the channel pointer.
   *
   * @description
   * Returns the fmod channel pointer.
   *
   * @return
   * The fmod channel pointer.
   */
  FORCEINLINE FMOD::Channel**
  getChannel()
  {
    return &m_channel;
  }

 private:
  /**
   * The sound fmod resource.
   */
  FMOD::Sound* m_tempSound = nullptr;
  /**
   * The channel the sound is playing. Creo
   */
  FMOD::Channel* m_channel = nullptr;
};
}
