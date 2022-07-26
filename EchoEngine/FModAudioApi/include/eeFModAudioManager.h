/************************************************************************/
/**
 * @file eeFModAudioManager.h
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
#include "eePrerequisitesFMod.h"
#include <eeAudioManager.h>

#include <fmod.hpp>

namespace eeEngineSDK {
/**
 * @brief
 * The instance of an audio that is currently playing.
 */
struct PlayingAudioInstance
{
  /**
   * The audio that is playing.
   */
  SPtr<Audio> playingAudio;
  /**
   * The audio that is playing.
   */
  int32 playingSubAudioIndex = 0;
};
/**
 * @brief
 * The manager for the audio utilities. For loading and playing audios and
 * sounds.
 */
class EE_FMOD_EXPORT FModAudioManager : public AudioManager
{
 public:
  /**
   * @brief
   * Default constructor
   */
  FModAudioManager() = default;
  /**
   * @brief
   * Default destructor
   */
  ~FModAudioManager() = default;

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
  bool
  init(int32 maxAudioChannels = 64) override;

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
  void
  update(float deltaTime) override;

  /**
   * @brief
   * Creates a sound resource.
   *
   * @description
   * Creates and initializes a sound resource.
   * 
   * @param soundFilePath
   * The file path of the audio.
   * @param outSoundPtr
   * The sound pointer to be initialized.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  bool
  createSound(const String& soundFilePathSound, SPtr<Sound>& outSoundSrc) override;

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
  bool
  createAudio(const String& audioFilePath, SPtr<Audio>& outAudioPtr) override;

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
  bool
  playSound(SPtr<Sound> soundSrc) override;

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
  bool
  playAudio(SPtr<Audio> audioPtr) override;

 private:
  /**
   * The system of the fmod library.
   */
  FMOD::System* m_fmodSystem = nullptr;

  /**
   * The max number of channels for the entire system.
   */
  int32 m_maxChannels = 64;

  /**
   * The sounds that are currently playing.
   */
  Vector<PlayingAudioInstance> m_playingSounds;
};
}