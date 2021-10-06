#include "eeMatrix3.h"
#include "eeMatrix2.h"
#include "eeVector3.h" 
#include "eeMath.h"

namespace eeEngineSDK {
const Matrix3f Matrix3f::ZERO = Matrix3f(0.0f, 0.0f, 0.0f,
                                         0.0f, 0.0f, 0.0f, 
                                         0.0f, 0.0f, 0.0f );
const Matrix3f Matrix3f::ONES = Matrix3f(1.0f, 1.0f, 1.0f,
                                         1.0f, 1.0f, 1.0f, 
                                         1.0f, 1.0f, 1.0f );
const Matrix3f Matrix3f::IDENTITY = Matrix3f(1.0f, 0.0f, 0.0f,
                                             0.0f, 1.0f, 0.0f, 
                                             0.0f, 0.0f, 1.0f);


const Matrix3i Matrix3i::ZERO = Matrix3i(0, 0, 0,
                                         0, 0, 0,
                                         0, 0, 0);
const Matrix3i Matrix3i::ONES = Matrix3i(1, 1, 1,
                                         1, 1, 1,
                                         1, 1, 1);
const Matrix3i Matrix3i::IDENTITY = Matrix3i(1, 0, 0,
                                             0, 1, 0,
                                             0, 0, 1);


const Matrix3u Matrix3u::ZERO = Matrix3u(0u, 0u, 0u,
                                         0u, 0u, 0u,
                                         0u, 0u, 0u);
const Matrix3u Matrix3u::ONES = Matrix3u(1u, 1u, 1u,
                                         1u, 1u, 1u,
                                         1u, 1u, 1u);
const Matrix3u Matrix3u::IDENTITY = Matrix3u(1u, 0u, 0u,
                                             0u, 1u, 0u,
                                             0u, 0u, 1u);



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
  Matrix3f rx( 1.0f, 0.0f,                0.0f,
               0.0f, Math::cos(angle.x), -Math::sin(angle.x),
               0.0f, Math::sin(angle.x),  Math::cos(angle.x));
  Matrix3f ry( Math::cos(angle.y), 0.0f, Math::sin(angle.y),
               0.0f,               1.0f, 0.0f,
              -Math::sin(angle.y), 0.0f, Math::cos(angle.y));
  Matrix3f rz( Math::cos(angle.z), -Math::sin(angle.z), 0.0f,
               Math::sin(angle.z),  Math::cos(angle.z), 0.0f,
               0.0f,                0.0f,               1.0f);

  Matrix3f rzy = rz * ry;
  return rzy * rx;
}
Matrix3f 
Matrix3f::scaleMatrix(const Vector3f& scale)
{
  return Matrix3f(scale.x, 0.0f,    0.0f,
                  0.0f,    scale.y, 0.0f,
                  0.0f,    0.0f,    scale.z);
}



Matrix3f::Matrix3f()
{
}
Matrix3f::Matrix3f(float src[9])
{
  //memcpy(m, src, sizeof(float) * 9);
  //Copy(m, m + 9, src);
  std::copy(src, src + 9, m);
}
Matrix3f::Matrix3f(float _00, float _01, float _02, 
                   float _10, float _11, float _12, 
                   float _20, float _21, float _22) 
                  : m_00(_00), m_01(_01), m_02(_02),
                    m_10(_10), m_11(_11), m_12(_12),
                    m_20(_20), m_21(_21), m_22(_22)
{
}
Matrix3f::~Matrix3f()
{
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
                  m_02, m_12, m_22 );
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
                           Matrix2f(m_00, m_01, m_10, m_11).getDeterminant() );

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
Matrix3f &
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
  for (int i = 0; i < 9; ++i)
  {
    if (Math::abs(this->m[i] - other.m[i]) > 
        Math::kFLOAT_EQUAL_SMALL_DIFFERENCE)
    {
      return false;
    }
  }
  return true;
}



