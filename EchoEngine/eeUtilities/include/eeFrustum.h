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
class EE_UTILITY_EXPORT Frustum
{
 public:
  Frustum() = default;
  ~Frustum() = default;

 void
 UpdateFrustum(const Vector3f& position,
               const Vector3f& frontVec,
               const Vector3f& upVec,
               const Vector3f& rightVec,
               float nearDistance,
               float farDistance,
               float fovAngle,
               float aspectRatio);

  bool
  isSphereInside(const Sphere& sphere);
  bool
  isBoxInside(const BoxAAB& sphere);

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
