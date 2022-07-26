#include "eeSkeletal.h"

#pragma warning(push, 0)   
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)

#include <eeLogger.h>

#include "eeConstantBuffer.h"
#include "eeGraficsApi.h"

namespace eeEngineSDK{
Bone::Bone(const String& name,
           const Vector<VertexWeight>& vertexWeights,
           Matrix4f offsetMatrix)
 : m_name(name),
   m_vertexWeights(vertexWeights),
   m_offsetMatrix(offsetMatrix)
{}
void
Bone::addBoneData(VertexWeight vw)
{
  m_vertexWeights.push_back(vw);
}

Skeletal::Skeletal(const Vector<Vector<Bone>>& bonesPerMesh,
                   const Vector<Matrix4f>& globalInverseTransforms,
                   const Vector<Map<String, uint32>>& boneMappings,
                   const Vector<uint32>& numsBones,
                   const String& name)
{
  loadFromData(bonesPerMesh,
               globalInverseTransforms,
               boneMappings,
               numsBones,
               name);
}
void
Skeletal::boneTransform(const aiNode* root, uint32 meshIndex)
{
  readNodeHeirarchy(root, Matrix4f::kIDENTITY, meshIndex);
}
void
Skeletal::readNodeHeirarchy(const aiNode* pNode,
                            const Matrix4f& ParentTransform,
                            SIZE_T meshIndex)
{
  String NodeName(pNode->mName.data);

  //trans
  float m[16];
  memcpy(m, &pNode->mTransformation.a1, 16 * sizeof(float));
  Matrix4f NodeTransformation = Matrix4f(m);

  Matrix4f GlobalTransformation = ParentTransform * NodeTransformation;


  if (m_boneMappings[meshIndex].find(NodeName) != m_boneMappings[meshIndex].end()) {
    uint32 BoneIndex = m_boneMappings[meshIndex][NodeName];

    m_bonesPerMesh[meshIndex][BoneIndex].m_finalTransformation =
                          m_globalInverseTransforms[meshIndex]
                        * GlobalTransformation
                        * m_bonesPerMesh[meshIndex][BoneIndex].m_offsetMatrix;
  }

  for (uint32 i = 0; i < pNode->mNumChildren; i++) {
    readNodeHeirarchy(pNode->mChildren[i], GlobalTransformation, meshIndex);
  }
}
bool
Skeletal::loadFromData(const Vector<Vector<Bone>>& bonesPerMesh,
                       const Vector<Matrix4f>& globalInverseTransforms,
                       const Vector<Map<String, uint32>>& boneMappings,
                       const Vector<uint32>& numsBones,
                       const String& name)
{
  m_bonesPerMesh = bonesPerMesh;
  m_globalInverseTransforms = globalInverseTransforms;
  m_boneMappings = boneMappings;
  m_numsBones = numsBones;

  m_name = name;

  return true;
}
Vector<Vector<Bone>>&
Skeletal::getBonesData()
{
  return m_bonesPerMesh;
}
bool
Skeletal::getBonesDataForMesh(SIZE_T index, Vector<Bone>& outBoneData) const
{
  if (m_bonesPerMesh.size() > index) {
    outBoneData = m_bonesPerMesh[index];
    return true;
  }

  return false;
}

Vector<Map<String, uint32>>&
Skeletal::getBoneMapping()
{
  return m_boneMappings;
}

Vector<Matrix4f>&
Skeletal::getGlobalInverseTransforms()
{
  return m_globalInverseTransforms;
}

Vector<Matrix4f>
Skeletal::getBonesMatrices(SIZE_T meshNum)
{
  Vector<Matrix4f> bonesMatrices(100);
  if (m_bonesPerMesh.size() > meshNum) {
    for (SIZE_T i = 0; i < m_bonesPerMesh[meshNum].size(); i++) {
      if (i >= bonesMatrices.size()) {
        break;
      }
      bonesMatrices[i] = m_bonesPerMesh[meshNum][i].m_finalTransformation;
    }
  }

  return bonesMatrices;
}
}