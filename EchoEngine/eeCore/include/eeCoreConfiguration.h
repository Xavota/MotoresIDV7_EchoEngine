#pragma once
#define DX11

#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK {
int32 screenWidth = 1280;
int32 screenHeight = 720;

#ifdef _M_IX86
String platformTarget = "x86";
#elif defined(_M_X64)
String platformTarget = "x64";
#endif

#ifdef _DEBUG
String platformConfig = "Debug";
String platformConfigPrefix = "d";
#else
String platformConfig = "Release";
String platformConfigPrefix = "";
#endif

#ifdef DX11
String graphicsApi = "DX11GraphicsApi";
#endif

String dynamicLibSufix = ".dll";
String staticLibSufix = ".lib";
}