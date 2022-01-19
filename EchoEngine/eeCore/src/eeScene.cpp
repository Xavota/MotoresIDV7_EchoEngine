#include "eeScene.h"
#include "eeActor.h"
#include "eeCRender.h"
#include "eeCModel.h"
#include "eeCCamera.h"

namespace eeEngineSDK {
Vector<SPtr<Actor>>
Scene::getAllRenderableActorsInside(SPtr<CCamera> camera)
{
  Vector<SPtr<Actor>> renderActors;
  for (auto& act : m_actors) {
    if (act.second->isActive()) {
      SPtr<CRender> render = act.second->getComponent<CRender>();
      SPtr<CModel> model = act.second->getComponent<CModel>();
      if (render && model && camera->isModelOnCamera(model)) {
        renderActors.push_back(act.second);
      }
    }
  }
  return renderActors;
}
SPtr<Actor>
Scene::addActor(String name)
{
  if (m_actors.find(name) != m_actors.end()) {
    eeOut << "ERROR TRYING TO ADD ACTOR TO SCENE" << eeEndl;
    eeOut << "Actor already with that name!" << eeEndl;
    return nullptr;
  }

  m_actors[name] = MemoryManager::instance().newPtr<Actor>();
  m_actors[name]->init(name);
  return m_actors[name];
}
SPtr<Actor>
Scene::getActor(String name)
{
  if (m_actors.find(name) == m_actors.end()) {
    eeOut << "ERROR TRYING TO GET ACTOR" << eeEndl;
    eeOut << "Not an actor with that name!" << eeEndl;
    return nullptr;
  }
  return m_actors[name];
}
void
Scene::init()
{
  
}
void
Scene::update()
{
  for (auto& act : m_actors) {
    if (act.second->isActive()) {
      act.second->update();
    }
  }
}
void
Scene::release()
{
  for (auto& a : m_actors) {
    a.second->destroy();
  }
}
bool
Scene::isActive()
{
  return m_active;
}
void
Scene::setActive(bool active)
{
  m_active = active;
}
bool
Scene::isOffActive()
{
  return m_offActive;
}
void
Scene::setOffActive(bool active)
{
  m_offActive = active;
}
}