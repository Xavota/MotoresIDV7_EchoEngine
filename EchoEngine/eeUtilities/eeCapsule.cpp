#include "eeCapsule.h"

namespace eeEngineSDK {
  Capsule::Capsule()
  {
  }
  Capsule::Capsule(const Vector3f& center, 
                   const float height, 
                   const float radious) :
                   m_center(center),
                   m_height(height),
                   m_radious(radious)
  {
  }
  Capsule::~Capsule()
  {
  }
}