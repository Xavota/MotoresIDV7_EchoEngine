#include "eeMatrix4.h"
#include "eeMatrix3.h"
#include "eeVector3.h"
#include "eeVector4.h"
#include "eeMath.h"

namespace eeEngineSDK {
const Matrix4f Matrix4f::ZERO = Matrix4f(0.0f, 0.0f, 0.0f, 0.0f,
                                         0.0f, 0.0f, 0.0f, 0.0f,
                                         0.0f, 0.0f, 0.0f, 0.0f,
                                         0.0f, 0.0f, 0.0f, 0.0f);
const Matrix4f Matrix4f::ONES = Matrix4f(1.0f, 1.0f, 1.0f, 1.0f,
                                         1.0f, 1.0f, 1.0f, 1.0f,
                                         1.0f, 1.0f, 1.0f, 1.0f,
                                         1.0f, 1.0f, 1.0f, 1.0f);
const Matrix4f Matrix4f::IDENTITY = Matrix4f(1.0f, 0.0f, 0.0f, 0.0f,
                                             0.0f, 1.0f, 0.0f, 0.0f,
                                             0.0f, 0.0f, 1.0f, 0.0f,
                                             0.0f, 0.0f, 0.0f, 1.0f);


const Matrix4i Matrix4i::ZERO = Matrix4i(0, 0, 0, 0,
                                         0, 0, 0, 0,
                                         0, 0, 0, 0,
                                         0, 0, 0, 0);
const Matrix4i Matrix4i::ONES = Matrix4i(1, 1, 1, 1,
                                         1, 1, 1, 1,
                                         1, 1, 1, 1,
                                         1, 1, 1, 1);
const Matrix4i Matrix4i::IDENTITY = Matrix4i(1, 0, 0, 0,
                                             0, 1, 0, 0,
                                             0, 0, 1, 0,
                                             0, 0, 0, 1);


const Matrix4u Matrix4u::ZERO = Matrix4u(0u, 0u, 0u, 0u,
                                         0u, 0u, 0u, 0u,
                                         0u, 0u, 0u, 0u,
                                         0u, 0u, 0u, 0u);
const Matrix4u Matrix4u::ONES = Matrix4u(1u, 1u, 1u, 1u,
                                         1u, 1u, 1u, 1u,
                                         1u, 1u, 1u, 1u,
                                         1u, 1u, 1u, 1u);
const Matrix4u Matrix4u::IDENTITY = Matrix4u(1u, 0u, 0u, 0u,
                                             0u, 1u, 0u, 0u,
                                             0u, 0u, 1u, 0u,
                                             0u, 0u, 0u, 1u);



Matrix4f
Matrix4f::translationMatrix(const Vector3f& move)
{
  return Matrix4f(1.0f, 0.0f, 0.0f, move.x,
                  0.0f, 1.0f, 0.0f, move.y,
                  0.0f, 0.0f, 1.0f, move.z,
                  0.0f, 0.0f, 0.0f, 1.0f);
}
Matrix4f
Matrix4f::rotationMatrix(const Vector3f& angle)
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
  Matrix4f::scaleMatrix(const Vector3f& scale)
{
  return Matrix4f(scale.x, 0.0f,    0.0f,    0.0f,
                  0.0f,    scale.y, 0.0f,    0.0f,
                  0.0f,    0.0f,    scale.z, 0.0f,
                  0.0f,    0.0f,    0.0f,    1.0f);
}

Matrix4f Matrix4f::viewMatrix(const Vector3f& eye, 
                              const Vector3f& lookAt,
                              const Vector3f& worldUp)
{
  Vector3f z = lookAt - eye;
  z.normalize();

  Vector3f x = worldUp.cross(z);
  x.normalize();

  Vector3f y = z.cross(x);

  return Matrix4f(        x.x,         y.x,         z.x, 0,
                          x.y,         y.y,         z.y, 0,
                          x.z,         y.z,         z.z, 0,
                  -x.dot(eye), -y.dot(eye), -z.dot(eye), 1 );
}

Matrix4f Matrix4f::orthograficMatrixMatrix(float ViewWidth,
                                           float ViewHeight, 
                                           float NearZ, 
                                           float FarZ)
{
  float r = ViewWidth / 2;
  float l = -ViewWidth / 2;
  float t = ViewHeight / 2;
  float b = -ViewHeight / 2;
  float f = (FarZ - NearZ) / 2;
  float n = -(FarZ - NearZ) / 2;

  return Matrix4f(
      2 / (r - l),            0,            0,  -((r + l) / (r - l)),
                0,  2 / (t - b),            0,  -((t + b) / (t - b)),
                0,            0,  2 / (f - n),  -((f + n) / (f - n)),
                0,            0,            0,                     1
  );
}

Matrix4f Matrix4f::perspectiveMatrix(float FovAngleY, 
                                     float AspectRatio,
                                     float NearZ, 
                                     float FarZ)
{
  float fovCos = Math::cos(FovAngleY * .5f);
  float fovSin = Math::sin(FovAngleY * .5f);
  float height = fovCos / fovSin;
  //float width = AspectRatio * height;

  return Matrix4f(
      height / AspectRatio, 0, 0, 0,
      0, height, 0, 0,
      0, 0, (FarZ / (FarZ - NearZ)), 1,
      0, 0, -FarZ / (FarZ - NearZ) * NearZ, 0
  );
}



Matrix4f::Matrix4f() 
{
}
Matrix4f::Matrix4f(float src[16])
{
  //memcpy(m, src, sizeof(float) * 16);
  //Copy(m, m + 16, src);
  std::copy(src, src + 16, m);
}
Matrix4f::Matrix4f(float _00, float _01, float _02, float _03,
                   float _10, float _11, float _12, float _13,
                   float _20, float _21, float _22, float _23,
                   float _30, float _31, float _32, float _33)
                  : m_00(_00), m_01(_01), m_02(_02), m_03(_03),
                    m_10(_10), m_11(_11), m_12(_12), m_13(_13),
                    m_20(_20), m_21(_21), m_22(_22), m_23(_23),
                    m_30(_30), m_31(_31), m_32(_32), m_33(_33)
{
}
Matrix4f::~Matrix4f()
{
}
float
Matrix4f::getDeterminant() const
{
  /*return m_00 * m_11 * m_22 * m_33 + m_01 * m_12 * m_23 * m_30 +
         m_02 * m_13 * m_20 * m_31 + m_03 * m_10 * m_21 * m_32 - 
         m_03 * m_12 * m_21 * m_30 - m_00 * m_13 * m_22 * m_31 - 
         m_01 * m_10 * m_23 * m_32 - m_02 * m_11 * m_20 * m_33;*/
  return m_00 * Matrix3f(m_11, m_12, m_13,
                         m_21, m_22, m_23,
                         m_31, m_32, m_33).getDeterminant() -
         m_01 * Matrix3f(m_10, m_12, m_13,
                         m_20, m_22, m_23,
                         m_30, m_32, m_33).getDeterminant() +
         m_02 * Matrix3f(m_10, m_11, m_13,
                         m_20, m_21, m_23,
                         m_30, m_31, m_33).getDeterminant() -
         m_03 * Matrix3f(m_10, m_11, m_12,
                         m_20, m_21, m_22,
                         m_30, m_31, m_32).getDeterminant();
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
  *this *= translationMatrix(move);
  return *this;
}
Matrix4f&
Matrix4f::rotate(const Vector3f& angle)
{
  *this *= rotationMatrix(angle);
  return *this;
}
Matrix4f&
  Matrix4f::scale(const Vector3f& scale)
{
  *this *= scaleMatrix(scale);
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
Vector4f
Matrix4f::operator*(const Vector4f& v) const
{
  return Vector4f(
    m_00 * v.x + m_01 * v.y + m_02 * v.z + m_03 * v.w,
    m_10 * v.x + m_11 * v.y + m_12 * v.z + m_13 * v.w,
    m_20 * v.x + m_21 * v.y + m_22 * v.z + m_23 * v.w,
    m_30 * v.x + m_31 * v.y + m_32 * v.z + m_33 * v.w
  );
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
    if (Math::abs(this->m[i] - other.m[i]) > 
        Math::kFLOAT_EQUAL_SMALL_DIFFERENCE)
    {
      return false;
    }
  }
  return true;
}



Matrix4i::Matrix4i()
{
}
Matrix4i::Matrix4i(int32 src[16])
{
  //memcpy(m, src, sizeof(int32) * 16);
  //Copy(m, m + 16, src);
  std::copy(src, src + 16, m);
}
Matrix4i::Matrix4i(int32 _00, int32 _01, int32 _02, int32 _03,
                   int32 _10, int32 _11, int32 _12, int32 _13,
                   int32 _20, int32 _21, int32 _22, int32 _23,
                   int32 _30, int32 _31, int32 _32, int32 _33)
                  : m_00(_00), m_01(_01), m_02(_02), m_03(_03),
                    m_10(_10), m_11(_11), m_12(_12), m_13(_13),
                    m_20(_20), m_21(_21), m_22(_22), m_23(_23),
                    m_30(_30), m_31(_31), m_32(_32), m_33(_33)
{
}
Matrix4i::~Matrix4i()
{
}
float
Matrix4i::getDeterminant() const
{
  /*return static_cast<float>(m_00 * m_11 * m_22 * m_33) +
         static_cast<float>(m_01 * m_12 * m_23 * m_30) + 
         static_cast<float>(m_02 * m_13 * m_20 * m_31) + 
         static_cast<float>(m_03 * m_10 * m_21 * m_32) -
         static_cast<float>(m_03 * m_12 * m_21 * m_30) - 
         static_cast<float>(m_00 * m_13 * m_22 * m_31) - 
         static_cast<float>(m_01 * m_10 * m_23 * m_32) - 
         static_cast<float>(m_02 * m_11 * m_20 * m_33);*/
  return m_00 * Matrix3f(static_cast<float>(m_11), 
                         static_cast<float>(m_12), 
                         static_cast<float>(m_13),
                         static_cast<float>(m_21), 
                         static_cast<float>(m_22), 
                         static_cast<float>(m_23),
                         static_cast<float>(m_31),
                         static_cast<float>(m_32), 
                         static_cast<float>(m_33)).getDeterminant() -
         m_01 * Matrix3f(static_cast<float>(m_10), 
                         static_cast<float>(m_12), 
                         static_cast<float>(m_13),
                         static_cast<float>(m_20), 
                         static_cast<float>(m_22), 
                         static_cast<float>(m_23),
                         static_cast<float>(m_30), 
                         static_cast<float>(m_32), 
                         static_cast<float>(m_33)).getDeterminant() +
         m_02 * Matrix3f(static_cast<float>(m_10), 
                         static_cast<float>(m_11), 
                         static_cast<float>(m_13),
                         static_cast<float>(m_20), 
                         static_cast<float>(m_21), 
                         static_cast<float>(m_23),
                         static_cast<float>(m_30), 
                         static_cast<float>(m_31), 
                         static_cast<float>(m_33)).getDeterminant() -
         m_03 * Matrix3f(static_cast<float>(m_10), 
                         static_cast<float>(m_11), 
                         static_cast<float>(m_12),
                         static_cast<float>(m_20), 
                         static_cast<float>(m_21), 
                         static_cast<float>(m_22),
                         static_cast<float>(m_30), 
                         static_cast<float>(m_31), 
                         static_cast<float>(m_32)).getDeterminant();
}
Matrix4i
Matrix4i::getTranspose() const
{
  return Matrix4i(m_00, m_10, m_20, m_30,
                  m_01, m_11, m_21, m_31,
                  m_02, m_12, m_22, m_32,
                  m_03, m_13, m_23, m_33);
}
Matrix4i&
Matrix4i::transpose()
{
  *this = getTranspose();
  return *this;
}
Matrix4i
Matrix4i::operator+(const Matrix4i& other) const
{
  return Matrix4i(this->m_00 + other.m_00,
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
Matrix4i
Matrix4i::operator-(const Matrix4i& other) const
{
  return Matrix4i(this->m_00 - other.m_00,
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
Matrix4i
Matrix4i::operator*(const Matrix4i& other) const
{
  return Matrix4i(
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
    + this->m_32 * other.m_23 + this->m_33 * other.m_33);
}
Matrix4i
Matrix4i::operator*(int32 k) const
{
  return Matrix4i(this->m_00 * k,
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
Matrix4i&
Matrix4i::operator=(const Matrix4i& other)
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
Matrix4i&
Matrix4i::operator+=(const Matrix4i& other)
{
  *this = *this + other;
  return *this;
}
Matrix4i&
Matrix4i::operator-=(const Matrix4i& other)
{
  *this = *this - other;
  return *this;
}
Matrix4i&
Matrix4i::operator*=(const Matrix4i& other)
{
  *this = *this * other;
  return *this;
}
Matrix4i&
Matrix4i::operator*=(int32 k)
{
  *this = *this * k;
  return *this;
}
bool
Matrix4i::operator==(const Matrix4i& other)
{
  for (int i = 0; i < 16; ++i)
  {
    if (this->m[i] != other.m[i])
    {
      return false;
    }
  }
  return true;
}



Matrix4u::Matrix4u()
{
}
Matrix4u::Matrix4u(uint32 src[16])
{
  //memcpy(m, src, sizeof(uint32) * 16);
  //Copy(m, m + 16, src);
  std::copy(src, src + 16, m);
}
Matrix4u::Matrix4u(uint32 _00, uint32 _01, uint32 _02, uint32 _03,
                   uint32 _10, uint32 _11, uint32 _12, uint32 _13,
                   uint32 _20, uint32 _21, uint32 _22, uint32 _23,
                   uint32 _30, uint32 _31, uint32 _32, uint32 _33)
                   : m_00(_00), m_01(_01), m_02(_02), m_03(_03),
                     m_10(_10), m_11(_11), m_12(_12), m_13(_13),
                     m_20(_20), m_21(_21), m_22(_22), m_23(_23),
                     m_30(_30), m_31(_31), m_32(_32), m_33(_33)
{
}
Matrix4u::~Matrix4u()
{
}
float
Matrix4u::getDeterminant() const
{
  /*return static_cast<float>(m_00 * m_11 * m_22 * m_33) +
         static_cast<float>(m_01 * m_12 * m_23 * m_30) +
         static_cast<float>(m_02 * m_13 * m_20 * m_31) +
         static_cast<float>(m_03 * m_10 * m_21 * m_32) -
         static_cast<float>(m_03 * m_12 * m_21 * m_30) -
         static_cast<float>(m_00 * m_13 * m_22 * m_31) -
         static_cast<float>(m_01 * m_10 * m_23 * m_32) -
         static_cast<float>(m_02 * m_11 * m_20 * m_33);*/
  return m_00 * Matrix3f(static_cast<float>(m_11),
                         static_cast<float>(m_12),
                         static_cast<float>(m_13),
                         static_cast<float>(m_21),
                         static_cast<float>(m_22),
                         static_cast<float>(m_23),
                         static_cast<float>(m_31),
                         static_cast<float>(m_32),
                         static_cast<float>(m_33)).getDeterminant() -
         m_01 * Matrix3f(static_cast<float>(m_10),
                         static_cast<float>(m_12),
                         static_cast<float>(m_13),
                         static_cast<float>(m_20),
                         static_cast<float>(m_22),
                         static_cast<float>(m_23),
                         static_cast<float>(m_30),
                         static_cast<float>(m_32),
                         static_cast<float>(m_33)).getDeterminant() +
         m_02 * Matrix3f(static_cast<float>(m_10),
                         static_cast<float>(m_11),
                         static_cast<float>(m_13),
                         static_cast<float>(m_20),
                         static_cast<float>(m_21),
                         static_cast<float>(m_23),
                         static_cast<float>(m_30),
                         static_cast<float>(m_31),
                         static_cast<float>(m_33)).getDeterminant() -
         m_03 * Matrix3f(static_cast<float>(m_10),
                         static_cast<float>(m_11),
                         static_cast<float>(m_12),
                         static_cast<float>(m_20),
                         static_cast<float>(m_21),
                         static_cast<float>(m_22),
                         static_cast<float>(m_30),
                         static_cast<float>(m_31),
                         static_cast<float>(m_32)).getDeterminant();
}
Matrix4u
Matrix4u::getTranspose() const
{
  return Matrix4u(m_00, m_10, m_20, m_30,
                  m_01, m_11, m_21, m_31,
                  m_02, m_12, m_22, m_32,
                  m_03, m_13, m_23, m_33);
}
Matrix4u&
Matrix4u::transpose()
{
  *this = getTranspose();
  return *this;
}
Matrix4u
Matrix4u::operator+(const Matrix4u& other) const
{
  return Matrix4u(this->m_00 + other.m_00,
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
Matrix4u
Matrix4u::operator-(const Matrix4u& other) const
{
  return Matrix4u(this->m_00 - other.m_00,
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
Matrix4u
Matrix4u::operator*(const Matrix4u& other) const
{
  return Matrix4u(
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
    + this->m_32 * other.m_23 + this->m_33 * other.m_33);
}
Matrix4u
Matrix4u::operator*(uint32 k) const
{
  return Matrix4u(this->m_00 * k,
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
Matrix4u&
Matrix4u::operator=(const Matrix4u& other)
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
Matrix4u&
Matrix4u::operator+=(const Matrix4u& other)
{
  *this = *this + other;
  return *this;
}
Matrix4u&
Matrix4u::operator-=(const Matrix4u& other)
{
  *this = *this - other;
  return *this;
}
Matrix4u&
Matrix4u::operator*=(const Matrix4u& other)
{
  *this = *this * other;
  return *this;
}
Matrix4u&
Matrix4u::operator*=(uint32 k)
{
  *this = *this * k;
  return *this;
}
bool
Matrix4u::operator==(const Matrix4u& other)
{
  for (int i = 0; i < 16; ++i)
  {
    if (this->m[i] != other.m[i])
    {
      return false;
    }
  }
  return true;
}
}