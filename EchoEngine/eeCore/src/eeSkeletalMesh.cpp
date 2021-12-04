#include "eeSkeletalMesh.h"
#include "eeConstantBuffer.h"
#include "eeGraficsApi.h"
#pragma warning(push, 0)   
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)

namespace eeEngineSDK{
Bone::Bone(String name,
           Vector<VertexWeight> vertexWeights,
           Matrix4f offsetMatrix)
{
  m_name = name;
  m_vertexWeights = vertexWeights;
  m_offsetMatrix = offsetMatrix;
}
Bone::~Bone()
{
}
void
Bone::addBoneData(VertexWeight vw)
{
  m_vertexWeights.push_back(vw);
}


bool
SkeletalMesh::loadFromFile(String fileName)
{
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
    return false;
  }
  scene->mRootNode->mChildren[1]->mChildren;

  for (int32 i = 0; i < scene->mNumMeshes; i++)
  {
    m_bonesPerMesh.push_back(Vector<Bone>(100));
    m_boneMappings.push_back(Map<String, int32>());
    m_numsBones.push_back(0);

    aiMatrix4x4 globalTransform = scene->mRootNode->mTransformation;
    globalTransform.Inverse();
    m_globalInverseTransforms.push_back(
      Matrix4f(&globalTransform.a1));

    if (scene->mMeshes[i]->HasBones())
    {
      for (int32 j = 0; j < scene->mMeshes[i]->mNumBones; j++)
      {
        uint32 boneIndex = 0;
        String name = scene->mMeshes[i]->mBones[j]->mName.C_Str();

        if (m_boneMappings[i].find(name) == m_boneMappings[i].end())
        {
          boneIndex = m_numsBones[i];
          m_numsBones[i]++;
        }
        else
        {
          boneIndex = m_boneMappings[i][name];
        }

        m_boneMappings[i][name] = boneIndex;

        m_bonesPerMesh[i][boneIndex].m_name = name;
        m_bonesPerMesh[i][boneIndex].m_offsetMatrix =
              Matrix4f(&scene->mMeshes[i]->mBones[boneIndex]->mOffsetMatrix.a1);
        m_bonesPerMesh[i][boneIndex].m_finalTransformation =
                                    m_bonesPerMesh[i][boneIndex].m_offsetMatrix;
        for (int32 k = 0; k < scene->mMeshes[i]->mBones[j]->mNumWeights; k++)
        {
          uint32 vertexID =
                            scene->mMeshes[i]->mBones[j]->mWeights[k].mVertexId;
          float weight = scene->mMeshes[i]->mBones[j]->mWeights[k].mWeight;

          m_bonesPerMesh[i][boneIndex].addBoneData({ vertexID, weight });
        }
      }
    }
  }

  for (int i = 0; i < scene->mNumMeshes; i++)
  {
    boneTransform(scene->mRootNode, i);
  }

  m_matricesBuffer = GraphicsApi::instance().createConstantBufferPtr();
  m_matricesBuffer->initData(100 * sizeof(Matrix4f), sizeof(Matrix4f), nullptr);

  return true;
}
void
SkeletalMesh::boneTransform(const aiNode* root, int meshIndex)
{
  readNodeHeirarchy(root, Matrix4f::IDENTITY, meshIndex);
}
void
SkeletalMesh::readNodeHeirarchy(const aiNode* pNode,
                                const Matrix4f& ParentTransform,
                                int meshIndex)
{
  String NodeName(pNode->mName.data);

  //trans
  float m[16];
  memcpy(m, &pNode->mTransformation.a1, 16 * sizeof(float));
  Matrix4f NodeTransformation = Matrix4f(m);

  Matrix4f GlobalTransformation = ParentTransform * NodeTransformation;


  if (m_boneMappings[meshIndex].find(NodeName) != m_boneMappings[meshIndex].end())
  {
    uint32 BoneIndex = m_boneMappings[meshIndex][NodeName];

    m_bonesPerMesh[meshIndex][BoneIndex].m_finalTransformation =
                          m_globalInverseTransforms[meshIndex] *
                          GlobalTransformation                 *
                          m_bonesPerMesh[meshIndex][BoneIndex].m_offsetMatrix;
  }

  for (int i = 0; i < pNode->mNumChildren; i++)
  {
    readNodeHeirarchy(pNode->mChildren[i], GlobalTransformation, meshIndex);
  }
}
Vector<Vector<Bone>>&
SkeletalMesh::getBonesData()
{
  return m_bonesPerMesh;
}
const Vector<Bone>&
SkeletalMesh::getBonesDataForMesh(int32 index) const
{
  if (m_bonesPerMesh.size() > index)
    return m_bonesPerMesh[index];
  else
    return Vector<Bone>();
}

Vector<Map<String, int32>>&
SkeletalMesh::getBoneMapping()
{
  return m_boneMappings;
}

Vector<Matrix4f>&
SkeletalMesh::getGlobalInverseTransforms()
{
  return m_globalInverseTransforms;
}

Vector<Matrix4f>
SkeletalMesh::getBonesMatrices(int meshNum)
{
  Vector<Matrix4f> bonesMatrices(100);
  if (m_bonesPerMesh.size() > meshNum)
  {
    for (int i = 0; i < m_bonesPerMesh[meshNum].size(); i++)
    {
      //bonesMatrices[i] = m_bonesPerMesh[meshNum][i].m_offsetMatrix;
      if (i >= bonesMatrices.size())
      {
        break;
      }
      bonesMatrices[i] = m_bonesPerMesh[meshNum][i].m_finalTransformation;
    }
  }

  return bonesMatrices;
}
void
SkeletalMesh::use(int meshNum)
{
  Vector<Matrix4f> mats = getBonesMatrices(meshNum);
  m_matricesBuffer->updateData(reinterpret_cast<Byte*>(mats.data()));
  m_matricesBuffer->setInVertex(3);
}
}