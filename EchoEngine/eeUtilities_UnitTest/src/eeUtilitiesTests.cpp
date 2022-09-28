#include <eePrerequisitesUtilities.h>

#pragma warning(push)
#pragma warning ( disable: 4389 )
#include <gtest/gtest.h>
#pragma warning(pop)

#include "eeMath.h"

#include "eeVector2.h"
#include "eeVector3.h"
#include "eeVector4.h"

#include "eeMatrix2.h"
#include "eeMatrix3.h"
#include "eeMatrix4.h"

#include "eePlane.h"
#include "eeSphere.h"
#include "eeBox.h"
#include "eeCapsule.h"
#include "eeRectangle.h"

#include "eeQuaternion.h"
	
using eeEngineSDK::Math;
using eeEngineSDK::int32;
using eeEngineSDK::uint32;

using eeEngineSDK::Vector2f;
using eeEngineSDK::Vector2i;
using eeEngineSDK::Point2D;

using eeEngineSDK::Vector3f;
using eeEngineSDK::Vector3i;
using eeEngineSDK::Point3D;

using eeEngineSDK::Vector4f;
using eeEngineSDK::Vector4i;
using eeEngineSDK::Point4D;

using eeEngineSDK::Matrix2f;
using eeEngineSDK::Matrix2i;
using eeEngineSDK::Matrix2u;

using eeEngineSDK::Matrix3f;
using eeEngineSDK::Matrix3i;
using eeEngineSDK::Matrix3u;

using eeEngineSDK::Matrix4f;
using eeEngineSDK::Matrix4i;
using eeEngineSDK::Matrix4u;

using eeEngineSDK::Plane;
using eeEngineSDK::Sphere;
using eeEngineSDK::BoxAAB;
using eeEngineSDK::Capsule;
using eeEngineSDK::Rectangle;

using eeEngineSDK::Quaternion;

TEST(eeUtilities, Basic_Type_Sizes)
{
  EXPECT_EQ(sizeof(eeEngineSDK::int8), 1);
  EXPECT_EQ(sizeof(eeEngineSDK::int16), 2);
  EXPECT_EQ(sizeof(eeEngineSDK::int32), 4);
  EXPECT_EQ(sizeof(eeEngineSDK::int64), 8);

  EXPECT_EQ(sizeof(eeEngineSDK::uint8), 1);
  EXPECT_EQ(sizeof(eeEngineSDK::uint16), 2);
  EXPECT_EQ(sizeof(eeEngineSDK::uint32), 4);
  EXPECT_EQ(sizeof(eeEngineSDK::uint64), 8);

  EXPECT_EQ(sizeof(eeEngineSDK::WCHAR), 2);
  EXPECT_EQ(sizeof(eeEngineSDK::ANSICHAR), 1);
  EXPECT_EQ(sizeof(eeEngineSDK::UNICHAR), 2);
  EXPECT_EQ(sizeof(eeEngineSDK::unchar), 1);

  EXPECT_EQ(sizeof(eeEngineSDK::TYPE_OF_NULL), 4);
  //EXPECT_EQ(sizeof(eeEngineSDK::SIZE_T), 8); // Cambai segun la arquitectura
}

