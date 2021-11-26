/************************************************************************/
/**
 * @file eeInput.h
 * @author Diego Castellanos
 * @date 24/11/21
 * @brief
 * The input manager for the api.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeModule.h>

namespace eeEngineSDK{
class EE_CORE_EXPORT SceneManager : public Module<SceneManager>
{
 public:
  SceneManager() = default;
  ~SceneManager() = default;

  void
  update();

  SPtr<Scene>
  addScene(String name);
  SPtr<Scene>
  getScene(String name);

  Vector<SPtr<Actor>>
  getAllRenderableActorsInside(CCamera* camera);


 private:
  Map<String, SPtr<Scene>> m_scenes;
};
}
