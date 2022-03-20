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
  kMinMagMipPoint,
  kMinMagPointMipLinear,
  kMinPointMagLinearMipPoint,
  kMinPointMagMipLinear,
  kMinLinearMagMipPoint,
  kMinLinearMagPointMipLinear,
  kMIN_MAG_LINEAR_MIP_POINT,
  kMIN_MAG_MIP_LINEAR,
  kANISOTROPIC,
  kCOMPARISON_MIN_MAG_MIP_POINT,
  kCOMPARISON_MIN_MAG_POINT_MIP_LINEAR,
  kCOMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,
  kCOMPARISON_MIN_POINT_MAG_MIP_LINEAR,
  kCOMPARISON_MIN_LINEAR_MAG_MIP_POINT,
  kCOMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
  kCOMPARISON_MIN_MAG_LINEAR_MIP_POINT,
  kCOMPARISON_MIN_MAG_MIP_LINEAR,
  kCOMPARISON_ANISOTROPIC,
  kMINIMUM_MIN_MAG_MIP_POINT,
  kMINIMUM_MIN_MAG_POINT_MIP_LINEAR,
  kMINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
  kMINIMUM_MIN_POINT_MAG_MIP_LINEAR,
  kMINIMUM_MIN_LINEAR_MAG_MIP_POINT,
  kMINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
  kMINIMUM_MIN_MAG_LINEAR_MIP_POINT,
  kMINIMUM_MIN_MAG_MIP_LINEAR,
  kMINIMUM_ANISOTROPIC,
  kMAXIMUM_MIN_MAG_MIP_POINT,
  kMAXIMUM_MIN_MAG_POINT_MIP_LINEAR,
  kMAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
  kMAXIMUM_MIN_POINT_MAG_MIP_LINEAR,
  kMAXIMUM_MIN_LINEAR_MAG_MIP_POINT,
  kMAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
  kMAXIMUM_MIN_MAG_LINEAR_MIP_POINT,
  kMAXIMUM_MIN_MAG_MIP_LINEAR,
  kMAXIMUM_ANISOTROPIC
};
}

/**
 * @brief
 * How to interpret the UVs outside the range 0.0 - 1.0
 */
