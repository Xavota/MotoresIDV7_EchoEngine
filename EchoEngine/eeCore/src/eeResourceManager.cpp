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

#include <eeSerializationUtilities.h>

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
                         const Map<uint32, WPtr<Material>>& textures,
                         SPtr<StaticMesh>* outStaticMesh)
{
  *outStaticMesh = MemoryManager::instance().newPtr<StaticMesh>();

  Vector<Pair<Mesh, WPtr<Material>>> meshes;
  meshes.resize(scene->mNumMeshes);

  Vector3f maxBound(-99999.99f, -99999.99f, -99999.99f);
  Vector3f minBound( 99999.99f,  99999.99f,  99999.99f);
  float furtherDistance = 0.0f;
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

        if (distance > furtherDistance)
        {
          furtherDistance = distance;
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

  (*outStaticMesh)->loadFromMeshes(meshes, furtherDistance, maxBound, minBound);
}
SPtr<SkeletalMesh>
loadSkeletalMeshFromAssimp(const aiScene* scene,
                           WPtr<Skeletal> skeleton,
                           const Map<uint32, WPtr<Material>>& textures)
{
  SPtr<SkeletalMesh> outSkeletalMesh = MemoryManager::instance().newPtr<SkeletalMesh>();

  Vector<Pair<BoneMesh, WPtr<Material>>> meshes;

  Vector3f maxBound(-99999.99f, -99999.99f, -99999.99f);
  Vector3f minBound(99999.99f, 99999.99f, 99999.99f);
  float furtherDist = 0.0f;
  meshes.resize(scene->mNumMeshes);
  for (uint32 i = 0; i < scene->mNumMeshes; ++i) {
    Vector<ComplexBigAnimVertex<4>> vertices;
    aiMesh* AssimpMesh = scene->mMeshes[i];

    for (uint32 j = 0; j < AssimpMesh->mNumVertices; ++j) {
      ComplexBigAnimVertex<4> v;
      memset(&v, 0, sizeof(ComplexBigAnimVertex<4>));
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

        if (distance > furtherDist)
        {
          furtherDist = distance;
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
            for (uint32 l = 0; l < 4; l++) {
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

    
    meshes[i] = Pair<BoneMesh, WPtr<Material>>(
      BoneMesh(),
      textures.find(AssimpMesh->mMaterialIndex) != textures.end()
      ? (*textures.find(AssimpMesh->mMaterialIndex)).second
      : resourseManager.getResourceMaterial("Default_mat"));
    meshes[i].first.loadFromArray(vertices, indices);

    vertices.clear();
    indices.clear();
  }

  outSkeletalMesh->loadFromMeshes(meshes,
                                  skeleton,
                                  furtherDist,
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
loadSkeletalFromAssimp(const aiScene* scene)
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
                            numsBones);

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
                           int32 animIndex)
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

  outAnimation->loadFromData(ticksPerSecond, duration, channels, rootNode);

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
      | aiProcess_Triangulate
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
      String strName = eeWStringtoString(name);
      String resName = strName + "_sk";
      SPtr<Skeletal> skeleton = nullptr;
      if (m_skeletals.find(resName) == m_skeletals.end()) {
        skeleton = loadSkeletalFromAssimp(scene);
        if (skeleton) {
          skeleton->setResourceName(resName);
          m_skeletals.insert(
          Pair<String, SPtr<Skeletal>>(resName, skeleton));
        
          serializeSkeleton(resName,
                            L"Assets/"
                          + eeStringtoWString(resName)
                          + L".echoasset");
        }
      }
      else {
        skeleton = m_skeletals[resName];
      }
      
      if (scene->HasMeshes()) {
        // Load skeletal mesh
        resName = strName + "_skm";
        if (m_skeletalMeshes.find(resName) == m_skeletalMeshes.end()) {
          SPtr<SkeletalMesh> skMesh =
          //loadSkeletalMeshFromAssimp(scene, skeleton, name + "_skm", textures);
          loadSkeletalMeshFromAssimp(scene,
                                     skeleton,
                                     materials);
          if (skMesh) {
            skMesh->setResourceName(resName);
            m_skeletalMeshes.insert(
              Pair<String, SPtr<SkeletalMesh>>(resName,
                                               skMesh));

            serializeSkeletalMesh(resName,
                                  L"Assets/"
                                + eeStringtoWString(resName)
                                + L".echoasset");
          }
        }
      }
    }
    else if (importFlags == IMPORT_FLAGS::kNone
         ||  Math::hasFlag(importFlags, IMPORT_FLAGS::kImportStaticMeshes)
         || (Math::hasFlag(importFlags, IMPORT_FLAGS::kImportAll)
         &&  Math::hasFlag(importFlags, IMPORT_FLAGS::kNotImportStaticMeshes))) {
      if (scene->HasMeshes()) {
        // Load static mesh
        String resName = eeWStringtoString(name) + "_sm";
        if (m_staticMeshes.find(resName) == m_staticMeshes.end()) {
          SPtr<StaticMesh> stMesh;
          loadStaticMeshFromAssimp(scene,
                                   materials,
                                   &stMesh);
          
          if (stMesh) {
            stMesh->setResourceName(resName);
            m_staticMeshes.insert(
              Pair<String, SPtr<StaticMesh>>(resName,
                                             stMesh));
          
            serializeStaticMesh(resName,
                                L"Assets/"
                              + eeStringtoWString(resName)
                              + L".echoasset");
          }
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
        if (m_animations.find(animName) == m_animations.end()) {
          SPtr<Animation> anim = loadOneAnimationFromAssimp(scene, i);
          if (anim) {
            anim->setResourceName(animName);
            m_animations.insert(Pair<String, SPtr<Animation>>(animName, anim));
            
            serializeAnimation(animName,
                               L"Assets/"
                             + eeStringtoWString(animName)
                             + L".echoasset");
          }
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
    return m_textures[resourceName];
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

  tex->setResourceName(resourceName);
  m_textures.insert(Pair<String, SPtr<Texture>>(resourceName,
                                                tex));

  serializeTexture(resourceName, L"Assets/" + eeStringtoWString(resourceName) + L".echoasset");

  return m_textures[resourceName];
}
WPtr<Material>
ResourceManager::loadMaterialFromTextures(const Map<uint32, WPtr<Texture>>& textures,
                                          const String& resourceName)
{
  if (m_materials.find(resourceName) != m_materials.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return m_materials[resourceName];
  }

  SPtr<Material> mat =
  MemoryManager::instance().newPtr<Material>(textures);

  mat->setResourceName(resourceName);
  m_materials.insert(Pair<String, SPtr<Material>>(resourceName,
                                                  mat));

  serializeMaterial(resourceName, L"Assets/" + eeStringtoWString(resourceName) + L".echomat");

  return m_materials[resourceName];
}
WPtr<StaticMesh>
ResourceManager::loadStaticMeshFromMeshesArray(const Vector<Mesh>& meshes,
                                               const String& resourceName,
                                               float furtherDist,
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
                                 furtherDist,
                                 maxCoordinate,
                                 minCoordinate)) {
    return {};
  }

  staticMesh->setResourceName(resourceName);
  m_staticMeshes.insert(Pair<String, SPtr<StaticMesh>>(resourceName,
                                                       staticMesh));

  serializeStaticMesh(resourceName,
                      L"Assets/"
                    + eeStringtoWString(resourceName)
                    + L".echoasset");

  return m_staticMeshes[resourceName];
}
WPtr<StaticMesh>
ResourceManager::loadStaticMeshFromMeshesArray(
                               const Vector<Pair<Mesh, WPtr<Material>>>& meshes,
                               const String& resourceName,
                               float furtherDist,
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
                                  furtherDist,
                                  maxCoordinate,
                                  minCoordinate)) {
    return {};
  }

  staticMesh->setResourceName(resourceName);
  m_staticMeshes.insert(Pair<String, SPtr<StaticMesh>>(resourceName,
                                                       staticMesh));

  serializeStaticMesh(resourceName,
                      L"Assets/"
                    + eeStringtoWString(resourceName)
                    + L".echoasset");

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

  SPtr<Skeletal> skeleton = loadSkeletalFromAssimp(scene);
  delete importer;
  if (skeleton)
  {
    skeleton->setResourceName(resourceName);
    m_skeletals.insert(Pair<String, SPtr<Skeletal>>(resourceName,
                                                    skeleton));
    return m_skeletals[resourceName];
  }

  serializeSkeleton(resourceName,
                    L"Assets/"
                  + eeStringtoWString(resourceName)
                  + L".echoasset");

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

  SPtr<Animation> anim = loadOneAnimationFromAssimp(scene, animIndex);
  delete importer;
  if (anim) {
    anim->setResourceName(resourceName);
    m_animations.insert(Pair<String, SPtr<Animation>>(resourceName,
                                                      anim));

    serializeAnimation(resourceName,
                       L"Assets/"
                     + eeStringtoWString(resourceName)
                     + L".echoasset");

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
getResourceData(File& iFile,
                uint8& resourceCode,
                uint8& versionNum,
                uint8& sizeTSize)
{
  iFile.readBytes(reinterpret_cast<Byte*>(&resourceCode),
                  sizeof(uint8));
  iFile.readBytes(reinterpret_cast<Byte*>(&versionNum),
                  sizeof(uint8));
  iFile.readBytes(reinterpret_cast<Byte*>(&sizeTSize),
                  sizeof(uint8));
}

void
ResourceManager::loadAllSerialized()
{
  auto filesArray = std::filesystem::directory_iterator("Assets");
  for (auto const& dir_entry : filesArray) {
    if (dir_entry.is_regular_file()) {
      File loadFile;
      WString filePath = dir_entry.path();
      loadFile.openFile(filePath, OPEN_TYPE::kReadOnly
                                | OPEN_TYPE::kBinary);
      if (loadFile.isOpen()) {
        String resourceName;
        getFileName(filePath, resourceName);

        uint8 readResourceCode = 0;
        uint8 readVersionNum = 0;
        uint8 readSizeTSize = 0;
        getResourceData(loadFile, readResourceCode, readVersionNum, readSizeTSize);
        
        if (readResourceCode == eRESOURCE_CODE::kTexture) {
          std::cout << dir_entry.path() << '\n';
          loadSerializedTexture(loadFile,
                                resourceName,
                                readVersionNum,
                                readSizeTSize);
        }
        else if (readResourceCode == eRESOURCE_CODE::kSkeletal) {
          std::cout << dir_entry.path() << '\n';
          loadSerializedSkeleton(loadFile,
                                 resourceName,
                                 readVersionNum,
                                 readSizeTSize);
        }
        else if (readResourceCode == eRESOURCE_CODE::kAnimation) {
          std::cout << dir_entry.path() << '\n';
          loadSerializedAnimation(loadFile,
                                  resourceName,
                                  readVersionNum,
                                  readSizeTSize);
        }

        loadFile.close();
      }
    }
  }
  filesArray = std::filesystem::directory_iterator("Assets");
  for (auto const& dir_entry : filesArray) {
    if (dir_entry.is_regular_file()) {
      File loadFile;
      WString filePath = dir_entry.path();
      loadFile.openFile(filePath, OPEN_TYPE::kReadOnly
        | OPEN_TYPE::kBinary);
      if (loadFile.isOpen()) {
        String resourceName;
        getFileName(filePath, resourceName);

        uint8 readResourceCode = 0;
        uint8 readVersionNum = 0;
        uint8 readSizeTSize = 0;
        getResourceData(loadFile, readResourceCode, readVersionNum, readSizeTSize);

        if (readResourceCode == eRESOURCE_CODE::kMaterial) {
          std::cout << dir_entry.path() << '\n';
          loadSerializedMaterial(loadFile,
                                 resourceName,
                                 readVersionNum,
                                 readSizeTSize);
        }

        loadFile.close();
      }
    }
  }
  filesArray = std::filesystem::directory_iterator("Assets");
  for (auto const& dir_entry : filesArray) {
    if (dir_entry.is_regular_file()) {
      File loadFile;
      WString filePath = dir_entry.path();
      loadFile.openFile(filePath, OPEN_TYPE::kReadOnly
        | OPEN_TYPE::kBinary);
      if (loadFile.isOpen()) {
        String resourceName;
        getFileName(filePath, resourceName);

        uint8 readResourceCode = 0;
        uint8 readVersionNum = 0;
        uint8 readSizeTSize = 0;
        getResourceData(loadFile, readResourceCode, readVersionNum, readSizeTSize);

        if (readResourceCode == eRESOURCE_CODE::kStaticMesh) {
          std::cout << dir_entry.path() << '\n';
          loadSerializedStaticMesh(loadFile,
                                   resourceName,
                                   readVersionNum,
                                   readSizeTSize);
        }
        else if (readResourceCode == eRESOURCE_CODE::kSkeletalMesh) {
          std::cout << dir_entry.path() << '\n';
          loadSerializedSkeletalMesh(loadFile,
                                     resourceName,
                                     readVersionNum,
                                     readSizeTSize);
        }

        loadFile.close();
      }
    }
  }
}

void
serializeFileStartData(File& oFile, uint8 resourceCode, uint8 versionNum)
{
  oFile.writeBytes(reinterpret_cast<Byte*>(&resourceCode), sizeof(uint8));
  oFile.writeBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  uint8 sizeTSize = sizeof(SIZE_T);
  oFile.writeBytes(reinterpret_cast<Byte*>(&sizeTSize), sizeof(uint8));
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
      serializeFileStartData(saveFile, eRESOURCE_CODE::kTexture, 1);

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

        serializeString(saveFile, img->getPath());
      }
      saveFile.close();

      return true;
    }
  }
  return false;
}
bool
ResourceManager::serializeMaterial(const String& resourceName,
                                   const WString& fileToSave)
{
  if (m_materials.find(resourceName) != m_materials.end()) {
    File saveFile;
    saveFile.openFile(fileToSave, OPEN_TYPE::kWriteOnly | OPEN_TYPE::kBinary);
    if (saveFile.isOpen()) {
      auto mat = m_materials[resourceName];
      serializeFileStartData(saveFile, eRESOURCE_CODE::kMaterial, 0);

      Map<uint32, WPtr<Texture>> texsMap = mat->getTexturesMap();
      SIZE_T texCount = texsMap.size();
      saveFile.writeBytes(reinterpret_cast<Byte*>(&texCount), sizeof(SIZE_T));

      for (auto& tex : texsMap) {
        uint32 texIndex = tex.first;
        saveFile.writeBytes(reinterpret_cast<Byte*>(&texIndex), sizeof(uint32));
        String texName = tex.second.lock()->getResourceName();
        serializeString(saveFile, texName);
      }
      saveFile.close();

      return true;
    }
  }
  return false;
}
void
serializeMesh(File& saveFile, const Mesh& meshToSerialize)
{
  uint8 vertexType = meshToSerialize.getVertexType();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&vertexType), sizeof(uint8));
  if (vertexType == eVertexType::kComplex) {
    Vector<Triangle> trianglesArr = meshToSerialize.getTrianglesArray();

    SIZE_T trianglesCount = trianglesArr.size();
    saveFile.writeBytes(reinterpret_cast<Byte*>(&trianglesCount), sizeof(SIZE_T));
    saveFile.writeBytes(reinterpret_cast<Byte*>(trianglesArr.data()),
                        static_cast<uint32>(trianglesCount * sizeof(Triangle)));

    Vector<uint32> indicesArr = meshToSerialize.getIndicesArray();

    SIZE_T indicesCount = indicesArr.size();
    saveFile.writeBytes(reinterpret_cast<Byte*>(&indicesCount), sizeof(SIZE_T));
    saveFile.writeBytes(reinterpret_cast<Byte*>(indicesArr.data()),
                        static_cast<uint32>(indicesCount * sizeof(uint32)));
  }
  else if (vertexType == eVertexType::kControlPoints) {
    Vector<ComplexVertex> pointsArr = meshToSerialize.getControlPointsArray();

    SIZE_T pointsCount = pointsArr.size();
    saveFile.writeBytes(reinterpret_cast<Byte*>(&pointsCount), sizeof(SIZE_T));
    saveFile.writeBytes(reinterpret_cast<Byte*>(pointsArr.data()),
                        static_cast<uint32>(pointsCount * sizeof(ComplexVertex)));
  }
}
bool
ResourceManager::serializeStaticMesh(const String& resourceName,
                                     const WString& fileToSave)
{
  if (m_staticMeshes.find(resourceName) != m_staticMeshes.end()) {
    File saveFile;
    saveFile.openFile(fileToSave, OPEN_TYPE::kWriteOnly | OPEN_TYPE::kBinary);
    if (saveFile.isOpen()) {
      auto sMesh = m_staticMeshes[resourceName];
      serializeFileStartData(saveFile, eRESOURCE_CODE::kStaticMesh, 0);

      Vector<Pair<Mesh, WPtr<Material>>> meshes = sMesh->getMeshes();
      SIZE_T meshesCount = meshes.size();
      saveFile.writeBytes(reinterpret_cast<Byte*>(&meshesCount), sizeof(SIZE_T));

      for (SIZE_T i = 0; i < meshesCount; ++i) {
        serializeMesh(saveFile, meshes[i].first);
        if (!meshes[i].second.expired()) {
          serializeString(saveFile, meshes[i].second.lock()->getResourceName());
        }
        else {
          SIZE_T stringLength = 0;
          saveFile.writeBytes(reinterpret_cast<Byte*>(&stringLength), sizeof(SIZE_T));
        }
      }

      Sphere boundSphere = sMesh->getBoundingSphere();
      float sphereRadius = boundSphere.getRadious();
      saveFile.writeBytes(reinterpret_cast<Byte*>(&sphereRadius), sizeof(float));

      BoxAAB boundBox = sMesh->getBoundingBox();
      Vector3f boxMinVertex = boundBox.getA();
      saveFile.writeBytes(reinterpret_cast<Byte*>(&boxMinVertex), sizeof(Vector3f));
      Vector3f boxMaxVertex = boundBox.getB();
      saveFile.writeBytes(reinterpret_cast<Byte*>(&boxMaxVertex), sizeof(Vector3f));

      saveFile.close();

      return true;
    }
  }

  return false;
}
bool
ResourceManager::serializeSkeleton(const String& resourceName,
                                   const WString& fileToSave)
{
  if (m_skeletals.find(resourceName) != m_skeletals.end()) {
    File saveFile;
    saveFile.openFile(fileToSave, OPEN_TYPE::kWriteOnly | OPEN_TYPE::kBinary);
    if (saveFile.isOpen()) {
      auto sSkeleton = m_skeletals[resourceName];
      serializeFileStartData(saveFile, eRESOURCE_CODE::kSkeletal, 0);

      Vector<Vector<Bone>>& bonesPerMesh = sSkeleton->getBonesData();
      Vector<Matrix4f>& globalInverseTransforms = sSkeleton->getGlobalInverseTransforms();
      Vector<Map<String, uint32>>& boneMaping = sSkeleton->getBoneMapping();
      Vector<uint32> numsBones = sSkeleton->getNumBones();

      SIZE_T meshesCount = bonesPerMesh.size();
      saveFile.writeBytes(reinterpret_cast<Byte*>(&meshesCount), sizeof(SIZE_T));

      for (SIZE_T i = 0; i < meshesCount; ++i) {
        SIZE_T bonesCount = bonesPerMesh[i].size();
        saveFile.writeBytes(reinterpret_cast<Byte*>(&bonesCount), sizeof(SIZE_T));
        for (SIZE_T j = 0; j < bonesCount; ++j) {
          serializeString(saveFile, bonesPerMesh[i][j].m_name);

          SIZE_T vertexWeightsCount = bonesPerMesh[i][j].m_vertexWeights.size();
          saveFile.writeBytes(reinterpret_cast<Byte*>(&vertexWeightsCount),
                              sizeof(SIZE_T));
          saveFile.writeBytes(
            reinterpret_cast<Byte*>(bonesPerMesh[i][j].m_vertexWeights.data()),
            static_cast<uint32>(vertexWeightsCount * sizeof(VertexWeight)));
            
          saveFile.writeBytes(
            reinterpret_cast<Byte*>(&bonesPerMesh[i][j].m_offsetMatrix),
            sizeof(Matrix4f));
          saveFile.writeBytes(
            reinterpret_cast<Byte*>(&bonesPerMesh[i][j].m_finalTransformation),
            sizeof(Matrix4f));

        }

        saveFile.writeBytes(reinterpret_cast<Byte*>(&globalInverseTransforms[i]),
                            sizeof(Matrix4f));

        SIZE_T bonesMapsCount = boneMaping[i].size();
        saveFile.writeBytes(reinterpret_cast<Byte*>(&bonesMapsCount),
                            sizeof(SIZE_T));
        for (auto& bm : boneMaping[i]) {
          serializeString(saveFile, bm.first);
          saveFile.writeBytes(reinterpret_cast<Byte*>(&bm.second),
                              sizeof(uint32));
        }

        saveFile.writeBytes(reinterpret_cast<Byte*>(&numsBones[i]),
                            sizeof(uint32));
      }
      saveFile.close();

      return true;
    }
  }

  return false;
}
void
serializeBoneMesh(File& saveFile, const BoneMesh& meshToSerialize)
{
  Vector<ComplexBigAnimVertex<4>> verticesArr = meshToSerialize.getVertexArray();

  SIZE_T verticesCount = verticesArr.size();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&verticesCount), sizeof(SIZE_T));
  saveFile.writeBytes(reinterpret_cast<Byte*>(verticesArr.data()),
          static_cast<uint32>(verticesCount * sizeof(ComplexBigAnimVertex<4>)));

  Vector<uint32> indicesArr = meshToSerialize.getIndexArray();

  SIZE_T indicesCount = indicesArr.size();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&indicesCount), sizeof(SIZE_T));
  saveFile.writeBytes(reinterpret_cast<Byte*>(indicesArr.data()),
                      static_cast<uint32>(indicesCount * sizeof(uint32)));
}
bool
ResourceManager::serializeSkeletalMesh(const String& resourceName,
                                       const WString& fileToSave)
{
  if (m_skeletalMeshes.find(resourceName) != m_skeletalMeshes.end()) {
    File saveFile;
    saveFile.openFile(fileToSave, OPEN_TYPE::kWriteOnly | OPEN_TYPE::kBinary);
    if (saveFile.isOpen()) {
      auto sSkMesh = m_skeletalMeshes[resourceName];
      serializeFileStartData(saveFile, eRESOURCE_CODE::kSkeletalMesh, 0);

      auto skeleton = sSkMesh->getSkeletal();
      if (!skeleton.expired()) {
        serializeString(saveFile, skeleton.lock()->getResourceName());
      }
      else {
        SIZE_T stringLength = 0;
        saveFile.writeBytes(reinterpret_cast<Byte*>(&stringLength), sizeof(SIZE_T));
      }

      Vector<Pair<BoneMesh, WPtr<Material>>> meshes = sSkMesh->getMeshes();
      SIZE_T meshesCount = meshes.size();
      saveFile.writeBytes(reinterpret_cast<Byte*>(&meshesCount), sizeof(SIZE_T));
  
      for (SIZE_T i = 0; i < meshesCount; ++i) {
        serializeBoneMesh(saveFile, meshes[i].first);
        if (!meshes[i].second.expired()) {
          serializeString(saveFile, meshes[i].second.lock()->getResourceName());
        }
        else {
          SIZE_T stringLength = 0;
          saveFile.writeBytes(reinterpret_cast<Byte*>(&stringLength), sizeof(SIZE_T));
        }
      }
  
      Sphere boundSphere = sSkMesh->getBoundingSphere();
      float sphereRadius = boundSphere.getRadious();
      saveFile.writeBytes(reinterpret_cast<Byte*>(&sphereRadius), sizeof(float));
  
      BoxAAB boundBox = sSkMesh->getBoundingBox();
      Vector3f boxMinVertex = boundBox.getA();
      saveFile.writeBytes(reinterpret_cast<Byte*>(&boxMinVertex), sizeof(Vector3f));
      Vector3f boxMaxVertex = boundBox.getB();
      saveFile.writeBytes(reinterpret_cast<Byte*>(&boxMaxVertex), sizeof(Vector3f));

      saveFile.close();

      return true;
    }
  }
  
  return false;
}
void
serializeAnimationNode(File& saveFile, SPtr<Node> node)
{
  serializeString(saveFile, node->m_name);

  saveFile.writeBytes(reinterpret_cast<Byte*>(&node->m_transformation),
                      sizeof(Matrix4f));

  saveFile.writeBytes(reinterpret_cast<Byte*>(&node->m_childrenCount),
                      sizeof(uint32));

  for (uint32 i = 0; i < node->m_childrenCount; ++i) {
    serializeAnimationNode(saveFile, node->m_pChildren[i]);
  }
}
bool
ResourceManager::serializeAnimation(const String& resourceName,
                                    const WString& fileToSave)
{
  if (m_animations.find(resourceName) != m_animations.end()) {
    File saveFile;
    saveFile.openFile(fileToSave, OPEN_TYPE::kWriteOnly | OPEN_TYPE::kBinary);
    if (saveFile.isOpen()) {
      auto sAnim = m_animations[resourceName];
      serializeFileStartData(saveFile, eRESOURCE_CODE::kAnimation, 0);

      float ticksPerSec = sAnim->getTicksPerSecond();
      saveFile.writeBytes(reinterpret_cast<Byte*>(&ticksPerSec), sizeof(float));
      float duration = sAnim->getDuration();
      saveFile.writeBytes(reinterpret_cast<Byte*>(&duration), sizeof(float));

      Vector<AnimNode> channels = sAnim->getChannels();
      SIZE_T channelsCount = channels.size();
      saveFile.writeBytes(reinterpret_cast<Byte*>(&channelsCount),
                          sizeof(SIZE_T));
      for (SIZE_T i = 0; i < channelsCount; ++i) {
        serializeString(saveFile, channels[i].m_name);

        saveFile.writeBytes(reinterpret_cast<Byte*>(&channels[i].m_positionKeysCount),
                            sizeof(uint32));
        saveFile.writeBytes(reinterpret_cast<Byte*>(&channels[i].m_rotationKeysCount),
                            sizeof(uint32));
        saveFile.writeBytes(reinterpret_cast<Byte*>(&channels[i].m_scalingKeysCount),
                            sizeof(uint32));

        saveFile.writeBytes(reinterpret_cast<Byte*>(channels[i].m_positionKeys.data()),
                            channels[i].m_positionKeysCount * sizeof(VectorKeyFrame));
        saveFile.writeBytes(reinterpret_cast<Byte*>(channels[i].m_rotationKeys.data()),
                            channels[i].m_rotationKeysCount * sizeof(QuatKeyFrame));
        saveFile.writeBytes(reinterpret_cast<Byte*>(channels[i].m_scalingKeys.data()),
                            channels[i].m_scalingKeysCount * sizeof(VectorKeyFrame));
      }

      serializeAnimationNode(saveFile, sAnim->getRootNode());

      saveFile.close();

      return true;
    }
  }
  
  return false;
}

