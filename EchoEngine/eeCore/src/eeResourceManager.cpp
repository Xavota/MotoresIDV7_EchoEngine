#include "eeResourceManager.h"
#include "eeModel.h"
#include "eeMesh.h"
#include "eeTexture.h"
#include "eeVertexShader.h"
#include "eePixelShader.h"
#include "eeGraficsApi.h"
#include "eeSkeletalMesh.h"
#include "eeAnimation.h"


#pragma warning(push, 0)   
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)

#include <eeMemoryManager.h>

namespace eeEngineSDK
{
SPtr<Texture> 
ResourceManager::loadTextureFromFile(const String& fileName,
                                     const String resourceName,
                                     SamplerStateDesc desc)
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

  SPtr<Texture> tex = GraphicsApi::instance().createTexturePtr();
  if (!tex->loadFromFile(fileName, desc))
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

  if (fileName == "")
  {
    std::cout << "Empty info loading model" << std::endl;
    return nullptr;
  }

  Assimp::Importer* importer = nullptr;
  const aiScene* scene = nullptr;

  importer = new Assimp::Importer();
  scene = importer->ReadFile
  (
    fileName,
    aiProcessPreset_TargetRealtime_MaxQuality
    | aiProcess_ConvertToLeftHanded
  );
  if (!scene)
  {
    std::cout << importer->GetErrorString() << std::endl;
    return nullptr;
  }


  SPtr<Model> model = MemoryManager::instance().newPtr<Model>();
  if (scene->HasAnimations())
  {
    SPtr<SkeletalMesh> skMesh =
    loadSkeletalMeshFromFile(fileName, resourceName + "_sk");

    if (skMesh)
    {
      if (!model->loadFromFile(fileName, skMesh))
      {
        return nullptr;
      }
    }
    else
    {
      if (!model->loadFromFile(fileName))
      {
        return nullptr;
      }
    }
  }
  else
  {
    if (!model->loadFromFile(fileName))
    {
      return nullptr;
    }
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

  SPtr<Model> model = MemoryManager::instance().newPtr<Model>();
  if (!model->loadFromMeshes(meshes))
  {
    return nullptr;
  }

  m_models.insert(make_pair(resourceName, model));
  return m_models[resourceName];
}
SPtr<Model>
ResourceManager::loadModelFromMeshesArray(
  const Vector<Pair<SPtr<Mesh>, SPtr<Texture>>>& meshes,
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

  SPtr<Model> model = MemoryManager::instance().newPtr<Model>();
  if (!model->loadFromMeshes(meshes))
  {
    return nullptr;
  }

  m_models.insert(make_pair(resourceName, model));
  return m_models[resourceName];
}



SPtr<SkeletalMesh>
ResourceManager::loadSkeletalMeshFromFile(const String& fileName,
                                          const String& resourceName)
{
  if (m_skeletalMeshes.find(resourceName) != m_skeletalMeshes.end())
  {
    std::cout << "Resource already with this name" << std::endl;
    return nullptr;
  }

  if (fileName == "")
  {
    std::cout << "Empty info loading model" << std::endl;
    return nullptr;
  }

  SPtr<SkeletalMesh> skeletal = MemoryManager::instance().newPtr<SkeletalMesh>();
  if (!skeletal->loadFromFile(fileName))
  {
    return nullptr;
  }

  m_skeletalMeshes.insert(make_pair(resourceName, skeletal));
  return m_skeletalMeshes[resourceName];
}

SPtr<Animation>
ResourceManager::loadAnimationFromFile(const String& fileName, const String& resourceName)
{
  if (m_animations.find(resourceName) != m_animations.end())
  {
    std::cout << "Resource already with this name" << std::endl;
    return nullptr;
  }

  if (fileName == "")
  {
    std::cout << "Empty info loading model" << std::endl;
    return nullptr;
  }

  SPtr<Animation> anim = MemoryManager::instance().newPtr<Animation>();
  if (!anim->loadFromFile(fileName))
  {
    return nullptr;
  }

  m_animations.insert(make_pair(resourceName, anim));
  return m_animations[resourceName];
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

  SPtr<VertexShader> shader = GraphicsApi::instance().createVertexShaderPtr();
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

  SPtr<VertexShader> shader = GraphicsApi::instance().createVertexShaderPtr();
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

  SPtr<PixelShader> shader = GraphicsApi::instance().createPixelShaderPtr();
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

  SPtr<PixelShader> shader = GraphicsApi::instance().createPixelShaderPtr();
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
SPtr<SkeletalMesh> ResourceManager::getResourceSkeletalMesh(const String& resourceName)
{
  if (m_skeletalMeshes.find(resourceName) != m_skeletalMeshes.end())
  {
    return m_skeletalMeshes[resourceName];
  }
  return nullptr;
}
SPtr<Animation> ResourceManager::getResourceAnimation(const String& resourceName)
{
  if (m_animations.find(resourceName) != m_animations.end())
  {
    return m_animations[resourceName];
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