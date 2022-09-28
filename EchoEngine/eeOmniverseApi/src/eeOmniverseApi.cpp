#include "eeOmniverseApi.h"
#include <mutex>


#include <eeLogger.h>
#include <eeMemoryManager.h>
#include <eeResourceManager.h>

#include <eeScene.h>

#include <eeActor.h>
#include <eeCTransform.h>
#include <eeCBounds.h>
#include <eeCRender.h>
#include <eeMaterial.h>
#include <eeCStaticMesh.h>
#include <eeStaticMesh.h>
#include <eeCSkeletalMesh.h>
#include <eeSkeletalMesh.h>

#include <eeImage.h>

#include <eeStringUtilities.h>
#include <eeMath.h>
#include <eeFile.h>

#include <eeSerializationUtilities.h>



// Multiplatform array size
#define HW_ARRAY_COUNT(array) (sizeof(array) / sizeof(array[0]))

TF_DEFINE_PRIVATE_TOKENS(
  _tokens,
  (box)
  (DistantLight)
  (DomeLight)
  (Looks)
  (Root)
  (Shader)
  (st)

  // These tokens will be reworked or replaced by the official MDL schema for USD.
  // https://developer.nvidia.com/usd/MDLschema
  (Material)
  ((_module, "module"))
  (name)
  (out)
  ((shaderId, "mdlMaterial"))
  (mdl)

  // Tokens used for USD Preview Surface
  (diffuseColor)
  (normal)
  (file)
  (result)
  (varname)
  (rgb)
  (RAW)
  (sRGB)
  (surface)
  (PrimST)
  (UsdPreviewSurface)
  ((UsdShaderId, "UsdPreviewSurface"))
  ((PrimStShaderId, "UsdPrimvarReader_float2"))
  (UsdUVTexture)
);

