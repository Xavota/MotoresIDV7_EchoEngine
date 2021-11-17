#pragma once
#include "eePrerequisitesDX11.h"
#include <eeBlendState.h>
#pragma warning(push, 0)   
#include <d3d11.h>
#pragma warning(pop) 

namespace eeEngineSDK {
class DX11BlendState : public BlendState
{
 public:
  DX11BlendState() = default;
  ~DX11BlendState() = default;

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
  ID3D11BlendState* m_blendState = nullptr;
};
}