TEST(eeUtilities, Vector2)
{
  /* Vector2f */
  // Size
  EXPECT_EQ(sizeof(Vector2f), 8);

  // Default constructor
  Vector2f vf = Vector2f::kZERO;
  EXPECT_EQ(vf, Vector2f::kZERO);

  // operator=
  vf = Vector2f(-3.0f, 1.0f);
  EXPECT_EQ(vf, Vector2f(-3.0f, 1.0f));

  // Custom constructor constructor
  Vector2f vf2(-3.0f, 4.0f);
  EXPECT_EQ(vf2, Vector2f(-3.0f, 4.0f));

  // Functions
  EXPECT_EQ(vf.dot(vf2), 13.0f);

  EXPECT_EQ(vf.getDistance(vf2), 3.0f);
  EXPECT_EQ(vf2.getMagnitud(), 5.0f);

  float mag = vf.getMagnitud();
  EXPECT_TRUE(vf.getNormalize() == Vector2f(-0.948683f, 0.316228f));
  vf.normalize();
  EXPECT_TRUE(vf == Vector2f(-0.948683f, 0.316228f));
  EXPECT_TRUE(vf.getTruncate(7.0f) == Vector2f(-6.64078309f, 
                                                             2.21359436f));
  vf.truncate(7.0f);
  EXPECT_TRUE(vf == Vector2f(-6.64078309f, 2.21359436f));
  vf.truncate(mag);

  // Operators with other vectors
  //vf =  {-3.0f,  1.0f}
  //vf2 = {-3.0f,  4.0f}
  EXPECT_TRUE(vf + vf2 == Vector2f(-6.0f,  5.0f));
  EXPECT_TRUE(vf - vf2 == Vector2f( 0.0f, -3.0f));
  EXPECT_TRUE(vf * vf2 == Vector2f( 9.0f,  4.0f));
  EXPECT_TRUE(vf / vf2 == Vector2f( 1.0f,  0.25f));
  EXPECT_TRUE(vf % vf2 == Vector2f( 0.0f,  1.0f));

  // Operators with numbers
  EXPECT_TRUE(vf + 1.0f == Vector2f(-2.0f,  2.0f));
  EXPECT_TRUE(1.0f + vf == Vector2f(-2.0f,  2.0f));
  EXPECT_TRUE(vf - 2.0f == Vector2f(-5.0f, -1.0f));
  EXPECT_TRUE(2.0f - vf == Vector2f( 5.0f,  1.0f));
  EXPECT_TRUE(vf * 3.0f == Vector2f(-9.0f,  3.0f));
  EXPECT_TRUE(3.0f * vf == Vector2f(-9.0f,  3.0f));
  EXPECT_TRUE(vf / 2.0f == Vector2f(-1.5f,  0.5f));
  EXPECT_TRUE(2.0f / vf == Vector2f(-0.66666666f,  2.0f));
  EXPECT_TRUE(vf % 1.5f == Vector2f( 0.0f,  1.0f));
  EXPECT_TRUE(1.5f % vf == Vector2f( 1.5f,  0.5f));


  // Assign operators with other vectors
  vf += vf2;
  EXPECT_TRUE(vf == Vector2f(-6.0f,  5.0f));
  vf -= vf2;
  EXPECT_TRUE(vf == Vector2f(-3.0f,  1.0f));
  vf *= vf2;
  EXPECT_TRUE(vf == Vector2f( 9.0f,  4.0f));
  vf /= vf2;
  EXPECT_TRUE(vf == Vector2f(-3.0f,  1.0f));
  vf %= vf2;
  EXPECT_TRUE(vf == Vector2f( 0.0f,  1.0f));

  // Assign operators with numbers
  vf += 1.0f;
  EXPECT_TRUE(vf == Vector2f( 1.0f,  2.0f));
  vf -= 3.0f;
  EXPECT_TRUE(vf == Vector2f(-2.0f, -1.0f));
  vf *= 3.0f;
  EXPECT_TRUE(vf == Vector2f(-6.0f, -3.0f));
  vf /= 2.0f;
  EXPECT_TRUE(vf == Vector2f(-3.0f, -1.5f));
  vf %= 2.0f;
  EXPECT_TRUE(vf == Vector2f(-1.0f, -1.5f));


  // Logic operators
  EXPECT_TRUE(vf != vf2);



  /* Vector2i */
  // Size
  EXPECT_EQ(sizeof(Vector2i), 8);

  // Default constructor
  Vector2i vi = Vector2i::kZERO;
  EXPECT_EQ(vi, Vector2i::kZERO);

  // operator=
  vi = Vector2i(-3, 1);
  EXPECT_EQ(vi, Vector2i(-3, 1));

  // Custom constructor constructor
  Vector2i vi2(-3, 4);
  EXPECT_EQ(vi2, Vector2i(-3, 4));

  // Functions
  EXPECT_EQ(vi.dot(vi2), 13.0f);

  EXPECT_EQ(vi.getDistance(vi2), 3.0f);
  EXPECT_EQ(vi2.getMagnitude(), 5.0f);

  // Operators with other vectors
  //vi  = {-3,  1}
  //vi2 = {-3,  4}
  EXPECT_TRUE(vi + vi2 == Vector2i(-6,  5));
  EXPECT_TRUE(vi - vi2 == Vector2i( 0, -3));
  EXPECT_TRUE(vi * vi2 == Vector2i( 9,  4));
  EXPECT_TRUE(vi / vi2 == Vector2i( 1,  0));
  EXPECT_TRUE(vi % vi2 == Vector2i( 0,  1));

  // Operators with numbers
  EXPECT_TRUE(vi + 1 == Vector2i(-2,  2));
  EXPECT_TRUE(vi - 2 == Vector2i(-5, -1));
  EXPECT_TRUE(vi * 3 == Vector2i(-9,  3));
  EXPECT_TRUE(vi / 2 == Vector2i(-1,  0));
  EXPECT_TRUE(vi % 2 == Vector2i(-1,  1));


  // Assign operators with other vectors
  vi += vi2;
  EXPECT_TRUE(vi == Vector2i(-6,  5));
  vi -= vi2;
  EXPECT_TRUE(vi == Vector2i(-3,  1));
  vi *= vi2;
  EXPECT_TRUE(vi == Vector2i( 9,  4));
  vi /= vi2;
  EXPECT_TRUE(vi == Vector2i(-3,  1));
  vi %= vi2;
  EXPECT_TRUE(vi == Vector2i( 0,  1));

  // Assign operators with numbers
  vi += 1;
  EXPECT_TRUE(vi == Vector2i( 1,  2));
  vi -= 3;
  EXPECT_TRUE(vi == Vector2i(-2, -1));
  vi *= 3;
  EXPECT_TRUE(vi == Vector2i(-6, -3));
  vi /= 2;
  EXPECT_TRUE(vi == Vector2i(-3, -1));
  vi %= 2;
  EXPECT_TRUE(vi == Vector2i(-1, -1));


  // Logic operators
  EXPECT_TRUE(vi != vi2);



  /* Vector2u */
  // Size
  EXPECT_EQ(sizeof(Point2D), 8);

  // Default constructor
  Point2D vu = Point2D::kZERO;
  EXPECT_EQ(vu, Point2D::kZERO);

  // operator=
  vu = Point2D(3, 1);
  EXPECT_EQ(vu, Point2D(3, 1));

  // Custom constructor constructor
  Point2D vu2(3, 4);
  EXPECT_EQ(vu2, Point2D(3, 4));

  // Functions
  EXPECT_EQ(vu.dot(vu2), 13.0f);

  EXPECT_EQ(vu.getDistance(vu2), 3.0f);
  EXPECT_EQ(vu2.getMagnitud(), 5.0f);

  // Operators with other vectors
  //vu  = {3, 1}
  //vu2 = {3, 4}
  EXPECT_TRUE(vu + vu2 == Point2D(6, 5));
  EXPECT_TRUE(vu2 - vu == Point2D(0, 3));
  EXPECT_TRUE(vu * vu2 == Point2D(9, 4));
  EXPECT_TRUE(vu2 / vu == Point2D(1, 4));
  EXPECT_TRUE(vu % vu2 == Point2D(0, 1));

  // Operators with numbers
  EXPECT_TRUE(vu  + 1u == Point2D(4, 2));
  EXPECT_TRUE(vu2 - 2u == Point2D(1, 2));
  EXPECT_TRUE(vu  * 3u == Point2D(9, 3));
  EXPECT_TRUE(vu  / 2u == Point2D(1, 0));
  EXPECT_TRUE(vu  % 2u == Point2D(1, 1));


  // Assign operators with other vectors
  vu += vu2;
  EXPECT_TRUE(vu == Point2D(6, 5));
  vu -= vu2;
  EXPECT_TRUE(vu == Point2D(3, 1));
  vu *= vu2;
  EXPECT_TRUE(vu == Point2D(9, 4));
  vu /= vu2;
  EXPECT_TRUE(vu == Point2D(3, 1));
  vu %= vu2;
  EXPECT_TRUE(vu == Point2D(0, 1));

  // Assign operators with numbers
  vu += 1u;
  EXPECT_TRUE(vu  == Point2D(1, 2));
  vu2 -= 3u;
  EXPECT_TRUE(vu2 == Point2D(0, 1));
  vu *= 3u;
  EXPECT_TRUE(vu  == Point2D(3, 6));
  vu /= 2u;
  EXPECT_TRUE(vu  == Point2D(1, 3));
  vu %= 2u;
  EXPECT_TRUE(vu  == Point2D(1, 1));


  // Logic operators
  EXPECT_TRUE(vu != vu2);
}

