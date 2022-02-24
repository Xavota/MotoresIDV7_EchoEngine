/************************************************************************/
/**
 * @file eeFrustum.h
 * @author Diego Castellanos
 * @date 09/02/22
 * @brief Holds 6 planes in a truncate pyramid to calculate things inside.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesUtilities.h"
#include "eeVector3.h"
#include "eePlane.h"
#include "eeSphere.h"
#include "eeBox.h"

namespace eeEngineSDK {
/**
 * @brief
 * Holds 6 planes in a truncate pyramid to calculate things inside.
 */
class EE_UTILITY_EXPORT Frustum
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  Frustum() = default;
  /**
   * @brief
   * Sets the planes of the frustum.
   *
   * @description
   * Uses values to update the planes of the frustum.
   *
   * @param position
   * The position of the frustum.
   * @param frontVec
   * The direction of the frustum.
   * @param upVec
   * The up direction of the frustum.
   * @param rightVec
   * The right direction of the frustum.
   * @param nearDistance
   * The distance to the near plane from the position.
   * @param farDistance
   * The distance to the far plane from the position.
   * @param fovAngle
   * The angle in the Y axis of aperture of the up and down planes.
   * @param aspectRatio
   * The ration between the width and height of the frustum.
   */
  Frustum(const Vector3f& position,
          const Vector3f& frontVec,
          const Vector3f& upVec,
          const Vector3f& rightVec,
          float nearDistance,
          float farDistance,
          float fovAngle,
          float aspectRatio);
  /**
   * @brief
   * Default destructor.
   */
  ~Frustum() = default;
  
  /**
   * @brief
   * Sets the planes of the frustum.
   *
   * @description
   * Uses values to update the planes of the frustum.
   *
   * @param position
   * The position of the frustum.
   * @param frontVec
   * The direction of the frustum.
   * @param upVec
   * The up direction of the frustum.
   * @param rightVec
   * The right direction of the frustum.
   * @param nearDistance
   * The distance to the near plane from the position.
   * @param farDistance
   * The distance to the far plane from the position.
   * @param fovAngle
   * The angle in the Y axis of aperture of the up and down planes.
   * @param aspectRatio
   * The ration between the width and height of the frustum.
   */
  void
  UpdateFrustum(const Vector3f& position,
                const Vector3f& frontVec,
                const Vector3f& upVec,
                const Vector3f& rightVec,
                float nearDistance,
                float farDistance,
                float fovAngle,
                float aspectRatio);

  /**
   * @brief
   * Checks if the sphere is in the frustum.
   *
   * @description
   * Checks if the sphere is inside or touching the frustum.
   *
   * @param sphere
   * The sphere to check.
   *
   * @return
   * If the sphere is inside or touching the frustum.
   */
  bool
  isSphereInside(const Sphere& sphere);
  /**
   * @brief
   * Checks if the box is in the frustum.
   *
   * @description
   * Checks if the box is inside or touching the frustum.
   *
   * @param box
   * The box to check.
   *
   * @return
   * If the box is inside or touching the frustum.
   */
  bool
  isBoxInside(const BoxAAB& box);

 private:
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
};
}
