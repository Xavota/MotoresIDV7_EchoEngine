/************************************************************************/
/**
 * @file eePrerequisitesCore.h
 * @author Diego Castellanos
 * @date 10/10/21
 * @brief A derived class of BaseApp, for testing porpoise.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include <eeBaseApp.h>

using eeEngineSDK::BaseApp;
using eeEngineSDK::int32;
using eeEngineSDK::SPtr;
using eeEngineSDK::Object;
using eeEngineSDK::ConstantBuffer;
using eeEngineSDK::RenderTarget;
using eeEngineSDK::DepthStencil;
using eeEngineSDK::RasterizerState;
using eeEngineSDK::Actor;
using eeEngineSDK::CCamera;

/**
* @brief
* A derived class of BaseApp, for testing porpoise.
*/
class BaseAppTest1 : public BaseApp
{
 public:
  /**
  * @brief
  * Default constructor
  */
  BaseAppTest1() = default;
  /**
  * @brief
  * Default destructor
  */
  ~BaseAppTest1() = default;

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
  update() override;

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
  * A Screen Align Quad, used for rendering textures of a render target on
  * another
  */
  SPtr<Object> m_SAQ;

  /*
  * The buffer for the view matrix.
  */
  SPtr<ConstantBuffer> m_viewMatrixBuffer;
  /*
  * The buffer for the projection matrix.
  */
  SPtr<ConstantBuffer> m_projectionMatrixBuffer;

  ///*
  //* The back buffer.
  //*/
  //SPtr<RenderTarget> m_rtv;
  ///*
  //* The depth stencil of the back buffer
  //*/
  //SPtr<DepthStencil> m_dsv;

  /*
  * A rasterizer for on world objects rendering.
  */
  SPtr<RasterizerState> m_rasterizer;
  /*
  * A rasterizer for on screen rendering.
  */
  SPtr<RasterizerState> m_rasterizer2;


  SPtr<ConstantBuffer> m_viewPosBuffer;

  SPtr<ConstantBuffer> m_constantBuffers;
};
