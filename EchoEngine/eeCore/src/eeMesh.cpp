#include "eeMesh.h"

#include <eeMath.h>

#include <eeVertex.h>

namespace eeEngineSDK {
/*template<typename V, typename I>*/
Mesh/*<V,I>*/::Mesh(const Mesh& other)
{
  if (other.m_vertexData && other.m_vertexData->isValid()
   && other.m_indexData  && other.m_indexData->isValid()) {
    auto& graphicsApi = GraphicsApi::instance();
    if (!m_vertexData) {
      m_vertexData = graphicsApi.createVertexBufferPtr();
    }
    if (!m_indexData) {
      m_indexData = graphicsApi.createIndexBufferPtr();
    }

    m_vertexData->initData(other.m_vertexData->getDataSize(),
                           other.m_vertexData->getBatchSize(),
                           other.m_vertexData->getData().data());
    m_indexData->initData(other.m_indexData->getDataSize(),
                          other.m_indexData->getBatchSize(),
                          other.m_indexData->getData().data());
    
    m_indexCount = other.m_indexCount;
  }
}
/*template<typename V, typename I>*/
Mesh/*<V, I>*/::~Mesh()
{
  MemoryManager::instance().safeRelease(m_vertexData);
  MemoryManager::instance().safeRelease(m_indexData);
}
/*template<typename V, typename I>*/
void
Mesh/*<V, I>*/::set() const
{
  m_vertexData->set();
  m_indexData->set();
}
/*template<typename V, typename I>*/
const SPtr<VertexBuffer>
Mesh/*<V, I>*/::getVertexData() const
{
  return m_vertexData;
}
/*template<typename V, typename I>*/
const SPtr<IndexBuffer> 
Mesh/*<V, I>*/::getIndexData() const
{
  return m_indexData;
}
/*template<typename V, typename I>*/
Mesh/*<V,I>*/ Mesh/*<V,I>*/::cube;
/*template<typename V, typename I>*/
Mesh/*<V,I>*/ Mesh/*<V,I>*/::tetrahedron;
/*template<typename V, typename I>*/
Mesh/*<V,I>*/ Mesh/*<V,I>*/::cone;
/*template<typename V, typename I>*/
Mesh/*<V,I>*/ Mesh/*<V,I>*/::cylinder;
/*template<typename V, typename I>*/
Mesh/*<V,I>*/ Mesh/*<V,I>*/::sphere;
/*template<typename V, typename I>*/
Mesh/*<V,I>*/ Mesh/*<V,I>*/::capsule;
/*template<typename V, typename I>*/
Mesh/*<V,I>*/ Mesh/*<V,I>*/::SAQ;
/*template<typename V, typename I>*/
void
Mesh/*<V, I>*/::initPrimitives()
{
  Vector<SimpleVertex> vertices;
  Vector<uint16> indices;

  vertices = 
  {
    // Front
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f,  1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f,  1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f,  1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f,  1.0f, 0.0f)
    },

