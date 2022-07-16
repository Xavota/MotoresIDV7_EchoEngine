/************************************************************************/
/**
 * @file eeImage.h
 * @author Diego Castellanos
 * @date 01/02/22
 * @brief The image resource for the textures.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

#include <eeColor.h>

namespace eeEngineSDK {
/**
 * @brief
 * The image resource for the textures.
 */
class EE_CORE_EXPORT Image
{
 public: 
  /**
   * @brief
   * Default constructor
   */
  Image() = default;
  /**
   * @brief
   * Copy constructor
   */
  Image(const Image& other);
  /**
   * @brief
   * Loads an image from a file.
   *
   * @description
   * Loads an image from a file and stores its pixels values.
   *
   * @param path
   * The file path for the image.
   */
  Image(const WString& path);
  /**
   * @brief
   * Copy constructor
   */
  ~Image();

  /**
   * @brief
   * Loads an image from a file.
   *
   * @description
   * Loads an image from a file and stores its pixels values.
   *
   * @param path
   * The file path for the image.
   *
   * @return
   * Weather it succeed or failed to load.
   */
  bool
  loadFromFile(const WString& path);

  /**
   * @brief
   * Get the image data.
   *
   * @description
   * Returns the array of color data.
   *
   * @return
   * The array of color data.
   */
  FORCEINLINE ColorI*
  getData()
  {
    return m_data;
  }

  /**
   * @brief
   * Get the image width.
   *
   * @description
   * Returns the width of the image.
   *
   * @return
   * The width of the image.
   */
  FORCEINLINE uint32
  getWidth()
  {
    return m_width;
  }
  /**
   * @brief
   * Get the image height.
   *
   * @description
   * Returns the height of the image.
   *
   * @return
   * The height of the image.
   */
  FORCEINLINE uint32
  getHeight()
  {
    return m_height;
  }
  /**
   * @brief
   * Get the image data real size.
   *
   * @description
   * Returns the real size of the image to use as buffer.
   *
   * @return
   * The real size of the image to use as buffer.
   */
  FORCEINLINE uint32
  getDataSize()
  {
    return m_width * sizeof(ColorI);
  }

  /**
   * @brief
   * Get the pixel color.
   *
   * @description
   * Returns the color of a pixel in the given coordinate.
   *
   * @param x
   * The x coord of the pixel.
   * @param y
   * The y coord of the pixel.
   *
   * @return
   * The color of a pixel in the given coordinate.
   */
  ColorI
  getPixelColor(int32 x, int32 y)
  {
    return m_data[y * m_width + x];
  }
  /**
   * @brief
   * Set the pixel color.
   *
   * @description
   * Sets the color of a pixel in the given coordinate.
   *
   * @param x
   * The x coord of the pixel.
   * @param y
   * The y coord of the pixel.
   * @param newColor
   * The new color for the pixel.
   *
   * @return
   * The color of a pixel in the given coordinate.
   */
  void
  setPixelColor(int32 x, int32 y, ColorI newColor)
  {
    m_data[y * m_width + x] = newColor;
  }

 private:
  /**
   * The width of the image.
   */
  int32 m_width = 0;
  /**
   * The height of the image.
   */
  int32 m_height = 0;

  /**
   * The data of the image.
   */
  ColorI* m_data = nullptr;
};
}
