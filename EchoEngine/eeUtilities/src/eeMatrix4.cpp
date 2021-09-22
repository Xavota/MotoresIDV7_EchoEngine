#include "eeMatrix4.h"
#include "eeMatrix3.h"

namespace eeEngineSDK {
Matrix4f Matrix4f::ZERO = Matrix4f(0.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f);
Matrix4f Matrix4f::ONES = Matrix4f(1.0f, 1.0f, 1.0f, 1.0f,
                                   1.0f, 1.0f, 1.0f, 1.0f,
                                   1.0f, 1.0f, 1.0f, 1.0f,
                                   1.0f, 1.0f, 1.0f, 1.0f);
Matrix4f Matrix4f::IDENTITY = Matrix4f(1.0f, 0.0f, 0.0f, 0.0f,
                                       0.0f, 1.0f, 0.0f, 0.0f,
                                       0.0f, 0.0f, 1.0f, 0.0f,
                                       0.0f, 0.0f, 0.0f, 1.0f);


Matrix4i Matrix4i::ZERO = Matrix4i(0, 0, 0, 0,
                                   0, 0, 0, 0,
                                   0, 0, 0, 0,
                                   0, 0, 0, 0);
Matrix4i Matrix4i::ONES = Matrix4i(1, 1, 1, 1,
                                   1, 1, 1, 1,
                                   1, 1, 1, 1,
                                   1, 1, 1, 1);
Matrix4i Matrix4i::IDENTITY = Matrix4i(1, 0, 0, 0,
                                       0, 1, 0, 0,
                                       0, 0, 1, 0,
                                       0, 0, 0, 1);


Matrix4u Matrix4u::ZERO = Matrix4u(0u, 0u, 0u, 0u,
                                   0u, 0u, 0u, 0u,
                                   0u, 0u, 0u, 0u,
                                   0u, 0u, 0u, 0u);
Matrix4u Matrix4u::ONES = Matrix4u(1u, 1u, 1u, 1u,
                                   1u, 1u, 1u, 1u,
                                   1u, 1u, 1u, 1u,
                                   1u, 1u, 1u, 1u);
Matrix4u Matrix4u::IDENTITY = Matrix4u(1u, 0u, 0u, 0u,
                                       0u, 1u, 0u, 0u,
                                       0u, 0u, 1u, 0u,
                                       0u, 0u, 0u, 1u);



Matrix4f
Matrix4f::TranslationMatrix(const Vector3f& move)
{
  return Matrix4f(1.0f, 0.0f, 0.0f, move.x,
                  0.0f, 1.0f, 0.0f, move.y,
                  0.0f, 0.0f, 1.0f, move.z,
                  0.0f, 0.0f, 0.0f, 1.0f);
}
Matrix4f
Matrix4f::RotationMatrix(const Vector3f& angle)
{
  Matrix4f rx( 1.0f, 0.0f,                0.0f,               0.0f,
               0.0f, Math::cos(angle.x), -Math::sin(angle.x), 0.0f,
               0.0f, Math::sin(angle.x),  Math::cos(angle.x), 0.0f, 
               0.0f, 0.0f,                0.0f,               1.0f);
  Matrix4f ry( Math::cos(angle.y), 0.0f, Math::sin(angle.y), 0.0f,
               0.0f,               1.0f, 0.0f,               0.0f,
              -Math::sin(angle.y), 0.0f, Math::cos(angle.y), 0.0f,
               0.0f,               0.0f, 0.0f,               1.0f);
  Matrix4f rz(Math::cos(angle.z), -Math::sin(angle.z), 0.0f, 0.0f,
              Math::sin(angle.z),  Math::cos(angle.z), 0.0f, 0.0f,
              0.0f,                0.0f,               1.0f, 0.0f,
              0.0f,                0.0f,               0.0f, 1.0f);

  Matrix4f rzy = rz * ry;
  return rzy * rx;
}
Matrix4f
  Matrix4f::ScaleMatrix(const Vector3f& scale)
{
  return Matrix4f(scale.x, 0.0f,    0.0f,    0.0f,
                  0.0f,    scale.y, 0.0f,    0.0f,
                  0.0f,    0.0f,    scale.z, 0.0f,
                  0.0f,    0.0f,    0.0f,    1.0f);
}



Matrix4f::Matrix4f() : m_00(0.0f), m_01(0.0f), m_02(0.0f), m_03(0.0f),
                       m_10(0.0f), m_11(0.0f), m_12(0.0f), m_13(0.0f),
                       m_20(0.0f), m_21(0.0f), m_22(0.0f), m_23(0.0f),
                       m_30(0.0f), m_31(0.0f), m_32(0.0f), m_33(0.0f)
{
}
Matrix4f::Matrix4f(float src[16])
{
  memcpy(m, src, sizeof(float) * 16);
}
Matrix4f::Matrix4f(const Vector4f& r0, const Vector4f& r1, 
                   const Vector4f& r2, const Vector4f& r3)
{
  m_r0 = r0;
  m_r1 = r1;
  m_r2 = r2;
  m_r3 = r3;
}
Matrix4f::Matrix4f(float _00, float _01, float _02, float _03,
                   float _10, float _11, float _12, float _13,
                   float _20, float _21, float _22, float _23,
                   float _30, float _31, float _32, float _33)
{
  m_00 = _00;
  m_01 = _01;
  m_02 = _02;
  m_03 = _03;

  m_10 = _10;
  m_11 = _11;
  m_12 = _12;
  m_13 = _13;

  m_20 = _20;
  m_21 = _21;
  m_22 = _22;
  m_23 = _23;

  m_30 = _30;
  m_31 = _31;
  m_32 = _32;
  m_33 = _33;
}
Matrix4f::~Matrix4f()
{
}
float
Matrix4f::getDeterminant() const
{
  return m_00 * m_11 * m_22 * m_33 + m_01 * m_12 * m_23 * m_30 + 
         m_02 * m_13 * m_20 * m_31 + m_03 * m_10 * m_21 * m_32 - 
         m_03 * m_12 * m_21 * m_30 - m_00 * m_13 * m_22 * m_31 - 
         m_01 * m_10 * m_23 * m_32 - m_02 * m_11 * m_20 * m_33;
}
Matrix4f
Matrix4f::getTranspose() const
{
  return Matrix4f(m_00, m_10, m_20, m_30,
                  m_01, m_11, m_21, m_31,
                  m_02, m_12, m_22, m_32,
                  m_03, m_13, m_23, m_33);
}
Matrix4f&
Matrix4f::transpose()
{
  *this = getTranspose();
  return *this;
}
Matrix4f
Matrix4f::getInverse() const
{
  Matrix4f adj =  Matrix4f( Matrix3f(m_11, m_12, m_13, 
                                     m_21, m_22, m_23, 
                                     m_31, m_32, m_33).getDeterminant(),
                           -Matrix3f(m_10, m_12, m_13, 
                                     m_20, m_22, m_23, 
                                     m_30, m_32, m_33).getDeterminant(),
                            Matrix3f(m_10, m_11, m_13, 
                                     m_20, m_21, m_23, 
                                     m_30, m_31, m_33).getDeterminant(),
                           -Matrix3f(m_10, m_11, m_12, 
                                     m_20, m_21, m_22, 
                                     m_30, m_31, m_32).getDeterminant(),

                                     
                           -Matrix3f(m_01, m_02, m_03, 
                                     m_21, m_22, m_23, 
                                     m_31, m_32, m_33).getDeterminant(),
                            Matrix3f(m_00, m_02, m_03, 
                                     m_20, m_22, m_23, 
                                     m_30, m_32, m_33).getDeterminant(),
                           -Matrix3f(m_00, m_01, m_03, 
                                     m_20, m_21, m_23, 
                                     m_30, m_31, m_33).getDeterminant(),
                            Matrix3f(m_00, m_01, m_02, 
                                     m_20, m_21, m_22, 
                                     m_30, m_31, m_32).getDeterminant(),
                            
                                      
                            Matrix3f(m_01, m_02, m_03, 
                                     m_11, m_12, m_13, 
                                     m_31, m_32, m_33).getDeterminant(),
                           -Matrix3f(m_00, m_02, m_03, 
                                     m_10, m_12, m_13, 
                                     m_30, m_32, m_33).getDeterminant(),
                            Matrix3f(m_00, m_01, m_03, 
                                     m_10, m_11, m_13, 
                                     m_30, m_31, m_33).getDeterminant(),
                           -Matrix3f(m_00, m_01, m_02, 
                                     m_10, m_11, m_12, 
                                     m_30, m_31, m_32).getDeterminant(),
                            
                                      
                           -Matrix3f(m_01, m_02, m_03, 
                                     m_11, m_12, m_13, 
                                     m_21, m_22, m_23).getDeterminant(),
                            Matrix3f(m_00, m_02, m_03,
                                     m_10, m_12, m_13, 
                                     m_20, m_22, m_23).getDeterminant(),
                           -Matrix3f(m_00, m_01, m_03,
                                     m_10, m_11, m_13, 
                                     m_20, m_21, m_23).getDeterminant(),
                            Matrix3f(m_00, m_01, m_02,
                                     m_10, m_11, m_12, 
                                     m_20, m_21, m_22).getDeterminant());

  adj.transpose();
  return adj * (1 / getDeterminant());
}
Matrix4f&
Matrix4f::inverse()
{
  *this = getInverse();
  return *this;
}
Matrix4f&
Matrix4f::translate(const Vector3f& move)
{
  *this *= TranslationMatrix(move);
  return *this;
}
Matrix4f&
Matrix4f::rotate(const Vector3f& angle)
{
  *this *= RotationMatrix(angle);
  return *this;
}
Matrix4f&
  Matrix4f::scale(const Vector3f& scale)
{
  *this *= ScaleMatrix(scale);
  return *this;
}
Matrix4f
Matrix4f::operator+(const Matrix4f& other) const
{
  return Matrix4f(this->m_00 + other.m_00,
                  this->m_01 + other.m_01,
                  this->m_02 + other.m_02,
                  this->m_03 + other.m_03,
                  
                  this->m_10 + other.m_10,
                  this->m_11 + other.m_11,
                  this->m_12 + other.m_12,
                  this->m_13 + other.m_13,
                  
                  this->m_20 + other.m_20,
                  this->m_21 + other.m_21,
                  this->m_22 + other.m_22,
                  this->m_23 + other.m_23,
                  
                  this->m_30 + other.m_30,
                  this->m_31 + other.m_31,
                  this->m_32 + other.m_32,
                  this->m_33 + other.m_33);
}
Matrix4f
Matrix4f::operator-(const Matrix4f& other) const
{
  return Matrix4f(this->m_00 - other.m_00,
                  this->m_01 - other.m_01,
                  this->m_02 - other.m_02,
                  this->m_03 - other.m_03,
                  
                  this->m_10 - other.m_10,
                  this->m_11 - other.m_11,
                  this->m_12 - other.m_12,
                  this->m_13 - other.m_13,
                  
                  this->m_20 - other.m_20,
                  this->m_21 - other.m_21,
                  this->m_22 - other.m_22,
                  this->m_23 - other.m_23,
                  
                  this->m_30 - other.m_30,
                  this->m_31 - other.m_31,
                  this->m_32 - other.m_32,
                  this->m_33 - other.m_33);
}
Matrix4f
Matrix4f::operator*(const Matrix4f& other) const
{
  return Matrix4f(
    this->m_00 * other.m_00 + this->m_01 * other.m_10 
    + this->m_02 * other.m_20 + this->m_03 * other.m_30,
    this->m_00 * other.m_01 + this->m_01 * other.m_11 
    + this->m_02 * other.m_21 + this->m_03 * other.m_31,
    this->m_00 * other.m_02 + this->m_01 * other.m_12 
    + this->m_02 * other.m_22 + this->m_03 * other.m_32,
    this->m_00 * other.m_03 + this->m_01 * other.m_13 
    + this->m_02 * other.m_23 + this->m_03 * other.m_33,

    this->m_10 * other.m_00 + this->m_11 * other.m_10 
    + this->m_12 * other.m_20 + this->m_13 * other.m_30,
    this->m_10 * other.m_01 + this->m_11 * other.m_11 
    + this->m_12 * other.m_21 + this->m_13 * other.m_31,
    this->m_10 * other.m_02 + this->m_11 * other.m_12 
    + this->m_12 * other.m_22 + this->m_13 * other.m_32,
    this->m_10 * other.m_03 + this->m_11 * other.m_13 
    + this->m_12 * other.m_23 + this->m_13 * other.m_33, 

    this->m_20 * other.m_00 + this->m_21 * other.m_10 
    + this->m_22 * other.m_20 + this->m_23 * other.m_30,
    this->m_20 * other.m_01 + this->m_21 * other.m_11 
    + this->m_22 * other.m_21 + this->m_23 * other.m_31,
    this->m_20 * other.m_02 + this->m_21 * other.m_12 
    + this->m_22 * other.m_22 + this->m_23 * other.m_32,
    this->m_20 * other.m_03 + this->m_21 * other.m_13 
    + this->m_22 * other.m_23 + this->m_23 * other.m_33, 

    this->m_30 * other.m_00 + this->m_31 * other.m_10 
    + this->m_32 * other.m_20 + this->m_33 * other.m_30,
    this->m_30 * other.m_01 + this->m_31 * other.m_11 
    + this->m_32 * other.m_21 + this->m_33 * other.m_31,
    this->m_30 * other.m_02 + this->m_31 * other.m_12 
    + this->m_32 * other.m_22 + this->m_33 * other.m_32,
    this->m_30 * other.m_03 + this->m_31 * other.m_13 
    + this->m_32 * other.m_23 + this->m_33 * other.m_33 );
}
Matrix4f
Matrix4f::operator*(float k) const
{
  return Matrix4f(this->m_00 * k,
                  this->m_01 * k,
                  this->m_02 * k,
                  this->m_03 * k,
                  
                  this->m_10 * k,
                  this->m_11 * k,
                  this->m_12 * k,
                  this->m_13 * k,
                  
                  this->m_20 * k,
                  this->m_21 * k,
                  this->m_22 * k,
                  this->m_23 * k,
                  
                  this->m_30 * k,
                  this->m_31 * k,
                  this->m_32 * k,
                  this->m_33 * k);
}
Matrix4f&
Matrix4f::operator=(const Matrix4f& other)
{
  this->m_00 = other.m_00;
  this->m_01 = other.m_01;
  this->m_02 = other.m_02;
  this->m_03 = other.m_03;

  this->m_10 = other.m_10;
  this->m_11 = other.m_11;
  this->m_12 = other.m_12;
  this->m_13 = other.m_13;

  this->m_20 = other.m_20;
  this->m_21 = other.m_21;
  this->m_22 = other.m_22;
  this->m_23 = other.m_23;

  this->m_30 = other.m_30;
  this->m_31 = other.m_31;
  this->m_32 = other.m_32;
  this->m_33 = other.m_33;
  return *this;
}
Matrix4f&
Matrix4f::operator+=(const Matrix4f& other)
{
  *this = *this + other;
  return *this;
}
Matrix4f&
Matrix4f::operator-=(const Matrix4f& other)
{
  *this = *this - other;
  return *this;
}
Matrix4f&
Matrix4f::operator*=(const Matrix4f& other)
{
  *this = *this * other;
  return *this;
}
Matrix4f&
Matrix4f::operator*=(float k)
{
  *this = *this * k;
  return *this;
}
bool
Matrix4f::operator==(const Matrix4f& other)
{
  for (int i = 0; i < 16; ++i)
  {
    if (Math::abs(this->m[i] - other.m[i]) > .001f)
    {
      return false;
    }
  }
  return true;
}
}