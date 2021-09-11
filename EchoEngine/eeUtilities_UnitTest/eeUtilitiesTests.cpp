#include "../eeUtilities/include/eePrerequisitesUtilities.h"

#include <gtest/gtest.h>

#include "../eeUtilities/include/eeVector2.h"
#include "../eeUtilities/include/eeVector3.h"
#include "../eeUtilities/include/eeVector4.h"

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
  EXPECT_EQ(sizeof(eeEngineSDK::SIZE_T), 8);
}

TEST(eeUtilities, Vector2)
{
  /* Vector2f */
  // Default constructor
  eeEngineSDK::Vector2f vf;
  EXPECT_EQ(vf, eeEngineSDK::Vector2f::ZERO);

  // operator=
  vf = eeEngineSDK::Vector2f(-3.0f, 1.0f);
  EXPECT_EQ(vf, eeEngineSDK::Vector2f(-3.0f, 1.0f));

  // Custom constructor constructor
  eeEngineSDK::Vector2f vf2(-3.0f, 4.0f);
  EXPECT_EQ(vf2, eeEngineSDK::Vector2f(-3.0f, 4.0f));

  // Functions
  EXPECT_EQ(vf.dot(vf2), 13.0f);

  EXPECT_EQ(vf.distance(vf2), 3.0f);
  EXPECT_EQ(vf2.length(), 5.0f);
  EXPECT_TRUE(vf.normalize() == eeEngineSDK::Vector2f(-0.948683f, 0.316228f));
  EXPECT_TRUE(vf.truncate(7.0f) == eeEngineSDK::Vector2f(-6.64078309f, 2.21359436f));

  // Operators with other vectors
  //vf =  {-3.0f,  1.0f}
  //vf2 = {-3.0f,  4.0f}
  EXPECT_TRUE(vf + vf2 == eeEngineSDK::Vector2f(-6.0f,  5.0f));
  EXPECT_TRUE(vf - vf2 == eeEngineSDK::Vector2f( 0.0f, -3.0f));
  EXPECT_TRUE(vf * vf2 == eeEngineSDK::Vector2f( 9.0f,  4.0f));
  EXPECT_TRUE(vf / vf2 == eeEngineSDK::Vector2f( 1.0f,  0.25f));
  EXPECT_TRUE(vf % vf2 == eeEngineSDK::Vector2f( 0.0f,  1.0f));

  // Operetors with numbers
  EXPECT_TRUE(vf + 1.0f == eeEngineSDK::Vector2f(-2.0f,  2.0f));
  EXPECT_TRUE(vf - 2.0f == eeEngineSDK::Vector2f(-5.0f, -1.0f));
  EXPECT_TRUE(vf * 3.0f == eeEngineSDK::Vector2f(-9.0f,  3.0f));
  EXPECT_TRUE(vf / 2.0f == eeEngineSDK::Vector2f(-1.5f,  0.5f));
  EXPECT_TRUE(vf % 1.5f == eeEngineSDK::Vector2f( 0.0f,  1.0f));


  // Asign operators with other vectors
  vf += vf2;
  EXPECT_TRUE(vf == eeEngineSDK::Vector2f(-6.0f,  5.0f));
  vf -= vf2;
  EXPECT_TRUE(vf == eeEngineSDK::Vector2f(-3.0f,  1.0f));
  vf *= vf2;
  EXPECT_TRUE(vf == eeEngineSDK::Vector2f( 9.0f,  4.0f));
  vf /= vf2;
  EXPECT_TRUE(vf == eeEngineSDK::Vector2f(-3.0f,  1.0f));
  vf %= vf2;
  EXPECT_TRUE(vf == eeEngineSDK::Vector2f( 0.0f,  1.0f));

  // Asign operators with numbers
  vf += 1.0f;
  EXPECT_TRUE(vf == eeEngineSDK::Vector2f( 1.0f,  2.0f));
  vf -= 3.0f;
  EXPECT_TRUE(vf == eeEngineSDK::Vector2f(-2.0f, -1.0f));
  vf *= 3.0f;
  EXPECT_TRUE(vf == eeEngineSDK::Vector2f(-6.0f, -3.0f));
  vf /= 2.0f;
  EXPECT_TRUE(vf == eeEngineSDK::Vector2f(-3.0f, -1.5f));
  vf %= 2.0f;
  EXPECT_TRUE(vf == eeEngineSDK::Vector2f(-1.0f, -1.5f));


  // Logic operators
  EXPECT_TRUE(vf != vf2);
  EXPECT_FALSE(vf > vf2);
  EXPECT_FALSE(vf >= vf2);
  EXPECT_TRUE(vf < vf2);
  EXPECT_TRUE(vf <= vf2);



  /* Vector2i */
  // Default constructor
  eeEngineSDK::Vector2i vi;
  EXPECT_EQ(vi, eeEngineSDK::Vector2i::ZERO);

  // operator=
  vi = eeEngineSDK::Vector2i(-3, 1);
  EXPECT_EQ(vi, eeEngineSDK::Vector2i(-3, 1));

  // Custom constructor constructor
  eeEngineSDK::Vector2i vi2(-3, 4);
  EXPECT_EQ(vi2, eeEngineSDK::Vector2i(-3, 4));

  // Functions
  EXPECT_EQ(vi.dot(vi2), 13.0f);

  EXPECT_EQ(vi.distance(vi2), 3.0f);
  EXPECT_EQ(vi2.length(), 5.0f);
  EXPECT_TRUE(vi.normalize() == eeEngineSDK::Vector2f(-0.948683f, 0.316228f));
  EXPECT_TRUE(vi.truncate(7.0f) == eeEngineSDK::Vector2f(-6.64078309f, 2.21359436f));

  // Operators with other vectors
  //vi  = {-3,  1}
  //vi2 = {-3,  4}
  EXPECT_TRUE(vi + vi2 == eeEngineSDK::Vector2i(-6,  5));
  EXPECT_TRUE(vi - vi2 == eeEngineSDK::Vector2i( 0, -3));
  EXPECT_TRUE(vi * vi2 == eeEngineSDK::Vector2i( 9,  4));
  EXPECT_TRUE(vi / vi2 == eeEngineSDK::Vector2i( 1,  0));
  EXPECT_TRUE(vi % vi2 == eeEngineSDK::Vector2i( 0,  1));

  // Operetors with numbers
  EXPECT_TRUE(vi + 1 == eeEngineSDK::Vector2i(-2,  2));
  EXPECT_TRUE(vi - 2 == eeEngineSDK::Vector2i(-5, -1));
  EXPECT_TRUE(vi * 3 == eeEngineSDK::Vector2i(-9,  3));
  EXPECT_TRUE(vi / 2 == eeEngineSDK::Vector2i(-1,  0));
  EXPECT_TRUE(vi % 2 == eeEngineSDK::Vector2i(-1,  1));


  // Asign operators with other vectors
  vi += vi2;
  EXPECT_TRUE(vi == eeEngineSDK::Vector2i(-6,  5));
  vi -= vi2;
  EXPECT_TRUE(vi == eeEngineSDK::Vector2i(-3,  1));
  vi *= vi2;
  EXPECT_TRUE(vi == eeEngineSDK::Vector2i( 9,  4));
  vi /= vi2;
  EXPECT_TRUE(vi == eeEngineSDK::Vector2i(-3,  1));
  vi %= vi2;
  EXPECT_TRUE(vi == eeEngineSDK::Vector2i( 0,  1));

  // Asign operators with numbers
  vi += 1;
  EXPECT_TRUE(vi == eeEngineSDK::Vector2i( 1,  2));
  vi -= 3;
  EXPECT_TRUE(vi == eeEngineSDK::Vector2i(-2, -1));
  vi *= 3;
  EXPECT_TRUE(vi == eeEngineSDK::Vector2i(-6, -3));
  vi /= 2;
  EXPECT_TRUE(vi == eeEngineSDK::Vector2i(-3, -1));
  vi %= 2;
  EXPECT_TRUE(vi == eeEngineSDK::Vector2i(-1, -1));


  // Logic operators
  EXPECT_TRUE(vi != vi2);
  EXPECT_FALSE(vi > vi2);
  EXPECT_FALSE(vi >= vi2);
  EXPECT_TRUE(vi < vi2);
  EXPECT_TRUE(vi <= vi2);



  /* Vector2u */
  // Default constructor
  eeEngineSDK::Vector2u vu;
  EXPECT_EQ(vu, eeEngineSDK::Vector2u::ZERO);

  // operator=
  vu = eeEngineSDK::Vector2u(3, 1);
  EXPECT_EQ(vu, eeEngineSDK::Vector2u(3, 1));

  // Custom constructor constructor
  eeEngineSDK::Vector2u vu2(3, 4);
  EXPECT_EQ(vu2, eeEngineSDK::Vector2u(3, 4));

  // Functions
  EXPECT_EQ(vu.dot(vu2), 13.0f);

  EXPECT_EQ(vu.distance(vu2), 3.0f);
  EXPECT_EQ(vu2.length(), 5.0f);
  EXPECT_TRUE(vu.normalize() == eeEngineSDK::Vector2f(0.948683f, 0.316228f));
  EXPECT_TRUE(vu.truncate(7.0f) == eeEngineSDK::Vector2f(6.64078309f, 2.21359436f));

  // Operators with other vectors
  //vu  = {3, 1}
  //vu2 = {3, 4}
  EXPECT_TRUE(vu + vu2 == eeEngineSDK::Vector2u(6, 5));
  EXPECT_TRUE(vu2 - vu == eeEngineSDK::Vector2u(0, 3));
  EXPECT_TRUE(vu * vu2 == eeEngineSDK::Vector2u(9, 4));
  EXPECT_TRUE(vu2 / vu == eeEngineSDK::Vector2u(1, 4));
  EXPECT_TRUE(vu % vu2 == eeEngineSDK::Vector2u(0, 1));

  // Operetors with numbers
  EXPECT_TRUE(vu  + 1u == eeEngineSDK::Vector2u(4, 2));
  EXPECT_TRUE(vu2 - 2u == eeEngineSDK::Vector2u(1, 2));
  EXPECT_TRUE(vu  * 3u == eeEngineSDK::Vector2u(9, 3));
  EXPECT_TRUE(vu  / 2u == eeEngineSDK::Vector2u(1, 0));
  EXPECT_TRUE(vu  % 2u == eeEngineSDK::Vector2u(1, 1));


  // Asign operators with other vectors
  vu += vu2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector2u(6, 5));
  vu -= vu2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector2u(3, 1));
  vu *= vu2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector2u(9, 4));
  vu /= vu2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector2u(3, 1));
  vu %= vu2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector2u(0, 1));

  // Asign operators with numbers
  vu += 1u;
  EXPECT_TRUE(vu  == eeEngineSDK::Vector2u(1, 2));
  vu2 -= 3u;
  EXPECT_TRUE(vu2 == eeEngineSDK::Vector2u(0, 1));
  vu *= 3u;
  EXPECT_TRUE(vu  == eeEngineSDK::Vector2u(3, 6));
  vu /= 2u;
  EXPECT_TRUE(vu  == eeEngineSDK::Vector2u(1, 3));
  vu %= 2u;
  EXPECT_TRUE(vu  == eeEngineSDK::Vector2u(1, 1));


  // Logic operators
  EXPECT_TRUE(vu != vu2);
  EXPECT_TRUE(vu > vu2);
  EXPECT_TRUE(vu >= vu2);
  EXPECT_FALSE(vu < vu2);
  EXPECT_FALSE(vu <= vu2);
}

