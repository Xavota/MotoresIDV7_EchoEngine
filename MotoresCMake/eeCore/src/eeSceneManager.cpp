#include "eeSceneManager.h"

#include <eeLogger.h>

#include <eeMemoryManager.h>

#include <eeBox.h>

namespace eeEngineSDK {
SceneManager::~SceneManager()
{
  for (auto& sc : m_scenes) {
    sc.second->release();
  }
}
void
SceneManager::update()
{
  for (auto& sc : m_scenes) {
    if (sc.second->isActive() || sc.second->isOffActive()) {
      sc.second->update();
    }
  }
}
SPtr<Scene>
SceneManager::addScene(const String& name)
{
  if (m_scenes.find(name) != m_scenes.end()) {
    Logger::instance().ConsoleLog("ERROR TRYING TO ADD SCENE");
    Logger::instance().ConsoleLog("Scene already with that name!");
    return nullptr;
  }

  m_scenes[name] = MemoryManager::instance().newPtr<Scene>();
  m_scenes[name]->init();
  return m_scenes[name];
}
SPtr<Scene>
SceneManager::getScene(const String& name)
{
  if (m_scenes.find(name) == m_scenes.end()) {
    Logger::instance().ConsoleLog("ERROR TRYING TO GET SCENE");
    Logger::instance().ConsoleLog("Not a scene with that name!");
    return nullptr;
  }
  return m_scenes[name];
}
Vector<SPtr<Actor>>
SceneManager::getAllRenderableActorsInside(SPtr<CCamera> camera,
                                           RENDER_ACTOR_FLAGS::E flags)
{
  if (!camera) { return {}; }

  Vector<SPtr<Actor>> renderActors;
  for (auto& sc : m_scenes) {
    Vector<SPtr<Actor>> tmpRenderActors;
    if (sc.second->isActive()) {
      tmpRenderActors = sc.second->getAllRenderableActorsInside(camera, flags);
    }

    for (auto& ra : tmpRenderActors) {
      renderActors.push_back(ra);
    }
  }
  return renderActors;
}
Vector<SPtr<Actor>>
SceneManager::getAllActorsByComponentFlags(uint32 flags)
{
  Vector<SPtr<Actor>> r;
  Vector<SPtr<Actor>> tempR;

  for (const auto& sc : m_scenes) {
    tempR = sc.second->getAllActorsByComponentFlags(flags);

    for (const auto& act : tempR) {
      r.emplace_back(act);
    }
  }

  return r;
}
void
SceneManager::partitionScenes()
{
  Vector<SPtr<Scene>> sceneArr;
  for (const auto& s : m_scenes) {
    sceneArr.emplace_back(s.second);
  }
  m_spacePartition.calculateTree(BoxAAB(Vector3f{ -100.0f, -100.0f, -100.0f },
                                        Vector3f{  200.0f,  200.0f,  200.0f }),
                                 sceneArr);
}
void
SceneManager::getPartitionedSceneMeshes(Vector<SPtr<StaticMesh>>& outMeshesVec)
{
  m_spacePartition.getMeshes(outMeshesVec);
}
}