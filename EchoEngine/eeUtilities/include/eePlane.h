#pragma once
#include "eePrerequisitesUtilities.h"
#include "eeVector3.h"


namespace eeEngineSDK {
  /**
  * @brief
  * A plane. Build by a point and a normal vector.
  * It's a two dimensional surface that extends infinitely.
  */
class Plane
{
 public:
   /**
   * @brief
   * Default constructor.
   *
   * @description
   * Makes the plane equal to de XY axis plane
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
  void move(const Vector3f& movement);
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
  void rotate(const Vector3f& rotation);

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
  FORCEINLINE const Vector3f& getPoint() const 
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
  FORCEINLINE void setPoint(const Vector3f& point)
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
  FORCEINLINE const Vector3f& getNormal() const
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
  FORCEINLINE void setNormal(const Vector3f& normal)
  {
    m_normal = normal.getNormalize();
  }

 private:
  Vector3f m_point;
  Vector3f m_normal;
};
}
