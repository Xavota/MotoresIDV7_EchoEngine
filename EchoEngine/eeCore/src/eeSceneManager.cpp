#include "eeSceneManager.h"
#include "eeScene.h"

#include <eeMemoryManager.h>

namespace eeEngineSDK {
void
SceneManager::update()
{
  for (auto& sc : m_scenes)
  {
    if (sc.second->isActive() || sc.second->isOffActive())
    {
      sc.second->update();
    }
  }
}
SPtr<Scene>
SceneManager::addScene(String name)
{
  if (m_scenes.find(name) != m_scenes.end())
  {
    eeOStream::print("ERROR TRYING TO ADD SCENE"); eeOStream::endl();
    eeOStream::print("Scene already with that name!"); eeOStream::endl();
    return nullptr;
  }

  m_scenes[name] = MemoryManager::instance().newPtr<Scene>();
  m_scenes[name]->init();
  return m_scenes[name];
}
SPtr<Scene>
SceneManager::getScene(String name)
{
  if (m_scenes.find(name) == m_scenes.end())
  {
    eeOStream::print("ERROR TRYING TO GET SCENE"); eeOStream::endl();
    eeOStream::print("Not a scene with that name!"); eeOStream::endl();
    return nullptr;
  }
  return m_scenes[name];
}
Vector<SPtr<Actor>>
SceneManager::getAllRenderableActorsInside(SPtr<CCamera> camera)
{
  Vector<SPtr<Actor>> renderActors;
  for (auto& sc : m_scenes)
  {
    Vector<SPtr<Actor>> tmpRenderActors;
    if (sc.second->isActive())
    {
      tmpRenderActors = sc.second->getAllRenderableActorsInside(camera);
    }

    for (auto& ra : tmpRenderActors)
    {
      renderActors.push_back(ra);
    }
  }
  return renderActors;
}
}