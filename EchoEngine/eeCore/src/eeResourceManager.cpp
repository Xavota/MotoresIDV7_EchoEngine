#include "eeResourceManager.h"

#pragma warning(push, 0)   
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)
#include <eeLogger.h>
#include <eeMemoryManager.h>
#include <eeMath.h>

#include <eeFile.h>
#include <eeVertex.h>

#include "eeGraficsApi.h"

#include "eeMesh.h"
#include "eeTexture.h"
#include "eeMaterial.h"
#include "eeVertexShader.h"
#include "eePixelShader.h"
#include "eeHullShader.h"
#include "eeDomainShader.h"
#include "eeStaticMesh.h"
#include "eeSkeletalMesh.h"
#include "eeSkeletal.h"
#include "eeAnimation.h"
#include "eeImage.h"


namespace eeEngineSDK
{
Map<uint32, WPtr<Material>>
loadMaterialsFromAssimp(const aiScene* scene,
                        const String& /*name*/)
{
  for (uint32 i = 0; i < scene->mNumMaterials; ++i) {
    scene->mMaterials;
  }
  return {};
}

void
loadStaticMeshFromAssimp(const aiScene* scene,
                         const String& name,
                         const Map<uint32, WPtr<Material>>& textures,
                         SPtr<StaticMesh>* outStaticMesh)
{
  *outStaticMesh = MemoryManager::instance().newPtr<StaticMesh>();

  Vector<Pair<Mesh, WPtr<Material>>> meshes;
  meshes.resize(scene->mNumMeshes);

  Vector3f maxBound(-99999.99f, -99999.99f, -99999.99f);
  Vector3f minBound( 99999.99f,  99999.99f,  99999.99f);
  Vector3f furtherPosition(0.0f, 0.0f, 0.0f);
      //----Vertices----
  for (uint32 i = 0; i < scene->mNumMeshes; ++i) {
    Vector<ComplexVertex> vertices;
    aiMesh* AssimpMesh = scene->mMeshes[i];

    for (uint32 j = 0; j < AssimpMesh->mNumVertices; ++j) {
      ComplexVertex v;
      //---Pos
      if (AssimpMesh->HasPositions()) {
        const aiVector3D& vertex = AssimpMesh->mVertices[j];
        v.position.x = vertex.x;
        maxBound.x = v.position.x > maxBound.x ? v.position.x : maxBound.x;
        minBound.x = v.position.x < minBound.x ? v.position.x : minBound.x;
        v.position.y = vertex.y;
        maxBound.y = v.position.y > maxBound.y ? v.position.y : maxBound.y;
        minBound.y = v.position.y < minBound.y ? v.position.y : minBound.y;
        v.position.z = vertex.z;
        maxBound.z = v.position.z > maxBound.z ? v.position.z : maxBound.z;
        minBound.z = v.position.z < minBound.z ? v.position.z : minBound.z;
        v.position.w = 1.0f;

        float distance = Math::pow(Math::pow(v.position.x, 2.0f)
                                 + Math::pow(v.position.y, 2.0f)
                                 + Math::pow(v.position.z, 2.0f), 0.5f);

        if (distance > furtherPosition.getMagnitud())
        {
          furtherPosition = Vector3f(v.position.x, v.position.y, v.position.z);
        }
      }
      else {
        v.position = Vector4f{};
      }

      //---UVs
      //for (int32 k = 0; k < scene->mMeshes[i]->mMaterialIndex; ++k)
    //	{
      if (AssimpMesh->HasTextureCoords(0)) {
        const aiVector3D& uv = AssimpMesh->mTextureCoords[0][j];
        v.uvCoord.x = uv.x;
        v.uvCoord.y = uv.y;
        v.uvCoord.z = 0.0f;
        v.uvCoord.w = 0.0f;
      }
      //}

      //---Norms
      if (AssimpMesh->HasNormals()) {
        const aiVector3D& norm = AssimpMesh->mNormals[j];
        v.normal.x = norm.x;
        v.normal.y = norm.y;
        v.normal.z = norm.z;
        v.normal.w = 0.0f;
      }
      else {
        v.normal = Vector4f{};
      }

      //---Tan
      if (AssimpMesh->HasTangentsAndBitangents()) {
        const aiVector3D& tan = AssimpMesh->mTangents[j];
        v.tangent.x = tan.x;
        v.tangent.y = tan.y;
        v.tangent.z = tan.z;
        v.tangent.w = 0.0f;
      }

      //---Bit
      if (AssimpMesh->HasTangentsAndBitangents()) {
        const aiVector3D& bit = AssimpMesh->mBitangents[j];
        v.binormal.x = bit.x;
        v.binormal.y = bit.y;
        v.binormal.z = bit.z;
        v.binormal.w = 0.0f;
      }

      vertices.push_back(v);
    }


    Vector<uint32> indices;

    for (uint32 j = 0; j < AssimpMesh->mNumFaces; ++j) {
      for (uint32 k = 0; k < AssimpMesh->mFaces[j].mNumIndices; ++k) {
        indices.push_back(AssimpMesh->mFaces[j].mIndices[k]);
      }
    }

    auto& resourseManager = ResourceManager::instance();

    meshes[i] = Pair<Mesh, WPtr<Material>>(
      Mesh(),
      textures.find(AssimpMesh->mMaterialIndex) != textures.end()
      ? (*textures.find(AssimpMesh->mMaterialIndex)).second
      : resourseManager.getResourceMaterial("Default_mat"));
    meshes[i].first.loadFromVertexArray(vertices, indices);

    indices.clear();
    vertices.clear();
  }

  (*outStaticMesh)->loadFromMeshes(meshes, name, furtherPosition, maxBound, minBound);
}
SPtr<SkeletalMesh>
loadSkeletalMeshFromAssimp(const aiScene* scene,
                           WPtr<Skeletal> skeleton,
                           const String& name,
                           const Map<uint32, WPtr<Material>>& textures)
{
  SPtr<SkeletalMesh> outSkeletalMesh = MemoryManager::instance().newPtr<SkeletalMesh>();

  Vector<Pair<BoneMesh, WPtr<Material>>> meshes;

  Vector3f maxBound(-99999.99f, -99999.99f, -99999.99f);
  Vector3f minBound(99999.99f, 99999.99f, 99999.99f);
  Vector3f furtherPosition = Vector3f(0.0f, 0.0f, 0.0f);
  for (uint32 i = 0; i < scene->mNumMeshes; ++i) {
    Vector<ComplexBigAnimVertex<5>> vertices;
    aiMesh* AssimpMesh = scene->mMeshes[i];

    for (uint32 j = 0; j < AssimpMesh->mNumVertices; ++j) {
      ComplexBigAnimVertex<5> v;
      memset(&v, 0, sizeof(ComplexBigAnimVertex<5>));
      // Positions
      if (AssimpMesh->HasPositions()) {
        const aiVector3D& vertex = AssimpMesh->mVertices[j];
        v.position.x = vertex.x;
        maxBound.x = v.position.x > maxBound.x ? v.position.x : maxBound.x;
        minBound.x = v.position.x < minBound.x ? v.position.x : minBound.x;
        v.position.y = vertex.y;
        maxBound.y = v.position.y > maxBound.y ? v.position.y : maxBound.y;
        minBound.y = v.position.y < minBound.y ? v.position.y : minBound.y;
        v.position.z = vertex.z;
        maxBound.z = v.position.z > maxBound.z ? v.position.z : maxBound.z;
        minBound.z = v.position.z < minBound.z ? v.position.z : minBound.z;
        v.position.w = 1.0f;

        float distance = Math::pow(Math::pow(v.position.x, 2.0f)
                                 + Math::pow(v.position.y, 2.0f)
                                 + Math::pow(v.position.z, 2.0f), 0.5f);

        if (distance > furtherPosition.getMagnitud())
        {
          furtherPosition = Vector3f(v.position.x, v.position.y, v.position.z);
        }
      }
      else {
        v.position = Vector4f{};
      }

      // UVs
      //for (int32 k = 0; k < scene->mMeshes[i]->mMaterialIndex; ++k)
    //	{
      if (AssimpMesh->HasTextureCoords(0)) {
        const aiVector3D& uv = AssimpMesh->mTextureCoords[0][j];
        v.uvCoord.x = uv.x;
        v.uvCoord.y = uv.y;
        v.uvCoord.z = 0.0f;
        v.uvCoord.w = 0.0f;
      }
      //}

      // Normals
      if (AssimpMesh->HasNormals()) {
        const aiVector3D& norm = AssimpMesh->mNormals[j];
        v.normal.x = norm.x;
        v.normal.y = norm.y;
        v.normal.z = norm.z;
        v.normal.w = 0.0f;
      }
      else {
        v.normal = Vector4f{};
      }

      //---Tan
      if (AssimpMesh->HasTangentsAndBitangents()) {
        const aiVector3D& tan = AssimpMesh->mTangents[j];
        v.tangent.x = tan.x;
        v.tangent.y = tan.y;
        v.tangent.z = tan.z;
        v.tangent.w = 0.0f;
      }

      //---Bit
      if (AssimpMesh->HasTangentsAndBitangents()) {
        const aiVector3D& bit = AssimpMesh->mBitangents[j];
        v.binormal.x = bit.x;
        v.binormal.y = bit.y;
        v.binormal.z = bit.z;
        v.binormal.w = 0.0f;
      }

      vertices.push_back(v);
    }

    Vector<Bone> bones;
    if (!skeleton.expired() && skeleton.lock()->getBonesDataForMesh(i, bones)) {
      if (!bones.empty()) {
        SIZE_T bonesCount = bones.size();
        for (SIZE_T j = 0; j < bonesCount; j++) {
          Bone bone = bones[j];
          bool yes = false;
          for (auto vw : bone.m_vertexWeights) {
            yes = false;
            for (uint32 l = 0; l < 16; l++) {
              if (vertices[vw.m_vertexID].boneWeights[l] == 0.0f) {
                vertices[vw.m_vertexID].boneIndices[l] = static_cast<int32>(j);
                vertices[vw.m_vertexID].boneWeights[l] = vw.m_weight;
                yes = true;
                break;
              }
            }

            if (!yes) {
              Logger::instance().consoleLog("No more bone space");
            }
          }
        }
      }
      else {
        for (auto& v : vertices) {
          v.boneIndices[0] = -1;
        }
      }
    }


    Vector<uint32> indices;
    for (uint32 j = 0; j < AssimpMesh->mNumFaces; ++j) {
      for (uint32 k = 0; k < AssimpMesh->mFaces[j].mNumIndices; ++k) {
        indices.push_back(AssimpMesh->mFaces[j].mIndices[k]);
      }
    }

    auto& resourseManager = ResourceManager::instance();


    meshes.emplace_back
    (
      Pair<BoneMesh, WPtr<Material>>
      (
        BoneMesh(),
        textures.find(AssimpMesh->mMaterialIndex) != textures.end()
        ? (*textures.find(AssimpMesh->mMaterialIndex)).second
        : resourseManager.getResourceMaterial("Default_mat")
      )
    );
    meshes[meshes.size() - 1].first.loadFromArray(vertices, indices);

    vertices.clear();
    indices.clear();
  }

  outSkeletalMesh->loadFromMeshes(meshes,
                                  skeleton,
                                  name,
                                  furtherPosition,
                                  maxBound,
                                  minBound);
  return outSkeletalMesh;
}
void
readNodeHeirarchy(const aiNode* pNode,
                  const Matrix4f& ParentTransform,
                  int32 meshIndex,
                  const Vector<Map<String, uint32>>& boneMappings,
                  const Vector<Matrix4f>& globalInverseTransforms,
                  Vector<Vector<Bone>>& outBonesPerMesh)
{
  String NodeName(pNode->mName.data);

  //trans
  float m[16];
  memcpy(m, &pNode->mTransformation.a1, 16 * sizeof(float));
  Matrix4f NodeTransformation = Matrix4f(m);

  Matrix4f GlobalTransformation = ParentTransform * NodeTransformation;


  if (boneMappings[meshIndex].find(NodeName) != boneMappings[meshIndex].end()) {
    uint32 BoneIndex = boneMappings[meshIndex].find(NodeName)->second;

    outBonesPerMesh[meshIndex][BoneIndex].m_finalTransformation =
                          globalInverseTransforms[meshIndex]
                        * GlobalTransformation
                        * outBonesPerMesh[meshIndex][BoneIndex].m_offsetMatrix;
  }

  for (uint32 i = 0; i < pNode->mNumChildren; i++) {
    readNodeHeirarchy(pNode->mChildren[i],
                      GlobalTransformation,
                      meshIndex,
                      boneMappings,
                      globalInverseTransforms,
                      outBonesPerMesh);
  }
}
void
boneTransform(const aiNode* root,
              int32 meshIndex,
              const Vector<Map<String, uint32>>& boneMappings,
              const Vector<Matrix4f>& globalInverseTransforms,
              Vector<Vector<Bone>>& outBonesPerMesh)
{
  readNodeHeirarchy(root,
                    Matrix4f::kIDENTITY,
                    meshIndex,
                    boneMappings,
                    globalInverseTransforms,
                    outBonesPerMesh);
}
SPtr<Skeletal>
loadSkeletalFromAssimp(const aiScene* scene,
                       const String& name)
{
  SPtr<Skeletal> outSkeleton = MemoryManager::instance().newPtr<Skeletal>();

  Vector<Vector<Bone>> bonesPerMesh;
  Vector<Matrix4f> globalInverseTransforms;
  Vector<Map<String, uint32>> boneMappings;
  Vector<uint32> numsBones;

  for (uint32 i = 0; i < scene->mNumMeshes; i++) {
    bonesPerMesh.emplace_back(Vector<Bone>(100));
    boneMappings.emplace_back(Map<String, uint32>());
    numsBones.push_back(0);

    aiMatrix4x4 globalTransform = scene->mRootNode->mTransformation;
    globalTransform.Inverse();
    globalInverseTransforms.emplace_back(Matrix4f(&globalTransform.a1));

    if (scene->mMeshes[i]->HasBones()) {
      for (uint32 j = 0; j < scene->mMeshes[i]->mNumBones; j++) {
        uint32 boneIndex = 0;
        String boneName = scene->mMeshes[i]->mBones[j]->mName.C_Str();

        if (boneMappings[i].find(boneName) == boneMappings[i].end()) {
          boneIndex = numsBones[i];
          numsBones[i]++;
        }
        else {
          boneIndex = boneMappings[i][boneName];
        }

        if (boneIndex >= bonesPerMesh[i].size()) {
          continue;
        }

        boneMappings[i][boneName] = boneIndex;

        bonesPerMesh[i][boneIndex].m_name = boneName;
        float m[16];
        memcpy(m,
               &scene->mMeshes[i]->mBones[boneIndex]->mOffsetMatrix.a1,
               sizeof(float) * 16);
        bonesPerMesh[i][boneIndex].m_offsetMatrix = Matrix4f(m);
        bonesPerMesh[i][boneIndex].m_finalTransformation =
                                    bonesPerMesh[i][boneIndex].m_offsetMatrix;
        for (uint32 k = 0; k < scene->mMeshes[i]->mBones[j]->mNumWeights; k++) {
          uint32 vertexID = scene->mMeshes[i]->mBones[j]->mWeights[k].mVertexId;
          float weight = scene->mMeshes[i]->mBones[j]->mWeights[k].mWeight;

          bonesPerMesh[i][boneIndex].addBoneData({ vertexID, weight });
        }
      }
    }
  }

  for (uint32 i = 0; i < scene->mNumMeshes; i++) {
    boneTransform(scene->mRootNode,
                  i,
                  boneMappings,
                  globalInverseTransforms,
                  bonesPerMesh);
  }

  outSkeleton->loadFromData(bonesPerMesh,
                            globalInverseTransforms,
                            boneMappings,
                            numsBones,
                            name);

  return outSkeleton;
}
void
storeAnim(aiAnimation* anim, Vector<AnimNode>& channels)
{
  SIZE_T channelsCount = anim->mNumChannels;
  for (uint32 i = 0; i < channelsCount; ++i) {
    channels.emplace_back(AnimNode());
    AnimNode& an = channels[i];
    const aiNodeAnim* aina = anim->mChannels[i];

    an.m_name = aina->mNodeName.C_Str();
    an.m_positionKeysCount = aina->mNumPositionKeys;
    an.m_rotationKeysCount = aina->mNumRotationKeys;
    an.m_scalingKeysCount = aina->mNumScalingKeys;

    for (uint32 j = 0; j < an.m_positionKeysCount; ++j) {
      an.m_positionKeys.emplace_back(VectorKeyFrame());
      VectorKeyFrame& vkf = an.m_positionKeys[j];
      const aiVectorKey& aiVkf = aina->mPositionKeys[j];

      vkf.m_time = static_cast<float>(aiVkf.mTime);
      vkf.m_value.x = aiVkf.mValue.x;
      vkf.m_value.y = aiVkf.mValue.y;
      vkf.m_value.z = aiVkf.mValue.z;
    }

    for (uint32 j = 0; j < an.m_rotationKeysCount; ++j) {
      an.m_rotationKeys.emplace_back(QuatKeyFrame());
      QuatKeyFrame& qkf = an.m_rotationKeys[j];
      const aiQuatKey& aiQkf = aina->mRotationKeys[j];

      qkf.m_time = static_cast<float>(aiQkf.mTime);
      qkf.m_value.w = aiQkf.mValue.w;
      qkf.m_value.x = aiQkf.mValue.x;
      qkf.m_value.y = aiQkf.mValue.y;
      qkf.m_value.z = aiQkf.mValue.z;
    }

    for (uint32 j = 0; j < an.m_scalingKeysCount; ++j) {
      an.m_scalingKeys.emplace_back(VectorKeyFrame());
      VectorKeyFrame& vkf = an.m_scalingKeys[j];
      const aiVectorKey& aiVkf = aina->mScalingKeys[j];

      vkf.m_time = static_cast<float>(aiVkf.mTime);
      vkf.m_value.x = aiVkf.mValue.x;
      vkf.m_value.y = aiVkf.mValue.y;
      vkf.m_value.z = aiVkf.mValue.z;
    }
  }
}
void
storeNodes(aiNode* current, WPtr<Node> storage)
{
  auto& memoryMan = MemoryManager::instance();

  auto sstorage = storage.lock();
  sstorage->m_name = current->mName.C_Str();
  float m[16];
  memcpy(m, &current->mTransformation.a1, 16 * sizeof(float));
  sstorage->m_transformation = Matrix4f(m);

  sstorage->m_childrenCount = current->mNumChildren;

  for (uint32 i = 0; i < sstorage->m_childrenCount; ++i) {
    sstorage->m_pChildren.push_back(memoryMan.newPtr<Node>());
    storeNodes(current->mChildren[i], sstorage->m_pChildren[i]);
    sstorage->m_pChildren[i]->m_pParent = sstorage;
  }
}
SPtr<Animation>
loadOneAnimationFromAssimp(const aiScene* scene,
                           int32 animIndex,
                           const String& name)
{
  SPtr<Animation> outAnimation = MemoryManager::instance().newPtr<Animation>();

  aiAnimation* anim = scene->mAnimations[animIndex];

  float ticksPerSecond = anim->mTicksPerSecond != 0.0
                         ? static_cast<float>(anim->mTicksPerSecond)
                         : 24.0f;
  float duration = static_cast<float>(anim->mDuration);
  Vector<AnimNode> channels;
  SPtr<Node> rootNode = MemoryManager::instance().newPtr<Node>();

  storeNodes(scene->mRootNode, rootNode);
  storeAnim(scene->mAnimations[animIndex], channels);

  outAnimation->loadFromData(ticksPerSecond, duration, channels, rootNode, name);

  return outAnimation;
}

bool
ResourceManager::importResourceFromFile(const WString& fileName,
                                        uint16 importFlags)
{
  /*  GET NAME AND FILE EXTENSION */
  WString name;
  WString fileExtension;
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

  // To lower the file extension
  for (wchar_t& c : fileExtension) {
    c = (c >= 'A' && c <= 'Z' ? c + 32 : c);
  }

  /* LOAD RESOURCES FROM THE FILE */
  // If is a texture extension
  if (fileExtension == L"png"  || fileExtension == L"jpg"
   || fileExtension == L"tga"  || fileExtension == L"bmp"
   || fileExtension == L"tiff") {
    // Check flags
    if (importFlags == IMPORT_FLAGS::kNone
    ||  Math::hasFlag(importFlags, IMPORT_FLAGS::kImportTextures)
    || (Math::hasFlag(importFlags, IMPORT_FLAGS::kImportAll)
    &&  Math::hasFlag(importFlags, IMPORT_FLAGS::kNotImportTextures))) {
      // Load texture from file
      String resourceName = eeWStringtoString(name) + "_tex";
      loadTextureFromFile(fileName, resourceName);
    }
  }
  // If is a 3D model extension
  else if (fileExtension == L"obj"     || fileExtension == L"fbx"
        || fileExtension == L"md5mesh" || fileExtension == L"md5anim") {
    // Load Assimp Scene
    auto* importer = new Assimp::Importer();
    const aiScene* scene = importer->ReadFile
    (
      eeWStringtoString(fileName),
      aiProcessPreset_TargetRealtime_MaxQuality
      | aiProcess_ConvertToLeftHanded
    );

    if (!scene) {
      Logger::instance().consoleLog(importer->GetErrorString());
      delete importer;
      return false;
    }

    // Use the scene
    Map<uint32, WPtr<Material>> materials;
    if (scene->HasTextures()
    &&  importFlags == IMPORT_FLAGS::kNone
    ||  Math::hasFlag(importFlags, IMPORT_FLAGS::kImportTextures)
    || (Math::hasFlag(importFlags, IMPORT_FLAGS::kImportAll)
    &&  Math::hasFlag(importFlags, IMPORT_FLAGS::kNotImportTextures))) {
      materials = loadMaterialsFromAssimp(scene, eeWStringtoString(name));
    }

    if (scene->mRootNode
    && (importFlags == IMPORT_FLAGS::kNone
    ||  Math::hasFlag(importFlags, IMPORT_FLAGS::kImportSkeletalMeshes)
    || (Math::hasFlag(importFlags, IMPORT_FLAGS::kImportAll)
    &&  Math::hasFlag(importFlags, IMPORT_FLAGS::kNotImportSkeletalMeshes)))) {
      // Load skeleton
      SPtr<Skeletal> skeleton =
      loadSkeletalFromAssimp(scene, eeWStringtoString(name));
      if (skeleton) {
        m_skeletals.insert(
        Pair<String, SPtr<Skeletal>>(eeWStringtoString(name) + "_sk",
                                     skeleton));
      }
      
      if (scene->HasMeshes()) {
        // Load skeletal mesh
        SPtr<SkeletalMesh> skMesh =
        //loadSkeletalMeshFromAssimp(scene, skeleton, name + "_skm", textures);
        loadSkeletalMeshFromAssimp(scene,
                                   skeleton,
                                   eeWStringtoString(name) + "_skm",
                                   materials);
        if (skMesh) {
          m_skeletalMeshes.insert(
            Pair<String, SPtr<SkeletalMesh>>(eeWStringtoString(name) + "_skm",
                                             skMesh));
        }
      }
    }
    else if (importFlags == IMPORT_FLAGS::kNone
         ||  Math::hasFlag(importFlags, IMPORT_FLAGS::kImportStaticMeshes)
         || (Math::hasFlag(importFlags, IMPORT_FLAGS::kImportAll)
         &&  Math::hasFlag(importFlags, IMPORT_FLAGS::kNotImportStaticMeshes))) {
      if (scene->HasMeshes()) {
        // Load static mesh
        SPtr<StaticMesh> stMesh;
        SPtr<StaticMesh>* tempMesh = &stMesh;
        loadStaticMeshFromAssimp(scene,
                                 eeWStringtoString(name) + "_sm",
                                 materials,
                                 tempMesh);
        
        if (stMesh) {
          m_staticMeshes.insert(
            Pair<String, SPtr<StaticMesh>>(eeWStringtoString(name) + "_sm", 
                                           stMesh));
        }
      }
    }

    if (scene->HasAnimations()
    &&  importFlags == IMPORT_FLAGS::kNone
    ||  Math::hasFlag(importFlags, IMPORT_FLAGS::kImportAnimations)
    || (Math::hasFlag(importFlags, IMPORT_FLAGS::kImportAll)
    &&  Math::hasFlag(importFlags, IMPORT_FLAGS::kNotImportAnimations))) {
      // Load animations
      for (uint32 i = 0; i < scene->mNumAnimations; ++i) {
        String animName = eeWStringtoString(name)
                        + "_anim_"
                        + scene->mAnimations[i]->mName.C_Str();
        SPtr<Animation> anim = loadOneAnimationFromAssimp(scene, i, animName);
        if (anim) {
          m_animations.insert(Pair<String, SPtr<Animation>>(animName, anim));
        }
      }
    }
    delete importer;
  }
  return true;
}
WPtr<Texture>
ResourceManager::loadTextureFromFile(const WString& fileName,
                                     String& resourceName)
{
  if (m_textures.find(resourceName) != m_textures.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return {};
  }

  if (fileName.empty()) {
    Logger::instance().consoleLog("Empty info loading texture");
    return {};
  }

  SPtr<Image> tempImg = MemoryManager::instance().newPtr<Image>();
  if (!tempImg->loadFromFile(fileName)) {
    return {};
  }

  SPtr<Texture> tex = GraphicsApi::instance().createTexturePtr();
  tex->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                Point2D{ tempImg->getWidth(), tempImg->getHeight() });

