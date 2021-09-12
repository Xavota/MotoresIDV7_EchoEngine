#pragma once
#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK {
class Matrix2f
{
 public:
  Matrix2f();
  Matrix2f(float src[4]);
  Matrix2f(Vector2f r0, Vector2f r1);
  Matrix2f(float _00, float _01, float _10, float _11);
  ~Matrix2f();

  float determinant();
  Matrix2f transpose();
  Matrix2f inverse();

  Matrix2f operator+(const Matrix2f& other);
  Matrix2f operator-(const Matrix2f& other);
  Matrix2f operator*(const Matrix2f& other);

  Matrix2f operator=(const Matrix2f& other);

  Matrix2f operator+=(const Matrix2f& other);
  Matrix2f operator-=(const Matrix2f& other);
  Matrix2f operator*=(const Matrix2f& other);
};
}
