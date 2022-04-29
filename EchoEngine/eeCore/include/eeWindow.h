/************************************************************************/
/**
 * @file eeWindow.h
 * @author Diego Castellanos
 * @date 05/03/22
 * @brief
 * The window class, for managing the windows in any api.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
/**
 * @brief
 * The window class, for managing the windows in any api.
 */
class EE_CORE_EXPORT Window
{
 public: 
  /**
   * @brief
   * Default constructor
   */
   Window() = default;
  /**
   * @brief
   * Initializes the window.
   * 
   * @description
   * Initializes the window from its size.
   *
   * @param callback
   * The function callback for the window events.
   * @param width
   * The width of the window.
   * @param height
   * The height of the window.
   */
   Window(void* callback, uint32 width, uint32 height);
  /**
   * @brief
   * Default destructor
   */
  virtual 
  ~Window() = default;


  /**
   * @brief
   * Initializes the window.
   *
   * @description
   * Initializes the window from its size.
   *
   * @param callback
   * The function callback for the window events.
   * @param width
   * The width of the window.
   * @param height
   * The height of the window.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  virtual bool
  initWindow(void* callback, uint32 width, uint32 height);
  /**
   * @brief
   * Initializes the window.
   *
   * @description
   * Initializes the window from its size.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  virtual bool
  initRenders();

  /**
   * @brief
   * Shows the window.
   *
   * @description
   * Opens the window on the screen.
   */
  virtual void
  showWindow() {}
  /**
   * @brief
   * Minimizes the window.
   *
   * @description
   * Minimizes the window.
   */
  virtual void
  minimizeWindow() {}
  /**
   * @brief
   * Maximizes the window.
   *
   * @description
   * Maximizes the window.
   */
  virtual void
  maximizeWindow() {}
  /**
   * @brief
   * Closes the window.
   *
   * @description
   * Closes the window.
   */
  virtual void
  closeWindow() {}

  /**
   * @brief
   * Resize the window.
   *
   * @description
   * Resize the window.
   *
   * @param width
   * The new width of the window.
   * @param height
   * The new height of the window.
   *
   * @return
   * Weather it succeed or failed to resize.
   */
  virtual bool
  resize(uint32 width, uint32 height);


  /**
   * @brief
   * Returns the render target of the window.
   *
   * @description
   * Returns the render target of the window.
   *
   * @return
   * The render target of the window.
   */
  SPtr<Texture>
  getRenderTarget() const { return m_rtv; }
  /**
   * @brief
   * Returns the depth stencil of the window.
   *
   * @description
   * Returns the depth stencil of the window.
   *
   * @return
   * The depth stencil of the window.
   */
  SPtr<Texture>
  getDepthStencil() const { return m_dsv; }

  /**
   * @brief
   * Returns the window pointer.
   *
   * @description
   * Returns the window pointer.
   *
   * @return
   * The window pointer.
   */
  void*
  getWindowPtr() { return m_win; }

  /**
   * @brief
   * Releases the data.
   *
   * @description
   * Deletes the memory of all data allocated.
   */
  void 
  release();

 protected:
  /**
   * The width of the window
   */
  uint32 m_width = 0u;
  /**
   * The height of the window
   */
  uint32 m_height = 0u;

  /*
  * The back buffer.
  */
  SPtr<Texture> m_rtv;
  /*
  * The depth stencil of the back buffer
  */
  SPtr<Texture> m_dsv;

  /**
   * The screen information
   */
  void* m_win = nullptr;
};
}
