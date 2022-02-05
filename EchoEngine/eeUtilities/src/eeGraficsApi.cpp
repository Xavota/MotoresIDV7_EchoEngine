#include "eeGraficsApi.h"
#include "eeCoreConfiguration.h"
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
#include "eeSkeletal.h"
#include "eeCModel.h"
#include "eeActor.h"

namespace eeEngineSDK {
bool
GraphicsApi::initialize()
{
  //auto& graphicsApi = GraphicsApi::instance();
  //
  //m_rtv = graphicsApi.createRenderTragetPtr();
  //m_rtv->createAsBackBuffer();
  //
  //m_dsv = graphicsApi.createDepthStencilPtr();
  //m_dsv->create(eeConfigurations::screenWidth, eeConfigurations::screenHeight);

  ViewportDesc desc;
  memset(&desc, 0, sizeof(desc));
  desc.maxDepth = 1.0f;
  desc.minDepth = 0;
  desc.width = static_cast<float>(eeConfigurations::screenWidth);
  desc.height = static_cast<float>(eeConfigurations::screenHeight);
  desc.topLeftX = 0;
  desc.topLeftY = 0;
  setViewports({ desc });

  return true;
}
bool GraphicsApi::initializeScreen(void*)
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
  //EE_NO_EXIST_RETURN(act);
  //
  //auto& graphicsApi = GraphicsApi::instance();
  //
  //SPtr<CTransform> transform = act->getTransform();
  //
  //SPtr<CModel> model = act->getComponent<CModel>();
  //
  //EE_NO_EXIST_RETURN(model);
  //EE_NO_EXIST_RETURN(model->getModel());
  //
  //const Vector<Pair<SPtr<Mesh>, SPtr<Texture>>>& meshes = model->getModel()->getMeshes();
  //int32 meshesCount = static_cast<uint32>(meshes.size());
  //
  //const SPtr<CSkeletalMesh> skeletal = act->getComponent<CSkeletalMesh>();
  //
  //transform->getModelBuffer()->setInVertex(0u);
  //
  //for (int32 i = 0; i < meshesCount; ++i) {
  //  if (!meshes[i].first) { break; }
  //
  //  meshes[i].first->set();
  //
  //  graphicsApi.setTextures({ meshes[i].second }, 0u);
  //
  //  if (skeletal && skeletal->getSkeletal()) {
  //    skeletal->getSkeletal()->use(i);
  //  }
  //
  //  drawIndexed(meshes[i].first->getIndexCount());
  //
  //  graphicsApi.unsetVertexBuffers(1u, 0u);
  //  graphicsApi.unsetTextures(1u, 0u);
  //}


  EE_NO_EXIST_RETURN(act);

  auto& graphicsApi = GraphicsApi::instance();

  Vector<Pair<SPtr<Mesh>, SPtr<Texture>>> meshes;
  int32 meshesCount = 0;

  SPtr<CTransform> transform = act->getTransform();

  const SPtr<CModel> model = act->getComponent<CModel>();
  if (model && model->getModel())
  {
    meshes = model->getModel()->getMeshes();
    meshesCount = static_cast<uint32>(meshes.size());

    transform->getModelBuffer()->setInVertex(0u);

    for (int32 i = 0; i < meshesCount; ++i) {
      if (!meshes[i].first) { break; }

      meshes[i].first->set();

      graphicsApi.setTextures({ meshes[i].second }, 0u);

      drawIndexed(meshes[i].first->getIndexCount());

      graphicsApi.unsetVertexBuffers(1u, 0u);
      graphicsApi.unsetTextures(1u, 0u);
    }
  }

  const SPtr<CSkeletalMesh> skeletal = act->getComponent<CSkeletalMesh>();
  if (skeletal && skeletal->getModel())
  {
    const SPtr<SkeletalMesh> skModel = skeletal->getModel();
    meshes = skModel->getMeshes();
    meshesCount = static_cast<uint32>(meshes.size());

    transform->getModelBuffer()->setInVertex(0u);

    const SPtr<Skeletal> skeleton = skModel->getSkeletal();
    for (int32 i = 0; i < meshesCount; ++i) {
      if (!meshes[i].first) { break; }

      meshes[i].first->set();

      graphicsApi.setTextures({ meshes[i].second }, 0u);

      if (skeleton) {
        skeleton->use(i);
      }

      drawIndexed(meshes[i].first->getIndexCount());

      graphicsApi.unsetVertexBuffers(1u, 0u);
      graphicsApi.unsetTextures(1u, 0u);
    }
  }
}
void
GraphicsApi::release()
{
}
void GraphicsApi::resizeWindow(Vector2i newSize)
{
  ViewportDesc desc;
  memset(&desc, 0, sizeof(desc));
  desc.maxDepth = 1.0f;
  desc.minDepth = 0;
  desc.width = static_cast<float>(newSize.x);
  desc.height = static_cast<float>(newSize.y);
  desc.topLeftX = 0;
  desc.topLeftY = 0;
  setViewports({ desc });
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