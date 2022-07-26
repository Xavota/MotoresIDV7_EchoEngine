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
WPtr<Scene>
SceneManager::addScene(const String& name)
{
  if (m_scenes.find(name) != m_scenes.end()) {
    Logger::instance().consoleLog("ERROR TRYING TO ADD SCENE");
    Logger::instance().consoleLog("Scene already with that name!");
    return {};
  }

  m_scenes[name] = MemoryManager::instance().newPtr<Scene>();
  m_scenes[name]->init();
  return m_scenes[name];
}
WPtr<Scene>
SceneManager::getScene(const String& name)
{
  if (m_scenes.find(name) == m_scenes.end()) {
    Logger::instance().consoleLog("ERROR TRYING TO GET SCENE");
    Logger::instance().consoleLog("Not a scene with that name!");
    return {};
  }
  return m_scenes[name];
}
Vector<WPtr<Actor>>
SceneManager::getAllRenderableActorsInside(WPtr<CCamera> camera,
                                           RENDER_ACTOR_FLAGS::E flags)
{
  if (camera.expired()) { return {}; }

  Vector<WPtr<Actor>> renderActors;
  for (auto& sc : m_scenes) {
    Vector<WPtr<Actor>> tmpRenderActors;
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
  Vector<WPtr<Scene>> sceneArr;
  for (const auto& s : m_scenes) {
    sceneArr.emplace_back(s.second);
  }
  m_spacePartition.calculateTree(BoxAAB(Vector3f{ -100.0f, -100.0f, -100.0f },
                                        Vector3f{  200.0f,  200.0f,  200.0f }),
                                 sceneArr);
}
void
SceneManager::getPartitionedSceneMeshes(Vector<WPtr<StaticMesh>>& outMeshesVec)
{
  m_spacePartition.getMeshes(outMeshesVec);
}
}