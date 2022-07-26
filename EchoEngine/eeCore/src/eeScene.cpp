#include "eeScene.h"

#include <eeLogger.h>

#include <eeMath.h>

#include "eeActor.h"
#include "eeCAnimation.h"
#include "eeCBounds.h"
#include "eeCCamera.h"
#include "eeCLight.h"
#include "eeCRender.h"
#include "eeCSkeletalMesh.h"
#include "eeCStaticMesh.h"

namespace eeEngineSDK {
Vector<WPtr<Actor>>
Scene::getAllRenderableActorsInside(WPtr<CCamera> camera,
                                    RENDER_ACTOR_FLAGS::E flags)
{
  Vector<SPtr<Actor>> actorsToCheck;
  for (auto& act : m_actors) {
    if (act.second->isActive()) {  
      actorsToCheck.emplace_back(act.second);
    }
  }

  Vector<WPtr<Actor>> renderActors;
  if (!actorsToCheck.empty()) {
    getAllRenderableActorsInsideHelper(camera,
                                       actorsToCheck,
                                       flags,
                                       renderActors);
  }
  return renderActors;
}
void
Scene::getAllRenderableActorsInsideHelper(WPtr<CCamera> camera,
                                          const Vector<SPtr<Actor>>& actors,
                                          RENDER_ACTOR_FLAGS::E flags,
                                          Vector<WPtr<Actor>>& outRenderActors)
{
  Vector<SPtr<Actor>> actorsToCheck;
  for (auto& act : actors) {
    auto sAct = act;
    Vector<SPtr<Actor>> childs = sAct->getChildren();
    for (auto& childAct : childs) {
      if (childAct->isActive()) {
        actorsToCheck.emplace_back(childAct);
      }
    }

    if (sAct->isActive()
     && !sAct->getComponent<CRender>().expired()) {
      bool canPass = false;
      if (Math::hasFlag(flags, RENDER_ACTOR_FLAGS::kStaticMesh)
        && !sAct->getComponent<CStaticMesh>().expired()) {
        canPass = true;
      }
      if (Math::hasFlag(flags, RENDER_ACTOR_FLAGS::kSkeletalMesh)
        && !sAct->getComponent<CSkeletalMesh>().expired()) {
        canPass = true;
      }
      if (!canPass) {
        continue;
      }

      WPtr<CBounds> boundC = sAct->getComponent<CBounds>();
      if (!boundC.expired() && camera.lock()->isModelOnCamera(boundC)) {
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
WPtr<Actor>
Scene::addActor(const String& name)
{
  if (m_actors.find(name) != m_actors.end()) {
    Logger::instance().consoleLog("ERROR TRYING TO ADD ACTOR TO SCENE");
    Logger::instance().consoleLog("Actor already with that name!");
    return {};
  }

  m_actors[name] = MemoryManager::instance().newPtr<Actor>();
  m_actors[name]->init(name);
  return m_actors[name];
}
WPtr<Actor>
Scene::getActor(const String& name)
{
  if (m_actors.find(name) == m_actors.end()) {
    Logger::instance().consoleLog("ERROR TRYING TO GET ACTOR");
    Logger::instance().consoleLog("Not an actor with that name!");
    return {};
  }
  return m_actors[name];
}
Vector<SPtr<Actor>>
Scene::getAllActorsByComponentFlags(uint32 flags)
{
  Vector<SPtr<Actor>> r;
  if (Math::hasFlag(flags, eCOMPONENT_TYPE::kTransform)) {
    getAllActorsVector(r);
    return r;
  }

  for (const auto& act : m_actors) {
    if (Math::hasFlag(flags, eCOMPONENT_TYPE::kAnimation)
     && !act.second->getComponent<CAnimation>().expired()) {
      r.emplace_back(act.second);
    }
    if (Math::hasFlag(flags, eCOMPONENT_TYPE::kBounds)
     && !act.second->getComponent<CBounds>().expired()) {
      r.emplace_back(act.second);
    }
    if (Math::hasFlag(flags, eCOMPONENT_TYPE::kCamera)
     && !act.second->getComponent<CCamera>().expired()) {
      r.emplace_back(act.second);
    }
    if (Math::hasFlag(flags, eCOMPONENT_TYPE::kLight)
     && !act.second->getComponent<CLight>().expired()) {
      r.emplace_back(act.second);
    }
    if (Math::hasFlag(flags, eCOMPONENT_TYPE::kRender)
     && !act.second->getComponent<CRender>().expired()) {
      r.emplace_back(act.second);
    }
    if (Math::hasFlag(flags, eCOMPONENT_TYPE::kSkeletalMesh)
     && !act.second->getComponent<CSkeletalMesh>().expired()) {
      r.emplace_back(act.second);
    }
    if (Math::hasFlag(flags, eCOMPONENT_TYPE::kStaticMesh)
     && !act.second->getComponent<CStaticMesh>().expired()) {
      r.emplace_back(act.second);
    }
  }
  return r;
}
bool
Scene::setActorChild(const String& parentName, const String& childName)
{
  if (m_actors.find(parentName) == m_actors.end()
   && m_actors.find(childName) == m_actors.end()) {
    Logger::instance().consoleLog("ERROR TRYING TO PARENT ACTOR");
    Logger::instance().consoleLog("Not an actor with that name!");
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