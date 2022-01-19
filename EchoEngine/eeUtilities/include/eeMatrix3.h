/************************************************************************/
/**
 * @file eeMatrix3.h
 * @author Diego Castellanos
 * @date 16/09/21
 * @brief This file defines the Matrix3 in its 3 forms: floats, int32 and
 *        uint32, as well as its functions, operators and members.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK {
/**
 * @brief
 * Matrix 3x3. Holds 3 rows and 3 columns of floats.
 * Has all the possible operations for matrices.
 */
class EE_UTILITY_EXPORT Matrix3f
{
public:
  /**
   * @brief
   * The default constructor.
   */
  Matrix3f();
  /**
   * @brief
   * Custom constructor.
   *
   * @description
   * Takes an array of values to initialize the matrix.
   * Ordered from left to right, up to down.
   *
   * @param src
   * The source from where the data is taken.
   */
  Matrix3f(float src[9]);
//#ifdef VECTOR3
//  /**
//   * @brief
//   * Custom constructor.
//   *
//   * @description
//   * Initializes the matrix with vectors,
//   * one for each row.
//   *
//   * @param r0
//   * The first row of the matrix.
//   * @param r1
//   * The second row of the matrix.
//   * @param r2
//   * The third row of the matrix.
//   */
//  Matrix3f(const Vector3f& r0, const Vector3f& r1, const Vector3f& r2);
//#endif
  /**
   * @brief
   * Custom constructor.
   *
   * @description
   * Initializes the matrix with values. Representing each value in the matrix.
   * Name '_xy'
   * x: row
   * y: column
   *
   * @param _00
   * First row, first column.
   * @param _01
   * First row, second column.
   * @param _02
   * First row, third column.
   * @param _10
   * Second row, first column.
   * @param _11
   * Second row, second column.
   * @param _12
   * Second row, third column.
   * @param _20
   * Third row, first column.
   * @param _21
   * Third row, second column.
   * @param _22
   * Third row, third column.
   */
  Matrix3f(float _00, float _01, float _02,
           float _10, float _11, float _12, 
           float _20, float _21, float _22);
  /**
   * @brief
   * The destructor.
   *
   * @description
   * Frees allocated memory.
   */
  ~Matrix3f();

  /**
   * @brief
   * Calculates the determinant of the matrix.
   *
   * @description
   * Returns the determinant of the matrix with its current values.
   *
   * @return
   * The determinant of the matrix.
   */
  float
  getDeterminant() const;
  /**
   * @brief
   * Calculates the transpose of the matrix.
   *
   * @description
   * Returns the transpose of the matrix, inverting rows and columns.
   *
   * @return
   * The transpose of the matrix.
   */
  Matrix3f
  getTranspose() const;
  /**
   * @brief
   * Transpose the matrix.
   *
   * @description
   * Modifies the matrix to its transposed form.
   *
   * @return
   * The transpose of the matrix.
   */
  Matrix3f&
  transpose();
  /**
   * @brief
   * Calculates the inverse of the matrix.
   *
   * @description
   * Returns the inverse of the matrix with its current values.
   *
   * @return
   * The inverse of the matrix.
   */
  Matrix3f
  getInverse() const;
  /**
   * @brief
   * Inverse the matrix.
   *
   * @description
   * Modify the matrix to its inverse form with its current values.
   *
   * @return
   * The matrix inverted.
   */
  Matrix3f&
  inverse();

  /**
   * @brief
   * Translates the matrix.
   *
   * @description
   * Multiplies the matrix with a translation matrix, to combine the 
   * transformations.
   *
   * @param move
   * The vector indicating how much you want to move.
   *
   * @return
   * The translation matrix.
   */
  Matrix3f&
  translate(const Vector3f& move);
  /**
   * @brief
   * Rotates the matrix.
   *
   * @description
   * Multiplies the matrix with a rotation matrix, to combine the
   * transformations.
   *
   * @param angle
   * The vector indicating how much you want to rotate, angles in radians.
   *
   * @return
   * The rotation matrix.
   */
  Matrix3f&
  rotate(const Vector3f& angle);
  /**
   * @brief
   * Scales the matrix.
   *
   * @description
   * Multiplies the matrix with a scale matrix, to combine the
   * transformations.
   *
   * @param scale
   * The vector indicating how much you want to scale.
   *
   * @return
   * The scale matrix.
   */
  Matrix3f&
  scale(const Vector3f& scale);