  tex->loadImages({ tempImg });

  m_textures.insert(Pair<String, SPtr<Texture>>(resourceName,
                                                tex));

  serializeTexture(resourceName, L"Assets/" + eeStringtoWString(resourceName) + L".echoasset");

  return m_textures[resourceName];
}
WPtr<Material>
ResourceManager::loadMaterialFromTextures(const Map<uint32, WPtr<Texture>>& textures,
                                          const String& resourceName)
{
  if (m_textures.find(resourceName) != m_textures.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return {};
  }

  SPtr<Material> mat =
  MemoryManager::instance().newPtr<Material>(textures);

  m_materials.insert(Pair<String, SPtr<Material>>(resourceName,
                                                  mat));
  return m_materials[resourceName];
}
WPtr<StaticMesh>
ResourceManager::loadStaticMeshFromMeshesArray(const Vector<Mesh>& meshes,
                                               const String& resourceName,
                                               const Vector3f& furtherVertexPosition,
                                               const Vector3f& maxCoordinate,
                                               const Vector3f& minCoordinate)
{
  if (m_staticMeshes.find(resourceName) != m_staticMeshes.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return {};
  }

  if (meshes.empty()) {
    Logger::instance().consoleLog("Empty info loading static mesh");
    return {};
  }

  SPtr<StaticMesh> staticMesh = MemoryManager::instance().newPtr<StaticMesh>();
  if (!staticMesh->loadFromMeshes(meshes,
                                 resourceName,
                                 furtherVertexPosition,
                                 maxCoordinate,
                                 minCoordinate)) {
    return {};
  }

  m_staticMeshes.insert(Pair<String, SPtr<StaticMesh>>(resourceName,
                                                       staticMesh));
  return m_staticMeshes[resourceName];
}
WPtr<StaticMesh>
ResourceManager::loadStaticMeshFromMeshesArray(
                                const Vector<Pair<Mesh, WPtr<Material>>>& meshes,
                                const String& resourceName,
                                const Vector3f& furtherVertexPosition,
                                const Vector3f& maxCoordinate,
                                const Vector3f& minCoordinate)
{
  if (m_staticMeshes.find(resourceName) != m_staticMeshes.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return {};
  }

  if (meshes.empty()) {
    Logger::instance().consoleLog("Empty info loading static mesh");
    return {};
  }

  SPtr<StaticMesh> staticMesh = MemoryManager::instance().newPtr<StaticMesh>();
  if (!staticMesh->loadFromMeshes(meshes,
                                  resourceName,
                                  furtherVertexPosition,
                                  maxCoordinate,
                                  minCoordinate)) {
    return {};
  }
  
  m_staticMeshes.insert(Pair<String, SPtr<StaticMesh>>(resourceName,
                                                       staticMesh));
  return m_staticMeshes[resourceName];
}

