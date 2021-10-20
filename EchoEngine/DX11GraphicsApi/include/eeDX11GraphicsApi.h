#pragma once
#include "eePrerequisitesDX11.h"
#include <eeGraficsApi.h>
#include "eeDX11Texture.h"

#include <d3d11.h>

namespace eeEngineSDK {
class EE_PLUGINDX11_EXPORT DX11GraphicsApi : public GraphicsApi
{
 public:
  DX11GraphicsApi() = default;
  ~DX11GraphicsApi();

  bool
  initialize() override;

  bool
  appIsRunning() override;

  bool
  initializeScreen() override;

  void
  processEvents() override;

  void
  clearScreen(float r, float g, float b) override;

  void
  drawObject(SPtr<Object> obj) override;

  void
  present() override;





  ////////////////////////////////////////////////////
  /*
  *    Resources
  */
  ////////////////////////////////////////////////////

  FORCEINLINE SPtr<Texture>
  getTexturePtr()  override 
  { 
    return std::make_shared<DX11Texture>(); 
  }

 private:
  void* m_win = nullptr;

  ID3D11Device* m_device = nullptr;
  ID3D11DeviceContext* m_deviceContext = nullptr;
  IDXGISwapChain* m_swapChain = nullptr;

  ID3D11RenderTargetView* m_rtv;
};
}

