/************************************************************************/
/**
 * @file eeDLLDynamics.h
 * @author Diego Castellanos
 * @date 02/09/21
 * @brief All the includes and forward declarations needed for the Utilities
 * module.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once

#include "eePlatformDefines.h"
#include "eePlatformTypes.h"
#include "eeSTDHeaders.h"

namespace eeEngineSDK {
class Vector2f;
class Vector2i;
class Point2D;

class Vector3f;
class Vector3i;
class Point3D;

class Vector4f;
class Vector4i;
class Point4D;

class Color;
class ColorI;

class Quaternion;

class Matrix2f;
class Matrix2i;
class Matrix2u;

class Matrix3f;
class Matrix3i;
class Matrix3u;

class Matrix4f;
class Matrix4i;
class Matrix4u;

struct SimplexVertex;
struct ComplexVertex;
struct SimpleAnimVertex;
struct ComplexAnimVertex;
template<uint32 size = 4>
struct SimpleBigAnimVertex;
template<uint32 size = 4>
struct ComplexBigAnimVertex;

class Triangle;
class Plane;
class Sphere;
class BoxAAB;
class Rectangle;
class Capsule;
class Frustum;
class UtilityCamera;

class File;

class Time;
class DLLDynamics;
class Logger;
class MemoryManager;
}