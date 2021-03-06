/************************************************************************/
/**
 * @file eeDX11PrerequisitesDX11.h
 * @author Diego Castellanos
 * @date 14/10/21
 * @brief
 * Everything the Graphics Module for DirectX 11 needs.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include <eePrerequisitesCore.h>
#pragma warning(push, 0)   
#include <d3d11.h>
#pragma warning(pop)  

#define DX11SAFE_RELEASE(x) if (x) { x->Release(); x = nullptr; }




/************************************************************************/
/**
 * Library export specifics
 */
 /************************************************************************/
#if EE_PLATFORM == EE_PLATFORM_WIN32
# if EE_COMPILER == EE_COMPILER_MSVC
#   if defined( EE_STATIC_lib )
#     define EE_PLUGINDX11_EXPORT
#   else
#     if defined ( EE_PLUGINDX11_EXPORTS )
#       define EE_PLUGINDX11_EXPORT __declspec( dllexport )
#     else
#       define EE_PLUGINDX11_EXPORT __declspec( dllimport )
#     endif
#   endif
# else //Any other compiler
#   if defined( EE_STATIC_LIB )
#     define EE_PLUGINDX11_EXPORT
#   else
#     if defined( EE_PLUGINDX11_EXPORTS )
#       define EE_PLUGINDX11_EXPORT __attribute__ ((dllexport))
#     else
#       define EE_PLUGINDX11_EXPORT __attribute__ ((dllimport))
#     endif
#   endif
# endif
# define EE_PLUGINDX11_HIDDEN
#else
# define EE_PLUGINDX11_EXPORT __attribute__ ((visibility ("default")))
# define EE_PLUGINDX11_HIDDEN __attribute__ ((visibility ("hidden")))
#endif


#define EE_EXTERN extern "C"


namespace eeEngineSDK {
class DX11BlendState;
class DX11ConstantBuffer;
class DX11DepthStencilState;
class DX11GraphicsApi;
class DX11IndexBuffer;
class DX11PixelShader;
class DX11RasterizerState;
class DX11SamplerState;
class DX11Texture;
class DX11VertexBuffer;
class DX11VertexShader;
class DX11Window;
}