TEST(eeUtilities, Vector3)
{
  /* Vector3f */
  // Size
  EXPECT_EQ(sizeof(Vector3f), 12);

  // Default constructor
  Vector3f vf = Vector3f::kZERO;
  EXPECT_EQ(vf, Vector3f::kZERO);
  
  // operator=
  vf = Vector3f(2.0f, 2.0f, -6.0f);
  EXPECT_EQ(vf, Vector3f(2.0f, 2.0f, -6.0f));
  
  // Custom constructor constructor
  Vector3f vf2(-1.0f, 2.0f, -2.0f);
  EXPECT_EQ(vf2, Vector3f(-1.0f, 2.0f, -2.0f));
  
  // Functions
  EXPECT_EQ(vf.dot(vf2), 14.0f);
  EXPECT_TRUE(vf.cross(vf2) == Vector3f( 8.0f,  10.0f,  6.0f));
  
  EXPECT_EQ(vf.getDistance(vf2), 5.0f);
  EXPECT_EQ(vf2.getMagnitude(), 3.0f);

  float mag = vf.getMagnitude();
  EXPECT_TRUE(vf.getNormalize() == Vector3f( 0.30151134f,  
                                                          0.30151134f, 
                                                         -0.90453403f));
  vf.normalize();
  EXPECT_TRUE(vf == Vector3f( 0.30151134f,  
                                           0.30151134f, 
                                          -0.90453403f));

  EXPECT_TRUE(vf.getTruncate(7.0f) == Vector3f( 2.11057941f,  
                                                             2.11057941f, 
                                                            -6.33173824f));
  vf.truncate(7.0f);
  EXPECT_TRUE(vf == Vector3f( 2.11057941f,  
                                           2.11057941f, 
                                          -6.33173824f));
  vf.truncate(mag);
  
  // Operators with other vectors
  //vf =  { 2.0f,  2.0f, -6.0f}
  //vf2 = {-1.0f,  2.0f, -2.0f}
  EXPECT_TRUE(vf + vf2 == Vector3f( 1.0f,  4.0f, -8.0f));
  EXPECT_TRUE(vf - vf2 == Vector3f( 3.0f,  0.0f, -4.0f));
  EXPECT_TRUE(vf * vf2 == Vector3f(-2.0f,  4.0f,  12.0f));
  EXPECT_TRUE(vf / vf2 == Vector3f(-2.0f,  1.0f,  3.0f));
  EXPECT_TRUE(vf % vf2 == Vector3f( 0.0f,  0.0f,  0.0f));
  
  // Operators with numbers
  EXPECT_TRUE(vf + 1.0f == Vector3f( 3.0f,  3.0f, -5.0f));
  EXPECT_TRUE(vf - 2.0f == Vector3f( 0.0f,  0.0f, -8.0f));
  EXPECT_TRUE(vf * 3.0f == Vector3f( 6.0f,  6.0f, -18.0f));
  EXPECT_TRUE(vf / 2.0f == Vector3f( 1.0f,  1.0f, -3.0f));
  EXPECT_TRUE(vf % 1.5f == Vector3f( 0.5f,  0.5f,  0.0f));
  
  
  // Assign operators with other vectors
  vf += vf2;
  EXPECT_TRUE(vf == Vector3f( 1.0f,  4.0f, -8.0f));
  vf -= vf2;
  EXPECT_TRUE(vf == Vector3f( 2.0f,  2.0f, -6.0f));
  vf /= vf2;
  EXPECT_TRUE(vf == Vector3f(-2.0f,  1.0f,  3.0f));
  vf *= vf2;
  EXPECT_TRUE(vf == Vector3f( 2.0f,  2.0f, -6.0f));
  vf %= vf2;
  EXPECT_TRUE(vf == Vector3f( 0.0f,  0.0f,  0.0f));
   
  // Assign operators with numbers
  vf += 1.0f;
  EXPECT_TRUE(vf == Vector3f( 1.0f,  1.0f,  1.0f));
  vf -= 3.0f;
  EXPECT_TRUE(vf == Vector3f(-2.0f, -2.0f, -2.0f));
  vf *= 3.0f;
  EXPECT_TRUE(vf == Vector3f(-6.0f, -6.0f, -6.0f));
  vf /= 2.0f;
  EXPECT_TRUE(vf == Vector3f(-3.0f, -3.0f, -3.0f));
  vf %= 2.0f;
  EXPECT_TRUE(vf == Vector3f(-1.0f, -1.0f, -1.0f));
  
  
  // Logic operators
  EXPECT_TRUE(vf != vf2);



  /* Vector3i */
  // Size
  EXPECT_EQ(sizeof(Vector3i), 12);

  // Default constructor
  Vector3i vi = Vector3i::kZERO;
  EXPECT_EQ(vi, Vector3i::kZERO);

  // operator=
  vi = Vector3i(2, 2, -6);
  EXPECT_EQ(vi, Vector3i(2, 2, -6));

  // Custom constructor constructor
  Vector3i vi2(-1, 2, -2);
  EXPECT_EQ(vi2, Vector3i(-1, 2, -2));

  // Functions
  EXPECT_EQ(vi.dot(vi2), 14.0f);
  EXPECT_TRUE(vi.cross(vi2) == Vector3f(8.0f, 10.0f, 6.0f));

  EXPECT_EQ(vi.getDistance(vi2), 5.0f);
  EXPECT_EQ(vi2.getMagnitud(), 3.0f);

  // Operators with other vectors
  //vi =  { 2,  2, -6}
  //vi2 = {-1,  2, -2}
  EXPECT_TRUE(vi + vi2 == Vector3i( 1,  4, -8));
  EXPECT_TRUE(vi - vi2 == Vector3i( 3,  0, -4));
  EXPECT_TRUE(vi * vi2 == Vector3i(-2,  4,  12));
  EXPECT_TRUE(vi / vi2 == Vector3i(-2,  1,  3));
  EXPECT_TRUE(vi % vi2 == Vector3i( 0,  0,  0));

  // Operators with numbers
  EXPECT_TRUE(vi + 1 == Vector3i( 3,  3, -5));
  EXPECT_TRUE(vi - 2 == Vector3i( 0,  0, -8));
  EXPECT_TRUE(vi * 3 == Vector3i( 6,  6, -18));
  EXPECT_TRUE(vi / 2 == Vector3i( 1,  1, -3));
  EXPECT_TRUE(vi % 3 == Vector3i( 2,  2,  0));


  // Assign operators with other vectors
  vi += vi2;
  EXPECT_TRUE(vi == Vector3i( 1,  4, -8));
  vi -= vi2;
  EXPECT_TRUE(vi == Vector3i( 2,  2, -6));
  vi /= vi2;
  EXPECT_TRUE(vi == Vector3i(-2,  1,  3));
  vi *= vi2;
  EXPECT_TRUE(vi == Vector3i( 2,  2, -6));
  vi %= vi2;
  EXPECT_TRUE(vi == Vector3i( 0,  0,  0));

  // Assign operators with numbers
  vi += 1;
  EXPECT_TRUE(vi == Vector3i( 1,  1,  1));
  vi -= 3;
  EXPECT_TRUE(vi == Vector3i(-2, -2, -2));
  vi *= 3;
  EXPECT_TRUE(vi == Vector3i(-6, -6, -6));
  vi /= 2;
  EXPECT_TRUE(vi == Vector3i(-3, -3, -3));
  vi %= 2;
  EXPECT_TRUE(vi == Vector3i(-1, -1, -1));


  // Logic operators
  EXPECT_TRUE(vi != vi2);



  /* Vector3u */
  // Size
  EXPECT_EQ(sizeof(Point3D), 12);

  // Default constructor
  Point3D vu = Point3D::kZERO;
  EXPECT_EQ(vu, Point3D::kZERO);

  // operator=
  vu = Point3D(4, 2, 6);
  EXPECT_EQ(vu, Point3D(4, 2, 6));

  // Custom constructor constructor
  Point3D vu2(1, 2, 2);
  EXPECT_EQ(vu2, Point3D(1, 2, 2));

  // Functions
  EXPECT_EQ(vu.getDistance(vu2), 5.0f);
  EXPECT_EQ(vu2.getMagnitud(), 3.0f);

  // Operators with other vectors
  //vu =  {4, 2, 6}
  //vu2 = {1, 2, 2}
  EXPECT_TRUE(vu + vu2 == Point3D(5, 4, 8));
  EXPECT_TRUE(vu - vu2 == Point3D(3, 0, 4));
  EXPECT_TRUE(vu * vu2 == Point3D(4, 4, 12));
  EXPECT_TRUE(vu / vu2 == Point3D(4, 1, 3));
  EXPECT_TRUE(vu % vu2 == Point3D(0, 0, 0));

  // Operators with numbers
  EXPECT_TRUE(vu + 1 == Point3D(5, 3, 7));
  EXPECT_TRUE(vu - 2 == Point3D(2, 0, 4));
  EXPECT_TRUE(vu * 3 == Point3D(12, 6, 18));
  EXPECT_TRUE(vu / 2 == Point3D(2, 1, 3));
  EXPECT_TRUE(vu % 3 == Point3D(1, 2, 0));


  // Assign operators with other vectors
  vu += vu2;
  EXPECT_TRUE(vu == Point3D(5, 4, 8));
  vu -= vu2;
  EXPECT_TRUE(vu == Point3D(4, 2, 6));
  vu /= vu2;
  EXPECT_TRUE(vu == Point3D(4, 1, 3));
  vu *= vu2;
  EXPECT_TRUE(vu == Point3D(4, 2, 6));
  vu %= vu2;
  EXPECT_TRUE(vu == Point3D(0, 0, 0));

  // Assign operators with numbers
  vu += 2;
  EXPECT_TRUE(vu == Point3D(2, 2, 2));
  vu -= 1;
  EXPECT_TRUE(vu == Point3D(1, 1, 1));
  vu *= 3;
  EXPECT_TRUE(vu == Point3D(3, 3, 3));
  vu /= 2;
  EXPECT_TRUE(vu == Point3D(1, 1, 1));
  vu %= 2;
  EXPECT_TRUE(vu == Point3D(1, 1, 1));


  // Logic operators
  EXPECT_TRUE(vu != vu2);
}

