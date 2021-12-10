/************************************************************************/
/**
 * @file eeDX11GraphicsApi.h
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
#include "eeDX11DepthStencil.h"
#include "eeDX11RasterizerState.h"

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
  initializeScreen(void* callback) override;

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
  * Unset the render targets and depth stencil.
  *
  * @description
  * Sets a nullptr render target and depth stencil.
  */
  void
  unsetRenderTargets() override;

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
  * Unset the textures.
  *
  * @description
  * Sets nullptr textures.
  *
  * @param textureCount
  * The number of textures to unset
  * @param startSlot
  * The first index for the texture indices.
  */
  void
  unsetTextures(uint32 textureCount, uint32 startSlot) override;

  /**
  * @brief
  * Sets the buffers given.
  *
  * @description
  * Sets several buffers for the vertex shader.
  *
  * @param buffers
  * The vector of buffers to set.
  * @param startSlot
  * The first index for the buffers indices.
  */
  void
  setVSConstantBuffers(Vector<SPtr<ConstantBuffer>> buffers,
                       uint32 startSlot) override;

  /**
  * @brief
  * Unset the buffers on the vertex buffer.
  *
  * @description
  * Sets nullptr buffers on the vertex buffer.
  *
  * @param buffersCount
  * The number of buffers to unset
  * @param startSlot
  * The first index for the buffers indices.
  */
  void
  unsetVSConstantBuffers(uint32 buffersCount, uint32 startSlot) override;

  /**
  * @brief
  * Sets the buffers given.
  *
  * @description
  * Sets several buffers for the pixel shader.
  *
  * @param buffers
  * The vector of buffers to set.
  * @param startSlot
  * The first index for the buffers indices.
  */
  void
  setPSConstantBuffers(Vector<SPtr<ConstantBuffer>> buffers,
                       uint32 startSlot) override;

  /**
  * @brief
  * Unset the buffers on the pixel buffer.
  *
  * @description
  * Sets nullptr buffers on the pixel buffer.
  *
  * @param buffersCount
  * The number of buffers to unset.
  * @param startSlot
  * The first index for the buffers indices.
  */
  void
  unsetPSConstantBuffers(uint32 buffersCount, uint32 startSlot) override;

  /**
  * @brief
  * Sets the vertex buffers given.
  *
  * @description
  * Sets several vertex buffers for the shaders.
  *
  * @param buffers
  * The vector of vertex buffers to set.
  * @param offsets
  * The vector of offsets for the buffers.
  * @param startSlot
  * The first index for the buffers indices.
  */
  void
  setVertexBuffers(Vector<SPtr<VertexBuffer>> buffers,
                   Vector<uint32> offsets,
                   uint32 startSlot) override;

  /**
  * @brief
  * Unset the vertex buffers on the shaders.
  *
  * @description
  * Sets nullptr vertex buffers on the shaders.
  *
  * @param buffersCount
  * The number of vertex buffers to unset.
  * @param startSlot
  * The first index for the vertex buffers indices.
  */
  void
  unsetVertexBuffers(uint32 buffersCount, uint32 startSlot) override;

  /**
  * @brief
  * Sets the index buffers given.
  *
  * @description
  * Sets several index buffers for the shaders.
  *
  * @param buffer
  * The index buffers to set.
  * @param offset
  * The offset for the starting point on the buffer.
  */
  void
  setIndexBuffer(SPtr<IndexBuffer> buffers,
                 uint32 offsets) override;

  /**
  * @brief
  * Unset the vertex buffers on the shaders.
  *
  * @description
  * Sets nullptr vertex buffers on the shaders.
  */
  void
  unsetIndexBuffer() override;

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
  setPrimitiveTopology(ePRIMITIVE_TOPOLOGY topology) override;

  /**
  * @brief
  * Shows in screen.
  *
  * @description
  * Changes the back buffer to the front buffer to show it in the screen.
  *
  * @param syncInterval
  * How often the screen will sync.
  * @param flags
  * Extra info flags.
  */
  void
  present(uint32 syncInterval, uint32 flags) override;

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
  createTexturePtr() const override
  {
    return MemoryManager::instance().newPtr<DX11Texture>();
  }

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
  createVertexShaderPtr() const override
  {
    return MemoryManager::instance().newPtr<DX11VertexShader>();
  }

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
  createPixelShaderPtr() const override
  {
    return MemoryManager::instance().newPtr<DX11PixelShader>();
  }

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
  createVertexBufferPtr() const override
  {
    return MemoryManager::instance().newPtr<DX11VertexBuffer>();
  }

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
  createIndexBufferPtr() const override 
  {
    return MemoryManager::instance().newPtr<DX11IndexBuffer>();
  }

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
  createConstantBufferPtr() const override
  {
    return MemoryManager::instance().newPtr<DX11ConstantBuffer>();
  }

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
  createRenderTragetPtr() const override
  {
    return MemoryManager::instance().newPtr<DX11RenderTarget>();
  }

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
  createDepthStencilPtr() const override
  {
    return MemoryManager::instance().newPtr<DX11DepthStencil>();
  }

  /**
  * @brief
  * Gets the specific rasterizer state pointer.
  *
  * @description
  * Returns a pointer to a rasterizer state depending on the api.
  *
  * @return
  * The pointer to a rasterizer state depending on the api.
  */
  FORCEINLINE virtual SPtr<RasterizerState>
  createRasterizerStatePtr() const override
  {
    return MemoryManager::instance().newPtr<DX11RasterizerState>();
  }



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

  /**
  * @brief
  * Gets the window for the api.
  *
  * @description
  * Returns the window that the api is using.
  *
  * @return
  * A void pointer containing the window that the api is using.
  */
  FORCEINLINE virtual void*
  getWindow() const override { return m_win; }


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

