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
#include "eeCTransform.h"

namespace eeEngineSDK {
void
getAllRenderableActorsInsideHelper(WPtr<CCamera> camera,
                                   const Vector<SPtr<ActorNode>>& actors,
                                   eRENDER_ACTOR_FLAGS::E flags,
                                   Vector<WPtr<Actor>>& outRenderActors)
{
  Vector<SPtr<ActorNode>> actorsToCheck;
  for (auto& act : actors) {
    Vector<SPtr<ActorNode>> childs = act->childrenNode;
    for (auto& childAct : childs) {
      if (childAct->actorValue.lock()->isActive()) {
        actorsToCheck.emplace_back(childAct);
      }
    }

    auto sAct = act->actorValue.lock();
    if (!sAct->getComponent<CRender>().expired()
     && sAct->getComponent<CRender>().lock()->getActive()) {
      bool canPass = false;
      if (Math::hasFlag(flags, eRENDER_ACTOR_FLAGS::kStaticMesh)
       && !sAct->getComponent<CStaticMesh>().expired()
       && sAct->getComponent<CStaticMesh>().lock()->getActive()) {
        canPass = true;
      }
      if (Math::hasFlag(flags, eRENDER_ACTOR_FLAGS::kSkeletalMesh)
       && !sAct->getComponent<CSkeletalMesh>().expired()
       && sAct->getComponent<CSkeletalMesh>().lock()->getActive()) {
        canPass = true;
      }
      if (!canPass) {
        continue;
      }

      WPtr<CBounds> boundC = sAct->getComponent<CBounds>();
      if (!boundC.expired() && camera.lock()->isModelOnCamera(boundC)) {
        outRenderActors.push_back(act->actorValue);
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
Vector<WPtr<Actor>>
Scene::getAllRenderableActorsInside(WPtr<CCamera> camera,
                                    eRENDER_ACTOR_FLAGS::E flags)
{
  Vector<SPtr<ActorNode>> actorsToCheck;
  for (auto& act : m_actorsTree) {
    if (act->actorValue.lock()->isActive()) {  
      actorsToCheck.emplace_back(act);
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
WPtr<Actor>
Scene::addActor(const String& name)
{
  if (m_actors.find(name) != m_actors.end()) {
    Logger::instance().consoleLog("ERROR TRYING TO ADD ACTOR TO SCENE");
    Logger::instance().consoleLog("Actor already with that name!");
    return m_actors[name];
  }

  m_actors[name] = MemoryManager::instance().newPtr<Actor>();
  m_actors[name]->init(name);
  SIZE_T nodeIndex = m_actorsTree.size();
  m_actorsTree.emplace_back(MemoryManager::instance().newPtr<ActorNode>());
  m_actorsTree[nodeIndex]->actorValue = m_actors[name];
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
SPtr<ActorNode>
getActorNodeByNameInTreeNode(const String& actorName, SPtr<ActorNode> rootNode)
{
  if (!rootNode->actorValue.expired()) {
    if (rootNode->actorValue.lock()->getName() == actorName) {
      return rootNode;
    }

    for (auto& anc : rootNode->childrenNode) {
      return getActorNodeByNameInTreeNode(actorName, anc);
    }
  }
  return nullptr;
}
SPtr<ActorNode>
Scene::getActorNodeByName(const String& actorName)
{
  for (auto& an : m_actorsTree) {
    auto actorNode = getActorNodeByNameInTreeNode(actorName, an);
    if (actorNode) return actorNode;
  }
  return nullptr;
}
bool
Scene::setActorChild(const String& parentName, const String& childName)
{
  if (m_actors.find(childName) == m_actors.end()) {
    Logger::instance().consoleLog("ERROR TRYING TO PARENT ACTOR");
    Logger::instance().consoleLog("Not an actor with that name!");
    return false;
  }

  if (m_actors.find(parentName) == m_actors.end()) {
    m_actors[childName]->getTransform().lock()->attachTo({});

    auto childNode = getActorNodeByName(childName);
    if (childNode) {
      if (!childNode->parentNode.expired()) {
        auto& parentChildren = childNode->parentNode.lock()->childrenNode;
        SIZE_T childrenCount = parentChildren.size();
        for (SIZE_T i = 0; i < childrenCount; ++i) {
          if (parentChildren[i]->actorValue.lock()->getName() == childName) {
            parentChildren.erase(parentChildren.begin() + i);
          }
        }
      }
      childNode->parentNode = {};
    }
  }
  else {
    m_actors[childName]->getTransform().lock()->attachTo(
    m_actors[parentName]->getTransform());

    auto childNode = getActorNodeByName(childName);
    auto parentNode = getActorNodeByName(parentName);
    if (childNode) {
      if (!childNode->parentNode.expired()
      && childNode->parentNode.lock()->actorValue.lock()->getName() != parentName) {
        auto& parentChildren = childNode->parentNode.lock()->childrenNode;
        SIZE_T childrenCount = parentChildren.size();
        for (SIZE_T i = 0; i < childrenCount; ++i) {
          if (parentChildren[i]->actorValue.lock()->getName() == childName) {
            parentChildren.erase(parentChildren.begin() + i);
          }
        }
      }
      else {
        SIZE_T childrenCount = m_actorsTree.size();
        for (SIZE_T i = 0; i < childrenCount; ++i) {
          if (m_actorsTree[i]->actorValue.lock()->getName() == childName) {
            m_actorsTree.erase(m_actorsTree.begin() + i);
          }
        }
      }
      if (parentNode) {
        childNode->parentNode = parentNode;
        parentNode->childrenNode.emplace_back(childNode);
      }
      else {
        childNode->parentNode = {};
      }
    }
  }
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