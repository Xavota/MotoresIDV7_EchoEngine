/************************************************************************/
/**
 * @file eePrerequisitesOGL.h
 * @author Diego Castellanos
 * @date 11/05/22
 * @brief
 * Everything the Graphics Module for DirectX 11 needs.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include <eePrerequisitesCore.h>




/************************************************************************/
/**
 * Library export specifics
 */
 /************************************************************************/
#if EE_PLATFORM == EE_PLATFORM_WIN32
# if EE_COMPILER == EE_COMPILER_MSVC
#   if defined( EE_STATIC_lib )
#     define EE_PLUGINOGL_EXPORT
#   else
#     if defined ( EE_PLUGINOGL_EXPORTS )
#       define EE_PLUGINOGL_EXPORT __declspec( dllexport )
#     else
#       define EE_PLUGINOGL_EXPORT __declspec( dllimport )
#     endif
#   endif
# else //Any other compiler
#   if defined( EE_STATIC_LIB )
#     define EE_PLUGINOGL_EXPORT
#   else
#     if defined( EE_PLUGINOGL_EXPORTS )
#       define EE_PLUGINOGL_EXPORT __attribute__ ((dllexport))
#     else
#       define EE_PLUGINOGL_EXPORT __attribute__ ((dllimport))
#     endif
#   endif
# endif
# define EE_PLUGINOGL_HIDDEN
#else
# define EE_PLUGINOGL_EXPORT __attribute__ ((visibility ("default")))
# define EE_PLUGINOGL_HIDDEN __attribute__ ((visibility ("hidden")))
#endif


#define EE_EXTERN extern "C"


namespace eeEngineSDK {
class OGLGraphicsApi;
class OGLIndexBuffer;
class OGLPixelShader;
class OGLSamplerState;
//class OGLTexture;
class OGLVertexBuffer;
class OGLVertexShader;
class OGLWindow;
}