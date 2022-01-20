#include "eeQuaternion.h"
#include "eeVector3.h"
#include "eeMatrix4.h"
#include "eeMath.h"

namespace eeEngineSDK{
Quaternion::Quaternion(float _w, float _x, float _y, float _z)
 : w(_w), 
   x(_x),
   y(_y),
   z(_z)
{
}
Quaternion::Quaternion(const Vector3f& euclidean)
{
  setEuclidean(euclidean);
}

Quaternion
Quaternion::getConjugate()
{
  Quaternion r(w, -x, -y, -z);
  return r;
}

Quaternion&
Quaternion::conjugate()
{
  x = -x;
  y = -y;
  z = -z;

  return *this;
}
Quaternion
Quaternion::getNormalize() const
{
  float rad = Math::sqrt(x * x + y * y + z * z + w * w);
  Quaternion r(w / rad, x / rad, y / rad, z / rad);
  return r;
}
Quaternion&
Quaternion::normalize()
{
  float rad = Math::sqrt(x * x + y * y + z * z + w * w);
  x /= rad;
  y /= rad;
  z /= rad;
  w /= rad;
  return *this;
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
  if (Math::abs(sinp) >= 1) {
    angles.y = Math::copysign(Math::kPI / 2, sinp); // use 90 degrees if out of range
  }
  else {
    angles.y = Math::asin(sinp);
  }

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
  //Quaternion q(vec);
  //return (*this * q).getEuclidean();
  float num = x * 2.0f;
  float num2 = y * 2.0f;
  float num3 = z * 2.0f;
  float num4 = x * num;
  float num5 = y * num2;
  float num6 = z * num3;
  float num7 = x * num2;
  float num8 = x * num3;
  float num9 = y * num3;
  float num10 = w * num;
  float num11 = w * num2;
  float num12 = w * num3;
  Vector3f result;
  result.x = (1.0f - (num5 + num6)) * vec.x + (num7 - num12) * vec.y + (num8 + num11) * vec.z;
  result.y = (num7 + num12) * vec.x + (1.0f - (num4 + num6)) * vec.y + (num9 - num10) * vec.z;
  result.z = (num8 - num11) * vec.x + (num9 + num10) * vec.y + (1.0f - (num4 + num5)) * vec.z;
  return result.getNormalize();
}
Quaternion
Quaternion::createFromAxisAngle(const Vector3f& axis,
                                const float& angle)
{
  float factor = sinf(angle * 0.5f);

  Quaternion quat;
  quat.x = axis.x * factor;
  quat.y = axis.y * factor;
  quat.z = axis.z * factor;

  quat.w = cosf(angle * 0.5f);
  return quat.getNormalize();
}
Vector3f Quaternion::getFrontVector()
{
  return rotateVector(Vector3f::kFORWARD);
}

Vector3f Quaternion::getRightVector()
{
  return rotateVector(Vector3f::kRIGHT);
}

Vector3f Quaternion::getUpVector()
{
  return rotateVector(Vector3f::kUP);
}

String Quaternion::toString() const
{
  return "{ " + eeToString(x) + "i, "
              + eeToString(y) + "j, "
              + eeToString(z) + "k, "
              + eeToString(w) + " }";
}

float Quaternion::dot(const Quaternion& other) const
{
  return this->w * other.w
       + this->x * other.x
       + this->y * other.y
       + this->z * other.z;
}

Quaternion
Quaternion::operator*(const Quaternion& other)
{
  Quaternion r(
  this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z,
  this->w * other.x + this->x * other.w + this->y * other.z - this->z * other.y,
  this->w * other.y - this->x * other.z + this->y * other.w + this->z * other.x,
  this->w * other.z + this->x * other.y - this->y * other.x + this->z * other.w
  );
  return r;
}
Quaternion
Quaternion::operator*(const float other)
{
  Quaternion r(w * other, x * other, y * other, z * other);
  return r;
}
Quaternion
Quaternion::operator+(const Quaternion& other)
{
  Quaternion r(this->x + other.x,
               this->y + other.y,
               this->z + other.z,
               this->w + other.w);
  return r;
}
bool
Quaternion::operator==(const Quaternion& other) const
{
  return Math::checkFloatsEqual(this->w, other.w)
      && Math::checkFloatsEqual(this->x, other.x)
      && Math::checkFloatsEqual(this->y, other.y)
      && Math::checkFloatsEqual(this->z, other.z);
}
Quaternion Quaternion::interpolate(const Quaternion& a, const Quaternion& b, float t)
{
  //Quaternion a1 = a.getNormalize();
  //Quaternion b1 = b.getNormalize();
  //float theta = Math::acos(a1.dot(b1));
  //
  //float f1 = (Math::sin(1 - t) * theta) / sin(theta);
  //float f2 = (Math::sin(t * theta)) / sin(theta);
  //
  //return a1 * f1 + b1 * f2;


    // calc cosine theta
  float cosom = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;

  // adjust signs (if necessary)
  Quaternion end = b;
  if (cosom < 0.0)
  {
    cosom = -cosom;
    end.x = -end.x;   // Reverse all signs
    end.y = -end.y;
    end.z = -end.z;
    end.w = -end.w;
  }

  // Calculate coefficients
  float sclp, sclq;
  if ((1.0 - cosom) > 0.0001) // 0.0001 -> some epsillon
  {
    // Standard case (slerp)
    float omega, sinom;
    omega = std::acos(cosom); // extract theta from dot product's cos theta
    sinom = std::sin(omega);
    sclp = std::sin((1.0 - t) * omega) / sinom;
    sclq = std::sin(t * omega) / sinom;
  }
  else
  {
    // Very close, do linear interp (because it's faster)
    sclp = 1.0 - t;
    sclq = t;
  }

  Quaternion out;
  out.x = sclp * a.x + sclq * end.x;
  out.y = sclp * a.y + sclq * end.y;
  out.z = sclp * a.z + sclq * end.z;
  out.w = sclp * a.w + sclq * end.w;

  return out;
}
}