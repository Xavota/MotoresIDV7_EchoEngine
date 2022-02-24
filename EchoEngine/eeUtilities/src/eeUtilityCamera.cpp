#include "eeUtilityCamera.h"

namespace eeEngineSDK {
UtilityCamera::UtilityCamera(CameraDesc desc)
{
  init(desc);
}
void
UtilityCamera::init(CameraDesc desc)
{
  m_projectionType = desc.projectionType;
  m_fovAngleY = desc.fovAngleY;
  m_viewSize = desc.viewSize;
  m_nearZ = desc.nearZ;
  m_farZ = desc.farZ;

  m_dirtyView = true;
  m_dirtyProj = true;
}
Vector3f
UtilityCamera::getEyePosition()
{
  return m_eyePos;
}
void UtilityCamera::setEyePosition(Vector3f eyePos)
{
  m_eyePos = eyePos;
  m_dirtyView = true;
  m_dirtyFrustum = true;
}
Vector3f
UtilityCamera::getLookAtPosition()
{
  return m_lookAt;
}
void UtilityCamera::setLookAtPosition(Vector3f lookAtPos)
{
  m_lookAt = lookAtPos;
  m_dirtyView = true;
  m_dirtyFrustum = true;
}
Vector3f
UtilityCamera::getUpVector()
{
  return m_upVector;
}
void
UtilityCamera::setProjectionType(CAMERA_PROJECTION_TYPE type)
{
  m_projectionType = type;

  m_dirtyProj = true;
}
CAMERA_PROJECTION_TYPE
UtilityCamera::getProjectionType()
{
  return m_projectionType;
}
void
UtilityCamera::setFovAngle(float angle)
{
  m_fovAngleY = angle;

  m_dirtyProj = true;
}
float
UtilityCamera::getFovAngle()
{
  return m_fovAngleY;
}
void
UtilityCamera::setViewSize(Vector2f viewSize)
{
  m_viewSize = viewSize;

  m_dirtyProj = true;
}
Vector2f
UtilityCamera::getViewSize()
{
  return m_viewSize;
}
void
UtilityCamera::setNearPlane(float near)
{
  m_nearZ = near;

  m_dirtyProj = true;
}
float
UtilityCamera::getNearPlane()
{
  return m_nearZ;
}
void
UtilityCamera::setFarPlane(float far)
{
  m_farZ = far;

  m_dirtyProj = true;
}
float
UtilityCamera::getFarPlane()
{
  return m_farZ;
}
Vector3f
UtilityCamera::getFront()
{
  return (m_lookAt - m_eyePos).getNormalize();
}
Vector3f
UtilityCamera::getRight()
{
  Vector3f front = getFront();

  return -front.cross(m_upVector).getNormalize();
}
Vector3f
UtilityCamera::getUp()
{
  return getFront().cross(getRight());
}
Matrix4f
UtilityCamera::getViewMatrix()
{
  if (m_dirtyView) {
    m_dirtyView = false;

    m_viewMat = Matrix4f::viewMatrix(m_eyePos, m_lookAt, m_upVector);
  }
  return m_viewMat;
}
Matrix4f
UtilityCamera::getProjectionMatrix()
{
  if (m_dirtyProj) {
    m_dirtyProj = false;
    
    switch (m_projectionType) {
    case eeEngineSDK::CAMERA_PROJECTION_TYPE::kNone:
      m_projectionMat = Matrix4f::kIDENTITY;
      break;
    case eeEngineSDK::CAMERA_PROJECTION_TYPE::kOrthographic:
      m_projectionMat = Matrix4f::orthograficMatrixMatrix(m_viewSize.x,
                                                          m_viewSize.y,
                                                          m_nearZ,
                                                          m_farZ);
      break;
    case eeEngineSDK::CAMERA_PROJECTION_TYPE::kPerspective:
      m_projectionMat = Matrix4f::perspectiveMatrix(m_fovAngleY,
                                                    m_viewSize.x / m_viewSize.y,
                                                    m_nearZ,
                                                    m_farZ);
      break;
    }
  }
  return m_projectionMat;
}
void UtilityCamera::updateFrustrum()
{
  if (m_dirtyFrustum) {
    m_dirtyFrustum = false;

    m_viewFrustum.UpdateFrustum(m_eyePos,
                                getFront(),
                                getUp(),
                                getRight(),
                                m_nearZ,
                                m_farZ,
                                m_fovAngleY,
                                m_viewSize.x / m_viewSize.y);
  }
}
bool UtilityCamera::isSphereOnCamera(const Sphere& sphereBound)
{
  updateFrustrum();
  return m_viewFrustum.isSphereInside(sphereBound);
}
bool UtilityCamera::isBoxOnCamera(const BoxAAB& boxBound)
{
  updateFrustrum();
  return m_viewFrustum.isBoxInside(boxBound);
}
}