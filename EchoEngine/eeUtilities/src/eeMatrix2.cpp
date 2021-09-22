#include "eeMatrix2.h"

namespace eeEngineSDK {
Matrix2f Matrix2f::ZERO = Matrix2f(0.0f, 0.0f, 0.0f, 0.0f);
Matrix2f Matrix2f::ONES = Matrix2f(1.0f, 1.0f, 1.0f, 1.0f);
Matrix2f Matrix2f::IDENTITY = Matrix2f(1.0f, 0.0f, 0.0f, 1.0f);

Matrix2f::Matrix2f() : m_00(0.0f), m_01(0.0f), m_10(0.0f), m_11(0.0f)
{
}

Matrix2f::Matrix2f(float src[4])
{
  memcpy(m, src, sizeof(float) * 4);
}

Matrix2f::Matrix2f(const Vector2f& r0, const Vector2f& r1)
{
  m_r0 = r0;
  m_r1 = r1;
}

Matrix2f::Matrix2f(float _00, float _01, float _10, float _11)
{
  m_00 = _00;
  m_01 = _01;
  m_10 = _10;
  m_11 = _11;
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
  for (int i = 0; i < 4; ++i)
  {
    if (Math::abs(this->m[i] - other.m[i]) > .001f)
    {
      return false;
    }
  }
  return true;
}



Matrix2i Matrix2i::ZERO = Matrix2i(0, 0, 0, 0);
Matrix2i Matrix2i::ONES = Matrix2i(1, 1, 1, 1);
Matrix2i Matrix2i::IDENTITY = Matrix2i(1, 0, 0, 1);

Matrix2i::Matrix2i() : m_00(0), m_01(0), m_10(0), m_11(0)
{
}

Matrix2i::Matrix2i(int32 src[4])
{
  memcpy(m, src, sizeof(int32) * 4);
}

Matrix2i::Matrix2i(const Vector2i& r0, const Vector2i& r1)
{
  m_r0 = r0;
  m_r1 = r1;
}

Matrix2i::Matrix2i(int32 _00, int32 _01, int32 _10, int32 _11)
{
  m_00 = _00;
  m_01 = _01;
  m_10 = _10;
  m_11 = _11;
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
  for (int i = 0; i < 4; ++i)
  {
    if (this->m[i] != other.m[i])
    {
      return false;
    }
  }
  return true;
}



Matrix2u Matrix2u::ZERO = Matrix2u(0u, 0u, 0u, 0u);
Matrix2u Matrix2u::ONES = Matrix2u(1u, 1u, 1u, 1u);
Matrix2u Matrix2u::IDENTITY = Matrix2u(1u, 0u, 0u, 1u);

Matrix2u::Matrix2u() : m_00(0u), m_01(0u), m_10(0u), m_11(0u)
{
}

Matrix2u::Matrix2u(uint32 src[4])
{
  memcpy(m, src, sizeof(uint32) * 4);
}

Matrix2u::Matrix2u(const Vector2u& r0, const Vector2u& r1)
{
  m_r0 = r0;
  m_r1 = r1;
}

Matrix2u::Matrix2u(uint32 _00, uint32 _01, uint32 _10, uint32 _11)
{
  m_00 = _00;
  m_01 = _01;
  m_10 = _10;
  m_11 = _11;
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
  for (int i = 0; i < 4; ++i)
  {
    if (this->m[i] != other.m[i])
    {
      return false;
    }
  }
  return true;
}
}