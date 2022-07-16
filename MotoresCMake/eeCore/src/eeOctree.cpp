#include "eeOctree.h"

#include <eeMemoryManager.h>

#include "eeScene.h"
#include "eeActor.h"
#include "eeCStaticMesh.h"
#include "eeCTransform.h"
#include "eeStaticMesh.h"
#include "eeMesh.h"

#include "eeOctreeNode.h"

namespace eeEngineSDK {
void
Octree::calculateTree(const BoxAAB& space, const Vector<SPtr<Scene>>& scenes)
{
  Vector<SPtr<CStaticMesh>> staticMeshes;
  for (const auto& s : scenes) {
    Vector<SPtr<Actor>> sceneActors;
    s->getAllActorsVector(sceneActors);
    for (const auto& sa : sceneActors) {
      SPtr<CStaticMesh> statMesh = sa->getComponent<CStaticMesh>();
      if (statMesh && statMesh->getMobilityType() == eMOBILITY_TYPE::kStatic) {
        staticMeshes.emplace_back(statMesh);
      }
    }
  }

  Vector<Pair<Mesh, SPtr<Material>>> meshMap;

  for (const auto& sm : staticMeshes) {
    Vector<Pair<Mesh, SPtr<Material>>> tempMeshMap;
    sm->getStaticMesh()->getMeshes(tempMeshMap);
    Matrix4f transMat = sm->getActor()->getTransform()->getModelMatrix();
    for (auto& m : tempMeshMap) {
      Mesh newMesh;
      Mesh::copyMeshTransformed(m.first, transMat, newMesh);
      m.first = newMesh;
      meshMap.emplace_back(m);
    }
  }

  auto& memoryManager = MemoryManager::instance();
  if (!meshMap.empty()) {
    SPtr<StaticMesh> holeMesh = memoryManager.newPtr<StaticMesh>();
    holeMesh->loadFromMeshes(meshMap, "", {}, {}, {});
    m_root = memoryManager.newPtr<OctreeNode>();
    m_root->CalculateTree(space, holeMesh);
  }
}
void
Octree::getMeshes(Vector<SPtr<StaticMesh>>& outMeshesVec)
{
  if (m_root) {
    m_root->getMeshes(outMeshesVec);
  }
}
}