/************************************************************************/
/**
 * @file eeOmniverseApi.h
 * @author Diego Castellanos
 * @date 08/09/22
 * @brief
 * The omniverse class for the functions needed to connect, edit and all.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerrequisitesOmniverse.h"

#include <eeOmniverseManager.h>

#include "xformUtils.h"
#include "primUtils.h"

#include <chrono>
#include <cctype>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <vector>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
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

#include <fstream>
#include <mutex>
#include <memory>
#include <map>
#include <condition_variable>

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
#include <pxr/usd/usdShade/shader.h>
#include <pxr/usd/usd/modelAPI.h>

// Physics includes, note that usdPhysics is now part of USD itself, 
// in newer USD versions these includes will be replaced by pxr official usdPhysics schema
#include <usdPhysics/scene.h>
#include <usdPhysics/rigidBodyAPI.h>
#include <usdPhysics/collisionAPI.h>
#include <usdPhysics/meshCollisionAPI.h>

PXR_NAMESPACE_USING_DIRECTIVE

#include <eeTransform.h>


namespace eeEngineSDK {
/**
 * @brief
 * The omniverse class for the functions needed to connect, edit and all.
 */
class EE_OMNIVERSE_EXPORT OmniverseApi : public OmniverseManager
{
 public:
  /**
   * @brief
   * Default constructor
   */
  OmniverseApi() = default;
  /**
   * @brief
   * Default destructor.
   */
  ~OmniverseApi();

  /**
  * @brief
  * Starts the omniverse application.
  *
  * @description
  * Starts the omniverse application.
  */
  bool
  init(bool doLiveEdit) override;

  /**
  * @brief
  * Stops the omniverse application.
  *
  * @description
  * Stops the omniverse application.
  */
  void
  destroy() override;

  /**
  * @brief
  * Gets if the omniverse api is on a live session.
  *
  * @description
  * Returns true if the omniverse api is on a live session.
  *
  * @return
  * If the omniverse api is on a live session.
  */
  bool
  isLive() override
  {
    return m_isLive;
  }
  /**
  * @brief
  * Gets if the stage is opened.
  *
  * @description
  * Returns true if the stage is opened.
  *
  * @return
  * If the stage is opened.
  */
  bool
  stageIsOpen() override
  {
    return m_stage != nullptr;
  }

  /**
  * @brief
  * Creates a stage .usd file.
  *
  * @description
  * Creates a stage file, .usd file, and loads it to use.
  *
  * @param stageUrl
  * The url of the new stage.
  */
  void
  createStage(const String& stageUrl) override;
  /**
  * @brief
  * Opens a stage .usd file.
  *
  * @description
  * Opens a stage file, .usd file, and loads it to use.
  *
  * @param stageUrl
  * The url of the new stage.
  */
  void
  openStage(const String& stageUrl) override;
  /**
  * @brief
  * Closes the active stage.
  *
  * @description
  * Closes the active stage.
  */
  void
  closeStage() override;
  /**
  * @brief
  * Saves the active stage to the .usd file.
  *
  * @description
  * Saves the active stage to the .usd file.
  *
  * @param scenegraph
  * The scene that will be inserted in the stage.
  */
  void
  saveStage(WPtr<Scene> scenegraph) override;

  /**
  * @brief
  * Gets an absolute path for omniverse.
  *
  * @description
  * Returns the user local folder path for the omniverse storage.
  *
  * @return
  * The user local folder path for the omniverse storage.
  */
  String
  getUserLocalPath() override;

  /**
  * @brief
  * Transform the scene graph into a usd stage.
  *
  * @description
  * Inserts everything in the scene into the usd stage file.
  *
  * @param scenegraph
  * The scene that will be inserted in the stage.
  *
  * @return
  * If it succeeded on inserting the scene on the stage.
  */
  bool
  setScenegraphOnStage(WPtr<Scene> scenegraph) override;
  /**
  * @brief
  * Returns the scenegraph inside the stage.
  *
  * @description
  * Inserts everything in the stage file into the scene.
  *
  * @param scenegraph
  * The scene that will get the stage.
  */
  void
  getScenegraphFromStage(WPtr<Scene> scenegraph) override;
  /**
  * @brief
  * Updates the scenegraph inside the stage.
  *
  * @description
  * Inserts everything on the stage file into the scene.
  *
  * @param scenegraph
  * The scene that will get the stage.
  */
  void
  updateScenegraphFromStage(WPtr<Scene> scenegraph) override;

  
  /**
  * @brief
  * Gets the names of the existing live sessions.
  *
  * @description
  * Returns the names of the existing live sessions.
  *
  * @return
  * The names of the existing live sessions.
  */
  Vector<String>
  getExisitingSessionNames() override
  {
    String sessionFolderForStage = m_liveSessionInfo.GetSessionFolderPathForStage();
    Vector<String> sessionList = m_liveSessionInfo.GetLiveSessionList();
    return sessionList;
  }
  /**
  * @brief
  * Join an existing session.
  *
  * @description
  * Join a live session that already exists.
  *
  * @return
  * If it succeeded on joining the session.
  */
  bool
  joinSession(const String& sessionName) override;
  /**
  * @brief
  * Creates a new session.
  *
  * @description
  * Creates a new live session.
  *
  * @return
  * If it succeeded on creating the session.
  */
  bool
  createNewSession(const String& sessionName) override;
  /**
  * @brief
  * Stops the currently active live session.
  *
  * @description
  * Stops the currently active live session.
  */
  void
  stopLiveSession() override;
  /**
  * @brief
  * Getter of the active session name.
  *
  * @description
  * Returns the currently active session name.
  *
  * @return
  * The currently active session name.
  */
  const String&
  getActiveSessionName() override
  {
    return m_activeSessionName;
  }


 private:
  /**
  * Globals for Omniverse Connection and base Stage
  */
  UsdStageRefPtr m_stage;
  /**
  * The root path of the stage
  */
  SdfPath m_rootPrimPath;
  /**
  * The information for the life session of the Omniverse api
  */
  LiveSessionInfo m_liveSessionInfo;
  /**
  * The current active session name.
  */
  String m_activeSessionName;
  /**
  * If the api is active live.
  */
  bool m_isLive = false;
  /**
  * The path of the stage file.
  */
  String m_stagePath;
  /**
  * The name of the stage file, which is the name of the active scene.
  */
  String m_stageFileName;
};
}