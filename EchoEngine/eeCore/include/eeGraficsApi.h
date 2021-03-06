/************************************************************************/
/**
 * @file eeGraphicsApir.h
 * @author Diego Castellanos
 * @date 01/10/21
 * @brief
 * The class in charge of every action involving graphics, like creating the
 * window or draw objects.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeModule.h>
#include <eeMemoryManager.h>

#include <eeColor.h>

#include "eeWindow.h"

#include "eeTexture.h"
#include "eeVertexShader.h"
#include "eePixelShader.h"
#include "eeHullShader.h"
#include "eeDomainShader.h"
#include "eeVertexBuffer.h"
#include "eeIndexBuffer.h"
#include "eeConstantBuffer.h"
#include "eeRasterizerState.h"


namespace eeEngineSDK {
/**
 * @brief
 * The class in charge of every action involving graphics, like creating the 
 * window or draw objects.
 */
class EE_CORE_EXPORT GraphicsApi : public Module<GraphicsApi>
{
 public:
  /**
   * @brief
   * Default constructor
   */
  GraphicsApi() = default;
  /**
   * @brief
   * Default destructor
   */
  virtual
  ~GraphicsApi();

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
  virtual bool
  initialize();

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
  virtual bool
  appIsRunning(){return true;}

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
  virtual bool
  initializeBasics() { return false; }

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
  virtual bool
  initializeScreen(void* callback,
                   uint32 witdh,
                   uint32 height,
                   const String& displayName);

  /**
   * @brief
   * Processes the events given by the system.
   *
   * @description
   * Gets all the events given by the systems and interprets them to something
   * useful.
   */
  virtual void
  processEvents() {};

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
  virtual void
  clearRenderTargets(Vector<SPtr<Texture>> rtvs, Color /*screenColor*/) {};

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
  virtual void
  cleanDepthStencils(Vector<SPtr<Texture>> /*dsvs*/) {};

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
  virtual void
  setRenderTargets(Vector<SPtr<Texture>> /*rtvs*/,
                   SPtr<Texture> /*dsv*/) {}

  /**
   * @brief
   * Unset the render targets and depth stencil.
   *
   * @description
   * Sets a nullptr render target and depth stencil.
   */
  virtual void
  unsetRenderTargets() {}

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
  virtual void
  setTextures(Vector<SPtr<Texture>> /*textures*/,
              uint32 /*startSlot*/) {}

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
  virtual void
  unsetTextures(uint32 /*textureCount*/, uint32 /*startSlot*/) {}

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
  virtual void
  setVSConstantBuffers(Vector<SPtr<ConstantBuffer>> /*buffers*/,
                       uint32 /*startSlot*/) {}

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
  virtual void
  unsetVSConstantBuffers(uint32 /*buffersCount*/, uint32 /*startSlot*/) {}

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
  virtual void
  setPSConstantBuffers(Vector<SPtr<ConstantBuffer>> /*buffers*/,
                       uint32 /*startSlot*/) {}

  /**
   * @brief
   * Unset the buffers on the pixel shader.
   *
   * @description
   * Sets nullptr buffers on the pixel shader.
   *
   * @param buffersCount
   * The number of buffers to unset.
   * @param startSlot
   * The first index for the buffers indices.
   */
  virtual void
  unsetPSConstantBuffers(uint32 /*buffersCount*/, uint32 /*startSlot*/) {}

  /**
   * @brief
   * Sets the buffers given.
   *
   * @description
   * Sets several buffers for the hull shader.
   *
   * @param buffers
   * The vector of buffers to set.
   * @param startSlot
   * The first index for the buffers indices.
   */
  virtual void
  setHSConstantBuffers(Vector<SPtr<ConstantBuffer>> /*buffers*/,
                       uint32 /*startSlot*/) {}

  /**
   * @brief
   * Unset the buffers on the hull shader.
   *
   * @description
   * Sets nullptr buffers on the hull shader.
   *
   * @param buffersCount
   * The number of buffers to unset.
   * @param startSlot
   * The first index for the buffers indices.
   */
  virtual void
  unsetHSConstantBuffers(uint32 /*buffersCount*/, uint32 /*startSlot*/) {}

  /**
   * @brief
   * Sets the buffers given.
   *
   * @description
   * Sets several buffers for the domain shader.
   *
   * @param buffers
   * The vector of buffers to set.
   * @param startSlot
   * The first index for the buffers indices.
   */
  virtual void
  setDSConstantBuffers(Vector<SPtr<ConstantBuffer>> /*buffers*/,
                       uint32 /*startSlot*/) {}

  /**
   * @brief
   * Unset the buffers on the domain shader.
   *
   * @description
   * Sets nullptr buffers on the domain shader.
   *
   * @param buffersCount
   * The number of buffers to unset.
   * @param startSlot
   * The first index for the buffers indices.
   */
  virtual void
  unsetDSConstantBuffers(uint32 /*buffersCount*/, uint32 /*startSlot*/) {}

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
   * The vector of off buffers to set.
   * @param startSlot
   * The first index for the buffers indices.
   */
  virtual void
  setVertexBuffers(Vector<SPtr<VertexBuffer>> /*buffers*/,
                   Vector<uint32> /*offsets*/,
                   uint32 /*startSlot*/) {}

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
  virtual void
  unsetVertexBuffers(uint32 /*buffersCount*/, uint32 /*startSlot*/) {}

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
  virtual void
  setIndexBuffer(SPtr<IndexBuffer> /*buffers*/,
                 uint32 /*offsets*/) {}