namespace eeEngineSDK {
OmniverseApi::~OmniverseApi()
{
  destroy();
}
static bool gOmniverseLoggingEnabled = false;
static std::mutex gLogMutex;
// Omniverse Log callback
static void
logCallback(const char* threadName,
            const char* component,
            OmniClientLogLevel level,
            const char* message) noexcept
{
  std::unique_lock<std::mutex> lk(gLogMutex);
  if (gOmniverseLoggingEnabled) {
    puts(message);
  }
}
static void
OmniClientConnectionStatusCallbackImpl(void* userData,
                                       const char* url,
                                       OmniClientConnectionStatus status)
                                       noexcept
{
  // Let's just print this regardless
  std::unique_lock<std::mutex> lk(gLogMutex);
  std::cout << "Connection Status: "
            << omniClientGetConnectionStatusString(status)
            << " [" << url << "]" << std::endl;

  if (status == eOmniClientConnectionStatus_ConnectError) {
    // We shouldn't just exit here - we should clean up a bit, but we're going
    // to do it anyway
    //std::cout << "[ERROR] Failed connection, exiting." << std::endl;
    Logger::instance().consoleLog("[ERROR] Failed connection, exiting.");
    //exit(-1);
    OmniverseManager::instance().setStatus(eOMNI_STATUS::kFailed);
    OmniverseManager::instance().shutDown();
  }
}


// Get the Absolute path of the current executable
// Borrowed from https://stackoverflow.com/questions/1528298/get-path-of-executable
static fs::path getExePath()
{
#ifdef _WIN32
  wchar_t path[MAX_PATH] = { 0 };
  GetModuleFileNameW(NULL, path, MAX_PATH);
  return path;
#else
  char result[PATH_MAX];
  ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
  return std::string(result, (count > 0) ? count : 0);
#endif
}

void
failNotify(const String& msg, const String detail = "")
{
  std::unique_lock<std::mutex> lk(gLogMutex);

  //fprintf(stderr, "%s\n", msg);
  Logger::instance().consoleLog(msg);
  if (!detail.empty()) {
    //fprintf(stderr, "%s\n", detail);
    Logger::instance().consoleLog(detail);
  }
}

bool
OmniverseApi::init(bool doLiveEdit)
{
  // This is not strictly required for this sample because the sample copies all of the USD plugin
  // files to the correct place relative to the executable and current working directory.  This is
  // an instructional bit for apps that may not be able to do this.

  // Find absolute path of the resolver plugins `resources` folder
  std::string pluginResourcesFolder = getExePath().parent_path().string() + "/usd/omniverse/resources";
  PlugRegistry::GetInstance().RegisterPlugins(pluginResourcesFolder);
  std::string PluginName = "OmniUsdResolver";
  if (TfType::FindByName(PluginName).IsUnknown())
  {
    failNotify("Could not find the Omniverse USD Resolver plugin");
    return false;
  }

  // Register a function to be called whenever the library wants to print something to a log
  omniClientSetLogCallback(logCallback);

  // The default log level is "Info", set it to "Debug" to see all messages
  omniClientSetLogLevel(eOmniClientLogLevel_Debug);

  // Initialize the library and pass it the version constant defined in OmniClient.h
  // This allows the library to verify it was built with a compatible version. It will
  // return false if there is a version mismatch.
  if (!omniClientInitialize(kOmniClientVersion))
  {
    return false;
  }

  omniClientRegisterConnectionStatusCallback(nullptr, OmniClientConnectionStatusCallbackImpl);

  return true;
}
void
OmniverseApi::destroy()
{
  // Calling this prior to shutdown ensures that all pending live updates complete.
  omniClientLiveWaitForPendingUpdates();

  // The stage is a sophisticated object that needs to be destroyed properly.  
  // Since gStage is a smart pointer we can just reset it
  m_stage.Reset();

  omniClientShutdown();
}

// Create a new connection for this model in Omniverse, returns the created stage URL
void
OmniverseApi::createStage(const String& stageUrl)
{
  // Delete the old version of this file on Omniverse and wait for the operation to complete  
  {
    std::unique_lock<std::mutex> lk(gLogMutex);
    //std::cout << "Waiting for " << stageUrl << " to delete... " << std::endl;
    Logger::instance().consoleLog("Waiting for " + stageUrl + " to delete... ");
  }
  omniClientWait(omniClientDelete(stageUrl.c_str(), nullptr, nullptr));
  {
    std::unique_lock<std::mutex> lk(gLogMutex);
    //std::cout << "finished" << std::endl;
    Logger::instance().consoleLog("finished");
  }

  // Create this file in Omniverse cleanly
  m_stage = UsdStage::CreateNew(stageUrl);
  if (!m_stage) {
    failNotify("Failure to create model in Omniverse", stageUrl);
    return;
  }

  {
    std::unique_lock<std::mutex> lk(gLogMutex);
    //std::cout << "New stage created: " << stageUrl << std::endl;
    Logger::instance().consoleLog("New stage created: " + stageUrl);
  }

  // Always a good idea to declare your up-ness
  UsdGeomSetStageUpAxis(m_stage, UsdGeomTokens->y);

  // For physics its important to set units!
  UsdGeomSetStageMetersPerUnit(m_stage, 1.0f);


  // Keep the model contained inside of "Root", only need to do this once per model
  m_rootPrimPath = SdfPath::AbsoluteRootPath().AppendChild(_tokens->Root);
  UsdGeomXform rootPrim = UsdGeomXform::Define(m_stage, m_rootPrimPath);

  // Define the defaultPrim as the /Root prim
  m_stage->SetDefaultPrim(rootPrim.GetPrim());

  getFileName(eeStringtoWString(stageUrl), m_stageFileName);
}
void
OmniverseApi::openStage(const String& stageUrl)
{
  m_stage = UsdStage::Open(stageUrl);
  if (!m_stage) {
    failNotify("Failure to open stage in Omniverse:", stageUrl);
  }

  // Define the defaultPrim as the /Root prim
  UsdGeomXform rootPrim = static_cast<UsdGeomXform>(m_stage->GetDefaultPrim());
  m_rootPrimPath = rootPrim.GetPath();

  getFileName(eeStringtoWString(stageUrl), m_stageFileName);
}
void
OmniverseApi::closeStage()
{
  if (m_stage) {
    m_stage.Reset();
  }
}
void
updateStMeshCmpToScenegraph(const SdfPath& parentPath,
                            UsdStageRefPtr stage,
                            WPtr<CStaticMesh> stMeshCmp,
                            WPtr<Actor> sceneActor)
{
  if (sceneActor.expired()) return;
  auto& sActor = sceneActor.lock();

  //auto transCmp = sActor->getComponent<CTransform>();
  //if (transCmp.expired()) return;
  //auto sTransCmp = transCmp.lock();
  if (stMeshCmp.expired()) return;
  auto sStMeshCmp = stMeshCmp.lock();

  auto stMesh = sStMeshCmp->getStaticMesh().lock();
  if (!stMesh) return;
  auto meshes = stMesh->getMeshes();
  if (meshes.empty()) return;
  
  int32 meshIndex = 0;
  for (auto& stm : meshes) {
    // Create the geometry inside of "Root"
    String meshName("ChActM_" + eeToString(meshIndex++));
    SdfPath meshPrimPath = parentPath.AppendChild(TfToken(meshName));//_tokens->box);
    UsdGeomMesh mesh = UsdGeomMesh::Get(stage, meshPrimPath);

    if (!mesh) continue;

    // Set orientation
    mesh.CreateOrientationAttr(VtValue(UsdGeomTokens->leftHanded));

    // Add all of the vertices
    int num_vertices = stm.first.getTrianglesCount();
    auto& vertices = stm.first.getTrianglesArray();
    VtArray<GfVec3f> points;
    points.resize(num_vertices * 3);
    for (int i = 0; i < num_vertices; i++) {
      points[i * 3 + 0] = GfVec3f(-vertices[i].x.position.x, vertices[i].x.position.y, vertices[i].x.position.z) * 100.0f;
      points[i * 3 + 1] = GfVec3f(-vertices[i].y.position.x, vertices[i].y.position.y, vertices[i].y.position.z) * 100.0f;
      points[i * 3 + 2] = GfVec3f(-vertices[i].z.position.x, vertices[i].z.position.y, vertices[i].z.position.z) * 100.0f;
    }
    mesh.CreatePointsAttr(VtValue(points));
    
    // Calculate indices for each triangle
    int num_indices = stm.first.getIndexCount();
    auto& indicesArr = stm.first.getIndicesArray();
    VtArray<int> vecIndices;
    vecIndices.resize(num_indices);
    for (int i = 0; i < num_indices; i++) {
      vecIndices[i] = indicesArr[i];
    }
    mesh.CreateFaceVertexIndicesAttr(VtValue(vecIndices));
    
    // Add vertex normals
    int num_normals = stm.first.getTrianglesCount();
    VtArray<GfVec3f> meshNormals;
    meshNormals.resize(num_normals * 3);
    for (int i = 0; i < num_normals; i++) {
      meshNormals[i * 3 + 0] = GfVec3f(-vertices[i].x.normal.x, vertices[i].x.normal.y, vertices[i].x.normal.z);
      meshNormals[i * 3 + 1] = GfVec3f(-vertices[i].y.normal.x, vertices[i].y.normal.y, vertices[i].y.normal.z);
      meshNormals[i * 3 + 2] = GfVec3f(-vertices[i].z.normal.x, vertices[i].z.normal.y, vertices[i].z.normal.z);
    }
    mesh.CreateNormalsAttr(VtValue(meshNormals));
    
    // Add face vertex count
    VtArray<int> faceVertexCounts;
    faceVertexCounts.resize(stm.first.getTrianglesCount());
    std::fill(faceVertexCounts.begin(), faceVertexCounts.end(), 3);
    mesh.CreateFaceVertexCountsAttr(VtValue(faceVertexCounts));
    
    // Set the color on the mesh
    UsdPrim meshPrim = mesh.GetPrim();
    UsdAttribute displayColorAttr = mesh.CreateDisplayColorAttr();
    {
      VtVec3fArray valueArray;
      GfVec3f rgbFace(0.463f, 0.725f, 0.0f);
      valueArray.push_back(rgbFace);
      displayColorAttr.Set(valueArray);
    }
    
    // Set the UV (st) values for this mesh
    UsdGeomPrimvar attr2 = mesh.CreatePrimvar(_tokens->st, SdfValueTypeNames->TexCoord2fArray);
    {
      int uv_count = stm.first.getTrianglesCount();
      VtVec2fArray valueArray;
      valueArray.resize(uv_count * 3);
      for (int i = 0; i < uv_count; ++i)
      {
        valueArray[i * 3 + 0].Set(vertices[i].x.uvCoord.x, 1.0f - vertices[i].x.uvCoord.y);
        valueArray[i * 3 + 1].Set(vertices[i].y.uvCoord.x, 1.0f - vertices[i].y.uvCoord.y);
        valueArray[i * 3 + 2].Set(vertices[i].z.uvCoord.x, 1.0f - vertices[i].z.uvCoord.y);
      }
    
      bool status = attr2.Set(valueArray);
    }
    attr2.SetInterpolation(UsdGeomTokens->vertex);



    String matName("Mat_" + stm.second.lock()->getResourceName());
    SdfPath matPath = meshPrimPath.AppendChild(TfToken("Mat_Pat"));
    auto mat = UsdShadeMaterial::Get(stage, matPath);
    
    auto pbrShader = UsdShadeShader::Get(stage, matPath.AppendChild(TfToken("PBRShader")));
    pbrShader.GetInput(TfToken("roughness")).Set(0.4f);
    pbrShader.GetInput(TfToken("metallic")).Set(0.0f);
    
    auto tex = stm.second.lock()->getTexturesMap();
    auto img = tex[0].lock()->getImages()[0];
    
    String imgPath = "D:/GitHub/MotoresIDV7_EchoEngine/EchoEngine/bin/" + img->getPath();
    
    auto diffuseTextureSampler = UsdShadeShader::Get(stage, matPath.AppendChild(TfToken("diffuseTexture")));
    diffuseTextureSampler.GetInput(TfToken("file")).Set(SdfAssetPath(imgPath));
  }
}
void
updateSkMeshCmpToScenegraph(const SdfPath& parentPath,
                            UsdStageRefPtr stage,
                            WPtr<CSkeletalMesh> skMeshCmp,
                            WPtr<Actor> sceneActor)
{
  if (sceneActor.expired()) return;
  auto& sActor = sceneActor.lock();

  //auto transCmp = sActor->getComponent<CTransform>();
  //if (transCmp.expired()) return;
  //auto sTransCmp = transCmp.lock();
  if (skMeshCmp.expired()) return;
  auto sSkMeshCmp = skMeshCmp.lock();

  auto skMesh = sSkMeshCmp->getModel().lock();
  if (!skMesh) return;
  auto meshes = skMesh->getMeshes();
  if (meshes.empty()) return;
  
  int32 meshIndex = 0;
  for (auto& stm : meshes) {
    // Create the geometry inside of "Root"
    String meshName("ChActM_" + eeToString(meshIndex++));
    SdfPath meshPrimPath = parentPath.AppendChild(TfToken(meshName));//_tokens->box);
    UsdGeomMesh mesh = UsdGeomMesh::Get(stage, meshPrimPath);

    if (!mesh) continue;

    // Add all of the vertices
    int num_vertices = stm.first.getVertexCount();
    auto& vertices = stm.first.getVertexArray();
    VtArray<GfVec3f> points;
    points.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
      points[i] = GfVec3f(-vertices[i].position.x, vertices[i].position.y, vertices[i].position.z) * 100.0f;
    }
    mesh.CreatePointsAttr(VtValue(points));
    
    // Calculate indices for each triangle
    int num_indices = stm.first.getIndexCount();
    auto& indicesArr = stm.first.getIndexArray();
    VtArray<int> vecIndices;
    vecIndices.resize(num_indices);
    for (int i = 0; i < num_indices; i++) {
      vecIndices[i] = indicesArr[i];
    }
    mesh.CreateFaceVertexIndicesAttr(VtValue(vecIndices));
    
    // Add vertex normals
    int num_normals = stm.first.getVertexCount();
    VtArray<GfVec3f> meshNormals;
    meshNormals.resize(num_normals);
    for (int i = 0; i < num_normals; i++) {
      meshNormals[i] = GfVec3f(-vertices[i].normal.x, vertices[i].normal.y, vertices[i].normal.z);
    }
    mesh.CreateNormalsAttr(VtValue(meshNormals));
    
    // Add face vertex count
    VtArray<int> faceVertexCounts;
    faceVertexCounts.resize(num_indices / 3);
    std::fill(faceVertexCounts.begin(), faceVertexCounts.end(), 3);
    mesh.CreateFaceVertexCountsAttr(VtValue(faceVertexCounts));
    
    // Set the color on the mesh
    UsdPrim meshPrim = mesh.GetPrim();
    UsdAttribute displayColorAttr = mesh.GetDisplayColorAttr();
    {
      VtVec3fArray valueArray;
      GfVec3f rgbFace(0.463f, 0.725f, 0.0f);
      valueArray.push_back(rgbFace);
      displayColorAttr.Set(valueArray);
    }
    
    // Set the UV (st) values for this mesh
    UsdGeomPrimvar attr2 = mesh.GetPrimvar(_tokens->st);
    {
      int uv_count = stm.first.getVertexCount();
      VtVec2fArray valueArray;
      valueArray.resize(uv_count);
      for (int i = 0; i < uv_count; ++i)
      {
        valueArray[i].Set(vertices[i].uvCoord.x, 1.0f - vertices[i].uvCoord.y);
      }
    
      bool status = attr2.Set(valueArray);
    }
    attr2.SetInterpolation(UsdGeomTokens->vertex);


    String matName("Mat_" + stm.second.lock()->getResourceName());
    SdfPath matPath = meshPrimPath.AppendChild(TfToken("Mat_Pat"));
    auto mat = UsdShadeMaterial::Get(stage, matPath);
    
    auto pbrShader = UsdShadeShader::Get(stage, matPath.AppendChild(TfToken("PBRShader")));
    pbrShader.GetInput(TfToken("roughness")).Set(0.4f);
    pbrShader.GetInput(TfToken("metallic")).Set(0.0f);
    
    auto tex = stm.second.lock()->getTexturesMap();
    auto img = tex[0].lock()->getImages()[0];
    
    String imgPath = "D:/GitHub/MotoresIDV7_EchoEngine/EchoEngine/bin/" + img->getPath();
    
    auto diffuseTextureSampler = UsdShadeShader::Get(stage, matPath.AppendChild(TfToken("diffuseTexture")));
    diffuseTextureSampler.GetInput(TfToken("file")).Set(SdfAssetPath(imgPath));
  }
}
void
updateActorToScenegraph(const SdfPath& parentPath,
                        UsdStageRefPtr stage,
                        WPtr<Actor> sceneActor)
{
  if (sceneActor.expired()) return;

  auto& memoryMan = MemoryManager::instance();

  auto& sActor = sceneActor.lock();

  auto transCmp = sActor->getComponent<CTransform>();
  if (transCmp.expired()) return;
  auto sTransCmp = transCmp.lock();

  UsdGeomXform act = UsdGeomXform::Get(stage, parentPath);

  const auto& actorTrans = sTransCmp->getTransformObj();
  Vector3f transPos = actorTrans.getPosition() * 100.0f;
  Vector3f transRot = actorTrans.getRotation().getEuclidean() * Math::k180_OVER_PI;
  Vector3f transScale = actorTrans.getScale();

  UsdGeomXformable xForm = act;

  // Define storage for the different xform ops that Omniverse Kit likes to use
  UsdGeomXformOp translateOp;
  UsdGeomXformOp rotateOp;
  UsdGeomXformOp scaleOp;
  GfVec3f position(0);
  GfVec3f rotXYZ(0);
  GfVec3f scale(1);

  // Get the xform ops stack
  bool resetXformStack = false;
  std::vector<UsdGeomXformOp> xFormOps = xForm.GetOrderedXformOps(&resetXformStack);

  // Get the current xform op values
  for (size_t i = 0; i < xFormOps.size(); i++)
  {
    switch (xFormOps[i].GetOpType()) {
    case UsdGeomXformOp::TypeTranslate:
      translateOp = xFormOps[i];
      translateOp.Get(&position);
      break;
    case UsdGeomXformOp::TypeRotateXYZ:
      rotateOp = xFormOps[i];
      rotateOp.Get(&rotXYZ);
      break;
    case UsdGeomXformOp::TypeScale:
      scaleOp = xFormOps[i];
      scaleOp.Get(&scale);
      break;
    }
  }

  position = GfVec3f(-transPos.x, transPos.y, transPos.z);
  rotXYZ = GfVec3f(transRot.x, -transRot.y, -transRot.z);
  scale = GfVec3f(transScale.x, transScale.y, transScale.z);

  // A utility class to set the position, rotation, or scale values
  class SetOp
  {
  public:
    SetOp(UsdGeomXformable& xForm, UsdGeomXformOp& op, UsdGeomXformOp::Type opType, const GfVec3f& value, const UsdGeomXformOp::Precision precision)
    {
      if (!op)
      {
        op = xForm.AddXformOp(opType, precision);
        std::unique_lock<std::mutex> lk(gLogMutex);
        std::cout << " Adding " << UsdGeomXformOp::GetOpTypeToken(opType) << std::endl;
      }

      if (op.GetPrecision() == UsdGeomXformOp::Precision::PrecisionFloat)
        op.Set(GfVec3f(value));
      else
        op.Set(value);

      std::unique_lock<std::mutex> lk(gLogMutex);
      std::cout << " Setting " << UsdGeomXformOp::GetOpTypeToken(opType) << std::endl;
    }
  };

  SetOp(xForm, translateOp, UsdGeomXformOp::TypeTranslate, position, UsdGeomXformOp::Precision::PrecisionFloat);
  SetOp(xForm, rotateOp, UsdGeomXformOp::TypeRotateXYZ, rotXYZ, UsdGeomXformOp::Precision::PrecisionFloat);
  SetOp(xForm, scaleOp, UsdGeomXformOp::TypeScale, scale, UsdGeomXformOp::Precision::PrecisionFloat);

  // Make sure the xform op order is correct (translate, rotate, scale)
  std::vector<UsdGeomXformOp> xFormOpsReordered;
  xFormOpsReordered.push_back(translateOp);
  xFormOpsReordered.push_back(rotateOp);
  xFormOpsReordered.push_back(scaleOp);
  xForm.SetXformOpOrder(xFormOpsReordered);


  //const auto& actorComponents = sActor->getAllComponents();
  //
  //for (const auto& cmp : actorComponents) {
  //  switch (cmp->getType()) {
  //  case eCOMPONENT_TYPE::kStaticMesh:
  //    updateStMeshCmpToScenegraph(parentPath,
  //                                stage,
  //                                memoryMan.reinterpretPtr<CStaticMesh>(cmp),
  //                                sceneActor);
  //    break;
  //  case eCOMPONENT_TYPE::kSkeletalMesh:
  //    updateSkMeshCmpToScenegraph(parentPath,
  //                                stage,
  //                                memoryMan.reinterpretPtr<CSkeletalMesh>(cmp),
  //                                sceneActor);
  //    break;
  //  }
  //}
}
void
updateActorOnStageHelper(const SdfPath& parentPath,
                         UsdStageRefPtr stage,
                         SPtr<ActorNode> actNode)
{
  auto& sActor = actNode->actorValue.lock();
  String parentName(sActor->getName());
  SdfPath parentPrimPath = parentPath.AppendChild(TfToken(parentName));

  updateActorToScenegraph(parentPrimPath, stage, actNode->actorValue);

  for (auto& a : actNode->childrenNode) {
    updateActorOnStageHelper(parentPrimPath, stage, a);
  }
}
void
updateScenegraphOnStage(WPtr<Scene> scenegraph,
                        const SdfPath& rootPath,
                        UsdStageRefPtr stage)
{
  auto& actorsTree = scenegraph.lock()->getActorsTree();
  for (auto& a : actorsTree) {
    updateActorOnStageHelper(rootPath, stage, a);
  }
}
void
OmniverseApi::saveStage()
{
  updateScenegraphOnStage(m_openedScenegraph, m_rootPrimPath, m_stage);

  m_stage->Save();
}
String
getConnectedUsername(const String& stageUrl)
{
  // Get the username for the connection
  String userName("_none_");
  omniClientWait(
  omniClientGetServerInfo(stageUrl.c_str(),
                          &userName,
  [](void* userData,
     OmniClientResult result,
     struct OmniClientServerInfo const* info) noexcept
  {
    auto userName = static_cast<String*>(userData);
    if (userData && userName && info && info->username)
    {
      userName->assign(info->username);
    }
  }));

  return userName;
}
String
OmniverseApi::getUserLocalPath()
{
  String userFolder = "omniverse://localhost/Users";
  String username = getConnectedUsername(userFolder);
  return userFolder + "/" + username;
}
void
addStMeshCmpToScenegraph(const SdfPath& parentPath,
                         UsdStageRefPtr stage,
                         WPtr<CStaticMesh> stMeshCmp,
                         WPtr<Actor> sceneActor)
{
  if (sceneActor.expired()) return;
  auto& sActor = sceneActor.lock();

  //auto transCmp = sActor->getComponent<CTransform>();
  //if (transCmp.expired()) return;
  //auto sTransCmp = transCmp.lock();
  if (stMeshCmp.expired()) return;
  auto sStMeshCmp = stMeshCmp.lock();

  auto stMesh = sStMeshCmp->getStaticMesh().lock();
  if (!stMesh) return;
  auto meshes = stMesh->getMeshes();
  if (meshes.empty()) return;
  
  int32 meshIndex = 0;
  for (auto& stm : meshes) {
    // Create the geometry inside of "Root"
    String meshName("ChActM_" + eeToString(meshIndex++));
    SdfPath meshPrimPath = parentPath.AppendChild(TfToken(meshName));//_tokens->box);
    UsdGeomMesh mesh = UsdGeomMesh::Define(stage, meshPrimPath);

    if (!mesh) continue;

    // Set orientation
    mesh.CreateOrientationAttr(VtValue(UsdGeomTokens->leftHanded));

    // Add all of the vertices
    int num_vertices = stm.first.getTrianglesCount();
    auto& vertices = stm.first.getTrianglesArray();
    VtArray<GfVec3f> points;
    points.resize(num_vertices * 3);
    for (int i = 0; i < num_vertices; i++) {
      points[i * 3 + 0] = GfVec3f(-vertices[i].x.position.x, vertices[i].x.position.y, vertices[i].x.position.z) * 100.0f;
      points[i * 3 + 1] = GfVec3f(-vertices[i].y.position.x, vertices[i].y.position.y, vertices[i].y.position.z) * 100.0f;
      points[i * 3 + 2] = GfVec3f(-vertices[i].z.position.x, vertices[i].z.position.y, vertices[i].z.position.z) * 100.0f;
    }
    mesh.CreatePointsAttr(VtValue(points));
    
    // Calculate indices for each triangle
    int num_indices = stm.first.getIndexCount();
    auto& indicesArr = stm.first.getIndicesArray();
    VtArray<int> vecIndices;
    vecIndices.resize(num_indices);
    for (int i = 0; i < num_indices; i++) {
      vecIndices[i] = indicesArr[i];
    }
    mesh.CreateFaceVertexIndicesAttr(VtValue(vecIndices));
    
    // Add vertex normals
    int num_normals = stm.first.getTrianglesCount();
    VtArray<GfVec3f> meshNormals;
    meshNormals.resize(num_normals * 3);
    for (int i = 0; i < num_normals; i++) {
      meshNormals[i * 3 + 0] = GfVec3f(-vertices[i].x.normal.x, vertices[i].x.normal.y, vertices[i].x.normal.z);
      meshNormals[i * 3 + 1] = GfVec3f(-vertices[i].y.normal.x, vertices[i].y.normal.y, vertices[i].y.normal.z);
      meshNormals[i * 3 + 2] = GfVec3f(-vertices[i].z.normal.x, vertices[i].z.normal.y, vertices[i].z.normal.z);
    }
    mesh.CreateNormalsAttr(VtValue(meshNormals));
    
    // Add face vertex count
    VtArray<int> faceVertexCounts;
    faceVertexCounts.resize(stm.first.getTrianglesCount());
    std::fill(faceVertexCounts.begin(), faceVertexCounts.end(), 3);
    mesh.CreateFaceVertexCountsAttr(VtValue(faceVertexCounts));
    
    // Set the color on the mesh
    UsdPrim meshPrim = mesh.GetPrim();
    UsdAttribute displayColorAttr = mesh.CreateDisplayColorAttr();
    {
      VtVec3fArray valueArray;
      GfVec3f rgbFace(0.463f, 0.725f, 0.0f);
      valueArray.push_back(rgbFace);
      displayColorAttr.Set(valueArray);
    }
    
    // Set the UV (st) values for this mesh
    UsdGeomPrimvar attr2 = mesh.CreatePrimvar(_tokens->st, SdfValueTypeNames->TexCoord2fArray);
    {
      int uv_count = stm.first.getTrianglesCount();
      VtVec2fArray valueArray;
      valueArray.resize(uv_count * 3);
      for (int i = 0; i < uv_count; ++i)
      {
        valueArray[i * 3 + 0].Set(vertices[i].x.uvCoord.x, 1.0f - vertices[i].x.uvCoord.y);
        valueArray[i * 3 + 1].Set(vertices[i].y.uvCoord.x, 1.0f - vertices[i].y.uvCoord.y);
        valueArray[i * 3 + 2].Set(vertices[i].z.uvCoord.x, 1.0f - vertices[i].z.uvCoord.y);
      }
    
      bool status = attr2.Set(valueArray);
    }
    attr2.SetInterpolation(UsdGeomTokens->vertex);
    
    //const auto& actorTrans = sTransCmp->getTransformObj();
    //Vector3f transPos = actorTrans.getPosition();
    //Vector3f transRot = actorTrans.getRotation().getEuclidean();
    //Vector3f transScale = actorTrans.getScale();
    // 
    //mesh.AddTranslateOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(-transPos.x, transPos.y, transPos.z) * 100.f);
    //mesh.AddRotateXYZOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(transRot.x, transRot.y, transRot.z) * Math::k180_OVER_PI);
    //mesh.AddScaleOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(transScale.x, transScale.y, transScale.z));



    String matName("Mat_" + stm.second.lock()->getResourceName());
    SdfPath matPath = meshPrimPath.AppendChild(TfToken("Mat_Pat"));
    auto mat = UsdShadeMaterial::Define(stage, matPath);
    
    auto pbrShader = UsdShadeShader::Define(stage, matPath.AppendChild(TfToken("PBRShader")));
    pbrShader.CreateIdAttr(VtValue(TfToken("UsdPreviewSurface")));
    pbrShader.CreateInput(TfToken("roughness"), SdfValueTypeNames->Float).Set(0.4f);
    pbrShader.CreateInput(TfToken("metallic"), SdfValueTypeNames->Float).Set(0.0f);
    
    mat.CreateSurfaceOutput().ConnectToSource(pbrShader.ConnectableAPI(), TfToken("surface"));
    
    auto stReader = UsdShadeShader::Define(stage, matPath.AppendChild(TfToken("stReader")));
    stReader.CreateIdAttr(VtValue(TfToken("UsdPrimvarReader_float2")));
    
    auto tex = stm.second.lock()->getTexturesMap();
    auto img = tex[0].lock()->getImages()[0];
    
    String imgPath = "D:/GitHub/MotoresIDV7_EchoEngine/EchoEngine/bin/" + img->getPath();
    
    auto diffuseTextureSampler = UsdShadeShader::Define(stage, matPath.AppendChild(TfToken("diffuseTexture")));
    diffuseTextureSampler.CreateIdAttr(VtValue(TfToken("UsdUVTexture")));
    diffuseTextureSampler.CreateInput(TfToken("file"), SdfValueTypeNames->Asset).Set(SdfAssetPath(imgPath));
    //diffuseTextureSampler.CreateInput(TfToken("rgba"), SdfValueTypeNames->Color4fArray).Set(VtVec4fArray());
    diffuseTextureSampler.CreateInput(TfToken("st"), SdfValueTypeNames->Float2).ConnectToSource(stReader.ConnectableAPI(), TfToken("result"));
    diffuseTextureSampler.CreateOutput(TfToken("rgb"), SdfValueTypeNames->Float3);
    pbrShader.CreateInput(TfToken("diffuseColor"), SdfValueTypeNames->Color3f).ConnectToSource(diffuseTextureSampler.ConnectableAPI(), TfToken("rgb"));
    
    auto stInput = mat.CreateInput(TfToken("frame:stPrimvarName"), SdfValueTypeNames->Token);
    stInput.Set(TfToken("st"));
    
    stReader.CreateInput(TfToken("varname"), SdfValueTypeNames->Token).ConnectToSource(stInput);
    UsdShadeMaterialBindingAPI(mesh).Bind(mat);
  }
}
void
addSkMeshCmpToScenegraph(const SdfPath& parentPath,
                         UsdStageRefPtr stage,
                         WPtr<CSkeletalMesh> skMeshCmp,
                         WPtr<Actor> sceneActor)
{
  if (sceneActor.expired()) return;
  auto& sActor = sceneActor.lock();

  //auto transCmp = sActor->getComponent<CTransform>();
  //if (transCmp.expired()) return;
  //auto sTransCmp = transCmp.lock();
  if (skMeshCmp.expired()) return;
  auto sSkMeshCmp = skMeshCmp.lock();

  auto skMesh = sSkMeshCmp->getModel().lock();
  if (!skMesh) return;
  auto meshes = skMesh->getMeshes();
  if (meshes.empty()) return;
  
  int32 meshIndex = 0;
  for (auto& stm : meshes) {
    // Create the geometry inside of "Root"
    String meshName("ChActM_" + eeToString(meshIndex++));
    SdfPath meshPrimPath = parentPath.AppendChild(TfToken(meshName));//_tokens->box);
    UsdGeomMesh mesh = UsdGeomMesh::Define(stage, meshPrimPath);

    if (!mesh) continue;

    // Set orientation
    mesh.CreateOrientationAttr(VtValue(UsdGeomTokens->leftHanded));

    // Add all of the vertices
    int num_vertices = stm.first.getVertexCount();
    auto& vertices = stm.first.getVertexArray();
    VtArray<GfVec3f> points;
    points.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
      points[i] = GfVec3f(-vertices[i].position.x, vertices[i].position.y, vertices[i].position.z) * 100.0f;
    }
    mesh.CreatePointsAttr(VtValue(points));
    
    // Calculate indices for each triangle
    int num_indices = stm.first.getIndexCount();
    auto& indicesArr = stm.first.getIndexArray();
    VtArray<int> vecIndices;
    vecIndices.resize(num_indices);
    for (int i = 0; i < num_indices; i++) {
      vecIndices[i] = indicesArr[i];
    }
    mesh.CreateFaceVertexIndicesAttr(VtValue(vecIndices));
    
    // Add vertex normals
    int num_normals = stm.first.getVertexCount();
    VtArray<GfVec3f> meshNormals;
    meshNormals.resize(num_normals);
    for (int i = 0; i < num_normals; i++) {
      meshNormals[i] = GfVec3f(-vertices[i].normal.x, vertices[i].normal.y, vertices[i].normal.z);
    }
    mesh.CreateNormalsAttr(VtValue(meshNormals));
    
    // Add face vertex count
    VtArray<int> faceVertexCounts;
    faceVertexCounts.resize(num_indices / 3);
    std::fill(faceVertexCounts.begin(), faceVertexCounts.end(), 3);
    mesh.CreateFaceVertexCountsAttr(VtValue(faceVertexCounts));
    
    // Set the color on the mesh
    UsdPrim meshPrim = mesh.GetPrim();
    UsdAttribute displayColorAttr = mesh.CreateDisplayColorAttr();
    {
      VtVec3fArray valueArray;
      GfVec3f rgbFace(0.463f, 0.725f, 0.0f);
      valueArray.push_back(rgbFace);
      displayColorAttr.Set(valueArray);
    }
    
    // Set the UV (st) values for this mesh
    UsdGeomPrimvar attr2 = mesh.CreatePrimvar(_tokens->st, SdfValueTypeNames->TexCoord2fArray);
    {
      int uv_count = stm.first.getVertexCount();
      VtVec2fArray valueArray;
      valueArray.resize(uv_count);
      for (int i = 0; i < uv_count; ++i)
      {
        valueArray[i].Set(vertices[i].uvCoord.x, 1.0f - vertices[i].uvCoord.y);
      }
    
      bool status = attr2.Set(valueArray);
    }
    attr2.SetInterpolation(UsdGeomTokens->vertex);
    
    //const auto& actorTrans = sTransCmp->getTransformObj();
    //Vector3f transPos = actorTrans.getPosition();
    //Vector3f transRot = actorTrans.getRotation().getEuclidean();
    //Vector3f transScale = actorTrans.getScale();
    //
    //mesh.AddTranslateOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(-transPos.x, transPos.y, transPos.z) * 100.f);
    //mesh.AddRotateXYZOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(transRot.x, transRot.y, transRot.z) * Math::k180_OVER_PI);
    //mesh.AddScaleOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(transScale.x, transScale.y, transScale.z));


    String matName("Mat_" + stm.second.lock()->getResourceName());
    SdfPath matPath = meshPrimPath.AppendChild(TfToken("Mat_Pat"));
    auto mat = UsdShadeMaterial::Define(stage, matPath);
    
    auto pbrShader = UsdShadeShader::Define(stage, matPath.AppendChild(TfToken("PBRShader")));
    pbrShader.CreateIdAttr(VtValue(TfToken("UsdPreviewSurface")));
    pbrShader.CreateInput(TfToken("roughness"), SdfValueTypeNames->Float).Set(0.4f);
    pbrShader.CreateInput(TfToken("metallic"), SdfValueTypeNames->Float).Set(0.0f);
    
    mat.CreateSurfaceOutput().ConnectToSource(pbrShader.ConnectableAPI(), TfToken("surface"));
    
    auto stReader = UsdShadeShader::Define(stage, matPath.AppendChild(TfToken("stReader")));
    stReader.CreateIdAttr(VtValue(TfToken("UsdPrimvarReader_float2")));
    
    auto tex = stm.second.lock()->getTexturesMap();
    auto img = tex[0].lock()->getImages()[0];
    
    String imgPath = "D:/GitHub/MotoresIDV7_EchoEngine/EchoEngine/bin/" + img->getPath();
    
    auto diffuseTextureSampler = UsdShadeShader::Define(stage, matPath.AppendChild(TfToken("diffuseTexture")));
    diffuseTextureSampler.CreateIdAttr(VtValue(TfToken("UsdUVTexture")));
    diffuseTextureSampler.CreateInput(TfToken("file"), SdfValueTypeNames->Asset).Set(SdfAssetPath(imgPath));
    //diffuseTextureSampler.CreateInput(TfToken("rgba"), SdfValueTypeNames->Color4fArray).Set(VtVec4fArray());
    diffuseTextureSampler.CreateInput(TfToken("st"), SdfValueTypeNames->Float2).ConnectToSource(stReader.ConnectableAPI(), TfToken("result"));
    diffuseTextureSampler.CreateOutput(TfToken("rgb"), SdfValueTypeNames->Float3);
    pbrShader.CreateInput(TfToken("diffuseColor"), SdfValueTypeNames->Color3f).ConnectToSource(diffuseTextureSampler.ConnectableAPI(), TfToken("rgb"));
    
    auto stInput = mat.CreateInput(TfToken("frame:stPrimvarName"), SdfValueTypeNames->Token);
    stInput.Set(TfToken("st"));
    
    stReader.CreateInput(TfToken("varname"), SdfValueTypeNames->Token).ConnectToSource(stInput);
    UsdShadeMaterialBindingAPI(mesh).Bind(mat);
  }
}
void
addActorToScenegraph(const SdfPath& parentPath,
                     UsdStageRefPtr stage,
                     WPtr<Actor> sceneActor)
{
  if (sceneActor.expired()) return;

  auto& memoryMan = MemoryManager::instance();

  auto& sActor = sceneActor.lock();

  auto transCmp = sActor->getComponent<CTransform>();
  if (transCmp.expired()) return;
  auto sTransCmp = transCmp.lock();

  UsdGeomXform act = UsdGeomXform::Define(stage, parentPath);

  const auto& actorTrans = sTransCmp->getTransformObj();
  Vector3f transPos = actorTrans.getPosition();
  Vector3f transRot = actorTrans.getRotation().getEuclidean();
  Vector3f transScale = actorTrans.getScale();

  act.AddTranslateOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(-transPos.x, transPos.y, transPos.z) * 100.f);
  act.AddRotateXYZOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(transRot.x, -transRot.y, -transRot.z) * Math::k180_OVER_PI);
  act.AddScaleOp(UsdGeomXformOp::PrecisionFloat).Set(GfVec3f(transScale.x, transScale.y, transScale.z));


  const auto& actorComponents = sActor->getAllComponents();

  for (const auto& cmp : actorComponents) {
    switch (cmp->getType()) {
    case eCOMPONENT_TYPE::kStaticMesh:
      addStMeshCmpToScenegraph(parentPath,
                               stage,
                               memoryMan.reinterpretPtr<CStaticMesh>(cmp),
                               sceneActor);
      break;
    case eCOMPONENT_TYPE::kSkeletalMesh:
      addSkMeshCmpToScenegraph(parentPath,
                               stage,
                               memoryMan.reinterpretPtr<CSkeletalMesh>(cmp),
                               sceneActor);
      break;
    }
  }
}
bool
setActorOnStageHelper(const SdfPath& parentPath,
                      UsdStageRefPtr stage,
                      SPtr<ActorNode> actNode)
{
  auto& sActor = actNode->actorValue.lock();
  String parentName(sActor->getName());
  SdfPath parentPrimPath = parentPath.AppendChild(TfToken(parentName));

  addActorToScenegraph(parentPrimPath, stage, actNode->actorValue);

  for (auto& a : actNode->childrenNode) {
    setActorOnStageHelper(parentPrimPath, stage, a);
  }

  return true;
}
bool
OmniverseApi::setScenegraphOnStage(WPtr<Scene> scenegraph)
{
  m_openedScenegraph = scenegraph;
  auto& actorsTree = m_openedScenegraph.lock()->getActorsTree();
  for (auto& a : actorsTree) {
    setActorOnStageHelper(m_rootPrimPath, m_stage, a);
  }

  // Commit the changes to the USD
  omniClientLiveProcess();
  m_stage->Save();
  return true;
}
void
loadMeshFromStage(const UsdGeomMesh& meshNode,
                  WPtr<Actor> actorMesh,
                  bool firstTime)
{
  auto stMeshCmp = actorMesh.lock()->getComponent<CStaticMesh>().lock();
  if (!stMeshCmp) {
    stMeshCmp = actorMesh.lock()->addComponent<CStaticMesh>().lock();
  }

  Mesh mesh;
  WPtr<Material> mat;
  Vector<ComplexVertex> verticesArr;
  float furtherDist = 0.0f;
  Vector3f maxCoord = Vector3f(-99999.9f, -99999.9f, -99999.9f);
  Vector3f minCoord = Vector3f(99999.9f, 99999.9f, 99999.9f);

  const auto& pointsAtrr = meshNode.GetPointsAttr();
  VtValue pointsVal;
  pointsAtrr.Get(&pointsVal);
  const auto& points = pointsVal.Get<VtArray<GfVec3f>>();

  SIZE_T pointsCount = points.size();
  Vector<Vector4f> pointsArrVal;
  pointsArrVal.resize(pointsCount);
  for (SIZE_T i = 0; i < pointsCount; ++i) {
    const float* pointArr = points[i].GetArray();
    Vector3f point = Vector3f(-pointArr[0],
                               pointArr[1],
                               pointArr[2]) * 0.01f;

    float dist = point.getMagnitude();
    furtherDist = furtherDist > dist ? furtherDist : dist;

    maxCoord.x = maxCoord.x > point.x ? maxCoord.x : point.x;
    maxCoord.y = maxCoord.y > point.y ? maxCoord.y : point.y;
    maxCoord.z = maxCoord.z > point.z ? maxCoord.z : point.z;

    minCoord.x = minCoord.x < point.x ? minCoord.x : point.x;
    minCoord.y = minCoord.y < point.y ? minCoord.y : point.y;
    minCoord.z = minCoord.z < point.z ? minCoord.z : point.z;

    
    pointsArrVal[i] = Vector4f(point.x,
                               point.y,
                               point.z,
                               1.0f);
  }

  const auto& normsAtrr = meshNode.GetNormalsAttr();
  VtValue normsVal;
  normsAtrr.Get(&normsVal);
  const auto& normals = normsVal.Get<VtArray<GfVec3f>>();

  SIZE_T normalsCount = normals.size();
  Vector<Vector4f> normalsArrVal;
  Vector<Vector4f> binormsArrVal;
  Vector<Vector4f> tansArrVal;
  normalsArrVal.resize(normalsCount);
  binormsArrVal.resize(normalsCount);
  tansArrVal.resize(normalsCount);
  for (SIZE_T i = 0; i < normalsCount; ++i) {
    const float* normalArr = normals[i].GetArray();
    normalsArrVal[i] = Vector4f(-normalArr[0],
                                 normalArr[1],
                                 normalArr[2],
                                 0.0f).getNormalize();
    binormsArrVal[i] = Vector4f(0.0f,
                                0.0f,
                                0.0f,
                                0.0f);
    tansArrVal[i] = Vector4f(0.0f,
                             0.0f,
                             0.0f,
                             0.0f);
  }

  const auto& primVarUV = meshNode.GetPrimvar(_tokens->st);
  VtVec2fArray uvsArr;
  primVarUV.Get<VtVec2fArray>(&uvsArr);

  SIZE_T uvsCount = uvsArr.size();
  Vector<Vector4f> uvsArrVal;
  uvsArrVal.resize(uvsCount);
  for (SIZE_T i = 0; i < uvsCount; ++i) {
    const float* uvArr = uvsArr[i].GetArray();
    uvsArrVal[i] = Vector4f(uvArr[0],
                            1.0f - uvArr[1],
                            0.0f,
                            0.0f);
  }

  SIZE_T verticesCount = pointsArrVal.size();
  verticesArr.resize(verticesCount);
  for (SIZE_T i = 0; i < verticesCount; ++i) {
    verticesArr[i] = ComplexVertex{pointsArrVal[i],
                                   uvsArrVal[i],
                                   normalsArrVal[i],
                                   binormsArrVal[i],
                                   tansArrVal[i]};
  }

  

  const auto& indicesAtrr = meshNode.GetFaceVertexIndicesAttr();
  VtValue indicesVal;
  indicesAtrr.Get(&indicesVal);
  const auto& indices = indicesVal.Get<VtArray<int>>();

  SIZE_T indicesCount = indices.size();
  Vector<uint32> indicesArrVal;
  indicesArrVal.resize(indicesCount);
  for (SIZE_T i = 0; i < indicesCount; ++i) {
    indicesArrVal[i] = indices[i];
  }


  mesh.loadFromVertexArray(verticesArr, indicesArrVal);


  auto stMesh =
  ResourceManager::instance().getResourceStaticMesh(
                              actorMesh.lock()->getName() + "_stm");
  if (stMesh.expired()) {
    stMesh =
    ResourceManager::instance().loadStaticMeshFromMeshesArray(
                              {Pair<Mesh, WPtr<Material>>(mesh, mat)},
                              actorMesh.lock()->getName() + "_stm",
                              furtherDist,
                              maxCoord,
                              minCoord);
  }
  else {
    if (firstTime) {
      stMesh.lock()->clear();
    }
    stMesh.lock()->addMesh(mesh, furtherDist, maxCoord, minCoord);
  }

  if (firstTime) {
    stMeshCmp->setStaticMesh(stMesh);

    actorMesh.lock()->addComponent<CBounds>().lock();
    actorMesh.lock()->addComponent<CRender>().lock();
  }
}
void
traversePrimChild(const UsdPrim& childPrim,
                  SPtr<Scene> scenegraph,
                  SPtr<Actor> parentActor)
{
  auto& act = static_cast<UsdGeomXform>(childPrim);



  const auto& children = childPrim.GetAllChildren();
  bool firstTime = true;
  for (const auto& child : children) {
    if (child.IsA<UsdGeomXform>()) {
      auto newAct = scenegraph->addActor(child.GetName()).lock();
      scenegraph->setActorChild(parentActor->getName(), newAct->getName());

      traversePrimChild(child, scenegraph, newAct);
    }
    else if (child.IsA<UsdGeomMesh>()) {
      loadMeshFromStage(static_cast<UsdGeomMesh>(child), parentActor, firstTime);
    }

    firstTime = false;
  }
}
void
OmniverseApi::getScenegraphFromStage(WPtr<Scene> scenegraph)
{
  auto& loggerMan = Logger::instance();
  auto& memoryMan = MemoryManager::instance();

  if (!m_stage) {
    loggerMan.consoleLog("There is no Omniverse Stage opened now.");
    return;
  }

  auto sScene = scenegraph.lock();
  sScene->setName(m_stageFileName);

  auto rootPrim = m_stage->GetPrimAtPath(m_rootPrimPath);
  const auto& children = rootPrim.GetAllChildren();
  for (const auto& child : children) {
    auto parentAct = sScene->addActor(child.GetName()).lock();

    traversePrimChild(child, sScene, parentAct);
  }

  //auto range = m_stage->Traverse();
  //for (const auto& node : range) {
  //  loggerMan.consoleLog(node.GetPath().GetString());
  //
  //  if (node.IsA<UsdGeomMesh>()) {
  //    auto act = sScene->addActor(node.GetName().GetString());
  //    loadMeshFromStage(static_cast<UsdGeomMesh>(node), m_stage, act);
  //  }
  //
  //  const auto& children = node.GetAllChildren();
  //}
}



EE_EXTERN EE_OMNIVERSE_EXPORT void
initPlugin()
{
  OmniverseManager::startUp<OmniverseApi>();
}
}