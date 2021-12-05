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
  for (auto& act : m_actors)
  {
    if (act.second->isActive())
    {
      SPtr<CRender> render = act.second->getComponent<CRender>();
      SPtr<CModel> model = act.second->getComponent<CModel>();
      if (render && model && camera->isModelOnCamera(model))
      {
        renderActors.push_back(act.second);
      }
    }
  }
  return renderActors;
}
SPtr<Actor>
Scene::addActor(String name)
{
  if (m_actors.find(name) != m_actors.end())
  {
    eeOStream::print("ERROR TRYING TO ADD ACTOR TO SCENE"); eeOStream::endl();
    eeOStream::print("Actor already with that name!"); eeOStream::endl();
    return nullptr;
  }

  //m_actors[name] = MemoryManager::instance().newPtr<Actor>(name);
  m_actors[name] = std::make_shared<Actor>(name);
  m_actors[name]->init();
  return m_actors[name];
}
SPtr<Actor>
Scene::getActor(String name)
{
  if (m_actors.find(name) == m_actors.end())
  {
    eeOStream::print("ERROR TRYING TO GET ACTOR"); eeOStream::endl();
    eeOStream::print("Not an actor with that name!"); eeOStream::endl();
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
  for (auto& act : m_actors)
  {
    if (act.second->isActive())
      act.second->update();
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