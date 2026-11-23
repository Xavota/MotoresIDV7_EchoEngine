#include "eeOmniverseApi.h"

#pragma warning(push)
#pragma warning ( disable: 4005 )
#pragma warning ( disable: 4100 )
#pragma warning ( disable: 4127 )
#pragma warning ( disable: 4457 )
#include "xformUtils.h"
#include "primUtils.h"

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <limits.h>
#include <unistd.h>     //readlink
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif


#include "OmniClient.h"
#include "OmniUsdResolver.h"
#include "OmniChannel.h"
#include "LiveSessionInfo.h"
#include "LiveSessionConfigFile.h"
#include "pxr/usd/usd/stage.h"
#include "pxr/usd/usdGeom/mesh.h"
#include "pxr/usd/usdGeom/metrics.h"
#include <pxr/base/gf/matrix4f.h>
#include "pxr/base/gf/vec2f.h"
#include <pxr/base/plug/registry.h>
#include <pxr/usd/usdUtils/pipeline.h>
#include <pxr/usd/usdUtils/sparseValueWriter.h>
#include <pxr/usd/usdShade/material.h>
#include "pxr/usd/usd/prim.h"
#include "pxr/usd/usd/primRange.h"
#include "pxr/usd/usdGeom/primvar.h"
#include <pxr/usd/usdShade/input.h>
#include <pxr/usd/usdShade/output.h>
#include <pxr/usd/usdGeom/xform.h>
#include <pxr/usd/usdGeom/cube.h>
#include <pxr/usd/usdShade/materialBindingAPI.h>
#include <pxr/usd/usdLux/distantLight.h>
#include <pxr/usd/usdLux/domeLight.h>
#include <pxr/usd/usdLux/sphereLight.h>
#include <pxr/usd/usdLux/diskLight.h>
#include <pxr/usd/usdShade/shader.h>
#include <pxr/usd/usd/modelAPI.h>

// Physics includes, note that usdPhysics is now part of USD itself, 
// in newer USD versions these includes will be replaced by pxr official usdPhysics schema
#include <usdPhysics/scene.h>
#include <usdPhysics/rigidBodyAPI.h>
#include <usdPhysics/collisionAPI.h>
#include <usdPhysics/meshCollisionAPI.h>
#pragma warning(pop)

PXR_NAMESPACE_USING_DIRECTIVE


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
#include <eeCLight.h>

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
/**
* Globals for Omniverse Connection and base Stage
*/
UsdStageRefPtr gStage;
/**
* The root path of the stage
*/
SdfPath gRootPrimPath;
/**
* The information for the life session of the Omniverse api
*/
LiveSessionInfo gLiveSessionInfo;

/**
* The folder of the stage file.
*/
String g_stageFileFolder;


