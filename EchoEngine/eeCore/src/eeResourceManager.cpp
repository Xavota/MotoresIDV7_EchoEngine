#include "eeResourceManager.h"
#include "eeModel.h"
#include "eeMesh.h"
#include "eeTexture.h"
#include "eeVertexShader.h"
#include "eePixelShader.h"
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

  if (fileName == "")
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



SPtr<VertexShader> 
ResourceManager::loadVertexShaderFromFile(const String& fileName, 
                                          const String& resourceName)
{
  if (m_vertexShaders.find(resourceName) != m_vertexShaders.end())
  {
    std::cout << "Resource already with this name" << std::endl;
    return nullptr;
  }

  SPtr<VertexShader> shader = GraphicsApi::instance().getVertexShaderPtr();
  if (!shader->compileFromFile(fileName))
  {
    return nullptr;
  }

  m_vertexShaders.insert(make_pair(resourceName, shader));
  return m_vertexShaders[resourceName];
}

SPtr<VertexShader>
ResourceManager::loadVertexShaderFromString(const String& shaderString,
                                            const String& resourceName)
{
  if (m_vertexShaders.find(resourceName) != m_vertexShaders.end())
  {
    std::cout << "Resource already with this name" << std::endl;
    return nullptr;
  }

  SPtr<VertexShader> shader = GraphicsApi::instance().getVertexShaderPtr();
  if (!shader->compileFromString(shaderString))
  {
    return nullptr;
  }

  m_vertexShaders.insert(make_pair(resourceName, shader));
  return m_vertexShaders[resourceName];
}

SPtr<PixelShader>
ResourceManager::loadPixelShaderFromFile(const String& fileName,
                                         const String& resourceName)
{
  if (m_pixelShaders.find(resourceName) != m_pixelShaders.end())
  {
    std::cout << "Resource already with this name" << std::endl;
    return nullptr;
  }

  SPtr<PixelShader> shader = GraphicsApi::instance().getPixelShaderPtr();
  if (!shader->compileFromFile(fileName))
  {
    return nullptr;
  }

  m_pixelShaders.insert(make_pair(resourceName, shader));
  return m_pixelShaders[resourceName];
}

SPtr<PixelShader>
ResourceManager::loadPixelShaderFromString(const String& shaderString,
                                           const String& resourceName)
{
  if (m_pixelShaders.find(resourceName) != m_pixelShaders.end())
  {
    std::cout << "Resource already with this name" << std::endl;
    return nullptr;
  }

  SPtr<PixelShader> shader = GraphicsApi::instance().getPixelShaderPtr();
  if (!shader->compileFromString(shaderString))
  {
    return nullptr;
  }

  m_pixelShaders.insert(make_pair(resourceName, shader));
  return m_pixelShaders[resourceName];
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
SPtr<VertexShader> ResourceManager::getResourceVertexShader(const String& resourceName)
{
  if (m_vertexShaders.find(resourceName) != m_vertexShaders.end())
  {
    return m_vertexShaders[resourceName];
  }
  return nullptr;
}
SPtr<PixelShader> ResourceManager::getResourcePixelShader(const String& resourceName)
{
  if (m_pixelShaders.find(resourceName) != m_pixelShaders.end())
  {
    return m_pixelShaders[resourceName];
  }
  return nullptr;
}
}