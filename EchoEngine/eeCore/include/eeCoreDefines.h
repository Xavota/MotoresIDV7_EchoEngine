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
 * Filter for the sampler.
 */
enum class eFILTER
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

/**
 * @brief
 * How to interpret the UVs outside the range 0.0 - 1.0
 */
enum class eTEXTURE_ADDRESS_MODE
{
  WRAP,
  MIRROR,
  CLAMP,
  BORDER,
  MIRROR_ONCE
};

/**
 * @brief
 * Comparison function.
 */
enum class eCOMPARISON_FUNC
{
  NEVER,
  LESS,
  EQUAL,
  LESS_EQUAL,
  GREATER,
  NOT_EQUAL,
  GREATER_EQUAL,
  ALWAYS
};

/**
 * @brief
 * How to render the vertices.
 */
enum class ePRIMITIVE_TOPOLOGY
{
  UNDEFINED = 0,
  POINTLIST = 1,
  LINELIST = 2,
  LINESTRIP = 3,
  TRIANGLELIST = 4,
  TRIANGLESTRIP = 5,
  LINELIST_ADJ = 10,
  LINESTRIP_ADJ = 11,
  TRIANGLELIST_ADJ = 12,
  TRIANGLESTRIP_ADJ = 13
}; 

/**
 * @brief
 * Format for read the texture info.
 */
enum class eFORMAT
{
  UNKNOWN = 0,
  R32G32B32A32_TYPELESS = 1,
  R32G32B32A32_FLOAT = 2,
  R32G32B32A32_UINT = 3,
  R32G32B32A32_SINT = 4,
  R32G32B32_TYPELESS = 5,
  R32G32B32_FLOAT = 6,
  R32G32B32_UINT = 7,
  R32G32B32_SINT = 8,
  R16G16B16A16_TYPELESS = 9,
  R16G16B16A16_FLOAT = 10,
  R16G16B16A16_UNORM = 11,
  R16G16B16A16_UINT = 12,
  R16G16B16A16_SNORM = 13,
  R16G16B16A16_SINT = 14,
  R32G32_TYPELESS = 15,
  R32G32_FLOAT = 16,
  R32G32_UINT = 17,
  R32G32_SINT = 18,
  R32G8X24_TYPELESS = 19,
  D32_FLOAT_S8X24_UINT = 20,
  R32_FLOAT_X8X24_TYPELESS = 21,
  X32_TYPELESS_G8X24_UINT = 22,
  R10G10B10A2_TYPELESS = 23,
  R10G10B10A2_UNORM = 24,
  R10G10B10A2_UINT = 25,
  R11G11B10_FLOAT = 26,
  R8G8B8A8_TYPELESS = 27,
  R8G8B8A8_UNORM = 28,
  R8G8B8A8_UNORM_SRGB = 29,
  R8G8B8A8_UINT = 30,
  R8G8B8A8_SNORM = 31,
  R8G8B8A8_SINT = 32,
  R16G16_TYPELESS = 33,
  R16G16_FLOAT = 34,
  R16G16_UNORM = 35,
  R16G16_UINT = 36,
  R16G16_SNORM = 37,
  R16G16_SINT = 38,
  R32_TYPELESS = 39,
  D32_FLOAT = 40,
  R32_FLOAT = 41,
  R32_UINT = 42,
  R32_SINT = 43,
  R24G8_TYPELESS = 44,
  D24_UNORM_S8_UINT = 45,
  R24_UNORM_X8_TYPELESS = 46,
  X24_TYPELESS_G8_UINT = 47,
  R8G8_TYPELESS = 48,
  R8G8_UNORM = 49,
  R8G8_UINT = 50,
  R8G8_SNORM = 51,
  R8G8_SINT = 52,
  R16_TYPELESS = 53,
  R16_FLOAT = 54,
  D16_UNORM = 55,
  R16_UNORM = 56,
  R16_UINT = 57,
  R16_SNORM = 58,
  R16_SINT = 59,
  R8_TYPELESS = 60,
  R8_UNORM = 61,
  R8_UINT = 62,
  R8_SNORM = 63,
  R8_SINT = 64,
  A8_UNORM = 65,
  R1_UNORM = 66,
  R9G9B9E5_SHAREDEXP = 67,
  R8G8_B8G8_UNORM = 68,
  G8R8_G8B8_UNORM = 69,
  BC1_TYPELESS = 70,
  BC1_UNORM = 71,
  BC1_UNORM_SRGB = 72,
  BC2_TYPELESS = 73,
  BC2_UNORM = 74,
  BC2_UNORM_SRGB = 75,
  BC3_TYPELESS = 76,
  BC3_UNORM = 77,
  BC3_UNORM_SRGB = 78,
  BC4_TYPELESS = 79,
  BC4_UNORM = 80,
  BC4_SNORM = 81,
  BC5_TYPELESS = 82,
  BC5_UNORM = 83,
  BC5_SNORM = 84,
  B5G6R5_UNORM = 85,
  B5G5R5A1_UNORM = 86,
  B8G8R8A8_UNORM = 87,
  B8G8R8X8_UNORM = 88,
  R10G10B10_XR_BIAS_A2_UNORM = 89,
  B8G8R8A8_TYPELESS = 90,
  B8G8R8A8_UNORM_SRGB = 91,
  B8G8R8X8_TYPELESS = 92,
  B8G8R8X8_UNORM_SRGB = 93,
  BC6H_TYPELESS = 94,
  BC6H_UF16 = 95,
  BC6H_SF16 = 96,
  BC7_TYPELESS = 97,
  BC7_UNORM = 98,
  BC7_UNORM_SRGB = 99,
  //FORCE_UINT = 0xffffffff
};

