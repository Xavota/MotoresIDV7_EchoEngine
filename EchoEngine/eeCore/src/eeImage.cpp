#include "eeImage.h"

#include <eeMemoryManager.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../externals/stb_image.h"

#include "eeStringUtilities.h"

namespace eeEngineSDK {
Image::Image(const Image& other)
{
  m_width = other.m_width;
  m_height = other.m_height;
  m_data = new ColorI[static_cast<SIZE_T>(m_width) * static_cast<SIZE_T>(m_height)];
  memcpy(m_data,
         other.m_data,
         static_cast<SIZE_T>(m_width)
       * static_cast<SIZE_T>(m_height)
       * sizeof(ColorI));
}
Image::Image(const WString& path)
{
  if (loadFromFile(path)) {
    m_data = nullptr;
  }
}
Image::~Image()
{
  MemoryManager::instance().rawSafeRelease<ColorI>(&m_data);
}
bool
Image::loadFromFile(const WString& path)
{
  int32 desiredChanels = 4;
  int32 channels = 0;
  uint8* image = stbi_load(eeWStringtoString(path).c_str(),
                           &m_width,
                           &m_height,
                           &channels,
                           desiredChanels);

  if (!image) {
    return false;
  }

  m_data = new ColorI[static_cast<SIZE_T>(m_width) * static_cast<SIZE_T>(m_height)];
  for (int32 i = 0; i < m_width * m_height; ++i) {
    m_data[i].r = image[i * 4 + 0];
    m_data[i].g = image[i * 4 + 1];
    m_data[i].b = image[i * 4 + 2];
    m_data[i].a = image[i * 4 + 3];
  }
  return true;
}
void
Image::loadFromPixelData(Byte* data, uint32 width, uint32 height)
{
  m_width = width;
  m_height = height;
  m_data = new ColorI[static_cast<SIZE_T>(m_width) * static_cast<SIZE_T>(m_height)];
  memcpy(m_data,
         data,
         static_cast<SIZE_T>(m_width)
       * static_cast<SIZE_T>(m_height)
       * sizeof(ColorI));
}
}