OmniverseApi::~OmniverseApi()
{
  destroy();
}
static bool gOmniverseLoggingEnabled = false;
static std::mutex gLogMutex;
// Omniverse Log callback
static void
logCallback(const char* /*threadName*/,
            const char* /*component*/,
            OmniClientLogLevel /*level*/,
            const char* message) noexcept
{
  std::unique_lock<std::mutex> lk(gLogMutex);
  if (gOmniverseLoggingEnabled) {
    puts(message);
  }
}
static void
OmniClientConnectionStatusCallbackImpl(void* /*userData*/,
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
static fs::path
getExePath()
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

String
getConnectedUsername(const String& stageUrl)
{
  // Get the username for the connection
  String userName("_none_");
  omniClientWait(
    omniClientGetServerInfo(stageUrl.c_str(),
      &userName,
      [](void* userData,
        OmniClientResult /*result*/,
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
OmniverseApi::getUserLocalPath(const String& ipAddress)
{
  //String userFolder = "omniverse://localhost/Users";
  //String userFolder = "omniverse://172.29.133.160/Users";
  String userFolder = "omniverse://" + ipAddress + "/Users";
  String username = getConnectedUsername(userFolder);
  return userFolder + "/" + username;
}
String
OmniverseApi::getConnectedUser(const String& ipAddress)
{
  String userFolder = "omniverse://" + ipAddress + "/Users";
  return getConnectedUsername(userFolder);
}

bool
OmniverseApi::init(bool /*doLiveEdit*/)
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
String
OmniverseApi::kritaInit(bool /*doLiveEdit*/)
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
    return "Could not find the Omniverse USD Resolver plugin";
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
    return "Failed to initialize OmniClient";
  }

  omniClientRegisterConnectionStatusCallback(nullptr, OmniClientConnectionStatusCallbackImpl);

  return "";
}
void
OmniverseApi::destroy()
{
  // Calling this prior to shutdown ensures that all pending live updates complete.
  omniClientLiveWaitForPendingUpdates();

  // The stage is a sophisticated object that needs to be destroyed properly.  
  // Since gStage is a smart pointer we can just reset it
  gStage.Reset();

  omniClientShutdown();
}

Vector<String>
OmniverseApi::getExisitingSessionNames()
{
  String sessionFolderForStage = gLiveSessionInfo.GetSessionFolderPathForStage();
  Vector<String> sessionList = gLiveSessionInfo.GetLiveSessionList();
  return sessionList;
}
bool
OmniverseApi::joinSession(const String& sessionName)
{
  auto& loggerMan = Logger::instance();

  if (!gStage) {
    loggerMan.consoleLog("No currently opened stage. Unable to join session");
    return false;
  }

  //gLiveSessionInfo.Initialize(gStagePath.c_str());

  gLiveSessionInfo.SetSessionName(sessionName.c_str());

  // Check that the config file version matches
  LiveSessionConfigFile sessionConfig;
  std::string tomlUrl = gLiveSessionInfo.GetLiveSessionTomlUrl();
  if (!sessionConfig.IsVersionCompatible(tomlUrl.c_str()))
  {
    std::string actualVersion = sessionConfig.GetSessionConfigValue(tomlUrl.c_str(), LiveSessionConfigFile::Key::Version);
    loggerMan.consoleLog("The session config TOML file version is not compatible, exiting.");
    String currentVer = LiveSessionConfigFile::kCurrentVersion;
    loggerMan.consoleLog("Expected: " + currentVer + " Actual: " + actualVersion);
    return false;
  }

  UsdStageRefPtr liveStage;
  std::string liveSessionUrl = gLiveSessionInfo.GetLiveSessionUrl();
  liveStage = UsdStage::Open(liveSessionUrl);


  // Get the live layer from the live stage
  SdfLayerHandle liveLayer = liveStage->GetRootLayer();

  // Construct the layers so that we can join the session
  gStage->GetSessionLayer()->InsertSubLayerPath(liveLayer->GetIdentifier());
  gStage->SetEditTarget(UsdEditTarget(liveLayer));

  m_isLive = true;

  return true;
}
bool
OmniverseApi::createNewSession(const String& sessionName)
{
  auto& loggerMan = Logger::instance();

  if (!gStage) {
    loggerMan.consoleLog("No currently opened stage. Unable to create session");
    return false;
  }

  //gLiveSessionInfo.Initialize(gStagePath.c_str());

  if (!gLiveSessionInfo.SetSessionName(sessionName.c_str()))
  {
    loggerMan.consoleLog("Session names must start with an alphabetical character, but may contain alphanumeric, hyphen, or underscore characters.");
    return false;
  }

  // Make sure that this session doesn't already exist (don't overwrite/stomp it)
  if (gLiveSessionInfo.DoesSessionExist())
  {
    loggerMan.consoleLog("Session config file already exists: " + gLiveSessionInfo.GetLiveSessionTomlUrl());
    return false;
  }

  // Create the session config file 
  LiveSessionConfigFile::KeyMap keyMap;
  std::string stageUrl = gLiveSessionInfo.GetStageUrl();
  std::string connectedUserName = getConnectedUsername(stageUrl);
  keyMap[LiveSessionConfigFile::Key::Admin] = connectedUserName.c_str();
  keyMap[LiveSessionConfigFile::Key::StageUrl] = stageUrl.c_str();
  keyMap[LiveSessionConfigFile::Key::Mode] = "default";
  LiveSessionConfigFile sessionConfig;
  if (!sessionConfig.CreateSessionConfigFile(gLiveSessionInfo.GetLiveSessionTomlUrl().c_str(), keyMap))
  {
    loggerMan.consoleLog("Unable to create session config file: " + gLiveSessionInfo.GetLiveSessionTomlUrl());
    return false;
  }

  // Create the new root.live file to be the stage's edit target
  UsdStageRefPtr liveStage;
  std::string liveSessionUrl = gLiveSessionInfo.GetLiveSessionUrl();
  liveStage = UsdStage::CreateNew(liveSessionUrl);


  // Get the live layer from the live stage
  SdfLayerHandle liveLayer = liveStage->GetRootLayer();

  // Construct the layers so that we can join the session
  gStage->GetSessionLayer()->InsertSubLayerPath(liveLayer->GetIdentifier());
  gStage->SetEditTarget(UsdEditTarget(liveLayer));

  m_isLive = true;

  return true;
}
void
OmniverseApi::stopLiveSession()
{
  gStage->GetSessionLayer()->GetSubLayerPaths().clear();
  gStage->SetEditTarget(UsdEditTarget(gStage->GetRootLayer()));

  m_isLive = false;
}

bool
OmniverseApi::stageIsOpen()
{
  return gStage != nullptr;
}
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
  gStage = UsdStage::CreateNew(stageUrl);
  if (!gStage) {
    failNotify("Failure to create model in Omniverse", stageUrl);
    return;
  }
  m_stagePath = stageUrl;

  {
    std::unique_lock<std::mutex> lk(gLogMutex);
    //std::cout << "New stage created: " << stageUrl << std::endl;
    Logger::instance().consoleLog("New stage created: " + m_stagePath);
  }

  // Always a good idea to declare your up-ness
  UsdGeomSetStageUpAxis(gStage, UsdGeomTokens->y);

  // For physics its important to set units!
  UsdGeomSetStageMetersPerUnit(gStage, 1.0f);


  // Keep the model contained inside of "Root", only need to do this once per model
  gRootPrimPath = SdfPath::AbsoluteRootPath().AppendChild(_tokens->Root);
  UsdGeomXform rootPrim = UsdGeomXform::Define(gStage, gRootPrimPath);

  // Define the defaultPrim as the /Root prim
  gStage->SetDefaultPrim(rootPrim.GetPrim());


  gLiveSessionInfo.Initialize(m_stagePath.c_str());

  //findOrCreateSession(gStage, gLiveSessionInfo);


  getFileName(eeStringtoWString(m_stagePath), m_stageFileName, &g_stageFileFolder);
}
void
OmniverseApi::openStage(const String& stageUrl)
{
  gStage = UsdStage::Open(stageUrl);
  if (!gStage) {
    failNotify("Failure to open stage in Omniverse:", stageUrl);
    return;
  }
  m_stagePath = stageUrl;

  // Define the defaultPrim as the /Root prim
  UsdGeomXform rootPrim = static_cast<UsdGeomXform>(gStage->GetDefaultPrim());
  gRootPrimPath = rootPrim.GetPath();


  gLiveSessionInfo.Initialize(m_stagePath.c_str());

  //findOrCreateSession(gStage, gLiveSessionInfo);


  getFileName(eeStringtoWString(m_stagePath), m_stageFileName, &g_stageFileFolder);
}
void
OmniverseApi::closeStage()
{
  if (gStage) {
    gStage.Reset();
  }
}

String
createMaterial(const String& matName, const String& omniPath, WPtr<Material> mat)
{
  auto& resourceManager = ResourceManager::instance();

  WString mdlPath = L"Cache/" + eeStringtoWString(matName) + L".mdl";

  File mdlFile;
  mdlFile.openFile(mdlPath,
                   OPEN_TYPE::kWriteOnly | OPEN_TYPE::kTruncate);

  auto sMat = mat.lock();
  auto textureMap = sMat->getTexturesMap();

  String diffuseTexFolder;
  String diffuseTexName;
  String diffuseTexExt;
  if (textureMap.find(TEXTURE_TYPE_INDEX::kDiffuse) != textureMap.end()) {
    auto img = textureMap[TEXTURE_TYPE_INDEX::kDiffuse].lock()->getImages()[0];
    getFileName(eeStringtoWString(img->getPath()),
                diffuseTexName,
                &diffuseTexFolder,
                &diffuseTexExt);
  }
  else {
    auto img =
    resourceManager.getResourceTexture("DefaultDiffuse").lock()->getImages()[0];
    getFileName(eeStringtoWString(img->getPath()),
                diffuseTexName,
                &diffuseTexFolder,
                &diffuseTexExt);
  }
  diffuseTexName += diffuseTexExt;

  String normalTexFolder;
  String normalTexName;
  String normalTexExt;
  if (textureMap.find(TEXTURE_TYPE_INDEX::kNormal) != textureMap.end()) {
    auto img = textureMap[TEXTURE_TYPE_INDEX::kNormal].lock()->getImages()[0];
    getFileName(eeStringtoWString(img->getPath()),
                normalTexName,
                &normalTexFolder,
                &normalTexExt);
  }
  else {
    auto img =
    resourceManager.getResourceTexture("DefaultNormalMap").lock()->getImages()[0];
    getFileName(eeStringtoWString(img->getPath()),
                normalTexName,
                &normalTexFolder,
                &normalTexExt);
  }
  normalTexName += normalTexExt;

  String mdlContent = "mdl 1.4;\n"
  "\n"
  "import ::OmniPBR::OmniPBR;\n"
  "import ::anno::author;\n"
  "import ::anno::description;\n"
  "import ::anno::display_name;\n"
  "import ::anno::key_words;\n"
  "import ::anno::version;\n"
  "import ::tex::gamma_mode;\n"
  "import ::state::normal;\n"
  "\n"
  "export material " + matName + "(*)\n"
  "[[\n"
  "    ::anno::display_name(\"Test Material \"),\n"
  "    ::anno::description(\"Material used for Videogame Tools school grade.\"),\n"
  "    ::anno::version(1, 0, 0, \"\"),\n"
  "    ::anno::author(\"Diego Mara C.\"),\n"
  "    ::anno::key_words(string[](\"Echo\", \"Test\", \"omniverse\", \"generic\"))\n"
  "]]\n"
  " = ::OmniPBR::OmniPBR(\n"
  "    diffuse_color_constant: color(0.200000003f, 0.200000003f, 0.200000003f),\n"
  "    diffuse_texture: texture_2d(\"./Textures/" + diffuseTexName + "\", ::tex::gamma_srgb),\n"
  "    albedo_desaturation: 0.f,\n"
  "    albedo_add: 0.f,\n"
  "    albedo_brightness: 1.f,\n"
  "    diffuse_tint: color(1.f, 1.f, 1.f),\n"
  "    reflection_roughness_constant: 0.5f,\n"
  "    reflection_roughness_texture_influence: 1.f,\n"
  "    reflectionroughness_texture: texture_2d(),\n"
  "    metallic_constant: 0.f,\n"
  "    metallic_texture_influence: 1.f,\n"
  "    metallic_texture: texture_2d(),\n"
  "    specular_level: 0.5f,\n"
  "    enable_ORM_texture: true,\n"
  "    ORM_texture: texture_2d(),\n"
  "    ao_to_diffuse: 0.f,\n"
  "    ao_texture: texture_2d(),\n"
  "    enable_emission: false,\n"
  "    emissive_color: color(1.f, 0.100000001f, 0.100000001f),\n"
  "    emissive_mask_texture: texture_2d(),\n"
  "    emissive_intensity: 40.f,\n"
  "    bump_factor: 1.f,\n"
  "    normalmap_texture: texture_2d(\"./Textures/" + normalTexName + "\", ::tex::gamma_linear),\n"
  "    detail_bump_factor: 0.300000012f,\n"
  "    detail_normalmap_texture: texture_2d(),\n"
  "    project_uvw: false,\n"
  "    world_or_object: false,\n"
  "    uv_space_index: 0,\n"
  "    texture_translate: float2(0.f),\n"
  "    texture_rotate: 0.f,\n"
  "    texture_scale: float2(1.f),\n"
  "    detail_texture_translate: float2(0.f),\n"
  "    detail_texture_rotate: 0.f,\n"
  "    detail_texture_scale: float2(1.f));\n";

  mdlFile.write(mdlContent);

  mdlFile.close();

  auto& omniMan = OmniverseManager::instance();

  String omniMdlPath = omniPath
                     //+ formatNumberPrefix(sMat->m_omniIndexFile, 5)
                     + matName
                     + ".mdl";
  //// Delete the old version of this folder on Omniverse and wait for the operation to complete
  //{
  //  std::unique_lock<std::mutex> lk(gLogMutex);
  //  std::cout << "Waiting for " << omniMdlPath << " to delete... ";
  //}
  //omniClientWait(omniClientDelete(omniMdlPath.c_str(), nullptr, nullptr));
  //{
  //  std::unique_lock<std::mutex> lk(gLogMutex);
  //  std::cout << "finished" << std::endl;
  //}
  //
  ////omniMdlPath = omniPath
  ////            + formatNumberPrefix(++sMat->m_omniIndexFile, 5)
  ////            + matName
  ////            + ".mdl";
  //// Upload the material folder (MDL and textures)
  //{
  //  std::unique_lock<std::mutex> lk(gLogMutex);
  //  std::cout << "Waiting for the resources/Materials folder to upload to " << omniMdlPath << " ... ";
  //}
  //omniClientWait(omniClientCopy(eeWStringtoString(mdlPath).c_str(),
  //                              omniMdlPath.c_str(),
  //                              nullptr,
  //                              nullptr));
  //{
  //  std::unique_lock<std::mutex> lk(gLogMutex);
  //  std::cout << "finished" << std::endl;
  //}
  omniMan.copyFileToDest(eeWStringtoString(mdlPath), omniMdlPath);

  String omniTexPath = omniPath + "Textures/" + diffuseTexName;
  diffuseTexName = diffuseTexFolder + diffuseTexName;
  //// Delete the old version of this folder on Omniverse and wait for the operation to complete
  //{
  //  std::unique_lock<std::mutex> lk(gLogMutex);
  //  std::cout << "Waiting for " << omniTexPath << " to delete... ";
  //}
  //omniClientWait(omniClientDelete(omniTexPath.c_str(), nullptr, nullptr));
  //{
  //  std::unique_lock<std::mutex> lk(gLogMutex);
  //  std::cout << "finished" << std::endl;
  //}
  //
  //// Upload the material folder (MDL and textures)
  //{
  //  std::unique_lock<std::mutex> lk(gLogMutex);
  //  std::cout << "Waiting for the resources/Materials folder to upload to " << omniTexPath << " ... ";
  //}
  //omniClientWait(omniClientCopy(diffuseTexName.c_str(), omniTexPath.c_str(), nullptr, nullptr));
  //{
  //  std::unique_lock<std::mutex> lk(gLogMutex);
  //  std::cout << "finished" << std::endl;
  //}
  omniMan.copyFileToDest(diffuseTexName, omniTexPath);

  omniTexPath = omniPath + "Textures/" + normalTexName;
  normalTexName = normalTexFolder + normalTexName;
  //// Delete the old version of this folder on Omniverse and wait for the operation to complete
  //{
  //  std::unique_lock<std::mutex> lk(gLogMutex);
  //  std::cout << "Waiting for " << omniTexPath << " to delete... ";
  //}
  //omniClientWait(omniClientDelete(omniTexPath.c_str(), nullptr, nullptr));
  //{
  //  std::unique_lock<std::mutex> lk(gLogMutex);
  //  std::cout << "finished" << std::endl;
  //}
  //
  //// Upload the material folder (MDL and textures)
  //{
  //  std::unique_lock<std::mutex> lk(gLogMutex);
  //  std::cout << "Waiting for the resources/Materials folder to upload to " << omniTexPath << " ... ";
  //}
  //omniClientWait(omniClientCopy(normalTexName.c_str(), omniTexPath.c_str(), nullptr, nullptr));
  //{
  //  std::unique_lock<std::mutex> lk(gLogMutex);
  //  std::cout << "finished" << std::endl;
  //}
  omniMan.copyFileToDest(normalTexName, omniTexPath);

  return matName + ".mdl";
}
void
updateStMeshCmpToScenegraph(const SdfPath& parentPath,
                            UsdStageRefPtr stage,
                            WPtr<CStaticMesh> stMeshCmp,
                            WPtr<Actor> sceneActor)
{
  if (sceneActor.expired()) return;
  //auto sActor = sceneActor.lock();
  
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
    String meshName("ChActM_" + eeToString(meshIndex));
    SdfPath meshPrimPath = parentPath.AppendChild(TfToken(meshName));//_tokens->box);
    UsdGeomMesh mesh = UsdGeomMesh::Get(stage, meshPrimPath);
  
    if (!mesh) {
      ++meshIndex;
      continue;
    }
  
  //  // Set orientation
  //  mesh.CreateOrientationAttr(VtValue(UsdGeomTokens->leftHanded));
  //
  //  // Add all of the vertices
  //  int num_vertices = stm.first.getTrianglesCount();
  //  auto& vertices = stm.first.getTrianglesArray();
  //  VtArray<GfVec3f> points;
  //  points.resize(num_vertices * 3);
  //  for (int i = 0; i < num_vertices; i++) {
  //    points[i * 3 + 0] = GfVec3f(-vertices[i].x.position.x, vertices[i].x.position.y, vertices[i].x.position.z) * 100.0f;
  //    points[i * 3 + 1] = GfVec3f(-vertices[i].y.position.x, vertices[i].y.position.y, vertices[i].y.position.z) * 100.0f;
  //    points[i * 3 + 2] = GfVec3f(-vertices[i].z.position.x, vertices[i].z.position.y, vertices[i].z.position.z) * 100.0f;
  //  }
  //  mesh.CreatePointsAttr(VtValue(points));
  //  
  //  // Calculate indices for each triangle
  //  int num_indices = stm.first.getIndexCount();
  //  auto& indicesArr = stm.first.getIndicesArray();
  //  VtArray<int> vecIndices;
  //  vecIndices.resize(num_indices);
  //  for (int i = 0; i < num_indices; i++) {
  //    vecIndices[i] = indicesArr[i];
  //  }
  //  mesh.CreateFaceVertexIndicesAttr(VtValue(vecIndices));
  //  
  //  // Add vertex normals
  //  int num_normals = stm.first.getTrianglesCount();
  //  VtArray<GfVec3f> meshNormals;
  //  meshNormals.resize(num_normals * 3);
  //  for (int i = 0; i < num_normals; i++) {
  //    meshNormals[i * 3 + 0] = GfVec3f(-vertices[i].x.normal.x, vertices[i].x.normal.y, vertices[i].x.normal.z);
  //    meshNormals[i * 3 + 1] = GfVec3f(-vertices[i].y.normal.x, vertices[i].y.normal.y, vertices[i].y.normal.z);
  //    meshNormals[i * 3 + 2] = GfVec3f(-vertices[i].z.normal.x, vertices[i].z.normal.y, vertices[i].z.normal.z);
  //  }
  //  mesh.CreateNormalsAttr(VtValue(meshNormals));
  //  
  //  // Add face vertex count
  //  VtArray<int> faceVertexCounts;
  //  faceVertexCounts.resize(stm.first.getTrianglesCount());
  //  std::fill(faceVertexCounts.begin(), faceVertexCounts.end(), 3);
  //  mesh.CreateFaceVertexCountsAttr(VtValue(faceVertexCounts));
  //  
  //  // Set the color on the mesh
  //  UsdPrim meshPrim = mesh.GetPrim();
  //  UsdAttribute displayColorAttr = mesh.CreateDisplayColorAttr();
  //  {
  //    VtVec3fArray valueArray;
  //    GfVec3f rgbFace(0.463f, 0.725f, 0.0f);
  //    valueArray.push_back(rgbFace);
  //    displayColorAttr.Set(valueArray);
  //  }
  //  
  //  // Set the UV (st) values for this mesh
  //  UsdGeomPrimvar attr2 = mesh.CreatePrimvar(_tokens->st, SdfValueTypeNames->TexCoord2fArray);
  //  {
  //    int uv_count = stm.first.getTrianglesCount();
  //    VtVec2fArray valueArray;
  //    valueArray.resize(uv_count * 3);
  //    for (int i = 0; i < uv_count; ++i)
  //    {
  //      valueArray[i * 3 + 0].Set(vertices[i].x.uvCoord.x, 1.0f - vertices[i].x.uvCoord.y);
  //      valueArray[i * 3 + 1].Set(vertices[i].y.uvCoord.x, 1.0f - vertices[i].y.uvCoord.y);
  //      valueArray[i * 3 + 2].Set(vertices[i].z.uvCoord.x, 1.0f - vertices[i].z.uvCoord.y);
  //    }
  //  
  //    bool status = attr2.Set(valueArray);
  //  }
  //  attr2.SetInterpolation(UsdGeomTokens->vertex);



    //String matName("Mat_" + stm.second.lock()->getResourceName());
    //SdfPath matPath = meshPrimPath.AppendChild(TfToken("Mat_Pat"));
    //auto mat = UsdShadeMaterial::Get(stage, matPath);
    //
    //auto pbrShader = UsdShadeShader::Get(stage, matPath.AppendChild(TfToken("PBRShader")));
    //pbrShader.GetInput(TfToken("roughness")).Set(0.4f);
    //pbrShader.GetInput(TfToken("metallic")).Set(0.0f);
    //
    //auto tex = stm.second.lock()->getTexturesMap();
    //auto img = tex[0].lock()->getImages()[0];
    //
    //String imgPath = "D:/GitHub/MotoresIDV7_EchoEngine/EchoEngine/bin/" + img->getPath();
    //
    //auto diffuseTextureSampler = UsdShadeShader::Get(stage, matPath.AppendChild(TfToken("diffuseTexture")));
    //diffuseTextureSampler.GetInput(TfToken("file")).Set(SdfAssetPath(imgPath));

    
    if (!stm.second.expired()) {
      if (stMesh->m_dirtyMatFlags[meshIndex].first) {
        String matName = stMesh->m_dirtyMatFlags[meshIndex].second;

        TfToken materialNameToken = TfToken(matName);
        SdfPath matPath = SdfPath::AbsoluteRootPath()
                            .AppendChild(_tokens->Root)
                            .AppendChild(_tokens->Looks)
                            .AppendChild(materialNameToken);

        if (!stm.second.expired()) {
          stMesh->m_dirtyMatFlags[meshIndex].second = stm.second.lock()->getResourceName();
        }
        else {
          stMesh->m_dirtyMatFlags[meshIndex].second = "Default_mat";
        }
      }
      else if (stm.second.lock()->m_dirtyMat) {
        String matName = stm.second.lock()->getResourceName();

        TfToken materialNameToken = TfToken(matName);
        SdfPath matPath = SdfPath::AbsoluteRootPath()
                            .AppendChild(_tokens->Root)
                            .AppendChild(_tokens->Looks)
                            .AppendChild(materialNameToken);

        stage->RemovePrim(matPath);
      }
      else {
        ++meshIndex;
        continue;
      }

      stm.second.lock()->m_dirtyMat = false;
      stMesh->m_dirtyMatFlags[meshIndex].first = false;

      String matName = stm.second.lock()->getResourceName();
      String mdlPath = "./" + createMaterial(matName, g_stageFileFolder, stm.second);


      TfToken materialNameToken = TfToken(matName);
      SdfPath matPath = SdfPath::AbsoluteRootPath()
                          .AppendChild(_tokens->Root)
                          .AppendChild(_tokens->Looks)
                          .AppendChild(materialNameToken);

      UsdShadeMaterial newMat = UsdShadeMaterial::Define(stage, matPath);


      UsdShadeMaterialBindingAPI usdMaterialBinding(mesh);
      usdMaterialBinding.Bind(newMat);
      
      // MDL Shader
      {
        // Create the MDL shader to bind to the material
        SdfAssetPath mdlShaderModule = SdfAssetPath(mdlPath);
        SdfPath shaderPath = matPath.AppendChild(materialNameToken);
        UsdShadeShader mdlShader = UsdShadeShader::Define(stage, shaderPath);
        mdlShader.CreateIdAttr(VtValue(_tokens->shaderId));
      
        // These attributes will be reworked or replaced in the official MDL schema for USD.
        // https://developer.nvidia.com/usd/MDLschema
        mdlShader.SetSourceAsset(mdlShaderModule, _tokens->mdl);
        mdlShader.GetPrim().CreateAttribute(TfToken("info:mdl:sourceAsset:subIdentifier"), SdfValueTypeNames->Token, false, SdfVariabilityUniform).Set(materialNameToken);
      
        // Set the linkage between material and MDL shader
        UsdShadeOutput mdlOutput = newMat.CreateSurfaceOutput(_tokens->mdl);
        mdlOutput.ConnectToSource(mdlShader, _tokens->out);
      }
      
      //UsdShadeMaterialBindingAPI usdMaterialBinding(mesh);
      //usdMaterialBinding.Bind(newMat);
    }

    ++meshIndex;
  }
}
void
updateSkMeshCmpToScenegraph(const SdfPath& parentPath,
                            UsdStageRefPtr stage,
                            WPtr<CSkeletalMesh> skMeshCmp,
                            WPtr<Actor> sceneActor)
{
  if (sceneActor.expired()) return;
  //auto sActor = sceneActor.lock();

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
    String meshName("ChActM_" + eeToString(meshIndex));
    SdfPath meshPrimPath = parentPath.AppendChild(TfToken(meshName));//_tokens->box);
    UsdGeomMesh mesh = UsdGeomMesh::Get(stage, meshPrimPath);

    if (!mesh) {
      ++meshIndex;
      continue;
    }

    //// Add all of the vertices
    //int num_vertices = stm.first.getVertexCount();
    //auto& vertices = stm.first.getVertexArray();
    //VtArray<GfVec3f> points;
    //points.resize(num_vertices);
    //for (int i = 0; i < num_vertices; i++) {
    //  points[i] = GfVec3f(-vertices[i].position.x, vertices[i].position.y, vertices[i].position.z) * 100.0f;
    //}
    //mesh.CreatePointsAttr(VtValue(points));
    //
    //// Calculate indices for each triangle
    //int num_indices = stm.first.getIndexCount();
    //auto& indicesArr = stm.first.getIndexArray();
    //VtArray<int> vecIndices;
    //vecIndices.resize(num_indices);
    //for (int i = 0; i < num_indices; i++) {
    //  vecIndices[i] = indicesArr[i];
    //}
    //mesh.CreateFaceVertexIndicesAttr(VtValue(vecIndices));
    //
    //// Add vertex normals
    //int num_normals = stm.first.getVertexCount();
    //VtArray<GfVec3f> meshNormals;
    //meshNormals.resize(num_normals);
    //for (int i = 0; i < num_normals; i++) {
    //  meshNormals[i] = GfVec3f(-vertices[i].normal.x, vertices[i].normal.y, vertices[i].normal.z);
    //}
    //mesh.CreateNormalsAttr(VtValue(meshNormals));
    //
    //// Add face vertex count
    //VtArray<int> faceVertexCounts;
    //faceVertexCounts.resize(num_indices / 3);
    //std::fill(faceVertexCounts.begin(), faceVertexCounts.end(), 3);
    //mesh.CreateFaceVertexCountsAttr(VtValue(faceVertexCounts));
    //
    //// Set the color on the mesh
    //UsdPrim meshPrim = mesh.GetPrim();
    //UsdAttribute displayColorAttr = mesh.GetDisplayColorAttr();
    //{
    //  VtVec3fArray valueArray;
    //  GfVec3f rgbFace(0.463f, 0.725f, 0.0f);
    //  valueArray.push_back(rgbFace);
    //  displayColorAttr.Set(valueArray);
    //}
    //
    //// Set the UV (st) values for this mesh
    //UsdGeomPrimvar attr2 = mesh.GetPrimvar(_tokens->st);
    //{
    //  int uv_count = stm.first.getVertexCount();
    //  VtVec2fArray valueArray;
    //  valueArray.resize(uv_count);
    //  for (int i = 0; i < uv_count; ++i)
    //  {
    //    valueArray[i].Set(vertices[i].uvCoord.x, 1.0f - vertices[i].uvCoord.y);
    //  }
    //
    //  bool status = attr2.Set(valueArray);
    //}
    //attr2.SetInterpolation(UsdGeomTokens->vertex);


    //String matName("Mat_" + stm.second.lock()->getResourceName());
    //SdfPath matPath = meshPrimPath.AppendChild(TfToken("Mat_Pat"));
    //auto mat = UsdShadeMaterial::Get(stage, matPath);
    //
    //auto pbrShader = UsdShadeShader::Get(stage, matPath.AppendChild(TfToken("PBRShader")));
    //pbrShader.GetInput(TfToken("roughness")).Set(0.4f);
    //pbrShader.GetInput(TfToken("metallic")).Set(0.0f);
    //
    //auto tex = stm.second.lock()->getTexturesMap();
    //auto img = tex[0].lock()->getImages()[0];
    //
    //String imgPath = "D:/GitHub/MotoresIDV7_EchoEngine/EchoEngine/bin/" + img->getPath();
    //
    //auto diffuseTextureSampler = UsdShadeShader::Get(stage, matPath.AppendChild(TfToken("diffuseTexture")));
    //diffuseTextureSampler.GetInput(TfToken("file")).Set(SdfAssetPath(imgPath));

    
    if (!stm.second.expired()) {
      if (skMesh->m_dirtyMatFlags[meshIndex].first) {
        String matName = skMesh->m_dirtyMatFlags[meshIndex].second;

        TfToken materialNameToken = TfToken(matName);
        SdfPath matPath = SdfPath::AbsoluteRootPath()
                            .AppendChild(_tokens->Root)
                            .AppendChild(_tokens->Looks)
                            .AppendChild(materialNameToken);

        if (!stm.second.expired()) {
          skMesh->m_dirtyMatFlags[meshIndex].second = stm.second.lock()->getResourceName();
        }
        else {
          skMesh->m_dirtyMatFlags[meshIndex].second = "Default_mat";
        }
      }
      else if (stm.second.lock()->m_dirtyMat) {
        String matName = stm.second.lock()->getResourceName();

        TfToken materialNameToken = TfToken(matName);
        SdfPath matPath = SdfPath::AbsoluteRootPath()
                            .AppendChild(_tokens->Root)
                            .AppendChild(_tokens->Looks)
                            .AppendChild(materialNameToken);

        stage->RemovePrim(matPath);
      }
      else {
        ++meshIndex;
        continue;
      }

      stm.second.lock()->m_dirtyMat = false;
      skMesh->m_dirtyMatFlags[meshIndex].first = false;

      String matName = stm.second.lock()->getResourceName();
      String mdlPath = "./" + createMaterial(matName, g_stageFileFolder, stm.second);


      TfToken materialNameToken = TfToken(matName);
      SdfPath matPath = SdfPath::AbsoluteRootPath()
                          .AppendChild(_tokens->Root)
                          .AppendChild(_tokens->Looks)
                          .AppendChild(materialNameToken);

      UsdShadeMaterial newMat = UsdShadeMaterial::Define(stage, matPath);


      UsdShadeMaterialBindingAPI usdMaterialBinding(mesh);
      usdMaterialBinding.Bind(newMat);
      
      // MDL Shader
      {
        // Create the MDL shader to bind to the material
        SdfAssetPath mdlShaderModule = SdfAssetPath(mdlPath);
        SdfPath shaderPath = matPath.AppendChild(materialNameToken);
        UsdShadeShader mdlShader = UsdShadeShader::Define(stage, shaderPath);
        mdlShader.CreateIdAttr(VtValue(_tokens->shaderId));
      
        // These attributes will be reworked or replaced in the official MDL schema for USD.
        // https://developer.nvidia.com/usd/MDLschema
        mdlShader.SetSourceAsset(mdlShaderModule, _tokens->mdl);
        mdlShader.GetPrim().CreateAttribute(TfToken("info:mdl:sourceAsset:subIdentifier"), SdfValueTypeNames->Token, false, SdfVariabilityUniform).Set(materialNameToken);
      
        // Set the linkage between material and MDL shader
        UsdShadeOutput mdlOutput = newMat.CreateSurfaceOutput(_tokens->mdl);
        mdlOutput.ConnectToSource(mdlShader, _tokens->out);
      }
      
      //UsdShadeMaterialBindingAPI usdMaterialBinding(mesh);
      //usdMaterialBinding.Bind(newMat);
    }
    ++meshIndex;
  }
}
void
updateDirectionalLightToScenegraph(const SdfPath& parentPath,
                                   UsdStageRefPtr stage,
                                   WPtr<CLight> lightCmp,
                                   WPtr<Actor> sceneActor,
                                   uint32 lightIndex)
{
  // Construct /Root/Light path
  SdfPath lightPath = parentPath.AppendChild(TfToken("DirLight" + eeToString(lightIndex)));
  UsdLuxDistantLight newLight = UsdLuxDistantLight::Get(stage, lightPath);

  // Set the attributes
  auto sLight = lightCmp.lock();
  Color lightColor = sLight->getColor();
  float lightIntensity = sLight->getIntensity() * 1000.0f;

  GfVec3f color(lightColor.r, lightColor.g, lightColor.b);
  if (newLight.GetColorAttr().IsValid()) {
    newLight.GetColorAttr().Set(VtValue(color));
  }
  if (newLight.GetIntensityAttr().IsValid()) {
    newLight.GetIntensityAttr().Set(VtValue(lightIntensity));
  }

  // Commit the changes to the USD
  stage->Save();
  omniClientLiveProcess();
}
void
updatePointLightToScenegraph(const SdfPath& parentPath,
                            UsdStageRefPtr stage,
                            WPtr<CLight> lightCmp,
                            WPtr<Actor> sceneActor,
                            uint32 lightIndex)
{
  // Construct /Root/Light path
  SdfPath lightPath = parentPath.AppendChild(TfToken("PointLight" + eeToString(lightIndex)));
  UsdLuxSphereLight newLight = UsdLuxSphereLight::Get(stage, lightPath);

  // Set the attributes
  auto sLight = lightCmp.lock();
  sLight->getDirection();
  Color lightColor = sLight->getColor();
  float lightIntensity = sLight->getIntensity();

  GfVec3f color(lightColor.r, lightColor.g, lightColor.b);
  if (newLight.GetColorAttr().IsValid()) {
    newLight.GetColorAttr().Set(VtValue(color));
  }
  if (newLight.GetIntensityAttr().IsValid()) {
    newLight.GetIntensityAttr().Set(VtValue(lightIntensity * 1000.0f));
  }
  if (newLight.GetRadiusAttr().IsValid()) {
    newLight.GetRadiusAttr().Set(VtValue(lightIntensity * 100.0f));
  }

  // Commit the changes to the USD
  stage->Save();
  omniClientLiveProcess();
}
void
updateSpotLightToScenegraph(const SdfPath& parentPath,
                            UsdStageRefPtr stage,
                            WPtr<CLight> lightCmp,
                            WPtr<Actor> sceneActor,
                            uint32 lightIndex)
{
  // Construct /Root/Light path
  SdfPath lightPath = parentPath.AppendChild(TfToken("SpotLight" + eeToString(lightIndex)));
  UsdLuxDiskLight newLight = UsdLuxDiskLight::Get(stage, lightPath);

  // Set the attributes
  auto sLight = lightCmp.lock();
  sLight->getDirection();
  Color lightColor = sLight->getColor();
  float lightIntensity = sLight->getIntensity();
  float lightInnerAngle = sLight->getInnerAngle();

  GfVec3f color(lightColor.r, lightColor.g, lightColor.b);
  if (newLight.GetColorAttr().IsValid()) {
    newLight.GetColorAttr().Set(VtValue(color));
  }
  if (newLight.GetIntensityAttr().IsValid()) {
    newLight.GetIntensityAttr().Set(VtValue(lightIntensity * 1000.0f));
  }
  if (newLight.GetRadiusAttr().IsValid()) {
    float distanceRad = 1.5f * 100.f;
    newLight.GetRadiusAttr().Set(VtValue(Math::tan(lightInnerAngle) * distanceRad));
  }

  // Commit the changes to the USD
  stage->Save();
  omniClientLiveProcess();
}
void
updateLightCmpToScenegraph(const SdfPath& parentPath,
                           UsdStageRefPtr stage,
                           WPtr<CLight> lightCmp,
                           WPtr<Actor> sceneActor)
{
  switch (lightCmp.lock()->getLightType())
  {
  case eLIGHT_TYPE::kDirectional:
    updateDirectionalLightToScenegraph(parentPath, stage, lightCmp, sceneActor, 0);
  break;
  case eLIGHT_TYPE::kPoint:
    updatePointLightToScenegraph(parentPath, stage, lightCmp, sceneActor, 0);
  break;
  case eLIGHT_TYPE::kSpot:
    updateSpotLightToScenegraph(parentPath, stage, lightCmp, sceneActor, 0);
  break;
  }
}
void
updateActorToScenegraph(const SdfPath& parentPath,
                        UsdStageRefPtr stage,
                        WPtr<Actor> sceneActor)
{
  if (sceneActor.expired()) return;

  auto& memoryMan = MemoryManager::instance();

  auto sActor = sceneActor.lock();

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
      }

      if (op.GetPrecision() == UsdGeomXformOp::Precision::PrecisionFloat)
        op.Set(GfVec3f(value));
      else
        op.Set(value);

      std::unique_lock<std::mutex> lk(gLogMutex);
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


  const auto& actorComponents = sActor->getAllComponents();
  //
  for (const auto& cmp : actorComponents) {
    switch (cmp->getType()) {
    case eCOMPONENT_TYPE::kStaticMesh:
      updateStMeshCmpToScenegraph(parentPath,
                                  stage,
                                  memoryMan.reinterpretPtr<CStaticMesh>(cmp),
                                  sceneActor);
      break;
    case eCOMPONENT_TYPE::kSkeletalMesh:
      updateSkMeshCmpToScenegraph(parentPath,
                                  stage,
                                  memoryMan.reinterpretPtr<CSkeletalMesh>(cmp),
                                  sceneActor);
      break;
    case eCOMPONENT_TYPE::kLight:
      updateLightCmpToScenegraph(parentPath,
                                 stage,
                                 memoryMan.reinterpretPtr<CLight>(cmp),
                                 sceneActor);
    break;
    }
  }
}
void
updateActorOnStageHelper(const SdfPath& parentPath,
                         UsdStageRefPtr stage,
                         SPtr<ActorNode> actNode)
{
  auto sActor = actNode->actorValue.lock();
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
OmniverseApi::saveStage(WPtr<Scene> scenegraph)
{
  if (scenegraph.expired()) {
    Logger::instance().consoleLog("No scenegraph passed.");
    return;
  }

  updateScenegraphOnStage(scenegraph, gRootPrimPath, gStage);

  if (m_isLive) omniClientLiveProcess();
  else gStage->Save();
}

void
addStMeshCmpToScenegraph(const SdfPath& parentPath,
                         UsdStageRefPtr stage,
                         WPtr<CStaticMesh> stMeshCmp)
{
  if (stMeshCmp.expired()) return;
  auto sStMeshCmp = stMeshCmp.lock();

  auto stMesh = sStMeshCmp->getStaticMesh().lock();
  if (!stMesh) return;
  auto meshes = stMesh->getMeshes();
  if (meshes.empty()) return;
  
  int32 meshIndex = 0;
  for (auto& stm : meshes) {
    // Create the geometry inside of "Root"
    String meshName("ChActM_" + eeToString(meshIndex));
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
    
      attr2.Set(valueArray);
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



    //String matName("Mat_" + stm.second.lock()->getResourceName());
    //SdfPath matPath = meshPrimPath.AppendChild(TfToken("Mat_Pat"));
    //auto mat = UsdShadeMaterial::Define(stage, matPath);
    //
    //auto pbrShader = UsdShadeShader::Define(stage, matPath.AppendChild(TfToken("PBRShader")));
    //pbrShader.CreateIdAttr(VtValue(TfToken("UsdPreviewSurface")));
    //pbrShader.CreateInput(TfToken("roughness"), SdfValueTypeNames->Float).Set(0.4f);
    //pbrShader.CreateInput(TfToken("metallic"), SdfValueTypeNames->Float).Set(0.0f);
    //
    //mat.CreateSurfaceOutput().ConnectToSource(pbrShader.ConnectableAPI(), TfToken("surface"));
    //
    //auto stReader = UsdShadeShader::Define(stage, matPath.AppendChild(TfToken("stReader")));
    //stReader.CreateIdAttr(VtValue(TfToken("UsdPrimvarReader_float2")));
    //
    //auto tex = stm.second.lock()->getTexturesMap();
    //auto img = tex[0].lock()->getImages()[0];
    //
    //String imgPath = "D:/GitHub/MotoresIDV7_EchoEngine/EchoEngine/bin/" + img->getPath();
    //
    //auto diffuseTextureSampler = UsdShadeShader::Define(stage, matPath.AppendChild(TfToken("diffuseTexture")));
    //diffuseTextureSampler.CreateIdAttr(VtValue(TfToken("UsdUVTexture")));
    //diffuseTextureSampler.CreateInput(TfToken("file"), SdfValueTypeNames->Asset).Set(SdfAssetPath(imgPath));
    ////diffuseTextureSampler.CreateInput(TfToken("rgba"), SdfValueTypeNames->Color4fArray).Set(VtVec4fArray());
    //diffuseTextureSampler.CreateInput(TfToken("st"), SdfValueTypeNames->Float2).ConnectToSource(stReader.ConnectableAPI(), TfToken("result"));
    //diffuseTextureSampler.CreateOutput(TfToken("rgb"), SdfValueTypeNames->Float3);
    //pbrShader.CreateInput(TfToken("diffuseColor"), SdfValueTypeNames->Color3f).ConnectToSource(diffuseTextureSampler.ConnectableAPI(), TfToken("rgb"));
    //
    //auto stInput = mat.CreateInput(TfToken("frame:stPrimvarName"), SdfValueTypeNames->Token);
    //stInput.Set(TfToken("st"));
    //
    //stReader.CreateInput(TfToken("varname"), SdfValueTypeNames->Token).ConnectToSource(stInput);
    //UsdShadeMaterialBindingAPI(mesh).Bind(mat);


    
    String matName = stm.second.lock()->getResourceName();
    String mdlPath = "./" + createMaterial(matName, g_stageFileFolder, stm.second);

    TfToken materialNameToken = TfToken(matName);
    SdfPath matPath = SdfPath::AbsoluteRootPath()
                        .AppendChild(_tokens->Root)
                        .AppendChild(_tokens->Looks)
                        .AppendChild(materialNameToken);
    UsdShadeMaterial newMat = UsdShadeMaterial::Define(stage, matPath);

    // MDL Shader
    {
      // Create the MDL shader to bind to the material
      SdfAssetPath mdlShaderModule = SdfAssetPath(mdlPath);
      SdfPath shaderPath = matPath.AppendChild(materialNameToken);
      UsdShadeShader mdlShader = UsdShadeShader::Define(stage, shaderPath);
      mdlShader.CreateIdAttr(VtValue(_tokens->shaderId));

      // These attributes will be reworked or replaced in the official MDL schema for USD.
      // https://developer.nvidia.com/usd/MDLschema
      mdlShader.SetSourceAsset(mdlShaderModule, _tokens->mdl);
      mdlShader.GetPrim().CreateAttribute(TfToken("info:mdl:sourceAsset:subIdentifier"), SdfValueTypeNames->Token, false, SdfVariabilityUniform).Set(materialNameToken);

      // Set the linkage between material and MDL shader
      UsdShadeOutput mdlOutput = newMat.CreateSurfaceOutput(_tokens->mdl);
      mdlOutput.ConnectToSource(mdlShader, _tokens->out);
    }

    UsdShadeMaterialBindingAPI usdMaterialBinding(mesh);
    usdMaterialBinding.Bind(newMat);


    stm.second.lock()->m_dirtyMat = false;
    stMesh->m_dirtyMatFlags[meshIndex].first = false;
    ++meshIndex;
  }
}
void
addSkMeshCmpToScenegraph(const SdfPath& parentPath,
                         UsdStageRefPtr stage,
                         WPtr<CSkeletalMesh> skMeshCmp)
{
  if (skMeshCmp.expired()) return;
  auto sSkMeshCmp = skMeshCmp.lock();

  auto skMesh = sSkMeshCmp->getModel().lock();
  if (!skMesh) return;
  auto meshes = skMesh->getMeshes();
  if (meshes.empty()) return;
  
  int32 meshIndex = 0;
  for (auto& stm : meshes) {
    // Create the geometry inside of "Root"
    String meshName("ChActM_" + eeToString(meshIndex));
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
    
      attr2.Set(valueArray);
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


    //String matName("Mat_" + stm.second.lock()->getResourceName());
    //SdfPath matPath = meshPrimPath.AppendChild(TfToken("Mat_Pat"));
    //auto mat = UsdShadeMaterial::Define(stage, matPath);
    //
    //auto pbrShader = UsdShadeShader::Define(stage, matPath.AppendChild(TfToken("PBRShader")));
    //pbrShader.CreateIdAttr(VtValue(TfToken("UsdPreviewSurface")));
    //pbrShader.CreateInput(TfToken("roughness"), SdfValueTypeNames->Float).Set(0.4f);
    //pbrShader.CreateInput(TfToken("metallic"), SdfValueTypeNames->Float).Set(0.0f);
    //
    //mat.CreateSurfaceOutput().ConnectToSource(pbrShader.ConnectableAPI(), TfToken("surface"));
    //
    //auto stReader = UsdShadeShader::Define(stage, matPath.AppendChild(TfToken("stReader")));
    //stReader.CreateIdAttr(VtValue(TfToken("UsdPrimvarReader_float2")));
    //
    //auto tex = stm.second.lock()->getTexturesMap();
    //auto img = tex[0].lock()->getImages()[0];
    //
    //String imgPath = "D:/GitHub/MotoresIDV7_EchoEngine/EchoEngine/bin/" + img->getPath();
    //
    //auto diffuseTextureSampler = UsdShadeShader::Define(stage, matPath.AppendChild(TfToken("diffuseTexture")));
    //diffuseTextureSampler.CreateIdAttr(VtValue(TfToken("UsdUVTexture")));
    //diffuseTextureSampler.CreateInput(TfToken("file"), SdfValueTypeNames->Asset).Set(SdfAssetPath(imgPath));
    ////diffuseTextureSampler.CreateInput(TfToken("rgba"), SdfValueTypeNames->Color4fArray).Set(VtVec4fArray());
    //diffuseTextureSampler.CreateInput(TfToken("st"), SdfValueTypeNames->Float2).ConnectToSource(stReader.ConnectableAPI(), TfToken("result"));
    //diffuseTextureSampler.CreateOutput(TfToken("rgb"), SdfValueTypeNames->Float3);
    //pbrShader.CreateInput(TfToken("diffuseColor"), SdfValueTypeNames->Color3f).ConnectToSource(diffuseTextureSampler.ConnectableAPI(), TfToken("rgb"));
    //
    //auto stInput = mat.CreateInput(TfToken("frame:stPrimvarName"), SdfValueTypeNames->Token);
    //stInput.Set(TfToken("st"));
    //
    //stReader.CreateInput(TfToken("varname"), SdfValueTypeNames->Token).ConnectToSource(stInput);
    //UsdShadeMaterialBindingAPI(mesh).Bind(mat);

    
    String matName = stm.second.lock()->getResourceName();
    String mdlPath = "./" + createMaterial(matName, g_stageFileFolder, stm.second);

    TfToken materialNameToken = TfToken(matName);
    SdfPath matPath = SdfPath::AbsoluteRootPath()
                        .AppendChild(_tokens->Root)
                        .AppendChild(_tokens->Looks)
                        .AppendChild(materialNameToken);
    UsdShadeMaterial newMat = UsdShadeMaterial::Define(stage, matPath);

    // MDL Shader
    {
      // Create the MDL shader to bind to the material
      SdfAssetPath mdlShaderModule = SdfAssetPath(mdlPath);
      SdfPath shaderPath = matPath.AppendChild(materialNameToken);
      UsdShadeShader mdlShader = UsdShadeShader::Define(stage, shaderPath);
      mdlShader.CreateIdAttr(VtValue(_tokens->shaderId));

      // These attributes will be reworked or replaced in the official MDL schema for USD.
      // https://developer.nvidia.com/usd/MDLschema
      mdlShader.SetSourceAsset(mdlShaderModule, _tokens->mdl);
      mdlShader.GetPrim().CreateAttribute(TfToken("info:mdl:sourceAsset:subIdentifier"), SdfValueTypeNames->Token, false, SdfVariabilityUniform).Set(materialNameToken);

      // Set the linkage between material and MDL shader
      UsdShadeOutput mdlOutput = newMat.CreateSurfaceOutput(_tokens->mdl);
      mdlOutput.ConnectToSource(mdlShader, _tokens->out);
    }

    UsdShadeMaterialBindingAPI usdMaterialBinding(mesh);
    usdMaterialBinding.Bind(newMat);


    stm.second.lock()->m_dirtyMat = false;
    skMesh->m_dirtyMatFlags[meshIndex].first = false;
    ++meshIndex;
  }
}
void
addDirectionalLightToScenegraph(const SdfPath& parentPath,
                                UsdStageRefPtr stage,
                                WPtr<CLight> lightCmp,
                                uint32 lightIndex)
{
  // Construct /Root/Light path
  SdfPath lightPath = parentPath.AppendChild(TfToken("DirLight" + eeToString(lightIndex)));
  UsdLuxDistantLight newLight = UsdLuxDistantLight::Define(stage, lightPath);

  // Set the attributes
  auto sLight = lightCmp.lock();
  Color lightColor = sLight->getColor();
  float lightIntensity = sLight->getIntensity() * 1000.0f;

  newLight.CreateAngleAttr(VtValue(0.53f));
  GfVec3f color(lightColor.r, lightColor.g, lightColor.b);
  newLight.CreateColorAttr(VtValue(color));
  newLight.CreateIntensityAttr(VtValue(lightIntensity));

  // Commit the changes to the USD
  stage->Save();
  omniClientLiveProcess();
}
void
addPointLightToScenegraph(const SdfPath& parentPath,
                          UsdStageRefPtr stage,
                          WPtr<CLight> lightCmp,
                          uint32 lightIndex)
{
  // Construct /Root/Light path
  SdfPath lightPath = parentPath.AppendChild(TfToken("PointLight" + eeToString(lightIndex)));
  UsdLuxSphereLight newLight = UsdLuxSphereLight::Define(stage, lightPath);

  // Set the attributes
  auto sLight = lightCmp.lock();
  sLight->getDirection();
  Color lightColor = sLight->getColor();
  float lightIntensity = sLight->getIntensity();

  GfVec3f color(lightColor.r, lightColor.g, lightColor.b);
  newLight.CreateColorAttr(VtValue(color));
  newLight.CreateIntensityAttr(VtValue(lightIntensity * 1000.0f));
  newLight.CreateRadiusAttr(VtValue(lightIntensity * 100.0f));

  // Commit the changes to the USD
  stage->Save();
  omniClientLiveProcess();
}
void
addSpotLightToScenegraph(const SdfPath& parentPath,
                         UsdStageRefPtr stage,
                         WPtr<CLight> lightCmp,
                         uint32 lightIndex)
{
  // Construct /Root/Light path
  SdfPath lightPath = parentPath.AppendChild(TfToken("SpotLight" + eeToString(lightIndex)));
  UsdLuxDiskLight newLight = UsdLuxDiskLight::Define(stage, lightPath);

  // Set the attributes
  auto sLight = lightCmp.lock();
  sLight->getDirection();
  Color lightColor = sLight->getColor();
  float lightIntensity = sLight->getIntensity();
  float lightInnerAngle = sLight->getInnerAngle();

  GfVec3f color(lightColor.r, lightColor.g, lightColor.b);
  newLight.CreateColorAttr(VtValue(color));
  newLight.CreateIntensityAttr(VtValue(lightIntensity * 1000.0f));
  float distanceRad = 1.5f * 100.f;
  newLight.CreateRadiusAttr(VtValue(Math::tan(lightInnerAngle) * distanceRad));

  // Commit the changes to the USD
  stage->Save();
  omniClientLiveProcess();
}
void
addLightCmpToScenegraph(const SdfPath& parentPath,
                        UsdStageRefPtr stage,
                        WPtr<CLight> lightCmp)
{
  switch (lightCmp.lock()->getLightType())
  {
  case eLIGHT_TYPE::kDirectional:
    addDirectionalLightToScenegraph(parentPath, stage, lightCmp, 0);
  break;
  case eLIGHT_TYPE::kPoint:
    addPointLightToScenegraph(parentPath, stage, lightCmp, 0);
  break;
  case eLIGHT_TYPE::kSpot:
    addSpotLightToScenegraph(parentPath, stage, lightCmp, 0);
  break;
  }
}
void
addActorToScenegraph(const SdfPath& parentPath,
                     UsdStageRefPtr stage,
                     WPtr<Actor> sceneActor)
{
  if (sceneActor.expired()) return;

  auto& memoryMan = MemoryManager::instance();

  auto sActor = sceneActor.lock();

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
                               memoryMan.reinterpretPtr<CStaticMesh>(cmp));
      break;
    case eCOMPONENT_TYPE::kSkeletalMesh:
      addSkMeshCmpToScenegraph(parentPath,
                               stage,
                               memoryMan.reinterpretPtr<CSkeletalMesh>(cmp));
      break;
    case eCOMPONENT_TYPE::kLight:
      addLightCmpToScenegraph(parentPath,
                              stage,
                              memoryMan.reinterpretPtr<CLight>(cmp));
      break;
    }
  }
}
bool
setActorOnStageHelper(const SdfPath& parentPath,
                      UsdStageRefPtr stage,
                      SPtr<ActorNode> actNode)
{
  auto sActor = actNode->actorValue.lock();
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
  if (!gStage) {
    Logger::instance().consoleLog("There is no Omniverse Stage opened now.");
    return false;
  }

  auto& actorsTree = scenegraph.lock()->getActorsTree();
  for (auto& a : actorsTree) {
    setActorOnStageHelper(gRootPrimPath, gStage, a);
  }

  // Commit the changes to the USD
  omniClientLiveProcess();
  gStage->Save();
  return true;
}