WPtr<Skeletal>
ResourceManager::loadSkeletalFromFile(const WString& fileName,
                                      const String& resourceName)
{
  if (m_skeletals.find(resourceName) != m_skeletals.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return {};
  }

  if (fileName.empty()) {
    Logger::instance().consoleLog("Empty info loading skeletal");
    return {};
  }

  auto* importer = new Assimp::Importer();
  const aiScene* scene = importer->ReadFile
  (
    eeWStringtoString(fileName),
    aiProcessPreset_TargetRealtime_MaxQuality
    | aiProcess_ConvertToLeftHanded
  );

  if (!scene) {
    Logger::instance().consoleLog(importer->GetErrorString());
    delete importer;
    return {};
  }

  SPtr<Skeletal> skeleton = loadSkeletalFromAssimp(scene, resourceName);
  delete importer;
  if (skeleton)
  {
    m_skeletals.insert(Pair<String, SPtr<Skeletal>>(resourceName,
                                                    skeleton));
    return m_skeletals[resourceName];
  }
  return {};
}

WPtr<Animation>
ResourceManager::loadAnimationFromFile(const WString& fileName,
                                       const String& resourceName,
                                       const int32 animIndex)
{
  if (m_animations.find(resourceName) != m_animations.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return {};
  }

  if (fileName.empty()) {
    Logger::instance().consoleLog("Empty info loading animation");
    return {};
  }

  auto* importer = new Assimp::Importer();
  const aiScene* scene = importer->ReadFile
  (
    eeWStringtoString(fileName),
    aiProcessPreset_TargetRealtime_MaxQuality
    | aiProcess_ConvertToLeftHanded
  );

  if (!scene) {
    Logger::instance().consoleLog(importer->GetErrorString());
    delete importer;
    return {};
  }

  SPtr<Animation> anim = loadOneAnimationFromAssimp(scene, animIndex, resourceName);
  delete importer;
  if (anim) {
    m_animations.insert(Pair<String, SPtr<Animation>>(resourceName,
                                                      anim));
    return m_animations[resourceName];
  }
  return {};
}

