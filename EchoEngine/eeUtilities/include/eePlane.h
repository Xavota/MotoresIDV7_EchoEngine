/************************************************************************/
/**
 * @file eePlane.h
 * @author Diego Castellanos
 * @date 21/09/21
 * @brief A plane. Build by a point and a normal vector.
 *        It's a two dimensional surface that extends infinitely.
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
* A plane. Build by a point and a normal vector.
* It's a two dimensional surface that extends infinitely.
*/
class EE_UTILITY_EXPORT Plane : public Vector3f
{
 public:
  /**
  * @brief
  * Default constructor.
  *
  * @description
  * Makes the plane equal to the XY axis plane
  */
  Plane();
  /**
  * @brief
  * Custom constructor.
  *
  * @description
  * Initializes the plane with a given point and normal.
  *
  * @param point
  * The place in 3D space where the plane it's gonna pass.
  * @param normal
  * The normal vector to wich is gonna be facing.
  */
  Plane(const Vector3f& point, const Vector3f& normal);
  /**
  * @brief
  * Custom constructor.
  *
  * @description
  * Initializes the plane given 3 points in the space 
  * that are on the plane.
  *
  * @param pA
  * First point, it's gonna be the point of the plane.
  * @param pB
  * Second point. Defines a line between A and it.
  * @param pC
  * Third point. Defines a line between A and it.
  */
  Plane(const Vector3f& pA, const Vector3f& pB, const Vector3f& pC);
  /**
  * @brief
  * Destructor.
  *
  * @description
  * Frees any memory that could have been allocated.
  */
  ~Plane();

  /**
  * @brief
  * Moves the plane.
  *
  * @description
  * Changes the point's position translating it the
  * given space.
  *
  * @param movement
  * The direction and magnitud of where it's gonna move.
  */
  void
  move(const Vector3f& movement);
  /**
  * @brief
  * Rotates the plane.
  *
  * @description
  * Changes the normal direction rotating it the
  * given angles.
  *
  * @param rotation
  * The angles, in radians, indicating how is gonna rotate
  * in the 3 axis.
  */
  void
  rotate(const Vector3f& rotation);

  /**
  * @brief
  * Getter of the point of the plane.
  *
  * @description
  * Returns the point that defines the plane.
  *
  * @return
  * The point that defines the plane.
  */
  FORCEINLINE const Vector3f& 
  getPoint() const 
  {
    return m_point;
  }
  /**
  * @brief
  * Setter of the point of the plane.
  *
  * @description
  * Changes the point defining the plane to the new given point.
  * 
  * @param point
  * The new point for the plane.
  */
  FORCEINLINE void 
  setPoint(const Vector3f& point)
  {
    m_point = point;
  }
  /**
  * @brief
  * Getter of the normal of the plane.
  *
  * @description
  * Returns the normal vector that defines the plane.
  *
  * @return
  * The normal vector that defines the plane.
  */
  FORCEINLINE const Vector3f& 
  getNormal() const
  {
    return m_normal;
  }
  /**
  * @brief
  * Setter of the normal vector of the plane.
  *
  * @description
  * Changes the normal vector defining the plane to 
  * the new given normal.
  *
  * @param normal
  * The new normal vector for the plane.
  */
  FORCEINLINE void 
  setNormal(const Vector3f& normal)
  {
    m_normal = normal.getNormalize();
  }


  /**
  * @brief
  * Checks intersection plane-point.
  *
  * @description
  * Returns true if the point os in the plane.
  *
  * @param point
  * The point to check if it's on the plane.
  *
  * @return
  * Whether it's intersecting or not.
  */
  bool
  intersects(const Vector3f& point);
  /**
  * @brief
  * Checks intersection plane-plane.
  *
  * @description
  * Returns true if the first plane intersects the second.
  *
  * @param plane
  * The second plane to check if it's touching the firts.
  *
  * @return
  * Whether it's intersecting or not.
  */
  bool
  intersects(const Plane& plane);
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
  * Whether it's intersecting or not.
  */
  bool
  intersects(const Sphere& sphere);
  /**
  * @brief
  * Checks intersection plane-box.
  *
  * @description
  * Returns true if the box intersects the plane.
  *
  * @param box
  * The box to check if it's touching the plane.
  *
  * @return
  * Whether it's intersecting or not.
  */
  bool
  intersects(const BoxAAB& box);
  /**
  * @brief
  * Checks intersection plane-capsule.
  *
  * @description
  * Returns true if the capsule intersects the plane.
  *
  * @param capsule
  * The capsule to check if it's touching the plane.
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
  static const Plane XY;
  /**
  * @brief
  * A plane oriented to the XZ plane.
  */
  static const Plane XZ;
  /**
  * @brief
  * A plane oriented to the YZ plane.
  */
  static const Plane YZ;

 private:
   /**
   * @brief
   * A point that's on the plane, indicates where the plane is.
   */
  Vector3f m_point;
  /**
  * @brief
  * The normal vector to which is gonna be facing.
  */
  Vector3f m_normal;
};
}