void
loadMeshFromStage(const UsdGeomMesh& meshNode,
                  UsdStageRefPtr stage,
                  WPtr<Actor> actorMesh,
                  bool firstTime)
{
  auto& resourceMan = ResourceManager::instance();

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


  //String matName("Mat_" + stm.second.lock()->getResourceName());
  //SdfPath matPath = meshPrimPath.AppendChild(TfToken("Mat_Pat"));
  //auto mat = UsdShadeMaterial::Define(stage, matPath);
  //
  //auto pbrShader = UsdShadeShader::Define(stage, matPath.AppendChild(TfToken("PBRShader")));
  //pbrShader.CreateIdAttr(VtValue(TfToken("UsdPreviewSurface")));
  //pbrShader.CreateInput(TfToken("roughness"), SdfValueTypeNames->Float).Set(0.4f);
  //pbrShader.CreateInput(TfToken("metallic"), SdfValueTypeNames->Float).Set(0.0f);
  //
  //mat.CreateSurfaceOutput().ConnectToSource(pbrShader.ConnectableAPI(), TfToken("surface"));
  //
  //auto stReader = UsdShadeShader::Define(stage, matPath.AppendChild(TfToken("stReader")));
  //stReader.CreateIdAttr(VtValue(TfToken("UsdPrimvarReader_float2")));
  //
  //auto tex = stm.second.lock()->getTexturesMap();
  //auto img = tex[0].lock()->getImages()[0];
  //
  //String imgPath = "D:/GitHub/MotoresIDV7_EchoEngine/EchoEngine/bin/" + img->getPath();
  //
  //auto diffuseTextureSampler = UsdShadeShader::Define(stage, matPath.AppendChild(TfToken("diffuseTexture")));
  //diffuseTextureSampler.CreateIdAttr(VtValue(TfToken("UsdUVTexture")));
  //diffuseTextureSampler.CreateInput(TfToken("file"), SdfValueTypeNames->Asset).Set(SdfAssetPath(imgPath));
  ////diffuseTextureSampler.CreateInput(TfToken("rgba"), SdfValueTypeNames->Color4fArray).Set(VtVec4fArray());
  //diffuseTextureSampler.CreateInput(TfToken("st"), SdfValueTypeNames->Float2).ConnectToSource(stReader.ConnectableAPI(), TfToken("result"));
  //diffuseTextureSampler.CreateOutput(TfToken("rgb"), SdfValueTypeNames->Float3);
  //pbrShader.CreateInput(TfToken("diffuseColor"), SdfValueTypeNames->Color3f).ConnectToSource(diffuseTextureSampler.ConnectableAPI(), TfToken("rgb"));
  //
  //auto stInput = mat.CreateInput(TfToken("frame:stPrimvarName"), SdfValueTypeNames->Token);
  //stInput.Set(TfToken("st"));
  //
  //stReader.CreateInput(TfToken("varname"), SdfValueTypeNames->Token).ConnectToSource(stInput);
  //UsdShadeMaterialBindingAPI(mesh).Bind(mat);


  //auto diffPath = meshNode.GetPath().AppendChild(TfToken("Mat_Pat")).AppendChild(TfToken("diffuseTexture"));
  //String pathStr = diffPath.GetString();
  //SdfAssetPath imgAssetPath;
  //UsdShadeShader::Get(stage, diffPath).GetInput(TfToken("file")).Get<SdfAssetPath>(&imgAssetPath);
  //String imgPathVal = imgAssetPath.GetAssetPath();
  //
  //auto imgPathSize = static_cast<int64>(imgPathVal.size());
  //String realImgPathVal;
  //String currentFolder;
  //bool readingFolder = false;
  //for (int64 i = imgPathSize - 1; i >= 0; --i) {
  //  if (!readingFolder) {
  //    if (imgPathVal[i] == '/' || imgPathVal[i] == '\\') {
  //      readingFolder = true;
  //      currentFolder += imgPathVal[i];
  //      continue;
  //    }
  //    realImgPathVal = imgPathVal[i] + realImgPathVal;
  //  }
  //  else {
  //    if (imgPathVal[i] == '/' || imgPathVal[i] == '\\') {
  //      if (currentFolder == "Textures/") {
  //        realImgPathVal = currentFolder + realImgPathVal;
  //        break;
  //      }
  //      else {
  //        realImgPathVal = currentFolder + realImgPathVal;
  //        currentFolder.clear();
  //        currentFolder += imgPathVal[i];
  //        continue;
  //      }
  //    }
  //    currentFolder = imgPathVal[i] + currentFolder;
  //  }
  //}
  //
  //WString imgPath = eeStringtoWString(realImgPathVal);
  //
  //String imgFileName;
  //getFileName(imgPath, imgFileName);
  //auto tex = resourceMan.loadTextureFromFile(imgPath, imgFileName + "_tex");
  //
  //if (!tex.expired()) {
  //  Map<uint32, WPtr<Texture>> texsMap;
  //  texsMap[0] = tex;
  //  mat = resourceMan.loadMaterialFromTextures(texsMap, imgFileName + "_mat");
  //}
  //
  //
  //auto stMesh =
  //resourceMan.getResourceStaticMesh(actorMesh.lock()->getName() + "_stm");
  //if (stMesh.expired()) {
  //  stMesh =
  //  resourceMan.loadStaticMeshFromMeshesArray(
  //                                      {Pair<Mesh, WPtr<Material>>(mesh, mat)},
  //                                      actorMesh.lock()->getName() + "_stm",
  //                                      furtherDist,
  //                                      maxCoord,
  //                                      minCoord);
  //}
  //else {
  //  if (firstTime) {
  //    stMesh.lock()->clear();
  //  }
  //  stMesh.lock()->addMesh(mesh, mat, furtherDist, maxCoord, minCoord);
  //}
  //
  //if (firstTime) {
  //  stMeshCmp->setStaticMesh(stMesh);
  //
  //  actorMesh.lock()->addComponent<CBounds>();
  //  actorMesh.lock()->addComponent<CRender>();
  //}
}
void
loadDirectionalLightFromStage(const UsdLuxDistantLight& lightNode,
                              UsdStageRefPtr stage,
                              WPtr<Actor> actorMesh,
                              bool /*firstTime*/)
{
  Color lightColor;
  float lightIntensity = 0.0f;

  VtValue colorVal;
  lightNode.GetColorAttr().Get(&colorVal);
  GfVec3f color = colorVal.Get<GfVec3f>();
  const float* colorArr = color.GetArray();
  lightColor.r = colorArr[0];
  lightColor.g = colorArr[1];
  lightColor.b = colorArr[2];
  lightColor.a = 1.0f;
  VtValue intensityVal;
  lightNode.GetIntensityAttr().Get(&intensityVal);
  lightIntensity = intensityVal.Get<float>();

  auto sLight = actorMesh.lock()->addComponent<CLight>().lock();
  sLight->setLightType(eLIGHT_TYPE::kDirectional);
  sLight->setColor(lightColor);
  sLight->setIntensity(lightIntensity * 0.001f);
}
void
loadPointLightFromStage(const UsdLuxSphereLight& lightNode,
                        UsdStageRefPtr stage,
                        WPtr<Actor> actorMesh,
                        bool /*firstTime*/)
{
  Color lightColor;
  float lightIntensity = 0.0f;

  VtValue colorVal;
  lightNode.GetColorAttr().Get(&colorVal);
  GfVec3f color = colorVal.Get<GfVec3f>();
  const float* colorArr = color.GetArray();
  lightColor.r = colorArr[0];
  lightColor.g = colorArr[1];
  lightColor.b = colorArr[2];
  lightColor.a = 1.0f;
  VtValue intensityVal;
  lightNode.GetIntensityAttr().Get(&intensityVal);
  lightIntensity = intensityVal.Get<float>();

  auto sLight = actorMesh.lock()->addComponent<CLight>().lock();
  sLight->setLightType(eLIGHT_TYPE::kPoint);
  sLight->setColor(lightColor);
  sLight->setIntensity(lightIntensity * 0.001f);
}
void
loadSpotLightFromStage(const UsdLuxDiskLight& lightNode,
                       UsdStageRefPtr stage,
                       WPtr<Actor> actorMesh,
                       bool /*firstTime*/)
{
  Color lightColor;
  float lightIntensity = 0.0f;
  float lightInnerAngle = 0.0f;

  VtValue colorVal;
  lightNode.GetColorAttr().Get(&colorVal);
  GfVec3f color = colorVal.Get<GfVec3f>();
  const float* colorArr = color.GetArray();
  lightColor.r = colorArr[0];
  lightColor.g = colorArr[1];
  lightColor.b = colorArr[2];
  lightColor.a = 1.0f;
  VtValue intensityVal;
  lightNode.GetIntensityAttr().Get(&intensityVal);
  lightIntensity = intensityVal.Get<float>();
  VtValue angleVal;
  lightNode.GetRadiusAttr().Get(&angleVal);
  lightInnerAngle = angleVal.Get<float>();

  auto sLight = actorMesh.lock()->addComponent<CLight>().lock();
  sLight->setLightType(eLIGHT_TYPE::kPoint);
  sLight->setColor(lightColor);
  sLight->setIntensity(lightIntensity * 0.001f);
  float distanceRad = 1.5f * 100.f;
  sLight->setInnerAngle(Math::atan(lightInnerAngle / distanceRad));
}
void
traversePrimChild(const UsdPrim& childPrim,
                  UsdStageRefPtr stage,
                  SPtr<Scene> scenegraph,
                  SPtr<Actor> parentActor)
{
  //auto& act = static_cast<UsdGeomXform>(childPrim);

  GfVec3i defaultRotationOrder(0, 1, 2);
  GfVec3d pos(0);
  GfVec3d rot(0);
  GfVec3d sca(1);

  if (!xformUtils::getLocalTransformSRT(childPrim,
                                        pos,
                                        rot,
                                        defaultRotationOrder,
                                        sca)) { 
    return;
  }

  auto trans = parentActor->getTransform().lock();
  const double* position = pos.GetArray();
  trans->setPosition(Vector3f{ static_cast<float>(-position[0]),
                               static_cast<float>(position[1]),
                               static_cast<float>(position[2]) } * 0.01f);
  const double* rotationXYZ = rot.GetArray();
  trans->setRotation(Quaternion{Vector3f{ static_cast<float>(rotationXYZ[0]),
                                          static_cast<float>(-rotationXYZ[1]),
                                          static_cast<float>(-rotationXYZ[2]) }
                              * Math::kPI_OVER_180});
  const double* scale = sca.GetArray();
  trans->setScale(Vector3f{ static_cast<float>(scale[0]),
                            static_cast<float>(scale[1]),
                            static_cast<float>(scale[2]) });



  const auto& children = childPrim.GetAllChildren();
  bool firstTime = true;
  for (const auto& child : children) {
    if (child.IsA<UsdGeomXform>()) {
      auto newAct = scenegraph->addActor(child.GetName()).lock();
      scenegraph->setActorChild(parentActor->getName(), newAct->getName());

      traversePrimChild(child, stage, scenegraph, newAct);
    }
    else if (child.IsA<UsdGeomMesh>()) {
      loadMeshFromStage(static_cast<UsdGeomMesh>(child), stage, parentActor, firstTime);
    }
    else if (child.IsA<UsdLuxDistantLight>()) {
      loadDirectionalLightFromStage(static_cast<UsdLuxDistantLight>(child), stage, parentActor, firstTime);
    }
    else if (child.IsA<UsdLuxSphereLight>()) {
      loadPointLightFromStage(static_cast<UsdLuxSphereLight>(child), stage, parentActor, firstTime);
    }
    else if (child.IsA<UsdLuxDiskLight>()) {
      loadSpotLightFromStage(static_cast<UsdLuxDiskLight>(child), stage, parentActor, firstTime);
    }

    firstTime = false;
  }
}
void
OmniverseApi::getScenegraphFromStage(WPtr<Scene> scenegraph)
{
  auto& loggerMan = Logger::instance();
  //auto& memoryMan = MemoryManager::instance();

  if (!gStage) {
    loggerMan.consoleLog("There is no Omniverse Stage opened now.");
    return;
  }

  auto sScene = scenegraph.lock();
  sScene->setName(m_stageFileName);

  auto rootPrim = gStage->GetPrimAtPath(gRootPrimPath);
  const auto& children = rootPrim.GetAllChildren();
  for (const auto& child : children) {
    auto parentAct = sScene->addActor(child.GetName()).lock();

    traversePrimChild(child, gStage, sScene, parentAct);
  }
}