WPtr<VertexShader>
ResourceManager::loadVertexShaderFromFile(const WString& fileName, 
                                          const String& functionName,
                                          const Vector<ShaderMacro>& macroDefinitions,
                                          const String& resourceName)
{
  if (m_vertexShaders.find(resourceName) != m_vertexShaders.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return {};
  }

  SPtr<VertexShader> shader = GraphicsApi::instance().createVertexShaderPtr();
  if (!shader->compileFromFile(fileName, functionName, macroDefinitions)) {
    Logger::instance().consoleLog("Error compiling shader");
    return {};
  }

  m_vertexShaders.insert(Pair<String, SPtr<VertexShader>>(resourceName,
                                                          shader));
  return m_vertexShaders[resourceName];
}

WPtr<VertexShader>
ResourceManager::loadVertexShaderFromString(const String& shaderString,
                                            const String& functionName,
                                            const Vector<ShaderMacro>& macroDefinitions,
                                            const String& resourceName)
{
  if (m_vertexShaders.find(resourceName) != m_vertexShaders.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return {};
  }

  SPtr<VertexShader> shader = GraphicsApi::instance().createVertexShaderPtr();
  if (!shader->compileFromString(shaderString, functionName, macroDefinitions)) {
    Logger::instance().consoleLog("Error compiling shader");
    return {};
  }

  m_vertexShaders.insert(Pair<String, SPtr<VertexShader>>(resourceName,
                                                          shader));
  return m_vertexShaders[resourceName];
}

