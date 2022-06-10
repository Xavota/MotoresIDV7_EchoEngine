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

#include "eePrerequisitesUtilities.h"

/*#define OGL//*/#define DX11
#define DEFERRED_RENDERING//*/#define OGL_TEST_RENDERING
#define GAINPUT

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
const String graphicsApi = "eeDX11GraphicsApi";
#elif defined(OGL)
const String graphicsApi = "eeOGLGraphicsApi";
#else
const String graphicsApi;
#endif

/**
 * The current render pipeline.
 */
#ifdef DEFERRED_RENDERING
const String rendererName = "eeDeferredRenderer";
#elif defined(OGL_TEST_RENDERING)
const String rendererName = "eeOGLTestRenderer";
#else
const String rendererName;
#endif

/**
 * The current input manager pipeline.
 */
#ifdef GAINPUT
const String inputManagerName = "eeGainput";
#else
const String inputManagerName;
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