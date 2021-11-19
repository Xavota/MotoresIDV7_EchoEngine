#include "eeCTransform.h"
#include "..\include\eeCTransform.h"

namespace eeEngineSDK {
CTransform::CTransform() :
m_position(0.0f, 0.0f, 0.0f),
m_rotation(Vector3f( 0.0f,0.0f,0.0f )),
m_scale(1.0f, 1.0f, 1.0f)
{
  m_type = eCOMPONENT_TYPE::TRANSFORM;
}
Matrix4f
CTransform::getModelMatrix()
{
  return Matrix4f::translationMatrix(m_position) *
         Matrix4f::rotationMatrix(m_rotation.getEuclidean()) *
         Matrix4f::scaleMatrix(m_scale);
}
Vector3f
CTransform::getPosition()
{
  return m_position;
}
void
CTransform::setPosition(const Vector3f& pos)
{
  m_position = pos;
}
Quaternion
CTransform::getRotation()
{
  return m_rotation;
}
void
CTransform::setRotation(const Quaternion& rot)
{
  m_rotation = rot;
}
Vector3f
CTransform::getScale()
{
  return m_scale;
}
void
CTransform::setScale(const Vector3f& scale)
{
  m_scale = scale;
}
}