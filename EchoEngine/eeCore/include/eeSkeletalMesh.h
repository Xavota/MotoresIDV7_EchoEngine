/************************************************************************/
/**
 * @file eeSkeletalMesh.h
 * @author Diego Castellanos
 * @date 27/11/21
 * @brief
 * The skeletal mesh resource, contains bone data.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeMatrix4.h>

struct aiNode;

namespace eeEngineSDK {
/**
 * @brief
 * Data for the vertices info.
 */
struct VertexWeight
{
  uint32 m_vertexID = 0;
  float m_weight = 0;
};

/**
 * @brief
 * The Bone data.
 */
struct Bone
{
  Bone() = default;
  Bone(String name, Vector<VertexWeight> vertexWeights, Matrix4f offsetMatrix);
  ~Bone() = default;

  void addBoneData(VertexWeight vw);

  String m_name;
  Vector<VertexWeight> m_vertexWeights;
  Matrix4f m_offsetMatrix;

  Matrix4f m_finalTransformation;
};

/**
 * @brief
 * The skeletal mesh resource, contains bone data.
 */
class EE_CORE_EXPORT SkeletalMesh
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  SkeletalMesh() = default;
  /**
   * @brief
   * Default destructor.
   */
  ~SkeletalMesh() = default;

  /**
   * @brief
   * Loads an skeletal mesh.
   *
   * @description
   * Loads the skeletal mesh from a file.
   *
   * @param fileName
   * The file path for the skeletal.
   *
   * @return
   * Whether it succeeded to load or not.
   */
  bool
  loadFromFile(String fileName);

  /**
   * @brief
   * Gets the bone data.
   *
   * @description
   * Returns the bones data of the skeleton.
   *
   * @return
   * Bone data.
   */
  Vector<Vector<Bone>>&
  getBonesData();
  /**
   * @brief
   * Gets the bone data of a mesh.
   *
   * @description
   * Returns the bones data from a specific mesh of the skeleton.
   *
   * @param index
   * The index of the mesh.
   *
   * @return
   * Bone data.
   */
  const Vector<Bone>&
  getBonesDataForMesh(int32 index) const;

  /**
   * @brief
   * Returns the bone mapping data.
   *
   * @description
   * Returns the bone mapping data of the skeleton.
   *
   * @return
   * Bone mapping.
   */
  Vector<Map<String, int32>>&
  getBoneMapping();
  /**
   * @brief
   * Gets the global inverse transforms of the skeleton.
   *
   * @description
   * Returns the global inverse transforms of the skeletons meshes.
   *
   * @return
   * Global inverse transforms.
   */
  Vector<Matrix4f>&
  getGlobalInverseTransforms();

  /**
   * @brief
   * Updates the bones data.
   *
   * @description
   * Updates the bones matrices to the original pose of the skeleton.
   *
   * @param root
   * The root node of the skeleton.
   * @param meshIndex
   * The mesh index that is being modified.
   */
  void
  boneTransform(const aiNode* root, int32 meshIndex);
  /**
   * @brief
   * Updates the bones data.
   *
   * @description
   * Updates the bones matrices to the original pose of the skeleton.
   *
   * @param pNode
   * The parent node on the skeleton graph.
   * @param parentTransform
   * The transform of the parent node.
   * @param meshIndex
   * The mesh index that is being modified.
   * 
   * @param meshIndex
   * 
   */
  void
  readNodeHeirarchy(const aiNode* pNode,
                    const Matrix4f& parentTransform,
                    int32 meshIndex);

  /**
   * @brief
   * Gets the matrices of the bones.
   *
   * @description
   * Returns the matrices of each bone with is transformations.
   *
   * @param meshNum
   * The mesh of the skeleton to take the matrices.
   *
   * @return
   * The matrices of each bone with is transformations.
   */
  Vector<Matrix4f>
  getBonesMatrices(int32 meshNum);


  /**
   * @brief
   * Sets the skeletal mesh to use.
   *
   * @description
   * Sets the skeletal mesh bones data to the graphic memory.
   *
   * @param meshNum
   * The mesh index to set.
   */
  void
  use(int32 meshNum);

 private:
  /**
   * The buffer for the bone matrices.
   */
  SPtr<ConstantBuffer> m_matricesBuffer;

  /**
   * Bone data for every mesh.
   */
  Vector<Vector<Bone>> m_bonesPerMesh;

  /**
   * Global inverse transforms for every mesh.
   */
  Vector<Matrix4f> m_globalInverseTransforms;
  /**
   * Bone mapping of every mesh.
   */
  Vector<Map<String, int32>> m_boneMappings;
  /**
   * Bones count for every mesh.
   */
  Vector<int32> m_numsBones;
};
}
