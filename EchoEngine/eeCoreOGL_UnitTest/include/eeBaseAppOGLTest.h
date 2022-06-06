/************************************************************************/
/**
 * @file eeBaseAppOGLTest.h
 * @author Diego Castellanos
 * @date 11/05/22
 * @brief A derived class of BaseApp, for testing porpoise.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include <eeBaseApp.h>

using eeEngineSDK::BaseApp;
using eeEngineSDK::int32;

/**
* @brief
* A derived class of BaseApp, for testing porpoise.
*/
class BaseAppOGLTest : public BaseApp
{
 public:
  /**
  * @brief
  * Default constructor
  */
  BaseAppOGLTest() = default;
  /**
  * @brief
  * Default destructor
  */
  ~BaseAppOGLTest() = default;

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
  int32
  run(void* callback) override;

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
  void
  onInit() override;

  /**
  * @brief
  * The update method.
  *
  * @description
  * Updates everything in the app every frame.
  *
  * @param deltaTime
  * The time elapsed since the last frame.
  */
  void
  onUpdate(float deltaTime) override;

  /**
  * @brief
  * The render method.
  *
  * @description
  * Renders everything in the app every frame.
  */
  void
  onRender() override;

  /**
  * @brief
  * The destroy method.
  *
  * @description
  * Cleans all the memory allocated during the application run.
  */
  void
  onDestroy() override;


 private:
};
