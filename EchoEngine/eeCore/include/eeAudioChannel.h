/************************************************************************/
/**
 * @file eeAudioChannel.h
 * @author Diego Castellanos
 * @date 19/08/22
 * @brief
 * The channel class, that plays the data of an audio.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once

#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
/**
 * @brief
 * The channel class, that plays the data of an audio.
 */
class AudioChannel
{
 public:
  /**
   * @brief
   * Default constructor
   */
  AudioChannel() = default;
  /**
   * @brief
   * Default destructor
   */
  ~AudioChannel() = default;

  
  void
  PlaySound(WPtr<Audio> mySound);
  //void
  //PlaySyntheticSound(SynthetiseSound* sound);
  void
  Stop();
  void
  WriteSoundData(float* data, int count, float parentPitch);

  bool
  GetPaused() const { return paused; }
  void
  SetPaused(bool value) { paused = value; }

  bool
  GetLoop() const { return loop; }
  void
  SetLoop(bool value) { loop = value; }

  float
  GetVolume() const { return volume; }
  void
  SetVolume(float value)
  {
    volume = value;
  }

  float
  GetPitch() const { return pitch; }
  void
  SetPitch(float value)
  {
    if (value < 0.25f) pitch = 0.25f;
    else if (value > 4.0f) pitch = 4.0f;
    else pitch = value;
  }

  float
  GetPan() const { return pan; }
  void
  SetPan(float value)
  {
    if (value < -1.0f) pan = -1.0f;
    else if (value > 1.0f) pan = 1.0f;
    else pan = value;
    updatePan();
  }

  float
  getPositionSec();
  float
  getPositionFreq()
  {
    return position;
  }
  float
  getMaxPositionSec();
  float
  getMaxPositionFreq();
  void
  seek(float second);
  void
  seekFreq(uint32 freq)
  {
    position = static_cast<float>(freq);
  }

  //void
  //addSoundEffect(SoundEffect* sfx)
  //{
  //  m_effects.emplace_back(sfx);
  //}

 private:
  void
  updatePan();

  WPtr<Audio> sound;
  float position;

  bool paused;

  bool loop;

  float volume;

  float pitch;

  float leftGain;
  float rightGain;
  float pan;

  //SynthetiseSound* syntheticSound;
  //
  //std::vector<SoundEffect*> m_effects;
};
}