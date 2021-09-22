#include "eeCollitionDetector.h"

namespace eeEngineSDK {
bool CollitionDetector::isColliding(Vector3f _point, Plane _plane)
{
  float real = _plane.getNormal().dot(_plane.getPoint());
  float dot = _plane.getNormal().dot(_point);
  return Math::abs(dot - real) < .001f;
}
bool CollitionDetector::isColliding(Plane _plane, Vector3f _point)
{
  float real = _plane.getNormal().dot(_plane.getPoint());
  float dot = _plane.getNormal().dot(_point);
  return Math::abs(dot - real) < .001f;
}
}