#include "eeScene.h"

#include <eeLogger.h>

#include <eeMath.h>

#include "eeActor.h"
#include "eeCRender.h"
#include "eeCStaticMesh.h"
#include "eeCSkeletalMesh.h"
#include "eeCCamera.h"
#include "eeCBounds.h"

namespace eeEngineSDK {
Vector<SPtr<Actor>>
Scene::getAllRenderableActorsInside(SPtr<CCamera> camera,
                                    RENDER_ACTOR_FLAGS::E flags)
{
  Vector<SPtr<Actor>> actorsToCheck;
  for (auto& act : m_actors) {
    if (act.second->isActive()) {  
      actorsToCheck.emplace_back(act.second);
    }
  }

  Vector<SPtr<Actor>> renderActors;
  if (!actorsToCheck.empty()) {
    getAllRenderableActorsInsideHelper(camera,
                                       actorsToCheck,
                                       flags,
                                       renderActors);
  }
  return renderActors;
}
void
Scene::getAllRenderableActorsInsideHelper(SPtr<CCamera> camera,
                                          Vector<SPtr<Actor>> actors,
                                          RENDER_ACTOR_FLAGS::E flags,
                                          Vector<SPtr<Actor>>& outRenderActors)
{
  Vector<SPtr<Actor>> actorsToCheck;
  for (auto& act : actors) {
    Vector<SPtr<Actor>> childs = act->getChildren();
    for (auto& childAct : childs) {
      if (childAct->isActive()) {
        actorsToCheck.emplace_back(childAct);
      }
    }

    if (act->isActive()
     && act->getComponent<CRender>()) {
      bool canPass = false;
      if (Math::hasFlag(flags, RENDER_ACTOR_FLAGS::kStaticMesh)
        && act->getComponent<CStaticMesh>()) {
        canPass = true;
      }
      if (Math::hasFlag(flags, RENDER_ACTOR_FLAGS::kSkeletalMesh)
        && act->getComponent<CSkeletalMesh>()) {
        canPass = true;
      }
      if (!canPass) {
        continue;
      }

      SPtr<CBounds> boundC = act->getComponent<CBounds>();
      if (boundC && camera->isModelOnCamera(boundC)) {
        outRenderActors.push_back(act);
      }
    }
  }


  if (!actorsToCheck.empty()) {
    getAllRenderableActorsInsideHelper(camera,
                                       actorsToCheck,
                                       flags,
                                       outRenderActors);
  }
}
SPtr<Actor>
Scene::addActor(String name)
{
  if (m_actors.find(name) != m_actors.end()) {
    Logger::instance().ConsoleLog("ERROR TRYING TO ADD ACTOR TO SCENE");
    Logger::instance().ConsoleLog("Actor already with that name!");
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
    Logger::instance().ConsoleLog("ERROR TRYING TO GET ACTOR");
    Logger::instance().ConsoleLog("Not an actor with that name!");
    return nullptr;
  }
  return m_actors[name];
}
bool
Scene::setActorChild(String parentName, String childName)
{
  if (m_actors.find(parentName) == m_actors.end()
   && m_actors.find(childName) == m_actors.end()) {
    Logger::instance().ConsoleLog("ERROR TRYING TO PARENT ACTOR");
    Logger::instance().ConsoleLog("Not an actor with that name!");
    return false;
  }

  m_actors[childName]->attachTo(m_actors[parentName]);
  m_actors.erase(m_actors.find(childName));
  return true;
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