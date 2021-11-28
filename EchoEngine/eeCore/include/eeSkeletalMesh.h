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

  void AddBoneData(VertexWeight vw);

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

 private:
  SPtr<ConstantBuffer> m_matricesBuffer;

  std::vector<std::vector<Bone>> m_bonesPerMesh;

  Vector<Matrix4f> m_globalInverseTransforms;
  std::vector<std::map<std::string, int32>> m_boneMappings;
  std::vector<int32> m_numsBones;
};
}