  /**
   * @brief
   * The operator '+' with other matrix.
   *
   * @description
   * Sums every value with its counterpart on the other matrix.
   *
   * @param other
   * The other matrix to sum.
   *
   * @return
   * The sum of the two matrices.
   */
  Matrix3f
  operator+(const Matrix3f& other) const;
  /**
   * @brief
   * The operator '-' with other matrix.
   *
   * @description
   * Subtracts every value with its counterpart on the other matrix.
   *
   * @param other
   * The other matrix to subtract.
   *
   * @return
   * The subtraction of the two matrices.
   */
  Matrix3f
  operator-(const Matrix3f& other) const;
  /**
   * @brief
   * The operator '*' with other matrix.
   *
   * @description
   * Multiply the two matrices, rows times columns.
   *
   * @param other
   * The other matrix to multiply.
   *
   * @return
   * The multiplication of the two matrices.
   */
  Matrix3f
  operator*(const Matrix3f& other) const;
  /**
   * @brief
   * The operator '*' with a number.
   *
   * @description
   * Multiply each value of the matrix with the number.
   *
   * @param k
   * The value to multiply.
   *
   * @return
   * The multiplication of the values of the matrix, time the number.
   */
  Matrix3f
  operator*(float k) const;

  /**
   * @brief
   * The operator '=' with other matrix.
   *
   * @description
   * Makes every component of the matrix equal to its counterpart
   * on the other matrix.
   *
   * @param other
   * The matrix to be equal.
   *
   * @return
   * This matrix with its values changed.
   */
  Matrix3f&
  operator=(const Matrix3f& other);

  /**
   * @brief
   * The operator '+=' with other matrix.
   *
   * @description
   * Makes this matrix equal to the sum of it plus the
   * other matrix.
   *
   * @param other
   * The other matrix to sum.
   *
   * @return
   * This matrix with its values changed.
   */
  Matrix3f&
  operator+=(const Matrix3f& other);
  /**
   * @brief
   * The operator '-=' with other matrix.
   *
   * @description
   * Makes this matrix equal to the subtraction of it minus the
   * other matrix.
   *
   * @param other
   * The other matrix to subtract.
   *
   * @return
   * This matrix with its values changed.
   */
  Matrix3f&
  operator-=(const Matrix3f& other);
  /**
   * @brief
   * The operator '*=' with other matrix.
   *
   * @description
   * Makes this matrix equal to the multiplication of it times the
   * other matrix.
   *
   * @param other
   * The other matrix to multiply.
   *
   * @return
   * This matrix with its values changed.
   */
  Matrix3f&
  operator*=(const Matrix3f& other);
  /**
   * @brief
   * The operator '*=' with a value.
   *
   * @description
   * Makes this matrix equal to the multiplication of its components
   * times the number.
   *
   * @param k
   * The value to multiply.
   *
   * @return
   * This matrix with its values changed.
   */
  Matrix3f&
  operator*=(float k);

  /**
   * @brief
   * The operator '==' with a value.
   *
   * @description
   * Checks if the two matrices are equal, or really close to be.
   *
   * @param other
   * The other matrix to check.
   *
   * @return
   * True if the two matrices are equal.
   */
  bool
  operator==(const Matrix3f& other);

public:
  /**
   * @brief
   * Calculates a translation matrix.
   *
   * @description
   * Gives a translation matrix that moves a point the given space.
   *
   * @param move
   * The vector indicating how much you want to move.
   *
   * @return
   * The translation matrix.
   */
  static Matrix3f
  translationMatrix(const Vector3f& move);
  /**
   * @brief
   * Calculates a rotation matrix.
   *
   * @description
   * Gives a rotation matrix that rotates a point from the origin, the given
   * angles in the 3 axis, in radians.
   *
   * @param angle
   * The vector indicating how much you want to rotate, angles in radians.
   *
   * @return
   * The rotation matrix.
   */
  static Matrix3f
  rotationMatrix(const Vector3f& angle);
  /**
   * @brief
   * Calculates a scale matrix.
   *
   * @description
   * Gives a scale matrix that moves a point away from the origin, to increase
   * the size of its object.
   *
   * @param scale
   * The vector indicating how much you want to scale.
   *
   * @return
   * The scale matrix.
   */
  static Matrix3f
  scaleMatrix(const Vector3f& scale);

