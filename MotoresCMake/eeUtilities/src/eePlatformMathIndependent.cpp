#include "eePlatformMath.h"

#include "eeVector3.h"
#include "eePlane.h"
#include "eeSphere.h"
#include "eeBox.h"
#include "eeCapsule.h"
#include "eeRectangle.h"

namespace eeEngineSDK
{
const float PlatformMath::kPI = atan(1.0f) * 4;
const float PlatformMath::kPI_OVER_180 = PlatformMath::kPI / 180.0f;
const float PlatformMath::k180_OVER_PI = 180 / PlatformMath::kPI;
const float PlatformMath::k2_PI = PlatformMath::kPI * 2.0f;
const float PlatformMath::kPI_OVER_2 = PlatformMath::kPI / 2.0f;

const float PlatformMath::kEuler = std::expf(1);

const float PlatformMath::kFLOAT_EQUAL_SMALL_DIFFERENCE = 0.001f;
const float PlatformMath::kMAX_FLOAT = std::numeric_limits<float>::max();
const float PlatformMath::kMIN_FLOAT = std::numeric_limits<float>::min();
const int32 PlatformMath::kMIN_INT = std::numeric_limits<int32>::min();
const int32 PlatformMath::kMAX_INT = std::numeric_limits<int32>::max();
const uint32 PlatformMath::kMAX_UINT = std::numeric_limits<uint32>::max();


float 
PlatformMath::planeDistance(const Plane& p, const Vector3f& point)
{
  Vector3f d = point - p.getPoint();
  return d.dot(p.getNormal());
}
bool 
PlatformMath::sphereInsidePlane(const Sphere& s, const Plane& p) 
{
  return -planeDistance(p, s.getCenter()) > s.getRadious();
}
bool 
PlatformMath::sphereIntersectsPlane(const Sphere& s, const Plane& p) 
{
  return abs(planeDistance(p, s.getCenter())) <= s.getRadious();
}
bool 
PlatformMath::sphereInsideBox(const Sphere& s, const BoxAAB& b) 
{
  Plane front(b.getA(), Vector3f::kFORWARD);
  Plane back(b.getB(), -Vector3f::kFORWARD);
  Plane top(b.getA(), Vector3f::kUP);
  Plane bottom(b.getB(), -Vector3f::kUP);
  Plane left(b.getA(), -Vector3f::kRIGHT);
  Plane right(b.getB(), Vector3f::kRIGHT);
  if (!sphereInsidePlane(s, front)) { return false; }
  if (!sphereInsidePlane(s, back)) { return false; }
  if (!sphereInsidePlane(s, top)) { return false; }
  if (!sphereInsidePlane(s, bottom)) { return false; }
  if (!sphereInsidePlane(s, left)) { return false; }
  if (!sphereInsidePlane(s, right)) { return false; }

  return true;
}
bool 
PlatformMath::sphereIntersectsPlanePoint(const Sphere& s, 
                                         const Plane& p, 
                                         Vector3f* point, 
                                         float* radius) 
{
  float d = planeDistance(p, s.getCenter());
  Vector3f proj = p.getNormal() * d;
  *point = s.getCenter() - proj;
  *radius = sqrt(max(s.getRadious() * s.getRadious() - d * d, 0));
  return abs(d) <= s.getRadious();
}
bool 
PlatformMath::sphereIntersectsBox(const Sphere& s, const BoxAAB& b) {

  Plane front(b.getA(), Vector3f::kFORWARD);
  Plane back(b.getB(), -Vector3f::kFORWARD);
  Plane top(b.getA(), Vector3f::kUP);
  Plane bottom(b.getB(), -Vector3f::kUP);
  Plane left(b.getA(), -Vector3f::kRIGHT);
  Plane right(b.getB(), Vector3f::kRIGHT);


  Vector3f point;
  float radius;

  if (sphereIntersectsPlanePoint(s, top, &point, &radius)) {
    if (planeDistance(left, point) <= radius &&
        planeDistance(right, point) <= radius &&
        planeDistance(front, point) <= radius &&
        planeDistance(back, point) <= radius) {
      return true;
    }
  }

  if (sphereIntersectsPlanePoint(s, bottom, &point, &radius)) {
    if (planeDistance(left, point) <= radius &&
        planeDistance(right, point) <= radius &&
        planeDistance(front, point) <= radius &&
        planeDistance(back, point) <= radius) {
      return true;
    }
  }

  if (sphereIntersectsPlanePoint(s, left, &point, &radius)) {
    if (planeDistance(top, point) <= radius &&
        planeDistance(bottom, point) <= radius &&
        planeDistance(front, point) <= radius &&
        planeDistance(back, point) <= radius) {
      return true;
    }
  }

  if (sphereIntersectsPlanePoint(s, right, &point, &radius)) {
    if (planeDistance(top, point) <= radius &&
        planeDistance(bottom, point) <= radius &&
        planeDistance(front, point) <= radius &&
        planeDistance(back, point) <= radius) {
      return true;
    }
  }

  if (sphereIntersectsPlanePoint(s, front, &point, &radius)) {
    if (planeDistance(top, point) <= radius &&
        planeDistance(bottom, point) <= radius &&
        planeDistance(left, point) <= radius &&
        planeDistance(right, point) <= radius) {
      return true;
    }
  }

  if (sphereIntersectsPlanePoint(s, back, &point, &radius)) {
    if (planeDistance(top, point) <= radius &&
        planeDistance(bottom, point) <= radius &&
        planeDistance(left, point) <= radius &&
        planeDistance(right, point) <= radius) {
      return true;
    }
  }

  return false;
}

bool
PlatformMath::intersectionPlanePoint(const Plane& _plane,
                                     const Vector3f& _point)
{
  float real = _point.x * _plane.x + _point.y * _plane.y + _point.z * _plane.z;
  return abs(_plane.d - real) < kFLOAT_EQUAL_SMALL_DIFFERENCE;
}
bool 
PlatformMath::intersectionPlanePlane(const Plane& _plane1, 
                                     const Plane& _plane2)
{
  const Vector3f& n1 = _plane1.getNormal();
  const Vector3f& n2 = _plane2.getNormal();

  return n1.cross(n2) != Vector3f::kZERO;
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
  return sphereIntersectsPlane(_sphere, _plane);
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
      && _point.y >= A.y && _point.y <= B.y
      && _point.z >= A.z && _point.z <= B.z;
}
bool 
PlatformMath::intersectionBoxPlane(const BoxAAB& _box, const Plane& _plane)
{
  const Vector3f& n = _plane.getNormal();
  const Vector3f& A = _box.getA() - _plane.getPoint();
  float dotAn = A.dot(n);

  const Vector3f& B = _box.getB() - _plane.getPoint();
  if (dotAn * B.dot(n) < 0.0f) {
    return true;
  }

  const Vector3f& C = Vector3f(A.x, A.y, B.z);
  if (dotAn * C.dot(n) < 0.0f) {
    return true;
  }

  const Vector3f& D = Vector3f(A.x, B.y, A.z);
  if (dotAn * D.dot(n) < 0.0f) {
    return true;
  }

  const Vector3f& E = Vector3f(A.x, B.y, B.z);
  if (dotAn * E.dot(n) < 0.0f) {
    return true;
  }

  const Vector3f& F = Vector3f(B.x, A.y, A.z);
  if (dotAn * F.dot(n) < 0.0f) {
    return true;
  }

  const Vector3f& G = Vector3f(B.x, A.y, B.z);
  if (dotAn * G.dot(n) < 0.0f) {
    return true;
  }

  const Vector3f& H = Vector3f(B.x, B.y, A.z);
  if (dotAn * H.dot(n) < 0.0f) {
    return true;
  }

  return false;
}
bool 
PlatformMath::intersectionBoxSphere(const BoxAAB& _box, const Sphere& _sphere)
{
  return sphereInsideBox(_sphere, _box) || sphereIntersectsBox(_sphere, _box);
}
bool 
PlatformMath::intersectionBoxBox(const BoxAAB& _box1, const BoxAAB& _box2)
{
  const Vector3f& A1 = _box1.getA();
  if (intersectionBoxPoint(_box2, A1)) {
    return true;
  }
  const Vector3f& A2 = _box2.getA();
  if (intersectionBoxPoint(_box1, A2)) {
    return true;
  }

  const Vector3f& B1 = _box1.getB();
  if (intersectionBoxPoint(_box2, B1)) {
    return true;
  }
  const Vector3f& B2 = _box2.getB();
  if (intersectionBoxPoint(_box1, B2)) {
    return true;
  }

  const Vector3f& C1 = Vector3f(A1.x, A1.y, B1.z);
  if (intersectionBoxPoint(_box2, C1)) {
    return true;
  }
  const Vector3f& C2 = Vector3f(A2.x, A2.y, B2.z);
  if (intersectionBoxPoint(_box1, C2)) {
    return true;
  }

  const Vector3f& D1 = Vector3f(A1.x, B1.y, A1.z);
  if (intersectionBoxPoint(_box2, D1)) {
    return true;
  }
  const Vector3f& D2 = Vector3f(A2.x, B2.y, A2.z);
  if (intersectionBoxPoint(_box1, D2)) {
    return true;
  }

  const Vector3f& E1 = Vector3f(A1.x, B1.y, B1.z);
  if (intersectionBoxPoint(_box2, E1)) {
    return true;
  }
  const Vector3f& E2 = Vector3f(A2.x, B2.y, B2.z);
  if (intersectionBoxPoint(_box1, E2)) {
    return true;
  }

  const Vector3f& F1 = Vector3f(B1.x, A1.y, A1.z);
  if (intersectionBoxPoint(_box2, F1)) {
    return true;
  }
  const Vector3f& F2 = Vector3f(B2.x, A2.y, A2.z);
  if (intersectionBoxPoint(_box1, F2)) {
    return true;
  }

  const Vector3f& G1 = Vector3f(B1.x, A1.y, B1.z);
  if (intersectionBoxPoint(_box2, G1)) {
    return true;
  }
  const Vector3f& G2 = Vector3f(B2.x, A2.y, B2.z);
  if (intersectionBoxPoint(_box1, G2)) {
    return true;
  }

  const Vector3f& H1 = Vector3f(B1.x, B1.y, A1.z);
  if (intersectionBoxPoint(_box2, H1)) {
    return true;
  }
  const Vector3f& H2 = Vector3f(B2.x, B2.y, A2.z);
  if (intersectionBoxPoint(_box1, H2)) {
    return true;
  }
  
  return false;
}
bool
PlatformMath::intersectionCapsulePoint(const Capsule& _capsule, 
                                       const Vector3f& _point)
{
  Vector3f center = _capsule.getCenter();
  float r = _capsule.getRadious();

  Vector3f cA = center + (Vector3f::kUP * ((_capsule.getHeight() / 2) - r));

  Sphere A(cA, r);
  if (intersectionSpherePoint(A, _point)) {
    return true;
  }

  Vector3f cB = center - (Vector3f::kUP * ((_capsule.getHeight() / 2) - r));

  Sphere B(cB, r);
  if (intersectionSpherePoint(B, _point)) {
    return true;
  }

  Vector3f d = _point - center;
  float h = d.getMagnitud();
  float a = d.dot(Vector3f::kUP);
  float distance = sqrt(h*h - a*a);

  if (distance <= r && _point.y <= cA.y && _point.y >= cB.y) {
    return true;
  }

  return false;
}
bool
PlatformMath::intersectionCapsulePlane(const Capsule& _capsule, 
                                       const Plane& _plane)
{
  Vector3f center = _capsule.getCenter();
  float r = _capsule.getRadious();

  Vector3f cA = center + (Vector3f::kUP * ((_capsule.getHeight() / 2) - r));

  Sphere A(cA, r);
  if (intersectionSpherePlane(A, _plane)) {
    return true;
  }

  Vector3f cB = center - (Vector3f::kUP * ((_capsule.getHeight() / 2) - r));

  Sphere B(cB, r);
  if (intersectionSpherePlane(B, _plane)) {
    return true;
  }

  float d1 = planeDistance(_plane, cA);
  float d2 = planeDistance(_plane, cB);

  if (d1 * d2 < 0) {
    return true;
  }

  return false;
}
bool
PlatformMath::intersectionCapsuleSphere(const Capsule& _capsule, 
                                        const Sphere& _sphere)
{
  Vector3f center = _capsule.getCenter();
  float r = _capsule.getRadious();

  Vector3f cA = center + (Vector3f::kUP * ((_capsule.getHeight() / 2) - r));

  Sphere A(cA, r);
  if (intersectionSphereSphere(A, _sphere)) {
    return true;
  }

  Vector3f cB = center - (Vector3f::kUP * ((_capsule.getHeight() / 2) - r));

  Sphere B(cB, r);
  if (intersectionSphereSphere(B, _sphere)) {
    return true;
  }

  Vector3f sCenter = _sphere.getCenter();
  
  Vector3f d = _sphere.getCenter() - center;
  float h = d.getMagnitud();
  float a = d.dot(Vector3f::kUP);
  float distance = sqrt(h * h - a * a);

  if (distance <= r + _sphere.getRadious() 
   && sCenter.y <= cA.y 
   && sCenter.y >= cB.y) {
    return true;
  }

  return false;
}
/*bool
PlatformMath::intersectionCapsuleBox(const Capsule& _capsule, 
                                     const BoxAAB& _box)
{
  return false;
}*/
bool
PlatformMath::intersectionCapsuleCapsule(const Capsule& _capsule1, 
                                         const Capsule& _capsule2)
{
  Vector3f center1 = _capsule1.getCenter();
  float r1 = _capsule1.getRadious();
  float h1 = _capsule1.getHeight();

  Vector3f center2 = _capsule2.getCenter();
  float r2 = _capsule2.getRadious();
  float h2 = _capsule2.getHeight();


  Vector3f cA1 = center1 + (Vector3f::kUP * ((h1 / 2) - r1));
  Vector3f cA2 = center2 + (Vector3f::kUP * ((h2 / 2) - r2));

  Sphere A1(cA1, r1);
  Sphere A2(cA2, r2);

  Vector3f cB1 = center1 - (Vector3f::kUP * ((h1 / 2) - r1));
  Vector3f cB2 = center2 - (Vector3f::kUP * ((h2 / 2) - r2));

  Sphere B1(cB1, r1);
  Sphere B2(cB2, r2);

  if (intersectionSphereSphere(A1, B2)) {
    return true;
  }
  if (intersectionSphereSphere(A2, B1)) {
    return true;
  }



  Vector3f d = center2 - center1;
  float h = d.getMagnitud();
  float a = d.dot(Vector3f::kUP);
  float distance = sqrt(h * h - a * a);

  if (distance <= r1 + r2 && cA2.y >= cB1.y && cB2.y <= cA1.y) {
    return true;
  }

  return false;


  return false;
  // Posibles coliciones ya con inclinación
  // https://wickedengine.net/2020/04/26/capsule-collision-detection/#:~:text=T
  // he%20capsule%20collisions%20in%20action%20Capsules%20are%20often,well%20fo
  // r%20other%20types%20of%20more%20rounded%20characters.
}
bool
PlatformMath::intersectionRectanglePoint2D(const Rectangle& _rectangle, 
                                           const Vector2f& _point2D)
{
  Vector2f A = _rectangle.getA();
  Vector2f B = _rectangle.getB();
  return _point2D.x >= A.x && _point2D.x <= B.x
      && _point2D.y >= A.y && _point2D.y <= B.y;
}
bool 
PlatformMath::intersectionRectangleRectangle(const Rectangle& _rectangle1,
                                             const Rectangle& _rectangle2)
{
  const Vector2f& A1 = _rectangle1.getA();
  if (intersectionRectanglePoint2D(_rectangle2, A1)) {
    return true;
  }
  const Vector2f& A2 = _rectangle2.getA();
  if (intersectionRectanglePoint2D(_rectangle1, A2)) {
    return true;
  }

  const Vector2f& B1 = _rectangle1.getB();
  if (intersectionRectanglePoint2D(_rectangle2, B1)) {
    return true;
  }
  const Vector2f& B2 = _rectangle2.getB();
  if (intersectionRectanglePoint2D(_rectangle1, B2)) {
    return true;
  }

  const Vector2f& C1 = Vector2f(A1.x, B1.y);
  if (intersectionRectanglePoint2D(_rectangle2, C1)) {
    return true;
  }
  const Vector2f& C2 = Vector2f(A2.x, B2.y);
  if (intersectionRectanglePoint2D(_rectangle1, C2)) {
    return true;
  }

  const Vector2f& D1 = Vector2f(B1.x, A1.y);
  if (intersectionRectanglePoint2D(_rectangle2, D1)) {
    return true;
  }
  const Vector2f& D2 = Vector2f(B2.x, A2.y);
  if (intersectionRectanglePoint2D(_rectangle1, D2)) {
    return true;
  }

  return false;
}
}