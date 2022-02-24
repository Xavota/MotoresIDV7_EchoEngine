#include "eeResourceManager.h"

#pragma warning(push, 0)   
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)
#include <eeLogger.h>
#include <eeMemoryManager.h>
#include <eeMath.h>

#include "eeMesh.h"
#include "eeTexture.h"
#include "eeMaterial.h"
#include "eeVertexShader.h"
#include "eePixelShader.h"
#include "eeGraficsApi.h"
#include "eeSkeletalMesh.h"
#include "eeSkeletal.h"
#include "eeAnimation.h"
#include "eeImage.h"

namespace eeEngineSDK
{
SPtr<StaticMesh>
loadStaticMeshFromAssimp(const aiScene* scene,
                         const String& name,
                         const Vector<SPtr<Material>>& textures)
{
  SPtr<StaticMesh> outStaticMesh = MemoryManager::instance().newPtr<StaticMesh>();

  Vector<Pair<Mesh, SPtr<Material>>> meshes;

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

      vertices.push_back(v);
    }

    //---Tan/Bin
    for (uint32 j = 0; j * 3 + 2 < scene->mMeshes[i]->mNumVertices; ++j)
    {
      aiVector3D deltaPos1 = scene->mMeshes[i]->mVertices[j * 3 + 1] - scene->mMeshes[i]->mVertices[j * 3];
      aiVector3D deltaPos2 = scene->mMeshes[i]->mVertices[j * 3 + 2] - scene->mMeshes[i]->mVertices[j * 3];
      aiVector3D deltaUV1 = scene->mMeshes[i]->mTextureCoords[0][j * 3 + 1] - scene->mMeshes[i]->mTextureCoords[0][j * 3];
      aiVector3D deltaUV2 = scene->mMeshes[i]->mTextureCoords[0][j * 3 + 2] - scene->mMeshes[i]->mTextureCoords[0][j * 3];
      float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
      aiVector3D tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
      aiVector3D bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

      vertices[static_cast<SIZE_T>(j) * 3 + 0].binormal.x = bitangent.x;
      vertices[static_cast<SIZE_T>(j) * 3 + 0].binormal.y = bitangent.y;
      vertices[static_cast<SIZE_T>(j) * 3 + 0].binormal.z = bitangent.z;
      vertices[static_cast<SIZE_T>(j) * 3 + 0].binormal.w = 0.0f;

      vertices[static_cast<SIZE_T>(j) * 3 + 1].binormal.x = bitangent.x;
      vertices[static_cast<SIZE_T>(j) * 3 + 1].binormal.y = bitangent.y;
      vertices[static_cast<SIZE_T>(j) * 3 + 1].binormal.z = bitangent.z;
      vertices[static_cast<SIZE_T>(j) * 3 + 1].binormal.w = 0.0f;

      vertices[static_cast<SIZE_T>(j) * 3 + 2].binormal.x = bitangent.x;
      vertices[static_cast<SIZE_T>(j) * 3 + 2].binormal.y = bitangent.y;
      vertices[static_cast<SIZE_T>(j) * 3 + 2].binormal.z = bitangent.z;
      vertices[static_cast<SIZE_T>(j) * 3 + 2].binormal.w = 0.0f;


      vertices[static_cast<SIZE_T>(j) * 3 + 0].tangent.x = tangent.x;
      vertices[static_cast<SIZE_T>(j) * 3 + 0].tangent.y = tangent.y;
      vertices[static_cast<SIZE_T>(j) * 3 + 0].tangent.z = tangent.z;
      vertices[static_cast<SIZE_T>(j) * 3 + 0].tangent.w = 0.0f;

      vertices[static_cast<SIZE_T>(j) * 3 + 1].tangent.x = tangent.x;
      vertices[static_cast<SIZE_T>(j) * 3 + 1].tangent.y = tangent.y;
      vertices[static_cast<SIZE_T>(j) * 3 + 1].tangent.z = tangent.z;
      vertices[static_cast<SIZE_T>(j) * 3 + 1].tangent.w = 0.0f;

      vertices[static_cast<SIZE_T>(j) * 3 + 2].tangent.x = tangent.x;
      vertices[static_cast<SIZE_T>(j) * 3 + 2].tangent.y = tangent.y;
      vertices[static_cast<SIZE_T>(j) * 3 + 2].tangent.z = tangent.z;
      vertices[static_cast<SIZE_T>(j) * 3 + 2].tangent.w = 0.0f;
    }/**/



