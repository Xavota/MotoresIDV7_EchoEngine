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
* The width of the screen.
*/
int32 screenWidth = 1280;
/**
* The height of the screen.
*/
int32 screenHeight = 720;

/**
* The active platform target.
*/
#ifdef _M_IX86
String platformTarget = "x86";
#elif defined(_M_X64)
String platformTarget = "x64";
#endif

/**
* The name of the active configuration and prefix.
*/
#ifdef _DEBUG
String platformConfig = "Debug";
String platformConfigPrefix = "d";
#else
String platformConfig = "Release";
String platformConfigPrefix = "";
#endif

/**
* The current graphics api for use.
*/
#ifdef DX11
String graphicsApi = "DX11GraphicsApi";
#endif

/**
* The suffix for dynamic libraries.
*/
String dynamicLibSuffix = ".dll";
/**
* The suffix for static libraries.
*/
String staticLibSuffix = ".lib";
}
}