  /**
   * @brief
   * Unset the vertex buffers on the shaders.
   *
   * @description
   * Sets nullptr vertex buffers on the shaders.
   */
  virtual void
  unsetIndexBuffer() {}

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
  virtual void
  setViewports(Vector<ViewportDesc> /*descs*/) {}

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
  virtual void
  setPrimitiveTopology(ePRIMITIVE_TOPOLOGY::E /*topology*/) {}

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
  virtual void
  setShaderPrograms(SPtr<VertexShader> vertexShader,
                    SPtr<HullShader> hullShader,
                    SPtr<DomainShader> domainShader,
                    SPtr<PixelShader> pixelShader) {}

  /**
   * @brief
   * Draws on a Screen Align Quad object.
   *
   * @description
   * Draws on a Screen Align Quad object.
   */
  virtual void
  drawOnSAQ();

  /**
   * @brief
   * Draws a mesh.
   *
   * @description
   * Draws the given mesh.
   *
   * @param meshToDraw
   * The mesh to draw.
   */
  virtual void
  drawMesh(const Mesh& meshToDraw);
  /**
   * @brief
   * Draws a mesh.
   *
   * @description
   * Draws the given mesh as control points.
   *
   * @param meshToDraw
   * The mesh to draw.
   */
  virtual void
  drawMeshControlPoints(const Mesh& meshToDraw);
  /**
   * @brief
   * Draws a mesh.
   *
   * @description
   * Draws the given mesh.
   *
   * @param meshToDraw
   * The mesh to draw.
   */
  virtual void
  drawMesh(const BoneMesh& meshToDraw);

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
  virtual void
  present(uint32 /*syncInterval*/, uint32 /*flags*/){}

  /**
   * @brief
   * Releases the data.
   *
   * @description
   * Deletes the memory of all data allocated.
   */
  virtual void
  release() {};

  /**
   * @brief
   * Set function callback for imgui impl.
   *
   * @description
   * Set function callback for imgui implementation.
   * //TODO: THIS SHOULDN'T BE HERE, IT'S TEMPORARY
   *
   * @param func
   * Function callback for imgui.
   */
  //virtual void
  //setImguiCallback()


  ////////////////////////////////////////////////////
  /*
  *    Resources
  */
  ////////////////////////////////////////////////////

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
  FORCEINLINE virtual SPtr<Texture>
  createTexturePtr() const
  {
    return MemoryManager::instance().newPtr<Texture>();
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
  createVertexShaderPtr() const
  {
    return MemoryManager::instance().newPtr<VertexShader>();
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
  createPixelShaderPtr() const
  {
    return MemoryManager::instance().newPtr<PixelShader>();
  }

  /**
   * @brief
   * Gets the specific hull shader pointer.
   *
   * @description
   * Returns a pointer to a hull shader depending on the api.
   *
   * @return
   * The pointer to a hull shader depending on the api.
   */
  FORCEINLINE virtual SPtr<HullShader>
  createHullShaderPtr() const
  {
    return MemoryManager::instance().newPtr<HullShader>();
  }

  /**
   * @brief
   * Gets the specific hull shader pointer.
   *
   * @description
   * Returns a pointer to a hull shader depending on the api.
   *
   * @return
   * The pointer to a hull shader depending on the api.
   */
  FORCEINLINE virtual SPtr<DomainShader>
  createDomainShaderPtr() const
  {
    return MemoryManager::instance().newPtr<DomainShader>();
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
  createVertexBufferPtr() const
  {
    return MemoryManager::instance().newPtr<VertexBuffer>();
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
  createIndexBufferPtr() const
  {
    return MemoryManager::instance().newPtr<IndexBuffer>();
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
  createConstantBufferPtr() const
  {
    return MemoryManager::instance().newPtr<ConstantBuffer>();
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
  createRasterizerStatePtr() const
  {
    return MemoryManager::instance().newPtr<RasterizerState>();
  }

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
  virtual SPtr<SamplerState>
  createSamplerStatePtr() const
  {
    return MemoryManager::instance().newPtr<SamplerState>();
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
  FORCEINLINE virtual SPtr<Window>
  createWindowPtr() const
  {
    return MemoryManager::instance().newPtr<Window>();
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
  getBasics() const { return nullptr; }
  
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
  virtual void
  resizeWindow(Point2D newSize);

  /**
   * @brief
   * Returns the main window of the api.
   *
   * @description
   * Returns the main window of the api.
   *
   * @return
   * The main window of the api.
   */
  SPtr<Window>
  getMainWindow() { return m_mainWindow; }

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
  drawIndexed(uint32 /*indicesCount*/) const {}
  /**
   * @brief
   * Does the draw call.
   *
   * @description
   * Makes the draw call for the specific api.
   *
   * @param verticesCount
   * The number of vertices to be drawn.
   */
  virtual void
  drawNoIndexed(uint32 /*verticesCount*/) const {};



  /**
   * The main window.
   */
  SPtr<Window> m_mainWindow;
};
}
