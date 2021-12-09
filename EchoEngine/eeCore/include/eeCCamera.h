/************************************************************************/
/**
 * @file eeCCamera.h
 * @author Diego Castellanos
 * @date 19/11/21
 * @brief
 * The Camera component.
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
/**
* @brief
* Enum for camera projection mode.
*/
enum class eCAMERA_PROJECTION_TYPE
{
  NONE = -1,
  ORTHOGRAPHIC,
  PERSPECTIVE,
  COUNT
};

/**
* @brief
* A descriptor for the camera mode.
*/
struct CameraDesc
{
  /**
  * The camera projection mode.
  */
  eCAMERA_PROJECTION_TYPE projectionType = eCAMERA_PROJECTION_TYPE::NONE;
  /**
  * The halve field of view angle in Y direction.
  */
  float fovAngleY = 0.0f;
  /**
  * The screen size.
  */
  Vector2f viewSize = { 0.0f, 0.0f };
  /**
  * The distance to near plane.
  */
  float nearZ = 0.0f;
  /**
  * The distance to far plane.
  */
  float farZ = 0.0f;
};


/**
* The Camera component.
*/
class EE_CORE_EXPORT CCamera : public Component
{
 public:
  /**
  * @brief
  * The enum for identifying the component type.
  */
  enum { CmpType = eCOMPONENT_TYPE::CAMERA };

  /**
  * @brief
  * Returns the component type.
  *
  * @description
  * Returns the component type.
  *
  * @return
  * The component type.
  */
  virtual int32
  getType() override
  {
    return CmpType;
  }

  /**
  * @brief
  * Default constructor.
  */
  CCamera();
  /**
  * @brief
  * Default destructor.
  */
  ~CCamera() = default;

  /**
  * @brief
  * Initialize the camera.
  *
  * @description
  * Initialize the camera using a descriptor that contains the info required to
  * create the camera and its matrices.
  *
  * @param desc
  * The descriptor of the camera.
  */
  void
  init(CameraDesc desc);

  /**
  * @brief
  * Updates the camera logic.
  *
  * @description
  * Updates the position and rotation of the camera to match the actor to whom
  * it is attached.
  */
  void
  update() override;

  /**
  * @brief
  * Getter for the camera position
  *
  * @description
  * Returns the camera position, that matches its actor.
  *
  * @return
  * The camera eye position.
  */
  Vector3f
  getEyePosition();

  /**
  * @brief
  * Getter for the look at position.
  *
  * @description
  * Returns the look at position, that matches its actor position and rotation.
  * 
  * @return
  * The look at position.
  */
  Vector3f
  getLookAtPosition();


  /**
  * @brief
  * Getter for the up vector.
  *
  * @description
  * Returns the up vector of the camera, this is always the world up vector.
  *
  * @return
  * The world up vector.
  */
  Vector3f
  getUpVector();

  /**
  * @brief
  * Setter for the projection type.
  *
  * @description
  * Sets the new projection matrix type, orthographic or perspective.
  *
  * @param type
  * The enum for the projection type.
  */
  void
  setProjectionType(eCAMERA_PROJECTION_TYPE type);
  /**
  * @brief
  * Getter for the projection type.
  *
  * @description
  * Returns the projection matrix type of the camera.
  *
  * @return
  * The projection matrix type.
  */
  eCAMERA_PROJECTION_TYPE
  getProjectionType();

  /**
  * @brief
  * Setter for the FOV angle.
  *
  * @description
  * Sets the new field of view angle in Y.
  *
  * @param angle
  * Halve the FOV angle in Y.
  */
  void
  setFovAngle(float angle);
  /**
  * @brief
  * Getter for the FOV angle.
  *
  * @description
  * Returns the halve FOV angle in Y.
  *
  * @return
  * The FOV angle halved.
  */
  float
  getFovAngle();

  /**
  * @brief
  * Setter for the view size.
  *
  * @description
  * Sets the screen position for the projection matrix.
  *
  * @param viewSize
  * The new screen size.
  */
  void
  setViewSize(Vector2f viewSize);
  /**
  * @brief
  * Getter for the view size.
  *
  * @description
  * Returns the screen size of the camera.
  *
  * @return
  * The screen size.
  */
  Vector2f
  getViewSize();

  /**
  * @brief
  * Setter for the near distance plane.
  *
  * @description
  * Sets the new near distance plane for the camera
  *
  * @param near
  * The new near distance.
  */
  void
  setNearPlane(float near);
  /**
  * @brief
  * Getter for the near distance plane.
  *
  * @description
  * Returns the distance to the near plane of the frustum camera.
  *
  * @return
  * The distance to the near plane.
  */
  float
  getNearPlane();

  /**
  * @brief
  * Setter for the far distance plane.
  *
  * @description
  * Sets the new far distance plane for the camera
  *
  * @param far
  * The new far distance.
  */
  void
  setFarPlane(float far);
  /**
  * @brief
  * Getter for the far distance plane.
  *
  * @description
  * Returns the distance to the far plane of the frustum camera.
  *
  * @return
  * The distance to the far plane.
  */
  float
  getFarPlane();

