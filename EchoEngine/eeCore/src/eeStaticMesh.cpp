#include "eeStaticMesh.h"

#pragma warning(push, 0)   
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)

#include <eeMemoryManager.h>
#include <eeLogger.h>

#include <eeQuaternion.h>
#include <eeMath.h>

#include <eeVertex.h>

#include "eeResourceManager.h"
#include "eeSkeletalMesh.h"
#include "eeSkeletal.h"
#include "eeMaterial.h"

namespace eeEngineSDK {
StaticMesh::StaticMesh(const Vector<Mesh>&meshes,
                       float furtherDist,
                       const Vector3f& maxCoordinate,
                       const Vector3f& minCoordinate)
{
  loadFromMeshes(meshes,
                 furtherDist,
                 maxCoordinate,
                 minCoordinate);
}
StaticMesh::StaticMesh(const Vector<Pair<Mesh, WPtr<Material>>>& meshes,
                       float furtherDist,
                       const Vector3f& maxCoordinate,
                       const Vector3f& minCoordinate)
{
  loadFromMeshes(meshes,
                 furtherDist,
                 maxCoordinate,
                 minCoordinate);
}
bool
StaticMesh::loadFromMeshes(const Vector<Mesh>& meshes,
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
      Pair<Mesh, WPtr<Material>>
      (
        m,
        resourseManager.getResourceMaterial("Default_mat")
      )
    );
  }

  m_boundSphere.setCenter(Vector3f(0.0f, 0.0f, 0.0f));
  m_boundSphere.setRadious(furtherDist);

  m_boundCube.setA(minCoordinate);
  m_boundCube.setSize(maxCoordinate - minCoordinate);
  return true;
}
bool
StaticMesh::loadFromMeshes(const Vector<Pair<Mesh, WPtr<Material>>>& meshes,
                           float furtherDist,
                           const Vector3f& maxCoordinate,
                           const Vector3f& minCoordinate)
{
  if (meshes.empty()) {
    Logger::instance().consoleLog("Empty info loading model");
    return false;
  }

  int32 i = 0;
  m_meshes.resize(meshes.size());
  for (const auto& m : meshes) {
    m_meshes[i].first = m.first;
    m_meshes[i].second = m.second.lock();
    ++i;
  }

  m_boundSphere.setCenter(Vector3f(0.0f, 0.0f, 0.0f));
  m_boundSphere.setRadious(furtherDist);

  m_boundCube.setA(minCoordinate);
  m_boundCube.setSize(maxCoordinate - minCoordinate);
  return true;
}
Vector<Pair<Mesh, WPtr<Material>>>
StaticMesh::getMeshes()
{
  return m_meshes;
}
void
StaticMesh::getMeshes(Vector<Pair<Mesh, WPtr<Material>>>& outMeshes)
{
  int32 i = 0;
  outMeshes.resize(m_meshes.size());
  for (const auto& m : m_meshes) {
    outMeshes[i].first = m.first;
    outMeshes[i].second = m.second;
    ++i;
  }
}
Vector<WPtr<Material>>
StaticMesh::getTextures()
{
  Vector<WPtr<Material>> textures;
  for (auto& m : m_meshes)  {
    textures.push_back(m.second);
  }
  return textures;
}
void
StaticMesh::setTexture(WPtr<Material> texture, SIZE_T index)
{
  if (m_meshes.size() > index) {
    m_meshes[index].second = texture;
  }
}

const Sphere&
StaticMesh::getBoundingSphere()
{
  return m_boundSphere;
}

const BoxAAB&
StaticMesh::getBoundingBox()
{
  return m_boundCube;
}
}