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
#include <eeModule.h>

#include <eeLogger.h>
#include <eeMemoryManager.h>

namespace eeEngineSDK {
/**
 * @brief
 * Flags for importing files, to tell what to try to import and what not.
 */
namespace IMPORT_FLAGS {
enum E : uint16
{
  kNone = 0u,
  kImportAll = 1u,
  kNotImportTextures = 2u,
  kNotImportStaticMeshes = 4u,
  kNotImportSkeletalMeshes = 8u,
  kNotImportAnimations = 16u,
  kNotImportShaders = 32u,
  kImportTextures = 64u,
  kImportStaticMeshes = 128u,
  kImportSkeletalMeshes = 256u,
  kImportAnimations = 512u,
  kImportShaders = 1024u,
};
}

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
  importResourceFromFile(const WString& fileName, uint16 importFlags = 0u);

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
  WPtr<Texture>
  loadTextureFromFile(const WString& fileName,
                      String& resourceName);
                      
  /**
   * @brief
   * Initializes a material.
   *
   * @description
   * Initializes a material from a file and stores it with the given name.
   *
   * @param textures
   * The textures map for the material.
   * @param resourceName
   * The name that the resource will be stored with.
   *
   * @return
   * The resource initialized.
   */
  WPtr<Material>
  loadMaterialFromTextures(const Map<uint32, WPtr<Texture>>& textures,
                           const String& resourceName);

