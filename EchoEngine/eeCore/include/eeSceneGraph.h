#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK{
class EE_CORE_EXPORT SceneGraph
{
 public:
  SceneGraph() = default;
  ~SceneGraph() = default;

  void
  addNewActor(String name);

 private:
  Vector<SPtr<Actor>> m_actors;
};
}
