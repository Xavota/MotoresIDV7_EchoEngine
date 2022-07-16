/************************************************************************/
/**
 * @file eeOGLTestRenderer.h
 * @author Diego Castellanos
 * @date 03/03/22
 * @brief
 * The Main class of the renderer. Defines the things on the interface.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesOGLTestRenderer.h"
#include <eeRenderer.h>

#include <eeMesh.h>

namespace eeEngineSDK {
/**
 * @brief
 * The Main class of the renderer. Defines the things on the interface.
 */
class EE_OGL_TEST_RENDERER_EXPORT OGLTestRenderer : public Renderer
{
 public:
  /**
   * @brief
   * Default constructor
   */
   OGLTestRenderer();
  /**
   * @brief
   * Copy constructor
   */
  ~OGLTestRenderer() = default;

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
  void
  onUpdate(float deltaTime) override;

  /**
   * @brief
   * Executes the render pipeline.
   *
   * @description
   * Obtains the info of the base app to do the render pass.
   */
  void
  onRender() override;

private:
  Mesh m_testMesh;

  SPtr<Texture> m_testTexture;

  SPtr<SamplerState> m_samLinear;
};
}