TEST(eeUtilities, Vector4)
{
  /* Vector4f */
  // Size
  EXPECT_EQ(sizeof(Vector4f), 16);

  // Default constructor
  Vector4f vf = Vector4f::kZERO;
  EXPECT_EQ(vf, Vector4f::kZERO);

  // operator=
  vf = Vector4f(-7.0f, 4.0f, 6.0f, -4.0f);
  EXPECT_EQ(vf, Vector4f(-7.0f, 4.0f, 6.0f, -4.0f));

  // Custom constructor constructor
  Vector4f vf2(-5.0f, 2.0f, 4.0f, -6.0f);
  EXPECT_EQ(vf2, Vector4f(-5.0f, 2.0f, 4.0f, -6.0f));

  // Functions
  EXPECT_EQ(vf.dot(vf2), 91.0f);

  EXPECT_EQ(vf.getDistance(vf2), 4.0f);
  EXPECT_EQ(vf2.getMagnitude(), 9.0f);

  float mag = vf.getMagnitude();
  EXPECT_TRUE(vf.getNormalize() == Vector4f(-0.64715023f,  
                                                          0.36980013f,  
                                                          0.55470020f, 
                                                         -0.36980013f));
  vf.normalize();
  EXPECT_TRUE(vf == Vector4f(-0.64715023f,  
                                           0.36980013f,  
                                           0.55470020f, 
                                          -0.36980013f));

  EXPECT_TRUE(vf.getTruncate(7.0f) == Vector4f(-4.53005160f, 
                                                             2.58860092f, 
                                                             3.88290137f, 
                                                            -2.58860092f));
  vf.truncate(7.0f);
  EXPECT_TRUE(vf == Vector4f(-4.53005160f, 
                                           2.58860092f, 
                                           3.88290137f, 
                                          -2.58860092f));
  vf.truncate(mag);

  // Operators with other vectors
  //vf  = {-7.0f,  4.0f,  6.0f, -4.0f}
  //vf2 = {-5.0f,  2.0f,  4.0f, -6.0f}
  EXPECT_TRUE(vf + vf2 == Vector4f(-12.0f,  6.0f,  
                                                 10.0f, -10.0f));
  EXPECT_TRUE(vf - vf2 == Vector4f(-2.0f,   2.0f,  
                                                 2.0f,   2.0f));
  EXPECT_TRUE(vf * vf2 == Vector4f( 35.0f,  8.0f,  
                                                 24.0f,  24.0f));
  EXPECT_TRUE(vf / vf2 == Vector4f( 1.4f,   2.0f,  
                                                 1.5f,   0.66666667f));
  EXPECT_TRUE(vf % vf2 == Vector4f(-2.0f,   0.0f,  
                                                 2.0f,  -4.0f));

  // Operetors with numbers
  EXPECT_TRUE(vf + 1.0f == Vector4f(-6.0f,   5.0f,   
                                                  7.0f,  -3.0f));
  EXPECT_TRUE(vf - 2.0f == Vector4f(-9.0f,   2.0f,   
                                                  4.0f,  -6.0f));
  EXPECT_TRUE(vf * 3.0f == Vector4f(-21.0f,  12.0f,  
                                                  18.0f, -12.0f));
  EXPECT_TRUE(vf / 2.0f == Vector4f(-3.5f,   2.0f,   
                                                  3.0f,  -2.0f));
  EXPECT_TRUE(vf % 1.5f == Vector4f(-1.0f,   1.0f,   
                                                  0.0f,  -1.0f));


  // Asign operators with other vectors
  vf += vf2;
  EXPECT_TRUE(vf == Vector4f(-12.0f,  6.0f,  10.0f, -10.0f));
  vf -= vf2;
  EXPECT_TRUE(vf == Vector4f(-7.0f,   4.0f,  6.0f,  -4.0f));
  vf /= vf2;
  EXPECT_TRUE(vf == Vector4f( 1.4f,   2.0f,  1.5f,   0.6666667f));
  vf *= vf2;
  EXPECT_TRUE(vf == Vector4f(-7.0f,   4.0f,  6.0f,  -4.0f));
  vf %= vf2;
  EXPECT_TRUE(vf == Vector4f(-2.0f,   0.0f,  2.0f,  -4.0f));

  // Assign operators with numbers
  vf += 1.0f;
  EXPECT_TRUE(vf == Vector4f(-1.0f,   1.0f,  3.0f,  -3.0f));
  vf -= 3.0f;
  EXPECT_TRUE(vf == Vector4f(-4.0f,  -2.0f,  0.0f,  -6.0f));
  vf *= 3.0f;
  EXPECT_TRUE(vf == Vector4f(-12.0f, -6.0f,  0.0f,  -18.0f));
  vf /= 2.0f;
  EXPECT_TRUE(vf == Vector4f(-6.0f,  -3.0f,  0.0f,  -9.0f));
  vf %= 2.0f;
  EXPECT_TRUE(vf == Vector4f(-0.0f,  -1.0f,  0.0f,  -1.0f));


  // Logic operators
  EXPECT_TRUE(vf != vf2);



  /* Vector4i */
  // Size
  EXPECT_EQ(sizeof(Vector4i), 16);

  // Default constructor
  Vector4i vi = Vector4i::kZERO;
  EXPECT_EQ(vi, Vector4i::kZERO);

  // operator=
  vi = Vector4i(-7,  4,  6, -4);
  EXPECT_EQ(vi, Vector4i(-7,  4,  6, -4));

  // Custom constructor constructor
  Vector4i vi2(-5,  2,  4, -6);
  EXPECT_EQ(vi2, Vector4i(-5,  2,  4, -6));

  // Functions
  EXPECT_EQ(vi.dot(vi2), 91.0f);

  EXPECT_EQ(vi.getDistance(vi2), 4.0f);
  EXPECT_EQ(vi2.getMagnitude(), 9.0f);

  // Operators with other vectors
  //vi  = {-7,  4,  6, -4}
  //vi2 = {-5,  2,  4, -6}
  EXPECT_TRUE(vi + vi2 == Vector4i(-12,  6,   10, -10));
  EXPECT_TRUE(vi - vi2 == Vector4i(-2,   2,   2,   2));
  EXPECT_TRUE(vi * vi2 == Vector4i( 35,  8,   24,  24));
  EXPECT_TRUE(vi / vi2 == Vector4i( 1,   2,   1,   0));
  EXPECT_TRUE(vi % vi2 == Vector4i(-2,   0,   2,  -4));

  // Operators with numbers
  EXPECT_TRUE(vi + 1 == Vector4i(-6,   5,   7,  -3));
  EXPECT_TRUE(vi - 2 == Vector4i(-9,   2,   4,  -6));
  EXPECT_TRUE(vi * 3 == Vector4i(-21,  12,  18, -12));
  EXPECT_TRUE(vi / 2 == Vector4i(-3,   2,   3,  -2));
  EXPECT_TRUE(vi % 2 == Vector4i(-1,   0,   0,  0));


  // Assign operators with other vectors
  vi += vi2;
  EXPECT_TRUE(vi == Vector4i(-12,  6,   10, -10));
  vi -= vi2;
  EXPECT_TRUE(vi == Vector4i(-7,   4,   6,  -4));
  vi /= vi2;
  EXPECT_TRUE(vi == Vector4i( 1,   2,   1,   0));
  vi *= vi2;
  EXPECT_TRUE(vi == Vector4i(-5,   4,   4,   0));
  vi %= vi2;
  EXPECT_TRUE(vi == Vector4i( 0,   0,   0,   0));

  // Assign operators with numbers
  vi += 1;
  EXPECT_TRUE(vi == Vector4i( 1,   1,   1,   1));
  vi -= 3;
  EXPECT_TRUE(vi == Vector4i(-2,  -2,  -2,  -2));
  vi *= 3;
  EXPECT_TRUE(vi == Vector4i(-6,  -6,  -6,  -6));
  vi /= 2;
  EXPECT_TRUE(vi == Vector4i(-3,  -3,  -3,  -3));
  vi %= 2;
  EXPECT_TRUE(vi == Vector4i(-1,  -1,  -1,  -1));


  // Logic operators
  EXPECT_TRUE(vi != vi2);



  /* Vector4u */
  // Size
  EXPECT_EQ(sizeof(Point4D), 16);

  // Default constructor
  Point4D vu = Point4D::kZERO;
  EXPECT_EQ(vu, Point4D::kZERO);

  // operator=
  vu = Point4D(6, 6, 6, 8);
  EXPECT_EQ(vu, Point4D(6, 6, 6, 8));

  // Custom constructor constructor
  Point4D vu2(5, 2, 4, 6);
  EXPECT_EQ(vu2, Point4D(5, 2, 4, 6));

  // Functions
  EXPECT_EQ(vu.getDistance(vu2), 5.0f);
  EXPECT_EQ(vu2.getMagnitude(), 9.0f);

  // Operators with other vectors
  //vu  = {6, 6, 6, 8}
  //vu2 = {5, 2, 4, 6}
  EXPECT_TRUE(vu + vu2 == Point4D(11, 8, 10, 14));
  EXPECT_TRUE(vu - vu2 == Point4D(1, 4, 2, 2));
  EXPECT_TRUE(vu* vu2 == Point4D(30, 12, 24, 48));
  EXPECT_TRUE(vu / vu2 == Point4D(1, 3, 1, 1));
  EXPECT_TRUE(vu% vu2 == Point4D(1, 0, 2, 2));

  // Operators with numbers
  EXPECT_TRUE(vu + 1 == Point4D(7, 7, 7, 9));
  EXPECT_TRUE(vu - 2 == Point4D(4, 4, 4, 6));
  EXPECT_TRUE(vu * 3 == Point4D(18, 18, 18, 24));
  EXPECT_TRUE(vu / 2 == Point4D(3, 3, 3, 4));
  EXPECT_TRUE(vu % 2 == Point4D(0, 0, 0, 0));


  // Assign operators with other vectors
  vu += vu2;
  EXPECT_TRUE(vu == Point4D(11, 8, 10, 14));
  vu -= vu2;
  EXPECT_TRUE(vu == Point4D(6, 6, 6, 8));
  vu /= vu2;
  EXPECT_TRUE(vu == Point4D(1, 3, 1, 1));
  vu *= vu2;
  EXPECT_TRUE(vu == Point4D(5, 6, 4, 6));
  vu %= vu2;
  EXPECT_TRUE(vu == Point4D(0, 0, 0, 0));

  // Assign operators with numbers
  vu += 3;
  EXPECT_TRUE(vu == Point4D(3, 3, 3, 3));
  vu -= 2;
  EXPECT_TRUE(vu == Point4D(1, 1, 1, 1));
  vu *= 3;
  EXPECT_TRUE(vu == Point4D(3, 3, 3, 3));
  vu /= 2;
  EXPECT_TRUE(vu == Point4D(1, 1, 1, 1));
  vu %= 2;
  EXPECT_TRUE(vu == Point4D(1, 1, 1, 1));


  // Logic operators
  EXPECT_TRUE(vu != vu2);
}

