#include "eeCCamera.h"
#include "eeMatrix3.h"

#include "eeActor.h"
#include "eeCTransform.h"

namespace eeEngineSDK {
CCamera::CCamera()
{
  m_upVector = Vector3f::UP;
}
void
CCamera::init(CameraDesc desc)
{
  m_projectionType = desc.projectionType;
  m_fovAngleY = desc.fovAngleY;
  m_viewSize = desc.viewSize;
  m_nearZ = desc.nearZ;
  m_farZ = desc.farZ;

  m_dirtyView = true;
  m_dirtyProj = true;
}
void
CCamera::update(Actor* actor)
{
  if (!actor)
    return;
  SPtr<CTransform> transform = actor->getComponent<CTransform>();
  if (!transform)
    return;

  m_eyePos = transform->getPosition();
  m_lookAt = m_eyePos + transform->getRotation().getFrontVector();
  m_dirtyView = true;
}
void
CCamera::setEyePosition(Vector3f pos)
{
  m_eyePos = pos;

  m_dirtyView = true;
}
Vector3f
CCamera::getEyePosition()
{
  return m_eyePos;
}
void
CCamera::setLookAtPosition(Vector3f pos)
{
  m_lookAt = pos;

  m_dirtyView = true;
}
Vector3f
CCamera::getLookAtPosition()
{
  return m_lookAt;
}
void CCamera::rotateCamera(Quaternion rot)
{
  m_lookAt -= m_eyePos;
  
  m_lookAt *= Matrix3f::rotationMatrix(rot.getEuclidean());
  
  m_lookAt += m_eyePos;
}
void
CCamera::setUpVector(Vector3f pos)
{
  m_upVector = pos;

  m_dirtyView = true;
}
Vector3f
CCamera::getUpVector()
{
  return m_upVector;
}
void
CCamera::setProjectionType(eCAMERA_PROJECTION_TYPE type)
{
  m_projectionType = type;

  m_dirtyProj = true;
}
eCAMERA_PROJECTION_TYPE
CCamera::getProjectionType()
{
  return m_projectionType;
}
void
CCamera::setFovAngle(float angle)
{
  m_fovAngleY = angle;

  m_dirtyProj = true;
}
float
CCamera::getFovAngle()
{
  return m_fovAngleY;
}
void
CCamera::setViewSize(Vector2f viewSize)
{
  m_viewSize = viewSize;

  m_dirtyProj = true;
}
Vector2f
CCamera::getViewSize()
{
  return m_viewSize;
}
void
CCamera::setNearPlane(float near)
{
  m_nearZ = near;

  m_dirtyProj = true;
}
float
CCamera::getNearPlane()
{
  return m_nearZ;
}
void
CCamera::setFarPlane(float far)
{
  m_farZ = far;

  m_dirtyProj = true;
}
float
CCamera::getFarPlane()
{
  return m_farZ;
}
Vector3f CCamera::getFront()
{
  return (m_lookAt - m_eyePos).getNormalize();
}
Vector3f CCamera::getRight()
{
  Vector3f front = getFront();

  return -front.cross(m_upVector).getNormalize();
}
Matrix4f
CCamera::getViewMatrix()
{
  if (m_dirtyView)
  {
    m_dirtyView = false;

    m_viewMat = Matrix4f::viewMatrix(m_eyePos, m_lookAt, m_upVector);
  }
  return m_viewMat;
}
Matrix4f
CCamera::getProjectionMatrix()
{
  if (m_dirtyProj)
  {
    m_dirtyProj = false;
    
    switch (m_projectionType)
    {
    case eeEngineSDK::eCAMERA_PROJECTION_TYPE::NONE:
      m_projectionMat = Matrix4f::IDENTITY;
      break;
    case eeEngineSDK::eCAMERA_PROJECTION_TYPE::ORTHOGRAPHIC:
      m_projectionMat = Matrix4f::orthograficMatrixMatrix(m_viewSize.x,
                                                          m_viewSize.y,
                                                          m_nearZ,
                                                          m_farZ);
      break;
    case eeEngineSDK::eCAMERA_PROJECTION_TYPE::PERSPECTIVE:
      m_projectionMat = Matrix4f::perspectiveMatrix(m_fovAngleY,
                                                    m_viewSize.x / m_viewSize.y,
                                                    m_nearZ,
                                                    m_farZ);
      break;
    }
  }
  return m_projectionMat;
}
}