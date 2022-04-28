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

#include <eeUtilityCamera.h>

#include <eeFrustum.h>

#include <eeVector3.h>
#include <eeVector2.h>
#include <eeQuaternion.h>
#include <eeMatrix4.h>

namespace eeEngineSDK{
/**
 * @brief
 * The Camera component.
 */
class EE_CORE_EXPORT CCamera : public Component
{
 public:
  /**
   * @brief
   * The enum for identifying the component type.
   */
  enum { CmpType = eCOMPONENT_TYPE::kCamera };

  /**
   * @brief
   * Default constructor.
   */
  CCamera() = default;
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
  CCamera(CameraDesc desc);
  /**
   * @brief
   * Default destructor.
   */
  ~CCamera() = default;

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
  int32
  getType() override
  {
    return CmpType;
  }

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
  setProjectionType(CAMERA_PROJECTION_TYPE type);
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
  CAMERA_PROJECTION_TYPE
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
  isModelOnCamera(SPtr<CBounds> ActorModel);

 private:
  /**
   * The position of the camera.
   */
  UtilityCamera m_utilityCamera;

  /**
   * If the camera is rendering on the main view.
   */
  bool m_main = false;
};
}
