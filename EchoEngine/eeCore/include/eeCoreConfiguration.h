/************************************************************************/
/**
 * @file eeCoreConfiguration.h
 * @author Diego Castellanos
 * @date 03/10/21
 * @brief
 * A file that contains configurations for parts of the graphics api.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#define DX11

#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK {
namespace eeConfigurations {
/**
 * The active platform target.
 */
#ifdef _M_IX86
const String platformTarget = "x86";
#elif defined(_M_X64)
const String platformTarget = "x64";
#endif

/**
 * The name of the active configuration and prefix.
 */
#ifdef _DEBUG
const String platformConfig = "Debug";
const String platformConfigPrefix = "d";
#else
const String platformConfig = "Release";
const String platformConfigPrefix;
#endif

/**
 * The current graphics api for use.
 */
#ifdef DX11
const String graphicsApi = "DX11GraphicsApi";
#elif defined(OGL)
const String graphicsApi = "OGLGraphicsApi";
#else
const String graphicsApi;
#endif

/**
 * The suffix for dynamic libraries.
 */
const String dynamicLibSuffix = ".dll";
/**
 * The suffix for static libraries.
 */
const String staticLibSuffix = ".lib";
}
}