/************************************************************************/
/**
 * @file eeDX11PixelShader.h
 * @author Diego Castellanos
 * @date 22/10/21
 * @brief
 * The pixel shader for the graphic memory to paint every pixel.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesDX11.h"
#include <eePixelShader.h>

namespace eeEngineSDK {
/**
 * @brief
 * The pixel shader for the graphic memory to paint every pixel.
 */
class EE_PLUGINDX11_EXPORT DX11PixelShader : public PixelShader
{
 public:
  /**
   * @brief
   * Default constructor
   */
  DX11PixelShader() = default;
  /**
   * @brief
   * Default destructor
   */
  ~DX11PixelShader();

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
  compileFromFile(const WString& fileName,
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
   * The DX11 pixel shader.
   */
  ID3D11PixelShader* m_shader = nullptr;
};
}