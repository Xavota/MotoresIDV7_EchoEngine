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
  clear();

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
    m_dirtyMatFlags.emplace_back(Pair<bool, String>(true, "Default_mat"));
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
  clear();

  if (meshes.empty()) {
    Logger::instance().consoleLog("Empty info loading model");
    return false;
  }

  int32 i = 0;
  m_meshes.resize(meshes.size());
  m_dirtyMatFlags.resize(meshes.size());
  for (const auto& m : meshes) {
    m_meshes[i].first = m.first;
    m_meshes[i].second = m.second;

    m_dirtyMatFlags[i].first = true;
    if (!m_meshes[i].second.expired()) {
      m_dirtyMatFlags[i].second = m_meshes[i].second.lock()->getResourceName();
    }
    else {
      m_dirtyMatFlags[i].second = "Default_mat";
    }
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
void
StaticMesh::addMesh(const Mesh& stMesh,
                    float furtherDist,
                    const Vector3f& maxCoordinate,
                    const Vector3f& minCoordinate)
{
  addMesh(stMesh,
          ResourceManager::instance().getResourceMaterial("Default_mat"),
          furtherDist,
          minCoordinate,
          maxCoordinate);
}
void
StaticMesh::addMesh(const Mesh& stMesh,
                    WPtr<Material> mat,
                    float furtherDist,
                    const Vector3f& maxCoordinate,
                    const Vector3f& minCoordinate)
{
  m_meshes.emplace_back
  (
    Pair<Mesh, WPtr<Material>>
    (
      stMesh,
      mat
    )
  );
  if (!mat.expired()) {
    m_dirtyMatFlags.emplace_back(Pair<bool, String>(true,
                                                mat.lock()->getResourceName()));
  }
  else {
    m_dirtyMatFlags.emplace_back(Pair<bool, String>(true, "Default_mat"));
  }

  float rad = m_boundSphere.getRadious();
  rad = rad > furtherDist ? rad : furtherDist;
  m_boundSphere.setRadious(rad);

  Vector3f minCoord = m_boundCube.getA();
  minCoord.x = minCoord.x < minCoordinate.x ? minCoord.x : minCoordinate.x;
  minCoord.y = minCoord.y < minCoordinate.y ? minCoord.y : minCoordinate.y;
  minCoord.z = minCoord.z < minCoordinate.z ? minCoord.z : minCoordinate.z;
  m_boundCube.setA(minCoord);
  Vector3f maxCoord = m_boundCube.getB();
  maxCoord.x = maxCoord.x > maxCoordinate.x ? maxCoord.x : maxCoordinate.x;
  maxCoord.y = maxCoord.y > maxCoordinate.y ? maxCoord.y : maxCoordinate.y;
  maxCoord.z = maxCoord.z > maxCoordinate.z ? maxCoord.z : maxCoordinate.z;
  m_boundCube.setSize(maxCoord - minCoord);
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
    m_dirtyMatFlags[index].first = true;
    if (!m_meshes[index].second.expired()) {
      m_dirtyMatFlags[index].second = m_meshes[index].second.lock()->getResourceName();
    }
    else {
      m_dirtyMatFlags[index].second = "Default_mat";
    }
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
void
StaticMesh::clear()
{
  m_meshes.clear();
  m_dirtyMatFlags.clear();
  m_boundCube.setA(Vector3f(0.0f, 0.0f, 0.0f));
  m_boundCube.setSize(Vector3f(0.0f, 0.0f, 0.0f));
  m_boundSphere.setRadious(0.0f);
}
}