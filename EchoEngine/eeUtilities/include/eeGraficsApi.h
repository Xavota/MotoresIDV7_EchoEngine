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
#include "eeTexture.h"
#include "eeVertexShader.h"
#include "eePixelShader.h"
#include "eeVertexBuffer.h"
#include "eeIndexBuffer.h"
#include "eeConstantBuffer.h"
#include "eeRenderTarget.h"
#include "eeDepthStencil.h"

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
  ~GraphicsApi() = default;

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
  * Initializes the screen for the api.
  *
  * @description
  * Initializes the screen depending on the graphics api active.
  *
  * @return
  * Weather it succeed or failed to initialize.
  */
  virtual bool
  initializeScreen(){return true;}

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
  virtual void
  clearRenderTargets(Vector<SPtr<RenderTarget>> /*rtvs*/, float /*rgba*/[4]){};

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
  virtual void
  cleanDepthStencils(Vector<SPtr<DepthStencil>> /*dsvs*/) {};

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
  setRenderTargets(Vector<SPtr<RenderTarget>> /*rtvs*/,
                   SPtr<DepthStencil> /*dsv*/) {}

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
  setTextures(Vector<SPtr<Texture>> textures,
              uint32 startSlot) {}

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
  setViewports(Vector<ViewportDesc> descs) {}

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
  setPrimitiveTopology(PRIMITIVE_TOPOLOGY topology) {}

  /**
  * @brief
  * Draws the object.
  *
  * @description
  * Draws the given object.
  *
  * @param obj
  * The object to draw.
  */
  virtual void
  drawObject(SPtr<Object> obj);

  /**
  * @brief
  * Shows in screen.
  *
  * @description
  * Changes the back buffer to the front buffer to show it in the screen.
  */
  virtual void
  present(){}

  /**
  * @brief
  * Releases the data.
  *
  * @description
  * Deletes the memory of all data allocated.
  */
  virtual void
  release();





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
  createTexturePtr() const { return std::make_shared<Texture>(); }

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
  createVertexShaderPtr() const { return std::make_shared<VertexShader>(); }

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
  createPixelShaderPtr() const { return std::make_shared<PixelShader>(); }

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
  createVertexBufferPtr() const { return std::make_shared<VertexBuffer>(); }

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
  createIndexBufferPtr() const { return std::make_shared<IndexBuffer>(); }

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
  createConstantBufferPtr() const { return std::make_shared<ConstantBuffer>(); }

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
  createRenderTragetPtr() const { return std::make_shared<RenderTarget>(); }

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
  createDepthStencilPtr() const { return std::make_shared<DepthStencil>(); }



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
  drawIndexed(int32 /*indicesCount*/) const {}
};
}