  union
  {
    struct
    {
      /*
       * Component r0c0 of the matrix.
       */
      float m_00;
      /*
       * Component r0c1 of the matrix.
       */
      float m_01;
      /*
       * Component r0c2 of the matrix.
       */
      float m_02;
      /*
       * Component r1c0 of the matrix.
       */
      float m_10;
      /*
       * Component r1c1 of the matrix.
       */
      float m_11;
      /*
       * Component r1c2 of the matrix.
       */
      float m_12;
      /*
       * Component r2c0 of the matrix.
       */
      float m_20;
      /*
       * Component r2c1 of the matrix.
       */
      float m_21;
      /*
       * Component r2c2 of the matrix.
       */
      float m_22;
    };
//#ifdef VECTOR3
//    struct
//    {
//      /*
//       * The first row.
//       */
//      Vector3f m_r0;
//      /*
//       * The second row.
//       */
//      Vector3f m_r1;
//      /*
//       * The third row.
//       */
//      Vector3f m_r2;
//    };
//#endif
    /*
     * The entire matrix on an array.
     */
    float m[9];
  };

  /*
   * Matrix filled with zeros.
   */
  static const Matrix3f kZERO;
  /*
   * Matrix filled with ones.
   */
  static const Matrix3f kONES;
  /*
   * The identity matrix.
   */
  static const Matrix3f kIDENTITY;
};

//#ifdef VECTOR3
//Matrix3f::Matrix3f(const Vector3f& r0, const Vector3f& r1, const Vector3f& r2)
//  : m_r0(r0), m_r1(r1), m_r2(r2)
//{
//}
//#endif


/**
 * @brief
 * Matrix 3x3. Holds 3 rows and 3 columns of int32.
 * Has all the possible operations for matrices.
 */
class EE_UTILITY_EXPORT Matrix3i
{
public:
  /**
   * @brief
   * The default constructor.
   */
  Matrix3i();
  /**
   * @brief
   * Custom constructor.
   *
   * @description
   * Takes an array of values to initialize the matrix.
   * Ordered from left to right, up to down.
   *
   * @param src
   * The source from where the data is taken.
   */
  Matrix3i(int32 src[9]);
//#ifdef VECTOR3
//  /**
//   * @brief
//   * Custom constructor.
//   *
//   * @description
//   * Initializes the matrix with vectors,
//   * one for each row.
//   *
//   * @param r0
//   * The first row of the matrix.
//   * @param r1
//   * The second row of the matrix.
//   * @param r2
//   * The third row of the matrix.
//   */
//  Matrix3i(const Vector3i& r0, const Vector3i& r1, const Vector3i& r2);
//#endif
  /**
   * @brief
   * Custom constructor.
   *
   * @description
   * Initializes the matrix with values. Representing each value in the matrix.
   * Name '_xy'
   * x: row
   * y: column
   *
   * @param _00
   * First row, first column.
   * @param _01
   * First row, second column.
   * @param _02
   * First row, third column.
   * @param _10
   * Second row, first column.
   * @param _11
   * Second row, second column.
   * @param _12
   * Second row, third column.
   * @param _20
   * Third row, first column.
   * @param _21
   * Third row, second column.
   * @param _22
   * Third row, third column.
   */
  Matrix3i(int32 _00, int32 _01, int32 _02,
           int32 _10, int32 _11, int32 _12,
           int32 _20, int32 _21, int32 _22);
  /**
  * @brief
  * The destructor.
   *
   * @description
   * Frees allocated memory.
   */
  ~Matrix3i();

  /**
   * @brief
   * Calculates the determinant of the matrix.
   *
   * @description
   * Returns the determinant of the matrix with its current values.
   *
   * @return
   * The determinant of the matrix.
   */
  float
  getDeterminant() const;
  /**
   * @brief
   * Calculates the transpose of the matrix.
   *
   * @description
   * Returns the transpose of the matrix, inverting rows and columns.
   *
   * @return
   * The transpose of the matrix.
   */
  Matrix3i
  getTranspose() const;
  /**
   * @brief
   * Transpose the matrix.
   *
   * @description
   * Modifies the matrix to its transposed form.
   *
   * @return
   * The transpose of the matrix.
   */
  Matrix3i&
  transpose();

