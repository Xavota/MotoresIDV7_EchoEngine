#include "eePlatformMath.h"

namespace eeEngineSDK
{
const float PlatformMath::kPI = 3.14159265f;
const float PlatformMath::kPI_OVER_180 = 0.01745329f;
const float PlatformMath::k180_OVER_PI = 57.29577951f;
const float PlatformMath::kFLOAT_EQUAL_SMALL_DIFFERENCE = 0.001f;

bool PlatformMath::isColliding(Vector3f _point, Plane _plane)
{
  float real = _plane.getNormal().dot(_plane.getPoint());
  float dot = _plane.getNormal().dot(_point);
  return abs(dot - real) < .001f;
}
bool PlatformMath::isColliding(Plane _plane, Vector3f _point)
{
  float real = _plane.getNormal().dot(_plane.getPoint());
  float dot = _plane.getNormal().dot(_point);
  return abs(dot - real) < .001f;
}

}