  /**
  * @brief
  * Getter for the front vector of the camera.
  *
  * @description
  * Returns a unit vector on the front direction of the camera.
  *
  * @return
  * A unit vector on the front direction of the camera.
  */
  Vector3f
  getFront();
  /**
  * @brief
  * Getter for the right vector of the camera.
  *
  * @description
  * Returns a unit vector on the right direction of the camera.
  *
  * @return
  * A unit vector on the right direction of the camera.
  */
  Vector3f
  getRight();
  /**
  * @brief
  * Getter for the up vector of the camera.
  *
  * @description
  * Returns a unit vector on the up direction of the camera.
  *
  * @return
  * A unit vector on the up direction of the camera.
  */
  Vector3f
  getUp();

  /**
  * @brief
  * Getter for the view matrix.
  *
  * @description
  * Returns a view matrix with the data of the camera.
  *
  * @return
  * A view matrix.
  */
  Matrix4f
  getViewMatrix();

  /**
  * @brief
  * Getter for the projection matrix.
  *
  * @description
  * Returns a projection matrix with the data of the camera.
  *
  * @return
  * A projection matrix.
  */
  Matrix4f
  getProjectionMatrix();


  /**
  * @brief
  * Get if the camera is active.
  *
  * @description
  * Return if the camera is active or not.
  *
  * @return
  * True if the camera is active.
  */
  bool
  isActive();
  /**
  * @brief
  * Set the camera active.
  *
  * @description
  * Sets if the camera es active or not.
  *
  * @param active
  * The new active value for the camera.
  */
  void
  setActive(bool active);

  /**
  * @brief
  * Get if the camera is main.
  *
  * @description
  * Return if the camera is the main or not.
  *
  * @return
  * True if the camera is main.
  */
  bool
  isMain();
  /**
  * @brief
  * Get if the camera is main.
  *
  * @description
  * Gets if the camera es the main camera or not.
  *
  * @param active
  * The new is main value for the camera.
  */
  void
  setMain(bool active);

  /**
  * @brief
  * Getter for the render target.
  *
  * @description
  * Return the render target of the camera, to where all is rendered.
  *
  * @return
  * The render target of the camera with all its view.
  */
  SPtr<RenderTarget>
  getRenderTarget();

  /**
  * @brief
  * Getter for the depth stencil.
  *
  * @description
  * Return the depth stencil of the camera.
  *
  * @return
  * The depth stencil of the camera.
  */
  SPtr<DepthStencil>
  getDepthStencil();

  /**
  * @brief
  * See if the model is on the camera.
  *
  * @description
  * Returns if the model is inside the frustum of the camera, checking its 
  * bounds.
  *
  * @param ActorModel
  * The model to check if its on the camera.
  *
  * @return
  * True if the bounds are intersecting or inside the frustum.
  */
  bool
  isModelOnCamera(SPtr<CModel> ActorModel);

 private:
  // Camera info
  /**
  * The position of the camera.
  */
  Vector3f m_eyePos = {0.0f, 0.0f, 0.0f};
  /**
  * The look at position of the camera, for calculating rotation.
  */
  Vector3f m_lookAt = {0.0f, 0.0f, 0.0f};
  /**
  * The up vector of the camera, generally the up world vector.
  */
  Vector3f m_upVector = {0.0f, 0.0f, 0.0f};

  /**
  * The projection type for the projection matrix.
  */
  eCAMERA_PROJECTION_TYPE m_projectionType = eCAMERA_PROJECTION_TYPE::NONE;
  /**
  * The halve FOV Y angle.
  */
  float m_fovAngleY = 0.0f;
  /**
  * The screen size.
  */
  Vector2f m_viewSize = { 0.0f, 0.0f };
  /**
  * The distance to the near plane.
  */
  float m_nearZ = 0.0f;
  /**
  * The distance to the far plane.
  */
  float m_farZ = 0.0f;


  // Matrices
  /**
  * The view matrix stored, for not to calculate it each frame.
  */
  Matrix4f m_viewMat = Matrix4f::IDENTITY;
  /**
  * The dirty flag for the view matrix.
  */
  bool m_dirtyView = false;
  /**
  * The projection matrix stored, for not to calculate it each frame.
  */
  Matrix4f m_projectionMat = Matrix4f::IDENTITY;
  /**
  * The dirty flag for the projection matrix.
  */
  bool m_dirtyProj = false;


  // Render
  /**
  * If the camera is active.
  */
  bool m_active = true;
  /**
  * If the camera is rendering on the main view.
  */
  bool m_main = false;

  /**
  * The render target to where all is rendered.
  */
  SPtr<RenderTarget> m_renderTarget;
  /**
  * The depth stencil view for the depth stencil.
  */
  SPtr<DepthStencil> m_depthStencil;


  // Frustum
  /**
  * The near plane for the frustum.
  */
  Plane m_nearPlane;
  /**
  * The far plane for the frustum.
  */
  Plane m_farPlane;
  /**
  * The left plane for the frustum.
  */
  Plane m_leftPlane;
  /**
  * The right plane for the frustum.
  */
  Plane m_rightPlane;
  /**
  * The top plane for the frustum.
  */
  Plane m_topPlane;
  /**
  * The down plane for the frustum.
  */
  Plane m_downPlane;
  /**
  * The dirty flag for the frustum calculation.
  */
  bool m_dirtyFrustum = true;
};
}
