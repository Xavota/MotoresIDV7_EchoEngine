#include "eeResourceManager.h"
#include "eeModel.h"
#include "eeMesh.h"
#include "eeTexture.h"
#include "eeGraficsApi.h"

namespace eeEngineSDK
{
SPtr<Texture> 
ResourceManager::loadTextureFromFile(const String& fileName,
                                     const String resourceName)
{
  if (m_meshes.find(resourceName) != m_meshes.end())
  {
    std::cout << "Resource already with this name" << std::endl;
    return nullptr;
  }

  if (fileName != "")
  {
    std::cout << "Empty info loading model" << std::endl;
    return nullptr;
  }

  SPtr<Texture> tex = GraphicsApi::instance().getTexturePtr();
  if (!tex->loadFromFile(fileName))
  {
    return nullptr;
  }

  m_textures.insert(make_pair(resourceName, tex));
  return m_textures[resourceName];
}
SPtr<Model>
ResourceManager::loadModelFromFile(const String& fileName, 
                                   const String resourceName)
{
  if (m_meshes.find(resourceName) != m_meshes.end())
  {
    std::cout << "Resource already with this name" << std::endl;
    return nullptr;
  }

  if (fileName != "")
  {
    std::cout << "Empty info loading model" << std::endl;
    return nullptr;
  }

  SPtr<Model> model = std::make_shared<Model>();
  if (!model->loadFromFile(fileName))
  {
    return nullptr;
  }

  m_models.insert(make_pair(resourceName, model));
  return m_models[resourceName];
}
SPtr<Model> 
ResourceManager::loadModelFromMeshesArray(const Vector<SPtr<Mesh>>& meshes,
                                          const String resourceName)
{
  if (m_meshes.find(resourceName) != m_meshes.end())
  {
    std::cout << "Resource already with this name" << std::endl;
    return nullptr;
  }

  if (meshes.empty())
  {
    std::cout << "Empty info loading model" << std::endl;
    return nullptr;
  }

  SPtr<Model> model = std::make_shared<Model>();
  if (!model->loadFromMeshes(meshes))
  {
    return nullptr;
  }

  m_models.insert(make_pair(resourceName, model));
  return m_models[resourceName];
}
SPtr<Model>
ResourceManager::loadModelFromMeshesArray(const Vector<Pair<SPtr<Mesh>, uint8>>& meshes,
                                          const Vector<SPtr<Texture>>& textures,
                                          const String resourceName)
{
  if (m_meshes.find(resourceName) != m_meshes.end())
  {
    std::cout << "Resource already with this name" << std::endl;
    return nullptr;
  }

  if (meshes.empty())
  {
    std::cout << "Empty info loading model" << std::endl;
    return nullptr;
  }

  SPtr<Model> model = std::make_shared<Model>();
  if (!model->loadFromMeshes(meshes, textures))
  {
    return nullptr;
  }

  m_models.insert(make_pair(resourceName, model));
  return m_models[resourceName];
}


SPtr<Mesh> 
ResourceManager::loadMeshFromVertexArray(const Vector<SimplexVertex>& vertices,
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
SPtr<Mesh> 
ResourceManager::loadMeshFromVertexArray(const Vector<SimpleVertex>& vertices, 
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
SPtr<Mesh>
ResourceManager::loadMeshFromVertexArray(const Vector<ComplexVertex>& vertices,
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
SPtr<Mesh>
ResourceManager::loadMeshFromVertexArray(const Vector<SimpleAnimVertex>& vertices,
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
SPtr<Mesh>
ResourceManager::loadMeshFromVertexArray(const Vector<ComplexAnimVertex>& vertices,
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
SPtr<Mesh>
ResourceManager::loadMeshFromVertexArray(const Vector<SimplexVertex>& vertices,
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
SPtr<Mesh>
ResourceManager::loadMeshFromVertexArray(const Vector<SimpleVertex>& vertices,
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
SPtr<Mesh>
ResourceManager::loadMeshFromVertexArray(const Vector<ComplexVertex>& vertices,
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
SPtr<Mesh>
ResourceManager::loadMeshFromVertexArray(const Vector<SimpleAnimVertex>& vertices,
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
SPtr<Mesh>
ResourceManager::loadMeshFromVertexArray(const Vector<ComplexAnimVertex>& vertices,
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


SPtr<Texture> ResourceManager::getResourceTexture(const String& resourceName)
{
  if (m_textures.find(resourceName) != m_textures.end())
  {
    return m_textures[resourceName];
  }
  return nullptr;
}
SPtr<Model> ResourceManager::getResourceModel(const String& resourceName)
{
  if (m_models.find(resourceName) != m_models.end())
  {
    return m_models[resourceName];
  }
  return nullptr;
}
SPtr<Mesh> ResourceManager::getResourceMesh(const String& resourceName)
{
  if (m_meshes.find(resourceName) != m_meshes.end())
  {
    return m_meshes[resourceName];
  }
  return nullptr;
}
}