#include "eePlane.h"

namespace eeEngineSDK {
Plane::Plane() : m_point(0.0f, 0.0f, 0.0f), m_normal(0.0f, 0.0f, 1.0f)
{}
Plane::Plane(const Vector3f& point, const Vector3f& normal)
{
  m_point = point;
  m_normal = normal;
}
Plane::Plane(const Vector3f& pA, const Vector3f& pB, const Vector3f& pC)
{
  m_point = pA;

  Vector3f AB = pB - pA;
  Vector3f AC = pC - pA;

  m_normal = AB.cross(AC);
}
Plane::~Plane()
{
}
void Plane::move(const Vector3f& movement)
{
  m_point += movement;
}
void Plane::rotate(const Vector3f& rotation)
{
  //TODO: Multiplications of Matrix*Vector
}
}