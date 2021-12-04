/************************************************************************/
/**
 * @file eeTexture.h
 * @author Diego Castellanos
 * @date 07/10/21
 * @brief
 * The input texture for the models. It's sent to the graphics memory to be
 * used.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include "eeBuffer.h"
#include "eeSamplerState.h"

namespace eeEngineSDK {
/**
 * @brief
 * The input texture for the models. It's sent to the graphics memory to be
 * used.
 */
class EE_CORE_EXPORT Texture
{
 public:
   /**
   * @brief
   * Default constructor
   */
  Texture() = default;
  /**
  * @brief
  * Default destructor
  */
  virtual 
  ~Texture() = default;

  /**
  * @brief
  * Initializes the texture.
  *
  * @description
  * Initializes the texture from a file.
  *
  * @param fileName
  * The name of the file containing the texture.
  * @param desc
  * The descriptor for the sampler of the texture.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  virtual bool
  loadFromFile(const String /*fileName*/, SamplerStateDesc /*desc*/) { return true; }

  /**
  * @brief
  * Initializes the texture.
  *
  * @description
  * Initializes the texture from a buffer.
  *
  * @param buffer
  * The buffer containing the information about the texture.
  * @param desc
  * The descriptor for the sampler of the texture.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  virtual bool
  loadFromBuffer(void* /*buffer*/, SamplerStateDesc /*desc*/){return true;}

  /**
  * @brief
  * Set to graphics api.
  *
  * @description
  * Sets the shader for the graphic memory to use, only for override in graphics
  * api specializations.
  */
  virtual void
  use(){}

  /**
  * @brief
  * Releases the data.
  *
  * @description
  * Deletes the memory of all data allocated.
  */
  virtual void
  release() {};


 protected:
   String name;
};
}
