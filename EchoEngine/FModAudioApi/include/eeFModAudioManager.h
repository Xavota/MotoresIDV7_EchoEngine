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
#include "eePrerequisitesFMod.h"
#include <eeModule.h>

namespace eeEngineSDK {
/**
 * @brief
 * The manager for the audio utilities. For loading and playing audios and
 * sounds.
 */
class EE_FMOD_EXPORT FModAudioManager : public Module<FModAudioManager>
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
};
}