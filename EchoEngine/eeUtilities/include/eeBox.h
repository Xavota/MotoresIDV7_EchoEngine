/************************************************************************/
/**
 * @file eeBox.h
 * @author Diego Castellanos
 * @date 25/09/21
 * @brief This file defines all types of boxes, not oriented, oriented,
          as well as all its functions.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesUtilities.h"
#include "eeVector3.h"

namespace eeEngineSDK {
  /**
  * @brief
  * The simplest box. Not oriented. Defined by 2 points.
  */
class EE_UTILITY_EXPORT BoxAAB
{
 public:
  BoxAAB() = default;
  BoxAAB(const Vector3f A, const Vector3f size);
  ~BoxAAB() = default;

  FORCEINLINE void 
  move(const Vector3f& movement)
  {
    m_a += movement;
  }

  FORCEINLINE void
  setA(const Vector3f& A)
  {
    m_a = A;
  }
  FORCEINLINE Vector3f
  getA() const
  {
    return m_a;
  }
  FORCEINLINE void
  setSize(const Vector3f& size)
  {
    EE_ASSERT(size.x >= 0.0f && size.y >= 0.0f && size.z >= 0.0f
           && "Size can't be negative!");

    m_size = size;
  }
  FORCEINLINE Vector3f
  getSize() const
  {
    return m_size;
  }
  FORCEINLINE Vector3f
  getB() const
  {
    return m_a + Vector3f(m_size.x, -m_size.y, -m_size.z);
  }

  

  static const BoxAAB SIMPLEX;

 private:
  Vector3f m_a;
  Vector3f m_size;
};
}
