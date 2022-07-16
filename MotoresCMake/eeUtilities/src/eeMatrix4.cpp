#include "eeMatrix4.h"
#include "eeMatrix3.h"
#include "eeVector3.h"
#include "eeVector4.h"
#include "eeMath.h"

namespace eeEngineSDK {
const Matrix4f Matrix4f::kZERO = Matrix4f(0.0f, 0.0f, 0.0f, 0.0f,
                                          0.0f, 0.0f, 0.0f, 0.0f,
                                          0.0f, 0.0f, 0.0f, 0.0f,
                                          0.0f, 0.0f, 0.0f, 0.0f);
const Matrix4f Matrix4f::kONES = Matrix4f(1.0f, 1.0f, 1.0f, 1.0f,
                                          1.0f, 1.0f, 1.0f, 1.0f,
                                          1.0f, 1.0f, 1.0f, 1.0f,
                                          1.0f, 1.0f, 1.0f, 1.0f);
const Matrix4f Matrix4f::kIDENTITY = Matrix4f(1.0f, 0.0f, 0.0f, 0.0f,
                                              0.0f, 1.0f, 0.0f, 0.0f,
                                              0.0f, 0.0f, 1.0f, 0.0f,
                                              0.0f, 0.0f, 0.0f, 1.0f);



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
  Matrix4f rx( 1.0f,               0.0f,                0.0f, 0.0f,
               0.0f, Math::cos(angle.x), -Math::sin(angle.x), 0.0f,
               0.0f, Math::sin(angle.x),  Math::cos(angle.x), 0.0f, 
               0.0f,               0.0f,                0.0f, 1.0f);

  Matrix4f ry( Math::cos(angle.y), 0.0f, Math::sin(angle.y), 0.0f,
                             0.0f, 1.0f,               0.0f, 0.0f,
              -Math::sin(angle.y), 0.0f, Math::cos(angle.y), 0.0f,
                             0.0f, 0.0f,               0.0f, 1.0f);

  Matrix4f rz(Math::cos(angle.z), -Math::sin(angle.z), 0.0f, 0.0f,
              Math::sin(angle.z),  Math::cos(angle.z), 0.0f, 0.0f,
                            0.0f,                0.0f, 1.0f, 0.0f,
                            0.0f,                0.0f, 0.0f, 1.0f);

  Matrix4f rzy = rz * ry;
  return rzy * rx;
}
Matrix4f
  Matrix4f::scaleMatrix(const Vector3f& scale)
{
  return Matrix4f(scale.x,    0.0f,    0.0f, 0.0f,
                     0.0f, scale.y,    0.0f, 0.0f,
                     0.0f,    0.0f, scale.z, 0.0f,
                     0.0f,    0.0f,    0.0f, 1.0f);
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
                  -x.dot(eye), -y.dot(eye), -z.dot(eye), 1);
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

  return Matrix4f(2 / (r - l),            0,            0,  -((r + l) / (r - l)),
                            0,  2 / (t - b),            0,  -((t + b) / (t - b)),
                            0,            0,  2 / (f - n),  -((f + n) / (f - n)),
                            0,            0,            0,                     1);
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

  return Matrix4f(height / AspectRatio,      0,                              0, 0,
                                     0, height,                              0, 0,
                                     0,      0,        (FarZ / (FarZ - NearZ)), 1,
                                     0,      0, -FarZ / (FarZ - NearZ) * NearZ, 0);
}



Matrix4f::Matrix4f(float src[16])
{
  memcpy(m, src, sizeof(float) * 16);
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
  return Matrix4f(this->m_00 * other.m_00 + this->m_01 * other.m_10 
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
  return Vector4f(m_00 * v.x + m_01 * v.y + m_02 * v.z + m_03 * v.w,
                  m_10 * v.x + m_11 * v.y + m_12 * v.z + m_13 * v.w,
                  m_20 * v.x + m_21 * v.y + m_22 * v.z + m_23 * v.w,
                  m_30 * v.x + m_31 * v.y + m_32 * v.z + m_33 * v.w);
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
  for (int32 i = 0; i < 16; ++i) {
    if (!Math::checkFloatsEqual(this->m[i], other.m[i])) {
      return false;
    }
  }
  return true;
}
}