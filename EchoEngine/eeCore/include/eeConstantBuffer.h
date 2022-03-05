/************************************************************************/
/**
 * @file eeConstantBuffer.h
 * @author Diego Castellanos
 * @date 13/10/21
 * @brief
 * A buffer for passing any information to the graphics memory.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eeBuffer.h"

namespace eeEngineSDK {
/**
 * @brief
 * A buffer for passing any information to the graphics memory.
 */
class ConstantBuffer : public Buffer
{
 public:
  /**
   * @brief
   * Default constructor
   */
  ConstantBuffer() = default;
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
  ConstantBuffer(SIZE_T dataSize, uint32 batchSize, const Byte* data)
  {
    initData(dataSize, batchSize, data);
  }
  /**
   * @brief
   * Default destructor
   */
  virtual
  ~ConstantBuffer();


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
  initData(SIZE_T dataSize, uint32 batchSize, const Byte* data) override
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
  release() override 
  {
    Buffer::release();
  };

  /**
   * @brief
   * Sets the buffer to the vertex shader.
   *
   * @description
   * Sets the buffer data to be used by the active vertex shader. Only for
   * graphics api overrides.
   *
   * @param index
   * The index in witch the buffer will be put.
   */
  virtual void
  setInVertex(uint32 /*index*/){}

  /**
   * @brief
   * Sets the buffer to the pixel shader.
   *
   * @description
   * Sets the buffer data to be used by the active pixel shader. Only for
   * graphics api overrides.
   *
   * @param index
   * The index in witch the buffer will be put.
   */
  virtual void
  setInPixel(uint32 /*index*/){}
};
}
