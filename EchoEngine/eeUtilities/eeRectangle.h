#pragma once
#include "eePrerequisitesUtilities.h"
#include "eeVector2.h"

namespace eeEngineSDK {
class Rectangle
{
 public:
  Rectangle();
  Rectangle(const Vector2f& A, const Vector2f& size);
  Rectangle(const float Ax, const float Ay, 
            const float width, const float height);
  ~Rectangle();

  void 
  move(const Vector2f& _movement)
  {
    m_a += _movement;
  }

  void
  setA(const Vector2f& A)
  {
    m_a = A;
  }
  Vector2f
  getA() const
  {
    return m_a;
  }
  Vector2f
  getB() const
  {
    return m_a + Vector2f(m_size.x, -m_size.y);
  }
  void
  setSize(const Vector2f& size)
  {
    EE_ASSERT(size.x >= 0.0f && size.y >= 0.0f
           && "Size can't be negative!");
    m_size = size;
  }
  void
  setSize(const float width, const float height)
  {
    EE_ASSERT(width >= 0.0f && height >= 0.0f
      && "Size can't be negative!");

    m_size = Vector2f(width, height);
  }
  Vector2f
  getSize() const
  {
    return m_size;
  }

 private:
  Vector2f m_a;
  Vector2f m_size;
};
}
