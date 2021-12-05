#include "eeBox.h"
#include "eeMath.h"

namespace eeEngineSDK {
const BoxAAB BoxAAB::SIMPLEX(Vector3f(-1.0f, 1.0f, 1.0f),
                             Vector3f( 2.0f,  2.0f,  2.0f));




BoxAAB::BoxAAB() : m_a(-1.0f, 1.0f, 1.0f), m_size(2.0f, 2.0f, 2.0f)
{}

BoxAAB::BoxAAB(const Vector3f A, const Vector3f size) : m_a(A), m_size(size)
{
#if EE_DEBUG_MODE
  //EE_ASSERT(size.x >= 0.0f && size.y >= 0.0f && size.z >= 0.0f
  //       && "Size can't be negative!");
  if (size.x < 0.0f || size.y < 0.0f || size.z < 0.0f)
  {
    eeOStream::print("Size can't be negative!"); eeOStream::endl();
  }
#endif
}
bool BoxAAB::intersects(const Vector3f& point) const
{
  return Math::intersectionBoxPoint(*this, point);
}
bool BoxAAB::intersects(const Plane& plane) const
{
  return Math::intersectionBoxPlane(*this, plane);
}
bool BoxAAB::intersects(const Sphere& sphere)
{
  return Math::intersectionBoxSphere(*this, sphere);
}
bool BoxAAB::intersects(const BoxAAB& box)
{
  return Math::intersectionBoxBox(*this, box);
}
//bool BoxAAB::intersects(const Capsule& capsule)
//{
//  return Math::intersectionCapsuleBox(capsule, *this);
//}
}