TEST(eeUtilities, Matrix2)
{
  /* Matrix2f */
  // Size
  EXPECT_EQ(sizeof(Matrix2f), 16);

  // Default constructor and matrix ZERO
  Matrix2f deff = Matrix2f::kZERO;
  EXPECT_TRUE(deff == Matrix2f::kZERO);

  // Custom constructor 1 and matrix ONES
  float mf[4] = {1.0f,1.0f,1.0f,1.0f};
  Matrix2f cst1f(mf);
  EXPECT_TRUE(cst1f == Matrix2f::kONES);

  // Custom constructor 2 and matrix IDENTITY
  //Matrix2f cst2f(Vector2f(1.0f, 0.0f), 
  //               Vector2f(0.0f, 1.0f));
  Matrix2f cst2f(1.0f, 0.0f, 
                 0.0f, 1.0f);
  EXPECT_TRUE(cst2f == Matrix2f::kIDENTITY);

  // Custom constructor 3
  Matrix2f cst3f(1.0f, 2.0f, 3.0f, 4.0f);
  //EXPECT_TRUE(cst3f == Matrix2f(Vector2f(1.0f, 2.0f),
  //                              Vector2f(3.0f, 4.0f)));


  // Functions
  EXPECT_EQ(cst3f.getDeterminant(), -2.0f);
  EXPECT_TRUE(cst3f.getTranspose() == Matrix2f(1.0f,  3.0f, 
                                                            2.0f,  4.0f));
  EXPECT_TRUE(cst3f.getInverse() == Matrix2f(-2.0f,  1.0f, 
                                                           1.5f, -0.5f));

  Matrix2f temp(1.0f, 2.0f, 3.0f, 4.0f);
  temp.transpose();
  EXPECT_TRUE(temp == Matrix2f( 1.0f,  3.0f,
                                             2.0f,  4.0f));
  temp.inverse();
  EXPECT_TRUE(temp == Matrix2f(-2.0f,  1.5f,
                                             1.0f, -0.5f));


  // Operators overloads
  EXPECT_TRUE(cst3f + cst2f == Matrix2f(2.0f, 2.0f, 3.0f, 5.0f));
  EXPECT_TRUE(cst3f - cst2f == Matrix2f(0.0f, 2.0f, 3.0f, 3.0f));
  EXPECT_TRUE(cst3f * cst1f == Matrix2f(3.0f, 3.0f, 7.0f, 7.0f));
  EXPECT_TRUE(cst3f * 2 == Matrix2f(2.0f, 4.0f, 6.0f, 8.0f));

  cst3f = cst2f;
  EXPECT_TRUE(cst3f == cst2f);

  cst3f += cst1f;
  EXPECT_TRUE(cst3f == Matrix2f(2.0f, 1.0f, 1.0f, 2.0f));
  cst3f -= cst1f;
  EXPECT_TRUE(cst3f == Matrix2f(1.0f, 0.0f, 0.0f, 1.0f));
  cst3f *= cst1f;
  EXPECT_TRUE(cst3f == Matrix2f(1.0f, 1.0f, 1.0f, 1.0f));
  cst3f *= 3;
  EXPECT_TRUE(cst3f == Matrix2f(3.0f, 3.0f, 3.0f, 3.0f));
}

