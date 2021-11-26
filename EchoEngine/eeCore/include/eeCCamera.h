/************************************************************************/
/**
 * @file eeBaseApp.h
 * @author Diego Castellanos
 * @date 19/11/21
 * @brief
 * The Base app for the program. Initializes, destroy, and run all the
 * application.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include "eeComponent.h"
#include "eeVector3.h"
#include "eeVector2.h"
#include "eeQuaternion.h"
#include "eeMatrix4.h"
#include <eePlane.h>

namespace eeEngineSDK{
enum class eCAMERA_PROJECTION_TYPE
{
  NONE = -1,
  ORTHOGRAPHIC,
  PERSPECTIVE,
  COUNT
};

struct CameraDesc
{ 
  //Vector3f eyePos = { 0.0f, 0.0f, 0.0f };
  //Vector3f lookAt = { 0.0f, 0.0f, 0.0f };
  //Vector3f upVector = { 0.0f, 0.0f, 0.0f };

  eCAMERA_PROJECTION_TYPE projectionType = eCAMERA_PROJECTION_TYPE::NONE;
  float fovAngleY = 0.0f;
  Vector2f viewSize = { 0.0f, 0.0f };
  float nearZ = 0.0f;
  float farZ = 0.0f;
};


class EE_CORE_EXPORT CCamera : public Component
{
 public:
  enum { CmpType = eCOMPONENT_TYPE::CAMERA };

  virtual int32
  getType() override
  {
    return CmpType;
  }

  CCamera();
  ~CCamera() = default;

  void
  init(CameraDesc desc);


  void
  update(Actor* actor) override;

  void
  setEyePosition(Vector3f pos);
  Vector3f
  getEyePosition();

  void
  setLookAtPosition(Vector3f pos);
  Vector3f
  getLookAtPosition();

  void
  rotateCamera(Quaternion rot);

  void
  setUpVector(Vector3f pos);
  Vector3f
  getUpVector();
  
  void
  setProjectionType(eCAMERA_PROJECTION_TYPE type);
  eCAMERA_PROJECTION_TYPE
  getProjectionType();

  void
  setFovAngle(float angle);
  float
  getFovAngle();

  void
  setViewSize(Vector2f viewSize);
  Vector2f
  getViewSize();

  void
  setNearPlane(float near);
  float
  getNearPlane();

  void
  setFarPlane(float far);
  float
  getFarPlane();

  Vector3f
  getFront();
  Vector3f
  getRight();
  Vector3f
  getUp();

  Matrix4f
  getViewMatrix();

  Matrix4f
  getProjectionMatrix();


  bool
  isActive();
  void
  setActive(bool active);
  
  bool
  isMain();
  void
  setMain(bool active);

  SPtr<RenderTarget>
  getRenderTarget();
  
  SPtr<DepthStencil>
  getDepthStencil();

  bool
  isModelOnCamera(SPtr<CModel> ActorModel);

 private:
  // Camera info
  Vector3f m_eyePos = {0.0f, 0.0f, 0.0f};
  Vector3f m_lookAt = {0.0f, 0.0f, 0.0f};
  Vector3f m_upVector = {0.0f, 0.0f, 0.0f};

  eCAMERA_PROJECTION_TYPE m_projectionType = eCAMERA_PROJECTION_TYPE::NONE;
  float m_fovAngleY = 0.0f;
  Vector2f m_viewSize = { 0.0f, 0.0f };
  float m_nearZ = 0.0f;
  float m_farZ = 0.0f;


  // Matrices
  Matrix4f m_viewMat = Matrix4f::IDENTITY;
  bool m_dirtyView = false;
  Matrix4f m_projectionMat = Matrix4f::IDENTITY;
  bool m_dirtyProj = false;


  // Render
  bool m_active = true;
  bool m_main = false;

  SPtr<RenderTarget> m_renderTarget;
  SPtr<DepthStencil> m_depthStencil;


  // Frustum
  Plane m_nearPlane;
  Plane m_farPlane;
  Plane m_leftPlane;
  Plane m_rightPlane;
  Plane m_topPlane;
  Plane m_downPlane;
  bool m_dirtyFrustum = true;
};
}
