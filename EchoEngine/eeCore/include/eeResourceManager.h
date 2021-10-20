#pragma once
#include "eePrerequisitesCore.h"
#include "eeTexture.h"
#include "eeModel.h"
#include "eeMesh.h"
#include <eeModule.h>

namespace eeEngineSDK {
class EE_CORE_EXPORT ResourceManager : public Module<ResourceManager>
{
 public:
  ResourceManager() = default;
  ~ResourceManager() = default;

  SPtr<Texture>
  loadTextureFromFile(const String& fileName, const String resourceName);

  SPtr<Model> 
  loadModelFromFile(const String& fileName, const String resourceName);
  SPtr<Model>
  loadModelFromMeshesArray(const Vector<SPtr<Mesh>>& fileName, 
                           const String resourceName);
  SPtr<Model>
  loadModelFromMeshesArray(const Vector<Pair<SPtr<Mesh>, uint8>>& meshes,
                           const Vector<SPtr<Texture>>& textures,
                           const String resourceName);
                           
  SPtr<Mesh>
  loadMeshFromVertexArray(const Vector<SimplexVertex>& vertices,
                          const Vector<uint16>& indices, 
                          const String resourceName);
  SPtr<Mesh>
  loadMeshFromVertexArray(const Vector<SimpleVertex>& vertices,
                          const Vector<uint16>& indices, 
                          const String resourceName);
  SPtr<Mesh>
  loadMeshFromVertexArray(const Vector<ComplexVertex>& vertices,
                          const Vector<uint16>& indices, 
                          const String resourceName);
  SPtr<Mesh>
  loadMeshFromVertexArray(const Vector<SimpleAnimVertex>& vertices,
                          const Vector<uint16>& indices, 
                          const String resourceName);
  template<uint32 Size = 4>
  FORCEINLINE SPtr<Mesh>
  loadMeshFromVertexArray(const Vector<SimpleBigAnimVertex<Size>>& vertices,
                          const Vector<uint16>& indices, 
                          const String resourceName);
  SPtr<Mesh>
  loadMeshFromVertexArray(const Vector<ComplexAnimVertex>& vertices,
                          const Vector<uint16>& indices, 
                          const String resourceName);
  template<uint32 Size = 4>
  FORCEINLINE SPtr<Mesh>
  loadMeshFromVertexArray(const Vector<ComplexBigAnimVertex<Size>>& vertices,
                          const Vector<uint16>& indices, 
                          const String resourceName);
  SPtr<Mesh>
  loadMeshFromVertexArray(const Vector<SimplexVertex>& vertices,
                          const Vector<uint32>& indices, 
                          const String resourceName);
  SPtr<Mesh>
  loadMeshFromVertexArray(const Vector<SimpleVertex>& vertices,
                          const Vector<uint32>& indices, 
                          const String resourceName);
  SPtr<Mesh>
  loadMeshFromVertexArray(const Vector<ComplexVertex>& vertices,
                          const Vector<uint32>& indices, 
                          const String resourceName);
  SPtr<Mesh>
  loadMeshFromVertexArray(const Vector<SimpleAnimVertex>& vertices,
                          const Vector<uint32>& indices, 
                          const String resourceName);
  template<uint32 Size = 4>
  FORCEINLINE SPtr<Mesh>
  loadMeshFromVertexArray(const Vector<SimpleBigAnimVertex<Size>>& vertices,
                          const Vector<uint32>& indices, 
                          const String resourceName);
  SPtr<Mesh>
  loadMeshFromVertexArray(const Vector<ComplexAnimVertex>& vertices,
                          const Vector<uint32>& indices, 
                          const String resourceName);
  template<uint32 Size = 4>
  FORCEINLINE SPtr<Mesh>
  loadMeshFromVertexArray(const Vector<ComplexBigAnimVertex<Size>>& vertices,
                          const Vector<uint32>& indices, 
                          const String resourceName);

  SPtr<Texture>
  getResourceTexture(const String& resourceName);
  SPtr<Model>
  getResourceModel(const String& resourceName);
  SPtr<Mesh>
  getResourceMesh(const String& resourceName);


 private:
  Map<String, SPtr<Texture>> m_textures;
  Map<String, SPtr<Model>> m_models;
  Map<String, SPtr<Mesh>> m_meshes;
};
template<uint32 Size>
FORCEINLINE SPtr<Mesh>
ResourceManager::loadMeshFromVertexArray(const Vector<SimpleBigAnimVertex<Size>>& vertices, 
                                         const Vector<uint16>& indices, 
                                         const String resourceName)
{
  if (m_meshes.find(resourceName) != m_meshes.end())
  {
    std::cout << "Resource already with this name" << std::endl;
    return nullptr;
  }

  SPtr<Mesh> mesh = std::make_shared<Mesh>();
  if (!mesh->loadFromArray(vertices, indices))
  {
    return nullptr;
  }

  m_meshes.insert(make_pair(resourceName, mesh));
  return m_meshes[resourceName];
}
template<uint32 Size>
FORCEINLINE SPtr<Mesh>
ResourceManager::loadMeshFromVertexArray(const Vector<ComplexBigAnimVertex<Size>>& vertices,
                                         const Vector<uint16>& indices, 
                                         const String resourceName)
{
  if (m_meshes.find(resourceName) != m_meshes.end())
  {
    std::cout << "Resource already with this name" << std::endl;
    return nullptr;
  }

  SPtr<Mesh> mesh = std::make_shared<Mesh>();
  if (!mesh->loadFromArray(vertices, indices))
  {
    return nullptr;
  }

  m_meshes.insert(make_pair(resourceName, mesh));
  return m_meshes[resourceName];
}
template<uint32 Size>
FORCEINLINE SPtr<Mesh>
ResourceManager::loadMeshFromVertexArray(const Vector<SimpleBigAnimVertex<Size>>& vertices,
                                         const Vector<uint32>& indices, 
                                         const String resourceName)
{
  if (m_meshes.find(resourceName) != m_meshes.end())
  {
    std::cout << "Resource already with this name" << std::endl;
    return nullptr;
  }

  SPtr<Mesh> mesh = std::make_shared<Mesh>();
  if (!mesh->loadFromArray(vertices, indices))
  {
    return nullptr;
  }

  m_meshes.insert(make_pair(resourceName, mesh));
  return m_meshes[resourceName];
}
template<uint32 Size>
FORCEINLINE SPtr<Mesh>
ResourceManager::loadMeshFromVertexArray(const Vector<ComplexBigAnimVertex<Size>>& vertices,
                                         const Vector<uint32>& indices, 
                                         const String resourceName)
{
  if (m_meshes.find(resourceName) != m_meshes.end())
  {
    std::cout << "Resource already with this name" << std::endl;
    return nullptr;
  }

  SPtr<Mesh> mesh = std::make_shared<Mesh>();
  if (!mesh->loadFromArray(vertices, indices))
  {
    return nullptr;
  }

  m_meshes.insert(make_pair(resourceName, mesh));
  return m_meshes[resourceName];
}
}
