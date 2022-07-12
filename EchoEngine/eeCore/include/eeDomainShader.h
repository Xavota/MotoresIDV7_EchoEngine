/************************************************************************/
/**
 * @file eeDomainShader.h
 * @author Diego Castellanos
 * @date 04/07/22
 * @brief
 * The shader for the hull to vertex calculations.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
/**
 * @brief
 * The shader for the hull to vertex calculations.
 */
class DomainShader
{
 public:
  /**
   * @brief
   * Default constructor
   */
  DomainShader() = default;
  /**
   * @brief
   * Default destructor
   */
  virtual
  ~DomainShader() = default;

  /**
   * @brief
   * Initializes the shader.
   *
   * @description
   * Initializes the shader from a file.
   *
   * @param fileName
   * The name of the file containing the shader.
   * @param functionName
   * The name of the function it will compile for this shader.
   * @param macroDefinitions
   * The macros to compile the shader with.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  virtual bool
  compileFromFile(const String& /*fileName*/,
                  const String& /*functionName*/,
                  const Vector<ShaderMacro>& /*macroDefinitions*/) {return true;}
  /**
   * @brief
   * Initializes the shader.
   *
   * @description
   * Initializes the shader from a string.
   *
   * @param fileName
   * The string for the shader to compile.
   * @param functionName
   * The name of the function it will compile for this shader.
   * @param macroDefinitions
   * The macros to compile the shader with.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  virtual bool
  compileFromString(const String& /*shaderString*/,
                    const String& /*functionName*/,
                    const Vector<ShaderMacro>& /*macroDefinitions*/) {return true;}

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

  /**
   * @brief
   * Releases the data.
   *
   * @description
   * Deletes the memory of all data allocated.
   */
  virtual void
  release() {};

 private:
  /**
   * The string of the shader, for further modifying.
   */
  String m_shaderString;
};
}