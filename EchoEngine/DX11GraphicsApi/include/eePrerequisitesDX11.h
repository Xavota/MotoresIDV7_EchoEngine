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
}