TEST(eeUtilities, Vector3)
{
  /* Vector3f */
  // Default constructor
  eeEngineSDK::Vector3f vf;
  EXPECT_EQ(vf, eeEngineSDK::Vector3f::ZERO);
  
  // operator=
  vf = eeEngineSDK::Vector3f(2.0f, 2.0f, -6.0f);
  EXPECT_EQ(vf, eeEngineSDK::Vector3f(2.0f, 2.0f, -6.0f));
  
  // Custom constructor constructor
  eeEngineSDK::Vector3f vf2(-1.0f, 2.0f, -2.0f);
  EXPECT_EQ(vf2, eeEngineSDK::Vector3f(-1.0f, 2.0f, -2.0f));
  
  // Functions
  EXPECT_EQ(vf.dot(vf2), 14.0f);
  EXPECT_TRUE(vf.cross(vf2) == eeEngineSDK::Vector3f( 8.0f,  10.0f,  6.0f));
  
  EXPECT_EQ(vf.distance(vf2), 5.0f);
  EXPECT_EQ(vf2.length(), 3.0f);
  EXPECT_TRUE(vf.normalize() == eeEngineSDK::Vector3f( 0.30151134f,  0.30151134f, -0.90453403f));
  EXPECT_TRUE(vf.truncate(7.0f) == eeEngineSDK::Vector3f( 2.11057941f,  2.11057941f, -6.33173824f));
  
  // Operators with other vectors
  //vf =  { 2.0f,  2.0f, -6.0f}
  //vf2 = {-1.0f,  2.0f, -2.0f}
  EXPECT_TRUE(vf + vf2 == eeEngineSDK::Vector3f( 1.0f,  4.0f, -8.0f));
  EXPECT_TRUE(vf - vf2 == eeEngineSDK::Vector3f( 3.0f,  0.0f, -4.0f));
  EXPECT_TRUE(vf * vf2 == eeEngineSDK::Vector3f(-2.0f,  4.0f,  12.0f));
  EXPECT_TRUE(vf / vf2 == eeEngineSDK::Vector3f(-2.0f,  1.0f,  3.0f));
  EXPECT_TRUE(vf % vf2 == eeEngineSDK::Vector3f( 0.0f,  0.0f,  0.0f));
  
  // Operetors with numbers
  EXPECT_TRUE(vf + 1.0f == eeEngineSDK::Vector3f( 3.0f,  3.0f, -5.0f));
  EXPECT_TRUE(vf - 2.0f == eeEngineSDK::Vector3f( 0.0f,  0.0f, -8.0f));
  EXPECT_TRUE(vf * 3.0f == eeEngineSDK::Vector3f( 6.0f,  6.0f, -18.0f));
  EXPECT_TRUE(vf / 2.0f == eeEngineSDK::Vector3f( 1.0f,  1.0f, -3.0f));
  EXPECT_TRUE(vf % 1.5f == eeEngineSDK::Vector3f( 0.5f,  0.5f,  0.0f));
  
  
  // Asign operators with other vectors
  vf += vf2;
  EXPECT_TRUE(vf == eeEngineSDK::Vector3f( 1.0f,  4.0f, -8.0f));
  vf -= vf2;
  EXPECT_TRUE(vf == eeEngineSDK::Vector3f( 2.0f,  2.0f, -6.0f));
  vf /= vf2;
  EXPECT_TRUE(vf == eeEngineSDK::Vector3f(-2.0f,  1.0f,  3.0f));
  vf *= vf2;
  EXPECT_TRUE(vf == eeEngineSDK::Vector3f( 2.0f,  2.0f, -6.0f));
  vf %= vf2;
  EXPECT_TRUE(vf == eeEngineSDK::Vector3f( 0.0f,  0.0f,  0.0f));
   
  // Asign operators with numbers
  vf += 1.0f;
  EXPECT_TRUE(vf == eeEngineSDK::Vector3f( 1.0f,  1.0f,  1.0f));
  vf -= 3.0f;
  EXPECT_TRUE(vf == eeEngineSDK::Vector3f(-2.0f, -2.0f, -2.0f));
  vf *= 3.0f;									 	    
  EXPECT_TRUE(vf == eeEngineSDK::Vector3f(-6.0f, -6.0f, -6.0f));
  vf /= 2.0f;									 	    
  EXPECT_TRUE(vf == eeEngineSDK::Vector3f(-3.0f, -3.0f, -3.0f));
  vf %= 2.0f;									 	    
  EXPECT_TRUE(vf == eeEngineSDK::Vector3f(-1.0f, -1.0f, -1.0f));
  
  
  // Logic operators
  EXPECT_TRUE(vf != vf2);
  EXPECT_FALSE(vf > vf2);
  EXPECT_FALSE(vf >= vf2);
  EXPECT_TRUE(vf < vf2);
  EXPECT_TRUE(vf <= vf2);



  /* Vector3i */
  // Default constructor
  eeEngineSDK::Vector3i vi;
  EXPECT_EQ(vi, eeEngineSDK::Vector3i::ZERO);

  // operator=
  vi = eeEngineSDK::Vector3i(2, 2, -6);
  EXPECT_EQ(vi, eeEngineSDK::Vector3i(2, 2, -6));

  // Custom constructor constructor
  eeEngineSDK::Vector3i vi2(-1, 2, -2);
  EXPECT_EQ(vi2, eeEngineSDK::Vector3i(-1, 2, -2));

  // Functions
  EXPECT_EQ(vi.dot(vi2), 14.0f);
  EXPECT_TRUE(vi.cross(vi2) == eeEngineSDK::Vector3f(8.0f, 10.0f, 6.0f));

  EXPECT_EQ(vi.distance(vi2), 5.0f);
  EXPECT_EQ(vi2.length(), 3.0f);
  EXPECT_TRUE(vi.normalize() == eeEngineSDK::Vector3f(0.30151134f, 0.30151134f, -0.90453403f));
  EXPECT_TRUE(vi.truncate(7.0f) == eeEngineSDK::Vector3f(2.11057941f, 2.11057941f, -6.33173824f));

  // Operators with other vectors
  //vi =  { 2,  2, -6}
  //vi2 = {-1,  2, -2}
  EXPECT_TRUE(vi + vi2 == eeEngineSDK::Vector3i( 1,  4, -8));
  EXPECT_TRUE(vi - vi2 == eeEngineSDK::Vector3i( 3,  0, -4));
  EXPECT_TRUE(vi * vi2 == eeEngineSDK::Vector3i(-2,  4,  12));
  EXPECT_TRUE(vi / vi2 == eeEngineSDK::Vector3i(-2,  1,  3));
  EXPECT_TRUE(vi % vi2 == eeEngineSDK::Vector3i( 0,  0,  0));

  // Operetors with numbers
  EXPECT_TRUE(vi + 1 == eeEngineSDK::Vector3i( 3,  3, -5));
  EXPECT_TRUE(vi - 2 == eeEngineSDK::Vector3i( 0,  0, -8));
  EXPECT_TRUE(vi * 3 == eeEngineSDK::Vector3i( 6,  6, -18));
  EXPECT_TRUE(vi / 2 == eeEngineSDK::Vector3i( 1,  1, -3));
  EXPECT_TRUE(vi % 3 == eeEngineSDK::Vector3i( 2,  2,  0));


  // Asign operators with other vectors
  vi += vi2;
  EXPECT_TRUE(vi == eeEngineSDK::Vector3i( 1,  4, -8));
  vi -= vi2;							   	   
  EXPECT_TRUE(vi == eeEngineSDK::Vector3i( 2,  2, -6));
  vi /= vi2;							   	   
  EXPECT_TRUE(vi == eeEngineSDK::Vector3i(-2,  1,  3));
  vi *= vi2;							   	   
  EXPECT_TRUE(vi == eeEngineSDK::Vector3i( 2,  2, -6));
  vi %= vi2;							   	   
  EXPECT_TRUE(vi == eeEngineSDK::Vector3i( 0,  0,  0));

  // Asign operators with numbers
  vi += 1;
  EXPECT_TRUE(vi == eeEngineSDK::Vector3i( 1,  1,  1));
  vi -= 3;
  EXPECT_TRUE(vi == eeEngineSDK::Vector3i(-2, -2, -2));
  vi *= 3;
  EXPECT_TRUE(vi == eeEngineSDK::Vector3i(-6, -6, -6));
  vi /= 2;
  EXPECT_TRUE(vi == eeEngineSDK::Vector3i(-3, -3, -3));
  vi %= 2;
  EXPECT_TRUE(vi == eeEngineSDK::Vector3i(-1, -1, -1));


  // Logic operators
  EXPECT_TRUE(vi != vi2);
  EXPECT_FALSE(vi > vi2);
  EXPECT_FALSE(vi >= vi2);
  EXPECT_TRUE(vi < vi2);
  EXPECT_TRUE(vi <= vi2);



  /* Vector3u */
  // Default constructor
  eeEngineSDK::Vector3u vu;
  EXPECT_EQ(vu, eeEngineSDK::Vector3u::ZERO);

  // operator=
  vu = eeEngineSDK::Vector3u(4, 2, 6);
  EXPECT_EQ(vu, eeEngineSDK::Vector3u(4, 2, 6));

  // Custom constructor constructor
  eeEngineSDK::Vector3u vu2(1, 2, 2);
  EXPECT_EQ(vu2, eeEngineSDK::Vector3u(1, 2, 2));

  // Functions
  EXPECT_EQ(vu.dot(vu2), 20.0f);
  EXPECT_TRUE(vu.cross(vu2) == eeEngineSDK::Vector3f(-8.0f, -2.0f,  6.0f));

  EXPECT_EQ(vu.distance(vu2), 5.0f);
  EXPECT_EQ(vu2.length(), 3.0f);
  EXPECT_TRUE(vu.normalize() == eeEngineSDK::Vector3f(0.53452248f, 0.26726124f, 0.80178373f));
  EXPECT_TRUE(vu.truncate(7.0f) == eeEngineSDK::Vector3f(3.74165739f, 1.87082869f, 5.61248608f));

  // Operators with other vectors
  //vu =  {4, 2, 6}
  //vu2 = {1, 2, 2}
  EXPECT_TRUE(vu + vu2 == eeEngineSDK::Vector3u(5, 4, 8));
  EXPECT_TRUE(vu - vu2 == eeEngineSDK::Vector3u(3, 0, 4));
  EXPECT_TRUE(vu * vu2 == eeEngineSDK::Vector3u(4, 4, 12));
  EXPECT_TRUE(vu / vu2 == eeEngineSDK::Vector3u(4, 1, 3));
  EXPECT_TRUE(vu % vu2 == eeEngineSDK::Vector3u(0, 0, 0));

  // Operetors with numbers
  EXPECT_TRUE(vu + 1 == eeEngineSDK::Vector3u(5, 3, 7));
  EXPECT_TRUE(vu - 2 == eeEngineSDK::Vector3u(2, 0, 4));
  EXPECT_TRUE(vu * 3 == eeEngineSDK::Vector3u(12, 6, 18));
  EXPECT_TRUE(vu / 2 == eeEngineSDK::Vector3u(2, 1, 3));
  EXPECT_TRUE(vu % 3 == eeEngineSDK::Vector3u(1, 2, 0));


  // Asign operators with other vectors
  vu += vu2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector3u(5, 4, 8));
  vu -= vu2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector3u(4, 2, 6));
  vu /= vu2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector3u(4, 1, 3));
  vu *= vu2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector3u(4, 2, 6));
  vu %= vu2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector3u(0, 0, 0));

  // Asign operators with numbers
  vu += 2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector3u(2, 2, 2));
  vu -= 1;
  EXPECT_TRUE(vu == eeEngineSDK::Vector3u(1, 1, 1));
  vu *= 3;
  EXPECT_TRUE(vu == eeEngineSDK::Vector3u(3, 3, 3));
  vu /= 2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector3u(1, 1, 1));
  vu %= 2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector3u(1, 1, 1));


  // Logic operators
  EXPECT_TRUE(vu != vu2);
  EXPECT_FALSE(vu > vu2);
  EXPECT_FALSE(vu >= vu2);
  EXPECT_TRUE(vu < vu2);
  EXPECT_TRUE(vu <= vu2);
}

