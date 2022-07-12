/************************************************************************/
/**
 * @file eeDX11HullShader.h
 * @author Diego Castellanos
 * @date 04/07/22
 * @brief
 * The shader that creates and sends the control points from the vertex, to the
 * domain shader.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesDX11.h"
#include <eeHullShader.h>

namespace eeEngineSDK {
/**
 * @brief
 * The shader that creates and sends the control points from the vertex, to the
 * domain shader.
 */
class EE_PLUGINDX11_EXPORT DX11HullShader : public HullShader
{
 public:
  /**
   * @brief
   * Default constructor
   */
  DX11HullShader() = default;
  /**
   * @brief
   * Default destructor
   */
  virtual
  ~DX11HullShader() = default;

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
  bool
  compileFromFile(const String& fileName,
                  const String& functionName,
                  const Vector<ShaderMacro>& macroDefinitions) override;
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
  bool
  compileFromString(const String& shaderString,
                    const String& functionName,
                    const Vector<ShaderMacro>& macroDefinitions) override;

  /**
   * @brief
   * Set to graphics api.
   *
   * @description
   * Sets the shader for the graphic memory to use, only for override in graphics
   * api specializations.
   */
  void
  use() override;

  /**
   * @brief
   * Releases the data.
   *
   * @description
   * Deletes the memory of all data allocated.
   */
  void
  release() override;

 private:
  /**
   * The DX11 hull shader.
   */
  ID3D11HullShader* m_shader = nullptr;
};
}