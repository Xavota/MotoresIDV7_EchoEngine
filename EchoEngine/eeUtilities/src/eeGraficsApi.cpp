#include "eeGraficsApi.h"
#include "eeResourceManager.h"
#include "eeVertexShader.h"
#include "eePixelShader.h"
#include "eeConstantBuffer.h"
#include "eeObject.h"
#include "eeModel.h"
#include "eeMesh.h"

namespace eeEngineSDK {
bool GraphicsApi::initialize()
{
  return true;
}
void GraphicsApi::drawObject(SPtr<Object> obj)
{
  //m_basics.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);



  const Vector<Pair<SPtr<Mesh>, uint8>>& meshes = obj->getModel()->getMeshes();
  const Vector< SPtr<Texture>>& textures = obj->getModel()->getTextures();

  obj->getModelBuffer()->setInVertex(0u);

  for (const Pair<SPtr<Mesh>, uint8>& m : meshes)
  {
    m.first->set();

    GraphicsApi::instance().setTextures({textures[m.second]}, 0u);

    drawIndexed(m.first->getIndexCount());
  }  
}
void GraphicsApi::release()
{
}
}