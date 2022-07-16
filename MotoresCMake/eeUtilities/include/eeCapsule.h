/************************************************************************/
/**
 * @file eeCapsule.h
 * @author Diego Castellanos
 * @date 28/09/21
 * @brief The capsule, a cylinder with two semi spheres on it's ends.
 *        Defined by a center, the distance between the top and bottom
 *        and the radious of the semi spheres the is also the radious of
 *        the cylinder.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesUtilities.h"
#include "eeVector3.h"

namespace eeEngineSDK {
/**
 * @brief
 * The capsule, a cylinder with two semi spheres on it's ends.
 * Defined by a center, the distance between the top and bottom
 * and the radious of the semi spheres the is also the radious of
 * the cylinder.
 */
class EE_UTILITY_EXPORT Capsule
{
 public:
  /**
   * @brief
   * Default constructor.
   *
   * @description
   * Makes the capsule the simples capsule, with center in ZERO,
   * height of 2 and radious of 0.5f (diameter of 1).
   */
  Capsule();
  /**
   * @brief
   * Custom constructor.
   *
   * @description
   * Initializes the capsule with a given center, height and radious.
   *
   * @param center
   * The center of the capsule.
   * @param height
   * The distance between the highest and the lowest points.
   * @param radious
   * The radious of the semi-spheres on the top and bottom, and also of the
   * cylinder body.
   */
  Capsule(const Vector3f& center, const float height, const float radious);
  /**
   * @brief
   * Destructor.
   *
   * @description
   * Frees any memory that could have been allocated.
   */
  ~Capsule();

  /**
   * @brief
   * Moves the sphere.
   *
   * @description
   * Changes the center's position translating it the
   * given space.
   *
   * @param movement
   * The direction and magnitude of where it's gonna move.
   */
  FORCEINLINE void
  move(const Vector3f& movement)
  {
    m_center += movement;
  }

  /**
   * @brief
   * Getter of the center of the capsule.
   *
   * @description
   * Returns the center that defines the capsule.
   *
   * @return
   * The center that defines the capsule.
   */
  FORCEINLINE Vector3f
  getCenter() const
  {
    return m_center;
  }
  /**
   * @brief
   * Setter of the center of the capsule.
   *
   * @description
   * Changes the center defining the capsule to the new
   * given point.
   *
   * @param A
   * The new center for the capsule.
   */
  FORCEINLINE void
  setCenter(const Vector3f& center)
  {
    m_center = center;
  }
  /**
   * @brief
   * Getter of the height of the capsule.
   *
   * @description
   * Returns the distance between the highest and
   * lowest point of the capsule.
   *
   * @return
   * The distance between the highest and lowest point
   * of the capsule.
   */
  FORCEINLINE float
  getHeight() const
  {
    return m_height;
  }
  /**
   * @brief
   * Setter of the height of the capsule.
   *
   * @description
   * Changes the distance between the highest and 
   * lowest point of the capsule to the new given height.
   *
   * @param A
   * The new height for the capsule.
   */
  FORCEINLINE void
  setHeight(const float height)
  {
    m_height = height;
  }
  /**
   * @brief
   * Getter of the radious of the capsule.
   *
   * @description
   * Returns the radious of the semi-spheres on the top 
   * and bottom, and also of the cylinder body.
   *
   * @return
   * The radious of the semi-spheres on the top and bottom, 
   * and also of the cylinder body.
   */
  FORCEINLINE float
  getRadious() const
  {
    return m_radious;
  }
  /**
   * @brief
   * Setter of the radious of the capsule.
   *
   * @description
   * Changes the radious of the semi-spheres on the top 
   * and bottom, and also of the cylinder body to the new
   * given radious.
   *
   * @param A
   * The new height for the capsule.
   */
  FORCEINLINE void
  setRadious(const float radious)
  {
    m_radious = radious;
  }

  /**
   * @brief
   * Checks intersection capsule-point.
   *
   * @description
   * Returns true if the point is in the capsule.
   *
   * @param point
   * The point to check if it's in the capsule.
   *
   * @return
   * Whether it's intersecting or not.
   */
  bool
  intersects(const Vector3f& point) const;
  /**
   * @brief
   * Checks intersection capsule-plane.
   *
   * @description
   * Returns true if the plane intersects the capsule.
   *
   * @param plane
   * The plane to check if it's touching the capsule.
   *
   * @return
   * Whether it's intersecting or not.
   */
  bool
  intersects(const Plane& plane) const;
  /**
   * @brief
   * Checks intersection capsule-sphere.
   *
   * @description
   * Returns true if the sphere intersects the capsule.
   *
   * @param sphere
   * The sphere to check if it's touching the capsule.
   *
   * @return
   * Whether it's intersecting or not.
   */
  bool
  intersects(const Sphere& sphere);
  /**
   * @brief
   * Checks intersection capsule-box.
   *
   * @description
   * Returns true if the box intersects the capsule.
   *
   * @param box
   * The box to check if it's touching the capsule.
   *
   * @return
   * Whether it's intersecting or not.
   */
  //bool
  //intersects(const BoxAAB& box);
  /**
   * @brief
   * Checks intersection capsule-capsule.
   *
   * @description
   * Returns true if the first capsule intersects the second.
   *
   * @param capsule
   * The second capsule to check if it's touching the first.
   *
   * @return
   * Whether it's intersecting or not.
   */
  bool
  intersects(const Capsule& capsule);

  /**
   * @brief
   * The simpler capsule, with center in ZERO,
   * height of 2 and radious of 0.5f (diameter of 1).
   */
  static const Capsule kSIMPLEX; 

 private:
  /**
   * @brief
   * The center of the capsule.
   */
  Vector3f m_center;
  /**
   * @brief
   * The distance between the highest
   * and the lowest points.
   */
  float m_height;
  /**
   * @brief
   * The radious of the semi-spheres on
   * the top and bottom, and also of the
   * cylinder body.
   */
  float m_radious;
};
}
