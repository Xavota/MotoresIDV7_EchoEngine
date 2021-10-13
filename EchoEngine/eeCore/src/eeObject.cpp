#include "eeObject.h"

namespace eeEngineSDK {
Vector3f 
Object::getPosition()
{
  return m_position;
}
void 
Object::setPosition(const Vector3f& pos)
{
  m_position = pos;
}
Quaternion 
Object::getRotation()
{
  return m_rotation;
}
void 
Object::setRotation(const Quaternion& rot)
{
  m_rotation = rot;
}
Vector3f 
Object::getScale()
{
  return m_scale;
}
void 
Object::setScale(const Vector3f& scale)
{
  m_scale = scale;
}
void 
Object::setModel(SPtr<Model>& model)
{
  m_model = model;
}
}