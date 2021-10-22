#pragma once
#include "eePrerequisitesDX11.h"
#include <eeGraficsApi.h>
#include "eeDX11Texture.h"
#include "eeDX11Object.h"
#include "eeDX11Model.h"
#include "eeDX11Mesh.h"
#include "eeDX11VertexShader.h"
#include "eeDX11PixelShader.h"

#include <d3d11.h>

namespace eeEngineSDK {
struct DX11Basics
{
  ID3D11Device* m_device = nullptr;
  ID3D11DeviceContext* m_deviceContext = nullptr;
  IDXGISwapChain* m_swapChain = nullptr;
};

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
  setViewport(float width, float height);

  void
  drawObject(SPtr<Object> obj) override;

  void
  present() override;





  /////////////////////////////////////////////////////////////////////////////
  /*                                                                         */
  /*                                Resources                                */
  /*                                                                         */
  /////////////////////////////////////////////////////////////////////////////

  FORCEINLINE SPtr<Texture>
  getTexturePtr() override { return std::make_shared<DX11Texture>(); }

  FORCEINLINE virtual SPtr<Mesh>
  getMeshPtr() { return std::make_shared<DX11Mesh>(); }

  FORCEINLINE virtual SPtr<Model>
  getModelPtr() { return std::make_shared<DX11Model>(); }

  FORCEINLINE virtual SPtr<Object>
  getObjectPtr() { return std::make_shared<DX11Object>(); }

  FORCEINLINE virtual SPtr<VertexShader>
  getVertexShaderPtr() { return std::make_shared<DX11VertexShader>(); }

  FORCEINLINE virtual SPtr<PixelShader>
  getPixelShaderPtr() { return std::make_shared<DX11PixelShader>(); }

  FORCEINLINE virtual void*
  getBasics() { return reinterpret_cast<void*>(&m_basics); }

 private:
  void* m_win = nullptr;

  DX11Basics m_basics;
  ID3D11RenderTargetView* m_rtv;
};
}

