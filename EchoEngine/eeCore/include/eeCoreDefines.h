/************************************************************************/
/**
 * @file eeCoreDefines.h
 * @author Diego Castellanos
 * @date 15/10/21
 * @brief All the enumerators and structures needed for the graphic module.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"


namespace eeEngineSDK {
/**
 * @brief
 * The types of texture binds.
 */
namespace eTEXTURE_BIND_FLAGS
{
enum E
{
  kNone = 0u,
  kShaderResource = 1u,
  kRenderTarget = 2u,
  kDepthStencil = 4u
};
}

/**
 * @brief
 * Texture formats.
 */
namespace eTEXTURE_FORMAT
{
enum E
{
  kNone = 0u,
  kUnknown,
  kR32G32B32A32_Float ,
  kR32G32B32A32_Uint,
  kR32G32B32A32_Sint,
  kR32G32B32A32_Typeless,
  kR32G32B32_Float,
  kR32G32B32_Uint,
  kR32G32B32_Sint,
  kR32G32B32_Typeless,
  kR16G16B16A16_Float,
  kR16G16B16A16_Uint,
  kR16G16B16A16_Unorm,
  kR16G16B16A16_Sint,
  kR16G16B16A16_Snorm,
  kR16G16B16A16_Typeless,
  kR8G8B8A8_Uint,
  kR8G8B8A8_Unorm,
  kR8G8B8A8_Unorm_Srgb,
  kR8G8B8A8_Sint,
  kR8G8B8A8_Snorm,
  kR8G8B8A8_Typeless,
  kB8G8R8A8_Unorm,
  kB8G8R8A8_Unorm_Srgb,
  kB8G8R8A8_Typeless,
  kR16_Float,
  kR16_Uint,
  kR16_Unorm,
  kR16_Sint,
  kR16_Snorm,
  kR16_Typeless,
  kR8_Uint,
  kR8_Unorm,
  kR8_Sint,
  kR8_Snorm,
  kR8_Typeless,
  kD32_Float,
  kD24_Unorm_S8_Uint,
  kD16_Unorm
};
//DXGI_FORMAT_R16_TYPELESS = 53,
//DXGI_FORMAT_R16_FLOAT = 54,
//DXGI_FORMAT_R16_UNORM = 56,
//DXGI_FORMAT_R16_UINT = 57,
//DXGI_FORMAT_R16_SNORM = 58,
//DXGI_FORMAT_R16_SINT = 59,
//DXGI_FORMAT_R8_TYPELESS = 60,
//DXGI_FORMAT_R8_UNORM = 61,
//DXGI_FORMAT_R8_UINT = 62,
//DXGI_FORMAT_R8_SNORM = 63,
//DXGI_FORMAT_R8_SINT = 64,
}

/**
 * @brief
 * Filter for the sampler.
 */
namespace eFILTER {
enum E
{
  kMIN_MAG_MIP_POINT = 0,
  kMIN_MAG_POINT_MIP_LINEAR = 0x1,
  kMIN_POINT_MAG_LINEAR_MIP_POINT = 0x4,
  kMIN_POINT_MAG_MIP_LINEAR = 0x5,
  kMIN_LINEAR_MAG_MIP_POINT = 0x10,
  kMIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x11,
  kMIN_MAG_LINEAR_MIP_POINT = 0x14,
  kMIN_MAG_MIP_LINEAR = 0x15,
  kANISOTROPIC = 0x55,
  kCOMPARISON_MIN_MAG_MIP_POINT = 0x80,
  kCOMPARISON_MIN_MAG_POINT_MIP_LINEAR = 0x81,
  kCOMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x84,
  kCOMPARISON_MIN_POINT_MAG_MIP_LINEAR = 0x85,
  kCOMPARISON_MIN_LINEAR_MAG_MIP_POINT = 0x90,
  kCOMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x91,
  kCOMPARISON_MIN_MAG_LINEAR_MIP_POINT = 0x94,
  kCOMPARISON_MIN_MAG_MIP_LINEAR = 0x95,
  kCOMPARISON_ANISOTROPIC = 0xd5
};
}

/**
 * @brief
 * How to interpret the UVs outside the range 0.0 - 1.0
 */
namespace eTEXTURE_ADDRESS_MODE {
enum E
{
  kWrap = 1,
  kMirror,
  kClamp,
  kBorder,
  kMirrorOnce
};
}

/**
 * @brief
 * Comparison function.
 */
namespace eCOMPARISON_FUNC {
enum E
{
  kNever,
  kLess,
  kEqual,
  kLessEqual,
  kGreater,
  kNotEqual,
  kGreaterEqual,
  kAlways
};
}

