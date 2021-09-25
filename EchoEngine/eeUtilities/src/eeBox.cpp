#include "eeBox.h"

namespace eeEngineSDK {
const BoxAAB BoxAAB::SIMPLEX = BoxAAB(Vector3f(-1.0f, -1.0f, -1.0f),
                                      Vector3f( 1.0f,  1.0f,  1.0f));




BoxAAB::BoxAAB()
{
}
BoxAAB::BoxAAB(const Vector3f A, const Vector3f B) : m_A(A), m_B(B)
{
}
BoxAAB::~BoxAAB()
{
}
}