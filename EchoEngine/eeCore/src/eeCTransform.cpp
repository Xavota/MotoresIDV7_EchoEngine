#include "eeCTransform.h"
#include "eeGraficsApi.h"
#include <eeVector4.h>

namespace eeEngineSDK {
CTransform::CTransform()
 : //m_position(0.0f, 0.0f, 0.0f),
   //m_rotation(Vector3f( 0.0f,0.0f,0.0f )),
   //m_scale(1.0f, 1.0f, 1.0f),
   m_transform(Vector3f(0.0f, 0.0f, 0.0f),
               Quaternion(Vector3f(0.0f, 0.0f, 0.0f)),
               Vector3f(1.0f, 1.0f, 1.0f))
{}
void
CTransform::update()
{
  //if (m_actor.expired()) return;

  //if (m_dirtyModelMatrix) {
  //  m_dirtyModelMatrix = false;
  //}
}
Matrix4f
CTransform::getModelMatrix()
{
  Matrix4f transform = Matrix4f::kIDENTITY;
  if (!m_parent.expired()) {
    transform = m_parent.lock()->getModelMatrix();
  }
  //return transform
  //     * Matrix4f::translationMatrix(m_position)
  //     * m_rotation.getRotationMatrix()
  //     * Matrix4f::scaleMatrix(m_scale);
  return transform * m_transform.getModelMatrix();
}
Vector3f
CTransform::getPosition()
{
  //return m_position;
  return m_transform.getPosition();
}
Vector3f
CTransform::getGlobalPosition()
{
  Matrix4f transform = Matrix4f::kIDENTITY;
  if (!m_parent.expired()) {
    transform = m_parent.lock()->getModelMatrix();
  }
  //Vector4f worldPos = transform
  //                  * Vector4f(m_position.x, m_position.y, m_position.z, 1.0f);
  Vector3f localPos = m_transform.getPosition();
  Vector4f worldPos = transform
                    * Vector4f(localPos.x, localPos.y, localPos.z, 1.0f);
  Vector3f r(worldPos.x, worldPos.y, worldPos.z);
  return r;
}
void
CTransform::setPosition(const Vector3f& pos)
{
  //m_dirtyModelMatrix = true;
  //for (auto& child : m_children) {
  //  if (child) {
  //    child->m_dirtyModelMatrix = true;
  //  }
  //}

  //m_position = pos;
  m_transform.setPosition(pos);
}
Quaternion
CTransform::getRotation()
{
  //return m_rotation;
  return m_transform.getRotation();
}
Quaternion
CTransform::getGlobalRotation()
{
  Quaternion globalRot;
  if (!m_parent.expired()) {
    globalRot = m_parent.lock()->getRotation();
  }
  Quaternion localRot = m_transform.getRotation();
  return Quaternion(localRot.getEuclidean() + globalRot.getEuclidean());
}
void
CTransform::setRotation(const Quaternion& rot)
{
  //m_dirtyModelMatrix = true;
  //for (auto& child : m_children) {
  //  child->m_dirtyModelMatrix = true;
  //}

  //m_rotation = rot;
  m_transform.setRotation(rot);
}
Vector3f
CTransform::getScale()
{
  //return m_scale;
  return m_transform.getScale();
}
Vector3f
CTransform::getGlobalScale()
{
  Vector3f globalScale;
  if (!m_parent.expired()) {
    globalScale = m_parent.lock()->getScale();
  }
  Vector3f localScale = m_transform.getScale();
  return localScale * globalScale;
}
void
CTransform::setScale(const Vector3f& scale)
{
  //m_dirtyModelMatrix = true;
  //for (auto& child : m_children) {
  //  child->m_dirtyModelMatrix = true;
  //}

  //m_scale = scale;
  m_transform.setScale(scale);
}
void
CTransform::attachTo(WPtr<CTransform> transformParent)
{
  //if (!m_parent.expired()) {
  //  auto sParent = m_parent.lock();
  //  sParent->m_children.erase(sParent->m_children.begin()
  //                          + m_childIndex);
  //}

  m_parent = transformParent;
  //if (m_parent.expired()) return;

  //auto sParent = m_parent.lock();
  //m_childIndex = static_cast<int32>(sParent->m_children.size());
  //sParent->m_children.push_back(
  //  MemoryManager::instance().reinterpretPtr<CTransform>(shared_from_this()));
}
}