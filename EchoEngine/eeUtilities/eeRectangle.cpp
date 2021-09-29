#include "eeRectangle.h"

namespace eeEngineSDK {
Rectangle::Rectangle()
{
}

Rectangle::Rectangle(const Vector2f& A, const Vector2f& size)
{
  EE_ASSERT(size.x >= 0.0f && size.y >= 0.0f
         && "Size can't be negative!");

  m_a = A;
  m_size = size;
}

Rectangle::Rectangle(const float Ax, 
                     const float Ay, 
                     const float width, 
                     const float height)
{
  EE_ASSERT(width >= 0.0f && height >= 0.0f
         && "Size can't be negative!");

  m_a = Vector2f(Ax, Ay);
  m_size = Vector2f(width, height);
}

Rectangle::~Rectangle()
{
}
}