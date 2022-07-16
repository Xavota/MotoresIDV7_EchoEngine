#include "eeOGLSamplerState.h"
#pragma warning(push)
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#pragma warning(pop)

namespace eeEngineSDK {
OGLSamplerState::OGLSamplerState(eSAMPLER_FILTER::E filter,
                                 eTEXTURE_ADDRESS_MODE::E addressU,
                                 eTEXTURE_ADDRESS_MODE::E addressV,
                                 eTEXTURE_ADDRESS_MODE::E addressW)
{
  create(filter, addressU, addressV, addressW);
}
OGLSamplerState::~OGLSamplerState()
{
  release();
}
bool
OGLSamplerState::create(eSAMPLER_FILTER::E filter,
                        eTEXTURE_ADDRESS_MODE::E addressU,
                        eTEXTURE_ADDRESS_MODE::E addressV,
                        eTEXTURE_ADDRESS_MODE::E addressW)
{
  switch (filter)
  {
  case eSAMPLER_FILTER::kMinMagMipPoint:
    m_minFilter = GL_NEAREST_MIPMAP_NEAREST;
    m_magFilter = GL_NEAREST_MIPMAP_NEAREST;
    break;
  case eSAMPLER_FILTER::kMinMagMipLinear:
  default:
    m_minFilter = GL_LINEAR_MIPMAP_LINEAR;
    m_magFilter = GL_LINEAR_MIPMAP_LINEAR;
    break;
  case eSAMPLER_FILTER::kMinPointMagMipLinear:
    m_minFilter = GL_NEAREST_MIPMAP_LINEAR;
    m_magFilter = GL_LINEAR_MIPMAP_LINEAR;
    break;
  case eSAMPLER_FILTER::kMinLinearMagMipPoint:
    m_minFilter = GL_LINEAR_MIPMAP_NEAREST;
    m_magFilter = GL_NEAREST_MIPMAP_NEAREST;
    break;
  case eSAMPLER_FILTER::kMinMagPointMipLinear:
    m_minFilter = GL_NEAREST_MIPMAP_LINEAR;
    m_magFilter = GL_NEAREST_MIPMAP_LINEAR;
    break;
  case eSAMPLER_FILTER::kMinMagLinearMipPoint:
    m_minFilter = GL_LINEAR_MIPMAP_NEAREST;
    m_magFilter = GL_LINEAR_MIPMAP_NEAREST;
    break;
  case eSAMPLER_FILTER::kMinPointMagLinearMipPoint:
    m_minFilter = GL_NEAREST_MIPMAP_NEAREST;
    m_magFilter = GL_LINEAR_MIPMAP_NEAREST;
    break;
  case eSAMPLER_FILTER::kMinLinearMagPointMipLinear:
    m_minFilter = GL_LINEAR_MIPMAP_LINEAR;
    m_magFilter = GL_NEAREST_MIPMAP_LINEAR;
    break;
  case eSAMPLER_FILTER::kAnisotropic: // TODO: AGREGAR ANISOTROPIC
    m_minFilter = GL_LINEAR_MIPMAP_NEAREST;
    m_magFilter = GL_LINEAR_MIPMAP_NEAREST;
    break;
  }
  switch (addressU)
  {
  case eTEXTURE_ADDRESS_MODE::kWrap:
  default:
    m_addressU = GL_REPEAT;
    break;
  case eTEXTURE_ADDRESS_MODE::kMirror:
  case eTEXTURE_ADDRESS_MODE::kMirrorOnce:
    m_addressU = GL_MIRRORED_REPEAT;
    break;
  case eTEXTURE_ADDRESS_MODE::kClamp:
    m_addressU = GL_CLAMP_TO_EDGE;
    break;
  case eTEXTURE_ADDRESS_MODE::kBorder:
    m_addressU = GL_CLAMP_TO_BORDER;
    break;
  }
  switch (addressV)
  {
  case eTEXTURE_ADDRESS_MODE::kWrap:
  default:
    m_addressV = GL_REPEAT;
    break;
  case eTEXTURE_ADDRESS_MODE::kMirror:
  case eTEXTURE_ADDRESS_MODE::kMirrorOnce:
    m_addressV = GL_MIRRORED_REPEAT;
    break;
  case eTEXTURE_ADDRESS_MODE::kClamp:
    m_addressV = GL_CLAMP_TO_EDGE;
    break;
  case eTEXTURE_ADDRESS_MODE::kBorder:
    m_addressV = GL_CLAMP_TO_BORDER;
    break;
  }
  switch (addressW)
  {
  case eTEXTURE_ADDRESS_MODE::kWrap:
  default:
    m_addressW = GL_REPEAT;
    break;
  case eTEXTURE_ADDRESS_MODE::kMirror:
  case eTEXTURE_ADDRESS_MODE::kMirrorOnce:
    m_addressW = GL_MIRRORED_REPEAT;
    break;
  case eTEXTURE_ADDRESS_MODE::kClamp:
    m_addressW = GL_CLAMP_TO_EDGE;
    break;
  case eTEXTURE_ADDRESS_MODE::kBorder:
    m_addressW = GL_CLAMP_TO_BORDER;
    break;
  }
  return false;
}
void
OGLSamplerState::use()
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFilter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_addressU);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_addressV);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, m_addressW);
}
void
OGLSamplerState::release()
{
}
}