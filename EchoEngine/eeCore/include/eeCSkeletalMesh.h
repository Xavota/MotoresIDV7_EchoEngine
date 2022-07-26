/************************************************************************/
/**
 * @file eeCSkeletalMesh.h
 * @author Diego Castellanos
 * @date 28/11/21
 * @brief
 * The skeletal mesh component.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include "eeComponent.h"
#include <eeSphere.h>
#include <eeBox.h>

namespace eeEngineSDK{
/**
 * @brief
 * The skeletal mesh component.
 */
class EE_CORE_EXPORT CSkeletalMesh : public Component
{
public:
  /**
   * @brief
   * The enum for identifying the component type.
   */
  enum { CmpType = eCOMPONENT_TYPE::kSkeletalMesh };

  /**
   * @brief
   * Default constructor.
   */
  CSkeletalMesh() = default;
  /**
   * @brief
   * Default destructor.
   */
  ~CSkeletalMesh() = default;

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
   * Updates the skeletal mesh logic.
   *
   * @description
   * Updates the bones of the skeletal.
   */
  void
  update() override;

  /**
   * @brief
   * Getter of the skeletal mesh resource.
   *
   * @return
   * The skeletal mesh resource that store the bone data.
   */
  WPtr<SkeletalMesh>
  getModel();
  /**
   * @brief
   * Getter of the skeletal mesh resource.
   *
   * @description
   * Returns the skeletal mesh resource that stores the bone data.
   *
   * @return
   * The new skeletal mesh resource that stores the bone data.
   */
  void
  setModel(WPtr<SkeletalMesh> skeletal);

 private:
  /**
   * The skeletal mesh resource.
   */
  WPtr<SkeletalMesh> m_skMesh;
};
}
