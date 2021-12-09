#include "eeCCamera.h"
#include "eeMatrix3.h"

#include "eeActor.h"
#include "eeCTransform.h"
#include "eeCModel.h"

#include "eeGraficsApi.h"
#include <eeMath.h>

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



  m_renderTarget = GraphicsApi::instance().createRenderTragetPtr();
  m_renderTarget->createAsIOTexture();

  m_depthStencil = GraphicsApi::instance().createDepthStencilPtr();
  m_depthStencil->create(1280, 720);
}
void
CCamera::update()
{
  EE_NO_EXIST_RETURN(m_actor);

  SPtr<CTransform> transform = m_actor->getTransform();

  m_eyePos = transform->getPosition();
  m_lookAt = m_eyePos + transform->getRotation().getFrontVector();
  m_dirtyView = true;
  m_dirtyFrustum = true;

  if (m_active)
    GraphicsApi::instance().addActiveCamera(
         MemoryManager::instance().reinterpretPtr<CCamera>(shared_from_this()));
}
Vector3f
CCamera::getEyePosition()
{
  return m_eyePos;
}
Vector3f
CCamera::getLookAtPosition()
{
  return m_lookAt;
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
Vector3f
CCamera::getFront()
{
  return (m_lookAt - m_eyePos).getNormalize();
}
Vector3f
CCamera::getRight()
{
  Vector3f front = getFront();

  return -front.cross(m_upVector).getNormalize();
}
Vector3f
CCamera::getUp()
{
  return getFront().cross(getRight());
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
bool
CCamera::isActive()
{
  return m_active;
}
void
CCamera::setActive(bool active)
{
  m_active = active;
}
bool
CCamera::isMain()
{
  return m_main;
}
void
CCamera::setMain(bool active)
{
  m_main = active;
}
SPtr<RenderTarget>
CCamera::getRenderTarget()
{
  return m_renderTarget;
}
SPtr<DepthStencil>
CCamera::getDepthStencil()
{
  return m_depthStencil;
}
bool
CCamera::isModelOnCamera(SPtr<CModel> ActorModel)
{
  if (!ActorModel)
    return false;

  if (m_dirtyFrustum)
  {
    m_dirtyFrustum = false;


    // Recalculate Frustum
    Vector3f nearFront = getFront() * m_nearZ;
    Vector3f nearUp = getUp() * Math::tan(m_fovAngleY) * m_nearZ;
    Vector3f nearLeft = getRight() *
      (Math::tan(m_fovAngleY) * m_nearZ * (m_viewSize.x / m_viewSize.y));


    Vector3f nw = (nearFront + nearUp - nearLeft) * 500.0f;
    Vector3f ne = (nearFront + nearUp + nearLeft) * 500.0f;
    Vector3f sw = (nearFront - nearUp - nearLeft) * 500.0f;
    Vector3f se = (nearFront - nearUp + nearLeft) * 500.0f;
    m_nearPlane.setNormal(getFront());
    m_farPlane.setNormal(-getFront());
    m_leftPlane.setNormal(nw.cross(sw).getNormalize());
    m_rightPlane.setNormal(se.cross(ne).getNormalize());
    m_topPlane.setNormal(ne.cross(nw).getNormalize());
    m_downPlane.setNormal(sw.cross(se).getNormalize());

    m_nearPlane.setPoint(m_eyePos + nearFront);
    m_farPlane.setPoint(m_eyePos + getFront() * m_farZ);
    m_leftPlane.setPoint(m_eyePos);
    m_rightPlane.setPoint(m_eyePos);
    m_topPlane.setPoint(m_eyePos);
    m_downPlane.setPoint(m_eyePos);
  }

  const Sphere& boundSphere = ActorModel->getBoundingSphere();
  // See if in
  if (Math::intersectionSpherePlane(boundSphere, m_nearPlane))
  {
    return true;
  }
  if (Math::intersectionSpherePlane(boundSphere, m_farPlane))
  {
    return true;
  }
  if (Math::intersectionSpherePlane(boundSphere, m_leftPlane))
  {
    return true;
  }
  if (Math::intersectionSpherePlane(boundSphere, m_rightPlane))
  {
    return true;
  }
  if (Math::intersectionSpherePlane(boundSphere, m_topPlane))
  {
    return true;
  }
  if (Math::intersectionSpherePlane(boundSphere, m_downPlane))
  {
    return true;
  }

  Vector3f relativePoint = boundSphere.getCenter()
                         - m_nearPlane.getNormal() * m_nearPlane.d;
  if (relativePoint.dot(m_nearPlane.getNormal()) < 0.0f)
  {
    return false;
  }
  relativePoint = boundSphere.getCenter()
                - m_farPlane.getNormal() * m_farPlane.d;
  if (relativePoint.dot(m_farPlane.getNormal()) < 0.0f)
  {
    return false;
  }
  relativePoint = boundSphere.getCenter()
                - m_leftPlane.getNormal() * m_leftPlane.d;
  if (relativePoint.dot(m_leftPlane.getNormal()) < 0.0f)
  {
    return false;
  }
  relativePoint = boundSphere.getCenter()
                - m_rightPlane.getNormal() * m_rightPlane.d;
  if (relativePoint.dot(m_rightPlane.getNormal()) < 0.0f)
  {
    return false;
  }
  relativePoint = boundSphere.getCenter()
                - m_topPlane.getNormal() * m_topPlane.d;
  if (relativePoint.dot(m_topPlane.getNormal()) < 0.0f)
  {
    return false;
  }
  relativePoint = boundSphere.getCenter()
                - m_downPlane.getNormal() * m_downPlane.d;
  if (relativePoint.dot(m_downPlane.getNormal()) < 0.0f)
  {
    return false;
  }


  return true;
}
}