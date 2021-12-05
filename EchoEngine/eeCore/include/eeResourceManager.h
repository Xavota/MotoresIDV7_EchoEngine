/************************************************************************/
/**
 * @file eeResourceManager.h
 * @author Diego Castellanos
 * @date 06/10/21
 * @brief
 * The resource manager. It should load every resource to have a reference to
 * it and avoid duplicated resources.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include "eeTexture.h"
#include "eeModel.h"
#include "eeMesh.h"
#include "eeVertexShader.h"
#include "eePixelShader.h"
#include <eeModule.h>

#include <eeMemoryManager.h>

namespace eeEngineSDK {
/**
 * @brief
 * The resource manager. It should load every resource to have a reference to
 * it and avoid duplicated resources.
 */
class EE_CORE_EXPORT ResourceManager : public Module<ResourceManager>
{
 public:
  ResourceManager() = default;
  ~ResourceManager() = default;

  /**
  * @brief
  * Initializes a texture.
  *
  * @description
  * Initializes a texture from a file and stores it with the given name.
  *
  * @param fileName
  * The name of the file containing the texture.
  * @param resourceName
  * The name that the resource will be stored with.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  SPtr<Texture>
  loadTextureFromFile(const String& fileName,
                      const String resourceName,
                      SamplerStateDesc desc);

  /**
  * @brief
  * Initializes the model.
  *
  * @description
  * Initializes the model from a file and stores it with the given name.
  *
  * @param fileName
  * The name of the file containing the model.
  * @param resourceName
  * The name that the resource will be stored with.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  SPtr<Model> 
  loadModelFromFile(const String& fileName,
                    const String resourceName);
  /**
  * @brief
  * Initializes the model.
  *
  * @description
  * Initializes the model from an array of meshes and stores it with the given
  * name.
  *
  * @param meshes
  * The array of meshes.
  * @param resourceName
  * The name that the resource will be stored with.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  SPtr<Model>
  loadModelFromMeshesArray(const Vector<SPtr<Mesh>>& meshes,
                           const String resourceName);
  /**
  * @brief
  * Initializes the model.
  *
  * @description
  * Initializes the model from an array of pairs of meshes and texture indices
  * and its respective textures and stores it with the given name.
  *
  * @param meshes
  * The array of pair of meshes and texture indices, indicating with texture it
  * will use.
  * @param textures
  * The array of textures for the model.
  * @param resourceName
  * The name that the resource will be stored with.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  SPtr<Model>
  loadModelFromMeshesArray(const Vector<Pair<SPtr<Mesh>, SPtr<Texture>>>& meshes,
                           const String resourceName);

  /**
  * @brief
  * Initializes the mesh.
  *
  * @description
  * Initializes the mesh from an array of vertex and index and stores it with
  * the given name.
  *
  * @param vertices
  * The vertex data.
  * @param indices
  * The index data.
  * @param resourceName
  * The name that the resource will be stored with.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  template<class V, class I>
  SPtr<Mesh>
  loadMeshFromVertexArray(const Vector<V>& vertices,
                          const Vector<I>& indices,
                          const String resourceName);

  /**
  * @brief
  * Initializes a skeletal mesh.
  *
  * @description
  * Initializes a skeletal mesh from a file and stores it with the given name.
  *
  * @param fileName
  * The name of the file containing the skeletal mesh.
  * @param resourceName
  * The name that the resource will be stored with.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  SPtr<SkeletalMesh> 
  loadSkeletalMeshFromFile(const String& fileName,
                           const String& resourceName);
  /**
  * @brief
  * Initializes a skeletal mesh.
  *
  * @description
  * Initializes a skeletal mesh from a file and stores it with the given name.
  *
  * @param fileName
  * The name of the file containing the skeletal mesh.
  * @param resourceName
  * The name that the resource will be stored with.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  SPtr<Animation> 
  loadAnimationFromFile(const String& fileName,
                        const String& resourceName);

  /**
  * @brief
  * Initializes the shader.
  *
  * @description
  * Initializes the shader from a file and stores it with the given name.
  *
  * @param fileName
  * The name of the file containing the shader.
  * @param resourceName
  * The name that the resource will be stored with.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  SPtr<VertexShader>
  loadVertexShaderFromFile(const String& fileName,
                           const String& resourceName);
  /**
  * @brief
  * Initializes the shader.
  *
  * @description
  * Initializes the shader from a string and stores it with the given name.
  *
  * @param fileName
  * The string for the shader to compile.
  * @param resourceName
  * The name that the resource will be stored with.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  SPtr<VertexShader>
  loadVertexShaderFromString(const String& shaderString,
                             const String& resourceName);

  /**
  * @brief
  * Initializes the shader.
  *
  * @description
  * Initializes the shader from a file and stores it with the given name.
  *
  * @param fileName
  * The name of the file containing the shader.
  * @param resourceName
  * The name that the resource will be stored with.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  SPtr<PixelShader>
  loadPixelShaderFromFile(const String& fileName,
                          const String& resourceName);
  /**
  * @brief
  * Initializes a shader.
  *
  * @description
  * Initializes a shader from a string and stores it with the given name.
  *
  * @param fileName
  * The string for the shader to compile.
  * @param resourceName
  * The name that the resource will be stored with.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  SPtr<PixelShader>
  loadPixelShaderFromString(const String& shaderString,
                            const String& resourceName);

  /**
  * @brief
  * Gets a texture.
  *
  * @description
  * Gets a texture by a resource name.
  *
  * @param resourceName
  * The name of the resource.
  *
  * @return
  * The texture with that name
  */
  SPtr<Texture>
  getResourceTexture(const String& resourceName);
  /**
  * @brief
  * Gets a model.
  *
  * @description
  * Gets a model by a resource name.
  *
  * @param resourceName
  * The name of the resource.
  *
  * @return
  * The model with that name
  */
  SPtr<Model>
  getResourceModel(const String& resourceName);
  /**
  * @brief
  * Gets a mesh.
  *
  * @description
  * Gets a mesh by a resource name.
  *
  * @param resourceName
  * The name of the resource.
  *
  * @return
  * The mesh with that name
  */
  SPtr<Mesh>
  getResourceMesh(const String& resourceName);
  /**
  * @brief
  * Gets a skeletal mesh.
  *
  * @description
  * Gets a skeletal mesh by a resource name.
  *
  * @param resourceName
  * The name of the resource.
  *
  * @return
  * The skeletal mesh with that name
  */
  SPtr<SkeletalMesh>
  getResourceSkeletalMesh(const String& resourceName);
  /**
  * @brief
  * Gets an animation.
  *
  * @description
  * Gets an animation by a resource name.
  *
  * @param resourceName
  * The name of the resource.
  *
  * @return
  * The animation with that name
  */
  SPtr<Animation>
  getResourceAnimation(const String& resourceName);
  /**
  * @brief
  * Gets a vertex shader.
  *
  * @description
  * Gets a vertex shader by a resource name.
  *
  * @param resourceName
  * The name of the resource.
  *
  * @return
  * The vertex shader with that name
  */
  SPtr<VertexShader>
  getResourceVertexShader(const String& resourceName);
  /**
  * @brief
  * Gets a pixel shader.
  *
  * @description
  * Gets a pixel shader by a resource name.
  *
  * @param resourceName
  * The name of the resource.
  *
  * @return
  * The pixel shader with that name
  */
  SPtr<PixelShader>
  getResourcePixelShader(const String& resourceName);



