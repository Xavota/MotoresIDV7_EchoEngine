#pragma once
#include "eePrerequisitesUtilities.h"
#include "eeVector3.h"

namespace eeEngineSDK {
class Capsule
{
 public:
  Capsule();
  Capsule(const Vector3f& center, const float height, const float radious);
  ~Capsule();

  void
  move(const Vector3f& movement)
  {
    m_center += movement;
  }

  Vector3f
  getCenter() const
  {
    return m_center;
  }
  void
  setCenter(const Vector3f& center)
  {
    m_center = center;
  }
  float
  getHeight() const
  {
    return m_height;
  }
  void
  setHeight(const float height)
  {
    m_height = height;
  }
  float
  getRadious() const
  {
    return m_radious;
  }
  void
  setRadious(const float radious)
  {
    m_radious = radious;
  }
  

 private:
  Vector3f m_center;
  float m_height;
  float m_radious;
};
}
