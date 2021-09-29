/************************************************************************/
/**
 * @file eeSphere.h
 * @author Diego Castellanos
 * @date 24/09/21
 * @brief The sphere, defined by all the points that surrounds a point by 
 *        the exact same distance.
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
* The sphere, defined by all the points that surrounds a point by 
* the exact same distance.
*/
class EE_UTILITY_EXPORT Sphere
{
 public:
  /**
  * @brief
  * Default constructor.
  *
  * @description
  */
  Sphere();
  /**
  * @brief
  * Custom constructor.
  *
  * @description
  * Initializes teh sphere starting in the given center
  * and with the given radious.
  *
  * @param center
  * The point from where the sphere starts.
  * @param radious
  * The distance of all the points surrounding the center.
  */
  Sphere(Vector3f center, float radious);
  /**
  * @brief
  * Destructor.
  *
  * @description
  * Frees any memory allocated.
  */
  ~Sphere();

  /**
  * @brief
  * Moves the sphere.
  *
  * @description
  * Changes the center's position translating it the
  * given space.
  *
  * @param movement
  * The direction and magnitud of where it's gonna move.
  */
  FORCEINLINE void
  move(const Vector3f& movement)
  {
    m_center += movement;
  }

  /**
  * @brief
  * The getter of the center of the sphere.
  *
  * @description
  * Returns the position of the center of the sphere.
  *
  * @return
  * The position of the current center of the sphere.
  */
  FORCEINLINE Vector3f
  getCenter() const
  {
    return m_center;
  }
  /**
  * @brief
  * The setter of the center of the sphere.
  *
  * @description
  * Sets the center of the sphere to it's given new position.
  *
  * @param center
  * The new center of the sphere.
  */
  FORCEINLINE void
  setCenter(const Vector3f& center)
  {
    m_center = center;
  }
  /**
  * @brief
  * The getter of the radious of the sphere.
  *
  * @description
  * Returns the distance of all the points surrounding the center
  * of the sphere.
  *
  * @return
  * The current radious of the sphere.
  */
  FORCEINLINE float
  getRadious() const
  {
    return m_radious;
  }
  /**
  * @brief
  * The setter of the radious of the sphere.
  *
  * @description
  * Sets the radious of the sphere to it's given new radious.
  *
  * @param radious
  * The new radious of the sphere.
  */
  FORCEINLINE void
  setRadious(float radious)
  {
    m_radious = radious;
  }


  /**
  * @brief
  * Checks intersection sphere-point.
  *
  * @description
  * Returns true if the point is in the sphere.
  *
  * @param point
  * The point to check if it's in the sphere.
  *
  * @return
  * Whether it's intersacting or not.
  */
  bool
  intersects(const Vector3f& point) const;
  /**
  * @brief
  * Checks intersection sphere-plane.
  *
  * @description
  * Returns true if the plane intersects the sphere.
  *
  * @param plane
  * The plane to check if it's touching the sphere.
  *
  * @return
  * Whether it's intersacting or not.
  */
  bool
  intersects(const Plane& plane) const;
  /**
  * @brief
  * Checks intersection sphere-sphere.
  *
  * @description
  * Returns true if the firts sphere intersects the second.
  *
  * @param sphere
  * The second sphere to check if it's touching the first.
  *
  * @return
  * Whether it's intersecting or not.
  */
  bool
  intersects(const Sphere& sphere);
  /**
  * @brief
  * Checks intersection sphere-box.
  *
  * @description
  * Returns true if the box intersects the sphere.
  *
  * @param box
  * The box to check if it's touching the sphere.
  *
  * @return
  * Whether it's intersecting or not.
  */
  bool
  intersects(const BoxAAB& box);
  /**
  * @brief
  * Checks intersection sphere-capsule.
  *
  * @description
  * Returns true if the capsule intersects the sphere.
  *
  * @param capsule
  * The capsule to check if it's touching the sphere.
  *
  * @return
  * Whether it's intersecting or not.
  */
  bool
  intersects(const Capsule& capsule);


  /**
  * @brief
  * A plane oriented to the XY plane.
  */
  static const Sphere UNITARY;

 private:
   /**
   * @brief
   * The center of the sphere.
   */
  Vector3f m_center;
  /**
  * @brief
  * The max distance reached by the sphere.
  */
  float m_radious;
};
}
