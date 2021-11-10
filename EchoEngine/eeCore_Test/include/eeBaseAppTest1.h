#pragma once
#include <eeBaseApp.h>

using eeEngineSDK::BaseApp;
using eeEngineSDK::int32;
using eeEngineSDK::SPtr;
using eeEngineSDK::Object;
using eeEngineSDK::ConstantBuffer;

class BaseAppTest1 : public BaseApp
{
 public:
  BaseAppTest1();
  ~BaseAppTest1();

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
  virtual bool
  initResources() override;

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
  virtual void
  update(float deltaTime) override;

  /**
  * @brief
  * The render method.
  *
  * @description
  * Renders everything in the app every frame.
  */
  virtual void
  render() override;

  /**
  * @brief
  * The destroy method.
  *
  * @description
  * Cleans all the memory allocated during the application run.
  */
  virtual void
  destroy() override;


 private:
  /*
  * A triangle object, loaded manually.
  */
  SPtr<Object> m_triangle;
  /*
  * A cube object, loaded manually.
  */
  SPtr<Object> m_cube;
  /*
  * An object loaded from a file.
  */
  SPtr<Object> m_model;

  /*
  * The buffer for the view matrix
  */
  SPtr<ConstantBuffer> m_viewMatrixBuffer;
  /*
  * The buffer for the projection matrix
  */
  SPtr<ConstantBuffer> m_projectionMatrixBuffer;
};