/**
 * @brief
 * How to render the vertices.
 */
namespace ePRIMITIVE_TOPOLOGY {
enum E
{
  kUndefined = 0,
  kPointlist = 1,
  kLinelist = 2,
  kLinestrip = 3,
  kTrianglelist = 4,
  kTrianglestrip = 5,
  kLinelistADJ = 10,
  kLinestripADJ = 11,
  kTrienglelistADJ = 12,
  kTrianglestripADJ = 13
}; 
}

/**
 * @brief
 * Fill mode for the triangles.
 */
namespace eFILL_MODE {
enum E
{
  kWireframe = 2,
  kSolid = 3
};
}

/**
 * @brief
 * Cull mode, to render front, back or both.
 */
namespace eCULL_MODE {
enum E
{
  kNone = 1,
  kFront = 2,
  kBack = 3
};
}

/**
 * @brief
 * Depth write mask.
 */
namespace eDEPTH_WRITE_MASK {
enum E
{
  kZero,
  kAll
};
}

/**
 * @brief
 * Stencil operations.
 */
namespace eSTENCIL_OP { // TODO: Este enum no debería existir o al menos tener
enum E                  //       menos elementos más entendibles
{
  kKeep,
  kZero,
  kReplace,
  kIncrSat,
  kDecrSat,
  kInvert,
  kIncr,
  kDecr
};
}

/**
 * @brief
 * Blend info for blend state.
 */
namespace eBLEND { // TODO: Este enum no debería existir o al menos tener
enum E             //       menos elementos más entendibles
{
  kZero,
  kOne,
  kSrcColor,
  kInvSrcColor,
  kSrcAlpha,
  kInvSrcAlpha,
  kDestAlpha,
  kInvDestAlpha,
  kDestColor,
  kIinDestColor,
  kSrcAlphaSat,
  kBlendFactor,
  kInvLendFactor,
  kSrc1Color,
  kIinSrc1Color,
  kSrc1Alpha,
  kInvSrc1Alpha
};
}

/**
 * @brief
 * Blend operation for blend state.
 */
namespace eBLEND_OP {
enum E
{
  kAdd,
  kSubtract,
  kRevSubtract,
  kMin,
  kMax
};
}



////////////////////////////////////////////////////////////////////////////////
/*                                                                            */
/*                                 structures                                 */
/*                                                                            */
////////////////////////////////////////////////////////////////////////////////



/**
 * @brief
 * Descriptor for the viewport.
 */
struct ViewportDesc
{
  ViewportDesc() = default;
  ViewportDesc(float _width,
               float _height,
               float _topLeftX = 0.0f,
               float _topLeftY = 0.0f,
               float _minDepth = 0.0f,
               float _maxDepth = 1.0f) :
               width(_width),
               height(_height),
               topLeftX(_topLeftX),
               topLeftY(_topLeftY),
               minDepth(_minDepth),
               maxDepth(_maxDepth)
  {}

  float width;
  float height;
  float topLeftX;
  float topLeftY;
  float minDepth;
  float maxDepth;
};

// TODO: De aquí para abajo nada debería existir o al menos ser más entendibles.

/**
 * @brief
 * Descriptor for depth stencil operation.
 */
struct DepthStencilOPDesc
{
  eSTENCIL_OP::E         stencilFailOp;
  eSTENCIL_OP::E         stencilDepthFailOp;
  eSTENCIL_OP::E         stencilPassOp;
  eCOMPARISON_FUNC::E stencilFunc;
};

/**
 * @brief
 * Descriptor for a depth stencil.
 */
struct DepthStencilDesc
{
  bool                depthEnable;
  eDEPTH_WRITE_MASK::E   depthWriteMask;
  eCOMPARISON_FUNC::E depthFunc;
  bool                stencilEnable;
  uint8               stencilReadMask;
  uint8               stencilWriteMask;
  DepthStencilOPDesc  frontFace;
  DepthStencilOPDesc  backFace;
};

/**
 * @brief
 * Descriptor for a render target blend state.
 */
struct RenderTargetBlendDesc
{
  bool         blendEnable;
  eBLEND::E    srcBlend;
  eBLEND::E    destBlend;
  eBLEND_OP::E blendOp;
  eBLEND::E    srcBlendAlpha;
  eBLEND::E    destBlendAlpha;
  eBLEND_OP::E blendOpAlpha;
  uint8        renderTargetWriteMask;
};

/**
 * @brief
 * Descriptor for a blend state.
 */
struct BlendDesc
{
  bool                  alphaToCoverageEnable;
  bool                  independentBlendEnable;
  RenderTargetBlendDesc renderTarget[8];
};
}