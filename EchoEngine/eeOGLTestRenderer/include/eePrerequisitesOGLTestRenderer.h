/************************************************************************/
/**
 * @file eePrerequisitesOGLTestRenderer.h
 * @author Diego Castellanos
 * @date 03/03/22
 * @brief
 * Everything the OGL Test Renderer plugin needs.
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
#     define EE_PLUGINOGLTREND_EXPORT
#   else
#     if defined ( EE_OGL_TEST_RENDERER_EXPORTS )
#       define EE_OGL_TEST_RENDERER_EXPORT __declspec( dllexport )
#     else
#       define EE_OGL_TEST_RENDERER_EXPORT __declspec( dllimport )
#     endif
#   endif
# else //Any other compiler
#   if defined( EE_STATIC_LIB )
#     define EE_PLUGINOGLTREND_EXPORT
#   else
#     if defined( EE_OGL_TEST_RENDERER_EXPORTS )
#       define EE_OGL_TEST_RENDERER_EXPORT __attribute__ ((dllexport))
#     else
#       define EE_OGL_TEST_RENDERER_EXPORT __attribute__ ((dllimport))
#     endif
#   endif
# endif
# define EE_PLUGINOGLTREND_HIDDEN
#else
# define EE_PLUGINOGLTREND_EXPORT __attribute__ ((visibility ("default")))
# define EE_PLUGINOGLTREND_HIDDEN __attribute__ ((visibility ("hidden")))
#endif


#define EE_EXTERN extern "C"


namespace eeEngineSDK {
}