  /**
   * @brief
   * The operator '+' with other matrix.
   *
   * @description
   * Sums every value with its counterpart on the other matrix.
   *
   * @param other
   * The other matrix to sum.
   *
   * @return
   * The sum of the two matrices.
   */
  Matrix3i
  operator+(const Matrix3i& other) const;
  /**
   * @brief
   * The operator '-' with other matrix.
   *
   * @description
   * Subtracts every value with its counterpart on the other matrix.
   *
   * @param other
   * The other matrix to subtract.
   *
   * @return
   * The subtraction of the two matrices.
   */
  Matrix3i
  operator-(const Matrix3i& other) const;
  /**
   * @brief
   * The operator '*' with other matrix.
   *
   * @description
   * Multiply the two matrices, rows times columns.
   *
   * @param other
   * The other matrix to multiply.
   *
   * @return
   * The multiplication of the two matrices.
   */
  Matrix3i
  operator*(const Matrix3i& other) const;
  /**
   * @brief
   * The operator '*' with a number.
   *
   * @description
   * Multiply each value of the matrix with the number.
   *
   * @param k
   * The value to multiply.
   *
   * @return
   * The multiplication of the values of the matrix, time the number.
   */
  Matrix3i
  operator*(int32 k) const;

  /**
   * @brief
   * The operator '=' with other matrix.
   *
   * @description
   * Makes every component of the matrix equal to its counterpart
   * on the other matrix.
   *
   * @param other
   * The matrix to be equal.
   *
   * @return
   * This matrix with its values changed.
   */
  Matrix3i&
  operator=(const Matrix3i& other);

  /**
   * @brief
   * The operator '+=' with other matrix.
   *
   * @description
   * Makes this matrix equal to the sum of it plus the
   * other matrix.
   *
   * @param other
   * The other matrix to sum.
   *
   * @return
   * This matrix with its values changed.
   */
  Matrix3i&
  operator+=(const Matrix3i& other);
  /**
   * @brief
   * The operator '-=' with other matrix.
   *
   * @description
   * Makes this matrix equal to the subtraction of it minus the
   * other matrix.
   *
   * @param other
   * The other matrix to subtract.
   *
   * @return
   * This matrix with its values changed.
   */
  Matrix3i&
  operator-=(const Matrix3i& other);
  /**
   * @brief
   * The operator '*=' with other matrix.
   *
   * @description
   * Makes this matrix equal to the multiplication of it times the
   * other matrix.
   *
   * @param other
   * The other matrix to multiply.
   *
   * @return
   * This matrix with its values changed.
   */
  Matrix3i&
  operator*=(const Matrix3i& other);
  /**
   * @brief
   * The operator '*=' with a value.
   *
   * @description
   * Makes this matrix equal to the multiplication of its components
   * times the number.
   *
   * @param k
   * The value to multiply.
   *
   * @return
   * This matrix with its values changed.
   */
  Matrix3i&
  operator*=(int32 k);

  /**
   * @brief
   * The operator '==' with a value.
   *
   * @description
   * Checks if the two matrices are equal, or really close to be.
   *
   * @param other
   * The other matrix to check.
   *
   * @return
   * True if the two matrices are equal.
   */
  bool
  operator==(const Matrix3i& other);

public:
  union
  {
    struct
    {
      /*
       * Component r0c0 of the matrix.
       */
      int32 m_00;
      /*
       * Component r0c1 of the matrix.
       */
      int32 m_01;
      /*
       * Component r0c2 of the matrix.
       */
      int32 m_02;
      /*
       * Component r1c0 of the matrix.
       */
      int32 m_10;
      /*
       * Component r1c1 of the matrix.
       */
      int32 m_11;
      /*
       * Component r1c2 of the matrix.
       */
      int32 m_12;
      /*
       * Component r2c0 of the matrix.
       */
      int32 m_20;
      /*
       * Component r2c1 of the matrix.
       */
      int32 m_21;
      /*
       * Component r2c2 of the matrix.
       */
      int32 m_22;
    };
//#ifdef VECTOR3
//    struct
//    {
//      /*
//       * The first row.
//       */
//      Vector3i m_r0;
//      /*
//       * The second row.
//       */
//      Vector3i m_r1;
//      /*
//       * The third row.
//       */
//      Vector3i m_r2;
//    };
//#endif
    /*
     * The entire matrix on an array.
     */
    int32 m[9];
  };

