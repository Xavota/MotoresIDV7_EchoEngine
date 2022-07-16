#include "eePlane.h"
#include "eeMath.h"
#include "eeMatrix4.h"
#include "eeVector4.h"

namespace eeEngineSDK {
const Plane Plane::kXY = Plane(Vector3f(0.0f, 0.0f, 0.0f),
                               Vector3f(0.0f, 0.0f, 1.0f));
                              
const Plane Plane::kXZ = Plane(Vector3f(0.0f, 0.0f, 0.0f),
                               Vector3f(0.0f, 1.0f, 0.0f));

const Plane Plane::kYZ = Plane(Vector3f(0.0f, 0.0f, 0.0f),
                               Vector3f(1.0f, 0.0f, 1.0f));

Plane::Plane() : d(0.0f)
{
  x = 0.0f;
  y = 0.0f;
  z = 1.0f;
}
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
  d += Vector3f(x,y,z).dot(movement);
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
Vector3f
Plane::getPoint() const
{
  if (z != 0.0f) {
    return Vector3f(0.0f, 0.0f, d/z);
  }
  else if (y != 0.0f) {
    return Vector3f(0.0f, d/y, 0.0f);
  }
  else {
    return Vector3f(d/x, 0.0f, 0.0f);
  }
}
void
Plane::setPoint(const Vector3f& point)
{
  d = Vector3f(x, y, z).dot(point);
}
Vector3f
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
  //d = Vector3f(x, y, z).dot(d);
}
bool
Plane::intersects(const Vector3f& point)
{
  return Math::intersectionPlanePoint(*this, point);
}
bool
Plane::intersects(const Plane& plane)
{
  return Math::intersectionPlanePlane(*this, plane);
}
bool
Plane::intersects(const Sphere& sphere)
{
  return Math::intersectionSpherePlane(sphere, *this);
}
bool
Plane::intersects(const BoxAAB& box)
{
  return Math::intersectionBoxPlane(box, *this);
}
bool
Plane::intersects(const Capsule& capsule)
{
  return Math::intersectionCapsulePlane(capsule, *this);
}
}