#include "eeRectangle.h"
#include "eeMath.h"

namespace eeEngineSDK {
const Rectangle Rectangle::SIMPLEX(Vector2f(-1.0f, 1.0f), 
                                   Vector2f(2.0f, 2.0f));


Rectangle::Rectangle() : m_a(-1.0f, 1.0f), m_size(2.0f, 2.0f)
{
}

Rectangle::Rectangle(const Vector2f& A, const Vector2f& size) : 
   m_a(A), 
   m_size(size)
{
#if EE_DEBUG_MODE
  //EE_ASSERT(size.x >= 0.0f && size.y >= 0.0f && size.z >= 0.0f
  //       && "Size can't be negative!");
  if (size.x < 0.0f || size.y < 0.0f)
  {
    //Cout << "Size can't be negative!\n";
    std::cout << "Size can't be negative!\n";
  }
#endif
}

Rectangle::Rectangle(const float Ax, 
                     const float Ay, 
                     const float width, 
                     const float height) :
                     m_a(Ax, Ay),
                     m_size(width, height)
{
#if EE_DEBUG_MODE
  //EE_ASSERT(size.x >= 0.0f && size.y >= 0.0f && size.z >= 0.0f
  //       && "Size can't be negative!");
  if (width < 0.0f || height < 0.0f)
  {
    //Cout << "Size can't be negative!\n";
    std::cout << "Size can't be negative!\n";
  }
#endif
}

Rectangle::~Rectangle()
{
}
bool Rectangle::intersects(const Vector2f& point) const
{
  return Math::intersectionRectanglePoint2D(*this, point);
}
bool Rectangle::intersects(const Rectangle& rectangle) const
{
  return Math::intersectionRectangleRectangle(*this, rectangle);
}
}