#include "eeMatrix3.h"
#include "eeMatrix2.h"
#include "eeVector3.h" 
#include "eeMath.h"

namespace eeEngineSDK {
const Matrix3f Matrix3f::kZERO = Matrix3f(0.0f, 0.0f, 0.0f,
                                          0.0f, 0.0f, 0.0f, 
                                          0.0f, 0.0f, 0.0f );
const Matrix3f Matrix3f::kONES = Matrix3f(1.0f, 1.0f, 1.0f,
                                          1.0f, 1.0f, 1.0f, 
                                          1.0f, 1.0f, 1.0f );
const Matrix3f Matrix3f::kIDENTITY = Matrix3f(1.0f, 0.0f, 0.0f,
                                              0.0f, 1.0f, 0.0f, 
                                              0.0f, 0.0f, 1.0f);


Matrix3f 
Matrix3f::translationMatrix(const Vector3f& move)
{
  return Matrix3f(1.0f, 0.0f, move.x, 
                  0.0f, 1.0f, move.y, 
                  0.0f, 0.0f, move.z);
}
Matrix3f 
Matrix3f::rotationMatrix(const Vector3f& angle)
{
  Matrix3f rx( 1.0f,               0.0f,                0.0f,
               0.0f, Math::cos(angle.x), -Math::sin(angle.x),
               0.0f, Math::sin(angle.x),  Math::cos(angle.x));

  Matrix3f ry( Math::cos(angle.y), 0.0f, Math::sin(angle.y),
                             0.0f, 1.0f,               0.0f,
              -Math::sin(angle.y), 0.0f, Math::cos(angle.y));

  Matrix3f rz( Math::cos(angle.z), -Math::sin(angle.z), 0.0f,
               Math::sin(angle.z),  Math::cos(angle.z), 0.0f,
                             0.0f,                0.0f, 1.0f);

  Matrix3f rzy = rz * ry;
  return rzy * rx;
}
Matrix3f 
Matrix3f::scaleMatrix(const Vector3f& scale)
{
  return Matrix3f(scale.x,    0.0f,    0.0f,
                     0.0f, scale.y,    0.0f,
                     0.0f,    0.0f, scale.z);
}



Matrix3f::Matrix3f(float src[9])
{
  memcpy(m, src, sizeof(float) * 9);
}

float
Matrix3f::getDeterminant() const
{
  return m_00 * m_11 * m_22 + m_01 * m_12 * m_20 + m_02 * m_10 * m_21
       - m_02 * m_11 * m_20 - m_00 * m_12 * m_21 - m_01 * m_10 * m_22;
}
Matrix3f
Matrix3f::getTranspose() const
{
  return Matrix3f(m_00, m_10, m_20,
                  m_01, m_11, m_21, 
                  m_02, m_12, m_22);
}
Matrix3f&
Matrix3f::transpose()
{
  *this = getTranspose();
  return *this;
}
Matrix3f
Matrix3f::getInverse() const
{
  Matrix3f adj = Matrix3f( Matrix2f(m_11, m_12, m_21, m_22).getDeterminant(),
                          -Matrix2f(m_10, m_12, m_20, m_22).getDeterminant(), 
                           Matrix2f(m_10, m_11, m_20, m_21).getDeterminant(), 

                          -Matrix2f(m_01, m_02, m_21, m_22).getDeterminant(), 
                           Matrix2f(m_00, m_02, m_20, m_22).getDeterminant(), 
                          -Matrix2f(m_00, m_01, m_20, m_21).getDeterminant(), 

                           Matrix2f(m_01, m_02, m_11, m_12).getDeterminant(), 
                          -Matrix2f(m_00, m_02, m_10, m_12).getDeterminant(), 
                           Matrix2f(m_00, m_01, m_10, m_11).getDeterminant());

  adj.transpose();
  return adj * (1 / getDeterminant());
}
Matrix3f&
Matrix3f::inverse()
{
  *this = getInverse();
  return *this;
}
Matrix3f&
Matrix3f::translate(const Vector3f& move)
{
  *this *= translationMatrix(move);
  return *this;
}
Matrix3f&
Matrix3f::rotate(const Vector3f& angle)
{
  *this *= rotationMatrix(angle);
  return *this;
}
Matrix3f&
Matrix3f::scale(const Vector3f& scale)
{
  *this *= scaleMatrix(scale);
  return *this;
}

Matrix3f
Matrix3f::operator+(const Matrix3f& other) const
{
  return Matrix3f(this->m_00 + other.m_00,
                  this->m_01 + other.m_01,
                  this->m_02 + other.m_02, 

                  this->m_10 + other.m_10,
                  this->m_11 + other.m_11,
                  this->m_12 + other.m_12,

                  this->m_20 + other.m_20,
                  this->m_21 + other.m_21,
                  this->m_22 + other.m_22);
}
Matrix3f
Matrix3f::operator-(const Matrix3f& other) const
{
  return Matrix3f(this->m_00 - other.m_00,
                  this->m_01 - other.m_01,
                  this->m_02 - other.m_02,

                  this->m_10 - other.m_10,
                  this->m_11 - other.m_11,
                  this->m_12 - other.m_12,

                  this->m_20 - other.m_20,
                  this->m_21 - other.m_21,
                  this->m_22 - other.m_22);
}
Matrix3f
Matrix3f::operator*(const Matrix3f& other) const
{
  return Matrix3f(
  this->m_00 * other.m_00 + this->m_01 * other.m_10 + this->m_02 * other.m_20,
  this->m_00 * other.m_01 + this->m_01 * other.m_11 + this->m_02 * other.m_21,
  this->m_00 * other.m_02 + this->m_01 * other.m_12 + this->m_02 * other.m_22, 

  this->m_10 * other.m_00 + this->m_11 * other.m_10 + this->m_12 * other.m_20,
  this->m_10 * other.m_01 + this->m_11 * other.m_11 + this->m_12 * other.m_21,
  this->m_10 * other.m_02 + this->m_11 * other.m_12 + this->m_12 * other.m_22,
  
  this->m_20 * other.m_00 + this->m_21 * other.m_10 + this->m_22 * other.m_20,
  this->m_20 * other.m_01 + this->m_21 * other.m_11 + this->m_22 * other.m_21,
  this->m_20 * other.m_02 + this->m_21 * other.m_12 + this->m_22 * other.m_22);
}
Matrix3f
Matrix3f::operator*(float k) const
{
  return Matrix3f(this->m_00 * k,
                  this->m_01 * k,
                  this->m_02 * k,

                  this->m_10 * k,
                  this->m_11 * k,
                  this->m_12 * k,

                  this->m_20 * k,
                  this->m_21 * k,
                  this->m_22 * k);
}
Matrix3f&
Matrix3f::operator=(const Matrix3f& other)
{
  this->m_00 = other.m_00;
  this->m_01 = other.m_01;
  this->m_02 = other.m_02;

  this->m_10 = other.m_10;
  this->m_11 = other.m_11;
  this->m_12 = other.m_12;

  this->m_20 = other.m_20;
  this->m_21 = other.m_21;
  this->m_22 = other.m_22;
  return *this;
}
Matrix3f&
Matrix3f::operator+=(const Matrix3f& other)
{
  *this = *this + other;
  return *this;
}
Matrix3f&
Matrix3f::operator-=(const Matrix3f& other)
{
  *this = *this - other;
  return *this;
}
Matrix3f&
Matrix3f::operator*=(const Matrix3f& other)
{
  *this = *this * other;
  return *this;
}
Matrix3f&
Matrix3f::operator*=(float k)
{
  *this = *this * k;
  return *this;
}
bool
Matrix3f::operator==(const Matrix3f& other)
{
  for (int32 i = 0; i < 9; ++i) {
    if (!Math::checkFloatsEqual(this->m[i], other.m[i])) {
      return false;
    }
  }
  return true;
}
}