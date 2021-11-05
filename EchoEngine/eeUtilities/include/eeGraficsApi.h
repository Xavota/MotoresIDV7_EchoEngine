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
  clearScreen(float /*r*/, float /*g*/, float /*b*/){};

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
  virtual void
  setViewport(float width, float height) {}

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
  getTexturePtr() const { return std::make_shared<Texture>(); }

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
  getVertexShaderPtr() const { return std::make_shared<VertexShader>(); }

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
  getPixelShaderPtr() const { return std::make_shared<PixelShader>(); }

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
  getVertexBufferPtr() const { return std::make_shared<VertexBuffer>(); }

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
  getIndexBufferPtr() const { return std::make_shared<IndexBuffer>(); }

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
  getConstantBufferPtr() const { return std::make_shared<ConstantBuffer>(); }



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
