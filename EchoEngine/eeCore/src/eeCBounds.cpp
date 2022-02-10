#include "eeCBounds.h"
#include "eeActor.h"
#include "eeCModel.h"
#include "eeCSkeletalMesh.h"

namespace eeEngineSDK {
void
CBounds::update()
{
  SPtr<CModel> actorModel = m_actor->getComponent<CModel>();
  if (actorModel)
  {
    m_sphereBound = actorModel->getBoundingSphere();
    m_boxBound = actorModel->getBoundingBox();
    return;
  }

  SPtr<CSkeletalMesh> actorSkeletalMesh = m_actor->getComponent<CSkeletalMesh>();
  if (actorSkeletalMesh)
  {
    m_sphereBound = actorSkeletalMesh->getBoundingSphere();
    m_boxBound = actorSkeletalMesh->getBoundingBox();
    return;
  }
}
Sphere
CBounds::getSphereBound()
{
  return m_sphereBound;
}
BoxAAB
CBounds::getBoxBound()
{
  return m_boxBound;
}
}