#include "eeSceneManager.h"

#include <eeLogger.h>
#include <eeMemoryManager.h>
#include <eeResourceManager.h>

#include <eeBox.h>

#include <eeFile.h>

#include <eeSerializationUtilities.h>

#include "eeActor.h"

#include "eeCAnimation.h"
#include "eeCBounds.h"
#include "eeCCamera.h"
#include "eeCLight.h"
#include "eeCRender.h"
#include "eeCSkeletalMesh.h"
#include "eeSkeletalMesh.h"
#include "eeCStaticMesh.h"
#include "eeStaticMesh.h"
#include "eeCTransform.h"

#include "eeAnimation.h"

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
SceneManager::saveActiveScenes()
{
  for (const auto& sc : m_scenes) {
    if (sc.second->isActive()) saveScene(sc.first);
  }
}

void
serializeAnimComp(File& saveFile, SPtr<CAnimation> pComponent)
{
  uint8 versionNum = 0;
  saveFile.writeBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  bool isCmpActive = pComponent->getActive();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&isCmpActive), sizeof(bool));

  auto anim = pComponent->getAnimation();
  if (!anim.expired()) {
    serializeString(saveFile, anim.lock()->getResourceName());
  }
  else {
    SIZE_T stringLength = 0;
    saveFile.writeBytes(reinterpret_cast<Byte*>(&stringLength), sizeof(SIZE_T));
  }
}
void
serializeBoundsComp(File& saveFile, SPtr<CBounds> pComponent)
{
  uint8 versionNum = 0;
  saveFile.writeBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  bool isCmpActive = pComponent->getActive();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&isCmpActive), sizeof(bool));
}
void
serializeCamComp(File& saveFile, SPtr<CCamera> pComponent)
{
  uint8 versionNum = 0;
  saveFile.writeBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  bool isCmpActive = pComponent->getActive();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&isCmpActive), sizeof(bool));

  CameraDesc camDesc;
  camDesc.projectionType = pComponent->getProjectionType();
  camDesc.fovAngleY = pComponent->getFovAngle();
  camDesc.viewSize = pComponent->getViewSize();
  camDesc.nearZ = pComponent->getNearPlane();
  camDesc.farZ = pComponent->getFarPlane();

  saveFile.writeBytes(reinterpret_cast<Byte*>(&camDesc), sizeof(CameraDesc));

  bool isMain = pComponent->isMain();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&isMain), sizeof(bool));
}
void
serializeLightComp(File& saveFile, SPtr<CLight> pComponent)
{
  uint8 versionNum = 0;
  saveFile.writeBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  bool isCmpActive = pComponent->getActive();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&isCmpActive), sizeof(bool));

  eLIGHT_TYPE::E type = pComponent->getLightType();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&type), sizeof(uint8));
  Color newColor = pComponent->getColor();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&newColor), sizeof(Color));
  float intensity = pComponent->getIntensity();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&intensity), sizeof(float));
  float innerAngle = pComponent->getInnerAngle();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&innerAngle), sizeof(float));
  float outerAngle = pComponent->getOuterAngle();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&outerAngle), sizeof(float));
}
void
serializeRenderComp(File& saveFile, SPtr<CRender> pComponent)
{
  uint8 versionNum = 0;
  saveFile.writeBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  bool isCmpActive = pComponent->getActive();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&isCmpActive), sizeof(bool));
}
void
serializeSKMeshComp(File& saveFile, SPtr<CSkeletalMesh> pComponent)
{
  uint8 versionNum = 0;
  saveFile.writeBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  bool isCmpActive = pComponent->getActive();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&isCmpActive), sizeof(bool));

  auto skMesh = pComponent->getModel();
  if (!skMesh.expired()) {
    serializeString(saveFile, skMesh.lock()->getResourceName());
  }
  else {
    SIZE_T stringLength = 0;
    saveFile.writeBytes(reinterpret_cast<Byte*>(&stringLength), sizeof(SIZE_T));
  }
}
void
serializeSTMeshComp(File& saveFile, SPtr<CStaticMesh> pComponent)
{
  uint8 versionNum = 0;
  saveFile.writeBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  bool isCmpActive = pComponent->getActive();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&isCmpActive), sizeof(bool));

  auto stMesh = pComponent->getStaticMesh();
  if (!stMesh.expired()) {
    serializeString(saveFile, stMesh.lock()->getResourceName());
  }
  else {
    SIZE_T stringLength = 0;
    saveFile.writeBytes(reinterpret_cast<Byte*>(&stringLength), sizeof(SIZE_T));
  }

  eMOBILITY_TYPE::E movType = pComponent->getMobilityType();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&movType), sizeof(uint8));
}
void
serializeTransComp(File& saveFile, SPtr<CTransform> pComponent)
{
  uint8 versionNum = 0;
  saveFile.writeBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  bool isCmpActive = pComponent->getActive();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&isCmpActive), sizeof(bool));

  Vector3f pos = pComponent->getPosition();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&pos), sizeof(Vector3f));
  Quaternion rot = pComponent->getRotation();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&rot), sizeof(Quaternion));
  Vector3f scale = pComponent->getScale();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&scale), sizeof(Vector3f));
}
void
serializeComponent(File& saveFile, SPtr<Component> pComponent)
{
  auto cmpType = pComponent->getType();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&cmpType), sizeof(uint8));

  auto& memoryMan = MemoryManager::instance();
  switch (cmpType)
  {
  case eCOMPONENT_TYPE::kAnimation:
    serializeAnimComp(saveFile, memoryMan.reinterpretPtr<CAnimation>(pComponent));
    break;
  case eCOMPONENT_TYPE::kBounds:
    serializeBoundsComp(saveFile, memoryMan.reinterpretPtr<CBounds>(pComponent));
    break;
  case eCOMPONENT_TYPE::kCamera:
    serializeCamComp(saveFile, memoryMan.reinterpretPtr<CCamera>(pComponent));
    break;
  case eCOMPONENT_TYPE::kLight:
    serializeLightComp(saveFile, memoryMan.reinterpretPtr<CLight>(pComponent));
    break;
  case eCOMPONENT_TYPE::kRender:
    serializeRenderComp(saveFile, memoryMan.reinterpretPtr<CRender>(pComponent));
    break;
  case eCOMPONENT_TYPE::kSkeletalMesh:
    serializeSKMeshComp(saveFile, memoryMan.reinterpretPtr<CSkeletalMesh>(pComponent));
    break;
  case eCOMPONENT_TYPE::kStaticMesh:
    serializeSTMeshComp(saveFile, memoryMan.reinterpretPtr<CStaticMesh>(pComponent));
    break;
  case eCOMPONENT_TYPE::kTransform:
    serializeTransComp(saveFile, memoryMan.reinterpretPtr<CTransform>(pComponent));
    break;
  }
}
void
loadSerializedAnimComp(File& loadFile,
                       WPtr<Actor> compActor,
                       uint8 sizeTSize)
{
  auto cmp = compActor.lock()->addComponent<CAnimation>().lock();

  uint8 versionNum = 0;
  loadFile.readBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  bool isCmpActive = false;
  loadFile.readBytes(reinterpret_cast<Byte*>(&isCmpActive), sizeof(bool));

  String animName;
  loadSerializedString(loadFile, animName, sizeTSize);

  cmp->setAnimation(ResourceManager::instance().getResourceAnimation(animName));
  cmp->setActive(isCmpActive);
}
void
loadSerializedBoundsComp(File& loadFile,
                         WPtr<Actor> compActor,
                         uint8 sizeTSize)
{
  auto cmp = compActor.lock()->addComponent<CBounds>().lock();

  uint8 versionNum = 0;
  loadFile.readBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  bool isCmpActive = false;
  loadFile.readBytes(reinterpret_cast<Byte*>(&isCmpActive), sizeof(bool));

  cmp->setActive(isCmpActive);
}
void
loadSerializedCamComp(File& loadFile,
                      WPtr<Actor> compActor,
                      uint8 sizeTSize)
{
  auto cmp = compActor.lock()->addComponent<CCamera>().lock();

  uint8 versionNum = 0;
  loadFile.readBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  bool isCmpActive = false;
  loadFile.readBytes(reinterpret_cast<Byte*>(&isCmpActive), sizeof(bool));

  CameraDesc camDesc;

  loadFile.readBytes(reinterpret_cast<Byte*>(&camDesc), sizeof(CameraDesc));

  bool isMain = false;
  loadFile.readBytes(reinterpret_cast<Byte*>(&isMain), sizeof(bool));

  cmp->init(camDesc);
  cmp->setMain(isMain);
  cmp->setActive(isCmpActive);
}
void
loadSerializedLightComp(File& loadFile,
                        WPtr<Actor> compActor,
                        uint8 sizeTSize)
{
  auto cmp = compActor.lock()->addComponent<CLight>().lock();

  uint8 versionNum = 0;
  loadFile.readBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  bool isCmpActive = false;
  loadFile.readBytes(reinterpret_cast<Byte*>(&isCmpActive), sizeof(bool));

  eLIGHT_TYPE::E type = eLIGHT_TYPE::kDirectional;
  loadFile.readBytes(reinterpret_cast<Byte*>(&type), sizeof(uint8));
  Color newColor;
  loadFile.readBytes(reinterpret_cast<Byte*>(&newColor), sizeof(Color));
  float intensity = 0.0f;
  loadFile.readBytes(reinterpret_cast<Byte*>(&intensity), sizeof(float));
  float innerAngle = 0.0f;
  loadFile.readBytes(reinterpret_cast<Byte*>(&innerAngle), sizeof(float));
  float outerAngle = 0.0f;
  loadFile.readBytes(reinterpret_cast<Byte*>(&outerAngle), sizeof(float));

  cmp->init(type, newColor, intensity, innerAngle, outerAngle);
  cmp->setActive(isCmpActive);
}
void
loadSerializedRenderComp(File& loadFile,
                         WPtr<Actor> compActor,
                         uint8 sizeTSize)
{
  auto cmp = compActor.lock()->addComponent<CRender>().lock();

  uint8 versionNum = 0;
  loadFile.readBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  bool isCmpActive = false;
  loadFile.readBytes(reinterpret_cast<Byte*>(&isCmpActive), sizeof(bool));

  cmp->setActive(isCmpActive);
}
void
loadSerializedSKMeshComp(File& loadFile,
                         WPtr<Actor> compActor,
                         uint8 sizeTSize)
{
  auto cmp = compActor.lock()->addComponent<CSkeletalMesh>().lock();

  uint8 versionNum = 0;
  loadFile.readBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  bool isCmpActive = false;
  loadFile.readBytes(reinterpret_cast<Byte*>(&isCmpActive), sizeof(bool));

  String skMeshName;
  loadSerializedString(loadFile, skMeshName, sizeTSize);

  cmp->setModel(ResourceManager::instance().getResourceSkeletalMesh(skMeshName));
  cmp->setActive(isCmpActive);
}
void
loadSerializedSTMeshComp(File& loadFile,
                         WPtr<Actor> compActor,
                         uint8 sizeTSize)
{
  auto cmp = compActor.lock()->addComponent<CStaticMesh>().lock();

  uint8 versionNum = 0;
  loadFile.readBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  bool isCmpActive = false;
  loadFile.readBytes(reinterpret_cast<Byte*>(&isCmpActive), sizeof(bool));

  String stMeshName;
  loadSerializedString(loadFile, stMeshName, sizeTSize);
  eMOBILITY_TYPE::E movType = eMOBILITY_TYPE::kDynamic;
  loadFile.readBytes(reinterpret_cast<Byte*>(&movType), sizeof(uint8));

  cmp->setStaticMesh(ResourceManager::instance().getResourceStaticMesh(stMeshName));
  cmp->setMobilityType(movType);
  cmp->setActive(isCmpActive);
}
void
loadSerializedTransComp(File& loadFile,
                        WPtr<Actor> compActor,
                        uint8 sizeTSize)
{
  auto cmp = compActor.lock()->addComponent<CTransform>().lock();

  uint8 versionNum = 0;
  loadFile.readBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  bool isCmpActive = false;
  loadFile.readBytes(reinterpret_cast<Byte*>(&isCmpActive), sizeof(bool));

  Vector3f pos;
  loadFile.readBytes(reinterpret_cast<Byte*>(&pos), sizeof(Vector3f));
  Quaternion rot;
  loadFile.readBytes(reinterpret_cast<Byte*>(&rot), sizeof(Quaternion));
  Vector3f scale;
  loadFile.readBytes(reinterpret_cast<Byte*>(&scale), sizeof(Vector3f));

  cmp->setPosition(pos);
  cmp->setRotation(rot);
  cmp->setScale(scale);
  cmp->setActive(isCmpActive);
}
void
loadSerializedComponent(File& loadFile,
                        WPtr<Actor> compActor,
                        uint8 sizeTSize)
{
  auto& memoryMan = MemoryManager::instance();

  auto cmpType = 0;
  loadFile.readBytes(reinterpret_cast<Byte*>(&cmpType), sizeof(uint8));

  switch (cmpType)
  {
  case eCOMPONENT_TYPE::kAnimation:
    loadSerializedAnimComp(loadFile, compActor, sizeTSize);
    break;
  case eCOMPONENT_TYPE::kBounds:
    loadSerializedBoundsComp(loadFile, compActor, sizeTSize);
    break;
  case eCOMPONENT_TYPE::kCamera:
    loadSerializedCamComp(loadFile, compActor, sizeTSize);
    break;
  case eCOMPONENT_TYPE::kLight:
    loadSerializedLightComp(loadFile, compActor, sizeTSize);
    break;
  case eCOMPONENT_TYPE::kRender:
    loadSerializedRenderComp(loadFile, compActor, sizeTSize);
    break;
  case eCOMPONENT_TYPE::kSkeletalMesh:
    loadSerializedSKMeshComp(loadFile, compActor, sizeTSize);
    break;
  case eCOMPONENT_TYPE::kStaticMesh:
    loadSerializedSTMeshComp(loadFile, compActor, sizeTSize);
    break;
  case eCOMPONENT_TYPE::kTransform:
    loadSerializedTransComp(loadFile, compActor, sizeTSize);
    break;
  }
}
void
serializeActor(File& saveFile, SPtr<ActorNode> pActor)
{
  uint8 versionNum = 0;
  saveFile.writeBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));

  auto spActor = pActor->actorValue.lock();
  serializeString(saveFile, spActor->getName());
  bool active = spActor->isActive();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&active), sizeof(bool));

  Vector<SPtr<Component>> components = spActor->getAllComponents();

  SIZE_T compCount = components.size();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&compCount), sizeof(SIZE_T));
  for (auto& c : components) {
    serializeComponent(saveFile, c);
  }

  SIZE_T childrenCount = pActor->childrenNode.size();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&childrenCount), sizeof(SIZE_T));
  for (auto& a : pActor->childrenNode) {
    serializeActor(saveFile, a);
  }
}
void
loadSerializedActor(File& loadFile,
                    SPtr<Scene> loadingScene,
                    WPtr<Actor> parentActor,
                    uint8 sizeTSize)
{
  auto& memoryMan = MemoryManager::instance();

  uint8 versionNum = 0;
  loadFile.readBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));

  String actName;
  loadSerializedString(loadFile, actName, sizeTSize);
  bool active = false;
  loadFile.readBytes(reinterpret_cast<Byte*>(&active), sizeof(bool));
  auto newActor = loadingScene->addActor(actName);
  if (!parentActor.expired()) {
    loadingScene->setActorChild(parentActor.lock()->getName(),
                                newActor.lock()->getName());
  }
  newActor.lock()->setActive(active);

  SIZE_T compCount = 0;
  loadSerializedSize(loadFile, compCount, sizeTSize);
  for (SIZE_T i = 0; i < compCount; ++i) {
    loadSerializedComponent(loadFile, newActor, sizeTSize);
  }

  SIZE_T childrenCount = 0;
  loadSerializedSize(loadFile, childrenCount, sizeTSize);
  for (SIZE_T i = 0; i < childrenCount; ++i) {
    loadSerializedActor(loadFile, loadingScene, newActor, sizeTSize);
  }
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

  Vector<SPtr<ActorNode>> actors = m_scenes[name]->getActorsTree();

  SIZE_T actorsCount = actors.size();
  saveFile.writeBytes(reinterpret_cast<Byte*>(&actorsCount), sizeof(SIZE_T));
  for (auto& a : actors) {
    serializeActor(saveFile, a);
  }

  saveFile.close();
}
void
SceneManager::loadScene(const WString& filePath)
{
  unloadAllScene();

  auto& memoryMan = MemoryManager::instance();

  String sceneName;
  getFileName(filePath, sceneName);
  if (m_scenes.find(sceneName) == m_scenes.end()) {
    m_scenes[sceneName] = memoryMan.newPtr<Scene>();
  }

  File loadFile;
  loadFile.openFile(filePath,
                    OPEN_TYPE::kReadOnly | OPEN_TYPE::kBinary);

  uint8 versionNum = 0;
  loadFile.readBytes(reinterpret_cast<Byte*>(&versionNum), sizeof(uint8));
  uint8 sizeTSize = 0;
  loadFile.readBytes(reinterpret_cast<Byte*>(&sizeTSize), sizeof(uint8));


  SIZE_T actorsCount = 0;
  loadSerializedSize(loadFile, actorsCount, sizeTSize);
  for (SIZE_T i = 0; i < actorsCount; ++i) {
    loadSerializedActor(loadFile, m_scenes[sceneName], {}, sizeTSize);
  }

  loadFile.close();

  partitionScene(sceneName);

  m_scenes[sceneName]->setActive(true);
}
void
SceneManager::unloadAllScene()
{
  for (auto& s : m_scenes) {
    if (s.second->isActive()) {
      unloadScene(s.first);
    }
  }
}
void
SceneManager::unloadScene(const String& name) // TODO: Make that it unloads the
                                              // scenes, and not just deactivate them.
{
  if (m_scenes.find(name) != m_scenes.end()) {
    m_scenes[name]->setActive(false);
  }
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
SceneManager::partitionScene(const String& name)
{
  if (m_scenes.find(name) != m_scenes.end()) {
    m_spacePartition.calculateTree(BoxAAB(Vector3f{ -100.0f, -100.0f, -100.0f },
                                          Vector3f{  200.0f,  200.0f,  200.0f }),
                                   { m_scenes[name] });
  }
}
void
SceneManager::partitionAllScenes()
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