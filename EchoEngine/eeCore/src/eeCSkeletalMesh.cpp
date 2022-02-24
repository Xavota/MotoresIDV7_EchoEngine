#include "eeCSkeletalMesh.h"
#include "eeSkeletalMesh.h"
#include "eeActor.h"
#include "eeCTransform.h"

namespace eeEngineSDK{
void
CSkeletalMesh::update()
{
  EE_NO_EXIST_RETURN(m_actor);
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
}
}