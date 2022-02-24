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
 * The Static Mesh component.
 */
class EE_CORE_EXPORT CStaticMesh : public Component
{
 public:
  /**
   * @brief
   * The enum for identifying the component type.
   */
  enum { CmpType = COMPONENT_TYPE::kStaticMesh };

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
  int32
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
  virtual void
  setStaticMesh(SPtr<StaticMesh> staticMesh);

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
  virtual SPtr<StaticMesh>
  getStaticMesh();

 private:
  /**
   * The static mesh resource.
   */
  SPtr<StaticMesh> m_staticMesh;
};
}
