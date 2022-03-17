/************************************************************************/
/**
 * @file eeVertexShader.h
 * @author Diego Castellanos
 * @date 08/10/21
 * @brief
 * The vertex shader for the graphic memory.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesDX11.h"
#include <eeVertexShader.h>

namespace eeEngineSDK {
/**
 * @brief
 * The vertex shader for the graphic memory.
 */
class EE_PLUGINDX11_EXPORT DX11VertexShader : public VertexShader
{
 public:
  /**
   * @brief
   * Default constructor
   */
  DX11VertexShader() = default;
  /**
   * @brief
   * Default destructor
   */
  ~DX11VertexShader();

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
  bool
  compileFromFile(const String& fileName) override;
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
  bool
  compileFromString(const String& shaderString) override;

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
   * @brief
   * Creates the input layout.
   *
   * @description
   * Automatically creates the input layout using reflexion.
   *
   * @param pShaderBlob
   * The blob with the vertex shader information for the reflexion.
   *
   * @return
   * If it succeeds or fails.
   */
  HRESULT 
  createInputLayout(ID3DBlob* pShaderBlob);

  /**
   * The DX11 pixel shader.
   */
  ID3D11VertexShader* m_shader = nullptr;
  /**
   * The DX11 input layout. **TODO: HARCODED**
   */
  ID3D11InputLayout* m_inputLayout = nullptr;
};
}
