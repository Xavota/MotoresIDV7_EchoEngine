#include "eeTransform.h"

namespace eeEngineSDK {
Matrix4f
Transform::getModelMatrix()
{
  return Matrix4f::translationMatrix(m_position)
       * m_rotation.getRotationMatrix()
       * Matrix4f::scaleMatrix(m_scale);
}
Vector3f
Transform::getPosition() const
{
  return m_position;
}
void
Transform::setPosition(const Vector3f& pos)
{
  m_position = pos;
}
Quaternion
Transform::getRotation() const
{
  return m_rotation;
}
void
Transform::setRotation(const Quaternion& rot)
{
  m_rotation = rot;
}
Vector3f
Transform::getScale() const
{
  return m_scale;
}
void
Transform::setScale(const Vector3f& scale)
{
  m_scale = scale;
}
}