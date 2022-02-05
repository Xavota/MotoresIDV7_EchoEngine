#include "eeSkeletalMesh.h"

#pragma warning(push, 0)   
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)

#include <eeLogger.h>

#include <eeMemoryManager.h>

#include <eeQuaternion.h>
#include <eeMath.h>

#include "eeResourceManager.h"

#include "eeSkeletal.h"
#include "eeMesh.h"

namespace eeEngineSDK{
bool
SkeletalMesh::loadFromFile(const String& fileName,
                           SPtr<Skeletal> skMesh,
                           const Vector<SPtr<Texture>>& textures)
{
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

  /****************************************************************************/
  /*                                                                          */
  /*                                Load Mesh                                 */
  /*                                                                          */
  /****************************************************************************/

  /* Vertices */
  Vector3f maxBound(-99999.99f, -99999.99f, -99999.99f);
  Vector3f minBound(99999.99f, 99999.99f, 99999.99f);
  float maxDistance = 0.0f;
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

        maxDistance = distance > maxDistance ? distance : maxDistance;
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
    if (skMesh->getBonesDataForMesh(i, bones))
    {
      if (!bones.empty()) {
        for (uint32 j = 0; j < bones.size(); j++) {
          Bone bone = bones[j];
          bool yes = false;
          for (auto vw : bone.m_vertexWeights) {
            yes = false;
            for (uint32 l = 0; l < 16; l++) {
              if (vertices[vw.m_vertexID].boneWeights[l] == 0.0f) {
                vertices[vw.m_vertexID].boneIndices[l] = j;
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
    auto& memoryMan = MemoryManager::instance();
    
    SPtr<Mesh> mesh = memoryMan.newPtr<Mesh>();
    mesh->loadFromArray(vertices, indices);
    m_meshes.emplace_back
    (
      make_pair
      (
        mesh,
        textures.size() > AssimpMesh->mMaterialIndex
      ? textures[AssimpMesh->mMaterialIndex]
      : resourseManager.getResourceTexture("Default")
      )
    );

    vertices.clear();
    indices.clear();
  }

  m_skeleton = skMesh;

  m_boundSphere.setCenter({ 0.0f, 0.0f, 0.0f });
  m_boundSphere.setRadious(maxDistance);

  m_boundCube.setA({ minBound.x, maxBound.y, maxBound.z });
  m_boundCube.setSize(maxBound - minBound);

  delete importer;
  return true;
}
bool
SkeletalMesh::loadFromMeshes(const Vector<SPtr<Mesh>>& meshes)
{
  if (meshes.empty()) {
    Logger::instance().ConsoleLog("Empty info loading model");
    return false;
  }

  auto& resourseManager = ResourceManager::instance();

  for (const auto& m : meshes) {
    m_meshes.emplace_back
    (
      Pair<SPtr<Mesh>, SPtr<Texture>>
      (
        m,
        resourseManager.getResourceTexture("Default")
      )
    );
  }
  return true;
}
bool
SkeletalMesh::loadFromMeshes(const Vector<Pair<SPtr<Mesh>, SPtr<Texture>>>& meshes)
{
  if (meshes.empty()) {
    Logger::instance().ConsoleLog("Empty info loading model");
    return false;
  }

  m_meshes = meshes;
  return true;
}
Vector<Pair<SPtr<Mesh>, SPtr<Texture>>>
SkeletalMesh::getMeshes()
{
  return m_meshes;
}
Vector<SPtr<Texture>>
SkeletalMesh::getTextures()
{
  Vector<SPtr<Texture>> textures;
  for (auto& m : m_meshes) {
    textures.push_back(m.second);
  }
  return textures;
}
void
SkeletalMesh::setTexture(SPtr<Texture> texture, int32 index)
{
  if (static_cast<int32>(m_meshes.size()) > index) {
    m_meshes[index].second = texture;
  }
}
String
SkeletalMesh::getName()
{
  return m_name;
}
const
Sphere& SkeletalMesh::getBoundingSphere()
{
  return m_boundSphere;
}
const
BoxAAB& SkeletalMesh::getBoundingBox()
{
  return m_boundCube;
}
}