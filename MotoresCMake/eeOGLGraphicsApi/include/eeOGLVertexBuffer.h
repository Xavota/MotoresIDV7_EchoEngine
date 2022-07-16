/************************************************************************/
/**
 * @file eeOGLVertexBuffer.h
 * @author Diego Castellanos
 * @date 12/05/22
 * @brief
 * A buffer that tells the graphic memory the vertices to be drawn.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesOGL.h"
#include <eeVertexBuffer.h> 

namespace eeEngineSDK {
/**
 * @brief
 * A buffer that tells the graphic memory the vertices to be drawn.
 */
class EE_PLUGINOGL_EXPORT OGLVertexBuffer : public VertexBuffer
{
 public:
  /**
   * @brief
   * Default constructor
   */
  OGLVertexBuffer() = default;
  /**
   * @brief
   * Initializes its data.
   *
   * @description
   * Takes the data given and copies the number of bytes given.
   *
   * @param dataSize
   * The number of bytes the buffer will copy.
   * @param batchSize
   * The number of size of the data type stored.
   * @param data
   * The pointer to the bytes that will be copied.
   */
  OGLVertexBuffer(SIZE_T dataSize, uint32 batchSize, const Byte* data);
  /**
   * @brief
   * Default destructor
   */
  virtual
  ~OGLVertexBuffer();


  /**
   * @brief
   * Initializes its data.
   *
   * @description
   * Takes the data given and copies the number of bytes given.
   *
   * @param dataSize
   * The number of bytes the buffer will copy.
   * @param batchSize
   * The number of size of the data type stored.
   * @param data
   * The pointer to the bytes that will be copied.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  bool
  initData(SIZE_T dataSize, uint32 batchSize, const Byte* data) override;

  /**
   * @brief
   * Updates the data.
   *
   * @description
   * Overrides the data with the new data given.
   *
   * @param data
   * The pointer to the bytes that will be copied.
   */
  void
  updateData(const Byte* data) override;

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
   * Set to graphics api.
   *
   * @description
   * Sets the buffer for the graphic memory to use, only for override in graphics
   * api specializations.
   */
  void
  set() override;

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
  uint32 
  getResource() { return m_buffer; }

 private:
  /**
   * The OGL buffer.
   */
  uint32 m_buffer = 0;
  /**
   * The OGL Vertex Array Object.
   */
  uint32 m_vao = 0;
};
}
