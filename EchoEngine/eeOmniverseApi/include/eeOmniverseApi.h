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
  
  String
  kritaInit(bool doLiveEdit) override;

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
  stageIsOpen() override;

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
  * @param ipAdrees
  * The IP address where the located Omniverse Api is.
  *
  * @return
  * The user local folder path for the omniverse storage.
  */
  String
  getUserLocalPath(const String& ipAddress) override;
  /**
  * @brief
  * Gets the name of the connected user.
  *
  * @description
  * Returns the name of the connected user.
  *
  * @param ipAdrees
  * The IP address where the located Omniverse Api is.
  *
  * @return
  * The user name of the connected user.
  */
  String
  getConnectedUser(const String& ipAddress) override;

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
  getExisitingSessionNames() override;
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

  /**
  * @brief
  * Copy a file.
  *
  * @description
  * Copy a given file to the destination directory.
  *
  * @param src
  * The directory of the file to copy.
  * @param src
  * The directory for the file to be copy to.
  */
  void
  copyFileToDest(const String& src, const String& dest) override;


 private:
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