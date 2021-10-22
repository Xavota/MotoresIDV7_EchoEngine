#pragma once
#include <d3d11.h>
#include <eeMesh.h>

namespace eeEngineSDK {
class DX11Mesh : public Mesh
{
 public:
  DX11Mesh() = default;
  ~DX11Mesh() = default;

  bool
  constructBuffers() override;

  ID3D11Buffer*
  getVertexBuffer();
  ID3D11Buffer*
  getIndexBuffer();

private:
  ID3D11Buffer* m_vertexBuffer;
  ID3D11Buffer* m_indexBuffer;
};
}
