#include "eeCSkeletalMesh.h"
#include "eeSkeletalMesh.h"
#include "eeActor.h"
#include "eeCTransform.h"

namespace eeEngineSDK{
void
CSkeletalMesh::update()
{
  if (!m_actor.expired()) return;
}
WPtr<SkeletalMesh>
CSkeletalMesh::getModel()
{
  return m_skMesh;
}
void
CSkeletalMesh::setModel(WPtr<SkeletalMesh> skeletal)
{
  m_skMesh = skeletal;
}
}