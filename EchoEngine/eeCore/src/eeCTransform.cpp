#include "eeCTransform.h"
#include "eeGraficsApi.h"

namespace eeEngineSDK {
CTransform::CTransform() :
m_position(0.0f, 0.0f, 0.0f),
m_rotation(Vector3f( 0.0f,0.0f,0.0f )),
m_scale(1.0f, 1.0f, 1.0f)
{
  m_modelMatrixBuff = GraphicsApi::instance().createConstantBufferPtr();
  Matrix4f modelMat = getModelMatrix();
  m_modelMatrixBuff->initData(sizeof(Matrix4f),
                              sizeof(Matrix4f),
                              reinterpret_cast<Byte*>(&modelMat));
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
  Matrix4f modelMat = getModelMatrix();
  m_modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMat));
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
  Matrix4f modelMat = getModelMatrix();
  m_modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMat));
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
  Matrix4f modelMat = getModelMatrix();
  m_modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMat));
}
}