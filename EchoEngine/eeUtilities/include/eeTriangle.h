/************************************************************************/
/**
 * @file eeTriangle.h
 * @author Diego Castellanos
 * @date 08/03/22
 * @brief
 * The triangle struct. Holds 3 vertices in 3D space.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesUtilities.h"
#include <eeVertex.h>

namespace eeEngineSDK {
/**
 * @brief
 * The triangle class. Holds 3 vertices in 3D space.
 */
class EE_UTILITY_EXPORT Triangle
{
 public:
  /**
   * @brief
   * Default constructor
   */
  Triangle() = default;
  /**
   * @brief
   * Custom constructor
   * 
   * @description
   * Creates a triangles with 3 vertex points.
   * 
   * @param _x
   * The first vertex of the triangle.
   * @param _y
   * The second vertex of the triangle.
   * @param _z
   * The third vertex of the triangle.
   */
  Triangle(const ComplexVertex& _x,
           const ComplexVertex& _y, 
           const ComplexVertex& _z) :
  x(_x),
  y(_y),
  z(_z)
  {}
  /**
   * @brief
   * Default destructor.
   */
  ~Triangle() = default;


  /**
   * @brief
   * Splits triangles.
   *
   * @description
   * Returns the triangles resulting of the split of the given triangles by a
   * plane.
   *
   * @param splitTriangle
   * The triangle to be split.
   * @param splitterPlane
   * The plane to split the triangle.
   * 
   * @return
   * The triangles resulting of the split of the given triangles by a plane.
   */
  static Vector<Vector<Triangle>>
  getSplitTrianglesByPlane(const Triangle& splitTriangle,
                           const Plane& splitterPlane);
                           
  /**
   * @brief
   * Check if the triangle is colliding with the plane.
   *
   * @description
   * Check if the triangle is colliding with the plane.
   *
   * @param splitTriangle
   * The triangle to check.
   * @param splitterPlane
   * The plane to collide.
   * 
   * @return
   * True if they are colliding;
   */
  static bool
  isTrianglesCollidingPlane(const Triangle& checkingTriangle,
                            const Plane& collidingPlane);

  /**
   * The first vertex of the triangle.
   */
  ComplexVertex x;
  /**
   * The second vertex of the triangle.
   */
  ComplexVertex y;
  /**
   * The third vertex of the triangle.
   */
  ComplexVertex z;
};
}
