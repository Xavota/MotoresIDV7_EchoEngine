#include "eePlane.h"
#include "eeSphere.h"
#include "eeMath.h"

namespace eeEngineSDK {
  const Plane Plane::XY = Plane(Vector3f(0.0f, 0.0f, 0.0f),
                                Vector3f(0.0f, 0.0f, 1.0f));
                                
  const Plane Plane::XZ = Plane(Vector3f(0.0f, 0.0f, 0.0f),
                                Vector3f(0.0f, 1.0f, 0.0f));

  const Plane Plane::YZ = Plane(Vector3f(0.0f, 0.0f, 0.0f),
                                Vector3f(1.0f, 0.0f, 1.0f));

Plane::Plane()
{}
Plane::Plane(const Vector3f& point, const Vector3f& normal)
            : m_point(point), m_normal(normal.getNormalize())
{
}
Plane::Plane(const Vector3f& pA, const Vector3f& pB, const Vector3f& pC)
{
  m_point = pA;

  Vector3f AB = pB - pA;
  Vector3f AC = pC - pA;

  m_normal = AB.cross(AC);
}
Plane::~Plane()
{
}
void
Plane::move(const Vector3f& movement)
{
  m_point += movement;
}
void
Plane::rotate(const Vector3f& rotation)
{
  //TODO: Multiplications of Matrix*Vector
}
bool
Plane::intersects(const Vector3f& point)
{
  return Math::intersectionPlanePoint(*this, point);
}
bool
Plane::intersects(const Sphere& sphere)
{
  return Math::intersectionSpherePlane(sphere, *this);
}
}