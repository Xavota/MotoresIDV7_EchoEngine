#include "eeGraficsApi.h"
#include "eeCoreConfiguration.h"
#include "eeResourceManager.h"
#include "eeVertexShader.h"
#include "eePixelShader.h"
#include "eeConstantBuffer.h"
#include "eeStaticMesh.h"
#include "eeMesh.h"
#include "eeBoneMesh.h"
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
GraphicsApi::initialize()
{
  return true;
}
bool
GraphicsApi::initializeScreen(void* callback,
                              uint32 witdh,
                              uint32 height,
                              const String& displayName)
{
  m_mainWindow = createWindowPtr();
  if (!m_mainWindow->initWindow(callback, witdh, height, displayName)) {
    return false;
  }
  m_mainWindow->showWindow();


  if (!initializeBasics()) {
    return false;
  }


  ViewportDesc desc;
  memset(&desc, 0, sizeof(desc));
  desc.maxDepth = 1.0f;
  desc.minDepth = 0;
  desc.width = static_cast<float>(witdh);
  desc.height = static_cast<float>(height);
  desc.topLeftX = 0;
  desc.topLeftY = 0;
  setViewports({ desc });

  m_mainWindow->initRenders();

  return true;
}
void
GraphicsApi::drawOnSAQ()
{
  static SPtr<VertexBuffer> SAQVertexBuffer = nullptr;
  static SPtr<IndexBuffer> SAQIndexBuffer = nullptr;
  if (!SAQVertexBuffer || !SAQIndexBuffer) {
    SAQVertexBuffer = createVertexBufferPtr();
    SAQIndexBuffer = createIndexBufferPtr();

    Vector<SimplexVertex> vertices;
    Vector<uint16> indices;

    vertices = 
    {
      SimplexVertex
      {
        Vector4f(-1.0f,  1.0f, 0.0f, 1.0f),
        Vector4f(0.0f,  0.0f, 0.0f, 0.0f)
      },
      SimplexVertex
      {
        Vector4f(1.0f,  1.0f, 0.0f, 1.0f),
        Vector4f(1.0f,  0.0f, 0.0f, 0.0f)
      },
      SimplexVertex
      {
        Vector4f(1.0f, -1.0f,  0.0f, 1.0f),
        Vector4f(1.0f,  1.0f,  0.0f, 0.0f)
      },
      SimplexVertex
      {
        Vector4f(-1.0f, -1.0f,  0.0f, 1.0f),
        Vector4f(0.0f,  1.0f,  0.0f, 0.0f)
      }
    };
    
    indices =
    {
      0, 1, 2,
      0, 2, 3
    };
    
    SAQVertexBuffer->initData(vertices.size() * sizeof(SimplexVertex),
                              sizeof(SimplexVertex),
                              reinterpret_cast<const Byte*>(vertices.data()));
    SAQIndexBuffer->initData(indices.size() * sizeof(uint16),
                             sizeof(uint16),
                             reinterpret_cast<const Byte*>(indices.data()));
  }
  SAQVertexBuffer->set();
  SAQIndexBuffer->set();
  drawIndexed(6);
  unsetVertexBuffers(1u, 0u);
}
void
GraphicsApi::drawMesh(const Mesh& meshToDraw)
{
  meshToDraw.set();
  drawIndexed(static_cast<uint32>(meshToDraw.getIndexCount()));
  unsetVertexBuffers(1u, 0u);
}
void
GraphicsApi::drawMesh(const BoneMesh& meshToDraw)
{
  meshToDraw.set();
  drawIndexed(static_cast<uint32>(meshToDraw.getIndexCount()));
  unsetVertexBuffers(1u, 0u);
}
void
GraphicsApi::drawMeshControlPoints(const Mesh& meshToDraw)
{
  meshToDraw.getVertexData()->set();
  drawNoIndexed(static_cast<uint32>(meshToDraw.getControlPointsCount()));
  unsetVertexBuffers(1u, 0u);
}
void
GraphicsApi::resizeWindow(Point2D newSize)
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
}