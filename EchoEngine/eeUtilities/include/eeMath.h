/************************************************************************/
/**
 * @file eeMath.h
 * @author Diego Castellanos
 * @date 05/09/21
 * @brief This is for replacing the Math library for anything you want.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once

#include "eePrerequisitesUtilities.h"
#include "eePlatformMath.h"

namespace eeEngineSDK
{
#if EE_PLATFORM == EE_PLATFORM_WIN32 || \
	EE_PLATFORM == EE_PLATFORM_LINUX || \
	EE_PLATFORM == EE_PLATFORM_OSX
	using Math = PlatformMath;
#else
	using Math = PlatformMath;
#endif
}