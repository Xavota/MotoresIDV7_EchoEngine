#include "eeMatrix2.h"
#include "eeVector2.h"
#include "eeMath.h"

namespace eeEngineSDK {
const Matrix2f Matrix2f::kZERO = Matrix2f(0.0f, 0.0f, 0.0f, 0.0f);
const Matrix2f Matrix2f::kONES = Matrix2f(1.0f, 1.0f, 1.0f, 1.0f);
const Matrix2f Matrix2f::kIDENTITY = Matrix2f(1.0f, 0.0f, 0.0f, 1.0f);


Matrix2f::Matrix2f(float src[4])
{
  memcpy(m, src, sizeof(float) * 4);
}

float 
Matrix2f::getDeterminant() const
{
  return m_00 * m_11 - m_01 * m_10;
}
Matrix2f 
Matrix2f::getTranspose() const
{
  return Matrix2f(m_00, m_10, m_01, m_11);
}
Matrix2f&
Matrix2f::transpose()
{
  *this = Matrix2f(m_00, m_10, m_01, m_11);
  return *this;
}
Matrix2f
Matrix2f::getInverse() const
{
  Matrix2f tadj(m_11, -m_01, -m_10, m_00);
  return tadj * (1 / getDeterminant());
}
Matrix2f&
Matrix2f::inverse()
{
  Matrix2f tadj(m_11, -m_01, -m_10, m_00);
  *this = tadj * (1 / getDeterminant());
  return *this;
}
Matrix2f 
Matrix2f::operator+(const Matrix2f& other) const
{
  return Matrix2f(this->m_00 + other.m_00, this->m_01 + other.m_01,
                  this->m_10 + other.m_10, this->m_11 + other.m_11);
}
Matrix2f 
Matrix2f::operator-(const Matrix2f& other) const
{
  return Matrix2f(this->m_00 - other.m_00, this->m_01 - other.m_01,
                  this->m_10 - other.m_10, this->m_11 - other.m_11);
}
Matrix2f 
Matrix2f::operator*(const Matrix2f& other) const
{
  return Matrix2f(this->m_00 * other.m_00 + this->m_01 * other.m_10,
                  this->m_00 * other.m_01 + this->m_01 * other.m_11,
                  this->m_10 * other.m_00 + this->m_11 * other.m_10,
                  this->m_10 * other.m_01 + this->m_11 * other.m_11);
}
Matrix2f 
Matrix2f::operator*(float k) const
{
  return Matrix2f(this->m_00 * k, this->m_01 * k,
                  this->m_10 * k, this->m_11 * k);
}
Matrix2f&
Matrix2f::operator=(const Matrix2f& other)
{
  this->m_00 = other.m_00;
  this->m_01 = other.m_01;
  this->m_10 = other.m_10;
  this->m_11 = other.m_11;
  return *this;
}
Matrix2f&
Matrix2f::operator+=(const Matrix2f& other)
{
  *this = *this + other;
  return *this;
}
Matrix2f&
Matrix2f::operator-=(const Matrix2f& other)
{
  *this = *this - other;
  return *this;
}
Matrix2f&
Matrix2f::operator*=(const Matrix2f& other)
{
  *this = *this * other;
  return *this;
}
Matrix2f&
Matrix2f::operator*=(float k)
{
  *this = *this * k;
  return *this;
}
bool 
Matrix2f::operator==(const Matrix2f& other)
{
  for (int32 i = 0; i < 4; ++i) {
    if (!Math::checkFloatsEqual(this->m[i], other.m[i])) {
      return false;
    }
  }
  return true;
}
}