#include "eeObject.h"
#include "eeGraficsApi.h"
#include "eeConstantBuffer.h"
#include "eeMatrix4.h"

namespace eeEngineSDK {
bool 
Object::loadFromFile(const String& fileName,
                     Vector3f pos,
                     Quaternion rot,
                     Vector3f scale)
{
  // Load from resource manager

  m_model = std::make_shared<Model>();
  if (!m_model->loadFromFile(fileName))
  {
    return false; 
  }

  m_position = pos;
  m_rotation = rot;
  m_scale = scale;

  m_modelMatrixBuff = GraphicsApi::instance().createConstantBufferPtr();
  Matrix4f modelMat = getModelMatrix();
  m_modelMatrixBuff->initData(sizeof(Matrix4f), 
                              sizeof(Matrix4f),
                              reinterpret_cast<Byte*>(&modelMat));

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

  m_modelMatrixBuff = GraphicsApi::instance().createConstantBufferPtr();
  Matrix4f modelMat = getModelMatrix();
  m_modelMatrixBuff->initData(sizeof(Matrix4f),
    sizeof(Matrix4f),
    reinterpret_cast<Byte*>(&modelMat));

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
  Matrix4f modelMat = getModelMatrix();
  m_modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMat));
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
  Matrix4f modelMat = getModelMatrix();
  m_modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMat));
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
  Matrix4f modelMat = getModelMatrix();
  m_modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMat));
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
Matrix4f Object::getModelMatrix()
{
  return Matrix4f::translationMatrix(m_position) *
         Matrix4f::rotationMatrix(m_rotation.getEuclidean()) *
         Matrix4f::scaleMatrix(m_scale);
}
}