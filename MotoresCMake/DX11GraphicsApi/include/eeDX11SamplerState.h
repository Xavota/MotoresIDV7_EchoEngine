/************************************************************************/
/**
 * @file eeDX11DepthStencil.h
 * @author Diego Castellanos
 * @date 10/10/21
 * @brief
 * Sampler state, to describe how to read texture info.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesDX11.h"
#include <eeSamplerState.h>

namespace eeEngineSDK{
/**
 * @brief
 * Sampler state, to describe how to read texture info.
 */
class EE_PLUGINDX11_EXPORT DX11SamplerState : public SamplerState
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  DX11SamplerState() = default;
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
  DX11SamplerState(eSAMPLER_FILTER::E filter,
              eTEXTURE_ADDRESS_MODE::E addressU = eTEXTURE_ADDRESS_MODE::kWrap,
              eTEXTURE_ADDRESS_MODE::E addressV = eTEXTURE_ADDRESS_MODE::kWrap,
              eTEXTURE_ADDRESS_MODE::E addressW = eTEXTURE_ADDRESS_MODE::kWrap);
  /**
   * @brief
   * Default destructor.
   */
  ~DX11SamplerState();

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
  ID3D11SamplerState*
  getResource() { return m_sampler; }

 private:
  /**
   * The sampler state resource data.
   */
  ID3D11SamplerState* m_sampler;
};
}
