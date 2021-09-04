#pragma once

#include "eePlatformDefines.h"
#include "eePlatformTypes.h"
#include "eeSTDHeaders.h"

namespace eeEngineSDK
{
template<typename T>
class Vector2;
template<typename T>
class Vector3;
template<typename T>
class Vector4;

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int32>;
using Vector2u = Vector2<uint32>;
using Vector3f = Vector3<float>;
using Vector3i = Vector3<int32>;
using Vector3u = Vector3<uint32>;
using Vector4f = Vector4<float>;
using Vector4i = Vector4<int32>;
using Vector4u = Vector4<uint32>;
}