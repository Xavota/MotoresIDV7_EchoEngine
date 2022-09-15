/************************************************************************/
/**
 * @file eeCStaticMesh.h
 * @author Diego Castellanos
 * @date 18/11/21
 * @brief
 * The Static Mesh component.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeSphere.h>
#include <eeBox.h>
#include "eeComponent.h"

namespace eeEngineSDK{
/**
 * @brief
 * The type of mobility of the mesh. This is used for optimization process.
 */
namespace eMOBILITY_TYPE {
enum E : uint8 
{
  kDynamic = 0,
  kStatic
};
}
/**
 * @brief
 * The Static Mesh component.
 */
class EE_CORE_EXPORT CStaticMesh : public Component
{
 public:
  /**
   * @brief
   * The enum for identifying the component type.
   */
  enum { CmpType = eCOMPONENT_TYPE::kStaticMesh };

  /**
   * @brief
   * Default constructor.
   */
  CStaticMesh() = default;
  /**
   * @brief
   * Default destructor.
   */
  ~CStaticMesh() = default;

  /**
   * @brief
   * Returns the component type.
   *
   * @description
   * Returns the component type.
   *
   * @return
   * The component type.
   */
  int8
  getType() override
  {
    return CmpType;
  }

  /**
   * @brief
   * Updates the static mesh logic.
   *
   * @description
   * Updates the static mesh bounds with the transforms of the actor.
   */
  void
  update() override;

  /**
   * @brief
   * Setter for the static mesh resource.
   *
   * @description
   * Sets the static mesh resource for the component.
   *
   * @param staticMesh
   * The new static mesh resource.
   */
  void
  setStaticMesh(WPtr<StaticMesh> staticMesh);

  /**
   * @brief
   * Getter for the static mesh resource.
   *
   * @description
   * Gets the static mesh resource of the component.
   *
   * @return
   * The static mesh resource of the component.
   */
  WPtr<StaticMesh>
  getStaticMesh();

  /**
   * @brief
   * Getter for the mobility type.
   *
   * @description
   * Gets the mobility type of the static mesh, to pre-compute optimizations.
   *
   * @return
   * The mobility type of the component.
   */
  eMOBILITY_TYPE::E
  getMobilityType()
  {
    return m_mobilityType;
  }
  /**
   * @brief
   * Setter for the mobility type.
   *
   * @description
   * Sets the mobility type of the static mesh, to pre-compute optimizations.
   *
   * @param type
   * The mobility type of the component.
   */
  void
  setMobilityType(eMOBILITY_TYPE::E type)
  {
    m_mobilityType = type;
  }

 private:
  /**
   * The static mesh resource.
   */
  WPtr<StaticMesh> m_staticMesh;

  /**
   * The number of indices.
   */
  eMOBILITY_TYPE::E m_mobilityType = eMOBILITY_TYPE::kDynamic;
};
}
