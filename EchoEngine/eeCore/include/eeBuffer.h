/************************************************************************/
/**
 * @file eeBuffer.h
 * @author Diego Castellanos
 * @date 07/10/21
 * @brief
 * The base buffer class. A buffer contains raw data to be interpreted in any
 * way.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
/**
 * @brief
 * The base buffer class. A buffer contains raw data to be interpreted in any
 * way.
 */
class EE_CORE_EXPORT Buffer
{
 public:
  /**
   * @brief
   * Default constructor
   */
  Buffer() = default;
  /**
   * @brief
   * Default destructor
   */
  virtual
  ~Buffer() = default;

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
  initData(uint32 dataSize, uint32 batchSize, const Byte* data);

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
  updateData(const Byte* data);

  /**
   * @brief
   * Releases the data.
   *
   * @description
   * Deletes the memory of all data allocated.
   */
  virtual void 
  release(){};

  /**
   * @brief
   * Getter for the data size.
   *
   * @description
   * Returns the number of bytes stored in the buffer.
   *
   * @return
   * The number of bytes stored in the buffer..
   */
  FORCEINLINE virtual uint32
  getDataSize() const
  {
    return static_cast<uint32>(m_data.size());
  }
  /**
   * @brief
   * Getter for the data.
   *
   * @description
   * Returns a reference to the data.
   *
   * @return
   * The reference to the data.
   */
  FORCEINLINE virtual const Vector<Byte>&
  getData() const
  {
    return m_data;
  }
  /**
   * @brief
   * Getter for the batch size.
   *
   * @description
   * Returns the size of the data type.
   *
   * @return
   * The size of the data type.
   */
  FORCEINLINE virtual uint32
  getBatchSize() const
  {
    return m_batchSize;
  }

  /**
   * @brief
   * Set to graphics api.
   *
   * @description
   * Sets the buffer for the graphic memory to use, only for override in graphics
   * api specializations.
   */
  virtual void
  set(){}

 protected:
  /**
   * The data stored.
   */
  Vector<Byte> m_data;
  /**
   * The size of the data type.
   */
  uint32 m_batchSize = 0;
};
}
  