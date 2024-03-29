/************************************************************************/
/**
 * @file eeOGLGraphicsApi.h
 * @author Diego Castellanos
 * @date 11/05/22
 * @brief
 * The class in charge of every action involving graphics, like creating the
 * window or draw objects.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesOGL.h"
#include <eeGraficsApi.h>
#include "eeOGLTexture.h"
#include "eeOGLVertexShader.h"
#include "eeOGLPixelShader.h"
#include "eeOGLVertexBuffer.h"
#include "eeOGLIndexBuffer.h"
//#include "eeOGLConstantBuffer.h"
//#include "eeOGLRasterizerState.h"
#include "eeOGLSamplerState.h"
#include "eeOGLWindow.h"

namespace eeEngineSDK {
/**
 * @brief
 * The OGL basics. Contains the device, device context and swap chain used
 * everywhere.
 */
struct OGLBasics
{
  /**
   * The device for all the api. Creates every OGL data.
   */
  /**
   * The device context for all the api. Updates every OGL data.
   */
  /**
   * The swap chain for all the api. Does render related things.
   */
};

/**
 * @brief
 * The class in charge of every action involving graphics, like creating the
 * window or draw objects.
 */
class EE_PLUGINOGL_EXPORT OGLGraphicsApi : public GraphicsApi
{
 public:
  /**
   * @brief
   * Default constructor
   */
  OGLGraphicsApi() = default;
  /**
   * @brief
   * Default destructor
   */
  ~OGLGraphicsApi();
  
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
   * Initializes the basics for the api.
   *
   * @description
   * Initializes the basics depending on the graphics api active.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  bool
  initializeBasics() override;

  /**
   * @brief
   * Initializes the screen for the api.
   *
   * @description
   * Initializes the screen depending on the graphics api active.
   *
   * @param callback
   * The function callback for the window events.
   * @param width
   * The width of the window.
   * @param height
   * The height of the window.
   * @param displayName
   * The window display name.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  bool
  initializeScreen(void* callback,
                   uint32 witdh,
                   uint32 height,
                   const String& displayName) override;

  /**
   * @brief
   * Processes the events given by the system.
   *
   * @description
   * Gets all the events given by the systems and interprets them to something
   * useful.
   */
  void
  processEvents() override;

  /**
   * @brief
   * Clears the active screen.
   *
   * @description
   * Clears the active render target with the given color.
   *
   * @param rtvs
   * The list of render targets to clean.
   * @param screenColor
   * The color for cleaning the render target.
   */
  void
  clearRenderTargets(const Vector<WPtr<Texture>>&rtvs, Color screenColor) override;

  /**
   * @brief
   * Clean the depth stencil.
   *
   * @description
   * Remove all the last data from the depth stencil.
   *
   * @param dsvs
   * The list of depth stencils to clean.
   */
  void
  cleanDepthStencils(const Vector<WPtr<Texture>>& dsvs) override;

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
  setRenderTargets(const Vector<WPtr<Texture>>& rtvs,
                   WPtr<Texture> dsv) override;

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
  setTextures(const Vector<WPtr<Texture>>& textures,
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
  setVSConstantBuffers(const Vector<WPtr<ConstantBuffer>>& /*buffers*/,
                       uint32 /*startSlot*/) override {}

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
  setPSConstantBuffers(const Vector<WPtr<ConstantBuffer>>& /*buffers*/,
                       uint32 /*startSlot*/) override {};

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
  setVertexBuffers(const Vector<WPtr<VertexBuffer>>& buffers,
                   const Vector<uint32>& offsets,
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
  setIndexBuffer(WPtr<IndexBuffer> /*buffers*/,
                 uint32 /*offsets*/) override {};

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
  setViewports(const Vector<ViewportDesc>& descs) override;

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
  setPrimitiveTopology(ePRIMITIVE_TOPOLOGY::E topology) override;

  /**
   * @brief
   * Set shader programs.
   *
   * @description
   * Sets the shaders given to the GPU.
   *
   * @param vertexShader
   * The vertex shader to set.
   * @param hullShader
   * The hull shader to set.
   * @param domainShader
   * The domain shader to set.
   * @param pixelShader
   * The pixel shader to set.
   */
  void
  setShaderPrograms(WPtr<VertexShader> vertexShader,
                    WPtr<HullShader> hullShader,
                    WPtr<DomainShader> domainShader,
                    WPtr<PixelShader> pixelShader) override;

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
    return MemoryManager::instance().newPtr<OGLTexture>();
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
  FORCEINLINE SPtr<VertexShader>
  createVertexShaderPtr() const override
  {
    return MemoryManager::instance().newPtr<OGLVertexShader>();
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
  FORCEINLINE SPtr<PixelShader>
  createPixelShaderPtr() const override
  {
    return MemoryManager::instance().newPtr<OGLPixelShader>();
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
  FORCEINLINE SPtr<VertexBuffer>
  createVertexBufferPtr() const override
  {
    return MemoryManager::instance().newPtr<OGLVertexBuffer>();
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
  FORCEINLINE SPtr<IndexBuffer>
  createIndexBufferPtr() const override 
  {
    return MemoryManager::instance().newPtr<OGLIndexBuffer>();
  }
  
  ///**
  // * @brief
  // * Gets the specific constant buffer pointer.
  // *
  // * @description
  // * Returns a pointer to a constant buffer depending on the api.
  // *
  // * @return
  // * The pointer to a vertex constant depending on the api.
  // */
  //FORCEINLINE SPtr<ConstantBuffer>
  //createConstantBufferPtr() const override
  //{
  //  return MemoryManager::instance().newPtr<OGLConstantBuffer>();
  //}
  //
  ///**
  // * @brief
  // * Gets the specific rasterizer state pointer.
  // *
  // * @description
  // * Returns a pointer to a rasterizer state depending on the api.
  // *
  // * @return
  // * The pointer to a rasterizer state depending on the api.
  // */
  //FORCEINLINE SPtr<RasterizerState>
  //createRasterizerStatePtr() const override
  //{
  //  return MemoryManager::instance().newPtr<OGLRasterizerState>();
  //}
  //
  /**
   * @brief
   * Gets the specific sampler state pointer.
   *
   * @description
   * Returns a pointer to a sampler state depending on the api.
   *
   * @return
   * The pointer to a sampler state depending on the api.
   */
  FORCEINLINE SPtr<SamplerState>
  createSamplerStatePtr() const override
  {
    return MemoryManager::instance().newPtr<OGLSamplerState>();
  }

  /**
   * @brief
   * Gets the specific window pointer.
   *
   * @description
   * Returns a pointer to a window depending on the api.
   *
   * @return
   * The pointer to a window depending on the api.
   */
  FORCEINLINE SPtr<Window>
  createWindowPtr() const override
  {
    return MemoryManager::instance().newPtr<OGLWindow>();
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
  FORCEINLINE const void*
  getBasics() const override { return reinterpret_cast<const void*>(&m_basics); }
  
  /**
   * @brief
   * Resize the window for the api.
   *
   * @description
   * Resize the window and everything involving.
   *
   * @param newSize
   * The new size for the window.
   */
  void
  resizeWindow(Point2D newSize) override;

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
  void
  drawIndexed(uint32 indicesCount) const override;

 private:
  ///**
  // * The screen information
  // */
  //void* m_win = nullptr;

  /**
   * The basics for OGL
   */
  OGLBasics m_basics;
};
}

