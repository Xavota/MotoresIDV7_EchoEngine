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
#include "eeDX11RenderTarget.h"
#include "DX11DepthStencil.h"

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
  * Cleans the render targets given.
  *
  * @description
  * Cleans the render targets with the given color.
  *
  * @param rtvs
  * The render targets to clean.
  * @param rgba
  * The color to clean with in RGBA. From 0 to 1 inclusive.
  */
  void
  clearRenderTargets(Vector<SPtr<RenderTarget>> rtvs, float rgba[4]) override;

  /**
  * @brief
  * Clean the depth stencil.
  *
  * @description
  * Remove all the last data from the depth stencil.
  *
  * @param dsvs
  * The depth stencils to clean.
  */
  void
  cleanDepthStencils(Vector<SPtr<DepthStencil>> dsvs) override;

  /**
  * @brief
  * Sets the render targets given.
  *
  * @description
  * Sets the render targets with the depth stencil.
  *
  * @param rtvs
  * The render targets to set.
  * @param dsv
  * The depth stencil for the render targets.
  */
  void
  setRenderTargets(Vector<SPtr<RenderTarget>> rtvs,
                   SPtr<DepthStencil> dsv) override;

  /**
  * @brief
  * Sets the textures given.
  *
  * @description
  * Sets several textures for the graphics memory.
  *
  * @param textures
  * The vector of textures to set.
  * @param startSlot
  * The first index for the texture indices.
  */
  void
  setTextures(Vector<SPtr<Texture>> textures,
              uint32 startSlot) override;

  /**
  * @brief
  * Set viewports.
  *
  * @description
  * Sets the viewports for the screen.
  *
  * @param descs
  * The description for the different viewports. Also determines how many
  * viewports to set.
  */
  void
  setViewports(Vector<ViewportDesc> descs) override;

  /**
  * @brief
  * Set the topology.
  *
  * @description
  * Sets the topology for the render.
  *
  * @param topology
  * The topology to set.
  */
  void
  setPrimitiveTopology(PRIMITIVE_TOPOLOGY topology) override;

  /**
  * @brief
  * Shows in screen.
  *
  * @description
  * Changes the back buffer to the front buffer to show it in the screen.
  */
  void
  present() override;

  /**
  * @brief
  * Releases the data.
  *
  * @description
  * Deletes the memory of all data allocated.
  */
  void
  release() override;




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
  createTexturePtr() const override { return std::make_shared<DX11Texture>(); }

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
  createVertexShaderPtr() const override { return std::make_shared<DX11VertexShader>(); }

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
  createPixelShaderPtr() const override { return std::make_shared<DX11PixelShader>(); }

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
  createVertexBufferPtr() const override { return std::make_shared<DX11VertexBuffer>(); }

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
  createIndexBufferPtr() const override { return std::make_shared<DX11IndexBuffer>(); }

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
  createConstantBufferPtr() const override { return std::make_shared<DX11ConstantBuffer>(); }

  /**
  * @brief
  * Gets the specific render target pointer.
  *
  * @description
  * Returns a pointer to a render target depending on the api.
  *
  * @return
  * The pointer to a render target depending on the api.
  */
  FORCEINLINE virtual SPtr<RenderTarget>
  createRenderTragetPtr() const { return std::make_shared<DX11RenderTarget>(); }

  /**
  * @brief
  * Gets the specific depth stencil pointer.
  *
  * @description
  * Returns a pointer to a depth stencil depending on the api.
  *
  * @return
  * The pointer to a depth stencil depending on the api.
  */
  FORCEINLINE virtual SPtr<DepthStencil>
  createDepthStencilPtr() const { return std::make_shared<DX11DepthStencil>(); }



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
};
}

