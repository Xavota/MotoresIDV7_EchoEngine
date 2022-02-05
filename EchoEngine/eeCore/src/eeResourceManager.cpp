#include "eeResourceManager.h"

#pragma warning(push, 0)   
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)
#include <eeLogger.h>
#include <eeMemoryManager.h>
#include <eeMath.h>

#include "eeModel.h"
#include "eeMesh.h"
#include "eeTexture.h"
#include "eeVertexShader.h"
#include "eePixelShader.h"
#include "eeGraficsApi.h"
#include "eeSkeletalMesh.h"
#include "eeSkeletal.h"
#include "eeAnimation.h"

namespace eeEngineSDK
{
bool
ResourceManager::importResourceFromFile(const String& fileName)
{
  /*  GET NAME AND FILE EXTENSION */
  String name;
  String fileExtension;
  auto fileSize = static_cast<int32>(fileName.size());
  bool point = false;
  for (int32 i = fileSize - 1; i >= 0; --i) {
    if (!point) {
      if (fileName[i] != '.') {
        fileExtension = fileName[i] + fileExtension;
      }
      else {
        point = true;
      }
    }
    else {
      if (fileName[i] != '/' && fileName[i] != '\\') {
        name = fileName[i] + name;
      }
      else { break; }
    }
  }

  for (char& c : fileExtension) {
    c = (c >= 'A' && c <= 'Z' ? c + 32 : c);
  }

  if (fileExtension == "png" || fileExtension == "jpg"
   || fileExtension == "tga" || fileExtension == "bmp"
   || fileExtension == "tiff") {
    SamplerStateDesc samDesc;
    memset(&samDesc, 0, sizeof(samDesc));
    samDesc.filter = eFILTER::kMIN_MAG_MIP_LINEAR;
    samDesc.addressU = eTEXTURE_ADDRESS_MODE::WRAP;
    samDesc.addressV = eTEXTURE_ADDRESS_MODE::WRAP;
    samDesc.addressW = eTEXTURE_ADDRESS_MODE::WRAP;
    samDesc.comparisonFunc = eCOMPARISON_FUNC::NEVER;
    samDesc.minLOD = 0.0f;
    samDesc.maxLOD = Math::kMAX_FLOAT;

    loadTextureFromFile(fileName, name + "_tex", samDesc);
  }
  else if (fileExtension == "obj" || fileExtension == "fbx"
        || fileExtension == "md5mesh") {
    auto* importer = new Assimp::Importer();
    const aiScene* scene = importer->ReadFile
    (
      fileName,
      aiProcessPreset_TargetRealtime_MaxQuality
      | aiProcess_ConvertToLeftHanded
    );

    if (!scene) {
      Logger::instance().ConsoleLog(importer->GetErrorString());
      delete importer;
      return false;
    }
    
    Vector<SPtr<Texture>> textures;
    if (scene->HasTextures()) {
      // Load textures from assimp
    }
    if (scene->mRootNode) {
      SPtr<Skeletal> skMesh = loadSkeletalFromFile(fileName, name + "_sk");

      if (scene->HasMeshes()) {
        loadSkeletalMeshFromFile(fileName, name + "_skm", skMesh, textures);
      }
    }
    else {
      if (scene->HasMeshes()) {
        loadModelFromFile(fileName, name + "_sm", textures);
      }
    }
    if (scene->HasAnimations()) {
      for (uint32 i = 0; i < scene->mNumAnimations; ++i) {
        loadAnimationFromFile(fileName,
                         name + "_anim_" + scene->mAnimations[i]->mName.C_Str(),
                         i);
      }
    }
  }
  else if (fileExtension == "md5anim") {
    auto* importer = new Assimp::Importer();
    const aiScene* scene = importer->ReadFile
    (
      fileName,
      aiProcessPreset_TargetRealtime_MaxQuality
      | aiProcess_ConvertToLeftHanded
    );

    if (!scene) {
      Logger::instance().ConsoleLog(importer->GetErrorString());
      delete importer;
      return false;
    }

    if (scene->HasAnimations()) {
      for (uint32 i = 0; i < scene->mNumAnimations; ++i) {
        loadAnimationFromFile(fileName,
          name + "_anim_" + scene->mAnimations[i]->mName.C_Str(),
          i);
      }
    }
  }
  return false;
}
SPtr<Texture>
ResourceManager::loadTextureFromFile(const String& fileName,
                                     const String resourceName,
                                     SamplerStateDesc desc)
{
  if (m_textures.find(resourceName) != m_textures.end()) {
    Logger::instance().ConsoleLog("Resource already with this name");
    return nullptr;
  }

  if (fileName.empty()) {
    Logger::instance().ConsoleLog("Empty info loading texture");
    return nullptr;
  }

  SPtr<Texture> tex = GraphicsApi::instance().createTexturePtr();
  if (!tex->loadFromFile(fileName, desc)) {
    return nullptr;
  }

  m_textures.insert(make_pair(resourceName, tex));
  return m_textures[resourceName];
}
SPtr<Model>
ResourceManager::loadModelFromFile(const String& fileName, 
                                   const String resourceName,
                                   const Vector<SPtr<Texture>>& textures)
{
  if (m_models.find(resourceName) != m_models.end()) {
    Logger::instance().ConsoleLog("Resource already with this name");
    return nullptr;
  }

  if (fileName.empty()) {
    Logger::instance().ConsoleLog("Empty info loading model");
    return nullptr;
  }

  auto* importer = new Assimp::Importer();
  const aiScene* scene = importer->ReadFile
  (
    fileName,
    aiProcessPreset_TargetRealtime_MaxQuality
    | aiProcess_ConvertToLeftHanded
  );

  if (!scene) {
    Logger::instance().ConsoleLog(importer->GetErrorString());
    delete importer;
    return nullptr;
  }

  SPtr<Model> model = MemoryManager::instance().newPtr<Model>();
  //if (scene->HasAnimations()) {
  //  SPtr<SkeletalMesh> skMesh =
  //  loadSkeletalMeshFromFile(fileName, resourceName + "_sk");
  //
  //  if (skMesh) {
  //    if (!model->loadFromFile(fileName, skMesh)) {
  //      return nullptr;
  //    }
  //  }
  //  else {
  //    if (!model->loadFromFile(fileName)) {
  //      return nullptr;
  //    }
  //  }
  //}
  //else {
    if (!model->loadFromFile(fileName, resourceName, textures)) {
      return nullptr;
    }
  //}

  m_models.insert(make_pair(resourceName, model));
  return m_models[resourceName];
}
SPtr<Model> 
ResourceManager::loadModelFromMeshesArray(const Vector<SPtr<Mesh>>& meshes,
                                          const String resourceName)
{
  if (m_models.find(resourceName) != m_models.end()) {
    Logger::instance().ConsoleLog("Resource already with this name");
    return nullptr;
  }

  if (meshes.empty()) {
    Logger::instance().ConsoleLog("Empty info loading model");
    return nullptr;
  }

  SPtr<Model> model = MemoryManager::instance().newPtr<Model>();
  if (!model->loadFromMeshes(meshes, resourceName)) {
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
  if (m_models.find(resourceName) != m_models.end()) {
    Logger::instance().ConsoleLog("Resource already with this name");
    return nullptr;
  }

  if (meshes.empty()) {
    Logger::instance().ConsoleLog("Empty info loading model");
    return nullptr;
  }

  SPtr<Model> model = MemoryManager::instance().newPtr<Model>();
  if (!model->loadFromMeshes(meshes, resourceName)) {
    return nullptr;
  }

  m_models.insert(make_pair(resourceName, model));
  return m_models[resourceName];
}

SPtr<Skeletal>
ResourceManager::loadSkeletalFromFile(const String& fileName,
                                      const String& resourceName)
{
  if (m_skeletals.find(resourceName) != m_skeletals.end()) {
    Logger::instance().ConsoleLog("Resource already with this name");
    return nullptr;
  }

  if (fileName.empty()) {
    Logger::instance().ConsoleLog("Empty info loading skeletal");
    return nullptr;
  }

  SPtr<Skeletal> skeleton = MemoryManager::instance().newPtr<Skeletal>();
  if (!skeleton->loadFromFile(fileName)) {
    return nullptr;
  }

  m_skeletals.insert(make_pair(resourceName, skeleton));
  return m_skeletals[resourceName];
}

SPtr<SkeletalMesh>
ResourceManager::loadSkeletalMeshFromFile(const String& fileName,
                                          const String& resourceName,
                                          const SPtr<Skeletal> skMesh,
                                          const Vector<SPtr<Texture>>& textures)
{
  if (m_skeletalMeshes.find(resourceName) != m_skeletalMeshes.end()) {
    Logger::instance().ConsoleLog("Resource already with this name");
    return nullptr;
  }

  if (fileName.empty()) {
    Logger::instance().ConsoleLog("Empty info loading skeletal mesh");
    return nullptr;
  }

  SPtr<Skeletal> skeleton = nullptr;
  if (!skMesh) {
    skeleton = loadSkeletalFromFile(fileName, resourceName + "_sk");
  }
  else {
    skeleton = skMesh;
  }

  if (!skeleton) {
    return nullptr;
  }

  SPtr<SkeletalMesh> skeletal = MemoryManager::instance().newPtr<SkeletalMesh>();
  if (!skeletal->loadFromFile(fileName, skeleton, textures)) {
    return nullptr;
  }
  m_skeletalMeshes.insert(make_pair(resourceName, skeletal));
  
  return m_skeletalMeshes[resourceName];
}

SPtr<Animation>
ResourceManager::loadAnimationFromFile(const String& fileName,
                                       const String& resourceName,
                                       const int32 animIndex)
{
  if (m_animations.find(resourceName) != m_animations.end()) {
    Logger::instance().ConsoleLog("Resource already with this name");
    return nullptr;
  }

  if (fileName.empty()) {
    Logger::instance().ConsoleLog("Empty info loading animation");
    return nullptr;
  }

  SPtr<Animation> anim = MemoryManager::instance().newPtr<Animation>();
  if (!anim->loadFromFile(fileName, animIndex, resourceName)) {
    return nullptr;
  }

  m_animations.insert(make_pair(resourceName, anim));
  return m_animations[resourceName];
}

SPtr<VertexShader>
ResourceManager::loadVertexShaderFromFile(const String& fileName, 
                                          const String& resourceName)
{
  if (m_vertexShaders.find(resourceName) != m_vertexShaders.end()) {
    Logger::instance().ConsoleLog("Resource already with this name");
    return nullptr;
  }

  SPtr<VertexShader> shader = GraphicsApi::instance().createVertexShaderPtr();
  if (!shader->compileFromFile(fileName)) {
    Logger::instance().ConsoleLog("Error compiling shader");
    return nullptr;
  }

  m_vertexShaders.insert(make_pair(resourceName, shader));
  return m_vertexShaders[resourceName];
}

SPtr<VertexShader>
ResourceManager::loadVertexShaderFromString(const String& shaderString,
                                            const String& resourceName)
{
  if (m_vertexShaders.find(resourceName) != m_vertexShaders.end()) {
    Logger::instance().ConsoleLog("Resource already with this name");
    return nullptr;
  }

  SPtr<VertexShader> shader = GraphicsApi::instance().createVertexShaderPtr();
  if (!shader->compileFromString(shaderString)) {
    Logger::instance().ConsoleLog("Error compiling shader");
    return nullptr;
  }

  m_vertexShaders.insert(make_pair(resourceName, shader));
  return m_vertexShaders[resourceName];
}

SPtr<PixelShader>
ResourceManager::loadPixelShaderFromFile(const String& fileName,
                                         const String& resourceName)
{
  if (m_pixelShaders.find(resourceName) != m_pixelShaders.end()) {
    Logger::instance().ConsoleLog("Resource already with this name");
    return nullptr;
  }

  SPtr<PixelShader> shader = GraphicsApi::instance().createPixelShaderPtr();
  if (!shader->compileFromFile(fileName)) {
    Logger::instance().ConsoleLog("Error compiling shader");
    return nullptr;
  }

  m_pixelShaders.insert(make_pair(resourceName, shader));
  return m_pixelShaders[resourceName];
}

SPtr<PixelShader>
ResourceManager::loadPixelShaderFromString(const String& shaderString,
                                           const String& resourceName)
{
  if (m_pixelShaders.find(resourceName) != m_pixelShaders.end()) {
    Logger::instance().ConsoleLog("Resource already with this name");
    return nullptr;
  }

  SPtr<PixelShader> shader = GraphicsApi::instance().createPixelShaderPtr();
  if (!shader->compileFromString(shaderString)) {
    Logger::instance().ConsoleLog("Error compiling shader");
    return nullptr;
  }

  m_pixelShaders.insert(make_pair(resourceName, shader));
  return m_pixelShaders[resourceName];
}

SPtr<Texture>
ResourceManager::getResourceTexture(const String& resourceName)
{
  if (m_textures.find(resourceName) != m_textures.end()) {
    return m_textures[resourceName];
  }
  return nullptr;
}
SPtr<Model>
ResourceManager::getResourceModel(const String& resourceName)
{
  if (m_models.find(resourceName) != m_models.end()) {
    return m_models[resourceName];
  }
  return nullptr;
}
SPtr<Skeletal>
ResourceManager::getResourceSkeletal(const String& resourceName)
{
  if (m_skeletals.find(resourceName) != m_skeletals.end()) {
    return m_skeletals[resourceName];
  }
  return nullptr;
}
SPtr<SkeletalMesh>
ResourceManager::getResourceSkeletalMesh(const String& resourceName)
{
  if (m_skeletalMeshes.find(resourceName) != m_skeletalMeshes.end()) {
    return m_skeletalMeshes[resourceName];
  }
  return nullptr;
}
SPtr<Animation>
ResourceManager::getResourceAnimation(const String& resourceName)
{
  if (m_animations.find(resourceName) != m_animations.end()) {
    return m_animations[resourceName];
  }
  return nullptr;
}
SPtr<VertexShader>
ResourceManager::getResourceVertexShader(const String& resourceName)
{
  if (m_vertexShaders.find(resourceName) != m_vertexShaders.end()) {
    return m_vertexShaders[resourceName];
  }
  return nullptr;
}
SPtr<PixelShader>
ResourceManager::getResourcePixelShader(const String& resourceName)
{
  if (m_pixelShaders.find(resourceName) != m_pixelShaders.end()) {
    return m_pixelShaders[resourceName];
  }
  return nullptr;
}
Map<String, SPtr<Texture>>
ResourceManager::getAllTextureResources()
{
  return m_textures;
}
Map<String, SPtr<Model>>
ResourceManager::getAllModelResources()
{
  return m_models;
}
Map<String, SPtr<Skeletal>>
ResourceManager::getAllSkeletalResources()
{
  return m_skeletals;
}
Map<String, SPtr<SkeletalMesh>>
ResourceManager::getAllSkeletalMeshResources()
{
  return m_skeletalMeshes;
}
Map<String, SPtr<Animation>>
ResourceManager::getAllAnimationResources()
{
  return m_animations;
}
Map<String, SPtr<VertexShader>>
ResourceManager::getAllVertexShaderResources()
{
  return m_vertexShaders;
}
Map<String, SPtr<PixelShader>>
ResourceManager::getAllPixelShaderResources()
{
  return m_pixelShaders;
}
}