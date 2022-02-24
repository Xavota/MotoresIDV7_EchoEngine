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

  Vector3f relativePoint = sphere.getCenter()
    - m_nearPlane.getNormal() * m_nearPlane.d;
  if (relativePoint.dot(m_nearPlane.getNormal()) < 0.0f) {
    return false;
  }
  relativePoint = sphere.getCenter()
    - m_farPlane.getNormal() * m_farPlane.d;
  if (relativePoint.dot(m_farPlane.getNormal()) < 0.0f) {
    return false;
  }
  relativePoint = sphere.getCenter()
    - m_leftPlane.getNormal() * m_leftPlane.d;
  if (relativePoint.dot(m_leftPlane.getNormal()) < 0.0f) {
    return false;
  }
  relativePoint = sphere.getCenter()
    - m_rightPlane.getNormal() * m_rightPlane.d;
  if (relativePoint.dot(m_rightPlane.getNormal()) < 0.0f) {
    return false;
  }
  relativePoint = sphere.getCenter()
    - m_topPlane.getNormal() * m_topPlane.d;
  if (relativePoint.dot(m_topPlane.getNormal()) < 0.0f) {
    return false;
  }
  relativePoint = sphere.getCenter()
    - m_downPlane.getNormal() * m_downPlane.d;
  if (relativePoint.dot(m_downPlane.getNormal()) < 0.0f) {
    return false;
  }

  return true;
}
bool
Frustum::isBoxInside(const BoxAAB& box)
{
  return true;
}
}