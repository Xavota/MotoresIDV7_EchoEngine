#include "eeCSkeletalMesh.h"

namespace eeEngineSDK{
void
CSkeletalMesh::update(SPtr<Actor> actor)
{
}
SPtr<SkeletalMesh>
CSkeletalMesh::getSkeletal()
{
  return m_skMesh;
}
void
CSkeletalMesh::setSkeletal(SPtr<SkeletalMesh> skeletal)
{
  m_skMesh = skeletal;
}
}