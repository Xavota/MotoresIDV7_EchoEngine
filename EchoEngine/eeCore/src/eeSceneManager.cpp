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
    std::cout << "ERROR TRYING TO ADD SCENE" << std::endl;
    std::cout << "Scene already with that name!" << std::endl;
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
    std::cout << "ERROR TRYING TO GET SCENE" << std::endl;
    std::cout << "Not a scene with that name!" << std::endl;
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