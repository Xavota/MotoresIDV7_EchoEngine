#pragma once
#include "eePrerequisitesUtilities.h"
#include "eeVector2.h"

namespace eeEngineSDK {
  /**
  * @brief
  * Matrix 2x2. Holds 2 rows and 2 columns of floats.
  * Has all the possible operations for matrices.
  */
class EE_UTILITY_EXPORT Matrix2f
{
 public:
  /**
  * @brief
  * The default constructor.
  *
  * @description
  * Initializes every value in 0.
  */
  Matrix2f();
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
  Matrix2f(float src[4]);
  /**
  * @brief
  * Custom constructor.
  *
  * @description
  * Initializes the matrix with vectors,
  * one for each row.
  *
  * @param r0
  * The first row of the matrix.
  * @param r0
  * The second row of the matrix.
  */
  Matrix2f(const Vector2f& r0, const Vector2f& r1);
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
  * @param _1
  * Second row, second column.
  */
  Matrix2f(float _00, float _01, float _10, float _11);
  /**
  * @brief
  * The destructor.
  *
  * @description
  * Frees allocated memory.
  */
  ~Matrix2f();

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
    struct
    {
      /*
      * The first row.
      */
      Vector2f m_r0;
      /*
      * The second row.
      */
      Vector2f m_r1;
    };
    /*
    * The entire matrix on an array.
    */
    float m[4];
  };

  /*
  * Matrix filled with zeros.
  */
  static Matrix2f ZERO;
  /*
  * Matrix filled with ones.
  */
  static Matrix2f ONES;
  /*
  * The identity matrix.
  */
  static Matrix2f IDENTITY;
};


/**
* @brief
* Matrix 2x2. Holds 2 rows and 2 columns of int32.
* Has all the possible operations for matrices.
*/
class EE_UTILITY_EXPORT Matrix2i
{
 public:
  /**
  * @brief
  * The default constructor.
  *
  * @description
  * Initializes every value in 0.
  */
  Matrix2i();
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
  Matrix2i(int32 src[4]);
  /**
  * @brief
  * Custom constructor.
  *
  * @description
  * Initializes the matrix with vectors,
  * one for each row.
  *
  * @param r0
  * The first row of the matrix.
  * @param r0
  * The second row of the matrix.
  */
  Matrix2i(const Vector2i& r0, const Vector2i& r1);
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
  * @param _1
  * Second row, second column.
  */
  Matrix2i(int32 _00, int32 _01, int32 _10, int32 _11);
  /**
  * @brief
  * The destructor.
  *
  * @description
  * Frees allocated memory.
  */
  ~Matrix2i();

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
  Matrix2i 
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
  Matrix2i&
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
  Matrix2i 
  operator+(const Matrix2i& other) const;
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
  Matrix2i 
  operator-(const Matrix2i& other) const;
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
  Matrix2i 
  operator*(const Matrix2i& other) const;
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
  Matrix2i 
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
  Matrix2i& 
  operator=(const Matrix2i& other);

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
  Matrix2i& 
  operator+=(const Matrix2i& other);
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
  Matrix2i& 
  operator-=(const Matrix2i& other);
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
  Matrix2i& 
  operator*=(const Matrix2i& other);
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
  Matrix2i& 
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
  operator==(const Matrix2i& other);

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
      * Component r1c0 of the matrix.
      */
      int32 m_10;
      /*
      * Component r1c1 of the matrix.
      */
      int32 m_11;
    };
    struct
    {
      /*
      * The first row.
      */
      Vector2i m_r0;
      /*
      * The second row.
      */
      Vector2i m_r1;
    };
    /*
    * The entire matrix on an array.
    */
    int32 m[4];
  };

  /*
  * Matrix filled with zeros.
  */
  static Matrix2i ZERO;
  /*
  * Matrix filled with ones.
  */
  static Matrix2i ONES;
  /*
  * The identity matrix.
  */
  static Matrix2i IDENTITY;
};


/**
* @brief
* Matrix 2x2. Holds 2 rows and 2 columns of uint32.
* Has all the possible operations for matrices.
*/
class EE_UTILITY_EXPORT Matrix2u
{
 public:
  /**
  * @brief
  * The default constructor.
  *
  * @description
  * Initializes every value in 0.
  */
  Matrix2u();
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
  Matrix2u(uint32 src[4]);
  /**
  * @brief
  * Custom constructor.
  *
  * @description
  * Initializes the matrix with vectors,
  * one for each row.
  *
  * @param r0
  * The first row of the matrix.
  * @param r0
  * The second row of the matrix.
  */
  Matrix2u(const Vector2u& r0, const Vector2u& r1);
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
  * @param _1
  * Second row, second column.
  */
  Matrix2u(uint32 _00, uint32 _01, uint32 _10, uint32 _11);
  /**
  * @brief
  * The destructor.
  *
  * @description
  * Frees allocated memory.
  */
  ~Matrix2u();

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
  Matrix2u 
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
  Matrix2u&
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
  Matrix2u 
  operator+(const Matrix2u& other) const;
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
  Matrix2u 
  operator-(const Matrix2u& other) const;
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
  Matrix2u 
  operator*(const Matrix2u& other) const;
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
  Matrix2u 
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
  Matrix2u& 
  operator=(const Matrix2u& other);

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
  Matrix2u& 
  operator+=(const Matrix2u& other);
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
  Matrix2u& 
  operator-=(const Matrix2u& other);
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
  Matrix2u& 
  operator*=(const Matrix2u& other);
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
  Matrix2u&
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
  operator==(const Matrix2u& other);

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
      * Component r1c0 of the matrix.
      */
      uint32 m_10;
      /*
      * Component r1c1 of the matrix.
      */
      uint32 m_11;
    };
    struct
    {
      /*
      * The first row.
      */
      Vector2u m_r0;
      /*
      * The second row.
      */
      Vector2u m_r1;
    };
    /*
    * The entire matrix on an array.
    */
    uint32 m[4];
  };

  /*
  * Matrix filled with zeros.
  */
  static Matrix2u ZERO;
  /*
  * Matrix filled with ones.
  */
  static Matrix2u ONES;
  /*
  * The identity matrix.
  */
  static Matrix2u IDENTITY;
};
}