namespace eTEXTURE_ADDRESS_MODE {
enum E
{
  kWrap,
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
 * Usage for the buffers.
 */
enum class eUSAGE
{
  kDefault = 0,
  kImmutable = 1,
  kDynamic = 2,
  kStaging = 3
};

/**
 * @brief
 * Fill mode for the triangles.
 */
enum class eFILL_MODE
{
  kWireframe = 2,
  kSolid = 3
};

/**
 * @brief
 * Cull mode, to render front, back or both.
 */
enum class eCULL_MODE
{
  kNone = 1,
  kFront = 2,
  kBack = 3
};

/**
 * @brief
 * Depth write mask.
 */
enum class eDEPTH_WRITE_MASK
{
  kZero,
  kAll
};

/**
 * @brief
 * Stencil operations.
 */
enum eSTENCIL_OP
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

/**
 * @brief
 * Blend info for blend state.
 */
enum class eBLEND
{
  ZERO,
  ONE,
  SRC_COLOR,
  INV_SRC_COLOR,
  SRC_ALPHA,
  INV_SRC_ALPHA,
  DEST_ALPHA,
  INV_DEST_ALPHA,
  DEST_COLOR,
  INV_DEST_COLOR,
  SRC_ALPHA_SAT,
  BLEND_FACTOR,
  INV_BLEND_FACTOR,
  SRC1_COLOR,
  INV_SRC1_COLOR,
  SRC1_ALPHA,
  INV_SRC1_ALPHA
};

/**
 * @brief
 * Blend operation for blend state.
 */
enum class eBLEND_OP
{
  Add,
  Subtract,
  RevSubtract,
  Min,
  Max
};



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
  float topLeftX;
  float topLeftY;
  float width;
  float height;
  float minDepth;
  float maxDepth;
};

/**
 * @brief
 * Descriptor for the sampler state.
 */
struct SamplerStateDesc
{
  eFILTER::E               filter;
  eTEXTURE_ADDRESS_MODE::E addressU;
  eTEXTURE_ADDRESS_MODE::E addressV;
  eTEXTURE_ADDRESS_MODE::E addressW;
  float                    mipLODBias;
  uint32                   maxAnisotropy;
  eCOMPARISON_FUNC::E      comparisonFunc;
  float                    borderColor[4];
  float                    minLOD;
  float                    maxLOD;
};

/**
 * @brief
 * Descriptor for the sample.
 */
struct SampleDesc
{
  uint32 count;
  uint32 quality;
};

/**
 * @brief
 * Buffer Shader Resource View.
 */
struct BufferSRV
{
  union
  {
    uint32 firstElement;
    uint32 elementOffset;
  };
  union
  {
    uint32 numElements;
    uint32 elementWidth;
  };
};

/**
 * @brief
 * Texture 1D Shader Resource View.
 */
struct Tex1DSRV
{
  uint32 mostDetailedMip;
  uint32 mipLevels;
};

/**
 * @brief
 * Texture 1D Array Shader Resource View.
 */
struct Tex1dArraySRV
{
  uint32 mostDetailedMip;
  uint32 mipLevels;
  uint32 firstArraySlice;
  uint32 arraySize;
};

/**
 * @brief
 * Texture 2D Shader Resource View.
 */
struct Tex2DSRV
{
  uint32 mostDetailedMip;
  uint32 mipLevels;
};

/**
 * @brief
 * Texture 2D Array Shader Resource View.
 */
struct Tex2dArraySRV
{
  uint32 mostDetailedMip;
  uint32 mipLevels;
  uint32 firstArraySlice;
  uint32 arraySize;
};

/**
 * @brief
 * Texture 2D Ms Shader Resource View.
 */
struct Tex2DMsSRV
{
  uint32 unusedField_NothingToDefine;
};

/**
 * @brief
 * Texture 2D Ms Array Shader Resource View.
 */
struct Tex2DMsArraySRV
{
  uint32 firstArraySlice;
  uint32 arraySize;
};

/**
 * @brief
 * Texture 3D Shader Resource View.
 */
struct Tex3DSRV
{
  uint32 mostDetailedMip;
  uint32 mipLevels;
};

/**
 * @brief
 * Texture cube Shader Resource View.
 */
struct TexcubeSRV
{
  uint32 mostDetailedMip;
  uint32 mipLevels;
};

/**
 * @brief
 * Texture cube array Shader Resource View.
 */
struct TexcubeArraySRV
{
  uint32 mostDetailedMip;
  uint32 mipLevels;
  uint32 first2DArrayFace;
  uint32 numCubes;
};

/**
 * @brief
 * Buffer Ex Shader Resource View.
 */
struct BufferExSRV
{
  uint32 firstElement;
  uint32 numElements;
  uint32 flags;
};

/**
 * @brief
 * Descriptor for a rasterizer state.
 */
struct RasteraizerDesc
{
  eFILL_MODE fillMode;
  eCULL_MODE cullMode;
  bool       frontCounterClockwise;
  int32      depthBias;
  float      depthBiasClamp;
  float      slopeScaledDepthBias;
  bool       depthClipEnable;
  bool       scissorEnable;
  bool       multisampleEnable;
  bool       antialiasedLineEnable;
};

/**
 * @brief
 * Descriptor for depth stencil operation.
 */
struct DepthStencilOPDesc
{
  eSTENCIL_OP         stencilFailOp;
  eSTENCIL_OP         stencilDepthFailOp;
  eSTENCIL_OP         stencilPassOp;
  eCOMPARISON_FUNC::E stencilFunc;
};

/**
 * @brief
 * Descriptor for a depth stencil.
 */
struct DepthStencilDesc
{
  bool                depthEnable;
  eDEPTH_WRITE_MASK   depthWriteMask;
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
  bool      blendEnable;
  eBLEND    srcBlend;
  eBLEND    destBlend;
  eBLEND_OP blendOp;
  eBLEND    srcBlendAlpha;
  eBLEND    destBlendAlpha;
  eBLEND_OP blendOpAlpha;
  uint8     renderTargetWriteMask;
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