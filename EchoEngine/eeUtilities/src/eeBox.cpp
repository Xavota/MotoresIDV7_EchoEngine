#include "eeBox.h"

namespace eeEngineSDK {
const BoxAAB BoxAAB::SIMPLEX = BoxAAB(Vector3f(-1.0f, 1.0f, 1.0f),
                                      Vector3f( 2.0f,  2.0f,  2.0f));




BoxAAB::BoxAAB(const Vector3f A, const Vector3f size)
{
  EE_ASSERT(size.x >= 0.0f && size.y >= 0.0f && size.z >= 0.0f
         && "Size can't be negative!");

  m_a = A;
  m_size = size;
}
}