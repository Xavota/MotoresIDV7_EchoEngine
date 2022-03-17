/************************************************************************/
/**
 * @file eeDepthStencil.h
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
   * @param desc
   * The descriptor for the sampler state.
   */
  DX11SamplerState(SamplerStateDesc desc);
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
   * @param desc
   * The descriptor for the sampler state.
   *
   * @return
   * Whether it succeeded to create or not.
   */
  bool
  create(SamplerStateDesc desc) override;

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
