/************************************************************************/
/**
 * @file eeInput.h
 * @author Diego Castellanos
 * @date 27/11/21
 * @brief
 * The input manager for the api.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeMatrix4.h>

class aiNode;

namespace eeEngineSDK {
struct VertexWeight
{
  uint32 m_vertexID = 0;
  float m_weight = 0;
};

struct Bone
{
  Bone() = default;
  Bone(String name, Vector<VertexWeight> vertexWeights, Matrix4f offsetMatrix);
  ~Bone();

  void addBoneData(VertexWeight vw);

  String m_name;
  Vector<VertexWeight> m_vertexWeights;
  Matrix4f m_offsetMatrix;

  Matrix4f m_finalTransformation;
};

class SkeletalMesh
{
 public:
  SkeletalMesh() = default;
  ~SkeletalMesh() = default;

  bool
  loadFromFile(String fileName);

  Vector<Vector<Bone>>&
  getBonesData();
  const Vector<Bone>&
  getBonesDataForMesh(int32 index) const;

  Vector<Map<String, int32>>&
  getBoneMapping();
  Vector<Matrix4f>&
  getGlobalInverseTransforms();

  void
  boneTransform(const aiNode* root, int meshIndex);
  void
  readNodeHeirarchy(const aiNode* pNode,
                    const Matrix4f& ParentTransform,
                    int meshIndex);

  Vector<Matrix4f>
  getBonesMatrices(int meshNum);


  void
  use(int meshNum);

 private:
  SPtr<ConstantBuffer> m_matricesBuffer;

  Vector<Vector<Bone>> m_bonesPerMesh;

  Vector<Matrix4f> m_globalInverseTransforms;
  Vector<Map<String, int32>> m_boneMappings;
  Vector<int32> m_numsBones;
};
}
