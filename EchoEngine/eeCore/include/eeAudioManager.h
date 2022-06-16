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
};
}
