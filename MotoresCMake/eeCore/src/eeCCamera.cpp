#include "eeCCamera.h"

#include <eeMemoryManager.h>

#include <eeMath.h>

#include "eeCoreConfiguration.h"

#include "eeMatrix3.h"

#include "eeActor.h"
#include "eeCTransform.h"
#include "eeCStaticMesh.h"
#include "eeCSkeletalMesh.h"
#include "eeCBounds.h"
#include "eeTexture.h"

#include "eeGraficsApi.h"

namespace eeEngineSDK {
CCamera::CCamera(CameraDesc desc)
{
  init(desc);
}
void
CCamera::init(CameraDesc desc)
{
  m_utilityCamera.init(desc);
}
void
CCamera::update()
{
  EE_NO_EXIST_RETURN(m_actor);

  SPtr<CTransform> transform = m_actor->getTransform();

  m_utilityCamera.setEyePosition(transform->getPosition());
  m_utilityCamera.setLookAtPosition(transform->getPosition() 
                                  + transform->getRotation().getFrontVector());
}
Vector3f
CCamera::getEyePosition()
{
  return m_utilityCamera.getEyePosition();
}
Vector3f
CCamera::getLookAtPosition()
{
  return m_utilityCamera.getLookAtPosition();
}
Vector3f
CCamera::getUpVector()
{
  return m_utilityCamera.getUpVector();
}
void
CCamera::setProjectionType(CAMERA_PROJECTION_TYPE type)
{
  m_utilityCamera.setProjectionType(type);
}
CAMERA_PROJECTION_TYPE
CCamera::getProjectionType()
{
  return m_utilityCamera.getProjectionType();
}
void
CCamera::setFovAngle(float angle)
{
  m_utilityCamera.setFovAngle(angle);
}
float
CCamera::getFovAngle()
{
  return m_utilityCamera.getFovAngle();
}
void
CCamera::setViewSize(Vector2f viewSize)
{
  m_utilityCamera.setViewSize(viewSize);
}
Vector2f
CCamera::getViewSize()
{
  return m_utilityCamera.getViewSize();
}
void
CCamera::setNearPlane(float nearDistance)
{
  m_utilityCamera.setNearPlane(nearDistance);
}
float
CCamera::getNearPlane()
{
  return m_utilityCamera.getNearPlane();
}
void
CCamera::setFarPlane(float farDistance)
{
  m_utilityCamera.setFarPlane(farDistance);
}
float
CCamera::getFarPlane()
{
  return m_utilityCamera.getFarPlane();
}
Vector3f
CCamera::getFront()
{
  return m_utilityCamera.getFront();
}
Vector3f
CCamera::getRight()
{
  return m_utilityCamera.getRight();
}
Vector3f
CCamera::getUp()
{
  return m_utilityCamera.getUp();
}
Matrix4f
CCamera::getViewMatrix()
{
  return m_utilityCamera.getViewMatrix();
}
Matrix4f
CCamera::getProjectionMatrix()
{
  return m_utilityCamera.getProjectionMatrix();
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
bool
CCamera::isModelOnCamera(SPtr<CBounds> ActorBounds)
{
  if (!ActorBounds) {
    return false;
  }

  if (m_utilityCamera.isSphereOnCamera(ActorBounds->getSphereBound()))
  {
    return m_utilityCamera.isBoxOnCamera(ActorBounds->getBoxBound());
  }

  return false;
}
}