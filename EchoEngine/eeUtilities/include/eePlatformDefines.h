/************************************************************************/
/**
 * @file eePlatformDefines.h
 * @author Diego Castellanos
 * @date 02/09/21
 * @brief All the defines needed for the Utilities module.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once


/************************************************************************/
/**
 * Initial platform/compiler-related stuff to set.
*/
/************************************************************************/
#define EE_PLATFORM_WIN32   1                  //Windows Platform
#define EE_PLATFORM_LINUX   2                  //Linux Platform
#define EE_PLATFORM_OSX     3


#define EE_COMPILER_MSVC    1                  //Visual Studio Compiler
#define EE_COMPILER_GNUC    2                  //GCC Compiler
#define EE_COMPILER_INTEL   3                  //Intel Compiler
#define EE_COMPILER_CLANG   4                  //Clang Compiler

#define EE_ARCHITECTURE_X86_32 1               //Intel x86 32 bits
#define EE_ARCHITECTURE_X86_64 2               //Intel x86 64 bits

#define EE_ENDIAN_LITTLE  1
#define EE_ENDIAN_BIG     2

//Define the actual endian type (little endian for Windows, Linux, Apple and PS4)
#define EE_ENDIAN EE_ENDIAN_LITTLE

#define EE_VERSION_MAJOR    0                 //Engine version major
#define EE_VERSION_MINIOR   1
#define EE_VERSION_PATCH    0
#define EE_VERSION_BUILD    1

//Define if on crate a we want to report warnings on unknown symbols
#define EE_DEBUG_DETAILED_SYMBOLS   1

/************************************************************************/
/**
 * Compiler type and version
 */
 /************************************************************************/

#if defined(__clang__)
#   define EE_COMPILER EE_COMPILER_CLANG
#   define EE_COMP_VER __cland_version__
#   define EE_THREADLOCAL __thread
#   define EE_STDCALL __attribute__((stdcall))
#   define EE_CDECL __attribute__((cdecl))
#   define EE_FALLTHROUHG [[clang::fallthrough]];
#elif defined (__GNUC__) //Check after Cland, as Clang defines this too
#   define EE_COMPILER EE_COMPILER_GNUC
#   define EE_COMP_VER (((__GNUC__)*100)+(__GNUC_MINOR__*10)+__GNUC_PATCHLEVEL__)
#   define EE_THREADLOCAL __thread
#   define EE_STDCALL __attribute__((stdcall))
#   define EE_CDECL __attribute__((cdecl))
#   define EE_FALLTHROUHG __attribute__((fallthrough));
#elif defined (__INTEL_COMPILER)
#   define EE_COMPILER EE_COMPILER_INTEL
#   define EE_COMP_VER __INTEL_COMPILER
#   define EE_STDCALL __stdcall
#   define EE_CDECL __cdecl
#   define EE_FALLTHROUHG 

/**
 * EE_THREADLOCAL define is down below because Intel compiler defines it
 * differently based on platform
 */

 //Check after Clang end Intel, we could be building with either with Vs
#elif defined (_MSC_VER)
#   define EE_COMPILER EE_COMPILER_MSVC
#   define EE_COMP_VER _MSC_VER
#   define EE_THREADLOCAL __declspec
#   define EE_STDCALL __stdcall
#   define EE_CDECL __cdecl
#   define EE_FALLTHROUHG
#   undef __PRETTY_FUNCTION__
#   define __PRETTY_FUNCTION__ __FUNCSIG__
#else
//No know compiler found, send the error to the output (if any)
#   pragma error "No known compuler. "
#endif

/************************************************************************/
/**
 * See if we can use __forceinline or if we need to use __inline instead
 */
 /************************************************************************/
#if EE_COMPILER == EE_COMPILER_MSVC
# if EE_COMP_VER >= 1200
#   define FORCEINLINE __forceinline
#   ifndef RESTRICT 
#     define RESTRICT __restrict
#   endif
# endif
#elif defined (__MINGW32__)
# if !defined (FORCEINLINE)
#   define FORCEINLINE __inline
#   ifndef RESTRICT
#     define RESTRICT
#   endif
# endif
#else
# define FORCEINLINE __inline
# ifndef RESTRICT
#   define RESTRICT __restrict
# endif
#endif

/************************************************************************/
/**
 * Finds the current platform
 */
 /************************************************************************/
#if defined (__WIN32__) || defined (_WIN32)
# define EE_PLATFORM EE_PLATFORM_WIN32
#elif defined (__APPLE_CC__ )
# define EE_PLATFORM EE_PLATFORM_OSX
#elif defined (__ORBIS__)
# define EE_PLATFORM EE_PLATFORM_LINUX
#endif

/************************************************************************/
/**
 * Find the architecture type
 */
 /************************************************************************/
