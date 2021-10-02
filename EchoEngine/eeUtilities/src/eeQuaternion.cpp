#include "eeQuaternion.h"
#include "eeVector3.h"
#include "eeMatrix4.h"

namespace eeEngineSDK{
Quaternion::Quaternion()
{
}

Quaternion::Quaternion(float _w, float _x, float _y, float _z) : w(_w), 
                                                                 x(_x),
                                                                 y(_y),
                                                                 z(_z)
{
}

Quaternion::Quaternion(const Vector3f& euclidean)
{
  setEuclidean(euclidean);
}

Quaternion::~Quaternion()
{
}

Quaternion Quaternion::getConjugate()
{
  return Quaternion(w, -x, -y, -z);
}

void Quaternion::conjugate()
{
  x = -x;
  y = -y;
  z = -z;
}

Vector3f 
Quaternion::getEuclidean()
{
  Vector3f angles;
  // roll (x-axis rotation)
  float sinr_cosp = 2 * (w * x + y * z);
  float cosr_cosp = 1 - 2 * (x * x + y * y);
  angles.x = Math::atan2(sinr_cosp, cosr_cosp);

  // pitch (y-axis rotation)
  float sinp = 2 * (w * y - z * x);
  if (Math::abs(sinp) >= 1)
    angles.y = std::copysign(Math::kPI / 2, sinp); // use 90 degrees if out of range
  else
    angles.y = Math::asin(sinp);

  // yaw (z-axis rotation)
  float siny_cosp = 2 * (w * z + x * y);
  float cosy_cosp = 1 - 2 * (y * y + z * z);
  angles.z = Math::atan2(siny_cosp, cosy_cosp);

  return angles;
}

void 
Quaternion::setEuclidean(const Vector3f& euclidean)
{
  // Abbreviations for the various angular functions
  float cy = Math::cos(euclidean.z * 0.5f);
  float sy = Math::sin(euclidean.z * 0.5f);
  float cp = Math::cos(euclidean.y * 0.5f);
  float sp = Math::sin(euclidean.y * 0.5f);
  float cr = Math::cos(euclidean.x * 0.5f);
  float sr = Math::sin(euclidean.x * 0.5f);

  w = cr * cp * cy + sr * sp * sy;
  x = sr * cp * cy - cr * sp * sy;
  y = cr * sp * cy + sr * cp * sy;
  z = cr * cp * sy - sr * sp * cy;
}

Matrix4f 
Quaternion::getRotationMatrix()
{
  return Matrix4f::rotationMatrix(getEuclidean());
}

//void 
//Quaternion::setFromMatrix(const Matrix4f& rotMatrix)
//{
//}

Vector3f 
Quaternion::rotateVector(const Vector3f& vec)
{
  Quaternion P(0, vec.x, vec.y, vec.z);
  Quaternion R = *this * P * getConjugate();
  return Vector3f(R.x, R.y, R.z);
}

Quaternion& 
Quaternion::operator*(const Quaternion& other)
{
  Quaternion r(
    this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z,
    this->w * other.x + this->x * other.w + this->y * other.z - this->z * other.y,
    this->w * other.y - this->x * other.z + this->y * other.w + this->z * other.x,
    this->w * other.z + this->x * other.y - this->y * other.x + this->z * other.w
  );
  return *this;
}
bool Quaternion::operator==(const Quaternion& other) const
{
  return (Math::abs(this->w - other.w) < Math::kFLOAT_EQUAL_SMALL_DIFFERENCE)
      && (Math::abs(this->x - other.x) < Math::kFLOAT_EQUAL_SMALL_DIFFERENCE)
      && (Math::abs(this->y - other.y) < Math::kFLOAT_EQUAL_SMALL_DIFFERENCE)
      && (Math::abs(this->z - other.z) < Math::kFLOAT_EQUAL_SMALL_DIFFERENCE);
}
}