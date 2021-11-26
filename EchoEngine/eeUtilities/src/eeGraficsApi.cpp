#include "eeGraficsApi.h"
#include "eeResourceManager.h"
#include "eeVertexShader.h"
#include "eePixelShader.h"
#include "eeConstantBuffer.h"
#include "eeObject.h"
#include "eeModel.h"
#include "eeMesh.h"
#include "eeCTransform.h"
#include "eeCModel.h"
#include "eeActor.h"

namespace eeEngineSDK {
bool
GraphicsApi::initialize()
{
  return true;
}
void
GraphicsApi::drawObject(SPtr<Object> obj)
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


    GraphicsApi::instance().unsetVertexBuffers(1u, 0u);
  }  
}
void
GraphicsApi::drawObject(Actor* act)
{
  SPtr<CTransform> transform = act->getComponent<CTransform>();

  if (!transform)
    return;

  SPtr<CModel> model = act->getComponent<CModel>();

  const Vector<Pair<SPtr<Mesh>, uint8>>& meshes = model->getModel()->getMeshes();
  const Vector< SPtr<Texture>>& textures = model->getModel()->getTextures();

  transform->getModelBuffer()->setInVertex(0u);

  for (const Pair<SPtr<Mesh>, uint8>& m : meshes)
  {
    m.first->set();

    GraphicsApi::instance().setTextures({ textures[m.second] }, 0u);

    drawIndexed(m.first->getIndexCount());


    GraphicsApi::instance().unsetVertexBuffers(1u, 0u);
  }
}
void
GraphicsApi::release()
{
}
void
GraphicsApi::addActorToRenderFrame(Actor* actor)
{
  m_renderActors.push_back(actor);
}
Vector<Actor*>
GraphicsApi::getRenderFrameActors()
{
  return m_renderActors;
}
void
GraphicsApi::clearRenderFrameActors()
{
  m_renderActors.clear();
}
void
GraphicsApi::addActiveCamera(CCamera* camera)
{
  m_activeCameras.push_back(camera);
}
Vector<CCamera*>
GraphicsApi::getActiveCameras()
{
  return m_activeCameras;
}
void
GraphicsApi::clearActiveCameras()
{
  m_activeCameras.clear();
}
}