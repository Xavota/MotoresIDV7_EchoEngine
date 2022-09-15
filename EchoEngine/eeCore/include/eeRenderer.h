/************************************************************************/
/**
 * @file eeRenderer.h
 * @author Diego Castellanos
 * @date 04/03/22
 * @brief
 * The Main class of the renderer. Defines the things on the interface.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeModule.h>

namespace eeEngineSDK {
/**
 * @brief
 * The Main class of the renderer. Defines the things on the interface.
 */
class EE_CORE_EXPORT Renderer : public Module<Renderer>
{
 public:
  /**
   * @brief
   * Default constructor
   */
  Renderer() = default;
  /**
   * @brief
   * Default destructor.
   */
  virtual
  ~Renderer() = default;

  /**
  * @brief
  * The update method.
  *
  * @description
  * Updates everything in the app every frame.
  *
  * @param deltaTime
  * The time elapsed since the last frame.
  */
  virtual void
  onUpdate(float /*deltaTime*/) {}

  /**
   * @brief
   * Executes the render pipeline.
   *
   * @description
   * Obtains the info of the base app to do the render pass.
   */
  virtual void
  onRender() {}
};
}