void
updateDirectionalLightFromStage(const UsdLuxDistantLight& lightNode,
                                UsdStageRefPtr stage,
                                WPtr<Actor> actorMesh,
                                bool /*firstTime*/)
{
  Color lightColor;
  float lightIntensity = 0.0f;

  VtValue colorVal;
  lightNode.GetColorAttr().Get(&colorVal);
  GfVec3f color = colorVal.Get<GfVec3f>();
  const float* colorArr = color.GetArray();
  lightColor.r = colorArr[0];
  lightColor.g = colorArr[1];
  lightColor.b = colorArr[2];
  lightColor.a = 1.0f;
  VtValue intensityVal;
  lightNode.GetIntensityAttr().Get(&intensityVal);
  lightIntensity = intensityVal.Get<float>();

  auto sLight = actorMesh.lock()->getComponent<CLight>().lock();
  sLight->setLightType(eLIGHT_TYPE::kDirectional);
  sLight->setColor(lightColor);
  sLight->setIntensity(lightIntensity * 0.001f);
}
void
updatePointLightFromStage(const UsdLuxSphereLight& lightNode,
                          UsdStageRefPtr stage,
                          WPtr<Actor> actorMesh,
                          bool /*firstTime*/)
{
  Color lightColor;
  float lightIntensity = 0.0f;

  VtValue colorVal;
  lightNode.GetColorAttr().Get(&colorVal);
  GfVec3f color = colorVal.Get<GfVec3f>();
  const float* colorArr = color.GetArray();
  lightColor.r = colorArr[0];
  lightColor.g = colorArr[1];
  lightColor.b = colorArr[2];
  lightColor.a = 1.0f;
  VtValue intensityVal;
  lightNode.GetIntensityAttr().Get(&intensityVal);
  lightIntensity = intensityVal.Get<float>();

  auto sLight = actorMesh.lock()->getComponent<CLight>().lock();
  sLight->setLightType(eLIGHT_TYPE::kPoint);
  sLight->setColor(lightColor);
  sLight->setIntensity(lightIntensity * 0.001f);
}
void
updateSpotLightFromStage(const UsdLuxDiskLight& lightNode,
                         UsdStageRefPtr stage,
                         WPtr<Actor> actorMesh,
                         bool /*firstTime*/)
{
  Color lightColor;
  float lightIntensity = 0.0f;
  float lightInnerAngle = 0.0f;

  VtValue colorVal;
  lightNode.GetColorAttr().Get(&colorVal);
  GfVec3f color = colorVal.Get<GfVec3f>();
  const float* colorArr = color.GetArray();
  lightColor.r = colorArr[0];
  lightColor.g = colorArr[1];
  lightColor.b = colorArr[2];
  lightColor.a = 1.0f;
  VtValue intensityVal;
  lightNode.GetIntensityAttr().Get(&intensityVal);
  lightIntensity = intensityVal.Get<float>();
  VtValue angleVal;
  lightNode.GetRadiusAttr().Get(&angleVal);
  lightInnerAngle = angleVal.Get<float>();

  auto sLight = actorMesh.lock()->getComponent<CLight>().lock();
  sLight->setLightType(eLIGHT_TYPE::kPoint);
  sLight->setColor(lightColor);
  sLight->setIntensity(lightIntensity * 0.001f);
  float distanceRad = 1.5f * 100.f;
  sLight->setInnerAngle(Math::atan(lightInnerAngle / distanceRad));
}
void
updateTraversePrimChild(const UsdPrim& childPrim,
                        UsdStageRefPtr stage,
                        SPtr<Scene> scenegraph,
                        SPtr<Actor> parentActor)
{
  //auto& act = static_cast<UsdGeomXform>(childPrim);

  GfVec3i defaultRotationOrder(0, 1, 2);
  GfVec3d pos(0);
  GfVec3d rot(0);
  GfVec3d sca(1);

  if (!xformUtils::getLocalTransformSRT(childPrim,
                                        pos,
                                        rot,
                                        defaultRotationOrder,
                                        sca)) { 
    return;
  }

  auto trans = parentActor->getTransform().lock();
  const double* position = pos.GetArray();
  trans->setPosition(Vector3f{ static_cast<float>(-position[0]),
                               static_cast<float>(position[1]),
                               static_cast<float>(position[2]) } * 0.01f);
  const double* rotationXYZ = rot.GetArray();
  trans->setRotation(Quaternion{Vector3f{ static_cast<float>(rotationXYZ[0]),
                                          static_cast<float>(-rotationXYZ[1]),
                                          static_cast<float>(-rotationXYZ[2]) }
                              * Math::kPI_OVER_180});
  const double* scale = sca.GetArray();
  trans->setScale(Vector3f{ static_cast<float>(scale[0]),
                            static_cast<float>(scale[1]),
                            static_cast<float>(scale[2]) });



  const auto& children = childPrim.GetAllChildren();
  bool firstTime = true;
  for (const auto& child : children) {
    if (child.IsA<UsdGeomXform>()) {
      auto newAct = scenegraph->getActor(child.GetName()).lock();
      if (!newAct) {
        newAct = scenegraph->addActor(child.GetName()).lock();
        scenegraph->setActorChild(parentActor->getName(), newAct->getName()); // TODO: Check if it isn't already a child of this actor.
      }

      updateTraversePrimChild(child, stage, scenegraph, newAct);
    }
    else if (child.IsA<UsdLuxDistantLight>()) {
      updateDirectionalLightFromStage(static_cast<UsdLuxDistantLight>(child), stage, parentActor, firstTime);
    }
    else if (child.IsA<UsdLuxSphereLight>()) {
      updatePointLightFromStage(static_cast<UsdLuxSphereLight>(child), stage, parentActor, firstTime);
    }
    else if (child.IsA<UsdLuxDiskLight>()) {
      updateSpotLightFromStage(static_cast<UsdLuxDiskLight>(child), stage, parentActor, firstTime);
    }

    firstTime = false;
  }
}
void
OmniverseApi::updateScenegraphFromStage(WPtr<Scene> scenegraph)
{
  auto& loggerMan = Logger::instance();
  //auto& memoryMan = MemoryManager::instance();

  if (!gStage) {
    loggerMan.consoleLog("There is no Omniverse Stage opened now.");
    return;
  }
  if (scenegraph.expired()) {
    loggerMan.consoleLog("No scenegraph passed.");
    return;
  }

  omniClientLiveProcess();
  gStage->Reload();

  auto sScene = scenegraph.lock();

  auto rootPrim = gStage->GetPrimAtPath(gRootPrimPath);
  const auto& children = rootPrim.GetAllChildren();
  for (const auto& child : children) {
    auto parentAct = sScene->getActor(child.GetName()).lock();
    if (!parentAct) {
      parentAct = sScene->addActor(child.GetName()).lock();
    }

    updateTraversePrimChild(child, gStage, sScene, parentAct);
  }
}

void
OmniverseApi::copyFileToDest(const String& src, const String& dest)
{
  {
    std::unique_lock<std::mutex> lk(gLogMutex);
  }
  omniClientWait(omniClientDelete(dest.c_str(), nullptr, nullptr));
  {
    std::unique_lock<std::mutex> lk(gLogMutex);
    std::cout << "finished" << std::endl;
  }

  {
    std::unique_lock<std::mutex> lk(gLogMutex);
  }
  omniClientWait(omniClientCopy(src.c_str(), dest.c_str(), nullptr, nullptr));
  {
    std::unique_lock<std::mutex> lk(gLogMutex);
    std::cout << "finished" << std::endl;
  }
}



EE_EXTERN EE_OMNIVERSE_EXPORT void
initPlugin()
{
  OmniverseManager::startUp<OmniverseApi>();
}
}