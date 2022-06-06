/************************************************************************/
/**
 * @file eeOGLDepthStencil.h
 * @author Diego Castellanos
 * @date 24/05/22
 * @brief
 * Sampler state, to describe how to read texture info.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesOGL.h"
#include <eeSamplerState.h>

namespace eeEngineSDK {
/**
 * @brief
 * Sampler state, to describe how to read texture info.
 */
class EE_PLUGINOGL_EXPORT OGLSamplerState : public SamplerState
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  OGLSamplerState() = default;
  /**
   * @brief
   * Creates a sampler stencil state.
   *
   * @description
   * Creates the sampler stencil state with a descriptor.
   *
   * @param filter
   * The filter for the sampler.
   * @param adressU
   * The address function in horizontal axis.
   * @param adressV
   * The address function in vertical axis.
   * @param adressW
   * The address function in W axis.
   */
  OGLSamplerState(eSAMPLER_FILTER::E filter,
              eTEXTURE_ADDRESS_MODE::E addressU = eTEXTURE_ADDRESS_MODE::kWrap,
              eTEXTURE_ADDRESS_MODE::E addressV = eTEXTURE_ADDRESS_MODE::kWrap,
              eTEXTURE_ADDRESS_MODE::E addressW = eTEXTURE_ADDRESS_MODE::kWrap);
  /**
   * @brief
   * Default destructor.
   */
  ~OGLSamplerState();

  /**
   * @brief
   * Creates a sampler stencil state.
   *
   * @description
   * Creates the sampler stencil state with a descriptor.
   *
   * @param filter
   * The filter for the sampler.
   * @param adressU
   * The address function in horizontal axis.
   * @param adressV
   * The address function in vertical axis.
   * @param adressW
   * The address function in W axis.
   *
   * @return
   * Whether it succeeded to create or not.
   */
  bool
  create(eSAMPLER_FILTER::E filter,
         eTEXTURE_ADDRESS_MODE::E addressU = eTEXTURE_ADDRESS_MODE::kWrap,
         eTEXTURE_ADDRESS_MODE::E addressV = eTEXTURE_ADDRESS_MODE::kWrap,
         eTEXTURE_ADDRESS_MODE::E addressW = eTEXTURE_ADDRESS_MODE::kWrap) override;

  /**
   * @brief
   * Set to graphics api.
   *
   * @description
   * Sets the sampler state for the graphic memory to use, only for override in
   * graphics api specializations.
   */
  void
  use() override;

  /**
   * @brief
   * Releases the data.
   *
   * @description
   * Deletes the memory of all data allocated.
   */
  void
  release() override;

 private:
  /**
   * Minification filter mode.
   */
  uint32 m_minFilter = 0;
  /**
   * Magnification filter mode.
   */
  uint32 m_magFilter = 0;
  /**
   * Wrapper mode horizontal.
   */
  uint32 m_addressU = 0;
  /**
   * Wrapper mode vertical.
   */
  uint32 m_addressV = 0;
  /**
   * Wrapper mode upward.
   */
  uint32 m_addressW = 0;
};
}