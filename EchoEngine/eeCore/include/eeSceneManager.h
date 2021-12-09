/************************************************************************/
/**
 * @file eeSceneManager.h
 * @author Diego Castellanos
 * @date 24/11/21
 * @brief
 * The manager for all the scenes.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeModule.h>

namespace eeEngineSDK{
/**
* @brief
* The manager for all the scenes.
*/
class EE_CORE_EXPORT SceneManager : public Module<SceneManager>
{
 public:
  /**
  * @brief
  * Default constructor.
  */
  SceneManager() = default;
  /**
  * @brief
  * Default destructor.
  */
  ~SceneManager();

  /**
  * @brief
  * Updates the manager.
  *
  * @description
  * Updates the manager and all the scenes.
  */
  void
  update();

  /**
  * @brief
  * Adds a new scene.
  *
  * @description
  * Adds and initializes a new scene with its identifying name.
  *
  * @param name
  * The identifying name of the new scene.
  *
  * @return
  * The ptr to the new scene.
  */
  SPtr<Scene>
  addScene(String name);
  /**
  * @brief
  * Gets a scene.
  *
  * @description
  * Gets scene with its identifying name.
  *
  * @param name
  * The identifying name of the looking scene.
  *
  * @return
  * The ptr to the scene, nullptr if not found.
  */
  SPtr<Scene>
  getScene(String name);

  /**
  * @brief
  * Gets all actors of all active scenes inside the camera.
  *
  * @description
  * Gets all actors of all active scenes that are inside the frustum of the
  * camera and have a model and a render component.
  *
  * @param camera
  * The camera to check the frustum.
  *
  * @return
  * All actors inside.
  */
  Vector<SPtr<Actor>>
  getAllRenderableActorsInside(SPtr<CCamera> camera);


 private:
  /**
  * All the scenes.
  */
  Map<String, SPtr<Scene>> m_scenes;
};
}
