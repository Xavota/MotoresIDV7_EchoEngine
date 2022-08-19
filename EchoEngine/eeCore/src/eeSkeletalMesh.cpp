#include "eeSkeletalMesh.h"

#pragma warning(push, 0)   
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)

#include <eeLogger.h>

#include <eeMemoryManager.h>

#include <eeQuaternion.h>
#include <eeMath.h>

#include "eeResourceManager.h"

#include "eeSkeletal.h"
#include "eeMesh.h"

#include "eeMaterial.h"

namespace eeEngineSDK {
SkeletalMesh::SkeletalMesh(const Vector<BoneMesh>& meshes,
                           WPtr<Skeletal> skeleton,
                           float furtherDist,
                           const Vector3f& maxCoordinate,
                           const Vector3f& minCoordinate)
{
  loadFromMeshes(meshes,
                 skeleton,
                 furtherDist,
                 maxCoordinate,
                 minCoordinate);
}
SkeletalMesh::SkeletalMesh(const Vector<Pair<BoneMesh, WPtr<Material>>>& meshes,
                           WPtr<Skeletal> skeleton,
                           float furtherDist,
                           const Vector3f& maxCoordinate,
                           const Vector3f& minCoordinate)
{
  loadFromMeshes(meshes,
                 skeleton,
                 furtherDist,
                 maxCoordinate,
                 minCoordinate);
}
bool
SkeletalMesh::loadFromMeshes(const Vector<BoneMesh>& meshes,
                             WPtr<Skeletal> skeleton,
                             float furtherDist,
                             const Vector3f& maxCoordinate,
                             const Vector3f& minCoordinate)
{
  if (meshes.empty()) {
    Logger::instance().consoleLog("Empty info loading model");
    return false;
  }

  auto& resourseManager = ResourceManager::instance();

  for (const auto& m : meshes) {
    m_meshes.emplace_back
    (
      Pair<BoneMesh/*<V, I>*/, WPtr<Material>>
      (
        m,
        resourseManager.getResourceMaterial("Default_mat")
      )
    );
  }

  m_skeleton = skeleton;

  m_boundSphere.setCenter(Vector3f(0.0f, 0.0f, 0.0f));
  m_boundSphere.setRadious(furtherDist);

  m_boundCube.setA(minCoordinate);
  m_boundCube.setSize(maxCoordinate - minCoordinate);
  return true;
}
bool
SkeletalMesh::loadFromMeshes(const Vector<Pair<BoneMesh, WPtr<Material>>>& meshes,
                             WPtr<Skeletal> skeleton,
                             float furtherDist,
                             const Vector3f& maxCoordinate,
                             const Vector3f& minCoordinate)
{
  if (meshes.empty()) {
    Logger::instance().consoleLog("Empty info loading model");
    return false;
  }

  m_meshes = meshes;

  m_skeleton = skeleton;

  m_boundSphere.setCenter(Vector3f(0.0f, 0.0f, 0.0f));
  m_boundSphere.setRadious(furtherDist);

  m_boundCube.setA(minCoordinate);
  m_boundCube.setSize(maxCoordinate - minCoordinate);
  return true;
}
Vector<Pair<BoneMesh, WPtr<Material>>>
SkeletalMesh::getMeshes()
{
  return m_meshes;
}
Vector<WPtr<Material>>
SkeletalMesh::getTextures()
{
  Vector<WPtr<Material>> textures;
  for (auto& m : m_meshes) {
    textures.push_back(m.second);
  }
  return textures;
}
void
SkeletalMesh::setTexture(WPtr<Material> texture, uint32 index)
{
  if (static_cast<uint32>(m_meshes.size()) > index) {
    m_meshes[index].second = texture;
  }
}
const Sphere&
SkeletalMesh::getBoundingSphere()
{
  return m_boundSphere;
}

const Vector3f&
SkeletalMesh::getFurtherPosition()
{
  return m_furtherPosition;
}
const BoxAAB&
SkeletalMesh::getBoundingBox()
{
  return m_boundCube;
}
}