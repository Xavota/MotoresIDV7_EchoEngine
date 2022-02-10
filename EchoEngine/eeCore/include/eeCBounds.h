/************************************************************************/
/**
 * @file eeCBounds.h
 * @author Diego Castellanos
 * @date 09/02/22
 * @brief
 * The bounds component for a mesh or static mesh components.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include "eeComponent.h"

#include <eeSphere.h>
#include <eeBox.h>

namespace eeEngineSDK {
class EE_CORE_EXPORT CBounds : public Component
{
 public:
  /**
   * @brief
   * The enum for identifying the component type.
   */
  enum { CmpType = eCOMPONENT_TYPE::kBounds };

  /**
   * @brief
   * Default constructor.
   */
  CBounds() = default;
  /**
   * @brief
   * Default destructor.
   */
  ~CBounds() = default;

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
  FORCEINLINE int32
  getType() override
  {
    return CmpType;
  }

  /**
   * @brief
   * Updates the component logic.
   *
   * @description
   * Updates the everything the component needs.
   */
  void
  update() override;

  Sphere
  getSphereBound();
  BoxAAB
  getBoxBound();

 private:
  Sphere m_sphereBound;
  BoxAAB m_boxBound;
};
}
