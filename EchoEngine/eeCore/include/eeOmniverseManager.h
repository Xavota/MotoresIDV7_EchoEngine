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
  shutDown() {}

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
  createStage(const String& stageUrl) {}
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
  openStage(const String& stageUrl) {}

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
  * @param name
  * The name of the scene.
  *
  * @return
  * If it succeeded on inserting the scene on teh stage.
  */
  virtual bool
  setScenegraphOnStage(SPtr<Scene> scenegraph, const String& name) { return false; }
  


  // Test functions
  virtual void
  createBox(const Transform& /*boxTransform*/) {}
  virtual void
  createMeshActor(WPtr<Actor> meshActor) {}
  virtual void
  traverseStage() {}

protected:
  /**
   * Quick checker for its status.
   */
  eOMNI_STATUS::E m_status = eOMNI_STATUS::kNotStarted;
};
}