WPtr<PixelShader>
ResourceManager::loadPixelShaderFromFile(const WString& fileName,
                                         const String& functionName,
                                         const Vector<ShaderMacro>& macroDefinitions,
                                         const String& resourceName)
{
  if (m_pixelShaders.find(resourceName) != m_pixelShaders.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return {};
  }

  SPtr<PixelShader> shader = GraphicsApi::instance().createPixelShaderPtr();
  if (!shader->compileFromFile(fileName, functionName, macroDefinitions)) {
    Logger::instance().consoleLog("Error compiling shader");
    return {};
  }

  m_pixelShaders.insert(Pair<String, SPtr<PixelShader>>(resourceName,
                                                        shader));
  return m_pixelShaders[resourceName];
}

WPtr<PixelShader>
ResourceManager::loadPixelShaderFromString(const String& shaderString,
                                           const String& functionName,
                                           const Vector<ShaderMacro>& macroDefinitions,
                                           const String& resourceName)
{
  if (m_pixelShaders.find(resourceName) != m_pixelShaders.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return {};
  }

  SPtr<PixelShader> shader = GraphicsApi::instance().createPixelShaderPtr();
  if (!shader->compileFromString(shaderString, functionName, macroDefinitions)) {
    Logger::instance().consoleLog("Error compiling shader");
    return {};
  }

  m_pixelShaders.insert(Pair<String, SPtr<PixelShader>>(resourceName,
                                                        shader));
  return m_pixelShaders[resourceName];
}

