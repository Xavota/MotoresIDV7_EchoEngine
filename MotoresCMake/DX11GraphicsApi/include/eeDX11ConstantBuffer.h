/************************************************************************/
/**
 * @file eeDX11ConstantBuffer.h
 * @author Diego Castellanos
 * @date 27/10/21
 * @brief
 * A buffer for passing any information to the graphics memory.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesDX11.h"
#include <eeConstantBuffer.h>

namespace eeEngineSDK {
/**
 * @brief
 * A buffer for passing any information to the graphics memory.
 */
class EE_PLUGINDX11_EXPORT DX11ConstantBuffer : public ConstantBuffer
{
 public:
  /**
   * @brief
   * Default constructor
   */
  DX11ConstantBuffer() = default;
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
  DX11ConstantBuffer(SIZE_T dataSize, uint32 batchSize, const Byte* data);
  /**
   * @brief
   * Default destructor
   */
  virtual
  ~DX11ConstantBuffer();


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
  updateData(const Byte* data);

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
  ID3D11Buffer*
  getResource() { return m_buffer; }
  
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
   * Sets the buffer to the vertex shader.
   *
   * @description
   * Sets the buffer data to be used by the active vertex shader. Only for
   * graphics api overrides.
   *
   * @param index
   * The index in witch the buffer will be put.
   */
  void
  setInVertex(uint32 index) override;

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
  void
  setInPixel(uint32 index) override;


 private:
  /**
   * The buffer from DX11.
   */
  ID3D11Buffer* m_buffer = nullptr;
};
}

