#include "eeFrustum.h"
#include "eeMath.h"

namespace eeEngineSDK {
Frustum::Frustum(const Vector3f& position,
                 const Vector3f& frontVec,
                 const Vector3f& upVec,
                 const Vector3f& rightVec,
                 float nearDistance,
                 float farDistance,
                 float fovAngle,
                 float aspectRatio)
{
  UpdateFrustum(position,
                frontVec,
                upVec,
                rightVec,
                nearDistance,
                farDistance,
                fovAngle,
                aspectRatio);
}

void
Frustum::UpdateFrustum(const Vector3f& position,
                       const Vector3f& frontVec,
                       const Vector3f& upVec,
                       const Vector3f& rightVec,
                       float nearDistance,
                       float farDistance,
                       float fovAngle,
                       float aspectRatio)
{
  // Recalculate Frustum
  Vector3f nearFront = frontVec * nearDistance;
  Vector3f nearUp = upVec * Math::tan(fovAngle) * nearDistance;
  Vector3f nearLeft = rightVec
                    * (Math::tan(fovAngle) * nearDistance * aspectRatio);


  Vector3f nw = (nearFront + nearUp - nearLeft) * 500.0f;
  Vector3f ne = (nearFront + nearUp + nearLeft) * 500.0f;
  Vector3f sw = (nearFront - nearUp - nearLeft) * 500.0f;
  Vector3f se = (nearFront - nearUp + nearLeft) * 500.0f;
  m_nearPlane.setNormal(frontVec);
  m_farPlane.setNormal(-frontVec);
  m_leftPlane.setNormal(nw.cross(sw).getNormalize());
  m_rightPlane.setNormal(se.cross(ne).getNormalize());
  m_topPlane.setNormal(ne.cross(nw).getNormalize());
  m_downPlane.setNormal(sw.cross(se).getNormalize());

  m_nearPlane.setPoint(position + nearFront);
  m_farPlane.setPoint(position + frontVec * farDistance);
  m_leftPlane.setPoint(position);
  m_rightPlane.setPoint(position);
  m_topPlane.setPoint(position);
  m_downPlane.setPoint(position);
}

bool
Frustum::isPointIn(const Vector3f point)
{
  Vector3f relativePoint = point - m_nearPlane.getNormal() * m_nearPlane.d;
  if (relativePoint.dot(m_nearPlane.getNormal()) < 0.0f) {
    return false;
  }
  relativePoint = point - m_farPlane.getNormal() * m_farPlane.d;
  if (relativePoint.dot(m_farPlane.getNormal()) < 0.0f) {
    return false;
  }
  relativePoint = point - m_leftPlane.getNormal() * m_leftPlane.d;
  if (relativePoint.dot(m_leftPlane.getNormal()) < 0.0f) {
    return false;
  }
  relativePoint = point - m_rightPlane.getNormal() * m_rightPlane.d;
  if (relativePoint.dot(m_rightPlane.getNormal()) < 0.0f) {
    return false;
  }
  relativePoint = point - m_topPlane.getNormal() * m_topPlane.d;
  if (relativePoint.dot(m_topPlane.getNormal()) < 0.0f) {
    return false;
  }
  relativePoint = point - m_downPlane.getNormal() * m_downPlane.d;
  if (relativePoint.dot(m_downPlane.getNormal()) < 0.0f) {
    return false;
  }

  return true;
}

bool
Frustum::isSphereInside(const Sphere& sphere)
{
  // See if in
  if (Math::intersectionSpherePlane(sphere, m_nearPlane)) {
    return true;
  }
  if (Math::intersectionSpherePlane(sphere, m_farPlane)) {
    return true;
  }
  if (Math::intersectionSpherePlane(sphere, m_leftPlane)) {
    return true;
  }
  if (Math::intersectionSpherePlane(sphere, m_rightPlane)) {
    return true;
  }
  if (Math::intersectionSpherePlane(sphere, m_topPlane)) {
    return true;
  }
  if (Math::intersectionSpherePlane(sphere, m_downPlane)) {
    return true;
  }

  return isPointIn(sphere.getCenter());
}
bool
Frustum::isBoxInside(const BoxAAB& box)
{
  // See if in
  if (Math::intersectionBoxPlane(box, m_nearPlane)) {
    return true;
  }
  if (Math::intersectionBoxPlane(box, m_farPlane)) {
    return true;
  }
  if (Math::intersectionBoxPlane(box, m_leftPlane)) {
    return true;
  }
  if (Math::intersectionBoxPlane(box, m_rightPlane)) {
    return true;
  }
  if (Math::intersectionBoxPlane(box, m_topPlane)) {
    return true;
  }
  if (Math::intersectionBoxPlane(box, m_downPlane)) {
    return true;
  }


  Vector3f size = box.getSize();
  Vector3f pointA = box.getA();
  Vector3f pointB = pointA + Vector3f(size.x, 0.0f,   0.0f);
  Vector3f pointC = pointA + Vector3f(0.0f,   size.y, 0.0f);
  Vector3f pointD = pointA + Vector3f(size.x, size.y, 0.0f);
  Vector3f pointE = pointA + Vector3f(0.0f,   0.0f,   size.z);
  Vector3f pointF = pointA + Vector3f(size.x, 0.0f,   size.z);
  Vector3f pointG = pointA + Vector3f(0.0f,   size.y, size.z);
  Vector3f pointH = pointA + Vector3f(size.x, size.y, size.z);

  if (isPointIn(pointA)) {
    return true;
  }
  if (isPointIn(pointB)) {
    return true;
  }
  if (isPointIn(pointC)) {
    return true;
  }
  if (isPointIn(pointD)) {
    return true;
  }
  if (isPointIn(pointE)) {
    return true;
  }
  if (isPointIn(pointF)) {
    return true;
  }
  if (isPointIn(pointG)) {
    return true;
  }
  if (isPointIn(pointH)) {
    return true;
  }

  return false;
}
}