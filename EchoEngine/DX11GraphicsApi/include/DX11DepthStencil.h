#pragma once
#include "eePrerequisitesDX11.h"
#include <eeDepthStencil.h>
#pragma warning(push, 0)   
#include <d3d11.h>
#pragma warning(pop)  


namespace eeEngineSDK {
  class DX11DepthStencil : public DepthStencil
  {
  public:
    DX11DepthStencil() = default;
    ~DX11DepthStencil();

    bool
    create(int32 width, int32 height) override;

    void
    clean() override;

    /**
    * @brief
    * Releases the data.
    *
    * @description
    * Deletes the memory of all data allocated.
    */
    void
    release() override;

    ID3D11DepthStencilView*
    getResource();

  private:
    /**
    * The depth stencil for the back buffer **TODO: HARCODED**
    */
    ID3D11DepthStencilView* m_depthStencilView = nullptr;
    ID3D11Texture2D* m_depthStencilResource = nullptr;
  };
}

