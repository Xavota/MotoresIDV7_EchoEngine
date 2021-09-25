#include "eePlatformMath.h"

namespace eeEngineSDK
{
const float PlatformMath::kPI = 3.14159265f;
const float PlatformMath::kPI_OVER_180 = 0.01745329f;
const float PlatformMath::k180_OVER_PI = 57.29577951f;

const float PlatformMath::kEuler = 2.71828183f;

const float PlatformMath::kFLOAT_EQUAL_SMALL_DIFFERENCE = 0.001f;
const float PlatformMath::kSMALL_FLOAT = -999999.0f;
const float PlatformMath::kBIG_FLOAT = 999999.0f;
const int32 PlatformMath::kSMALL_INT = -2147483648;
const int32 PlatformMath::kBIG_INT = 2147483647;

bool 
PlatformMath::intersectionPlanePoint(const Plane& _plane,
                                     const Vector3f& _point)
{
  float real = _plane.getNormal().dot(_plane.getPoint());
  float dot = _plane.getNormal().dot(_point);
  return abs(dot - real) < .001f;
}
bool 
PlatformMath::intersectionSpherePoint(const Sphere& _sphere, 
                                      const Vector3f& _point)
{
  const float distance = _point.getDistance(_sphere.getCenter());
  return distance <= _sphere.getRadious();
}
bool 
PlatformMath::intersectionSpherePlane(const Sphere& _sphere, 
                                      const Plane& _plane)
{
  const Vector3f P = _sphere.getCenter();
  const Vector3f Q = _plane.getPoint();

  const Vector3f n = _plane.getNormal();
  const Vector3f v = P - Q;

  const float distance = n.dot(v);

  return abs(distance) <= _sphere.getRadious();
}
}