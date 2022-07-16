/**
 * @file eeOGLVertexShader.h
 * @author Diego Castellanos
 * @date 13/05/22
 * @brief
 * The vertex shader for the graphic memory.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesOGL.h"
#include <eeVertexShader.h>

namespace eeEngineSDK {
/**
 * @brief
 * The vertex shader for the graphic memory.
 */
class EE_PLUGINOGL_EXPORT OGLVertexShader : public VertexShader
{
 public:
  /**
   * @brief
   * Default constructor
   */
  OGLVertexShader() = default;
  /**
   * @brief
   * Default destructor
   */
  ~OGLVertexShader();

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
   * Releases the data.
   *
   * @description
   * Deletes the memory of all data allocated.
   */
  void
  release() override;

  /**
   * @brief
   * Getter for the OGL shader index.
   *
   * @description
   * Returns the index of the shader generated by openGL.
   * 
   * @return
   * The index of the shader generated by openGL.
   */
  inline uint32
  getShaderIndex()
  {
    return m_shader;
  }

 private:
  ///**
  // * @brief
  // * Creates the input layout.
  // *
  // * @description
  // * Automatically creates the input layout using reflexion.
  // *
  // * @param pShaderBlob
  // * The blob with the vertex shader information for the reflexion.
  // *
  // * @return
  // * If it succeeds or fails.
  // */
  //HRESULT 
  //createInputLayout(ID3DBlob* pShaderBlob);
  //
  /**
   * The OGL vertex shader.
   */
  uint32 m_shader = 0;
  ///**
  // * The OGL input layout. **TODO: HARCODED**
  // */
  //ID3D11InputLayout* m_inputLayout = nullptr;
};
}