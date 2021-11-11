#pragma once
#include "eePrerequisitesDX11.h"
#include <eeSamplerState.h>
#pragma warning(push, 0)   
#include <d3d11.h>
#pragma warning(pop)   

namespace eeEngineSDK{
class DX11SamplerState : public SamplerState
{
 public:
  DX11SamplerState() = default;
  ~DX11SamplerState();

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

  ID3D11SamplerState*
  getResource() { return m_sampler; }

 private:
  ID3D11SamplerState* m_sampler;
};
}