  /*
   * Matrix filled with zeros.
   */
  static const Matrix3i kZERO;
  /*
   * Matrix filled with ones.
   */
  static const Matrix3i kONES;
  /*
   * The identity matrix.
   */
  static const Matrix3i kIDENTITY;
};

//#ifdef VECTOR3
//Matrix3i::Matrix3i(const Vector3i& r0, const Vector3i& r1, const Vector3i& r2)
//  : m_r0(r0), m_r1(r1), m_r2(r2)
//{
//}
//#endif


/**
 * @brief
 * Matrix 3x3. Holds 3 rows and 3 columns of uint32.
 * Has all the possible operations for matrices.
 */
class EE_UTILITY_EXPORT Matrix3u
{
public:
  /**
   * @brief
   * The default constructor.
   */
  Matrix3u();
  /**
   * @brief
   * Custom constructor.
   *
   * @description
   * Takes an array of values to initialize the matrix.
   * Ordered from left to right, up to down.
   *
   * @param src
   * The source from where the data is taken.
   */
  Matrix3u(uint32 src[9]);
//#ifdef VECTOR3
//  /**
//   * @brief
//   * Custom constructor.
//   *
//   * @description
//   * Initializes the matrix with vectors,
//   * one for each row.
//   *
//   * @param r0
//   * The first row of the matrix.
//   * @param r1
//   * The second row of the matrix.
//   * @param r2
//   * The third row of the matrix.
//   */
//  Matrix3u(const Vector3u& r0, const Vector3u& r1, const Vector3u& r2);
//#endif
  /**
   * @brief
   * Custom constructor.
   *
   * @description
   * Initializes the matrix with values. Representing each value in the matrix.
   * Name '_xy'
   * x: row
   * y: column
   *
   * @param _00
   * First row, first column.
   * @param _01
   * First row, second column.
   * @param _02
   * First row, third column.
   * @param _10
   * Second row, first column.
   * @param _11
   * Second row, second column.
   * @param _12
   * Second row, third column.
   * @param _20
   * Third row, first column.
   * @param _21
   * Third row, second column.
   * @param _22
   * Third row, third column.
   */
  Matrix3u(uint32 _00, uint32 _01, uint32 _02,
           uint32 _10, uint32 _11, uint32 _12,
           uint32 _20, uint32 _21, uint32 _22);
  /**
   * @brief
   * The destructor.
   *
   * @description
   * Frees allocated memory.
   */
  ~Matrix3u();

  /**
   * @brief
   * Calculates the determinant of the matrix.
   *
   * @description
   * Returns the determinant of the matrix with its current values.
   *
   * @return
   * The determinant of the matrix.
   */
  float
  getDeterminant() const;
  /**
   * @brief
   * Calculates the transpose of the matrix.
   *
   * @description
   * Returns the transpose of the matrix, inverting rows and columns.
   *
   * @return
   * The transpose of the matrix.
   */
  Matrix3u
  getTranspose() const;
  /**
   * @brief
   * Transpose the matrix.
   *
   * @description
   * Modifies the matrix to its transposed form.
   *
   * @return
   * The transpose of the matrix.
   */
  Matrix3u&
  transpose();

  /**
   * @brief
   * The operator '+' with other matrix.
   *
   * @description
   * Sums every value with its counterpart on the other matrix.
   *
   * @param other
   * The other matrix to sum.
   *
   * @return
   * The sum of the two matrices.
   */
  Matrix3u
  operator+(const Matrix3u& other) const;
  /**
   * @brief
   * The operator '-' with other matrix.
   *
   * @description
   * Subtracts every value with its counterpart on the other matrix.
   *
   * @param other
   * The other matrix to subtract.
   *
   * @return
   * The subtraction of the two matrices.
   */
  Matrix3u
  operator-(const Matrix3u& other) const;
  /**
   * @brief
   * The operator '*' with other matrix.
   *
   * @description
   * Multiply the two matrices, rows times columns.
   *
   * @param other
   * The other matrix to multiply.
   *
   * @return
   * The multiplication of the two matrices.
   */
  Matrix3u
  operator*(const Matrix3u& other) const;
  /**
   * @brief
   * The operator '*' with a number.
   *
   * @description
   * Multiply each value of the matrix with the number.
   *
   * @param k
   * The value to multiply.
   *
   * @return
   * The multiplication of the values of the matrix, time the number.
   */
  Matrix3u
  operator*(uint32 k) const;

