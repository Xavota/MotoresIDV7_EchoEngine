#pragma once
#include "eePrerequisitesDX11.h"
#include <eeRasterizerState.h>
#pragma warning(push, 0)   
#include <d3d11.h>
#pragma warning(pop)   

namespace eeEngineSDK{
class DX11RasterizerState : public RasterizerState
{
 public:
  DX11RasterizerState() = default;
  ~DX11RasterizerState() = default;

  bool
  create(RasteraizerDesc desc) override;

  /**
  * @brief
  * Set to graphics api.
  *
  * @description
  * Sets the rasterizer state for the graphic memory to use, only for override
  * in graphics api specializations.
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
  ID3D11RasterizerState* m_rasterizer = nullptr;
};
}
