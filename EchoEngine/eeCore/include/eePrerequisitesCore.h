#pragma once

#include <eePrerequisitesUtilities.h>



/************************************************************************/
/**
 * Library export specifics
 */
 /************************************************************************/
#if EE_PLATFORM == EE_PLATFORM_WIN32
# if EE_COMPILER == EE_COMPILER_MSVC
#   if defined( EE_STATIC_lib )
#     define EE_CORE_EXPORT
#   else
#     if defined ( EE_CORE_EXPORTS )
#       define EE_CORE_EXPORT __declspec( dllexport )
#     else
#       define EE_CORE_EXPORT __declspec( dllimport )
#     endif
#   endif
# else //Any other compiler
#   if defined( EE_STATIC_LIB )
#     define EE_CORE_EXPORT
#   else
#     if defined( EE_CORE_EXPORTS )
#       define EE_CORE_EXPORT __attribute__ ((dllexport))
#     else
#       define EE_CORE_EXPORT __attribute__ ((dllimport))
#     endif
#   endif
# endif
# define EE_CORE_HIDDEN
#else
# define EE_CORE_EXPORT __attribute__ ((visibility ("default")))
# define EE_CORE_HIDDEN __attribute__ ((visibility ("hidden")))
#endif