#if defined (__x86_x64__) || defined(_M_X64)    //If this is a x64 compile
# define EE_ARCH_TYPE EE_ARCHITECTURE_X86_64
#else
#  define EE_ARCH_TYPE EE_ARCHITECTURE_X86_32
#endif

/************************************************************************/
/**
 * Memory Alignment macros
 */
 /************************************************************************/
#if EE_COMPILER == EE_COMPILER_MSVC
# define MS_ALIGN(n) __declspec(align(n))
# ifndef GCC_PACK
#   define GCC_PACK(n)
# endif
# ifndef GCC_ALIGN
#   define GCC_ALIGN(n)
# endif
#elif (EE_COMPILER == EE_COMPILER_GNUC)
# define MS_ALIGN(n)
# define GCC_PACK(n)
# define GCC_ALIGN(n) __attribute__( (__aligned__(n)) )
#else
# define MS_ALIGN(n)
# define GCC_PACK(n) __attribute__((packed, aligned(n)))
# define GCC_ALIGN(n) __attribute__( (__aligned__(n)) )
#endif

/************************************************************************/
/**
 * For throw override (deprecated on c++11 but VS does not have handle )
 */
 /************************************************************************/
#if EE_COMPILER == EE_COMPILER_MSVC
# define _NOEXCEPT noexcept
#elif EE_COMPILER == EE_COMPILER_INTEL
# define _NOEXCEPT noexcept
#elif EE_COMPILER == EE_COMPILER_GNUC
# define _NOEXCEPT noexcept
#else
# define _NOEXCEPT
#endif

/************************************************************************/
/**
 * Library export specifics
 */
 /************************************************************************/
#if EE_PLATFORM == EE_PLATFORM_WIN32
# if EE_COMPILER == EE_COMPILER_MSVC
#   if defined( EE_STATIC_lib )
#     define EE_UTILITY_EXPORT
#   else
#     if defined ( EE_UTILITY_EXPORTS )
#       define EE_UTILITY_EXPORT __declspec( dllexport )
#     else
#       define EE_UTILITY_EXPORT __declspec( dllimport )
#     endif
#   endif
# else //Any other compiler
#   if defined( EE_STATIC_LIB )
#     define EE_UTILITY_EXPORT
#   else
#     if defined( EE_UTILITY_EXPORTS )
#       define EE_UTILITY_EXPORT __attribute__ ((dllexport))
#     else
#       define EE_UTILITY_EXPORT __attribute__ ((dllimport))
#     endif
#   endif
# endif
# define EE_UTILITY_HIDDEN
#else
# define EE_UTILITY_EXPORT __attribute__ ((visibility ("default")))
# define EE_UTILITY_HIDDEN __attribute__ ((visibility ("hidden")))
#endif

 //DLL export plug ins
#if EE_PLATFORM == EE_PLATFORM_WIN32
# if EE_COMPILER == EE_COMPILER_MSVC
#   define EE_PLUGIN_EXPORT __declspec(dllexport)
# else
#   define EE_PLUGIN_EXPORT __attribute__ ((dllexport))
# endif
#else
#  define EE_PLUGIN_EXPORT __attribute__((visibility("default")))
#endif

/************************************************************************/
/**
 * Window specific Settings
 */
 /************************************************************************/
 //Win32
#if EE_PLATFORM == EE_PLATFORM_WIN32
# if defined(_DEBUG) || defined(DEBUG)
#   define EE_DEBUG_MODE 1
# else
#   define EE_DEBUG_MODE 0
# endif
# if EE_COMPILER == EE_COMPILER_INTEL
#   define EE_THREADLOCAL __declspec(thread)
# endif
#endif //EE_PLATFORM

/************************************************************************/
/**
 * LINUX-Apple specific Settings
 */
 /************************************************************************/

 //
#if EE_PLATFORM == EE_PLATFORM_LINUX || EE_PLATFORM == EE_PLATFORM_OSX

//if we're on debug mode
# if defined(_DEBUG) || defined(DEBUG)
#   define EE_DEBUG_MODE 1
# else
#   define EE_DEBUG_MODE 0
# endif
# if EE_COMPILER == EE_COMPILER_INTEL
#   define EE_THREADLOCAL thread
# endif
#endif //EE_PLATFORM

/************************************************************************/
/**
 * DEfinition of DEbug macros
 */
 /************************************************************************/
#if EE_DEBUG_MODE
# define EE_DEBUG_ONLY(x) x
# define EE_ASSERT(x) assert(x)
#else
# define EE_DEBUG_ONLY(x)
# define EE_ASSERT(x)
#endif

/************************************************************************/
/**
 * Disable some compiler warnings
 */
 /************************************************************************/

 //If we are compiling with VS
#if EE_COMPILER == EE_COMPILER_MSVC

# define _CRT_SECURE_NO_WARNINGS

# pragma warning(disable : 4201)

# pragma warning(disable : 4996)

# pragma warning(disable : 4251)

# pragma warning(disable : 4503)

#endif
