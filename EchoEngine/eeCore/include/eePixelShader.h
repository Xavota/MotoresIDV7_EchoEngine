/************************************************************************/
/**
 * @file eePixelShader.h
 * @author Diego Castellanos
 * @date 08/10/21
 * @brief
 * The pixel shader for the graphic memory to paint every pixel.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
/**
 * @brief
 * The pixel shader for the graphic memory to paint every pixel.
 */
class EE_CORE_EXPORT PixelShader
{
 public:
  /**
   * @brief
   * Default constructor
   */
  PixelShader() = default;
  /**
   * @brief
   * Default destructor
   */
  virtual
  ~PixelShader() = default;

  /**
   * @brief
   * Initializes the shader.
   *
   * @description
   * Initializes the shader from a file.
   *
   * @param fileName
   * The name of the file containing the shader.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  virtual bool
  compileFromFile(const String&/*fileName*/) { return true; }
  /**
   * @brief
   * Initializes the shader.
   *
   * @description
   * Initializes the shader from a string.
   *
   * @param fileName
   * The string for the shader to compile.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  virtual bool
  compileFromString(const String& /*shaderString*/){return true;}

  /**
   * @brief
   * Set to graphics api.
   *
   * @description
   * Sets the shader for the graphic memory to use, only for override in graphics
   * api specializations.
   */
  virtual void
  use() {}

 private:
  /**
   * The string of the shader, for further modifying.
   */
  String m_shaderString;
};
}
