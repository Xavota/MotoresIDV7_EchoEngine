#include "eeCTransform.h"
#include "eeGraficsApi.h"
#include <eeVector4.h>

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
void CTransform::update(SPtr<Actor> actor)
{
  if (m_dirtyModelMatrix)
  {
    m_dirtyModelMatrix = false;

    Matrix4f modelMat = getModelMatrix();
    m_modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMat));
  }
}
Matrix4f
CTransform::getModelMatrix()
{
  Matrix4f transform = Matrix4f::IDENTITY;
  if (m_parent)
  {
    transform = m_parent->getModelMatrix();
  }
  return transform *
         Matrix4f::translationMatrix(m_position) *
         Matrix4f::rotationMatrix(m_rotation.getEuclidean()) *
         Matrix4f::scaleMatrix(m_scale);
}
Vector3f
CTransform::getPosition()
{
  return m_position;
}
Vector3f CTransform::getGlobalPosition()
{
  Matrix4f transform = Matrix4f::IDENTITY;
  if (m_parent)
  {
    transform = m_parent->getModelMatrix();
  }
  Vector4f worldPos = transform *
                      Vector4f(m_position.x, m_position.y, m_position.z, 1.0f);
  return Vector3f(worldPos.x, worldPos.y, worldPos.z);
}
void
CTransform::setPosition(const Vector3f& pos)
{
  m_dirtyModelMatrix = true;
  for (auto& child : m_childs)
  {
    child->m_dirtyModelMatrix = true;
  }

  m_position = pos;
}
Quaternion
CTransform::getRotation()
{
  return m_rotation;
}
Quaternion CTransform::getGlobalRotation()
{
  Quaternion globalRot;
  if (m_parent)
  {
    globalRot = m_parent->getRotation();
  }
  return Quaternion(m_rotation.getEuclidean() + globalRot.getEuclidean());
}
void
CTransform::setRotation(const Quaternion& rot)
{
  m_dirtyModelMatrix = true;
  for (auto& child : m_childs)
  {
    child->m_dirtyModelMatrix = true;
  }

  m_rotation = rot;
}
Vector3f
CTransform::getScale()
{
  return m_scale;
}
Vector3f CTransform::getGlobalScale()
{
  Vector3f globalScale;
  if (m_parent)
  {
    globalScale = m_parent->getScale();
  }
  return m_scale * globalScale;
}
void
CTransform::setScale(const Vector3f& scale)
{
  m_dirtyModelMatrix = true;
  for (auto& child : m_childs)
  {
    child->m_dirtyModelMatrix = true;
  }

  m_scale = scale;
}
void CTransform::attatchTo(SPtr<CTransform> transformParent)
{
  if (m_parent)
  {
    m_parent->m_childs.erase(m_parent->m_childs.begin() + m_childIndex);
  }

  m_parent = transformParent;
  m_childIndex = m_parent->m_childs.size();
  m_parent->m_childs.push_back(
      MemoryManager::instance().reinterpretPtr<CTransform>(shared_from_this()));
}
}