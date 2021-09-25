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
  BoxAAB();
  BoxAAB(const Vector3f A, const Vector3f B);
  ~BoxAAB();

  FORCEINLINE void 
  move(const Vector3f& movement)
  {
    m_A += movement;
    m_B += movement;
  }

  FORCEINLINE void
  setA(const Vector3f& A)
  {
    m_A = A;
  }
  FORCEINLINE Vector3f
  getA() const
  {
    return m_A;
  }
  FORCEINLINE void
  setB(const Vector3f& B)
  {
    m_B = B;
  }
  FORCEINLINE Vector3f
  getB() const
  {
    return m_B;
  }

  

  static const BoxAAB SIMPLEX;

 private:
  Vector3f m_A;
  Vector3f m_B;
};
}
