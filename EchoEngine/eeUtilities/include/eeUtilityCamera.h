/************************************************************************/
/**
 * @file eeUtilityCamera.h
 * @author Diego Castellanos
 * @date 15/02/22
 * @brief The math part of a camera, with shapes, matrices, and functionality.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesUtilities.h"
#include "eeVector2.h"
#include "eeVector3.h"
#include "eeMatrix4.h"
#include "eeFrustum.h"

namespace eeEngineSDK {
/**
 * @brief
 * Enum for camera projection mode.
 */
enum class CAMERA_PROJECTION_TYPE
{
  kNone = -1,
  kOrthographic,
  kPerspective,
  kCount
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
  CAMERA_PROJECTION_TYPE projectionType = CAMERA_PROJECTION_TYPE::kNone;
  /**
   * The halve field of view angle in Y direction.
   */
  float fovAngleY = 0.0f;
  /**
   * The screen size.
   */
  Vector2f viewSize = Vector2f{ 0.0f, 0.0f };
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
 * @brief
 * The math part of a camera, with shapes, matrices, and functionality.
 */
class EE_UTILITY_EXPORT UtilityCamera
{
 public: 
  /**
   * @brief
   * Default constructor.
   */
  UtilityCamera() = default;
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
  UtilityCamera(CameraDesc desc);
  /**
   * @brief
   * Default destructor.
   */
  ~UtilityCamera() = default;

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
   * Setter for the camera position
   *
   * @description
   * Sets the camera eye position.
   *
   * @param eyePos
   * The camera new eye position.
   */
  void
  setEyePosition(Vector3f eyePos);

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
   * Setter for the camera look at position
   *
   * @description
   * Sets the camera look at position.
   *
   * @param lookAtPos
   * The camera new look at position.
   */
  void
  setLookAtPosition(Vector3f lookAtPos);


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
   * Updates the frustum if it needs to.
   *
   * @description
   * Checks if the frustum needs to be updated and if it does updates it with
   * the values of the camera.
   */
  void
  updateFrustrum();

  /**
   * @brief
   * See if the sphere is on the camera frustum.
   *
   * @description
   * Returns if the sphere is inside the frustum of the camera, checking its 
   * bounds.
   *
   * @param sphereBound
   * The sphere to check if its on the camera.
   *
   * @return
   * True if the sphere is intersecting or inside the frustum.
   */
  bool
  isSphereOnCamera(const Sphere& sphereBound);

  /**
   * @brief
   * See if the box is on the camera frustum.
   *
   * @description
   * Returns if the box is inside the frustum of the camera, checking its 
   * bounds.
   *
   * @param boxBound
   * The box to check if its on the camera.
   *
   * @return
   * True if the box is intersecting or inside the frustum.
   */
  bool
  isBoxOnCamera(const BoxAAB& boxBound);

 private:
  // Camera info
  /**
   * The position of the camera.
   */
  Vector3f m_eyePos = Vector3f{0.0f, 0.0f, 0.0f};
  /**
   * The look at position of the camera, for calculating rotation.
   */
  Vector3f m_lookAt = Vector3f{0.0f, 0.0f, 0.0f};
  /**
   * The up vector of the camera, generally the up world vector.
   */
  Vector3f m_upVector = Vector3f::kUP;

  /**
   * The projection type for the projection matrix.
   */
  CAMERA_PROJECTION_TYPE m_projectionType = CAMERA_PROJECTION_TYPE::kNone;
  /**
   * The halve FOV Y angle.
   */
  float m_fovAngleY = 0.0f;
  /**
   * The screen size.
   */
  Vector2f m_viewSize = Vector2f{ 0.0f, 0.0f };
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
  Matrix4f m_viewMat = Matrix4f::kIDENTITY;
  /**
   * The dirty flag for the view matrix.
   */
  bool m_dirtyView = false;
  /**
   * The projection matrix stored, for not to calculate it each frame.
   */
  Matrix4f m_projectionMat = Matrix4f::kIDENTITY;
  /**
   * The dirty flag for the projection matrix.
   */
  bool m_dirtyProj = false;

  /**
   * The frustum for the camera view.
   */
  Frustum m_viewFrustum;
  /**
   * The dirty flag for the frustum calculation.
   */
  bool m_dirtyFrustum = true;
};
}
