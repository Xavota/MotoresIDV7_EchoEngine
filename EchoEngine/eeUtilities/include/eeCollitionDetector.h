#pragma once
#include "eePrerequisitesUtilities.h"
#include "eeVector3.h"
#include "eePlane.h"

namespace eeEngineSDK {
class CollitionDetector
{
 public:
  static bool isColliding(Vector3f _point, Plane _plane);
  static bool isColliding(Plane _plane, Vector3f _point);
};
}
