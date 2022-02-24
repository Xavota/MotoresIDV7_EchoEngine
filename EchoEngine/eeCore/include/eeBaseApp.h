/************************************************************************/
/**
 * @file eeBaseApp.h
 * @author Diego Castellanos
 * @date 02/10/21
 * @brief
 * The Base app for the program. Initializes, destroy, and run all the
 * application.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

//#include <gainput/gainput.h>

namespace eeEngineSDK {
/**
 * @brief
 * The Base app for the program. Initializes, destroy, and run all the
 * application.
 */
class EE_CORE_EXPORT BaseApp
{
 public:
  /**
   * @brief
   * Default constructor
   */
  BaseApp() = default;
  /**
   * @brief
   * Default destructor
   */
  virtual
  ~BaseApp() = default;

  /**
   * @brief
   * Runs the application.
   *
   * @description
   * Tells everything to initialize and starts the main loop.
   *
   * @return
   * The finish code, tells if there was any error.
   */
  virtual int32
  run(void* callback);

 protected:
  /**
   * @brief
   * Initializes the app child.
   *
   * @description
   * The init event function for the app derivate.
   */
  virtual void
  onInit(){}
  /**
   * @brief
   * The update method.
   *
   * @description
   * Updates everything in the app every frame.
   */
  virtual void
  onUpdate(float /*deltaTime*/){};

  /**
   * @brief
   * The render method.
   *
   * @description
   * Renders everything in the app every frame.
   */
  virtual void
  onRender(){};

  /**
   * @brief
   * The destroy method.
   *
   * @description
   * Cleans all the memory allocated during the application run.
   */
  virtual void
  onDestroy(){};

 private:
  /**
   * @brief
   * Where the application stays till the end.
   *
   * @description
   * Keeps the application running, make the input/update/render loop.
   *
   * @return
   * The finish code, tells if there was any error.
   */
  int32
  mainLoop(void* callback);

  /**
   * @brief
   * Initializes everything.
   *
   * @description
   * Initializes everything that will be needed for the application to run.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  bool
  init(void* callback);

  /**
   * @brief
   * Initializes the systems needed.
   *
   * @description
   * Initializes the systems that the app needs, like the graphics, mesh loading,
   * inputs, etc.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  bool
  initSystems();
  /**
   * @brief
   * Initializes the resources needed.
   *
   * @description
   * Initializes the resources that the app needs, only used for hardcoding
   * resources for testing.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  bool
  initResources(){return true;}

  /**
   * @brief
   * Processes the events given by the system.
   *
   * @description
   * Gets all the events given by the systems and interprets them to something
   * useful.
   */
  void
  processEvents();

  /**
   * @brief
   * The update method.
   *
   * @description
   * Updates everything in the app every frame.
   */
  void
  update(float deltaTime);

  /**
   * @brief
   * The render method.
   *
   * @description
   * Renders everything in the app every frame.
   */
  void
  render();

  /**
   * @brief
   * The destroy method.
   *
   * @description
   * Cleans all the memory allocated during the application run.
   */
  void
  destroy();

 protected:
  /**
   * The width of the screen.
   */
  const uint32 screenWidth = 1280u;
  /**
   * The height of the screen.
   */
  const uint32 screenHeight = 720u;

 private:
  //gainput::InputManager m_inManager;
  //gainput::DeviceId m_mouseID;
  //SPtr<gainput::InputMap> m_inMap;
};
}
