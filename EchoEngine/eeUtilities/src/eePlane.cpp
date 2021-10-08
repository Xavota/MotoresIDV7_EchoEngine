#include "eePlane.h"
#include "eeMath.h"
#include "eeMatrix4.h"
#include "eeVector4.h"

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
{
  Vector3f norm = normal.getNormalize();

  x = norm.x;
  y = norm.y;
  z = norm.z;

  d = norm.dot(point);
}
Plane::Plane(const Vector3f& pA, const Vector3f& pB, const Vector3f& pC)
{
  Vector3f AB = pB - pA;
  Vector3f AC = pC - pA;

  Vector3f norm = AB.cross(AC).getNormalize();

  x = norm.x;
  y = norm.y;
  z = norm.z;

  d = norm.dot(pA);
}
Plane::Plane(const float a, const float b, const float c, const float d)
{
  x = a;
  y = b;
  z = c;
  this->d = d;
}
Plane::~Plane()
{
}
void
Plane::move(const Vector3f& movement)
{
  /*x += movement.x;
  y += movement.y;
  z += movement.z;*/
}
void
Plane::rotate(const Vector3f& rotation)
{
  Vector4f rotated = Matrix4f::rotationMatrix(rotation) * 
                     Vector4f(x, y, z, 0.0f);
  rotated.normalize();
  x = rotated.x;
  y = rotated.y;
  z = rotated.z;
}
const Vector3f&
Plane::getPoint() const
{
  //return m_point;
  return Vector3f();
}
void
Plane::setPoint(const Vector3f& point)
{
  //m_point = point;
}
const Vector3f&
Plane::getNormal() const
{
  return Vector3f(x,y,z);
}
void
Plane::setNormal(const Vector3f& normal)
{
  Vector3f nom = normal.getNormalize();
  x = nom.x;
  y = nom.y;
  z = nom.z;
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