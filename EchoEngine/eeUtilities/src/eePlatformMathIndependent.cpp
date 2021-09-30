#include "eePlatformMath.h"

#include "eeVector3.h"
#include "eePlane.h"
#include "eeSphere.h"
#include "eeBox.h"
#include "eeCapsule.h"
#include "eeRectangle.h"

namespace eeEngineSDK
{
const float PlatformMath::kPI = 3.14159265f;
const float PlatformMath::kPI_OVER_180 = 0.01745329f;
const float PlatformMath::k180_OVER_PI = 57.29577951f;

const float PlatformMath::kEuler = 2.71828183f;

const float PlatformMath::kFLOAT_EQUAL_SMALL_DIFFERENCE = 0.001f;
const float PlatformMath::kSMALL_FLOAT = -999999.0f;
const float PlatformMath::kBIG_FLOAT = 999999.0f;
const int32 PlatformMath::kSMALL_INT = -2147483648;
const int32 PlatformMath::kBIG_INT = 2147483647;

bool
PlatformMath::intersectionPlanePoint(const Plane& _plane,
                                     const Vector3f& _point)
{
  float real = _plane.getNormal().dot(_plane.getPoint());
  float dot = _plane.getNormal().dot(_point);
  return abs(dot - real) < .001f;
}
bool 
PlatformMath::intersectionPlanePlane(const Plane& _plane1, 
                                     const Plane& _plane2)
{
  const Vector3f& n1 = _plane1.getNormal();
  const Vector3f& n2 = _plane2.getNormal();

  return n1.cross(n2) != Vector3f::ZERO;
}
bool 
PlatformMath::intersectionSpherePoint(const Sphere& _sphere, 
                                      const Vector3f& _point)
{
  const float distance = _point.getDistance(_sphere.getCenter());
  return distance <= _sphere.getRadious();
}
bool 
PlatformMath::intersectionSpherePlane(const Sphere& _sphere, 
                                      const Plane& _plane)
{
  const Vector3f P = _sphere.getCenter();
  const Vector3f Q = _plane.getPoint();

  const Vector3f n = _plane.getNormal();
  const Vector3f v = P - Q;

  const float distance = n.dot(v);

  return abs(distance) <= _sphere.getRadious();
}
bool
PlatformMath::intersectionSphereSphere(const Sphere& _sphere1,
                                       const Sphere& _sphere2)
{
  float distance = _sphere1.getCenter().getDistance(_sphere2.getCenter());
  return distance <= _sphere1.getRadious() + _sphere2.getRadious();
}
bool 
PlatformMath::intersectionBoxPoint(const BoxAAB& _box, const Vector3f& _point)
{
  const Vector3f& A = _box.getA();
  const Vector3f& B = _box.getB();

  return _point.x >= A.x && _point.x <= B.x
      && _point.y >= B.y && _point.y <= A.y
      && _point.z >= B.z && _point.z <= A.z;
}
bool 
PlatformMath::intersectionBoxPlane(const BoxAAB& _box, const Plane& _plane)
{
  const Vector3f& n = _plane.getNormal();
  const Vector3f& A = _box.getA() - _plane.getPoint();
  float dotAn = A.dot(n);

  const Vector3f& B = _box.getB() - _plane.getPoint();
  if (dotAn * B.dot(n) < 0.0f)
  {
    return true;
  }

  const Vector3f& C = Vector3f(A.x, A.y, B.z);
  if (dotAn * C.dot(n) < 0.0f)
  {
    return true;
  }

  const Vector3f& D = Vector3f(A.x, B.y, A.z);
  if (dotAn * D.dot(n) < 0.0f)
  {
    return true;
  }

  const Vector3f& E = Vector3f(A.x, B.y, B.z);
  if (dotAn * E.dot(n) < 0.0f)
  {
    return true;
  }

  const Vector3f& F = Vector3f(B.x, A.y, A.z);
  if (dotAn * F.dot(n) < 0.0f)
  {
    return true;
  }

  const Vector3f& G = Vector3f(B.x, A.y, B.z);
  if (dotAn * G.dot(n) < 0.0f)
  {
    return true;
  }

  const Vector3f& H = Vector3f(B.x, B.y, A.z);
  if (dotAn * H.dot(n) < 0.0f)
  {
    return true;
  }

  return false;
}
bool 
PlatformMath::intersectionBoxSphere(const BoxAAB& _box, const Sphere& _sphere)
{
  //const Vector3f& A = _box.getA();
  //Vector3f(max(B.x, min(A.x, _sphere.getCenter().x)));
  return false;
}
bool 
PlatformMath::intersectionBoxBox(const BoxAAB& _box1, const BoxAAB& _box2)
{
  const Vector3f& A1 = _box1.getA();
  if (intersectionBoxPoint(_box2, A1))
  {
    return true;
  }
  const Vector3f& A2 = _box2.getA();
  if (intersectionBoxPoint(_box1, A2))
  {
    return true;
  }

  const Vector3f& B1 = _box1.getB();
  if (intersectionBoxPoint(_box2, B1))
  {
    return true;
  }
  const Vector3f& B2 = _box2.getB();
  if (intersectionBoxPoint(_box1, B2))
  {
    return true;
  }

  const Vector3f& C1 = Vector3f(A1.x, A1.y, B1.z);
  if (intersectionBoxPoint(_box2, C1))
  {
    return true;
  }
  const Vector3f& C2 = Vector3f(A2.x, A2.y, B2.z);
  if (intersectionBoxPoint(_box1, C2))
  {
    return true;
  }

  const Vector3f& D1 = Vector3f(A1.x, B1.y, A1.z);
  if (intersectionBoxPoint(_box2, D1))
  {
    return true;
  }
  const Vector3f& D2 = Vector3f(A2.x, B2.y, A2.z);
  if (intersectionBoxPoint(_box1, D2))
  {
    return true;
  }

  const Vector3f& E1 = Vector3f(A1.x, B1.y, B1.z);
  if (intersectionBoxPoint(_box2, E1))
  {
    return true;
  }
  const Vector3f& E2 = Vector3f(A2.x, B2.y, B2.z);
  if (intersectionBoxPoint(_box1, E2))
  {
    return true;
  }

  const Vector3f& F1 = Vector3f(B1.x, A1.y, A1.z);
  if (intersectionBoxPoint(_box2, F1))
  {
    return true;
  }
  const Vector3f& F2 = Vector3f(B2.x, A2.y, A2.z);
  if (intersectionBoxPoint(_box1, F2))
  {
    return true;
  }

  const Vector3f& G1 = Vector3f(B1.x, A1.y, B1.z);
  if (intersectionBoxPoint(_box2, G1))
  {
    return true;
  }
  const Vector3f& G2 = Vector3f(B2.x, A2.y, B2.z);
  if (intersectionBoxPoint(_box1, G2))
  {
    return true;
  }

  const Vector3f& H1 = Vector3f(B1.x, B1.y, A1.z);
  if (intersectionBoxPoint(_box2, H1))
  {
    return true;
  }
  const Vector3f& H2 = Vector3f(B2.x, B2.y, A2.z);
  if (intersectionBoxPoint(_box1, H2))
  {
    return true;
  }
  
  return false;
}
bool
PlatformMath::intersectionCapsulePoint(const Capsule& _capsule, 
                                       const Vector3f& _point)
{
  return false;
}
bool
PlatformMath::intersectionCapsulePlane(const Capsule& _capsule, 
                                       const Plane& _plane)
{
  return false;
}
bool
PlatformMath::intersectionCapsuleSphere(const Capsule& _capsule, 
                                        const Sphere& _sphere)
{
  return false;
}
bool
PlatformMath::intersectionCapsuleBox(const Capsule& _capsule, 
                                     const BoxAAB& _box)
{
  return false;
}
bool
PlatformMath::intersectionCapsuleCapsule(const Capsule& _capsule1, 
                                         const Capsule& _capsule2)
{
  return false;
}
bool
PlatformMath::intersectionRectanglePoint2D(const Rectangle& _rectangle, 
                                           const Vector2f& _point2D)
{
  Vector2f A = _rectangle.getA();
  Vector2f B = _rectangle.getB();
  return _point2D.x >= A.x && _point2D.x <= B.x
      && _point2D.y >= B.y && _point2D.y <= A.y;
}
bool 
PlatformMath::intersectionRectangleRectangle(const Rectangle& _rectangle1,
                                             const Rectangle& _rectangle2)
{
  const Vector2f& A1 = _rectangle1.getA();
  if (intersectionRectanglePoint2D(_rectangle2, A1))
  {
    return true;
  }
  const Vector2f& A2 = _rectangle2.getA();
  if (intersectionRectanglePoint2D(_rectangle1, A2))
  {
    return true;
  }

  const Vector2f& B1 = _rectangle1.getB();
  if (intersectionRectanglePoint2D(_rectangle2, B1))
  {
    return true;
  }
  const Vector2f& B2 = _rectangle2.getB();
  if (intersectionRectanglePoint2D(_rectangle1, B2))
  {
    return true;
  }

  const Vector2f& C1 = Vector2f(A1.x, B1.y);
  if (intersectionRectanglePoint2D(_rectangle2, C1))
  {
    return true;
  }
  const Vector2f& C2 = Vector2f(A2.x, B2.y);
  if (intersectionRectanglePoint2D(_rectangle1, C2))
  {
    return true;
  }

  const Vector2f& D1 = Vector2f(B1.x, A1.y);
  if (intersectionRectanglePoint2D(_rectangle2, D1))
  {
    return true;
  }
  const Vector2f& D2 = Vector2f(B2.x, A2.y);
  if (intersectionRectanglePoint2D(_rectangle1, D2))
  {
    return true;
  }

  return false;
}
}