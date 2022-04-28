#include "eeOctreeNode.h"

#include <eeMemoryManager.h>

#include <eePlane.h>

#include "eeStaticMesh.h"
#include "eeMesh.h"

namespace eeEngineSDK {
uint64 g_maxTrianglesCount = 15000u;

void
OctreeNode::CalculateTree(const BoxAAB& space, SPtr<StaticMesh> sMesh)
{
  auto& memoryManager = MemoryManager::instance();

  m_nodeSpace = space;

  if (sMesh) {
    uint64 trianglesCount = 0u;
    
    Vector<Pair<Mesh, SPtr<Material>>> meshes = sMesh->getMeshes();
    for (const auto& m : meshes) {
      trianglesCount += static_cast<uint64>(m.first.getIndexCount() / 3);
    }
    if (trianglesCount <= g_maxTrianglesCount) {
      m_nodeMesh = sMesh;
      return;
    }
    
    // Separate in new children.
    Vector<SPtr<StaticMesh>> childrenMeshes;
    
    Vector<SPtr<StaticMesh>> tempMeshes;
    Vector<SPtr<StaticMesh>> tempMeshes2;
    Vector<SPtr<StaticMesh>> tempMeshes3;
    Vector3f APoint = space.getA();
    Vector3f midPoint = (APoint + space.getB()) * 0.5f;
    Vector3f spaceSize = space.getSize();
    // First division
    Plane tempPlane = Plane(0.0f, 0.0f, 1.0f, midPoint.z);
    tempMeshes = DivideMesh(tempPlane, sMesh);
    // Second division
    tempPlane = Plane(0.0f, 1.0f, 0.0f, midPoint.y);
    if (tempMeshes[0]) {
      tempMeshes2 = DivideMesh(tempPlane, tempMeshes[0]);
    }
    else {
      tempMeshes2.resize(2, nullptr);
    }
    if (tempMeshes[1]) {
      tempMeshes = DivideMesh(tempPlane, tempMeshes[1]);
    }
    else {
      tempMeshes.resize(2, nullptr);
    }
    // Third division
    tempPlane = Plane(1.0f, 0.0f, 0.0f, midPoint.x);
    if (tempMeshes2[0]) {
      tempMeshes3 = DivideMesh(tempPlane, tempMeshes2[0]);
      childrenMeshes.push_back(tempMeshes3[0]);
      childrenMeshes.push_back(tempMeshes3[1]);
    }
    else {
      childrenMeshes.push_back(nullptr);
      childrenMeshes.push_back(nullptr);
    }
    if (tempMeshes2[1]) {
      tempMeshes3 = DivideMesh(tempPlane, tempMeshes2[1]);
      childrenMeshes.push_back(tempMeshes3[0]);
      childrenMeshes.push_back(tempMeshes3[1]);
    }
    else {
      childrenMeshes.push_back(nullptr);
      childrenMeshes.push_back(nullptr);
    }
    if (tempMeshes[0]) {
      tempMeshes3 = DivideMesh(tempPlane, tempMeshes[0]);
      childrenMeshes.push_back(tempMeshes3[0]);
      childrenMeshes.push_back(tempMeshes3[1]);
    }
    else {
      childrenMeshes.push_back(nullptr);
      childrenMeshes.push_back(nullptr);
    }
    if (tempMeshes[1]) {
      tempMeshes3 = DivideMesh(tempPlane, tempMeshes[1]);
      childrenMeshes.push_back(tempMeshes3[0]);
      childrenMeshes.push_back(tempMeshes3[1]);
    }
    else {
      childrenMeshes.push_back(nullptr);
      childrenMeshes.push_back(nullptr);
    }
    
    SIZE_T childrenCount = childrenMeshes.size();
    for (SIZE_T i = 0; i < childrenCount; ++i) {
      m_childNodes.emplace_back(memoryManager.newPtr<OctreeNode>());
      BoxAAB newSpace =
      BoxAAB(Vector3f((i % 2) < 1 ? APoint.x : midPoint.x,
                      (i % 4) < 2 ? APoint.y : midPoint.y,
                      (i % 8) < 4 ? APoint.z : midPoint.z),
             spaceSize * 0.5f);
      m_childNodes[i]->CalculateTree(newSpace, childrenMeshes[i]);
      childrenMeshes[i].reset();
    }
  }
}
Vector<SPtr<StaticMesh>>
OctreeNode::DivideMesh(const Plane& plane, SPtr<StaticMesh> sMesh)
{
  auto& memoryManager = MemoryManager::instance();

  Vector<Pair<Mesh, SPtr<Material>>> sideAMeshes;
  Vector<Pair<Mesh, SPtr<Material>>> sideBMeshes;
  for (const auto& m : sMesh->getMeshes()) {
    Vector<Triangle> sideATriangles;
    Vector<Triangle> sideBTriangles;

    Vector<Triangle> mTriArr = m.first.getTrianglesArray();
    for (const Triangle& tr : mTriArr) {
      Vector<Vector<Triangle>> triVec = Triangle::getSplitTrianglesByPlane(tr, plane);
      for (const Triangle& trr : triVec[0]) {
        sideATriangles.emplace_back(trr);
      }
      for (const Triangle& trr : triVec[1]) {
        sideBTriangles.emplace_back(trr);
      }
    }

    if (!sideATriangles.empty()) {
      sideAMeshes.emplace_back(make_pair(Mesh(), m.second));
      sideAMeshes[sideAMeshes.size() - 1].first.loadFromTrianglesArray(sideATriangles);
    }
    if (!sideBTriangles.empty()) {
      sideBMeshes.emplace_back(make_pair(Mesh(), m.second));
      sideBMeshes[sideBMeshes.size() - 1].first.loadFromTrianglesArray(sideBTriangles);
    }
  }
  Vector<SPtr<StaticMesh>> r;
  if (!sideAMeshes.empty()) {
    r.emplace_back(memoryManager.newPtr<StaticMesh>());
    r[0]->loadFromMeshes(sideAMeshes, "", {}, {}, {});
  }
  else {
    r.emplace_back(nullptr);
  }
  if (!sideBMeshes.empty()) {
    r.emplace_back(memoryManager.newPtr<StaticMesh>());
    r[1]->loadFromMeshes(sideBMeshes, "", {}, {}, {});
  }
  else {
    r.emplace_back(nullptr);
  }
  return r;
}
void
OctreeNode::getMeshes(Vector<SPtr<StaticMesh>>& outMeshesVec)
{
  if (m_nodeMesh) {
    outMeshesVec.push_back(m_nodeMesh);
  }
  else {
    for (const auto& ch : m_childNodes) {
      ch->getMeshes(outMeshesVec);
    }
  }
}
}