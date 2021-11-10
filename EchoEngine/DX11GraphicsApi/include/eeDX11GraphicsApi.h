/************************************************************************/
/**
 * @file eeGraphicsApir.h
 * @author Diego Castellanos
 * @date 15/10/21
 * @brief
 * The class in charge of every action involving graphics, like creating the
 * window or draw objects.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesDX11.h"
#include <eeGraficsApi.h>
#include "eeDX11Texture.h"
#include "eeDX11VertexShader.h"
#include "eeDX11PixelShader.h"
#include "eeDX11VertexBuffer.h"
#include "eeDX11IndexBuffer.h"
#include "eeDX11ConstantBuffer.h"

#pragma warning(push, 0)   
#include <d3d11.h>
#pragma warning(pop)   

namespace eeEngineSDK {
/**
 * @brief
 * The DX11 basics. Contains the device, device context and swap chain used
 * everywhere.
 */
struct DX11Basics
{
  /**
   * The device for all the api. Creates every DX11 data.
   */
  ID3D11Device* m_device = nullptr;
  /**
   * The device context for all the api. Updates every DX11 data.
   */
  ID3D11DeviceContext* m_deviceContext = nullptr;
  /**
   * The swap chain for all the api. Does render related things.
   */
  IDXGISwapChain* m_swapChain = nullptr;
};

/**
 * @brief
 * The class in charge of every action involving graphics, like creating the
 * window or draw objects.
 */
class EE_PLUGINDX11_EXPORT DX11GraphicsApi : public GraphicsApi
{
 public:
   /**
   * @brief
   * Default constructor
   */
  DX11GraphicsApi() = default;
  /**
  * @brief
  * Default destructor
  */
  ~DX11GraphicsApi();
  
  /**
  * @brief
  * Initializes the graphics api.
  *
  * @description
  * Initializes all the resources needed by the api.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  bool
  initialize() override;

  /**
  * @brief
  * Asks the api if it can still be running.
  *
  * @description
  * Returns true if certain parameters checks, depending on the api.
  *
  * @return
  * Weather it can still run or not.
  */
  bool
  appIsRunning() override;

  /**
  * @brief
  * Initializes the screen for the api.
  *
  * @description
  * Initializes the screen depending on the graphics api active.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  bool
  initializeScreen() override;

  /**
  * @brief
  * Clears the active screen.
  *
  * @description
  * Clears the active render target with the given color.
  * **TODO: NEEDS TO BE REFACTORED TO USE THE RENDER TARGETS AND DEPTH STENCILS**
  *
  * @param r
  * Red part of the color. From 0 to 1 inclusive.
  * @param g
  * Green part of the color. From 0 to 1 inclusive.
  * @param b
  * Blue part of the color. From 0 to 1 inclusive.
  */
  void
  clearScreen(float r, float g, float b) override;

  /**
  * @brief
  * Set the viewport's size.
  *
  * @description
  * Sets the dimensions of the viewport on the screen
  *
  * @param width
  * The width of the viewport.
  * @param height
  * The height of the viewport.
  */
  void
  setViewport(float width, float height) override;

  /**
  * @brief
  * Shows in screen.
  *
  * @description
  * Changes the back buffer to the front buffer to show it in the screen.
  */
  void
  present() override;





  /////////////////////////////////////////////////////////////////////////////
  /*                                                                         */
  /*                                Resources                                */
  /*                                                                         */
  /////////////////////////////////////////////////////////////////////////////

  /**
  * @brief
  * Gets the specific texture pointer.
  *
  * @description
  * Returns a pointer to a texture depending on the api.
  *
  * @return
  * The pointer to a texture depending on the api.
  */
  FORCEINLINE SPtr<Texture>
  getTexturePtr() const override { return std::make_shared<DX11Texture>(); }

  /**
  * @brief
  * Gets the specific vertex shader pointer.
  *
  * @description
  * Returns a pointer to a vertex shader depending on the api.
  *
  * @return
  * The pointer to a vertex shader depending on the api.
  */
  FORCEINLINE virtual SPtr<VertexShader>
  getVertexShaderPtr() const override { return std::make_shared<DX11VertexShader>(); }

  /**
  * @brief
  * Gets the specific pixel shader pointer.
  *
  * @description
  * Returns a pointer to a pixel shader depending on the api.
  *
  * @return
  * The pointer to a pixel shader depending on the api.
  */
  FORCEINLINE virtual SPtr<PixelShader>
  getPixelShaderPtr() const override { return std::make_shared<DX11PixelShader>(); }

  /**
  * @brief
  * Gets the specific vertex buffer pointer.
  *
  * @description
  * Returns a pointer to a vertex buffer depending on the api.
  *
  * @return
  * The pointer to a vertex buffer depending on the api.
  */
  FORCEINLINE virtual SPtr<VertexBuffer>
  getVertexBufferPtr() const override { return std::make_shared<DX11VertexBuffer>(); }

  /**
  * @brief
  * Gets the specific index buffer pointer.
  *
  * @description
  * Returns a pointer to a index buffer depending on the api.
  *
  * @return
  * The pointer to a index buffer depending on the api.
  */
  FORCEINLINE virtual SPtr<IndexBuffer>
  getIndexBufferPtr() const override { return std::make_shared<DX11IndexBuffer>(); }

  /**
  * @brief
  * Gets the specific constant buffer pointer.
  *
  * @description
  * Returns a pointer to a constant buffer depending on the api.
  *
  * @return
  * The pointer to a vertex constant depending on the api.
  */
  FORCEINLINE virtual SPtr<ConstantBuffer>
  getConstantBufferPtr() const override { return std::make_shared<DX11ConstantBuffer>(); }



  /**
  * @brief
  * Gets the specifics for the api.
  *
  * @description
  * Returns the specific variables needed for all the api.
  *
  * @return
  * A void pointer containing the specific data for the graphics api.
  */
  FORCEINLINE virtual const void*
  getBasics() const override { return reinterpret_cast<const void*>(&m_basics); }


 protected:
  /**
  * @brief
  * Does the draw call.
  *
  * @description
  * Makes the draw call for the specific api.
  *
  * @param indicesCount
  * The number of indices to be drawn.
  */
  virtual void
  drawIndexed(int32 /*indicesCount*/) const;

 private:
  /**
  * The screen information
  */
  void* m_win = nullptr;

  /**
  * The basics for DX11
  */
  DX11Basics m_basics;

  SPtr<RenderTarget> m_rtv;
  SPtr<DepthStencil> m_dsv;
};
}

