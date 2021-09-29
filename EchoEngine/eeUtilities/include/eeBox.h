/************************************************************************/
/**
 * @file eeBox.h
 * @author Diego Castellanos
 * @date 25/09/21
 * @brief This file defines all types of boxes, not oriented, oriented,
          as well as all its functions.
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
* The simplest box. Not oriented. Defined by 2 points.
*/
class EE_UTILITY_EXPORT BoxAAB
{
 public:
   /**
   * @brief
   * Default constructor.
   *
   * @description
   * Makes the box the simplest box.
   */
  BoxAAB();
  /**
  * @brief
  * Custom constructor.
  *
  * @description
  * Initializes the box with a given left-up-front most point and size.
  *
  * @param A
  * The left-up-front most point of the box.
  * @param size
  * The size in the three dimensions of the box.
  */
  BoxAAB(const Vector3f A, const Vector3f size);
  /**
  * @brief
  * Destructor.
  *
  * @description
  * Frees any memory that could have been allocated.
  */
  ~BoxAAB() = default;


  /**
  * @brief
  * Moves the Box.
  *
  * @description
  * Changes the A's position translating it the
  * given space.
  *
  * @param movement
  * The direction and magnitud of where it's gonna move.
  */
  FORCEINLINE void 
  move(const Vector3f& movement)
  {
    m_a += movement;
  }

  /**
  * @brief
  * Getter of the left-up-front most point of the box.
  *
  * @description
  * Returns the left-up-front most point that defines the box.
  *
  * @return
  * The left-up-front most point that defines the box.
  */
  FORCEINLINE Vector3f
  getA() const
  {
    return m_a;
  }
  /**
  * @brief
  * Setter of the left-up-front most point of the box.
  *
  * @description
  * Changes the left-up-front most point defining the box 
  * to the new given point.
  *
  * @param A
  * The new left-up-front most point for the box.
  */
  FORCEINLINE void
  setA(const Vector3f& A)
  {
    m_a = A;
  }
  /**
  * @brief
  * Getter of the size of the box.
  *
  * @description
  * Returns the size that defines the box.
  *
  * @return
  * The size that defines the box.
  */
  FORCEINLINE Vector3f
  getSize() const
  {
    return m_size;
  }
  /**
  * @brief
  * Setter of the size of the box.
  *
  * @description
  * Changes the size defining the box to the new given size.
  *
  * @param size
  * The new size for the box.
  */
  FORCEINLINE void
  setSize(const Vector3f& size)
  {
    EE_ASSERT(size.x >= 0.0f && size.y >= 0.0f && size.z >= 0.0f
      && "Size can't be negative!");

    m_size = size;
  }
  /**
  * @brief
  * Getter of the right-down-back most point of the box.
  *
  * @description
  * Returns the right-down-back most point that defines the box.
  *
  * @return
  * The right-down-back most point that defines the box.
  */
  FORCEINLINE Vector3f
  getB() const
  {
    return m_a + Vector3f(m_size.x, -m_size.y, -m_size.z);
  }

  

  /**
  * @brief
  * Checks intersection box-point.
  *
  * @description
  * Returns true if the point is in the box.
  *
  * @param point
  * The point to check if it's in the box.
  *
  * @return
  * Whether it's intersacting or not.
  */
  bool
  intersects(const Vector3f& point) const;
  /**
  * @brief
  * Checks intersection box-plane.
  *
  * @description
  * Returns true if the plane intersects the box.
  *
  * @param plane
  * The plane to check if it's touching the box.
  *
  * @return
  * Whether it's intersacting or not.
  */
  bool
  intersects(const Plane& plane) const;
  /**
  * @brief
  * Checks intersection box-sphere.
  *
  * @description
  * Returns true if the sphere intersects the box.
  *
  * @param sphere
  * The sphere to check if it's touching the box.
  *
  * @return
  * Whether it's intersecting or not.
  */
  bool
  intersects(const Sphere& sphere);
  /**
  * @brief
  * Checks intersection box-box.
  *
  * @description
  * Returns true if the firts box intersects the second.
  *
  * @param box
  * The second box to check if it's touching the first.
  *
  * @return
  * Whether it's intersecting or not.
  */
  bool
  intersects(const BoxAAB& box);
  /**
  * @brief
  * Checks intersection box-capsule.
  *
  * @description
  * Returns true if the capsule intersects the box.
  *
  * @param capsule
  * The capsule to check if it's touching the box.
  *
  * @return
  * Whether it's intersecting or not.
  */
  bool
  intersects(const Capsule& capsule);


  /**
  * @brief
  * The simpler box, with it's vertices on all the 1's of the plane.
  */
  static const BoxAAB SIMPLEX;

 private:
   /**
   * @brief
   * The left-up-front most point that defines the box.
   */
  Vector3f m_a;
  /**
  * @brief
  * The size that defines the box.
  */
  Vector3f m_size;
};
}
