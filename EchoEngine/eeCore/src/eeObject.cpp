#include "eeObject.h"

namespace eeEngineSDK {
bool 
Object::loadFromFile(const String& /*fileName*/)
{
  // Load from resource manager

  /*if (!m_model->loadFromFile(fileName))
  {
    
  }*/

  return true;
}
bool 
Object::loadFromModel(SPtr<Model> model,
                      Vector3f pos,
                      Quaternion rot,
                      Vector3f scale)
{
  if (!model)
  {
    std::cout << "There is no model here..." << std::endl;
    return false;
  }

  m_model = model;

  m_position = pos;
  m_rotation = rot;
  m_scale = scale;

  return true;
}
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
Object::setModel(const SPtr<Model>& model)
{
  m_model = model;
}
SPtr<Model> Object::getModel()
{
  return m_model;
}
}