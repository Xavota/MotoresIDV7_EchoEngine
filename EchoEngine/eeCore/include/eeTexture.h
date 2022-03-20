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

#include <eeVector2.h>

#include "eeBuffer.h"
#include "eeSamplerState.h"

#include "eeColor.h"

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
  virtual bool
  create2D(uint32 /*bindFlags*/,
           const Point2D& /*texSize*/,
           eTEXTURE_FORMAT::E /*format*/ = eTEXTURE_FORMAT::kNone,
           uint32 /*mipLevels*/ = 0u) { return true; }
           

           
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
  virtual bool
  createAsBackBuffer() { return true; }

  /**
   * @brief
   * Set as shader resource to the graphics api.
   *
   * @description
   * Sets as shader resource for the graphic memory to use, only for override
   * in graphics api specializations.
   */
  virtual void
  useAsShaderResource() {}
  
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
  virtual void
  loadImages(Vector<SPtr<Image>> images) { m_images = images; }

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
  virtual void
  clean(Color /*screenColor*/ = Color(0.0f, 0.0f, 0.0f, 1.0f)) {}

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
  /**
   * The name of the texture.
   */
  String name;

  /**
   * The images for the shader resources.
   */
  Vector<SPtr<Image>> m_images;
};
}
