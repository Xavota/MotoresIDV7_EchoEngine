/************************************************************************/
/**
 * @file eeDX11DepthStencil.h
 * @author Diego Castellanos
 * @date 27/10/21
 * @brief
 * The Depth Stencil for the DX11 graphics module.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesDX11.h"
#include <eeDepthStencil.h>
#pragma warning(push, 0)   
#include <d3d11.h>
#pragma warning(pop)  


namespace eeEngineSDK {
/**
 * @brief
 * The Depth Stencil for the DX11 graphics module.
 */
class DX11DepthStencil : public DepthStencil
{
public:
  /**
  * @brief
  * Default constructor.
  */
  DX11DepthStencil() = default;
  /**
  * @brief
  * Default destructor.
  */
  ~DX11DepthStencil();

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
  bool
  create(int32 width, int32 height) override;

  /**
  * @brief
  * Clean the depth stencil from graphic memory.
  *
  * @description
  * Loads a nullptr depth stencil, so the graphic memory unloads the current
  * one.
  */
  void
  clean() override;

  /**
  * @brief
  * Releases the data.
  *
  * @description
  * Deletes the memory of all data allocated.
  */
  void
  release() override;

  /**
  * @brief
  * Gets the resource data.
  *
  * @description
  * Returns the low level graphic api data of the resource.
  *
  * @return
  * Low level graphic api data of the resource.
  */
  ID3D11DepthStencilView*
  getResource();

private:
  /**
  * The depth stencil resource data.
  */
  ID3D11DepthStencilView* m_depthStencilView = nullptr;
  /**
  * The resource of the depth stencil.
  */
  ID3D11Texture2D* m_depthStencilResource = nullptr;
};
}