TEST(eeUtilities, Matrix3)
{
  /* Matrix3f */
  // Size
  EXPECT_EQ(sizeof(Matrix3f), 36);

  // Default constructor and matrix ZERO
  Matrix3f deff = Matrix3f::kZERO;
  EXPECT_TRUE(deff == Matrix3f::kZERO);

  // Custom constructor 1 and matrix kONES
  float mf[9] = { 1.0f, 1.0f, 1.0f,
                  1.0f, 1.0f, 1.0f,
                  1.0f, 1.0f, 1.0f };
  Matrix3f cst1f(mf);
  EXPECT_TRUE(cst1f == Matrix3f::kONES);

  // Custom constructor 2 and matrix IDENTITY
  //Matrix3f cst2f(Vector3f(1.0f, 0.0f, 0.0f),
  //               Vector3f(0.0f, 1.0f, 0.0f),
  //               Vector3f(0.0f, 0.0f, 1.0f));
  Matrix3f cst2f(1.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 1.0f);
  EXPECT_TRUE(cst2f == Matrix3f::kIDENTITY);

  // Custom constructor 3
  Matrix3f cst3f(1.0f, 2.0f, 7.0f, 
                 4.0f, 5.0f, 6.0f, 
                 3.0f, 8.0f, 9.0f);
  //EXPECT_TRUE(cst3f == Matrix3f(Vector3f(1.0f, 2.0f, 7.0f),
  //                              Vector3f(4.0f, 5.0f, 6.0f),
  //                              Vector3f(3.0f, 8.0f, 9.0f)));


  // Functions
  EXPECT_EQ(cst3f.getDeterminant(), 80.0f);
  EXPECT_TRUE(cst3f.getTranspose() == Matrix3f(1.0f, 4.0f, 3.0f,
                                               2.0f, 5.0f, 8.0f,
                                               7.0f, 6.0f, 9.0f));
  EXPECT_TRUE(cst3f.getInverse() ==  Matrix3f(-0.0375f,  0.475f, -0.2875f, 
                                              -0.225f , -0.15f ,  0.275f, 
                                               0.2125f, -0.025f, -0.0375f));

  Matrix3f temp(1.0f, 2.0f, 7.0f,
                4.0f, 5.0f, 6.0f,
                3.0f, 8.0f, 9.0f);
  temp.transpose();
  EXPECT_TRUE(temp == Matrix3f(1.0f, 4.0f, 3.0f,
                               2.0f, 5.0f, 8.0f,
                               7.0f, 6.0f, 9.0f));
  temp.inverse();
  EXPECT_TRUE(temp == Matrix3f(-0.0375f, -0.225f,  0.2125f,
                                0.475f , -0.15f , -0.025f,
                               -0.2875f,  0.275f, -0.0375f));


  Matrix3f transform;
  transform = Matrix3f::translationMatrix(Vector3f(1.0f, 2.0f, 3.0f));
  EXPECT_TRUE(transform == Matrix3f(1.0f, 0.0f, 1.0f,
                                    0.0f, 1.0f, 2.0f,
                                    0.0f, 0.0f, 3.0f));
  transform = Matrix3f::rotationMatrix(Vector3f(Math::kPI * 0.5f, 
                                                Math::kPI, 
                                                Math::kPI / 3.0f));
  EXPECT_TRUE(transform == Matrix3f(-0.5f      ,  0.0f,  0.8660254f,
                                    -0.8660254f,  0.0f, -0.5f,
                                     0.0f      , -1.0f,  0.0f));
  transform = Matrix3f::scaleMatrix(Vector3f(1.0f, 3.0f, 5.0f));
  EXPECT_TRUE(transform == Matrix3f(1.0f, 0.0f, 0.0f,
                                    0.0f, 3.0f, 0.0f,
                                    0.0f, 0.0f, 5.0f));

  transform = Matrix3f::kIDENTITY;
  transform.translate(Vector3f(2.0f, 4.0f, 1.0f));
  EXPECT_TRUE(transform == Matrix3f(1.0f, 0.0f, 2.0f,
                                    0.0f, 1.0f, 4.0f,
                                    0.0f, 0.0f, 1.0f));
  transform.scale(Vector3f(3.0f, 2.0f, 4.0f));
  EXPECT_TRUE(transform == Matrix3f(3.0f, 0.0f, 8.0f,
                                    0.0f, 2.0f, 16.0f,
                                    0.0f, 0.0f, 4.0f));
  transform.rotate(Vector3f(Math::kPI * 0.5f, Math::kPI, Math::kPI / 3.0f));
  EXPECT_TRUE(transform == Matrix3f(-1.5f      , -8.0f ,  2.5980762f,
                                    -1.7320508f, -16.0f, -1.0f,
                                     0.0f      , -4.0f ,  0.0f));


  // Operators overloads
  EXPECT_TRUE(cst3f + cst2f == Matrix3f(2.0f, 2.0f, 7.0f,
                                        4.0f, 6.0f, 6.0f,
                                        3.0f, 8.0f, 10.0f));
  EXPECT_TRUE(cst3f - cst2f == Matrix3f(0.0f, 2.0f, 7.0f,
                                        4.0f, 4.0f, 6.0f,
                                        3.0f, 8.0f, 8.0f));
  EXPECT_TRUE(cst3f * cst1f == Matrix3f(10.0f, 10.0f, 10.0f,
                                        15.0f, 15.0f, 15.0f,
                                        20.0f, 20.0f, 20.0f));
  EXPECT_TRUE(cst3f * 2 == Matrix3f(2.0f, 4.0f, 14.0f,
                                    8.0f, 10.0f, 12.0f,
                                    6.0f, 16.0f, 18.0f));

  cst3f = cst2f;
  EXPECT_TRUE(cst3f == cst2f);

  cst3f += cst1f;
  EXPECT_TRUE(cst3f == Matrix3f(2.0f, 1.0f, 1.0f,
                                1.0f, 2.0f, 1.0f,
                                1.0f, 1.0f, 2.0f));
  cst3f -= cst1f;
  EXPECT_TRUE(cst3f == Matrix3f(1.0f, 0.0f, 0.0f,
                                0.0f, 1.0f, 0.0f,
                                0.0f, 0.0f, 1.0f));
  cst3f *= cst1f;
  EXPECT_TRUE(cst3f == Matrix3f(1.0f, 1.0f, 1.0f,
                                1.0f, 1.0f, 1.0f, 
                                1.0f, 1.0f, 1.0f ));
  cst3f *= 3;
  EXPECT_TRUE(cst3f == Matrix3f(3.0f, 3.0f, 3.0f,
                                3.0f, 3.0f, 3.0f,
                                3.0f, 3.0f, 3.0f));
}

