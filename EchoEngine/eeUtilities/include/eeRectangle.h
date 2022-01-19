/************************************************************************/
/**
 * @file eeCapsule.h
 * @author Diego Castellanos
 * @date 28/09/21
 * @brief This file defines all types of rectangles, not oriented, oriented,
          as well as all its functions.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesUtilities.h"
#include "eeVector2.h"

namespace eeEngineSDK {
/**
 * @brief
 * The simplest rectangle. Not oriented. Defined by a point and a size.
 * For 2 dimensional spaces, like view ports.
 */
class EE_UTILITY_EXPORT Rectangle
{
 public:
  /**
   * @brief
   * Default constructor.
   *
   * @description
   * Makes the rectangle that goes from (-1,1) yo (1,-1)
   */
  Rectangle();
  /**
   * @brief
   * Custom constructor.
   *
   * @description
   * Initializes the box with a given left-up most point and size.
   *
   * @param A
   * The left-up most point of the box.
   * @param size
   * The size in the two dimensions of the box.
   */
  Rectangle(const Vector2f& A, const Vector2f& size);
  /**
   * @brief
   * Custom constructor.
   *
   * @description
   * Initializes the box with a given left-up most point and size.
   *
   * @param Ax
   * The left most coord of the box.
   * @param Ay
   * The up most coord of the box.
   * @param width
   * The size in the x axis of the box.
   * @param height
   * The size in the y axis of the box.
   */
  Rectangle(const float Ax, const float Ay, 
            const float width, const float height);
  /**
   * @brief
   * Destructor.
   *
   * @description
   * Frees any memory that could have been allocated.
   */
  ~Rectangle();

  /**
   * @brief
   * Moves the rectangle.
   *
   * @description
   * Changes the A's position translating it the
   * given space.
   *
   * @param movement
   * The direction and magnitude of where it's gonna move.
   */
  void 
  move(const Vector2f& _movement)
  {
    m_a += _movement;
  }

  /**
   * @brief
   * Getter of the left-up most point of the box.
   *
   * @description
   * Returns the left-up most point that defines the box.
   *
   * @return
   * The left-up most point that defines the box.
   */
  Vector2f
  getA() const
  {
    return m_a;
  }
  /**
   * @brief
   * Setter of the left-up most point of the box.
   *
   * @description
   * Changes the left-up most point defining the box
   * to the new given point.
   *
   * @param A
   * The new left-up most point for the box.
   */
  void
  setA(const Vector2f& A)
  {
    m_a = A;
  }
  /**
   * @brief
   * Getter of size point of the box.
   *
   * @description
   * Returns the size that defines the box.
   *
   * @return
   * The size that defines the box.
   */
  Vector2f
  getSize() const
  {
    return m_size;
  }
  /**
   * @brief
   * Setter of the size of the box.
   *
   * @description
   * Changes the size defining the box
   * to the new given point.
   *
   * @param A
   * The new size for the box.
   */
  void
  setSize(const Vector2f& size)
  {
    EE_ASSERT(size.x >= 0.0f && size.y >= 0.0f
           && "Size can't be negative!");
    m_size = size;
  }
  /**
   * @brief
   * Setter of the size of the box.
   *
   * @description
   * Changes the size defining the box
   * to the new given point.
   *
   * @param width
   * The new size in the x axis for the box.
   * @param height
   * The new size in the y axis for the box.
   */
  void
  setSize(const float width, const float height)
  {
    EE_ASSERT(width >= 0.0f && height >= 0.0f
      && "Size can't be negative!");

    m_size = Vector2f(width, height);
  }
  /**
   * @brief
   * Getter of the right-down most point of the box.
   *
   * @description
   * Returns the right-down most point that defines the box.
   *
   * @return
   * The right-down most point that defines the box.
   */
  Vector2f
  getB() const
  {
    return m_a + Vector2f(m_size.x, m_size.y);
  }



  /**
   * @brief
   * Checks intersection rectangle-point.
   *
   * @description
   * Returns true if the point is in the rectangle.
   *
   * @param point
   * The point to check if it's in the rectangle.
   *
   * @return
   * Whether it's intersecting or not.
   */
  bool
  intersects(const Vector2f& point) const;
  /**
   * @brief
   * Checks intersection rectangle-rectangle.
   *
   * @description
   * Returns true if the first rectangle intersects the second.
   *
   * @param rectangle
   * The second rectangle to check if it's touching the first.
   *
   * @return
   * Whether it's intersecting or not.
   */
  bool
  intersects(const Rectangle& rectangle) const;



  /**
   * @brief
   * The simpler box that goes from (-1,-1) yo (1,1)
   */
  static const Rectangle kSIMPLEX;

 private:
  /**
   * The left-up most point of the box.
   */
  Vector2f m_a;
  /**
   * The size in the two dimensions of the box.
   */
  Vector2f m_size;
};
}
