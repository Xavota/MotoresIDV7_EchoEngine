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
  FORCEINLINE int8
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

  /**
   * @brief
   * Getter of the sphere bound.
   *
   * @description
   * Returns the sphere bound, of the static mesh transformed by the Transform
   * component. If any of this isn't set, it returns a default sphere.
   * 
   * @return 
   * The sphere bound, of the static mesh transformed by the Transform
   * component. If any of this isn't set, it returns a default sphere.
   */
  FORCEINLINE const Sphere&
  getSphereBound()
  {
    return m_sphereBound;
  }
  /**
   * @brief
   * Getter of the box bound.
   *
   * @description
   * Returns the box bound, of the static mesh transformed by the Transform
   * component. If any of this isn't set, it returns a default box.
   *
   * @return
   * The box bound, of the static mesh transformed by the Transform
   * component. If any of this isn't set, it returns a default box.
   */
  FORCEINLINE const BoxAAB&
  getBoxBound()
  {
    return m_boxBound;
  }

 private:
  /**
   * The sphere bound of the actor, for the culling.
   */
  Sphere m_sphereBound;
  /**
   * The box bound of the actor, for the culling.
   */
  BoxAAB m_boxBound;
};
}