TEST(eeUtilities, Matrix4)
{
  /* Matrix4f */
  // Size
  EXPECT_EQ(sizeof(Matrix4f), 64);

  // Default constructor and matrix ZERO
  Matrix4f deff = Matrix4f::kZERO;
  EXPECT_TRUE(deff == Matrix4f::kZERO);

  // Custom constructor 1 and matrix ONES
  float mf[16] = { 1.0f, 1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f, 1.0f };
  Matrix4f cst1f(mf);
  EXPECT_TRUE(cst1f == Matrix4f::kONES);

  // Custom constructor 2 and matrix IDENTITY
  //Matrix4f cst2f(Vector4f(1.0f, 0.0f, 0.0f, 0.0f),
  //               Vector4f(0.0f, 1.0f, 0.0f, 0.0f),
  //               Vector4f(0.0f, 0.0f, 1.0f, 0.0f),
  //               Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
  Matrix4f cst2f(1.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f);
  EXPECT_TRUE(cst2f == Matrix4f::kIDENTITY);

  // Custom constructor 3
  Matrix4f cst3f(1.0f, 2.0f, 3.0f, 5.0f,
                 4.0f, 6.0f, 7.0f, 8.0f,
                 8.0f, 7.0f, 6.0f, 5.0f,
                 4.0f, 3.0f, 2.0f, 1.0f);
  //EXPECT_TRUE(cst3f == Matrix4f(Vector4f(1.0f, 2.0f, 3.0f, 5.0f),
  //                              Vector4f(4.0f, 6.0f, 7.0f, 8.0f),
  //                              Vector4f(8.0f, 7.0f, 6.0f, 5.0f),
  //                              Vector4f(4.0f, 3.0f, 2.0f, 1.0f)));


  // Functions
  EXPECT_EQ(cst3f.getDeterminant(), -4.0f);
  EXPECT_TRUE(cst3f.getTranspose() == Matrix4f(1.0f, 4.0f, 8.0f, 4.0f,
                                               2.0f, 6.0f, 7.0f, 3.0f,
                                               3.0f, 7.0f, 6.0f, 2.0f,
                                               5.0f, 8.0f, 5.0f, 1.0f));
  EXPECT_TRUE(cst3f.getInverse() == Matrix4f( 0.0f, -1.0f,  2.25f, -3.25f ,
                                              1.0f,  2.0f, -6.25f,  10.25f,
                                             -2.0f, -1.0f,  5.5f , -9.5f  ,
                                              1.0f,  0.0f, -1.25f,  2.25f  ));

  Matrix4f temp(1.0f, 2.0f, 3.0f, 5.0f,
                4.0f, 6.0f, 7.0f, 8.0f,
                8.0f, 7.0f, 6.0f, 5.0f,
                4.0f, 3.0f, 2.0f, 1.0f);
  temp.transpose();
  EXPECT_TRUE(temp == Matrix4f(1.0f, 4.0f, 8.0f, 4.0f,
                               2.0f, 6.0f, 7.0f, 3.0f,
                               3.0f, 7.0f, 6.0f, 2.0f,
                               5.0f, 8.0f, 5.0f, 1.0f));
  temp.inverse();
  EXPECT_TRUE(temp == Matrix4f( 0.0f ,  1.0f  , -2.0f,  1.0f ,
                               -1.0f ,  2.0f  , -1.0f,  0.0f ,
                                2.25f, -6.25f ,  5.5f, -1.25f,
                               -3.25f,  10.25f, -9.5f,  2.25f ));


  Matrix4f transform;
  transform = Matrix4f::translationMatrix(Vector3f(1.0f, 2.0f, 3.0f));
  EXPECT_TRUE(transform == Matrix4f(1.0f, 0.0f, 0.0f, 1.0f,
                                    0.0f, 1.0f, 0.0f, 2.0f,
                                    0.0f, 0.0f, 1.0f, 3.0f,
                                    0.0f, 0.0f, 0.0f, 1.0f));
  transform = Matrix4f::rotationMatrix(Vector3f(Math::kPI * 0.5f,
                                                Math::kPI,
                                                Math::kPI / 3.0f));
  EXPECT_TRUE(transform == Matrix4f(-0.5f      ,  0.0f,  0.8660254f, 0.0f,
                                    -0.8660254f,  0.0f, -0.5f      , 0.0f,
                                     0.0f      , -1.0f,  0.0f      , 0.0f,
                                     0.0f      ,  0.0f,  0.0f      , 1.0f));
  transform = Matrix4f::scaleMatrix(Vector3f(1.0f, 3.0f, 5.0f));
  EXPECT_TRUE(transform == Matrix4f(1.0f, 0.0f, 0.0f, 0.0f,
                                    0.0f, 3.0f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 5.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f, 1.0f));

  transform = Matrix4f::kIDENTITY;
  transform.translate(Vector3f(2.0f, 4.0f, 1.0f));
  EXPECT_TRUE(transform == Matrix4f(1.0f, 0.0f, 0.0f, 2.0f,
                                    0.0f, 1.0f, 0.0f, 4.0f,
                                    0.0f, 0.0f, 1.0f, 1.0f,
                                    0.0f, 0.0f, 0.0f, 1.0f));
  transform.scale(Vector3f(3.0f, 2.0f, 4.0f));
  EXPECT_TRUE(transform == Matrix4f(3.0f, 0.0f, 0.0f, 2.0f,
                                    0.0f, 2.0f, 0.0f, 4.0f,
                                    0.0f, 0.0f, 4.0f, 1.0f,
                                    0.0f, 0.0f, 0.0f, 1.0f));
  transform.rotate(Vector3f(Math::kPI * 0.5f, Math::kPI, Math::kPI / 3.0f));
  EXPECT_TRUE(transform == Matrix4f(-1.5f      ,  0.0f,  2.5980762f, 2.0f,
                                    -1.7320508f,  0.0f, -1.0f      , 4.0f,
                                     0.0f      , -4.0f,  0.0f      , 1.0f,
                                     0.0f      ,  0.0f,  0.0f      , 1.0f));


  // Operators overloads
  EXPECT_TRUE(cst3f + cst2f == Matrix4f(2.0f, 2.0f, 3.0f, 5.0f,
                                        4.0f, 7.0f, 7.0f, 8.0f,
                                        8.0f, 7.0f, 7.0f, 5.0f,
                                        4.0f, 3.0f, 2.0f, 2.0f));
  EXPECT_TRUE(cst3f - cst1f == Matrix4f(0.0f, 1.0f, 2.0f, 4.0f,
                                        3.0f, 5.0f, 6.0f, 7.0f,
                                        7.0f, 6.0f, 5.0f, 4.0f,
                                        3.0f, 2.0f, 1.0f, 0.0f));
  EXPECT_TRUE(cst3f * cst1f == Matrix4f(11.0f, 11.0f, 11.0f, 11.0f,
                                        25.0f, 25.0f, 25.0f, 25.0f,
                                        26.0f, 26.0f, 26.0f, 26.0f,
                                        10.0f, 10.0f, 10.0f, 10.0f));
  EXPECT_TRUE(cst3f * 2 == Matrix4f( 2.0f,  4.0f,  6.0f, 10.0f,
                                     8.0f, 12.0f, 14.0f, 16.0f,
                                    16.0f, 14.0f, 12.0f, 10.0f,
                                     8.0f,  6.0f,  4.0f, 2.0f));

  cst3f = cst2f;
  EXPECT_TRUE(cst3f == cst2f);

  cst3f += cst1f;
  EXPECT_TRUE(cst3f == Matrix4f(2.0f, 1.0f, 1.0f, 1.0f,
                                1.0f, 2.0f, 1.0f, 1.0f,
                                1.0f, 1.0f, 2.0f, 1.0f,
                                1.0f, 1.0f, 1.0f, 2.0f));
  cst3f -= cst1f;
  EXPECT_TRUE(cst3f == Matrix4f(1.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 1.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 1.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 1.0f));
  cst3f *= cst1f;
  EXPECT_TRUE(cst3f == Matrix4f(1.0f, 1.0f, 1.0f, 1.0f,
                                1.0f, 1.0f, 1.0f, 1.0f,
                                1.0f, 1.0f, 1.0f, 1.0f,
                                1.0f, 1.0f, 1.0f, 1.0f));
  cst3f *= 3;
  EXPECT_TRUE(cst3f == Matrix4f(3.0f, 3.0f, 3.0f, 3.0f,
                                3.0f, 3.0f, 3.0f, 3.0f,
                                3.0f, 3.0f, 3.0f, 3.0f,
                                3.0f, 3.0f, 3.0f, 3.0f));
}

