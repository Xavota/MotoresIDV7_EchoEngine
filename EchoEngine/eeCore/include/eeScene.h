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

namespace eeEngineSDK{
class EE_CORE_EXPORT Scene
{
 public:
  Scene() = default;
  ~Scene() = default;

  Vector<SPtr<Actor>>
  getAllRenderableActorsInside(SPtr<CCamera> camera);

  SPtr<Actor>
  addActor(String name);
  SPtr<Actor>
  getActor(String name);

  void
  init();

  void
  update();

  bool
  isActive();
  void
  setActive(bool active);
  
  bool
  isOffActive();
  void
  setOffActive(bool active);

 private:
  Map<String, SPtr<Actor>> m_actors;

  bool m_active = false;
  bool m_offActive = false;
};
}
