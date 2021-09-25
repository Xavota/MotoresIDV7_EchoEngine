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

class Plane;

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
  Sphere() = default;
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
  * Checks intersection plane-point.
  *
  * @description
  * Returns true if the point is on the plane.
  *
  * @param point
  * The point to check if it's on the plane.
  *
  * @return
  * Whether it's intersacting or not.
  */
  //bool
  //intersects(const Vector3f& point) const;
  /**
  * @brief
  * Checks intersection plane-sphere.
  *
  * @description
  * Returns true if the sphere intersects the plane.
  *
  * @param sphere
  * The sphere to check if it's touching the plane.
  *
  * @return
  * Whether it's intersacting or not.
  */
  //bool
  //intersects(const Plane& plane) const;


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
