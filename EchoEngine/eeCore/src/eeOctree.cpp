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
Octree::calculateTree(const BoxAAB& space, const Vector<WPtr<Scene>>& scenes)
{
  Vector<WPtr<CStaticMesh>> staticMeshes;
  for (const auto& s : scenes) {
    Vector<SPtr<Actor>> sceneActors;
    s.lock()->getAllActorsVector(sceneActors);
    for (const auto& sa : sceneActors) {
      WPtr<CStaticMesh> statMesh = sa->getComponent<CStaticMesh>();
      if (!statMesh.expired()
       && statMesh.lock()->getMobilityType() == eMOBILITY_TYPE::kStatic) {
        staticMeshes.emplace_back(statMesh);
      }
    }
  }

  Vector<Pair<Mesh, WPtr<Material>>> meshMap;

  for (const auto& sm : staticMeshes) {
    auto ssm = sm.lock();
    Vector<Pair<Mesh, WPtr<Material>>> tempMeshMap;
    ssm->getStaticMesh().lock()->getMeshes(tempMeshMap);
    Matrix4f transMat =
    ssm->getActor().lock()->getTransform().lock()->getModelMatrix();
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
Octree::getMeshes(Vector<WPtr<StaticMesh>>& outMeshesVec)
{
  if (m_root) {
    m_root->getMeshes(outMeshesVec);
  }
}
}