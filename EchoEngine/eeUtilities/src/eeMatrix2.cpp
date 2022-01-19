#include "eeMatrix2.h"
#include "eeVector2.h"
#include "eeMath.h"

namespace eeEngineSDK {
const Matrix2f Matrix2f::kZERO = Matrix2f(0.0f, 0.0f, 0.0f, 0.0f);
const Matrix2f Matrix2f::kONES = Matrix2f(1.0f, 1.0f, 1.0f, 1.0f);
const Matrix2f Matrix2f::kIDENTITY = Matrix2f(1.0f, 0.0f, 0.0f, 1.0f);

const Matrix2i Matrix2i::kZERO = Matrix2i(0, 0, 0, 0);
const Matrix2i Matrix2i::kONES = Matrix2i(1, 1, 1, 1);
const Matrix2i Matrix2i::kIDENTITY = Matrix2i(1, 0, 0, 1);

const Matrix2u Matrix2u::kZERO = Matrix2u(0u, 0u, 0u, 0u);
const Matrix2u Matrix2u::kONES = Matrix2u(1u, 1u, 1u, 1u);
const Matrix2u Matrix2u::kIDENTITY = Matrix2u(1u, 0u, 0u, 1u);


Matrix2f::Matrix2f()
{
}
Matrix2f::Matrix2f(float src[4])
{
  memcpy(m, src, sizeof(float) * 4);
}
Matrix2f::Matrix2f(float _00, float _01, float _10, float _11)
: m_00(_00), 
  m_01(_01), 
  m_10(_10), 
  m_11(_11)
{
}
Matrix2f::~Matrix2f()
{
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


Matrix2i::Matrix2i()
{
}
Matrix2i::Matrix2i(int32 src[4])
{
  memcpy(m, src, sizeof(int32) * 4);
}
Matrix2i::Matrix2i(int32 _00, int32 _01, int32 _10, int32 _11)
: m_00(_00),
  m_01(_01),
  m_10(_10),
  m_11(_11)
{
}
Matrix2i::~Matrix2i()
{
}

float 
Matrix2i::getDeterminant() const
{
  return static_cast<float>(m_00 * m_11) - static_cast<float>(m_01 * m_10);
}
Matrix2i&
Matrix2i::transpose()
{
  *this = Matrix2i(m_00, m_10, m_01, m_11);
  return *this;
}
Matrix2i 
Matrix2i::getTranspose() const
{
  return Matrix2i(m_00, m_10, m_01, m_11);
}
Matrix2i 
Matrix2i::operator+(const Matrix2i& other) const
{
  return Matrix2i(this->m_00 + other.m_00, this->m_01 + other.m_01,
                  this->m_10 + other.m_10, this->m_11 + other.m_11);
}
Matrix2i 
Matrix2i::operator-(const Matrix2i& other) const
{
  return Matrix2i(this->m_00 - other.m_00, this->m_01 - other.m_01,
                  this->m_10 - other.m_10, this->m_11 - other.m_11);
}
Matrix2i 
Matrix2i::operator*(const Matrix2i& other) const
{
  return Matrix2i(this->m_00 * other.m_00 + this->m_01 * other.m_10,
                  this->m_00 * other.m_01 + this->m_01 * other.m_11,
                  this->m_10 * other.m_00 + this->m_11 * other.m_10,
                  this->m_10 * other.m_01 + this->m_11 * other.m_11);
}
Matrix2i 
Matrix2i::operator*(int32 k) const
{
  return Matrix2i(this->m_00 * k, this->m_01 * k,
                  this->m_10 * k, this->m_11 * k);
}
Matrix2i&
Matrix2i::operator=(const Matrix2i& other)
{
  this->m_00 = other.m_00;
  this->m_01 = other.m_01;
  this->m_10 = other.m_10;
  this->m_11 = other.m_11;
  return *this;
}
Matrix2i&
Matrix2i::operator+=(const Matrix2i& other)
{
  *this = *this + other;
  return *this;
}
Matrix2i&
Matrix2i::operator-=(const Matrix2i& other)
{
  *this = *this - other;
  return *this;
}
Matrix2i&
Matrix2i::operator*=(const Matrix2i& other)
{
  *this = *this * other;
  return *this;
}
Matrix2i&
Matrix2i::operator*=(int32 k)
{
  *this = *this * k;
  return *this;
}
bool
Matrix2i::operator==(const Matrix2i& other)
{
  for (int32 i = 0; i < 4; ++i) {
    if (this->m[i] != other.m[i]) {
      return false;
    }
  }
  return true;
}


Matrix2u::Matrix2u()
{
}
Matrix2u::Matrix2u(uint32 src[4])
{
  memcpy(m, src, sizeof(uint32) * 4);
}
Matrix2u::Matrix2u(uint32 _00, uint32 _01, uint32 _10, uint32 _11)
: m_00(_00),
  m_01(_01),
  m_10(_10),
  m_11(_11)
{
}
Matrix2u::~Matrix2u()
{
}

float 
Matrix2u::getDeterminant() const
{
  return static_cast<float>(m_00 * m_11) - static_cast<float>(m_01 * m_10);
}
Matrix2u 
Matrix2u::getTranspose() const
{
  return Matrix2u(m_00, m_10, m_01, m_11);
}
Matrix2u& 
Matrix2u::transpose()
{
  *this = Matrix2u(m_00, m_10, m_01, m_11);
  return *this;
}
Matrix2u 
Matrix2u::operator+(const Matrix2u& other) const
{
  return Matrix2u(this->m_00 + other.m_00, this->m_01 + other.m_01,
                  this->m_10 + other.m_10, this->m_11 + other.m_11);
}
Matrix2u 
Matrix2u::operator-(const Matrix2u& other) const
{
  return Matrix2u(this->m_00 - other.m_00, this->m_01 - other.m_01,
                  this->m_10 - other.m_10, this->m_11 - other.m_11);
}
Matrix2u 
Matrix2u::operator*(const Matrix2u& other) const
{
  return Matrix2u(this->m_00 * other.m_00 + this->m_01 * other.m_10,
                  this->m_00 * other.m_01 + this->m_01 * other.m_11,
                  this->m_10 * other.m_00 + this->m_11 * other.m_10,
                  this->m_10 * other.m_01 + this->m_11 * other.m_11);
}
Matrix2u 
Matrix2u::operator*(uint32 k) const
{
  return Matrix2u(this->m_00 * k, this->m_01 * k,
                  this->m_10 * k, this->m_11 * k);
}
Matrix2u&
Matrix2u::operator=(const Matrix2u& other)
{
  this->m_00 = other.m_00;
  this->m_01 = other.m_01;
  this->m_10 = other.m_10;
  this->m_11 = other.m_11;
  return *this;
}
Matrix2u&
Matrix2u::operator+=(const Matrix2u& other)
{
  *this = *this + other;
  return *this;
}
Matrix2u&
Matrix2u::operator-=(const Matrix2u& other)
{
  *this = *this - other;
  return *this;
}
Matrix2u&
Matrix2u::operator*=(const Matrix2u& other)
{
  *this = *this * other;
  return *this;
}
Matrix2u&
Matrix2u::operator*=(uint32 k)
{
  *this = *this * k;
  return *this;
}
bool
Matrix2u::operator==(const Matrix2u& other)
{
  for (int32 i = 0; i < 4; ++i) {
    if (this->m[i] != other.m[i]) {
      return false;
    }
  }
  return true;
}
}