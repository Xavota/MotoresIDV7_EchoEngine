#include "eeFModAudioManager.h"

#include <eeMemoryManager.h>

#include "eeFModSound.h"
#include "eeFModAudio.h"

#define FMOD_ERROR_CHECK(FMOD_RESULT) if (r != FMOD_OK) return false;

namespace eeEngineSDK {
bool
FModAudioManager::init(int32 maxAudioChannels)
{
  FMOD_RESULT r;

  m_maxChannels = maxAudioChannels;

  r = FMOD::System_Create(&m_fmodSystem);
  FMOD_ERROR_CHECK(r);

  r = m_fmodSystem->init(m_maxChannels, FMOD_INIT_NORMAL, nullptr);
  FMOD_ERROR_CHECK(r);


  return true;
}

void
FModAudioManager::update(float deltaTime)
{
  FMOD_RESULT r;

  Vector<SIZE_T> deleteAudiosIndices;
  SIZE_T audiosPlayingCount = m_playingSounds.size();

  for (SIZE_T i = 0; i < audiosPlayingCount; ++i) {
    if (m_playingSounds[i].playingAudio) {
      SPtr<FModAudio> fmodAudio =
      MemoryManager::instance().reinterpretPtr<FModAudio>(
                                               m_playingSounds[i].playingAudio);

      if (m_playingSounds[i].playingSubAudioIndex == 0) {
        FMOD::Sound* soundToPlay = nullptr;
        if (fmodAudio->numSubSounds == 0) {
          soundToPlay = fmodAudio->soundResource;
        }
        else {
          fmodAudio->soundResource->getSubSound(0, &soundToPlay);
        }

        ++m_playingSounds[i].playingSubAudioIndex;

        r = m_fmodSystem->playSound(soundToPlay, 0, false, &fmodAudio->channel);
        if (r != FMOD_OK) {
          deleteAudiosIndices.push_back(i);
          continue;
        }
      }
      else {
        bool isPlayingAudio = false;
        fmodAudio->channel->isPlaying(&isPlayingAudio);

        if (!isPlayingAudio) {
          if (m_playingSounds[i].playingSubAudioIndex < fmodAudio->numSubSounds) {
            FMOD::Sound* soundToPlay = nullptr;
            fmodAudio->soundResource->getSubSound(
            m_playingSounds[i].playingSubAudioIndex++, &soundToPlay);

            r = m_fmodSystem->playSound(soundToPlay, 0, false, &fmodAudio->channel);
            if (r != FMOD_OK) {
              deleteAudiosIndices.push_back(i);
              continue;
            }
          }
          else {
            deleteAudiosIndices.push_back(i);
            continue;
          }
        }
      }
    }
  }

  for (auto& dai : deleteAudiosIndices) {
    m_playingSounds.erase(m_playingSounds.begin() + dai);  
  }
}

bool
FModAudioManager::createSound(const String& soundFilePathSound,
                              SPtr<Sound>& outSoundSrc)
{
  outSoundSrc = MemoryManager::instance().newPtr<FModSound>();

  SPtr<FModSound> fmodSound =
  MemoryManager::instance().reinterpretPtr<FModSound>(outSoundSrc); 

  FMOD_RESULT r = m_fmodSystem->createSound(soundFilePathSound.c_str(),
                                            FMOD_DEFAULT,
                                            nullptr,
                                            fmodSound->getResource());
  FMOD_ERROR_CHECK(r);

  return true;
}

bool
FModAudioManager::createAudio(const String& audioFilePath,
                              SPtr<Audio>& outAudioPtr)
{
  outAudioPtr = MemoryManager::instance().newPtr<FModAudio>();
  
  SPtr<FModAudio> fmodAudio =
  MemoryManager::instance().reinterpretPtr<FModAudio>(outAudioPtr);

  FMOD_RESULT r = m_fmodSystem->createStream(audioFilePath.c_str(),
                                             FMOD_INIT_NORMAL | FMOD_2D,
                                             0,
                                             &fmodAudio->soundResource);
  FMOD_ERROR_CHECK(r);

  fmodAudio->soundResource->getNumSubSounds(&fmodAudio->numSubSounds);

  return true;
}

bool
FModAudioManager::playSound(SPtr<Sound> soundSrc)
{
  SPtr<FModSound> fmodSound =
  MemoryManager::instance().reinterpretPtr<FModSound>(soundSrc);

  FMOD_RESULT r = m_fmodSystem->playSound(*fmodSound->getResource(),
                                          0,
                                          false,
                                          fmodSound->getChannel());
  FMOD_ERROR_CHECK(r);

  return true;
}

bool
FModAudioManager::playAudio(SPtr<Audio> audioPtr)
{
  m_playingSounds.emplace_back(PlayingAudioInstance{audioPtr, 0});

  return true;
}



EE_EXTERN EE_PLUGIN_EXPORT void
initPlugin()
{
  AudioManager::startUp<FModAudioManager>();
}
}