TEST(eeUtilities, Shapes)
{
  EXPECT_EQ(sizeof(Plane), 16);

  Plane p(Vector3f(1.0f,1.0f,1.0f), Vector3f(2.0f,-3.0f,4.0f));

  EXPECT_TRUE(p.getPoint() == Vector3f(0.0f, 0.0f, 0.75f));
  EXPECT_TRUE(p.getNormal() == Vector3f(2.0f, -3.0f, 4.0f).getNormalize());

  p.move(Vector3f(-1.0f, 2.0f, 1.0f));
  EXPECT_TRUE(p.getPoint() == Vector3f(0.0f, 0.0f, -0.25f));
  p.rotate(Vector3f(Math::kPI, 0.0f, 0.0f));
  EXPECT_TRUE(p.getNormal() == Vector3f(0.37139067f, 0.55778611f, -0.74278128f));


  p.setPoint(Vector3f(-1.0f, 2.0f, 1.0f));
  EXPECT_TRUE(p.getPoint() == Vector3f(0.0f, 0.0f, 0.0f));
  p.setNormal(Vector3f(1.0f, 0.0f, 0.0f));
  EXPECT_TRUE(p.getNormal() == Vector3f(1.0f, 0.0f, 0.0f).getNormalize());


  EXPECT_EQ(sizeof(Sphere), 16);

  Sphere s(Vector3f(2.0f, -1.0f, 3.0f), 5.0f);

  EXPECT_TRUE(s.getCenter() == Vector3f(2.0f, -1.0f, 3.0f));
  EXPECT_EQ(s.getRadious(), 5.0f);

  s.move(Vector3f(1.0f, 1.0f, 1.0f));
  EXPECT_TRUE(s.getCenter() == Vector3f(3.0f, 0.0f, 4.0f));

  s.setCenter(Vector3f(2.0f, -4.0f, -2.0f));
  EXPECT_TRUE(s.getCenter() == Vector3f(2.0f, -4.0f, -2.0f));
  s.setRadious(3.0f);
  EXPECT_EQ(s.getRadious(), 3.0f);

  
  EXPECT_EQ(sizeof(BoxAAB), 24);

  BoxAAB b(Vector3f(2.0f, 2.0f, 2.0f), Vector3f(1.0f, 2.0f, 3.0f));

  EXPECT_TRUE(b.getA() == Vector3f(2.0f, 2.0f, 2.0f));
  EXPECT_TRUE(b.getB() == Vector3f(3.0f, 4.0f, 5.0f));
  EXPECT_TRUE(b.getSize() == Vector3f(1.0f, 2.0f, 3.0f));

  b.move(Vector3f(-1.0f, -2.0f, -3.0f));
  EXPECT_TRUE(b.getA() == Vector3f(1.0f, 0.0f, -1.0f));
  EXPECT_TRUE(b.getB() == Vector3f(2.0f, 2.0f, 2.0f));

  b.setA(Vector3f(3.0f, 2.0f, 1.0f));
  EXPECT_TRUE(b.getA() == Vector3f(3.0f, 2.0f, 1.0f));
  EXPECT_TRUE(b.getB() == Vector3f(4.0f, 4.0f, 4.0f));

  b.setSize(Vector3f(3.0f, 1.0f, 3.0f));
  EXPECT_TRUE(b.getB() == Vector3f(6.0f, 3.0f, 4.0f));
  EXPECT_TRUE(b.getSize() == Vector3f(3.0f, 1.0f, 3.0f));


  EXPECT_EQ(sizeof(Capsule), 20);

  Capsule c(Vector3f(2.0f, 1.0f, -3.0f), 2.0f, 1.0f);

  EXPECT_TRUE(c.getCenter() == Vector3f(2.0f, 1.0f, -3.0f));
  EXPECT_TRUE(c.getHeight() == 2.0f);
  EXPECT_TRUE(c.getRadious() == 1.0f);

  c.move(Vector3f(-3.0f, 2.0f, 1.0f));
  EXPECT_TRUE(c.getCenter() == Vector3f(-1.0f, 3.0f, -2.0f));

  c.setCenter(Vector3f(1.0f, 1.0f, -2.0f));
  EXPECT_TRUE(c.getCenter() == Vector3f(1.0f, 1.0f, -2.0f));
  c.setHeight(10.0f);
  EXPECT_TRUE(c.getHeight() == 10.0f);
  c.setRadious(2.0f);
  EXPECT_TRUE(c.getRadious() == 2.0f);


  EXPECT_EQ(sizeof(Rectangle), 16);

  Rectangle r(Vector2f(2.0f,3.0f), Vector2f(3.0f, 4.0f));

  EXPECT_TRUE(r.getA() == Vector2f(2.0f, 3.0f));
  EXPECT_TRUE(r.getB() == Vector2f(5.0f, 7.0f));
  EXPECT_TRUE(r.getSize() == Vector2f(3.0f, 4.0f));

  r.move(Vector2f(1.0f, -2.0f));
  EXPECT_TRUE(r.getA() == Vector2f(3.0f, 1.0f));
  EXPECT_TRUE(r.getB() == Vector2f(6.0f, 5.0f));

  r.setA(Vector2f(0.0f, -1.0f));
  EXPECT_TRUE(r.getA() == Vector2f(0.0f, -1.0f));
  EXPECT_TRUE(r.getB() == Vector2f(3.0f, 3.0f));

  r.setSize(Vector2f(1.0f, 1.0f));
  EXPECT_TRUE(r.getB() == Vector2f(1.0f, 0.0f));
  EXPECT_TRUE(r.getSize() == Vector2f(1.0f, 1.0f));


  EXPECT_TRUE(r.intersects(Vector2f(0.5f, -0.5f)));
  EXPECT_TRUE(r.intersects(Rectangle(Vector2f(-1.0f, -0.5f), 
                                     Vector2f(4.0f, 4.0f))));


  EXPECT_TRUE(p.intersects(Vector3f(0.0f, 4.0f, 3.0f)));
  EXPECT_TRUE(p.intersects(Plane(Vector3f(0.0f, 1.0f, 2.0f), 
                                 Vector3f(1.0f, 2.0f, 3.0f))));
  EXPECT_TRUE(s.intersects(Vector3f(2.0f, -3.0f, -1.0f)));
  EXPECT_TRUE(s.intersects(p));
  EXPECT_TRUE(s.intersects(Sphere(Vector3f(0.0f, -4.0f, 2.0f), 3.0f)));
  EXPECT_FALSE(b.intersects(Vector3f(2.0f, -3.0f, -1.0f)));
  EXPECT_FALSE(b.intersects(p));
  EXPECT_FALSE(b.intersects(s));
  EXPECT_FALSE(b.intersects(BoxAAB(Vector3f(4.0f, 3.0f, 0.0f),
                                   Vector3f(4.0f, 5.0f, 0.5f))));
  EXPECT_TRUE(c.intersects(Vector3f(2.0f, -3.0f, -1.0f)));
  EXPECT_TRUE(c.intersects(p));
  EXPECT_TRUE(c.intersects(s));
  //EXPECT_TRUE(c.intersects(b));
  EXPECT_TRUE(c.intersects(Capsule(Vector3f(3.0f, 5.0f, -3.0f), 8.0f, 2.0f)));
}

TEST(eeUtilities, Quaternions)
{
  Quaternion q1(1.2f, 3.4f, 1.13f, -0.5f);

  EXPECT_TRUE(q1.getConjugate() == Quaternion(1.2f, -3.4f, -1.13f, 0.5f));
  q1.conjugate();
  EXPECT_TRUE(q1 == Quaternion(1.2f, -3.4f, -1.13f, 0.5f));

  Quaternion q2(Vector3f(2.0f, 1.0f, 3.0f));

  EXPECT_TRUE(q2.getEuclidean() == Vector3f(2.0f, 1.0f, 3.0f));
}

int main(int argc, char** argv) {
  int stop;
  ::testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  std::cin >> stop;
  return 0;
}