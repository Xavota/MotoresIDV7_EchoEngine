#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
class Window
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
   * @param width
   * The width of the window.
   * @param height
   * The height of the window.
   */
   Window(uint32 width, uint32 height);
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
   * @param width
   * The width of the window.
   * @param height
   * The height of the window.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  bool
  initWindow(uint32 width, uint32 height);

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
  resize(uint32 width, uint32 height);

 private:
  /**
   * The width of the window
   */
  uint32 m_width = 0u;
  /**
   * The height of the window
   */
  uint32 m_height = 0u;
};
}
