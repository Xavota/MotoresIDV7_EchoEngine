/************************************************************************/
/**
 * @file eeDepthStencil.h
 * @author Diego Castellanos
 * @date 25/10/21
 * @brief
 * The Depth Stencil for the graphics module.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
/**
 * @brief
 * The Depth Stencil for the graphics module.
 */
class DepthStencil
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  DepthStencil() = default;
  /**
   * @brief
   * Default destructor.
   */
  virtual
  ~DepthStencil() = default;

  /**
   * @brief
   * Creates a depth stencil.
   *
   * @description
   * Creates the depth stencil resource with a width and height screen.
   *
   * @param width
   * The width of the screen.
   * @param height
   * The height of the screen.
   *
   * @return
   * Whether it succeeded to create or not.
   */
  virtual bool
  create(int32 /*width*/, int32 /*height*/) { return true; }

  /**
   * @brief
   * Loads it to the graphic memory.
   *
   * @description
   * Tells the graphic api to load this depth stencil.
   */
  virtual void
  use() {}
  /**
   * @brief
   * Clean the depth stencil from graphic memory.
   *
   * @description
   * Loads a nullptr depth stencil, so the graphic memory unloads the current
   * one.
   */
  virtual void
  clean() {}

  /**
   * @brief
   * Releases the data.
   *
   * @description
   * Deletes the memory of all data allocated.
   */
  virtual void
  release() {}

 protected:
};
}