    // Back
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f, -1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f, -1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f, -1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f, -1.0f, 0.0f)
    },

    // Left
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
    },

    // Right
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f)
    },

    // Up
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f)
    },

    // Down
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f, -1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f, -1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f, -1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f, -1.0f,  0.0f, 0.0f)
    }
  };

  indices =
  {
    0u, 2u, 1u,
    0u, 3u, 2u,

    4u, 6u, 5u,
    4u, 7u, 6u,

    8u, 10u, 9u,
    8u, 11u, 10u,

    12u, 14u, 13u,
    12u, 15u, 14u,

    16u, 18u, 17u,
    16u, 19u, 18u,

    20u, 22u, 21u,
    20u, 23u, 22u
  };

  cube.loadFromArray(vertices, indices);



  vertices =
  {
    SimpleVertex
    {
      Vector4f(0.0f,  1.09f, 0.0f, 1.0f),
      Vector4f(0.5f,  0.0f, 0.0f, 0.0f),
      Vector4f(0.82f,  0.33f, 0.47f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(0.0f, -0.54f, 1.15f, 1.0f),
      Vector4f(1.0f,  1.0f, 0.0f, 0.0f),
      Vector4f(0.82f,  0.33f, 0.47f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(1.0f, -0.54f, -0.58f, 1.0f),
      Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(0.82f,  0.33f, 0.47f, 0.0f)
    },

    SimpleVertex
    {
      Vector4f(0.0f,  1.09f, 0.0f, 1.0f),
      Vector4f(0.5f,  0.0f, 0.0f, 0.0f),
      Vector4f(0.0f,  0.33f, -0.94f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(1.0f, -0.54f, -0.58f, 1.0f),
      Vector4f(1.0f,  1.0f, 0.0f, 0.0f),
      Vector4f(0.0f,  0.33f, -0.94f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-1.0f, -0.54f, -0.58f, 1.0f),
      Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.33f, -0.94f, 0.0f)
    },

    SimpleVertex
    {
      Vector4f(0.0f,  1.09f, 0.0f, 1.0f),
      Vector4f(0.5f,  0.0f, 0.0f, 0.0f),
      Vector4f(-0.82f,  0.33f, 0.47f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-1.0f, -0.54f, -0.58f, 1.0f),
      Vector4f(1.0f,  1.0f, 0.0f, 0.0f),
      Vector4f(-0.82f,  0.33f, 0.47f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(0.0f, -0.54f, 1.15f, 1.0f),
      Vector4f(1.0f,  0.0f, 0.0f, 0.0f),
      Vector4f(-0.82f,  0.33f, 0.47f, 0.0f)
    },

    SimpleVertex
    {
      Vector4f(0.0f, -0.54f, 1.15f, 1.0f),
      Vector4f(0.5f,  0.0f, 0.0f, 0.0f),
      Vector4f(0.0f,  0.0f, -1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-1.0f, -0.54f, -0.58f, 1.0f),
      Vector4f(1.0f,  1.0f, 0.0f, 0.0f),
      Vector4f(0.0f,  0.0f, -1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(1.0f, -0.54f, -0.58f, 1.0f),
      Vector4f(1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f, -1.0f, 0.0f)
    },
  };

  indices =
  {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,
    9, 10, 11
  };

  tetrahedron.loadFromArray(vertices, indices);

  getSpherePrimitive(1.0f, 20u, 20u, sphere);



  vertices = 
  {
    SimpleVertex
    {
      Vector4f(-1.0f,  1.0f, 0.0f, 1.0f),
      Vector4f(0.0f,  0.0f, 0.0f, 0.0f),
      Vector4f(0.0f,  0.0f, 0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(1.0f,  1.0f, 0.0f, 1.0f),
      Vector4f(1.0f,  0.0f, 0.0f, 0.0f),
      Vector4f(0.0f,  0.0f, 0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(1.0f, -1.0f,  0.0f, 1.0f),
      Vector4f(1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-1.0f, -1.0f,  0.0f, 1.0f),
      Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f,  0.0f, 0.0f)
    }
  };

  indices =
  {
    0, 1, 2,
    0, 2, 3
  };

  SAQ.loadFromArray(vertices, indices);
}

bool
Mesh::getSpherePrimitive(float radius,
                         uint32 verticalParts,
                         uint32 horizontalParts,
                         Mesh& outMesh)
{
  if (radius <= 0.0f || verticalParts <= 0u || horizontalParts <= 0u) {
    return false;
  }

  Vector<SimpleVertex> vertices;
  Vector<uint16> indices;

  for (uint32 n = 0; n <= verticalParts; ++n) {
    for (uint32 m = 0; m <= horizontalParts; ++m) {
      Vector4f pos;
      Vector4f uv;
      Vector4f normal;
      float a = n * Math::kPI / verticalParts;
      float b = 2 * m * Math::kPI / horizontalParts;

      pos.x = radius * Math::sin(b) * Math::sin(a);
      pos.y = radius * Math::cos(b) * Math::sin(a);
      pos.z = radius * Math::cos(a);
      pos.w = 1.0f;

      uv.x = m / (static_cast<float>(horizontalParts));
      uv.y = n / (static_cast<float>(verticalParts));
      uv.z = 0.0f;
      uv.w = 0.0f;

      normal.x = pos.x;
      normal.y = pos.y;
      normal.z = pos.z;
      normal.w = 0.0f;
      normal.normalize();

      vertices.emplace_back(SimpleVertex{pos, uv, normal});
    }
  }

  uint32 verticesCount = verticalParts * (horizontalParts + 1u);
  for (uint32 i = 0; i < verticesCount; ++i) {
    if ((i + 1) % (horizontalParts + 1) == 0) {
      continue;
    }

    indices.push_back(i);
    indices.push_back(i + 1);
    indices.push_back(i + horizontalParts + 1);

    indices.push_back(i + 1);
    indices.push_back(i + horizontalParts + 2);
    indices.push_back(i + horizontalParts + 1);
  }

  outMesh.loadFromArray(vertices, indices);

  return true;
}
}