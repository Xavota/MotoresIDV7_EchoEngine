#include "eeCSkeletalMesh.h"
#include "eeSkeletalMesh.h"
#include "eeActor.h"
#include "eeCTransform.h"

namespace eeEngineSDK{
void
CSkeletalMesh::update()
{
  EE_NO_EXIST_RETURN(m_actor);

  SPtr<CTransform> trans = m_actor->getTransform();

  m_boundSphere.setCenter(trans->getGlobalPosition());

  Vector3f scale = trans->getGlobalScale();
  float radScale = scale.x > scale.y ? scale.x : scale.y;
  radScale = radScale > scale.z ? radScale : scale.z;

  m_boundSphere.setRadious(m_originRadious * radScale);
}
SPtr<SkeletalMesh>
CSkeletalMesh::getModel()
{
  return m_skMesh;
}
void
CSkeletalMesh::setModel(SPtr<SkeletalMesh> skeletal)
{
  m_skMesh = skeletal;
  EE_NO_EXIST_RETURN(skeletal);

  m_boundSphere = skeletal->getBoundingSphere();

  m_originRadious = m_boundSphere.getRadious();
}
const Sphere&
CSkeletalMesh::getBoundingSphere()
{
  return m_boundSphere;
}
const BoxAAB&
CSkeletalMesh::getBoundingBox()
{
  return m_boundBox;
}
}