  /**
   * @brief
   * The operator '=' with other matrix.
   *
   * @description
   * Makes every component of the matrix equal to its counterpart
   * on the other matrix.
   *
   * @param other
   * The matrix to be equal.
   *
   * @return
   * This matrix with its values changed.
   */
  Matrix3u&
  operator=(const Matrix3u& other);

  /**
   * @brief
   * The operator '+=' with other matrix.
   *
   * @description
   * Makes this matrix equal to the sum of it plus the
   * other matrix.
   *
   * @param other
   * The other matrix to sum.
   *
   * @return
   * This matrix with its values changed.
   */
  Matrix3u&
  operator+=(const Matrix3u& other);
  /**
   * @brief
   * The operator '-=' with other matrix.
   *
   * @description
   * Makes this matrix equal to the subtraction of it minus the
   * other matrix.
   *
   * @param other
   * The other matrix to subtract.
   *
   * @return
   * This matrix with its values changed.
   */
  Matrix3u&
  operator-=(const Matrix3u& other);
  /**
   * @brief
   * The operator '*=' with other matrix.
   *
   * @description
   * Makes this matrix equal to the multiplication of it times the
   * other matrix.
   *
   * @param other
   * The other matrix to multiply.
   *
   * @return
   * This matrix with its values changed.
   */
  Matrix3u&
  operator*=(const Matrix3u& other);
  /**
   * @brief
   * The operator '*=' with a value.
   *
   * @description
   * Makes this matrix equal to the multiplication of its components
   * times the number.
   *
   * @param k
   * The value to multiply.
   *
   * @return
   * This matrix with its values changed.
   */
  Matrix3u&
  operator*=(uint32 k);

  /**
   * @brief
   * The operator '==' with a value.
   *
   * @description
   * Checks if the two matrices are equal, or really close to be.
   *
   * @param other
   * The other matrix to check.
   *
   * @return
   * True if the two matrices are equal.
   */
  bool
  operator==(const Matrix3u& other);

public:
  union
  {
    struct
    {
      /*
       * Component r0c0 of the matrix.
       */
      uint32 m_00;
      /*
       * Component r0c1 of the matrix.
       */
      uint32 m_01;
      /*
       * Component r0c2 of the matrix.
       */
      uint32 m_02;
      /*
       * Component r1c0 of the matrix.
       */
      uint32 m_10;
      /*
       * Component r1c1 of the matrix.
       */
      uint32 m_11;
      /*
       * Component r1c2 of the matrix.
       */
      uint32 m_12;
      /*
       * Component r2c0 of the matrix.
       */
      uint32 m_20;
      /*
       * Component r2c1 of the matrix.
       */
      uint32 m_21;
      /*
       * Component r2c2 of the matrix.
       */
      uint32 m_22;
    };
//#ifdef VECTOR3
//    struct
//    {
//      /*
//       * The first row.
//       */
//      Vector3u m_r0;
//      /*
//       * The second row.
//       */
//      Vector3u m_r1;
//      /*
//       * The third row.
//       */
//      Vector3u m_r2;
//    };
//#endif
    /*
     * The entire matrix on an array.
     */
    uint32 m[9];
  };

  /*
   * Matrix filled with zeros.
   */
  static const Matrix3u kZERO;
  /*
   * Matrix filled with ones.
   */
  static const Matrix3u kONES;
  /*
   * The identity matrix.
   */
  static const Matrix3u kIDENTITY;
};

//#ifdef VECTOR3
//Matrix3u::Matrix3u(const Vector3u& r0, const Vector3u& r1, const Vector3u& r2)
// : m_r0(r0), m_r1(r1), m_r2(r2)
//{
//}
//#endif
}