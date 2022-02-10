#include "eeCCamera.h"

#include <eeMemoryManager.h>

#include <eeMath.h>

#include "eeMatrix3.h"

#include "eeActor.h"
#include "eeCTransform.h"
#include "eeCModel.h"
#include "eeCSkeletalMesh.h"
#include "eeCBounds.h"

#include "eeGraficsApi.h"

namespace eeEngineSDK {
CCamera::CCamera()
{
  m_upVector = Vector3f::kUP;
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

  if (m_active) {
    GraphicsApi::instance().addActiveCamera(
         MemoryManager::instance().reinterpretPtr<CCamera>(shared_from_this()));
  }
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
  if (m_dirtyView) {
    m_dirtyView = false;

    m_viewMat = Matrix4f::viewMatrix(m_eyePos, m_lookAt, m_upVector);
  }
  return m_viewMat;
}
Matrix4f
CCamera::getProjectionMatrix()
{
  if (m_dirtyProj) {
    m_dirtyProj = false;
    
    switch (m_projectionType) {
    case eeEngineSDK::eCAMERA_PROJECTION_TYPE::kNone:
      m_projectionMat = Matrix4f::kIDENTITY;
      break;
    case eeEngineSDK::eCAMERA_PROJECTION_TYPE::kOrthographic:
      m_projectionMat = Matrix4f::orthograficMatrixMatrix(m_viewSize.x,
                                                          m_viewSize.y,
                                                          m_nearZ,
                                                          m_farZ);
      break;
    case eeEngineSDK::eCAMERA_PROJECTION_TYPE::kPerspective:
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
CCamera::isModelOnCamera(SPtr<CBounds> ActorBounds)
{
  if (!ActorBounds) {
    return false;
  }

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

  auto& memoryMan = MemoryManager::instance();

  if (m_viewFrustum.isSphereInside(ActorBounds->getSphereBound()))
  {
    return true; // m_viewFrustum.isSphereInside(boundBox);
  }

  return false;
}
}