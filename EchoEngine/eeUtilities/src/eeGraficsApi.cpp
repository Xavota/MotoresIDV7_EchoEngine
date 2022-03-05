#include "eeGraficsApi.h"
#include "eeCoreConfiguration.h"
#include "eeResourceManager.h"
#include "eeVertexShader.h"
#include "eePixelShader.h"
#include "eeConstantBuffer.h"
#include "eeObject.h"
#include "eeStaticMesh.h"
#include "eeMesh.h"
#include "eeCTransform.h"
#include "eeCSkeletalMesh.h"
#include "eeSkeletalMesh.h"
#include "eeSkeletal.h"
#include "eeCStaticMesh.h"
#include "eeActor.h"
#include "eeMaterial.h"

namespace eeEngineSDK {
GraphicsApi::~GraphicsApi()
{
  release();
}
bool
GraphicsApi::initialize(uint32 witdh, uint32 height)
{
  ViewportDesc desc;
  memset(&desc, 0, sizeof(desc));
  desc.maxDepth = 1.0f;
  desc.minDepth = 0;
  desc.width = static_cast<float>(witdh);
  desc.height = static_cast<float>(height);
  desc.topLeftX = 0;
  desc.topLeftY = 0;
  setViewports({ desc });
  
  //m_rtv = createTexturePtr();
  //m_rtv->createAsBackBuffer();
  //
  //m_dsv = createTexturePtr();
  //m_dsv->create2D(eTEXTURE_BIND_FLAGS::kDepthStencil,
  //                { witdh, height });

  m_mainWindow->initRenders();

  return true;
}
bool
GraphicsApi::initializeScreen(void* callback, uint32 witdh, uint32 height)
{
  m_mainWindow = createWindowPtr();
  if (!m_mainWindow->initWindow(callback, witdh, height)) {
    return false;
  }
  m_mainWindow->showWindow();
  return true;
}
void
GraphicsApi::drawObject(SPtr<Object> obj)
{
  auto& graphicsApi = GraphicsApi::instance();

  //m_basics.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  //Vector<Pair<Mesh, SPtr<Texture>>> meshes = obj->getModel()->getMeshes();
  Vector<Pair<Mesh, SPtr<Material>>> meshes = obj->getModel()->getMeshes();

  obj->getModelBuffer()->setInVertex(0u);

  SIZE_T meshesCount = meshes.size();
  for (SIZE_T i = 0; i < meshesCount; ++i) {
    meshes[i].first.set();

    graphicsApi.setTextures({meshes[i].second->m_diffuse}, 0u);

    drawIndexed(static_cast<uint32>(meshes[i].first.getIndexCount()));

    graphicsApi.unsetVertexBuffers(1u, 0u);
  }  
}
void
GraphicsApi::drawObject(SPtr<Actor> act)
{
  static SPtr<ConstantBuffer> modelMatrixBuff = nullptr;
  if (!modelMatrixBuff)
  {
    modelMatrixBuff = GraphicsApi::instance().createConstantBufferPtr();
    modelMatrixBuff->initData(sizeof(Matrix4f), sizeof(Matrix4f), nullptr);
  }

  EE_NO_EXIST_RETURN(act);

  auto& graphicsApi = GraphicsApi::instance();

  Vector<Pair<Mesh, SPtr<Material>>> meshes;
  SIZE_T meshesCount = 0;

  SPtr<CTransform> transform = act->getTransform();

  const SPtr<CStaticMesh> staticMesh = act->getComponent<CStaticMesh>();
  if (staticMesh && staticMesh->getStaticMesh())
  {
    meshes = staticMesh->getStaticMesh()->getMeshes();
    meshesCount = meshes.size();
  
    Matrix4f modelMatrix = transform->getModelMatrix();
    modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMatrix));
    modelMatrixBuff->setInVertex(0u);
  
    for (SIZE_T i = 0; i < meshesCount; ++i) {
      meshes[i].first.set();
  
      graphicsApi.setTextures({ meshes[i].second->m_diffuse }, 0u);
  
      drawIndexed(static_cast<uint32>(meshes[i].first.getIndexCount()));
  
      graphicsApi.unsetVertexBuffers(1u, 0u);
      graphicsApi.unsetTextures(1u, 0u);
    }
  }

  const SPtr<CSkeletalMesh> skeletal = act->getComponent<CSkeletalMesh>();
  if (skeletal && skeletal->getModel())
  {
    const SPtr<SkeletalMesh> skModel = skeletal->getModel();
    meshes = skModel->getMeshes();
    meshesCount = meshes.size();
  
    Matrix4f modelMatrix = transform->getModelMatrix();
    modelMatrixBuff->updateData(reinterpret_cast<Byte*>(&modelMatrix));
    modelMatrixBuff->setInVertex(0u);
  
    const SPtr<Skeletal> skeleton = skModel->getSkeletal();
    for (SIZE_T i = 0; i < meshesCount; ++i) {
      meshes[i].first.set();
  
      graphicsApi.setTextures({ meshes[i].second->m_diffuse }, 0u);
  
      if (skeleton) {
        skeleton->use(i);
      }
  
      drawIndexed(static_cast<uint32>(meshes[i].first.getIndexCount()));
  
      graphicsApi.unsetVertexBuffers(1u, 0u);
      graphicsApi.unsetTextures(1u, 0u);
    }
  }
}
void
GraphicsApi::release()
{
}
void GraphicsApi::resizeWindow(Vector2u newSize)
{
  //MemoryManager::instance().safeRelease<Texture>(m_rtv);
  //m_rtv->createAsBackBuffer();
  //MemoryManager::instance().safeRelease<Texture>(m_dsv);
  //m_dsv->create2D(eTEXTURE_BIND_FLAGS::kDepthStencil,
  //                { newSize.x, newSize.y });
  m_mainWindow->resize(newSize.x, newSize.y);

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