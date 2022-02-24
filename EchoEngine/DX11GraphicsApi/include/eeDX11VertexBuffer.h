/************************************************************************/
/**
 * @file eeVertexBuffer.h
 * @author Diego Castellanos
 * @date 24/10/21
 * @brief
 * A buffer that tells the graphic memory the vertices to be drawn.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesDX11.h"
#include <eeVertexBuffer.h>
#pragma warning(push, 0)   
#include <d3d11.h>
#pragma warning(pop)   

namespace eeEngineSDK {
/**
 * @brief
 * A buffer that tells the graphic memory the vertices to be drawn.
 */
class DX11VertexBuffer : public VertexBuffer
{
 public:
  /**
   * @brief
   * Default constructor
   */
  DX11VertexBuffer() = default;
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
  DX11VertexBuffer(SIZE_T dataSize, uint32 batchSize, const Byte* data);
  /**
   * @brief
   * Default destructor
   */
  virtual
  ~DX11VertexBuffer() = default;


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
  ID3D11Buffer*
  getResource() { return m_buffer; }

 private:
  /**
   * The DX11 buffer.
   */
  ID3D11Buffer* m_buffer = nullptr;
};
}
