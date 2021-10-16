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
#     define EE_PLUGIN_EXPORT
#   else
#     if defined ( EE_PLUGIN_EXPORTS )
#       define EE_PLUGIN_EXPORT __declspec( dllexport )
#     else
#       define EE_PLUGIN_EXPORT __declspec( dllimport )
#     endif
#   endif
# else //Any other compiler
#   if defined( EE_STATIC_LIB )
#     define EE_PLUGIN_EXPORT
#   else
#     if defined( EE_PLUGIN_EXPORTS )
#       define EE_PLUGIN_EXPORT __attribute__ ((dllexport))
#     else
#       define EE_PLUGIN_EXPORT __attribute__ ((dllimport))
#     endif
#   endif
# endif
# define EE_PLUGIN_HIDDEN
#else
# define EE_PLUGIN_EXPORT __attribute__ ((visibility ("default")))
# define EE_PLUGIN_HIDDEN __attribute__ ((visibility ("hidden")))
#endif


#define EE_EXTERN extern "C"


namespace eeEngineSDK {
}