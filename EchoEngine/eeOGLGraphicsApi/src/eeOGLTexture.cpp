#include "eeOGLTexture.h"
#pragma warning(push)
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#pragma warning(pop)

#include <eeMath.h>

#include <eeImage.h>

namespace eeEngineSDK {
OGLTexture::OGLTexture(uint32 bindFlags,
                       const Point2D& texSize,
                       eTEXTURE_FORMAT::E format,
                       uint32 mipLevels)
{
  create2D(bindFlags, texSize, format, mipLevels);
}
OGLTexture::~OGLTexture()
{
  release();
}
bool
OGLTexture::create2D(uint32 /*bindFlags*/,
                     const Point2D& texSize,
                     eTEXTURE_FORMAT::E format,
                     uint32 /*mipLevels*/)
{
  if (format == eTEXTURE_FORMAT::kNone) {
    format = eTEXTURE_FORMAT::kR32G32B32_Float;
  }

  //if (Math::hasFlag(bindFlags, eTEXTURE_BIND_FLAGS::kShaderResource)) {
    glGenTextures(1, &m_shaderResource);
    glBindTexture(GL_TEXTURE_2D, m_shaderResource);
    switch (format)
    {
    case eeEngineSDK::eTEXTURE_FORMAT::kR32G32B32A32_Float:
      m_textureFormat = GL_RGBA32F;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR32G32B32A32_Uint:
      m_textureFormat = GL_RGBA32UI;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR32G32B32A32_Sint:
      m_textureFormat = GL_RGBA32I;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR32G32B32A32_Typeless:
      m_textureFormat = GL_RGBA; // ?
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR32G32B32_Float:
      m_textureFormat = GL_RGB32F;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR32G32B32_Uint:
      m_textureFormat = GL_RGB32UI;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR32G32B32_Sint:
      m_textureFormat = GL_RGB32I;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR32G32B32_Typeless:
      m_textureFormat = GL_RGB; // ?
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR16G16B16A16_Float:
      m_textureFormat = GL_RGBA16F;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR16G16B16A16_Uint:
      m_textureFormat = GL_RGBA16UI;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR16G16B16A16_Unorm:
      //m_textureFormat = GL_RGBA16_UNORM;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR16G16B16A16_Sint:
      m_textureFormat = GL_RGBA16I;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR16G16B16A16_Snorm:
      m_textureFormat = GL_RGBA16_SNORM;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR16G16B16A16_Typeless:
      m_textureFormat = GL_RGBA16;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR8G8B8A8_Uint:
      m_textureFormat = GL_RGBA8UI;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR8G8B8A8_Unorm:
      //m_textureFormat = GL_RGBA8_UNORM;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR8G8B8A8_Unorm_Srgb:
      //m_textureFormat = GL_SRGB8_UNORM;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR8G8B8A8_Sint:
      m_textureFormat = GL_RGBA8I;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR8G8B8A8_Snorm:
      m_textureFormat = GL_RGBA8_SNORM;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR8G8B8A8_Typeless:
      m_textureFormat = GL_RGBA8;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kB8G8R8A8_Unorm:
      //m_textureFormat = GL_BGRA8_UNORM;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kB8G8R8A8_Unorm_Srgb:
      //m_textureFormat = GL_SBGRA_UNORM;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kB8G8R8A8_Typeless:
      m_textureFormat = GL_BGRA; // 8?
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR16_Float:
      m_textureFormat = GL_R16F;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR16_Uint:
      m_textureFormat = GL_R16UI;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR16_Unorm:
      //m_textureFormat = GL_R16_UNORM;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR16_Sint:
      m_textureFormat = GL_R16I;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR16_Snorm:
      m_textureFormat = GL_R16_SNORM;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR16_Typeless:
      m_textureFormat = GL_R16;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR8_Uint:
      m_textureFormat = GL_R8UI;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR8_Unorm:
      //m_textureFormat = GL_R8_UNORM;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR8_Sint:
      m_textureFormat = GL_R8I;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR8_Snorm:
      m_textureFormat = GL_R8_SNORM;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kR8_Typeless:
      m_textureFormat = GL_R8;
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kD32_Float:
      m_textureFormat = GL_DEPTH_COMPONENT; // ?
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kD24_Unorm_S8_Uint:
      m_textureFormat = GL_DEPTH_STENCIL; // ?
      break;
    case eeEngineSDK::eTEXTURE_FORMAT::kD16_Unorm:
      m_textureFormat = GL_DEPTH_COMPONENT; // ?
      break;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, m_textureFormat, texSize.x, texSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
  //}
  return false;
}
bool
OGLTexture::createAsBackBuffer()
{
  return false;
}
void
OGLTexture::useAsShaderResource()
{
}
void
OGLTexture::loadImages(const Vector<SPtr<Image>>& images)
{
  glBindTexture(GL_TEXTURE_2D, m_shaderResource);
  //for (int32 i = 0; i < 1000; ++i) {
  //  glTexImage2D(GL_TEXTURE_2D, i, m_textureFormat, images[0]->getWidth() * (1 / Math::pow(2, i)), images[0]->getHeight() * (1 / Math::pow(2, i)), 0, GL_RGBA, GL_UNSIGNED_BYTE, images[0]->getData());
  //}
  glTexImage2D(GL_TEXTURE_2D, 0, m_textureFormat, images[0]->getWidth(), images[0]->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, images[0]->getData());
  glBindTexture(GL_TEXTURE_2D, 0);
}
void
OGLTexture::generateMipmaps()
{
  glGenerateMipmap(m_shaderResource);
}
void
OGLTexture::clean(Color /*screenColor*/)
{
}
void
OGLTexture::release()
{
}
}