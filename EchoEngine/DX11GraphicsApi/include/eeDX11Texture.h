/************************************************************************/
/**
 * @file eeTexture.h
 * @author Diego Castellanos
 * @date 21/10/21
 * @brief
 * The input texture for the models. It's sent to the graphics memory to be
 * used.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesDX11.h"
#include <eeTexture.h>
#pragma warning(push, 0)   
#include <d3d11.h>
#pragma warning(pop)   

namespace eeEngineSDK {
/**
 * @brief
 * The input texture for the models. It's sent to the graphics memory to be
 * used.
 */
class EE_PLUGINDX11_EXPORT DX11Texture : public Texture
{
public:
  /**
  * @brief
  * Default constructor
  */
  DX11Texture() = default;
  /**
  * @brief
  * Default destructor
  */
  ~DX11Texture();

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
  bool
  loadFromFile(const String fileName, SamplerStateDesc desc) override;

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
  bool
  loadFromBuffer(SPtr<void> buffer, SamplerStateDesc desc) override;

  ID3D11ShaderResourceView*
  getResource() { return m_tex; }

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
  * DX11 shader resource view. The buffer that is passed to the graphic memory.
  */
  ID3D11ShaderResourceView* m_tex = nullptr;
  /**
  * sampler state. The sampler of the texture.
  */
  SPtr<SamplerState> m_sampler = nullptr;
};
}
