/************************************************************************/
/**
 * @file eeDX11BlendState.h
 * @author Diego Castellanos
 * @date 22/11/21
 * @brief
 * The Blend state class.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesDX11.h"
#include <eeBlendState.h>
#pragma warning(push, 0)   
#include <d3d11.h>
#pragma warning(pop) 

namespace eeEngineSDK {
/**
 * @brief
 * The Blend state class.
 */
class DX11BlendState : public BlendState
{
 public:
  /**
   * @brief
   * Default constructor
   */
  DX11BlendState() = default;
  /**
   * @brief
   * Default destructor
   */
  ~DX11BlendState() = default;

  /**
   * @brief
   * Creates a blend state.
   *
   * @description
   * Creates a blend state using a descriptor.
   *
   * @param desc
   * The descriptor of the blend state.
   *
   * @return
   * True if it succeeded to create the state.
   */
  bool
  create(BlendDesc desc) override;

  /**
   * @brief
   * Set to graphics api.
   *
   * @description
   * Sets the rasterizer state for the graphic memory to use, only for override
   * in graphics api specializations.
   */
  void
  use(float blendFactor[4], uint32 sampleMask) override;

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
   * The buffer from DX11.
   */
  ID3D11BlendState* m_blendState = nullptr;
};
}