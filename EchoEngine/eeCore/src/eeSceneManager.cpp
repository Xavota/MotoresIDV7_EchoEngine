#include "eeSceneManager.h"

#include <eeLogger.h>

#include <eeMemoryManager.h>

#include <eeBox.h>

#include <eeFile.h>

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

  File sceneSaveFile;
  sceneSaveFile.openFile(L"Scenes/" + eeStringtoWString(name) + L".echomap",
                         OPEN_TYPE::kWriteOnly | OPEN_TYPE::kBinary);
  sceneSaveFile.close();

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
void
SceneManager::saveAllScenes()
{
  for (const auto& sc : m_scenes) {
    saveScene(sc.first);
  }
}
void
serializeString(File& oFile, const String& stringToSerialize)
{
  if (oFile.isOpen()) {
    SIZE_T stringLength = stringToSerialize.size();
    oFile.writeBytes(reinterpret_cast<Byte*>(&stringLength), sizeof(SIZE_T));
    for (SIZE_T i = 0; i < stringLength; ++i) {
      char c = stringToSerialize[i];
      oFile.writeBytes(reinterpret_cast<Byte*>(&c), sizeof(char));
    }
  }
}
void
loadSerializedString(File& iFile, String& stringToLoad, uint8 sizeOfSizeT)
{
  if (iFile.isOpen()) {
    SIZE_T readStringLength = 0;
    if (sizeOfSizeT == 4) {
      uint32 byte4StringLenght = 0;
      iFile.readBytes(reinterpret_cast<Byte*>(&byte4StringLenght),
        sizeof(uint32));
      readStringLength = static_cast<SIZE_T>(byte4StringLenght);
    }
    else if (sizeOfSizeT == 8) {
      uint64 byte8StringLenght = 0;
      iFile.readBytes(reinterpret_cast<Byte*>(&byte8StringLenght),
        sizeof(uint64));
      readStringLength = static_cast<SIZE_T>(byte8StringLenght);
    }

    stringToLoad.clear();
    for (SIZE_T i = 0; i < readStringLength; ++i) {
      char c = 0;
      iFile.readBytes(reinterpret_cast<Byte*>(&c),
        sizeof(char));

      stringToLoad += c;
    }
  }
}
void
serializeActor(File& saveFile, SPtr<Actor> pActor)
{
  
}
void
serializeComponent(File& /*saveFile*/, SPtr<Component> /*pComponent*/)
{
  
}
void
SceneManager::saveScene(const String& name)
{
  File saveFile;
  saveFile.openFile(L"Scenes/" + eeStringtoWString(name) + L".echomap",
                    OPEN_TYPE::kWriteOnly | OPEN_TYPE::kBinary);

  uint8 versionNum = 0;
  saveFile.writeBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  uint8 sizeTSize = sizeof(SIZE_T);
  saveFile.writeBytes(reinterpret_cast<Byte*>(&sizeTSize), sizeof(uint8));

  Map<String, SPtr<Actor>> actors = m_scenes[name]->getAllActors();

  for (auto& a : actors) {
    serializeString(saveFile, a.first);
    serializeActor(saveFile, a.second);
  }

  saveFile.close();
}
Vector<WPtr<Actor>>
SceneManager::getAllRenderableActorsInside(WPtr<CCamera> camera,
                                           eRENDER_ACTOR_FLAGS::E flags)
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