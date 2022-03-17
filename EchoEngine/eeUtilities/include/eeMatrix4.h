/************************************************************************/
/**
 * @file eeMatrix4.h
 * @author Diego Castellanos
 * @date 18/09/21
 * @brief This file defines the Matrix4 in its 3 forms: floats, int32 and 
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
 * Matrix 4x4. Holds 4 rows and 4 columns of floats.
 * Has all the possible operations for matrices.
 * Row major
 */
class EE_UTILITY_EXPORT Matrix4f
{
public:
  /**
   * @brief
   * The default constructor.
   */
  Matrix4f() = default;
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
  Matrix4f(float src[16]);
//#ifdef VECTOR4
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
//   * @param r3
//   * The fourth row of the matrix.
//   */
//  Matrix4f(const Vector4f& r0, const Vector4f& r1,
//    const Vector4f& r2, const Vector4f& r3)
//    : m_r0(r0), m_r1(r1), m_r2(r2), m_r3(r3)
//  {}
//#endif
  /**
   * @brief
   * Custom constructor.
   *
   * @description
   * Initializes the matrix with values. Representing each value in the 
   * matrix.
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
   * @param _03
   * First row, fourth column.
   * @param _10
   * Second row, first column.
   * @param _11
   * Second row, second column.
   * @param _12
   * Second row, third column.
   * @param _13
   * Second row, fourth column.
   * @param _20
   * Third row, first column.
   * @param _21
   * Third row, second column.
   * @param _22
   * Third row, third column.
   * @param _23
   * Third row, fourth column.
   * @param _30
   * Fourth row, first column.
   * @param _31
   * Fourth row, second column.
   * @param _32
   * Fourth row, third column.
   * @param _33
   * Fourth row, fourth column.
   */
  FORCEINLINE explicit
  Matrix4f(float _00, float _01, float _02, float _03,
           float _10, float _11, float _12, float _13,
           float _20, float _21, float _22, float _23,
           float _30, float _31, float _32, float _33)
  : m_00(_00), m_01(_01), m_02(_02), m_03(_03),
    m_10(_10), m_11(_11), m_12(_12), m_13(_13),
    m_20(_20), m_21(_21), m_22(_22), m_23(_23),
    m_30(_30), m_31(_31), m_32(_32), m_33(_33)
  {}
  /**
   * @brief
   * The destructor.
   *
   * @description
   * Frees allocated memory.
   */
  ~Matrix4f() = default;

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
  Matrix4f
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
  Matrix4f&
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
  Matrix4f
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
  Matrix4f&
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
  Matrix4f&
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
  Matrix4f&
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
  Matrix4f&
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
  Matrix4f
  operator+(const Matrix4f& other) const;
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
  Matrix4f
  operator-(const Matrix4f& other) const;
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
  Matrix4f
  operator*(const Matrix4f& other) const;
  /**
   * @brief
   * The operator '*' with a vector4.
   *
   * @description
   * Multiply the matrix times the vector, and returns a new vector.
   *
   * @param v
   * The vector to multiply.
   *
   * @return
   * The resultant vector of the multiplication.
   */
  Vector4f
  operator*(const Vector4f& v) const;
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
  Matrix4f
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
  Matrix4f&
  operator=(const Matrix4f& other);

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
  Matrix4f&
  operator+=(const Matrix4f& other);
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
  Matrix4f&
  operator-=(const Matrix4f& other);
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
  Matrix4f&
  operator*=(const Matrix4f& other);
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
  Matrix4f&
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
  operator==(const Matrix4f& other);

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
  static Matrix4f
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
  static Matrix4f
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
  static Matrix4f
  scaleMatrix(const Vector3f& scale);

  /**
   * @brief
   * Calculates a view matrix.
   *
   * @description
   * Gives a view matrix using the eye, lookAt and world up vector.
   *
   * @param eye
   * The world position of the camera.
   * @param lookAt
   * The position on world that the camera is looking at.
   * @param worldUp
   * The world up vector.
   *
   * @return
   * A view matrix.
   */
  static Matrix4f
  viewMatrix(const Vector3f& eye, 
             const Vector3f& lookAt, 
             const Vector3f& worldUp);
  /**
   * @brief
   * Calculates an orthographic matrix.
   *
   * @description
   * Gives an orthographic matrix using with, height, and near and far distance
   * plane.
   *
   * @param ViewWidth
   * The width of the screen.
   * @param ViewHeight
   * The height of the screen.
   * @param NearZ
   * The distance to near plane of the camera.
   * @param FarZ
   * The distance to far plane of the camera.
   *
   * @return
   * An orthographic matrix.
   */
  static Matrix4f
  orthograficMatrixMatrix(float ViewWidth, 
                          float ViewHeight, 
                          float NearZ, 
                          float FarZ);
  /**
   * @brief
   * Calculates a perspective matrix.
   *
   * @description
   * Gives a perspective matrix using the Y field of view angle, the aspect ratio
   * of the screen, and near and far distance plane.
   *
   * @param FovAngleY
   * The Y field of view angle.
   * @param AspectRatio
   * The aspect ratio of the screen.
   * @param NearZ
   * The distance to near plane of the camera.
   * @param FarZ
   * The distance to far plane of the camera.
   *
   * @return
   * An orthographic matrix.
   */
  static Matrix4f
  perspectiveMatrix(float FovAngleY, 
                    float AspectRatio, 
                    float NearZ, 
                    float FarZ);

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
       * Component r0c3 of the matrix.
       */
      float m_03;
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
       * Component r1c3 of the matrix.
       */
      float m_13;
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
      /*
       * Component r2c3 of the matrix.
       */
      float m_23;
      /*
       * Component r3c0 of the matrix.
       */
      float m_30;
      /*
       * Component r3c1 of the matrix.
       */
      float m_31;
      /*
       * Component r3c2 of the matrix.
       */
      float m_32;
      /*
       * Component r3c3 of the matrix.
       */
      float m_33;
    };
#ifdef VECTOR4
    struct
    {
      /*
       * The first row.
       */
      Vector4f m_r0;
      /*
       * The second row.
       */
      Vector4f m_r1;
      /*
       * The third row.
       */
      Vector4f m_r2;
      /*
       * The fourth row.
       */
      Vector4f m_r3;
    };
#endif
    /*
     * The entire matrix on an array.
     */
    float m[16];
  };

  /*
   * Matrix filled with zeros.
   */
  static const Matrix4f kZERO;
  /*
   * Matrix filled with ones.
   */
  static const Matrix4f kONES;
  /*
   * The identity matrix.
   */
  static const Matrix4f kIDENTITY;
};
}