#pragma once
#include "eePrerequisitesCore.h"

#include <eeModule.h>

#include <eeTransform.h>

namespace eeEngineSDK {
namespace eOMNI_STATUS {
enum E : uint8 {
  kNotStarted = 0,
  kOk,
  kFailed
};
}
class EE_CORE_EXPORT OmniverseManager : public Module<OmniverseManager>
{
 public:
  /**
   * @brief
   * Default constructor
   */
   OmniverseManager() = default;
  /**
   * @brief
   * Default destructor.
   */
  virtual
  ~OmniverseManager() = default;

  /**
  * @brief
  * Starts the omniverse application.
  *
  * @description
  * Starts the omniverse application.
  *
  * @param doLiveEdit
  * True if the application is going to check for updates constantly.
  */
  virtual bool
  init(bool /*doLiveEdit*/) { return false; }

  /**
  * @brief
  * Stops the omniverse application.
  *
  * @description
  * Stops the omniverse application.
  */
  virtual void
  destroy() {}

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
  virtual bool
  isLive() { return false; }
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
  virtual bool
  stageIsOpen() { return false; }

  /**
  * @brief
  * Sets a status to the application.
  *
  * @description
  * Updates the status of the application to what it's needed. Only for internal
  * use.
  *
  * @param newStatus
  * The new status to set.
  */
  FORCEINLINE void
  setStatus(eOMNI_STATUS::E newStatus) { m_status = newStatus; }

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
  virtual void
  createStage(const String& /*stageUrl*/) {}
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
  virtual void
  openStage(const String& /*stageUrl*/) {}
  /**
  * @brief
  * Closes the active stage.
  *
  * @description
  * Closes the active stage.
  */
  virtual void
  closeStage() {}
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
  virtual void
  saveStage(WPtr<Scene> /*scenegraph*/) {}

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
  virtual String
  getUserLocalPath() { return ""; }

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
  virtual bool
  setScenegraphOnStage(WPtr<Scene> /*scenegraph*/) { return false; }
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
  virtual void
  getScenegraphFromStage(WPtr<Scene> scenegraph) {}
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
  virtual void
  updateScenegraphFromStage(WPtr<Scene> /*scenegraph*/) {}

  
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
  virtual Vector<String>
  getExisitingSessionNames() { return {}; }
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
  virtual bool
  joinSession(const String& /*sessionName*/) { return false; }
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
  virtual bool
  createNewSession(const String& /*sessionName*/) { return false; }
  /**
  * @brief
  * Stops the currently active live session.
  *
  * @description
  * Stops the currently active live session.
  */
  virtual void
  stopLiveSession() {}
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
  virtual const String&
  getActiveSessionName() { return ""; }

protected:
  /**
   * Quick checker for its status.
   */
  eOMNI_STATUS::E m_status = eOMNI_STATUS::kNotStarted;
};
}