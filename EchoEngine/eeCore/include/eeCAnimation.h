/************************************************************************/
/**
 * @file eeCAnimation.h
 * @author Diego Castellanos
 * @date 02/12/21
 * @brief The animation component for actors with Skeletal Mesh.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eeComponent.h"

namespace eeEngineSDK {
/**
 * @brief
 * The animation component for actors with Skeletal Mesh.
 */
class EE_CORE_EXPORT CAnimation : public Component
{
 public:
  /**
   * @brief
   * The enum for identifying the component type.
   */
  enum { CmpType = COMPONENT_TYPE::kAnimation };

  /**
   * @brief
   * Default constructor.
   */
  CAnimation() = default;
  /**
   * @brief
   * Default destructor.
   */
  ~CAnimation() = default;

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
   * Updates the component logic.
   *
   * @description
   * Updates everything the component needs to, if it needs to.
   */
  void
  update() override;

  /**
   * @brief
   * Returns the animation stored.
   *
   * @description
   * Returns the animation resource stored in the component.
   *
   * @return
   * The animation resource, nullptr if it is.
   */
  SPtr<Animation>
  getAnimation();
  /**
   * @brief
   * Sets an animation resource.
   *
   * @description
   * Stores an animation resource for the component.
   *
   * @param anim
   * The new animation resource.
   */
  void
  setAnimation(SPtr<Animation> anim); // TODO: CHANGE IT TO ADMIT ANIMATION 
                                      // STATE MACHINE.

 private:
  /**
   * The animation resource.
   */
  SPtr<Animation> m_anim;
  /**
   * The animation time.
   */
  float m_animTime = 0.0f;
};
}

