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
/*template<typename V, typename I>*/
StaticMesh/*<V,I>*/::StaticMesh(const Vector<Mesh/*<V, I>*/>&meshes,
                            const String& name,
                            const Vector3f& furtherVertexPosition,
                            const Vector3f& maxCoordinate,
                            const Vector3f& minCoordinate)
{
  loadFromMeshes(meshes,
                 name,
                 furtherVertexPosition,
                 maxCoordinate,
                 minCoordinate);
}
/*template<typename V, typename I>*/
StaticMesh/*<V, I>*/::StaticMesh(const Vector<Pair<Mesh/*<V,I>*/, SPtr<Material>>>& meshes,
                             const String& name,
                             const Vector3f& furtherVertexPosition,
                             const Vector3f& maxCoordinate,
                             const Vector3f& minCoordinate)
{
  loadFromMeshes(meshes,
                 name,
                 furtherVertexPosition,
                 maxCoordinate,
                 minCoordinate);
}
/*template<typename V, typename I>*/
bool
StaticMesh/*<V, I>*/::loadFromMeshes(const Vector<Mesh/*<V,I>*/>& meshes,
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
      Pair<Mesh, SPtr<Material>>
      (
        m,
        resourseManager.getResourceMaterial("Default_mat")
      )
    );
  }

  m_boundSphere.setCenter(Vector3f(0.0f, 0.0f, 0.0f));
  m_boundSphere.setRadious(furtherVertexPosition.getMagnitud());

  m_boundCube.setA(minCoordinate);
  m_boundCube.setSize(maxCoordinate - minCoordinate);
  return true;
}
/*template<typename V, typename I>*/
bool
StaticMesh/*<V, I>*/::loadFromMeshes(const Vector<Pair<Mesh/*<V,I>*/, SPtr<Material>>>& meshes,
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

  m_boundSphere.setCenter(Vector3f(0.0f, 0.0f, 0.0f));
  m_boundSphere.setRadious(furtherVertexPosition.getMagnitud());

  m_boundCube.setA(minCoordinate);
  m_boundCube.setSize(maxCoordinate - minCoordinate);
  return true;
}
/*template<typename V, typename I>*/
Vector<Pair<Mesh/*<V,I>*/, SPtr<Material>>>
StaticMesh/*<V, I>*/::getMeshes()
{
  return m_meshes;
}
/*template<typename V, typename I>*/
Vector<SPtr<Material>>
StaticMesh/*<V, I>*/::getTextures()
{
  Vector<SPtr<Material>> textures;
  for (auto& m : m_meshes)  {
    textures.push_back(m.second);
  }
  return textures;
}
/*template<typename V, typename I>*/
void
StaticMesh/*<V, I>*/::setTexture(SPtr<Material> texture, SIZE_T index)
{
  if (m_meshes.size() > index) {
    m_meshes[index].second = texture;
  }
}

/*template<typename V, typename I>*/
String
StaticMesh/*<V, I>*/::getName()
{
  return m_name;
}

/*template<typename V, typename I>*/
const Sphere&
StaticMesh/*<V, I>*/::getBoundingSphere()
{
  return m_boundSphere;
}

/*template<typename V, typename I>*/
const Vector3f&
StaticMesh/*<V, I>*/::getFurtherPosition()
{
  return m_furtherPosition;
}

/*template<typename V, typename I>*/
const BoxAAB&
StaticMesh/*<V, I>*/::getBoundingBox()
{
  return m_boundCube;
}
/*template<typename V, typename I>*/
SPtr<StaticMesh/*<V,I>*/> StaticMesh/*<V,I>*/::cube = nullptr;
/*template<typename V, typename I>*/
SPtr<StaticMesh/*<V,I>*/> StaticMesh/*<V,I>*/::tetrahedron = nullptr;
/*template<typename V, typename I>*/
SPtr<StaticMesh/*<V,I>*/> StaticMesh/*<V,I>*/::cone = nullptr;
/*template<typename V, typename I>*/
SPtr<StaticMesh/*<V,I>*/> StaticMesh/*<V,I>*/::cylinder = nullptr;
/*template<typename V, typename I>*/
SPtr<StaticMesh/*<V,I>*/> StaticMesh/*<V,I>*/::sphere = nullptr;
/*template<typename V, typename I>*/
SPtr<StaticMesh/*<V,I>*/> StaticMesh/*<V,I>*/::capsule = nullptr;
/*template<typename V, typename I>*/
SPtr<StaticMesh/*<V,I>*/> StaticMesh/*<V,I>*/::SAQ = nullptr;
/*template<typename V, typename I>*/
void
StaticMesh/*<V, I>*/::initPrimitives()
{
  Vector<SimpleVertex> vertices;
  Vector<uint16> indices;

  vertices = 
  {
    // Front
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f,  1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f,  1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f,  1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f,  1.0f, 0.0f)
    },

    // Back
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f, -1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f, -1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f, -1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f, -1.0f, 0.0f)
    },

    // Left
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
    },

    // Right
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f)
    },

    // Up
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f)
    },

    // Down
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f, -1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f, -1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f, -1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f, -1.0f,  0.0f, 0.0f)
    }
  };

  indices =
  {
    0u, 2u, 1u,
    0u, 3u, 2u,

    4u, 6u, 5u,
    4u, 7u, 6u,

    8u, 10u, 9u,
    8u, 11u, 10u,

    12u, 14u, 13u,
    12u, 15u, 14u,

    16u, 18u, 17u,
    16u, 19u, 18u,

    20u, 22u, 21u,
    20u, 23u, 22u
  };

  auto& memoryManager = MemoryManager::instance();

  Mesh/*<SimpleVertex,uint16>*/ cubeMesh;
  cubeMesh.loadFromArray
  (
    vertices,
    indices
  );

  cube = memoryManager.newPtr<StaticMesh/*<SimpleVertex,uint16>*/>();
  cube->loadFromMeshes
  (
    Vector<Mesh/*<SimpleVertex,uint16>*/>
    {
      cubeMesh
    },
    "Cube",
    Vector3f(0.5f, 0.5f, 0.5f),
    Vector3f(0.5f, 0.5f, 0.5f),
    Vector3f(-0.5f, -0.5f, -0.5f)
  );

  Mesh::initPrimitives();
}
}