WPtr<HullShader>
ResourceManager::loadHullShaderFromFile(const WString& fileName,
                                        const String& functionName,
                                        const Vector<ShaderMacro>& macroDefinitions,
                                        const String& resourceName)
{
  if (m_hullShaders.find(resourceName) != m_hullShaders.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return {};
  }

  SPtr<HullShader> shader = GraphicsApi::instance().createHullShaderPtr();
  if (!shader->compileFromFile(fileName, functionName, macroDefinitions)) {
    Logger::instance().consoleLog("Error compiling shader");
    return {};
  }

  m_hullShaders.insert(Pair<String, SPtr<HullShader>>(resourceName,
                                                      shader));
  return m_hullShaders[resourceName];
}

WPtr<HullShader>
ResourceManager::loadHullShaderFromString(const String& shaderString,
                                          const String& functionName,
                                          const Vector<ShaderMacro>& macroDefinitions,
                                          const String& resourceName)
{
  if (m_hullShaders.find(resourceName) != m_hullShaders.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return {};
  }

  SPtr<HullShader> shader = GraphicsApi::instance().createHullShaderPtr();
  if (!shader->compileFromString(shaderString, functionName, macroDefinitions)) {
    Logger::instance().consoleLog("Error compiling shader");
    return {};
  }

  m_hullShaders.insert(Pair<String, SPtr<HullShader>>(resourceName,
                                                      shader));
  return m_hullShaders[resourceName];
}