  /**
   * @brief
   * Initializes the StaticMesh.
   *
   * @description
   * Initializes the StaticMesh from an array of meshes and stores it with the given
   * name.
   *
   * @param meshes
   * The array of meshes.
   * @param resourceName
   * The name that the resource will be stored with.
   * @param furtherDist
   * The distance to the vertex most far away from the origin.
   * @param maxCoordinate
   * The max coordinate of all vertex positions.
   * @param minCoordinate
   * The min coordinate of all vertex positions.
   *
   * @return
   * The resource initialized.
   */
  WPtr<StaticMesh>
  loadStaticMeshFromMeshesArray(const Vector<Mesh>& meshes,
                                const String& resourceName,
                                float furtherDist,
                                const Vector3f& maxCoordinate,
                                const Vector3f& minCoordinate);
  /**
   * @brief
   * Initializes the StaticMesh.
   *
   * @description
   * Initializes the StaticMesh from an array of pairs of meshes and texture indices
   * and its respective textures and stores it with the given name.
   *
   * @param meshes
   * The array of pair of meshes and textures.
   * @param resourceName
   * The name that the resource will be stored with.
   * @param furtherDist
   * The distance to the vertex most far away from the origin.
   * @param maxCoordinate
   * The max coordinate of all vertex positions.
   * @param minCoordinate
   * The min coordinate of all vertex positions.
   *
   * @return
   * The resource initialized.
   */
  WPtr<StaticMesh>
  loadStaticMeshFromMeshesArray(const Vector<Pair<Mesh, WPtr<Material>>>& meshes,
                                const String& resourceName,
                                float furtherDist,
                                const Vector3f& maxCoordinate,
                                const Vector3f& minCoordinate);

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
  WPtr<Skeletal> 
  loadSkeletalFromFile(const WString& fileName,
                       const String& resourceName);
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
  WPtr<Animation> 
  loadAnimationFromFile(const WString& fileName,
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
  WPtr<VertexShader>
  loadVertexShaderFromFile(const WString& fileName,
                           const String& functionName,
                           const Vector<ShaderMacro>& macroDefinitions,
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
  WPtr<VertexShader>
  loadVertexShaderFromString(const String& shaderString,
                             const String& functionName,
                             const Vector<ShaderMacro>& macroDefinitions,
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
  WPtr<PixelShader>
  loadPixelShaderFromFile(const WString& fileName,
                          const String& functionName,
                          const Vector<ShaderMacro>& macroDefinitions,
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
  WPtr<PixelShader>
  loadPixelShaderFromString(const String& shaderString,
                            const String& functionName,
                            const Vector<ShaderMacro>& macroDefinitions,
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
   * @param functionName
   * The name of the function it will compile for this shader.
   * @param macroDefinitions
   * The macros to compile the shader with.
   * @param resourceName
   * The name that the resource will be stored with.
   *
   * @return
   * The resource initialized.
   */
  WPtr<HullShader>
  loadHullShaderFromFile(const WString& fileName,
                         const String& functionName,
                         const Vector<ShaderMacro>& macroDefinitions,
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
   * @param functionName
   * The name of the function it will compile for this shader.
   * @param macroDefinitions
   * The macros to compile the shader with.
   * @param resourceName
   * The name that the resource will be stored with.
   *
   * @return
   * The resource initialized.
   */
  WPtr<HullShader>
  loadHullShaderFromString(const String& shaderString,
                           const String& functionName,
                           const Vector<ShaderMacro>& macroDefinitions,
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
   * @param functionName
   * The name of the function it will compile for this shader.
   * @param macroDefinitions
   * The macros to compile the shader with.
   * @param resourceName
   * The name that the resource will be stored with.
   *
   * @return
   * The resource initialized.
   */
  WPtr<DomainShader>
  loadDomainShaderFromFile(const WString& fileName,
                           const String& functionName,
                           const Vector<ShaderMacro>& macroDefinitions,
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
   * @param functionName
   * The name of the function it will compile for this shader.
   * @param macroDefinitions
   * The macros to compile the shader with.
   * @param resourceName
   * The name that the resource will be stored with.
   *
   * @return
   * The resource initialized.
   */
  WPtr<DomainShader>
  loadDomainShaderFromString(const String& shaderString,
                             const String& functionName,
                             const Vector<ShaderMacro>& macroDefinitions,
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
  WPtr<Texture>
  getResourceTexture(const String& resourceName);
  /**
   * @brief
   * Gets a material.
   *
   * @description
   * Gets a material by a resource name.
   *
   * @param resourceName
   * The name of the resource.
   *
   * @return
   * The material with that name.
   */
  WPtr<Material>
  getResourceMaterial(const String& resourceName);
  /**
   * @brief
   * Gets a StaticMesh.
   *
   * @description
   * Gets a StaticMesh by a resource name.
   *
   * @param resourceName
   * The name of the resource.
   *
   * @return
   * The StaticMesh with that name.
   */
  /*template<typename V, typename I>*/
  WPtr<StaticMesh/*<V, I>*/>
  getResourceStaticMesh(const String& resourceName);
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
  WPtr<Skeletal>
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
  /*template<typename V, typename I>*/
  WPtr<SkeletalMesh/*<V, I>*/>
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
  WPtr<Animation>
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
  WPtr<VertexShader>
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
  WPtr<PixelShader>
  getResourcePixelShader(const String& resourceName);
  /**
   * @brief
   * Gets a hull shader.
   *
   * @description
   * Gets a hull shader by a resource name.
   *
   * @param resourceName
   * The name of the resource.
   *
   * @return
   * The hull shader with that name.
   */
  WPtr<HullShader>
  getResourceHullShader(const String& resourceName);
  /**
   * @brief
   * Gets a domain shader.
   *
   * @description
   * Gets a domain shader by a resource name.
   *
   * @param resourceName
   * The name of the resource.
   *
   * @return
   * The domain shader with that name.
   */
  WPtr<DomainShader>
  getResourceDomainShader(const String& resourceName);

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
   * Gets all materials.
   *
   * @description
   * Gets all stored materials.
   *
   * @return
   * All stored materials.
   */
  Map<String, SPtr<Material>>
  getAllMaterialResources();
  /**
   * @brief
   * Gets all StaticMeshes.
   *
   * @description
   * Gets all stored StaticMeshes.
   *
   * @return
   * All stored StaticMeshes.
   */
  /*template<typename V, typename I>*/
  Map<String, SPtr<StaticMesh/*<V, I>*/>>
  getAllStaticMeshResources();
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
  /*template<typename V, typename I>*/
  Map<String, SPtr<SkeletalMesh/*<V, I>*/>>
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
  /**
   * @brief
   * Gets all hull shaders.
   *
   * @description
   * Gets all stored hull shaders.
   *
   * @return
   * All stored hull shaders.
   */
  Map<String, SPtr<HullShader>>
  getAllHullShaderResources();
  /**
   * @brief
   * Gets all domain shaders.
   *
   * @description
   * Gets all stored domain shaders.
   *
   * @return
   * All stored domain shaders.
   */
  Map<String, SPtr<DomainShader>>
  getAllDomainShaderResources();


  /**
   * @brief
   * Deserialize and store all the resources files.
   *
   * @description
   * Deserialize and store all the resources files in the directory.
   */
  void
  loadAllSerialized();
  /**
   * @brief
   * Serialize and stores a texture resource.
   *
   * @description
   * Serialize and stores a texture resource.
   * 
   * @param resourceName
   * The name of the resources to serialize.
   * @param fileToSave
   * The path to the file for the serialized resource.
   *
   * @return
   * Whether or not it succeeded on serializing the texture.
   */
  bool
  serializeTexture(const String& resourceName, const WString& fileToSave);
  /**
   * @brief
   * Serialize and stores a material resource.
   *
   * @description
   * Serialize and stores a material resource.
   * 
   * @param resourceName
   * The name of the resources to serialize.
   * @param fileToSave
   * The path to the file for the serialized resource.
   *
   * @return
   * Whether or not it succeeded on serializing the material.
   */
  bool
  serializeMaterial(const String& resourceName, const WString& fileToSave);
  /**
   * @brief
   * Serialize and stores a static mesh resource.
   *
   * @description
   * Serialize and stores a static mesh resource.
   * 
   * @param resourceName
   * The name of the resources to serialize.
   * @param fileToSave
   * The path to the file for the serialized resource.
   *
   * @return
   * Whether or not it succeeded on serializing the static mesh.
   */
  bool
  serializeStaticMesh(const String& resourceName, const WString& fileToSave);
  /**
   * @brief
   * Serialize and stores a skeleton resource.
   *
   * @description
   * Serialize and stores a skeleton resource.
   * 
   * @param resourceName
   * The name of the resources to serialize.
   * @param fileToSave
   * The path to the file for the serialized resource.
   *
   * @return
   * Whether or not it succeeded on serializing the skeleton.
   */
  bool
  serializeSkeleton(const String& resourceName, const WString& fileToSave);
  /**
   * @brief
   * Serialize and stores a skeletal mesh resource.
   *
   * @description
   * Serialize and stores a skeletal mesh resource.
   * 
   * @param resourceName
   * The name of the resources to serialize.
   * @param fileToSave
   * The path to the file for the serialized resource.
   *
   * @return
   * Whether or not it succeeded on serializing the skeletal mesh.
   */
  bool
  serializeSkeletalMesh(const String& resourceName, const WString& fileToSave);
  /**
   * @brief
   * Serialize and stores a animation resource.
   *
   * @description
   * Serialize and stores a animation resource.
   * 
   * @param resourceName
   * The name of the resources to serialize.
   * @param fileToSave
   * The path to the file for the serialized resource.
   *
   * @return
   * Whether or not it succeeded on serializing the animation.
   */
  bool
  serializeAnimation(const String& resourceName, const WString& fileToSave);

  /**
   * @brief
   * Loads and stores a serialized texture resource.
   *
   * @description
   * Loads and stores a serialized texture resource.
   *
   * @param fileToLoad
   * The opened file that contains the resource to load.
   * @param resourceName
   * The name of the resources to load.
   * @param versionNum
   * The number of the version of the archive.
   * @param sizeTSize
   * The size of the SIZE_T when the resource was saved.
   *
   * @return
   * Whether or not it succeeded on loading the texture.
   */
  bool
  loadSerializedTexture(File& fileToLoad,
                        const String& resourceName,
                        uint8 versionNum,
                        uint8 sizeTSize);
  /**
   * @brief
   * Loads and stores a serialized material resource.
   *
   * @description
   * Loads and stores a serialized material resource.
   *
   * @param fileToLoad
   * The opened file that contains the resource to load.
   * @param resourceName
   * The name of the resources to load.
   * @param versionNum
   * The number of the version of the archive.
   * @param sizeTSize
   * The size of the SIZE_T when the resource was saved.
   *
   * @return
   * Whether or not it succeeded on loading the material.
   */
  bool
  loadSerializedMaterial(File& fileToLoad,
                         const String& resourceName,
                         uint8 versionNum,
                         uint8 sizeTSize);
  /**
   * @brief
   * Loads and stores a serialized static mesh resource.
   *
   * @description
   * Loads and stores a serialized static mesh resource.
   *
   * @param fileToLoad
   * The opened file that contains the resource to load.
   * @param resourceName
   * The name of the resources to load.
   * @param versionNum
   * The number of the version of the archive.
   * @param sizeTSize
   * The size of the SIZE_T when the resource was saved.
   *
   * @return
   * Whether or not it succeeded on loading the static mesh.
   */
  bool
  loadSerializedStaticMesh(File& fileToLoad,
                           const String& resourceName,
                           uint8 versionNum,
                           uint8 sizeTSize);
  /**
   * @brief
   * Loads and stores a serialized skeletons resource.
   *
   * @description
   * Loads and stores a serialized skeletons resource.
   *
   * @param fileToLoad
   * The opened file that contains the resource to load.
   * @param resourceName
   * The name of the resources to load.
   * @param versionNum
   * The number of the version of the archive.
   * @param sizeTSize
   * The size of the SIZE_T when the resource was saved.
   *
   * @return
   * Whether or not it succeeded on loading the skeletons.
   */
  bool
  loadSerializedSkeleton(File& fileToLoad,
                         const String& resourceName,
                         uint8 versionNum,
                         uint8 sizeTSize);
  /**
   * @brief
   * Loads and stores a serialized skeletal mesh resource.
   *
   * @description
   * Loads and stores a serialized skeletal mesh resource.
   *
   * @param fileToLoad
   * The opened file that contains the resource to load.
   * @param resourceName
   * The name of the resources to load.
   * @param versionNum
   * The number of the version of the archive.
   * @param sizeTSize
   * The size of the SIZE_T when the resource was saved.
   *
   * @return
   * Whether or not it succeeded on loading the skeletal mesh.
   */
  bool
  loadSerializedSkeletalMesh(File& fileToLoad,
                             const String& resourceName,
                             uint8 versionNum,
                             uint8 sizeTSize);
  /**
   * @brief
   * Loads and stores a serialized animation resource.
   *
   * @description
   * Loads and stores a serialized animation resource.
   *
   * @param fileToLoad
   * The opened file that contains the resource to load.
   * @param resourceName
   * The name of the resources to load.
   * @param versionNum
   * The number of the version of the archive.
   * @param sizeTSize
   * The size of the SIZE_T when the resource was saved.
   *
   * @return
   * Whether or not it succeeded on loading the animation.
   */
  bool
  loadSerializedAnimation(File& fileToLoad,
                          const String& resourceName,
                          uint8 versionNum,
                          uint8 sizeTSize);


 private:
  /**
   * The textures stored.
   */
  Map<String, SPtr<Texture>> m_textures;
  /**
   * The materials stored.
   */
  Map<String, SPtr<Material>> m_materials;
  /**
   * The StaticMeshes stored.
   */
  Map<String, SPtr<StaticMesh>> m_staticMeshes;
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
  /**
   * The hull shaders stored.
   */
  Map<String, SPtr<HullShader>> m_hullShaders;
  /**
   * The hull shaders stored.
   */
  Map<String, SPtr<DomainShader>> m_domainShaders;
};
}
