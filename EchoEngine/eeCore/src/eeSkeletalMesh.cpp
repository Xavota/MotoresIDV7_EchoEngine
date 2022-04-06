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
/*template<typename V, typename I>*/
SkeletalMesh/*<V, I>*/::SkeletalMesh(const Vector<BoneMesh/*<V, I>*/>& meshes,
                                 SPtr<Skeletal> skeleton,
                                 const String& name,
                                 const Vector3f& furtherVertexPosition,
                                 const Vector3f& maxCoordinate,
                                 const Vector3f& minCoordinate)
{
  loadFromMeshes(meshes,
                 skeleton,
                 name,
                 furtherVertexPosition,
                 maxCoordinate,
                 minCoordinate);
}
/*template<typename V, typename I>*/
SkeletalMesh/*<V, I>*/::SkeletalMesh(const Vector<Pair<BoneMesh/*<V, I>*/, SPtr<Material>>>& meshes,
                                 SPtr<Skeletal> skeleton,
                                 const String& name,
                                 const Vector3f& furtherVertexPosition,
                                 const Vector3f& maxCoordinate,
                                 const Vector3f& minCoordinate)
{
  loadFromMeshes(meshes,
                 skeleton,
                 name,
                 furtherVertexPosition,
                 maxCoordinate,
                 minCoordinate);
}
/*template<typename V, typename I>*/
bool
SkeletalMesh/*<V, I>*/::loadFromMeshes(const Vector<BoneMesh/*<V, I>*/>& meshes,
                                       SPtr<Skeletal> skeleton,
                                       const String& name,
                                       const Vector3f& furtherVertexPosition,
                                       const Vector3f& maxCoordinate,
                                       const Vector3f& minCoordinate)
{
  if (meshes.empty()) {
    Logger::instance().ConsoleLog("Empty info loading model");
    return false;
  }

  m_name = name;

  auto& resourseManager = ResourceManager::instance();

  for (const auto& m : meshes) {
    m_meshes.emplace_back
    (
      Pair<BoneMesh/*<V, I>*/, SPtr<Material>>
      (
        m,
        resourseManager.getResourceMaterial("Default_mat")
      )
    );
  }

  m_skeleton = skeleton;

  m_boundSphere.setCenter(Vector3f(0.0f, 0.0f, 0.0f));
  m_boundSphere.setRadious(furtherVertexPosition.getMagnitud());

  m_boundCube.setA(minCoordinate);
  m_boundCube.setSize(maxCoordinate - minCoordinate);
  return true;
}
/*template<typename V, class I>*/
bool
SkeletalMesh/*<V, I>*/::loadFromMeshes(const Vector<Pair<BoneMesh/*<V, I>*/, SPtr<Material>>>& meshes,
                                   SPtr<Skeletal> skeleton,
                                   const String& name,
                                   const Vector3f& furtherVertexPosition,
                                   const Vector3f& maxCoordinate,
                                   const Vector3f& minCoordinate)
{
  if (meshes.empty()) {
    Logger::instance().ConsoleLog("Empty info loading model");
    return false;
  }

  m_name = name;

  m_meshes = meshes;

  m_skeleton = skeleton;

  m_boundSphere.setCenter(Vector3f(0.0f, 0.0f, 0.0f));
  m_boundSphere.setRadious(furtherVertexPosition.getMagnitud());

  m_boundCube.setA(minCoordinate);
  m_boundCube.setSize(maxCoordinate - minCoordinate);
  return true;
}
/*template<typename V, typename I>*/
Vector<Pair<BoneMesh/*<V, I>*/, SPtr<Material>>>
SkeletalMesh/*<V, I>*/::getMeshes()
{
  return m_meshes;
}
/*template<typename V, typename I>*/
Vector<SPtr<Material>>
SkeletalMesh/*<V, I>*/::getTextures()
{
  Vector<SPtr<Material>> textures;
  for (auto& m : m_meshes) {
    textures.push_back(m.second);
  }
  return textures;
}
/*template<typename V, typename I>*/
void
SkeletalMesh/*<V, I>*/::setTexture(SPtr<Material> texture, uint32 index)
{
  if (static_cast<uint32>(m_meshes.size()) > index) {
    m_meshes[index].second = texture;
  }
}
/*template<typename V, typename I>*/
String
SkeletalMesh/*<V, I>*/::getName()
{
  return m_name;
}
/*template<typename V, typename I>*/
const Sphere&
SkeletalMesh/*<V, I>*/::getBoundingSphere()
{
  return m_boundSphere;
}

/*template<typename V, typename I>*/
const Vector3f&
SkeletalMesh/*<V, I>*/::getFurtherPosition()
{
  return m_furtherPosition;
}
/*template<typename V, typename I>*/
const BoxAAB&
SkeletalMesh/*<V, I>*/::getBoundingBox()
{
  return m_boundCube;
}
}