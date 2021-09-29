#include "eeCapsule.h"
#include "eeMath.h"

namespace eeEngineSDK {
const Capsule Capsule::SIMPLEX(Vector3f(0.0f, 0.0f, 0.0f), 2.0f, 0.5f);


Capsule::Capsule() :
  m_center(0.0f, 0.0f, 0.0f),
  m_height(2.0f),
  m_radious(0.5f)
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
bool Capsule::intersects(const Vector3f& point) const
{
  return Math::intersectionCapsulePoint(*this, point);
}
bool Capsule::intersects(const Plane& plane) const
{
  return Math::intersectionCapsulePlane(*this, plane);
}
bool Capsule::intersects(const Sphere& sphere)
{
  return Math::intersectionCapsuleSphere(*this, sphere);
}
bool Capsule::intersects(const BoxAAB& box)
{
  return Math::intersectionCapsuleBox(*this, box);
}
bool Capsule::intersects(const Capsule& capsule)
{
  return Math::intersectionCapsuleCapsule(*this, capsule);
}
}