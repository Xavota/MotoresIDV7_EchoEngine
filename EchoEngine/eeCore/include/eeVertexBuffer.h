/************************************************************************/
/**
 * @file eeVertexBuffer.h
 * @author Diego Castellanos
 * @date 10/10/21
 * @brief
 * A buffer that tells the graphic memory the vertices to be drawn.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eeBuffer.h"

namespace eeEngineSDK {
/**
 * @brief
 * A buffer that tells the graphic memory the vertices to be drawn.
 */
class EE_CORE_EXPORT VertexBuffer : public Buffer
{
 public:
  /**
   * @brief
   * Default constructor
   */
  VertexBuffer() = default;
  /**
   * @brief
   * Default destructor
   */
  virtual 
  ~VertexBuffer() = default;


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
  virtual bool
  initData(uint32 dataSize, uint32 batchSize, const Byte* data) override
  {
    return Buffer::initData(dataSize, batchSize, data);
  }

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
  virtual void
  updateData(const Byte* data) override
  {
    Buffer::updateData(data);
  }

  /**
   * @brief
   * Releases the data.
   *
   * @description
   * Deletes the memory of all data allocated.
   */
  virtual void
  release() override {};

  /**
   * @brief
   * Set to graphics api.
   *
   * @description
   * Sets the buffer for the graphic memory to use, only for override in graphics
   * api specializations.
   */
  virtual void
  set() override {}
};
}