    Vector<uint32> indices;

    for (uint32 j = 0; j < AssimpMesh->mNumFaces; ++j) {
      for (uint32 k = 0; k < AssimpMesh->mFaces[j].mNumIndices; ++k) {
        indices.push_back(AssimpMesh->mFaces[j].mIndices[k]);
      }
    }

    auto& resourseManager = ResourceManager::instance();

    meshes.emplace_back
    (
      Pair<Mesh, SPtr<Material>>
      (
        Mesh(),
        textures.size() > AssimpMesh->mMaterialIndex
        ? textures[AssimpMesh->mMaterialIndex]
        : resourseManager.getResourceMaterial("Default_mat")
      )
    );
    meshes[meshes.size() - 1].first.loadFromArray(vertices, indices);

    indices.clear();
    vertices.clear();
  }

  outStaticMesh->loadFromMeshes(meshes, name, furtherPosition, maxBound, minBound);

  return outStaticMesh;
}
SPtr<SkeletalMesh>
loadSkeletalMeshFromAssimp(const aiScene* scene,
                           SPtr<Skeletal> skeleton,
                           const String& name,
                           const Vector<SPtr<Material>>& textures)
{
  SPtr<SkeletalMesh> outSkeletalMesh = MemoryManager::instance().newPtr<SkeletalMesh>();

  Vector<Pair<Mesh, SPtr<Material>>> meshes;

  Vector3f maxBound(-99999.99f, -99999.99f, -99999.99f);
  Vector3f minBound(99999.99f, 99999.99f, 99999.99f);
  Vector3f furtherPosition = Vector3f(0.0f, 0.0f, 0.0f);
  for (uint32 i = 0; i < scene->mNumMeshes; ++i) {
    Vector<SimpleBigAnimVertex<6>> vertices;
    aiMesh* AssimpMesh = scene->mMeshes[i];

    for (uint32 j = 0; j < AssimpMesh->mNumVertices; ++j) {
      SimpleBigAnimVertex<6> v;
      memset(&v, 0, sizeof(SimpleBigAnimVertex<6>));
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

      vertices.push_back(v);
    }

    // Tangents/Bitangents
    /*for (int32 j = 0; j * 3 + 2 < scene->mMeshes[i]->mNumVertices; ++j)
    {
      aiVector3D deltaPos1 = scene->mMeshes[i]->mVertices[j * 3 + 1] - scene->mMeshes[i]->mVertices[j * 3];
      aiVector3D deltaPos2 = scene->mMeshes[i]->mVertices[j * 3 + 2] - scene->mMeshes[i]->mVertices[j * 3];
      aiVector3D deltaUV1 = scene->mMeshes[i]->mTextureCoords[0][j * 3 + 1] - scene->mMeshes[i]->mTextureCoords[0][j * 3];
      aiVector3D deltaUV2 = scene->mMeshes[i]->mTextureCoords[0][j * 3 + 2] - scene->mMeshes[i]->mTextureCoords[0][j * 3];
      float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
      aiVector3D tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
      aiVector3D bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

      vertices[j * 3 + 0].Binormal.x = bitangent.x;
      vertices[j * 3 + 0].Binormal.y = bitangent.y;
      vertices[j * 3 + 0].Binormal.z = bitangent.z;

      vertices[j * 3 + 1].Binormal.x = bitangent.x;
      vertices[j * 3 + 1].Binormal.y = bitangent.y;
      vertices[j * 3 + 1].Binormal.z = bitangent.z;

      vertices[j * 3 + 2].Binormal.x = bitangent.x;
      vertices[j * 3 + 2].Binormal.y = bitangent.y;
      vertices[j * 3 + 2].Binormal.z = bitangent.z;


      vertices[j * 3 + 0].Tangente.x = tangent.x;
      vertices[j * 3 + 0].Tangente.y = tangent.y;
      vertices[j * 3 + 0].Tangente.z = tangent.z;

      vertices[j * 3 + 1].Tangente.x = tangent.x;
      vertices[j * 3 + 1].Tangente.y = tangent.y;
      vertices[j * 3 + 1].Tangente.z = tangent.z;

      vertices[j * 3 + 2].Tangente.x = tangent.x;
      vertices[j * 3 + 2].Tangente.y = tangent.y;
      vertices[j * 3 + 2].Tangente.z = tangent.z;
    }/**/

    Vector<Bone> bones;
    if (skeleton && skeleton->getBonesDataForMesh(i, bones)) {
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
              Logger::instance().ConsoleLog("No more bone space");
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
      Pair<Mesh, SPtr<Material>>
      (
        Mesh(),
        static_cast<uint32>(textures.size()) > AssimpMesh->mMaterialIndex
        ? textures[AssimpMesh->mMaterialIndex]
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
                  Vector<Map<String, uint32>> boneMappings,
                  Vector<Matrix4f> globalInverseTransforms,
                  Vector<Vector<Bone>>& outBonesPerMesh)
{
  String NodeName(pNode->mName.data);

  //trans
  float m[16];
  memcpy(m, &pNode->mTransformation.a1, 16 * sizeof(float));
  Matrix4f NodeTransformation = Matrix4f(m);

  Matrix4f GlobalTransformation = ParentTransform * NodeTransformation;


  if (boneMappings[meshIndex].find(NodeName) != boneMappings[meshIndex].end()) {
    uint32 BoneIndex = boneMappings[meshIndex][NodeName];

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
              Vector<Map<String, uint32>> boneMappings,
              Vector<Matrix4f> globalInverseTransforms,
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
storeNodes(aiNode* current, SPtr<Node> storage)
{
  auto& memoryMan = MemoryManager::instance();

  storage->m_name = current->mName.C_Str();
  float m[16];
  memcpy(m, &current->mTransformation.a1, 16 * sizeof(float));
  storage->m_transformation = Matrix4f(m);

  storage->m_childrenCount = current->mNumChildren;

  for (uint32 i = 0; i < storage->m_childrenCount; ++i) {
    storage->m_children.push_back(memoryMan.newPtr<Node>());
    storeNodes(current->mChildren[i], storage->m_children[i]);
    storage->m_children[i]->m_parent = storage;
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
ResourceManager::importResourceFromFile(const String& fileName,
                                        uint16 importFlags)
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

  // To lower the file extension
  for (char& c : fileExtension) {
    c = (c >= 'A' && c <= 'Z' ? c + 32 : c);
  }

  /* LOAD RESOURCES FROM THE FILE */
  // If is a texture extension
  if (fileExtension == "png"  || fileExtension == "jpg"
   || fileExtension == "tga"  || fileExtension == "bmp"
   || fileExtension == "tiff") {
    // Check flags
    if (importFlags == IMPORT_FLAGS::kNone
    ||  Math::hasFlag(importFlags, IMPORT_FLAGS::kImportTextures)
    || (Math::hasFlag(importFlags, IMPORT_FLAGS::kImportAll)
    &&  Math::hasFlag(importFlags, IMPORT_FLAGS::kNotImportTextures))) {
      // Load texture from file
      loadTextureFromFile(fileName, name + "_tex");
    }
  }
  // If is a 3D model extension
  else if (fileExtension == "obj"     || fileExtension == "fbx"
        || fileExtension == "md5mesh" || fileExtension == "md5anim") {
    // Load Assimp Scene
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

    // Use the scene
    Vector<SPtr<Material>> materials;
    if (scene->HasTextures()
    &&  importFlags == IMPORT_FLAGS::kNone
    ||  Math::hasFlag(importFlags, IMPORT_FLAGS::kImportTextures)
    || (Math::hasFlag(importFlags, IMPORT_FLAGS::kImportAll)
    &&  Math::hasFlag(importFlags, IMPORT_FLAGS::kNotImportTextures))) {
      // Load textures
    }

    if (scene->mRootNode
    && (importFlags == IMPORT_FLAGS::kNone
    ||  Math::hasFlag(importFlags, IMPORT_FLAGS::kImportSkeletalMeshes)
    || (Math::hasFlag(importFlags, IMPORT_FLAGS::kImportAll)
    &&  Math::hasFlag(importFlags, IMPORT_FLAGS::kNotImportSkeletalMeshes)))) {
      // Load skeleton
      SPtr<Skeletal> skeleton = loadSkeletalFromAssimp(scene, name);
      if (skeleton) {
        m_skeletals.insert(Pair<String, SPtr<Skeletal>>(name + "_sk", skeleton));
      }
      
      if (scene->HasMeshes()) {
        // Load skeletal mesh
        SPtr<SkeletalMesh> skMesh =
        //loadSkeletalMeshFromAssimp(scene, skeleton, name + "_skm", textures);
        loadSkeletalMeshFromAssimp(scene, skeleton, name + "_skm", materials);
        if (skMesh) {
          m_skeletalMeshes.insert(Pair<String, SPtr<SkeletalMesh>>(name + "_skm", skMesh));
        }
      }
    }
    else if (importFlags == IMPORT_FLAGS::kNone
         ||  Math::hasFlag(importFlags, IMPORT_FLAGS::kImportStaticMeshes)
         || (Math::hasFlag(importFlags, IMPORT_FLAGS::kImportAll)
         &&  Math::hasFlag(importFlags, IMPORT_FLAGS::kNotImportStaticMeshes))) {
      if (scene->HasMeshes()) {
        // Load static mesh
        SPtr<StaticMesh> stMesh =
        loadStaticMeshFromAssimp(scene, name + "_sm", materials);
        if (stMesh) {
          m_staticMeshes.insert(Pair<String, SPtr<StaticMesh>>(name + "_sm", stMesh));
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
        String animName = name + "_anim_" + scene->mAnimations[i]->mName.C_Str();
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
SPtr<Texture>
ResourceManager::loadTextureFromFile(const String& fileName,
                                     const String resourceName)
{
  if (m_textures.find(resourceName) != m_textures.end()) {
    Logger::instance().ConsoleLog("Resource already with this name");
    return nullptr;
  }

  if (fileName.empty()) {
    Logger::instance().ConsoleLog("Empty info loading texture");
    return nullptr;
  }

  SPtr<Image> tempImg = MemoryManager::instance().newPtr<Image>();
  if (!tempImg->loadFromFile(fileName)) {
    return nullptr;
  }

  SPtr<Texture> tex = GraphicsApi::instance().createTexturePtr();
  tex->create2D(eeEngineSDK::eTEXTURE_BIND_FLAGS::kShaderResource,
                { tempImg->getWidth(), tempImg->getHeight() });

  tex->loadImages({ tempImg });

  m_textures.insert(Pair<String, SPtr<Texture>>(resourceName, tex));
  return m_textures[resourceName];
}
SPtr<Material>
ResourceManager::loadMaterialFromTextures(SPtr<Texture> diffuse,
                                          SPtr<Texture> normalMap,
                                          const String resourceName)
{
  if (m_textures.find(resourceName) != m_textures.end()) {
    Logger::instance().ConsoleLog("Resource already with this name");
    return nullptr;
  }

  SPtr<Material> mat =
  MemoryManager::instance().newPtr<Material>(diffuse, normalMap);

  m_materials.insert(Pair<String, SPtr<Material>>(resourceName, mat));
  return m_materials[resourceName];
}
SPtr<StaticMesh>
ResourceManager::loadStaticMeshFromFile(const String& fileName,
                                        const String resourceName,
                                        const Vector<SPtr<Material>>& textures)
{
  if (m_staticMeshes.find(resourceName) != m_staticMeshes.end()) {
    Logger::instance().ConsoleLog("Resource already with this name");
    return nullptr;
  }

  if (fileName.empty()) {
    Logger::instance().ConsoleLog("Empty info loading static mesh");
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

  SPtr<StaticMesh> stMesh =
  loadStaticMeshFromAssimp(scene, resourceName, textures);
  delete importer;
  if (stMesh) {
    m_staticMeshes.insert(Pair<String, SPtr<StaticMesh>>(resourceName, stMesh));
    return m_staticMeshes[resourceName];
  }

  return nullptr;
}
SPtr<StaticMesh>
ResourceManager::loadStaticMeshFromMeshesArray(const Vector<Mesh>& meshes,
                                               const String resourceName,
                                               const Vector3f& furtherVertexPosition,
                                               const Vector3f& maxCoordinate,
                                               const Vector3f& minCoordinate)
{
  if (m_staticMeshes.find(resourceName) != m_staticMeshes.end()) {
    Logger::instance().ConsoleLog("Resource already with this name");
    return nullptr;
  }

  if (meshes.empty()) {
    Logger::instance().ConsoleLog("Empty info loading static mesh");
    return nullptr;
  }

  SPtr<StaticMesh> staticMesh = MemoryManager::instance().newPtr<StaticMesh>();
  if (!staticMesh->loadFromMeshes(meshes,
                                 resourceName,
                                 furtherVertexPosition,
                                 maxCoordinate,
                                 minCoordinate)) {
    return nullptr;
  }

  m_staticMeshes.insert(Pair<String, SPtr<StaticMesh>>(resourceName, staticMesh));
  return m_staticMeshes[resourceName];
}
SPtr<StaticMesh>
ResourceManager::loadStaticMeshFromMeshesArray(
                                const Vector<Pair<Mesh, SPtr<Material>>>& meshes,
                                const String resourceName,
                                const Vector3f& furtherVertexPosition,
                                const Vector3f& maxCoordinate,
                                const Vector3f& minCoordinate)
{
  if (m_staticMeshes.find(resourceName) != m_staticMeshes.end()) {
    Logger::instance().ConsoleLog("Resource already with this name");
    return nullptr;
  }

  if (meshes.empty()) {
    Logger::instance().ConsoleLog("Empty info loading static mesh");
    return nullptr;
  }

  SPtr<StaticMesh> staticMesh = MemoryManager::instance().newPtr<StaticMesh>();
  if (!staticMesh->loadFromMeshes(meshes,
                                  resourceName,
                                  furtherVertexPosition,
                                  maxCoordinate,
                                  minCoordinate)) {
    return nullptr;
  }
  
  m_staticMeshes.insert(Pair<String, SPtr<StaticMesh>>(resourceName, staticMesh));
  return m_staticMeshes[resourceName];
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

  SPtr<Skeletal> skeleton = loadSkeletalFromAssimp(scene, resourceName);
  delete importer;
  if (skeleton)
  {
    m_skeletals.insert(Pair<String, SPtr<Skeletal>>(resourceName, skeleton));
    return m_skeletals[resourceName];
  }
  return nullptr;
}

SPtr<SkeletalMesh>
ResourceManager::loadSkeletalMeshFromFile(const String& fileName,
                                          const String& resourceName,
                                          const SPtr<Skeletal> skeleton,
                                          const Vector<SPtr<Material>>& textures)
{
  if (m_skeletalMeshes.find(resourceName) != m_skeletalMeshes.end()) {
    Logger::instance().ConsoleLog("Resource already with this name");
    return nullptr;
  }
  
  if (fileName.empty()) {
    Logger::instance().ConsoleLog("Empty info loading skeletal mesh");
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
  
  SPtr<Skeletal> skeletonBackup = nullptr;
  if (!skeleton) {
    skeletonBackup = loadSkeletalFromFile(fileName, resourceName + "_sk");
  }
  else {
    skeletonBackup = skeleton;
  }
  
  if (!skeletonBackup) {
    delete importer;
    return nullptr;
  }
  
  SPtr<SkeletalMesh> skMesh =
  loadSkeletalMeshFromAssimp(scene, skeleton, resourceName, textures);
  delete importer;
  if (skMesh) {
    m_skeletalMeshes.insert(Pair<String, SPtr<SkeletalMesh>>(resourceName, skMesh));
    return m_skeletalMeshes[resourceName];
  }
  return nullptr;
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

  SPtr<Animation> anim = loadOneAnimationFromAssimp(scene, animIndex, resourceName);
  delete importer;
  if (anim) {
    m_animations.insert(Pair<String, SPtr<Animation>>(resourceName, anim));
    return m_animations[resourceName];
  }
  return nullptr;
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

  m_vertexShaders.insert(Pair<String, SPtr<VertexShader>>(resourceName, shader));
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

  m_vertexShaders.insert(Pair<String, SPtr<VertexShader>>(resourceName, shader));
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

  m_pixelShaders.insert(Pair<String, SPtr<PixelShader>>(resourceName, shader));
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

  m_pixelShaders.insert(Pair<String, SPtr<PixelShader>>(resourceName, shader));
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
SPtr<Material>
ResourceManager::getResourceMaterial(const String& resourceName)
{
  if (m_materials.find(resourceName) != m_materials.end()) {
    return m_materials[resourceName];
  }
  return nullptr;
}
SPtr<StaticMesh>
ResourceManager::getResourceStaticMesh(const String& resourceName)
{
  if (m_staticMeshes.find(resourceName) != m_staticMeshes.end()) {
    return m_staticMeshes[resourceName];
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
}