TEST(eeUtilities, Vector4)
{
	/* Vector4f */
	// Default constructor
	eeEngineSDK::Vector4f vf;
	EXPECT_EQ(vf, eeEngineSDK::Vector4f::ZERO);

	// operator=
	vf = eeEngineSDK::Vector4f(-7.0f, 4.0f, 6.0f, -4.0f);
	EXPECT_EQ(vf, eeEngineSDK::Vector4f(-7.0f, 4.0f, 6.0f, -4.0f));

	// Custom constructor constructor
	eeEngineSDK::Vector4f vf2(-5.0f, 2.0f, 4.0f, -6.0f);
	EXPECT_EQ(vf2, eeEngineSDK::Vector4f(-5.0f, 2.0f, 4.0f, -6.0f));

	// Functions
	EXPECT_EQ(vf.dot(vf2), 91.0f);

	EXPECT_EQ(vf.distance(vf2), 4.0f);
	EXPECT_EQ(vf2.length(), 9.0f);
	EXPECT_TRUE(vf.normalize() == eeEngineSDK::Vector4f(-0.64715023f,  0.36980013f,  0.55470020f, -0.36980013f));
	EXPECT_TRUE(vf.truncate(7.0f) == eeEngineSDK::Vector4f(-4.53005160f,  2.58860092f,  3.88290137f, -2.58860092f));

	// Operators with other vectors
	//vf  = {-7.0f,  4.0f,  6.0f, -4.0f}
	//vf2 = {-5.0f,  2.0f,  4.0f, -6.0f}
	EXPECT_TRUE(vf + vf2 == eeEngineSDK::Vector4f(-12.0f,  6.0f,  10.0f, -10.0f));
	EXPECT_TRUE(vf - vf2 == eeEngineSDK::Vector4f(-2.0f,   2.0f,  2.0f,   2.0f));
	EXPECT_TRUE(vf * vf2 == eeEngineSDK::Vector4f( 35.0f,  8.0f,  24.0f,  24.0f));
	EXPECT_TRUE(vf / vf2 == eeEngineSDK::Vector4f( 1.4f,   2.0f,  1.5f,   0.66666667f));
	EXPECT_TRUE(vf % vf2 == eeEngineSDK::Vector4f(-2.0f,   0.0f,  2.0f,  -4.0f));

	// Operetors with numbers
	EXPECT_TRUE(vf + 1.0f == eeEngineSDK::Vector4f(-6.0f,   5.0f,   7.0f,  -3.0f));
	EXPECT_TRUE(vf - 2.0f == eeEngineSDK::Vector4f(-9.0f,   2.0f,   4.0f,  -6.0f));
	EXPECT_TRUE(vf * 3.0f == eeEngineSDK::Vector4f(-21.0f,  12.0f,  18.0f, -12.0f));
	EXPECT_TRUE(vf / 2.0f == eeEngineSDK::Vector4f(-3.5f,   2.0f,   3.0f,  -2.0f));
	EXPECT_TRUE(vf % 1.5f == eeEngineSDK::Vector4f(-1.0f,   1.0f,   0.0f,  -1.0f));


	// Asign operators with other vectors
	vf += vf2;
	EXPECT_TRUE(vf == eeEngineSDK::Vector4f(-12.0f,  6.0f,  10.0f, -10.0f));
	vf -= vf2;
	EXPECT_TRUE(vf == eeEngineSDK::Vector4f(-7.0f,   4.0f,  6.0f,  -4.0f));
  vf /= vf2;
  EXPECT_TRUE(vf == eeEngineSDK::Vector4f( 1.4f,   2.0f,  1.5f,   0.66666667f));
  vf *= vf2;
  EXPECT_TRUE(vf == eeEngineSDK::Vector4f(-7.0f,   4.0f,  6.0f,  -4.0f));
  vf %= vf2;
  EXPECT_TRUE(vf == eeEngineSDK::Vector4f(-2.0f,   0.0f,  2.0f,  -4.0f));

	// Asign operators with numbers
	vf += 1.0f;
	EXPECT_TRUE(vf == eeEngineSDK::Vector4f(-1.0f,   1.0f,  3.0f,  -3.0f));
	vf -= 3.0f;
	EXPECT_TRUE(vf == eeEngineSDK::Vector4f(-4.0f,  -2.0f,  0.0f,  -6.0f));
  vf *= 3.0f;
  EXPECT_TRUE(vf == eeEngineSDK::Vector4f(-12.0f, -6.0f,  0.0f,  -18.0f));
  vf /= 2.0f;
  EXPECT_TRUE(vf == eeEngineSDK::Vector4f(-6.0f,  -3.0f,  0.0f,  -9.0f));
  vf %= 2.0f;
  EXPECT_TRUE(vf == eeEngineSDK::Vector4f(-0.0f,  -1.0f,  0.0f,  -1.0f));


	// Logic operators
	EXPECT_TRUE(vf != vf2);
	EXPECT_FALSE(vf > vf2);
	EXPECT_FALSE(vf >= vf2);
	EXPECT_TRUE(vf < vf2);
	EXPECT_TRUE(vf <= vf2);


  // TODO: Terminar este Unit test
  /* Vector4i */
  // Default constructor
  eeEngineSDK::Vector4i vi;
  EXPECT_EQ(vi, eeEngineSDK::Vector4i::ZERO);

  // operator=
  vi = eeEngineSDK::Vector4i(-7,  4,  6, -4);
  EXPECT_EQ(vi, eeEngineSDK::Vector4i(-7,  4,  6, -4));

  // Custom constructor constructor
  eeEngineSDK::Vector4i vi2(-5,  2,  4, -6);
  EXPECT_EQ(vi2, eeEngineSDK::Vector4i(-5,  2,  4, -6));

  // Functions
  EXPECT_EQ(vi.dot(vi2), 91.0f);

  EXPECT_EQ(vi.distance(vi2), 4.0f);
  EXPECT_EQ(vi2.length(), 9.0f);
  EXPECT_TRUE(vi.normalize() == eeEngineSDK::Vector4f(-0.64715023f, 0.36980013f, 0.55470020f, -0.36980013f));
  EXPECT_TRUE(vi.truncate(7.0f) == eeEngineSDK::Vector4f(-4.53005160f, 2.58860092f, 3.88290137f, -2.58860092f));

  // Operators with other vectors
  //vi  = {-7,  4,  6, -4}
  //vi2 = {-5,  2,  4, -6}
  EXPECT_TRUE(vi + vi2 == eeEngineSDK::Vector4i(-12,  6,   10, -10));
  EXPECT_TRUE(vi - vi2 == eeEngineSDK::Vector4i(-2,   2,   2,   2));
  EXPECT_TRUE(vi * vi2 == eeEngineSDK::Vector4i( 35,  8,   24,  24));
  EXPECT_TRUE(vi / vi2 == eeEngineSDK::Vector4i( 1,   2,   1,   0));
  EXPECT_TRUE(vi % vi2 == eeEngineSDK::Vector4i(-2,   0,   2,  -4));

  // Operetors with numbers
  EXPECT_TRUE(vi + 1 == eeEngineSDK::Vector4i(-6,   5,   7,  -3));
  EXPECT_TRUE(vi - 2 == eeEngineSDK::Vector4i(-9,   2,   4,  -6));
  EXPECT_TRUE(vi * 3 == eeEngineSDK::Vector4i(-21,  12,  18, -12));
  EXPECT_TRUE(vi / 2 == eeEngineSDK::Vector4i(-3,   2,   3,  -2));
  EXPECT_TRUE(vi % 2 == eeEngineSDK::Vector4i(-1,   0,   0,  0));


  // Asign operators with other vectors
  vi += vi2;
  EXPECT_TRUE(vi == eeEngineSDK::Vector4i(-12,  6,   10, -10));
  vi -= vi2;
  EXPECT_TRUE(vi == eeEngineSDK::Vector4i(-7,   4,   6,  -4));
  vi /= vi2;
  EXPECT_TRUE(vi == eeEngineSDK::Vector4i( 1,   2,   1,   0));
  vi *= vi2;
  EXPECT_TRUE(vi == eeEngineSDK::Vector4i(-5,   4,   4,   0));
  vi %= vi2;
  EXPECT_TRUE(vi == eeEngineSDK::Vector4i( 0,   0,   0,   0));

  // Asign operators with numbers
  vi += 1;
  EXPECT_TRUE(vi == eeEngineSDK::Vector4i( 1,   1,   1,   1));
  vi -= 3;
  EXPECT_TRUE(vi == eeEngineSDK::Vector4i(-2,  -2,  -2,  -2));
  vi *= 3;
  EXPECT_TRUE(vi == eeEngineSDK::Vector4i(-6,  -6,  -6,  -6));
  vi /= 2;
  EXPECT_TRUE(vi == eeEngineSDK::Vector4i(-3,  -3,  -3,  -3));
  vi %= 2;
  EXPECT_TRUE(vi == eeEngineSDK::Vector4i(-1,  -1,  -1,  -1));


  // Logic operators
  EXPECT_TRUE(vi != vi2);
  EXPECT_FALSE(vi > vi2);
  EXPECT_FALSE(vi >= vi2);
  EXPECT_TRUE(vi < vi2);
  EXPECT_TRUE(vi <= vi2);



  /* Vector4u */
  // Default constructor
  eeEngineSDK::Vector4u vu;
  EXPECT_EQ(vu, eeEngineSDK::Vector4u::ZERO);

  // operator=
  vu = eeEngineSDK::Vector4u(-7, 4, 6, -4);
  EXPECT_EQ(vu, eeEngineSDK::Vector4u(-7, 4, 6, -4));

  // Custom constructor constructor
  eeEngineSDK::Vector4u vu2(-5, 2, 4, -6);
  EXPECT_EQ(vu2, eeEngineSDK::Vector4u(-5, 2, 4, -6));

  // Functions
  EXPECT_EQ(vu.dot(vu2), 91.0f);

  EXPECT_EQ(vu.distance(vu2), 4.0f);
  EXPECT_EQ(vu2.length(), 9.0f);
  EXPECT_TRUE(vu.normalize() == eeEngineSDK::Vector4f(-0.64715023f, 0.36980013f, 0.55470020f, -0.36980013f));
  EXPECT_TRUE(vu.truncate(7.0f) == eeEngineSDK::Vector4f(-4.53005160f, 2.58860092f, 3.88290137f, -2.58860092f));

  // Operators with other vectors
  //vu  = {-7,  4,  6, -4}
  //vu2 = {-5,  2,  4, -6}
  EXPECT_TRUE(vu + vu2 == eeEngineSDK::Vector4u(-12, 6, 10, -10));
  EXPECT_TRUE(vu - vu2 == eeEngineSDK::Vector4u(-2, 2, 2, 2));
  EXPECT_TRUE(vu* vu2 == eeEngineSDK::Vector4u(35, 8, 24, 24));
  EXPECT_TRUE(vu / vu2 == eeEngineSDK::Vector4u(1, 2, 1, 0));
  EXPECT_TRUE(vu% vu2 == eeEngineSDK::Vector4u(-2, 0, 2, -4));

  // Operetors with numbers
  EXPECT_TRUE(vu + 1 == eeEngineSDK::Vector4u(-6, 5, 7, -3));
  EXPECT_TRUE(vu - 2 == eeEngineSDK::Vector4u(-9, 2, 4, -6));
  EXPECT_TRUE(vu * 3 == eeEngineSDK::Vector4u(-21, 12, 18, -12));
  EXPECT_TRUE(vu / 2 == eeEngineSDK::Vector4u(-3, 2, 3, -2));
  EXPECT_TRUE(vu % 2 == eeEngineSDK::Vector4u(-1, 0, 0, 0));


  // Asign operators with other vectors
  vu += vu2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector4u(-12, 6, 10, -10));
  vu -= vu2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector4u(-7, 4, 6, -4));
  vu /= vu2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector4u(1, 2, 1, 0));
  vu *= vu2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector4u(-5, 4, 4, 0));
  vu %= vu2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector4u(0, 0, 0, 0));

  // Asign operators with numbers
  vu += 1;
  EXPECT_TRUE(vu == eeEngineSDK::Vector4u(1, 1, 1, 1));
  vu -= 3;
  EXPECT_TRUE(vu == eeEngineSDK::Vector4u(-2, -2, -2, -2));
  vu *= 3;
  EXPECT_TRUE(vu == eeEngineSDK::Vector4u(-6, -6, -6, -6));
  vu /= 2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector4u(-3, -3, -3, -3));
  vu %= 2;
  EXPECT_TRUE(vu == eeEngineSDK::Vector4u(-1, -1, -1, -1));


  // Logic operators
  EXPECT_TRUE(vu != vu2);
  EXPECT_FALSE(vu > vu2);
  EXPECT_FALSE(vu >= vu2);
  EXPECT_TRUE(vu < vu2);
  EXPECT_TRUE(vu <= vu2);
}

int main(int argc, char** argv) {
  int stop;
  ::testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  std::cin >> stop;
  return 0;
}