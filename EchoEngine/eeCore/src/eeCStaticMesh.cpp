#include "eeCStaticMesh.h"
#include "eeStaticMesh.h"
#include "eeActor.h"
#include "eeCTransform.h"

namespace eeEngineSDK {
void
CStaticMesh::update()
{
  EE_NO_EXIST_RETURN(m_actor);
}
void
CStaticMesh::setStaticMesh(SPtr<StaticMesh> staticMesh)
{
  m_staticMesh = staticMesh;
}
SPtr<StaticMesh>
CStaticMesh::getStaticMesh()
{
  return m_staticMesh;
}
}