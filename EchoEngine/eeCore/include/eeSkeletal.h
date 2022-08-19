/************************************************************************/
/**
 * @file ee.h
 * @author Diego Castellanos
 * @date 21/01/22
 * @brief
 * The skeleton info for the skeletal mesh.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeMatrix4.h>

#include "eeResource.h"

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
  Bone(const String& name,
       const Vector<VertexWeight>& vertexWeights,
       Matrix4f offsetMatrix);
  ~Bone() = default;

  void addBoneData(VertexWeight vw);

  String m_name;
  Vector<VertexWeight> m_vertexWeights;
  Matrix4f m_offsetMatrix;

  Matrix4f m_finalTransformation;
};
/**
 * @brief
 * The skeleton info for the skeletal mesh.
 */
class EE_CORE_EXPORT Skeletal : public Resource
{
 public:
  /**
   * @brief
   * Default constructor.
   */
   Skeletal() = default;
  /**
   * @brief
   * Loads an skeletal mesh.
   *
   * @description
   * Loads the skeletal mesh from all the data it needs.
   *
   * @param bonesPerMesh
   * The bones array for every mesh.
   * @param globalInverseTransforms
   * The global inverse transforms array for every mesh.
   * @param boneMappings
   * The mappings of the bones, with names and indices, for every mesh.
   * @param numsBones
   * The numbers of bones array for every mesh.
   *
   * @return
   * Whether it succeeded to load or not.
   */
   Skeletal(const Vector<Vector<Bone>>& bonesPerMesh,
            const Vector<Matrix4f>& globalInverseTransforms,
            const Vector<Map<String, uint32>>& boneMappings,
            const Vector<uint32>& numsBones);
  /**
   * @brief
   * Default destructor.
   */
  ~Skeletal() = default;

  /**
   * @brief
   * Loads an skeletal mesh.
   *
   * @description
   * Loads the skeletal mesh from all the data it needs.
   *
   * @param bonesPerMesh
   * The bones array for every mesh.
   * @param globalInverseTransforms
   * The global inverse transforms array for every mesh.
   * @param boneMappings
   * The mappings of the bones, with names and indices, for every mesh.
   * @param numsBones
   * The numbers of bones array for every mesh.
   *
   * @return
   * Whether it succeeded to load or not.
   */
  bool
  loadFromData(const Vector<Vector<Bone>>& bonesPerMesh,
               const Vector<Matrix4f>& globalInverseTransforms,
               const Vector<Map<String, uint32>>& boneMappings,
               const Vector<uint32>& numsBones);

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
  bool
  getBonesDataForMesh(SIZE_T index, Vector<Bone>& outBoneData) const;

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
  Vector<Map<String, uint32>>&
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
  getBonesMatrices(SIZE_T meshNum);

  /**
   * @brief
   * Getter of the number of bones per mesh.
   *
   * @description
   * Returns the array containing number of bones per mesh.
   *
   * @return
   * The marray containing number of bones per mesh.
   */
  FORCEINLINE Vector<uint32>
  getNumBones()
  {
    return m_numsBones;
  }

 private:
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
  Vector<Map<String, uint32>> m_boneMappings;
  /**
   * Bones count for every mesh.
   */
  Vector<uint32> m_numsBones;
};
}
