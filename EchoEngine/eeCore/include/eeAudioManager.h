/************************************************************************/
/**
 * @file eeAudioManager.h
 * @author Diego Castellanos
 * @date 15/06/22
 * @brief
 * The manager for the audio utilities. For loading and playing audios and
 * sounds.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeModule.h>

namespace eeEngineSDK {
class Sound;

/**
 * @brief
 * The manager for the audio utilities. For loading and playing audios and
 * sounds.
 */
class EE_CORE_EXPORT AudioManager : public Module<AudioManager>
{
 public:
  /**
   * @brief
   * Default constructor
   */
  AudioManager() = default;
  /**
   * @brief
   * Default destructor
   */
  ~AudioManager() = default;

  /**
   * @brief
   * Initializes the api.
   *
   * @description
   * Initializes the audio manager api.
   * 
   * @param maxAudioChannels
   * The maximum number of channels that can play at the same time.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  virtual bool
  init(int32 /*maxAudioChannels*/ = 64) { return true; }

  /**
   * @brief
   * Updates the api.
   *
   * @description
   * Updates the sounds that are playing simultaneously or anything else.
   * 
   * @param deltaTime
   * The time in seconds since the last frame.
   */
  virtual void
  update(float /*deltaTime*/) {}

  /**
   * @brief
   * Creates a sound resource.
   *
   * @description
   * Creates and initializes a sound resource.
   * 
   * @param soundFilePath
   * The file path of the sound.
   * @param outSoundPtr
   * The sound pointer to be initialized.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  virtual bool
  createSound(const String& /*soundFilePathSound*/, SPtr<Sound>& /*outSoundSrc*/) { return true; }

  /**
   * @brief
   * Creates an audio resource.
   *
   * @description
   * Creates and initializes an audio resource.
   * 
   * @param audioFilePath
   * The file path of the audio.
   * @param outAudioPtr
   * The audio pointer to be initialized.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  virtual bool
  createAudio(const String& /*audioFilePath*/, SPtr<Audio>& /*outAudioPtr*/) { return true; }

  /**
   * @brief
   * Plays a sound resource.
   *
   * @description
   * Starts playing a sound resource.
   * 
   * @param soundPtr
   * The sound pointer to play.
   *
   * @return
   * Weather it succeed or failed to play.
   */
  virtual bool
  playSound(SPtr<Sound> /*soundSrc*/) { return true; }

  /**
   * @brief
   * Plays an audio resource.
   *
   * @description
   * Starts playing an audio resource.
   * 
   * @param audioPtr
   * The audio pointer to play.
   *
   * @return
   * Weather it succeed or failed to play.
   */
  virtual bool
  playAudio(SPtr<Audio> /*audioPtr*/) { return true; }
};
}