/**
 * @brief
 * Usage for the buffers.
 */
enum class eUSAGE
{
  DEFAULT = 0,
  IMMUTABLE = 1,
  DYNAMIC = 2,
  STAGING = 3
};

/**
 * @brief
 * Dimension of the textures.
 */
enum class eSRV_DIMENSION
{
  UNKNOWN = 0,
  BUFFER = 1,
  TEXTURE1D = 2,
  TEXTURE1DARRAY = 3,
  TEXTURE2D = 4,
  TEXTURE2DARRAY = 5,
  TEXTURE2DMS = 6,
  TEXTURE2DMSARRAY = 7,
  TEXTURE3D = 8,
  TEXTURECUBE = 9,
  TEXTURECUBEARRAY = 10,
  BUFFEREX = 11
};

/**
 * @brief
 * Fill mode for the triangles.
 */
enum class eFILL_MODE
{
  WIREFRAME = 2,
  SOLID = 3
};

/**
 * @brief
 * Cull mode, to render front, back or both.
 */
enum class eCULL_MODE
{
  NONE = 1,
  FRONT = 2,
  BACK = 3
};

/**
 * @brief
 * Depth write mask.
 */
enum class eDEPTH_WRITE_MASK
{
  ZERO,
  ALL
};

/**
 * @brief
 * Stencil operations.
 */
enum eSTENCIL_OP
{
  KEEP,
  ZERO,
  REPLACE,
  INCR_SAT,
  DECR_SAT,
  INVERT,
  INCR,
  DECR
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
 ADD,
 SUBTRACT,
 REV_SUBTRACT,
 MIN,
 MAX
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
  eFILTER               filter;
  eTEXTURE_ADDRESS_MODE addressU;
  eTEXTURE_ADDRESS_MODE addressV;
  eTEXTURE_ADDRESS_MODE addressW;
  float                 mipLODBias;
  uint32                maxAnisotropy;
  eCOMPARISON_FUNC      comparisonFunc;
  float                 borderColor[4];
  float                 minLOD;
  float                 maxLOD;
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
 * Descriptor for a texture 2D buffer.
 */
struct Texture2DDesc
{
  uint32     width;
  uint32     height;
  uint32     mipLevels;
  uint32     arraySize;
  eFORMAT    format;
  SampleDesc sampleDesc;
  eUSAGE     usage;
  uint32     bindFlags;
  uint32     CPUAccessFlags;
  uint32     miscFlags;
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
 * Descriptor for shader resource view.
 */
struct ShaderResourceViewDesc
{
  eFORMAT        format;
  eSRV_DIMENSION viewDimension;
  union
  {
    BufferSRV       buffer;
    Tex1DSRV        texture1D;
    Tex1dArraySRV   texture1DArray;
    Tex2DSRV        texture2D;
    Tex2dArraySRV   texture2DArray;
    Tex2DMsSRV      texture2DMS;
    Tex2DMsArraySRV texture2DMSArray;
    Tex3DSRV        texture3D;
    TexcubeSRV      textureCube;
    TexcubeArraySRV textureCubeArray;
    BufferExSRV     bufferEx;
  };
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
  eSTENCIL_OP      stencilFailOp;
  eSTENCIL_OP      stencilDepthFailOp;
  eSTENCIL_OP      stencilPassOp;
  eCOMPARISON_FUNC stencilFunc;
};

/**
 * @brief
 * Descriptor for a depth stencil.
 */
struct DepthStencilDesc
{
  bool               depthEnable;
  eDEPTH_WRITE_MASK  depthWriteMask;
  eCOMPARISON_FUNC   depthFunc;
  bool               stencilEnable;
  uint8              stencilReadMask;
  uint8              stencilWriteMask;
  DepthStencilOPDesc frontFace;
  DepthStencilOPDesc backFace;
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