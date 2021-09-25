#include "eeSphere.h"
#include "eePlane.h"
#include "eeMath.h"

namespace eeEngineSDK {
const Sphere Sphere::UNITARY = Sphere(Vector3f(0.0f,0.0f,0.0f), 1.0f);

Sphere::Sphere(Vector3f center, float radious)
              : m_center(center), m_radious(radious)
{
}
Sphere::~Sphere()
{
}
/*bool
Sphere::intersects(const Vector3f& point) const
{
  return Math::intersectionSpherePoint(*this, point);
}
bool
Sphere::intersects(const Plane& plane) const
{
  return Math::intersectionSpherePlane(*this, plane);
}*/
}