bool
ResourceManager::loadSerializedTexture(File& fileToLoad,
                                       const String& resourceName,
                                       uint8 versionNum,
                                       uint8 sizeTSize)
{
  if (m_textures.find(resourceName) != m_textures.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return false;
  }

  if (fileToLoad.isOpen()) {
    SIZE_T readImagesCount = 0;
    loadSerializedSize(fileToLoad, readImagesCount, sizeTSize);

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
      if (versionNum > 0) {
        String imgPath;
        loadSerializedString(fileToLoad,imgPath, sizeTSize);
        readImages[i]->setPath(imgPath);
      }
    }

    SPtr<Texture> tex = GraphicsApi::instance().createTexturePtr();
    tex->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
      Point2D{ readImages[0]->getWidth(), readImages[0]->getHeight() });

    tex->loadImages(readImages);

    tex->setResourceName(resourceName);
    m_textures.insert(Pair<String, SPtr<Texture>>(resourceName, tex));

    return true;
  }
  return false;
}
bool
ResourceManager::loadSerializedMaterial(File& fileToLoad,
                                        const String& resourceName,
                                        uint8 /*versionNum*/,
                                        uint8 sizeTSize)
{  
  if (m_materials.find(resourceName) != m_materials.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return false;
  }

  if (fileToLoad.isOpen()) {
    SIZE_T readTexCount = 0;
    loadSerializedSize(fileToLoad, readTexCount, sizeTSize);

    Map<uint32, WPtr<Texture>> readTexsMap;
    for (SIZE_T i = 0; i < readTexCount; ++i) {
      uint32 texIndex = 0;
      fileToLoad.readBytes(reinterpret_cast<Byte*>(&texIndex), sizeof(uint32));
      String texName;
      loadSerializedString(fileToLoad, texName, sizeTSize);

      if (m_textures.find(texName) != m_textures.end()) {
        readTexsMap.insert(Pair<uint32, WPtr<Texture>>(texIndex,
                                                       m_textures[texName]));
      }
      else {
        readTexsMap.insert(Pair<uint32, WPtr<Texture>>(texIndex,
                                                       {}));
      }
    }
    SPtr<Material> mat = MemoryManager::instance().newPtr<Material>();
    mat->createMaterial(readTexsMap);

    mat->setResourceName(resourceName);
    m_materials.insert(Pair<String, SPtr<Material>>(resourceName, mat));

    return true;
  }
  return false;
}
void
loadSerializedMesh(File& fileToLoad, Mesh& meshToLoad, uint8 sizeTSize)
{
  uint8 vertexType = 0;
  fileToLoad.readBytes(reinterpret_cast<Byte*>(&vertexType),
                       sizeof(uint8));
                       
  if (vertexType == eVertexType::kComplex) {
    Vector<Triangle> trianglesArr;

    SIZE_T trianglesCount;
    loadSerializedSize(fileToLoad, trianglesCount, sizeTSize);
    trianglesArr.resize(trianglesCount);
    fileToLoad.readBytes(reinterpret_cast<Byte*>(trianglesArr.data()),
                         static_cast<uint32>(trianglesCount * sizeof(Triangle)));

    Vector<uint32> indicesArr;

    SIZE_T indicesCount;
    loadSerializedSize(fileToLoad, indicesCount, sizeTSize);
    indicesArr.resize(indicesCount);
    fileToLoad.readBytes(reinterpret_cast<Byte*>(indicesArr.data()),
                         static_cast<uint32>(indicesCount * sizeof(uint32)));

    meshToLoad.loadFromTrianglesArray(trianglesArr, indicesArr);
  }
  else if (vertexType == eVertexType::kControlPoints) {
    Vector<ComplexVertex> pointsArr;

    SIZE_T pointsCount;
    loadSerializedSize(fileToLoad, pointsCount, sizeTSize);
    pointsArr.resize(pointsCount);
    fileToLoad.readBytes(reinterpret_cast<Byte*>(pointsArr.data()),
                         static_cast<uint32>(pointsCount * sizeof(ComplexVertex)));

    meshToLoad.loadFromControlPoints(pointsArr);
  }
}
bool
ResourceManager::loadSerializedStaticMesh(File& fileToLoad,
                                          const String& resourceName,
                                          uint8 /*versionNum*/,
                                          uint8 sizeTSize)
{
  if (m_staticMeshes.find(resourceName) != m_staticMeshes.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return false;
  }

  if (fileToLoad.isOpen()) {
    SIZE_T meshesCount = 0;
    loadSerializedSize(fileToLoad, meshesCount, sizeTSize);

    Vector<Pair<Mesh, WPtr<Material>>> meshes;
    for (SIZE_T i = 0; i < meshesCount; ++i) {
      Mesh readMesh;
      loadSerializedMesh(fileToLoad, readMesh, sizeTSize);
      String matName;
      loadSerializedString(fileToLoad, matName, sizeTSize);
      if (m_materials.find(matName) != m_materials.end()) {
        meshes.emplace_back(Pair<Mesh, WPtr<Material>>(readMesh,
                                                       m_materials[matName]));
      }
      else {
        meshes.emplace_back(Pair<Mesh, WPtr<Material>>(readMesh,
                                                       {}));
      }
    }
    
    float sphereRadius = 0;
    fileToLoad.readBytes(reinterpret_cast<Byte*>(&sphereRadius),
                         sizeof(float));

    Vector3f boxMinVertex;
    fileToLoad.readBytes(reinterpret_cast<Byte*>(&boxMinVertex),
                         sizeof(Vector3f));
    Vector3f boxMaxVertex;
    fileToLoad.readBytes(reinterpret_cast<Byte*>(&boxMaxVertex),
                         sizeof(Vector3f));

    SPtr<StaticMesh> stMesh = MemoryManager::instance().newPtr<StaticMesh>();
    stMesh->loadFromMeshes(meshes, sphereRadius, boxMaxVertex, boxMinVertex);

    stMesh->setResourceName(resourceName);
    m_staticMeshes.insert(Pair<String, SPtr<StaticMesh>>(resourceName, stMesh));

    return true;
  }
  return false;
}
bool
ResourceManager::loadSerializedSkeleton(File& fileToLoad,
                                        const String& resourceName,
                                        uint8 /*versionNum*/,
                                        uint8 sizeTSize)
{
  if (m_skeletals.find(resourceName) != m_skeletals.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return false;
  }

  if (fileToLoad.isOpen()) {
    SIZE_T meshesCount = 0;
    loadSerializedSize(fileToLoad, meshesCount, sizeTSize);

    Vector<Vector<Bone>> bonesPerMesh;
    bonesPerMesh.resize(meshesCount);
    Vector<Matrix4f> globalInverseTransforms;
    globalInverseTransforms.resize(meshesCount);
    Vector<Map<String, uint32>> boneMaping;
    boneMaping.resize(meshesCount);
    Vector<uint32> numsBones;
    numsBones.resize(meshesCount);

    for (SIZE_T i = 0; i < meshesCount; ++i) {
      SIZE_T bonesCount;
      loadSerializedSize(fileToLoad, bonesCount, sizeTSize);
      bonesPerMesh[i].resize(bonesCount);
      for (SIZE_T j = 0; j < bonesCount; ++j) {
        loadSerializedString(fileToLoad,
                                   bonesPerMesh[i][j].m_name,
                                   sizeTSize);

        SIZE_T vertexWeightsCount;
        loadSerializedSize(fileToLoad, vertexWeightsCount, sizeTSize);
        bonesPerMesh[i][j].m_vertexWeights.resize(vertexWeightsCount);
        fileToLoad.readBytes(
          reinterpret_cast<Byte*>(bonesPerMesh[i][j].m_vertexWeights.data()),
          static_cast<uint32>(vertexWeightsCount * sizeof(VertexWeight)));
        
        fileToLoad.readBytes(
          reinterpret_cast<Byte*>(&bonesPerMesh[i][j].m_offsetMatrix),
          sizeof(Matrix4f));
        fileToLoad.readBytes(
          reinterpret_cast<Byte*>(&bonesPerMesh[i][j].m_finalTransformation),
          sizeof(Matrix4f));
      }

      fileToLoad.readBytes(reinterpret_cast<Byte*>(&globalInverseTransforms[i]),
                           sizeof(Matrix4f));

      SIZE_T bonesMapsCount;
      loadSerializedSize(fileToLoad, bonesMapsCount, sizeTSize);
      for (SIZE_T j = 0; j < bonesMapsCount; ++j) {
        String boneString;
        loadSerializedString(fileToLoad, boneString, sizeTSize);
        uint32 boneID;
        fileToLoad.readBytes(reinterpret_cast<Byte*>(&boneID),
                             sizeof(uint32));

        boneMaping[i].insert(Pair<String, uint32>(boneString, boneID));
      }

      fileToLoad.readBytes(reinterpret_cast<Byte*>(&numsBones[i]),
                           sizeof(uint32));
    }

    SPtr<Skeletal> skele = MemoryManager::instance().newPtr<Skeletal>();
    skele->loadFromData(bonesPerMesh,
                        globalInverseTransforms,
                        boneMaping,
                        numsBones);

    skele->setResourceName(resourceName);
    m_skeletals.insert(Pair<String, SPtr<Skeletal>>(resourceName, skele));

    return true;
  }
  return false;
}
void
loadSerializedBoneMesh(File& fileToLoad, BoneMesh& meshToLoad, uint8 sizeTSize)
{
  Vector<ComplexBigAnimVertex<4>> vertexArr;

  SIZE_T verticesCount;
  loadSerializedSize(fileToLoad, verticesCount, sizeTSize);
  vertexArr.resize(verticesCount);
  fileToLoad.readBytes(reinterpret_cast<Byte*>(vertexArr.data()),
          static_cast<uint32>(verticesCount * sizeof(ComplexBigAnimVertex<4>)));

  Vector<uint32> indicesArr;

  SIZE_T indicesCount;
  loadSerializedSize(fileToLoad, indicesCount, sizeTSize);
  indicesArr.resize(indicesCount);
  fileToLoad.readBytes(reinterpret_cast<Byte*>(indicesArr.data()),
                       static_cast<uint32>(indicesCount * sizeof(uint32)));

  meshToLoad.loadFromArray(vertexArr, indicesArr);
}
bool
ResourceManager::loadSerializedSkeletalMesh(File& fileToLoad,
                                            const String& resourceName,
                                            uint8 /*versionNum*/,
                                            uint8 sizeTSize)
{
  if (m_skeletalMeshes.find(resourceName) != m_skeletalMeshes.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return false;
  }

  if (fileToLoad.isOpen()) {
    String skeletonName;
    SPtr<Skeletal> skeleton = nullptr;
    loadSerializedString(fileToLoad, skeletonName, sizeTSize);
    if (m_skeletals.find(skeletonName) != m_skeletals.end()) {
      skeleton = m_skeletals[skeletonName];
    }

    SIZE_T meshesCount = 0;
    loadSerializedSize(fileToLoad, meshesCount, sizeTSize);

    Vector<Pair<BoneMesh, WPtr<Material>>> meshes;
    for (SIZE_T i = 0; i < meshesCount; ++i) {
      BoneMesh readMesh;
      loadSerializedBoneMesh(fileToLoad, readMesh, sizeTSize);
      String matName;
      loadSerializedString(fileToLoad, matName, sizeTSize);
      if (m_materials.find(matName) != m_materials.end()) {
        meshes.emplace_back(Pair<BoneMesh, WPtr<Material>>(readMesh,
                                                         m_materials[matName]));
      }
      else {
        meshes.emplace_back(Pair<BoneMesh, WPtr<Material>>(readMesh,
                                                           {}));
      }
    }
    
    float sphereRadius = 0;
    fileToLoad.readBytes(reinterpret_cast<Byte*>(&sphereRadius),
                         sizeof(float));

    Vector3f boxMinVertex;
    fileToLoad.readBytes(reinterpret_cast<Byte*>(&boxMinVertex),
                         sizeof(Vector3f));
    Vector3f boxMaxVertex;
    fileToLoad.readBytes(reinterpret_cast<Byte*>(&boxMaxVertex),
                         sizeof(Vector3f));

    SPtr<SkeletalMesh> skMesh = MemoryManager::instance().newPtr<SkeletalMesh>();
    skMesh->loadFromMeshes(meshes,
                           skeleton,
                           sphereRadius,
                           boxMaxVertex,
                           boxMinVertex);

    skMesh->setResourceName(resourceName);
    m_skeletalMeshes.insert(Pair<String, SPtr<SkeletalMesh>>(resourceName, skMesh));

    return true;
  }
  return false;
}
void
loadSerializedAnimationNode(File& fileToLoad, SPtr<Node>* node, uint8 sizeTSize)
{
  *node = MemoryManager::instance().newPtr<Node>();

  loadSerializedString(fileToLoad, (*node)->m_name, sizeTSize);

  fileToLoad.readBytes(reinterpret_cast<Byte*>(&(*node)->m_transformation),
                       sizeof(Matrix4f));

  fileToLoad.readBytes(reinterpret_cast<Byte*>(&(*node)->m_childrenCount),
                       sizeof(uint32));

  for (uint32 i = 0; i < (*node)->m_childrenCount; ++i) {
    SPtr<Node> childNode = nullptr;
    loadSerializedAnimationNode(fileToLoad, &childNode, sizeTSize);

    childNode->m_pParent = *node;
    (*node)->m_pChildren.push_back(childNode);
  }
}
bool
ResourceManager::loadSerializedAnimation(File& fileToLoad,
                                         const String& resourceName,
                                         uint8 /*versionNum*/,
                                         uint8 sizeTSize)
{
  if (m_animations.find(resourceName) != m_animations.end()) {
    Logger::instance().consoleLog("Resource already with this name");
    return false;
  }

  if (fileToLoad.isOpen()) {
    float ticksPerSec;
    fileToLoad.readBytes(reinterpret_cast<Byte*>(&ticksPerSec),
                         sizeof(float));
    float duration;
    fileToLoad.readBytes(reinterpret_cast<Byte*>(&duration),
                         sizeof(float));

    Vector<AnimNode> channels;
    SIZE_T channelsCount;
    loadSerializedSize(fileToLoad, channelsCount, sizeTSize);
    channels.resize(channelsCount);
    for (SIZE_T i = 0; i < channelsCount; ++i) {
      loadSerializedString(fileToLoad, channels[i].m_name, sizeTSize);
      
      fileToLoad.readBytes(reinterpret_cast<Byte*>(&channels[i].m_positionKeysCount),
                           sizeof(uint32));
      fileToLoad.readBytes(reinterpret_cast<Byte*>(&channels[i].m_rotationKeysCount),
                           sizeof(uint32));
      fileToLoad.readBytes(reinterpret_cast<Byte*>(&channels[i].m_scalingKeysCount),
                           sizeof(uint32));

      channels[i].m_positionKeys.resize(channels[i].m_positionKeysCount);
      fileToLoad.readBytes(reinterpret_cast<Byte*>(channels[i].m_positionKeys.data()),
                           channels[i].m_positionKeysCount * sizeof(VectorKeyFrame));
      channels[i].m_rotationKeys.resize(channels[i].m_rotationKeysCount);
      fileToLoad.readBytes(reinterpret_cast<Byte*>(channels[i].m_rotationKeys.data()),
                           channels[i].m_rotationKeysCount * sizeof(QuatKeyFrame));
      channels[i].m_scalingKeys.resize(channels[i].m_scalingKeysCount);
      fileToLoad.readBytes(reinterpret_cast<Byte*>(channels[i].m_scalingKeys.data()),
                           channels[i].m_scalingKeysCount * sizeof(VectorKeyFrame));
    }

    SPtr<Node> rootNode = nullptr;
    loadSerializedAnimationNode(fileToLoad, &rootNode, sizeTSize);

    SPtr<Animation> sAnim = MemoryManager::instance().newPtr<Animation>();
    sAnim->loadFromData(ticksPerSec,
                        duration,
                        channels,
                        rootNode);

    sAnim->setResourceName(resourceName);
    m_animations.insert(Pair<String, SPtr<Animation>>(resourceName, sAnim));

    return true;
  }
  return false;
}
}