WPtr<DomainShader>
ResourceManager::loadDomainShaderFromFile(const WString& fileName,
                                          const String& functionName,
                                          const Vector<ShaderMacro>& macroDefinitions,
                                          const String& resourceName)
{
  if (m_domainShaders.find(resourceName) != m_domainShaders.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return {};
  }

  SPtr<DomainShader> shader = GraphicsApi::instance().createDomainShaderPtr();
  if (!shader->compileFromFile(fileName, functionName, macroDefinitions)) {
    Logger::instance().consoleLog("Error compiling shader");
    return {};
  }

  m_domainShaders.insert(Pair<String, SPtr<DomainShader>>(resourceName,
                                                          shader));
  return m_domainShaders[resourceName];
}

WPtr<DomainShader>
ResourceManager::loadDomainShaderFromString(const String& shaderString,
                                            const String& functionName,
                                            const Vector<ShaderMacro>& macroDefinitions,
                                            const String& resourceName)
{
  if (m_domainShaders.find(resourceName) != m_domainShaders.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return {};
  }

  SPtr<DomainShader> shader = GraphicsApi::instance().createDomainShaderPtr();
  if (!shader->compileFromString(shaderString, functionName, macroDefinitions)) {
    Logger::instance().consoleLog("Error compiling shader");
    return {};
  }

  m_domainShaders.insert(Pair<String, SPtr<DomainShader>>(resourceName,
                                                          shader));
  return m_domainShaders[resourceName];
}

