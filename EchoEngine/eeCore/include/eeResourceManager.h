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

#include <eeLogger.h>

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
  /**
   * @brief
   * Default constructor.
   */
  ResourceManager() = default;
  /**
   * @brief
   * Default destructor.
   */
  ~ResourceManager() = default;

  /**
   * @brief
   * Imports a resource from a file.
   *
   * @description
   * Identifies the resource type and loads the correct resources.
   *
   * @param fileName
   * The name of the file containing the resources.
   *
   * @return
   * Weather it succeed or failed to import.
   */
  bool
  importResourceFromFile(const String& fileName);

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
   * The resource initialized.
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
   * The resource initialized.
   */
  SPtr<Model> 
  loadModelFromFile(const String& fileName,
                    const String resourceName,
                    const Vector<SPtr<Texture>>& textures = {});
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
   * The resource initialized.
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
   * The resource initialized.
   */
  SPtr<Model>
  loadModelFromMeshesArray(const Vector<Pair<SPtr<Mesh>, SPtr<Texture>>>& meshes,
                           const String resourceName);

  /**
   * @brief
   * Initializes a skeletal.
   *
   * @description
   * Initializes a skeletal from a file and stores it with the given name.
   *
   * @param fileName
   * The name of the file containing the skeletal.
   * @param resourceName
   * The name that the resource will be stored with.
   *
   * @return
   * The resource initialized.
   */
  SPtr<Skeletal> 
  loadSkeletalFromFile(const String& fileName,
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
   * The resource initialized.
   */
  SPtr<SkeletalMesh> 
  loadSkeletalMeshFromFile(const String& fileName,
                           const String& resourceName,
                           const SPtr<Skeletal> skMesh,
                           const Vector<SPtr<Texture>>& textures = {});
  /**
   * @brief
   * Initializes an animation.
   *
   * @description
   * Initializes an animation from a file and stores it with the given name.
   *
   * @param fileName
   * The name of the file containing the animation.
   * @param resourceName
   * The name that the resource will be stored with.
   *
   * @return
   * The resource initialized.
   */
  SPtr<Animation> 
  loadAnimationFromFile(const String& fileName,
                        const String& resourceName,
                        const int32 animIndex = 0);

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
   * The resource initialized.
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
   * The resource initialized.
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
   * The resource initialized.
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
   * The resource initialized.
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
   * The texture with that name.
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
   * The model with that name.
   */
  SPtr<Model>
  getResourceModel(const String& resourceName);
  /**
   * @brief
   * Gets a skeletal.
   *
   * @description
   * Gets a skeletal by a resource name.
   *
   * @param resourceName
   * The name of the resource.
   *
   * @return
   * The skeletal with that name.
   */
  SPtr<Skeletal>
  getResourceSkeletal(const String& resourceName);
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
   * The skeletal mesh with that name.
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
   * The animation with that name.
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
   * The vertex shader with that name.
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
   * The pixel shader with that name.
   */
  SPtr<PixelShader>
  getResourcePixelShader(const String& resourceName);

  /**
   * @brief
   * Gets all textures.
   *
   * @description
   * Gets all stored textures.
   *
   * @return
   * All stored textures.
   */
  Map<String, SPtr<Texture>>
  getAllTextureResources();
  /**
   * @brief
   * Gets all models.
   *
   * @description
   * Gets all stored models.
   *
   * @return
   * All stored models.
   */
  Map<String, SPtr<Model>>
  getAllModelResources();
  /**
   * @brief
   * Gets all skeletons.
   *
   * @description
   * Gets all stored skeletons.
   *
   * @return
   * All stored skeletons.
   */
  Map<String, SPtr<Skeletal>>
  getAllSkeletalResources();
  /**
   * @brief
   * Gets all skeletal meshes.
   *
   * @description
   * Gets all stored skeletal meshes.
   *
   * @return
   * All stored skeletal meshes.
   */
  Map<String, SPtr<SkeletalMesh>>
  getAllSkeletalMeshResources();
  /**
   * @brief
   * Gets all animations.
   *
   * @description
   * Gets all stored animations.
   *
   * @return
   * All stored animations.
   */
  Map<String, SPtr<Animation>>
  getAllAnimationResources();
  /**
   * @brief
   * Gets all vertex shaders.
   *
   * @description
   * Gets all stored vertex shaders.
   *
   * @return
   * All stored vertex shaders.
   */
  Map<String, SPtr<VertexShader>>
  getAllVertexShaderResources();
  /**
   * @brief
   * Gets all pixel shaders.
   *
   * @description
   * Gets all stored pixel shaders.
   *
   * @return
   * All stored pixel shaders.
   */
  Map<String, SPtr<PixelShader>>
  getAllPixelShaderResources();



 private:
  /**
   * The textures stored.
   */
  Map<String, SPtr<Texture>> m_textures;
  /**
   * The models stored.
   */
  Map<String, SPtr<Model>> m_models;
  /**
   * The skeletal meshes stored.
   */
  Map<String, SPtr<Skeletal>> m_skeletals;
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
}
