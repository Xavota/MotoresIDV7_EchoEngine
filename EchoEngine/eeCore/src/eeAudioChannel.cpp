#include "eeAudioChannel.h"

#include <eeMath.h>

#include "eeAudio.h"

#define DEF_FREQ 44100

namespace eeEngineSDK {
void
AudioChannel::PlaySound(WPtr<Audio> mySound)
{
}
void
AudioChannel::Stop()
{
}
void
AudioChannel::WriteSoundData(float* data, int count, float parentPitch)
{
  // If there is no sound assigned to the channel do nothing
  if (sound.expired() || !sound.lock()->data
   || sound.lock()->numChannels == 0 || paused) return;
  // We need to write "count" samples to the "data" array
  // Since output is stereo it is easier to advance in pairs
  auto sSound = sound.lock();
  
  //auto effectSoundData = new float[sound->count];
  //memcpy(effectSoundData,
  //       sound->data,
  //       sound->count * sizeof(float));
  //for (auto& eff : m_effects) {
  //  if (eff) eff->applyPreEffect(effectSoundData, sound->count);
  //}

  for (int i = 0; i < count; i += 2) {
    uint32 realPosition = static_cast<uint32>(position)
                        * static_cast<uint32>(sSound->numChannels);
    // If we have reached the end of the sound, stop and return
    if (realPosition + sSound->numChannels - 1 >= sSound->count) {
      if (loop) {
        position = 0;
        realPosition = 0;
      }
      else {
        Stop();
        return;
      }
    }

    // Read value from the sound data at the current position
    if (sSound->numChannels == 1) {
      float value = (float)(sSound->data[realPosition] * volume);
      //float value = (float)(effectSoundData[realPosition] * volume);
      // Write value to both the left and right channels
      data[i] += (float)(value * leftGain);
      data[i + 1] += (float)(value * rightGain);
    }
    else if (sSound->numChannels > 1) {
      // Write value to both the left and right channels
      data[i] += (float)(sSound->data[realPosition] * volume * leftGain);
      data[i + 1] += (float)(sSound->data[realPosition + 1] * volume * rightGain);
      //data[i] += (float)(effectSoundData[realPosition] * volume * leftGain);
      //data[i + 1] += (float)(effectSoundData[realPosition + 1] * volume * rightGain);
    }
    //if (syntheticSound) syntheticSound->getData(data, i);
    // Advance the position by one sample
    position += pitch * parentPitch;

  }

  //delete[] effectSoundData;

  //for (auto& eff : m_effects) {
  //  if (eff) eff->applyPostEffect(data, count);
  //}
}
float
AudioChannel::getPositionSec()
{
  if (!sound.expired()) {
    return position / sound.lock()->samplingRate;
  }
  else {
    return position / DEF_FREQ;
  }
}
float
AudioChannel::getMaxPositionSec()
{
  if (!sound.expired()) {
    auto sSound = sound.lock();
    return static_cast<float>(sSound->count
                           / (sSound->samplingRate * sSound->numChannels));
  }
  else {
    return 0;
  }
}
float
AudioChannel::getMaxPositionFreq()
{
  if (!sound.expired()) {
    auto sSound = sound.lock();
    return static_cast<float>(sSound->count / sSound->numChannels);
  }
  return 0;
}
void
AudioChannel::seek(float second)
{
  if (!sound.expired()) {
    seekFreq(static_cast<uint32>(second * sound.lock()->samplingRate));
  }
  else {
    seekFreq(static_cast<uint32>(second * DEF_FREQ));
  }
}
void
AudioChannel::updatePan()
{
  double angle = pan * static_cast<double>(Math::kPI) * 0.25;
  float sqrt_2 = Math::sqrt(2) * 0.5f;
  leftGain = (float)(sqrt_2 * (cos(angle) - sin(angle)));
  rightGain = (float)(sqrt_2 * (cos(angle) + sin(angle)));
}
}