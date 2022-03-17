/************************************************************************/
/**
 * @file eeMatrix2.h
 * @author Diego Castellanos
 * @date 15/09/21
 * @brief This file defines the Matrix2 in its 3 forms: floats, int32 and
 *        uint32, as well as its functions, operators and members.
 *        Row major
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK {
/**
 * @brief
 * Matrix 2x2. Holds 2 rows and 2 columns of floats.
 * Has all the possible operations for matrices.
 * Row major
 */
class EE_UTILITY_EXPORT Matrix2f
{
 public:
  /**
   * @brief
   * The default constructor.
   */
  Matrix2f() = default;
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
  explicit
  Matrix2f(float src[4]);
//#ifdef VECTOR2
//  /**
//  * @brief
//  * Custom constructor.
//  *
//  * @description
//  * Initializes the matrix with vectors,
//  * one for each row.
//  *
//  * @param r0
//  * The first row of the matrix.
//  * @param r1
//  * The second row of the matrix.
//  */
//  Matrix2f(const Vector2f& r0, const Vector2f& r1);
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
   * @param _10
   * Second row, first column.
   * @param _11
   * Second row, second column.
   */
  FORCEINLINE explicit
  Matrix2f(float _00, float _01, float _10, float _11)
  : m_00(_00),
    m_01(_01),
    m_10(_10),
    m_11(_11)
  {}
  /**
   * @brief
   * The destructor.
   *
   * @description
   * Frees allocated memory.
   */
  ~Matrix2f() = default;

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
  Matrix2f 
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
  Matrix2f&
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
  Matrix2f 
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
  Matrix2f&
  inverse();

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
  Matrix2f 
  operator+(const Matrix2f& other) const;
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
  Matrix2f 
  operator-(const Matrix2f& other) const;
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
  Matrix2f 
  operator*(const Matrix2f& other) const;
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
  Matrix2f 
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
  Matrix2f&
  operator=(const Matrix2f& other);

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
  Matrix2f&
  operator+=(const Matrix2f& other);
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
  Matrix2f&
  operator-=(const Matrix2f& other);
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
  Matrix2f&
  operator*=(const Matrix2f& other);
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
  Matrix2f&
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
  operator==(const Matrix2f& other);

 public:
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
       * Component r1c0 of the matrix.
       */
      float m_10;
      /*
       * Component r1c1 of the matrix.
       */
      float m_11;
    };
//#ifdef VECTOR2
//    struct
//    {
//      /*
//       * The first row.
//       */
//      Vector2f m_r0;
//      /*
//       * The second row.
//       */
//      Vector2f m_r1;
//    };
//#endif
    /*
     * The entire matrix on an array.
     */
    float m[4];
  };

  /*
   * Matrix filled with zeros.
   */
  static const Matrix2f kZERO;
  /*
   * Matrix filled with ones.
   */
  static const Matrix2f kONES;
  /*
   * The identity matrix.
   */
  static const Matrix2f kIDENTITY;
};

//#ifdef VECTOR2
//Matrix2f::Matrix2f(const Vector2f& r0, const Vector2f& r1) : m_r0(r0),
//m_r1(r1)
//{
//}
//#endif
}