 private:
  /**
  * The textures stored.
  */
  Map<String, SPtr<Texture>> m_textures;
  /**
  * The meshes stored.
  */
  Map<String, SPtr<Mesh>> m_meshes;
  /**
  * The models stored.
  */
  Map<String, SPtr<Model>> m_models;
  /**
  * The skeletal meshes stored.
  */
  Map<String, SPtr<SkeletalMesh>> m_skeletalMeshes;
  /**
  * The animations stored.
  */
  Map<String, SPtr<Animation>> m_animations;
  /**
  * The vertex shaders stored.
  */
  Map<String, SPtr<VertexShader>> m_vertexShaders;
  /**
  * The pixel shaders stored.
  */
  Map<String, SPtr<PixelShader>> m_pixelShaders;
};
template<class V, class I>
SPtr<Mesh>
ResourceManager::loadMeshFromVertexArray(const Vector<V>& vertices,
                                         const Vector<I>& indices,
                                         const String resourceName)
{
  if (m_meshes.find(resourceName) != m_meshes.end())
  {
    eeOStream::print("Resource already with this name"); eeOStream::endl();
    return nullptr;
  }

  SPtr<Mesh> mesh = MemoryManager::instance().newPtr<Mesh>();
  if (!mesh->loadFromArray<V, I>(vertices, indices))
  {
    return nullptr;
  }

  m_meshes.insert(make_pair(resourceName, mesh));
  return m_meshes[resourceName];
}
}
