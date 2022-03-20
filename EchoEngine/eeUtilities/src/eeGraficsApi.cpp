#include "eeGraficsApi.h"
#include "eeCoreConfiguration.h"
#include "eeResourceManager.h"
#include "eeVertexShader.h"
#include "eePixelShader.h"
#include "eeConstantBuffer.h"
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
GraphicsApi::drawOnSAQ()
{
  static Mesh SAQ = Mesh::SAQ;
  SAQ.set();
  drawIndexed(static_cast<uint32>(SAQ.getIndexCount()));
  unsetVertexBuffers(1u, 0u);
}
void GraphicsApi::drawMesh(const Mesh& meshToDraw)
{
  meshToDraw.set();
  drawIndexed(static_cast<uint32>(meshToDraw.getIndexCount()));
  unsetVertexBuffers(1u, 0u);
}
void
GraphicsApi::release() {}
void GraphicsApi::resizeWindow(Point2D newSize)
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