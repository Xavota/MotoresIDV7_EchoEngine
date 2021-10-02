#include "eePlane.h"
//#include "eeSphere.h"
#include "eeMath.h"
#include "eeMatrix4.h"

namespace eeEngineSDK {
  const Plane Plane::XY = Plane(Vector3f(0.0f, 0.0f, 0.0f),
                                Vector3f(0.0f, 0.0f, 1.0f));
                                
  const Plane Plane::XZ = Plane(Vector3f(0.0f, 0.0f, 0.0f),
                                Vector3f(0.0f, 1.0f, 0.0f));

  const Plane Plane::YZ = Plane(Vector3f(0.0f, 0.0f, 0.0f),
                                Vector3f(1.0f, 0.0f, 1.0f));

Plane::Plane() : m_point(0.0f, 0.0f, 0.0f), m_normal(0.0f, 0.0f, 1.0f)
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

  m_normal = AB.cross(AC).getNormalize();
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
  Vector4f rotated = Matrix4f::rotationMatrix(rotation) * 
                     Vector4f(m_normal.x, m_normal.y, m_normal.z, 0.0f);
  m_normal = Vector3f(rotated.x, rotated.y, rotated.z).getNormalize();
}
bool
Plane::intersects(const Vector3f& point)
{
  return Math::intersectionPlanePoint(*this, point);
}
bool Plane::intersects(const Plane& plane)
{
  return Math::intersectionPlanePlane(*this, plane);
}
bool
Plane::intersects(const Sphere& sphere)
{
  return Math::intersectionSpherePlane(sphere, *this);
}
bool Plane::intersects(const BoxAAB& box)
{
  return Math::intersectionBoxPlane(box, *this);
}
bool Plane::intersects(const Capsule& capsule)
{
  return Math::intersectionCapsulePlane(capsule, *this);
}
}