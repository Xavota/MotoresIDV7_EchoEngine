#pragma once
#include "eePrerequisitesDX11.h"
#include <eeDepthStencilState.h>
#pragma warning(push, 0)   
#include <d3d11.h>
#pragma warning(pop) 

namespace eeEngineSDK{
class DX11DepthStencilState : public DepthStencilState
{
public:
  DX11DepthStencilState() = default;
  ~DX11DepthStencilState() = default;

  bool
  create(DepthStencilDesc desc) override;

  /**
  * @brief
  * Set to graphics api.
  *
  * @description
  * Sets the rasterizer state for the graphic memory to use, only for override
  * in graphics api specializations.
  */
  void
  use(uint32 stencilRef) override;

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
  ID3D11DepthStencilState* m_depthStencil = nullptr;
};
}