Matrix3i::Matrix3i()
{
}
Matrix3i::Matrix3i(int32 src[9])
{
  //memcpy(m, src, sizeof(int32) * 9);
  //Copy(m, m + 9, src);
  std::copy(src, src + 9, m);
}
Matrix3i::Matrix3i(int32 _00, int32 _01, int32 _02,
                   int32 _10, int32 _11, int32 _12,
                   int32 _20, int32 _21, int32 _22)
                  : m_00(_00), m_01(_01), m_02(_02),
                    m_10(_10), m_11(_11), m_12(_12),
                    m_20(_20), m_21(_21), m_22(_22)
{
}
Matrix3i::~Matrix3i()
{
}
float
Matrix3i::getDeterminant() const
{
  return static_cast<float>(m_00 * m_11 * m_22) +
         static_cast<float>(m_01 * m_12 * m_20) +
         static_cast<float>(m_02 * m_10 * m_21) -
         static_cast<float>(m_02 * m_11 * m_20) -
         static_cast<float>(m_00 * m_12 * m_21) -
         static_cast<float>(m_01 * m_10 * m_22);
}
Matrix3i
Matrix3i::getTranspose() const
{
  return Matrix3i(m_00, m_10, m_20,
                  m_01, m_11, m_21,
                  m_02, m_12, m_22);
}
Matrix3i&
Matrix3i::transpose()
{
  *this = getTranspose();
  return *this;
}
Matrix3i
Matrix3i::operator+(const Matrix3i& other) const
{
  return Matrix3i(this->m_00 + other.m_00,
                  this->m_01 + other.m_01,
                  this->m_02 + other.m_02,
                  
                  this->m_10 + other.m_10,
                  this->m_11 + other.m_11,
                  this->m_12 + other.m_12,
                  
                  this->m_20 + other.m_20,
                  this->m_21 + other.m_21,
                  this->m_22 + other.m_22);
}
Matrix3i
Matrix3i::operator-(const Matrix3i& other) const
{
  return Matrix3i(this->m_00 - other.m_00,
                  this->m_01 - other.m_01,
                  this->m_02 - other.m_02,
                  
                  this->m_10 - other.m_10,
                  this->m_11 - other.m_11,
                  this->m_12 - other.m_12,
                  
                  this->m_20 - other.m_20,
                  this->m_21 - other.m_21,
                  this->m_22 - other.m_22);
}
Matrix3i
Matrix3i::operator*(const Matrix3i& other) const
{
  return Matrix3i(
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
Matrix3i
Matrix3i::operator*(int32 k) const
{
  return Matrix3i(this->m_00 * k,
                  this->m_01 * k,
                  this->m_02 * k,
                  
                  this->m_10 * k,
                  this->m_11 * k,
                  this->m_12 * k,
                  
                  this->m_20 * k,
                  this->m_21 * k,
                  this->m_22 * k);
}
Matrix3i&
Matrix3i::operator=(const Matrix3i& other)
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
Matrix3i&
Matrix3i::operator+=(const Matrix3i& other)
{
  *this = *this + other;
  return *this;
}
Matrix3i&
Matrix3i::operator-=(const Matrix3i& other)
{
  *this = *this - other;
  return *this;
}
Matrix3i&
Matrix3i::operator*=(const Matrix3i& other)
{
  *this = *this * other;
  return *this;
}
Matrix3i&
Matrix3i::operator*=(int32 k)
{
  *this = *this * k;
  return *this;
}
bool
Matrix3i::operator==(const Matrix3i& other)
{
  for (int i = 0; i < 9; ++i)
  {
    if (this->m[i] != other.m[i])
    {
      return false;
    }
  }
  return true;
}



Matrix3u::Matrix3u()
{
}
Matrix3u::Matrix3u(uint32 src[9])
{
  //memcpy(m, src, sizeof(uint32) * 9);
  //Copy(m, m + 9, src);
  std::copy(src, src + 9, m);
}
Matrix3u::Matrix3u(uint32 _00, uint32 _01, uint32 _02,
                   uint32 _10, uint32 _11, uint32 _12,
                   uint32 _20, uint32 _21, uint32 _22)
                   : m_00(_00), m_01(_01), m_02(_02),
                     m_10(_10), m_11(_11), m_12(_12),
                     m_20(_20), m_21(_21), m_22(_22)
{
}
Matrix3u::~Matrix3u()
{
}
float
Matrix3u::getDeterminant() const
{
  return static_cast<float>(m_00 * m_11 * m_22) + 
         static_cast<float>(m_01 * m_12 * m_20) + 
         static_cast<float>(m_02 * m_10 * m_21) - 
         static_cast<float>(m_02 * m_11 * m_20) - 
         static_cast<float>(m_00 * m_12 * m_21) - 
         static_cast<float>(m_01 * m_10 * m_22);
}
Matrix3u
Matrix3u::getTranspose() const
{
  return Matrix3u(m_00, m_10, m_20,
                  m_01, m_11, m_21,
                  m_02, m_12, m_22);
}
Matrix3u&
Matrix3u::transpose()
{
  *this = getTranspose();
  return *this;
}
Matrix3u
Matrix3u::operator+(const Matrix3u& other) const
{
  return Matrix3u(this->m_00 + other.m_00,
                  this->m_01 + other.m_01,
                  this->m_02 + other.m_02,
                  
                  this->m_10 + other.m_10,
                  this->m_11 + other.m_11,
                  this->m_12 + other.m_12,
                  
                  this->m_20 + other.m_20,
                  this->m_21 + other.m_21,
                  this->m_22 + other.m_22);
}
Matrix3u
Matrix3u::operator-(const Matrix3u& other) const
{
  return Matrix3u(this->m_00 - other.m_00,
                  this->m_01 - other.m_01,
                  this->m_02 - other.m_02,
                  
                  this->m_10 - other.m_10,
                  this->m_11 - other.m_11,
                  this->m_12 - other.m_12,
                  
                  this->m_20 - other.m_20,
                  this->m_21 - other.m_21,
                  this->m_22 - other.m_22);
}
Matrix3u
Matrix3u::operator*(const Matrix3u& other) const
{
  return Matrix3u(
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
Matrix3u
Matrix3u::operator*(uint32 k) const
{
  return Matrix3u(this->m_00 * k,
                  this->m_01 * k,
                  this->m_02 * k,
                  
                  this->m_10 * k,
                  this->m_11 * k,
                  this->m_12 * k,
                  
                  this->m_20 * k,
                  this->m_21 * k,
                  this->m_22 * k);
}
Matrix3u&
Matrix3u::operator=(const Matrix3u& other)
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
Matrix3u&
Matrix3u::operator+=(const Matrix3u& other)
{
  *this = *this + other;
  return *this;
}
Matrix3u&
Matrix3u::operator-=(const Matrix3u& other)
{
  *this = *this - other;
  return *this;
}
Matrix3u&
Matrix3u::operator*=(const Matrix3u& other)
{
  *this = *this * other;
  return *this;
}
Matrix3u&
Matrix3u::operator*=(uint32 k)
{
  *this = *this * k;
  return *this;
}
bool
Matrix3u::operator==(const Matrix3u& other)
{
  for (int i = 0; i < 9; ++i)
  {
    if (this->m[i] != other.m[i])
    {
      return false;
    }
  }
  return true;
}
}