/************************************************************************/
/**
 * @file eeDX11Window.h
 * @author Diego Castellanos
 * @date 05/03/22
 * @brief
 * The window class, for managing the windows in any api.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesDX11.h"
#include <eeWindow.h>

namespace eeEngineSDK {
/**
 * @brief
 * The window class, for managing the windows in any api.
 */
class EE_PLUGINDX11_EXPORT DX11Window : public Window
{
 public: 
  /**
   * @brief
   * Default constructor
   */
  DX11Window() = default;
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
  DX11Window(void* callback, uint32 width, uint32 height);
  /**
   * @brief
   * Default destructor
   */
  ~DX11Window() = default;


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
  bool
  initWindow(void* callback, uint32 width, uint32 height) override;

  /**
   * @brief
   * Shows the window.
   *
   * @description
   * Opens the window on the screen.
   */
  void
  showWindow() override;
  /**
   * @brief
   * Minimizes the window.
   *
   * @description
   * Minimizes the window.
   */
  void
  minimizeWindow() override;
  /**
   * @brief
   * Maximizes the window.
   *
   * @description
   * Maximizes the window.
   */
  void
  maximizeWindow() override;
  /**
   * @brief
   * Closes the window.
   *
   * @description
   * Closes the window.
   */
  void
  closeWindow() override;

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
  bool
  resize(uint32 width, uint32 height) override;

 private:
};
}