WPtr<Texture>
ResourceManager::getResourceTexture(const String& resourceName)
{
  if (m_textures.find(resourceName) != m_textures.end()) {
    return m_textures[resourceName];
  }
  return {};
}
WPtr<Material>
ResourceManager::getResourceMaterial(const String& resourceName)
{
  if (m_materials.find(resourceName) != m_materials.end()) {
    return m_materials[resourceName];
  }
  return {};
}
WPtr<StaticMesh>
ResourceManager::getResourceStaticMesh(const String& resourceName)
{
  if (m_staticMeshes.find(resourceName) != m_staticMeshes.end()) {
    return m_staticMeshes[resourceName];
  }
  return {};
}
WPtr<Skeletal>
ResourceManager::getResourceSkeletal(const String& resourceName)
{
  if (m_skeletals.find(resourceName) != m_skeletals.end()) {
    return m_skeletals[resourceName];
  }
  return {};
}
WPtr<SkeletalMesh>
ResourceManager::getResourceSkeletalMesh(const String& resourceName)
{
  if (m_skeletalMeshes.find(resourceName) != m_skeletalMeshes.end()) {
    return m_skeletalMeshes[resourceName];
  }
  return {};
}
WPtr<Animation>
ResourceManager::getResourceAnimation(const String& resourceName)
{
  if (m_animations.find(resourceName) != m_animations.end()) {
    return m_animations[resourceName];
  }
  return {};
}
WPtr<VertexShader>
ResourceManager::getResourceVertexShader(const String& resourceName)
{
  if (m_vertexShaders.find(resourceName) != m_vertexShaders.end()) {
    return m_vertexShaders[resourceName];
  }
  return {};
}
WPtr<PixelShader>
ResourceManager::getResourcePixelShader(const String& resourceName)
{
  if (m_pixelShaders.find(resourceName) != m_pixelShaders.end()) {
    return m_pixelShaders[resourceName];
  }
  return {};
}
WPtr<HullShader>
ResourceManager::getResourceHullShader(const String& resourceName)
{
  if (m_hullShaders.find(resourceName) != m_hullShaders.end()) {
    return m_hullShaders[resourceName];
  }
  return {};
}
WPtr<DomainShader>
ResourceManager::getResourceDomainShader(const String& resourceName)
{
  if (m_domainShaders.find(resourceName) != m_domainShaders.end()) {
    return m_domainShaders[resourceName];
  }
  return {};
}
Map<String, SPtr<Texture>>
ResourceManager::getAllTextureResources()
{
  return m_textures;
}
Map<String, SPtr<Material>> ResourceManager::getAllMaterialResources()
{
  return m_materials;
}
Map<String, SPtr<StaticMesh>>
ResourceManager::getAllStaticMeshResources()
{
  return m_staticMeshes;
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
Map<String, SPtr<HullShader>>
ResourceManager::getAllHullShaderResources()
{
  return m_hullShaders;
}

Map<String, SPtr<DomainShader>>
ResourceManager::getAllDomainShaderResources()
{
  return m_domainShaders;
}

namespace eRESOURCE_CODE {
enum E : uint8 {
  kNone = 0,
  kTexture,
  kMaterial,
  kStaticMesh,
  kSkeletal,
  kSkeletalMesh,
  kAnimation,
  kCount
};
}

void
ResourceManager::loadAllSerialized()
{
  for (auto const& dir_entry : std::filesystem::directory_iterator("Assets")) {
    std::cout << dir_entry.path() << '\n';

    if (dir_entry.is_regular_file()) {
      File loadFile;
      WString filePath = dir_entry.path();
      loadFile.openFile(filePath, OPEN_TYPE::kReadOnly
                                                | OPEN_TYPE::kBinary);
      if (loadFile.isOpen()) {
        String resourceName;

        String pathW2S = eeWStringtoString(filePath);
        bool readingName = false;
        int64 pathSize = static_cast<int64>(pathW2S.size());
        for (int64 i = pathSize - 1; i >= 0; --i) {
          if (!readingName) {
            if (pathW2S[i] == '.') {
              readingName = true;
            }
          }
          else {
            if (pathW2S[i] == '/' || pathW2S[i] == '\\') {
              break;
            }
            //resourceName.insert(resourceName.end() - 1, pathW2S[i]);
            resourceName = pathW2S[i] + resourceName;
          }
        }


        uint8 readResourceCode = 0;
        loadFile.readBytes(reinterpret_cast<Byte*>(&readResourceCode),
                           sizeof(uint8));

        switch (readResourceCode)
        {
        case eRESOURCE_CODE::kTexture:
          deserializeTexture(loadFile, resourceName);
          break;
        }
      }
    }
  }
}

bool
ResourceManager::serializeTexture(const String& resourceName,
                                  const WString& fileToSave)
{
  if (m_textures.find(resourceName) != m_textures.end()) {
    File saveFile;
    saveFile.openFile(fileToSave, OPEN_TYPE::kWriteOnly | OPEN_TYPE::kBinary);
    if (saveFile.isOpen()) {
      auto tex = m_textures[resourceName];
      uint8 resourceCode = eRESOURCE_CODE::kTexture;
      saveFile.writeBytes(reinterpret_cast<Byte*>(&resourceCode), sizeof(uint8));
      int8 sizeTSize = sizeof(SIZE_T);
      saveFile.writeBytes(reinterpret_cast<Byte*>(&sizeTSize), sizeof(uint8));
      Vector<SPtr<Image>> images = tex->getImages();
      SIZE_T imagesCount = images.size();
      saveFile.writeBytes(reinterpret_cast<Byte*>(&imagesCount), sizeof(SIZE_T));
      for (auto& img : images) {
        uint32 imgWidth = img->getWidth();
        uint32 imgHeight = img->getHeight();
        saveFile.writeBytes(reinterpret_cast<Byte*>(&imgWidth), sizeof(uint32));
        saveFile.writeBytes(reinterpret_cast<Byte*>(&imgHeight), sizeof(uint32));
        saveFile.writeBytes(reinterpret_cast<Byte*>(img->getData()),
                            imgWidth * imgHeight * sizeof(ColorI));
      }
      saveFile.close();

      return true;
    }
  }
  return false;
}
bool
ResourceManager::deserializeTexture(File& fileToLoad, const String& resourceName)
{
  if (m_textures.find(resourceName) != m_textures.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return false;
  }

  if (fileToLoad.isOpen()) {
    uint8 readSizeTSize = 0;
    fileToLoad.readBytes(reinterpret_cast<Byte*>(&readSizeTSize), sizeof(uint8));
    SIZE_T readImagesCount = 0;
    if (readSizeTSize == 4) {
      uint32 byte4ImagesCount = 0;
      fileToLoad.readBytes(reinterpret_cast<Byte*>(&byte4ImagesCount), sizeof(uint32));
      readImagesCount = static_cast<SIZE_T>(byte4ImagesCount);
    }
    else if (readSizeTSize == 8) {
      uint64 byte8ImagesCount = 0;
      fileToLoad.readBytes(reinterpret_cast<Byte*>(&byte8ImagesCount), sizeof(uint64));
      readImagesCount = static_cast<SIZE_T>(byte8ImagesCount);
    }
    Vector<SPtr<Image>> readImages;
    for (SIZE_T i = 0; i < readImagesCount; ++i) {
      readImages.push_back(MemoryManager::instance().newPtr<Image>());
      uint32 width = 0;
      uint32 height = 0;
      fileToLoad.readBytes(reinterpret_cast<Byte*>(&width), sizeof(uint32));
      fileToLoad.readBytes(reinterpret_cast<Byte*>(&height), sizeof(uint32));
      int32 dataArraySize = width * height * sizeof(ColorI);
      Byte* imgData = new Byte[dataArraySize];
      memset(imgData, 0, dataArraySize);
      fileToLoad.readBytes(imgData, dataArraySize);
      readImages[i]->loadFromPixelData(imgData, width, height);
      delete[] imgData;
    }

    SPtr<Texture> tex = GraphicsApi::instance().createTexturePtr();
    tex->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
      Point2D{ readImages[0]->getWidth(), readImages[0]->getHeight() });

    tex->loadImages(readImages);

    m_textures.insert(Pair<String, SPtr<Texture>>(resourceName, tex));

    return true;
  }
  return false;
}
}