#include "eeCStaticMesh.h"
#include "eeStaticMesh.h"
#include "eeActor.h"
#include "eeCTransform.h"

namespace eeEngineSDK {
void
CStaticMesh::update()
{
  if (m_actor.expired()) return;
}
void
CStaticMesh::setStaticMesh(WPtr<StaticMesh> staticMesh)
{
  m_staticMesh = staticMesh;
}
WPtr<StaticMesh>
CStaticMesh::getStaticMesh()
{
  return m_staticMesh;
}
}