/************************************************************************/
/**
 * @file eeDX11Texture.h
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
   * Creates a texture 2D.
   *
   * @description
   * Creates a 2 dimensional texture with the bindings and data specified.
   *
   * @param bindFlags
   * The bindings for the texture.
   * @param texSize
   * The size of the texture.
   * @param format
   * The format for the texture.
   * @param mipLevels
   * The number of mip levels it will create.
   */
  DX11Texture(uint32 bindFlags,
              const Point2D& texSize,
              eTEXTURE_FORMAT::E format = eTEXTURE_FORMAT::kNone,
              uint32 mipLevels = 0u);
  /**
   * @brief
   * Default destructor
   */
  ~DX11Texture();

  /**
   * @brief
   * Creates a texture 2D.
   *
   * @description
   * Creates a 2 dimensional texture with the bindings and data specified.
   *
   * @param bindFlags
   * The bindings for the texture.
   * @param texSize
   * The size of the texture.
   * @param format
   * The format for the texture.
   * @param mipLevels
   * The number of mip levels it will create.
   *
   * @return
   * Weather it succeed or failed to create.
   */
  bool
  create2D(uint32 bindFlags,
           const Point2D& texSize,
           eTEXTURE_FORMAT::E format = eTEXTURE_FORMAT::kUnknown,
           uint32 mipLevels = 0u) override;

           
  /**
   * @brief
   * Creates as the back buffer.
   *
   * @description
   * Creates a render target as the back buffer.
   *
   * @return
   * Weather it succeed or failed to create.
   */
  bool
  createAsBackBuffer() override;

  /**
   * @brief
   * Gets the shader resource data.
   *
   * @description
   * Returns the low level graphic api data of the shader resource.
   *
   * @return
   * Low level graphic api data of the shader resource.
   */
  ID3D11ShaderResourceView*
  getShaderResource() { return m_shaderResource; }

  /**
   * @brief
   * Gets the render target data.
   *
   * @description
   * Returns the low level graphic api data of the render target.
   *
   * @return
   * Low level graphic api data of the render target.
   */
  ID3D11RenderTargetView*
  getRenderTarget() { return m_renderTarget; }

  /**
   * @brief
   * Gets the depth stencil data.
   *
   * @description
   * Returns the low level graphic api data of the depth stencil.
   *
   * @return
   * Low level graphic api data of the depth stencil.
   */
  ID3D11DepthStencilView*
  getDepthStencil() { return m_depthStencilView; }

  /**
   * @brief
   * Set the shader resource to the graphics api.
   *
   * @description
   * Sets the shader resource for the graphic memory to use, only for override
   * in graphics api specializations.
   */
  void
  useAsShaderResource() override;
  
  /**
   * @brief
   * Loads from images.
   *
   * @description
   * Loads images for the shader resources.
   * 
   * @param images
   * The vector of images to use.
   */
  void
  loadImages(const Vector<SPtr<Image>>& images) override;
  
  /**
   * @brief
   * Generate mipmaps.
   *
   * @description
   * Generates the mipmaps of the texture automatically.
   */
  void
  generateMipmaps() override;

  /**
   * @brief
   * Cleans the resource.
   *
   * @description
   * Cleans the resource.
   *
   * @parm screenColor
   * The background color.
   */
  void
  clean(Color screenColor = Color(0.0f, 0.0f, 0.0f, 1.0f)) override;

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
  ID3D11ShaderResourceView* m_shaderResource = nullptr;
  /**
   * The dx11 render target.
   */
  ID3D11RenderTargetView* m_renderTarget = nullptr;
  /**
   * The depth stencil resource data.
   */
  ID3D11DepthStencilView* m_depthStencilView = nullptr;
  /**
   * The resource of the texture.
   */
  ID3D11Texture2D* m_textureResource = nullptr;

  /**
   * sampler state. The sampler of the texture.
   */
  uint32 m_bindFlags = eTEXTURE_BIND_FLAGS::kNone;
};
}
