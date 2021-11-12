#pragma once
#include "eePrerequisitesDX11.h"
#include <eeRenderTarget.h>
#pragma warning(push, 0)   
#include <d3d11.h>
#pragma warning(pop)  


namespace eeEngineSDK {
class DX11RenderTarget : public RenderTarget
{
 public:
  DX11RenderTarget() = default;
  ~DX11RenderTarget();

  bool
  createAsBackBuffer() override;
  bool
  createAsIOTexture() override;

  const SPtr<Texture>
  getAsTexture() const override;


  void
  set(SPtr<DepthStencil> stencil) override;
  void
  clean(float r, float g, float b, float a) override;

  ID3D11RenderTargetView*
  getResource() { return m_renderTarget; }

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
  * The dx11 render target.
  */
  ID3D11RenderTargetView* m_renderTarget = nullptr;
};
}
