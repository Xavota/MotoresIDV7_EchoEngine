#include "eeSphere.h"
#include "eePlane.h"
#include "eeMath.h"

namespace eeEngineSDK {
const Sphere Sphere::kUNITARY = Sphere(Vector3f(0.0f,0.0f,0.0f), 1.0f);

Sphere::Sphere() : m_center(0.0f, 0.0f, 0.0f), m_radious(1.0f)
{
}

Sphere::Sphere(const Vector3f& center, float radious)
 : m_center(center),
   m_radious(radious)
{
}
Sphere::~Sphere()
{
}
bool
Sphere::intersects(const Vector3f& point) const
{
  return Math::intersectionSpherePoint(*this, point);
}
bool
Sphere::intersects(const Plane& plane) const
{
  return Math::intersectionSpherePlane(*this, plane);
}
bool
Sphere::intersects(const Sphere& sphere)
{
  return Math::intersectionSphereSphere(*this, sphere);
}
bool
Sphere::intersects(const BoxAAB& box)
{
  return Math::intersectionBoxSphere(box, *this);
}
bool
Sphere::intersects(const Capsule& capsule)
{
  return Math::intersectionCapsuleSphere(capsule, *this);
}
}