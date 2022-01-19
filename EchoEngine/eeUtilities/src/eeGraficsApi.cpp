#include "eeGraficsApi.h"
#include "eeResourceManager.h"
#include "eeVertexShader.h"
#include "eePixelShader.h"
#include "eeConstantBuffer.h"
#include "eeObject.h"
#include "eeModel.h"
#include "eeMesh.h"
#include "eeCTransform.h"
#include "eeCSkeletalMesh.h"
#include "eeSkeletalMesh.h"
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
  auto& graphicsApi = GraphicsApi::instance();

  //m_basics.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  const Vector<Pair<SPtr<Mesh>, SPtr<Texture>>>& meshes = obj->getModel()->getMeshes();

  obj->getModelBuffer()->setInVertex(0u);

  for (const auto& m : meshes) {
    m.first->set();

    graphicsApi.setTextures({m.second}, 0u);

    drawIndexed(m.first->getIndexCount());

    graphicsApi.unsetVertexBuffers(1u, 0u);
  }  
}
void
GraphicsApi::drawObject(SPtr<Actor> act)
{
  EE_NO_EXIST_RETURN(act);

  auto& graphicsApi = GraphicsApi::instance();

  SPtr<CTransform> transform = act->getTransform();

  SPtr<CModel> model = act->getComponent<CModel>();
  EE_NO_EXIST_RETURN(model);
  EE_NO_EXIST_RETURN(model->getModel());

  const Vector<Pair<SPtr<Mesh>, SPtr<Texture>>>& meshes = model->getModel()->getMeshes();
  int32 meshesCount = static_cast<uint32>(meshes.size());

  const SPtr<CSkeletalMesh> skeletal = act->getComponent<CSkeletalMesh>();

  transform->getModelBuffer()->setInVertex(0u);

  for (int32 i = 0; i < meshesCount; ++i) {
    if (!meshes[i].first) { break; }

    meshes[i].first->set();

    graphicsApi.setTextures({ meshes[i].second }, 0u);

    if (skeletal && skeletal->getSkeletal()) {
      skeletal->getSkeletal()->use(i);
    }

    drawIndexed(meshes[i].first->getIndexCount());

    graphicsApi.unsetVertexBuffers(1u, 0u);
    graphicsApi.unsetTextures(1u, 0u);
  }
}
void
GraphicsApi::release()
{
}
void
GraphicsApi::addActorToRenderFrame(SPtr<Actor> actor)
{
  EE_NO_EXIST_RETURN(actor);
  m_renderActors.push_back(actor);
}
Vector<SPtr<Actor>>
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
GraphicsApi::addActiveCamera(SPtr<CCamera> camera)
{
  EE_NO_EXIST_RETURN(camera);
  m_activeCameras.push_back(camera);
}
Vector<SPtr<CCamera>>
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