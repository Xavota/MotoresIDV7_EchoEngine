#include "eeMesh.h"

#include <eeMath.h>
#include <eeMatrix4.h>

#include <eeVertex.h>
#include <eePlane.h>

#include "eeGraficsApi.h"

namespace eeEngineSDK {
//Mesh::Mesh(const Mesh& other)
//{
//  if (other.m_vertexData && other.m_vertexData->isValid()
//   && other.m_indexData  && other.m_indexData->isValid()) {
//    auto& graphicsApi = GraphicsApi::instance();
//    if (!m_vertexData) {
//      m_vertexData = graphicsApi.createVertexBufferPtr();
//    }
//    if (!m_indexData) {
//      m_indexData = graphicsApi.createIndexBufferPtr();
//    }
//
//    m_vertexData->initData(other.m_vertexData->getDataSize(),
//                           other.m_vertexData->getBatchSize(),
//                           other.m_vertexData->getData().data());
//    m_indexData->initData(other.m_indexData->getDataSize(),
//                          other.m_indexData->getBatchSize(),
//                          other.m_indexData->getData().data());
//    
//    m_indexCount = other.m_indexCount;
//  }
//}
Mesh::Mesh(const Vector<ComplexVertex>& vertices, const Vector<uint32>& indices)
{
  loadFromVertexArray(vertices, indices);
}
bool 
Mesh::loadFromVertexArray(const Vector<ComplexVertex>& vertices,
                          const Vector<uint32>& indices)
{
  auto& graphicsApi = GraphicsApi::instance();

  if (vertices.empty() || indices.empty()) {
    Logger::instance().consoleLog("Empty info loading mesh");
    return false;
  }

  SIZE_T indicesSize = indices.size();
  for (SIZE_T i = 0; i < indicesSize; i += 3) {
    if (i + 2 < indicesSize) {
      m_vertexArray.emplace_back(Triangle(vertices[indices[i]],
                                          vertices[indices[i + 1]],
                                          vertices[indices[i + 2]]));
      m_indexArray.push_back(static_cast<uint32>(i));
      m_indexArray.push_back(static_cast<uint32>(i + 1));
      m_indexArray.push_back(static_cast<uint32>(i + 2));
    }
  }


  if (!m_vertexData) {
    m_vertexData = graphicsApi.createVertexBufferPtr();
  }
  if (!m_indexData) {
    m_indexData = graphicsApi.createIndexBufferPtr();
  }
  m_vertexData->initData(m_vertexArray.size() * sizeof(ComplexVertex) * 3,
                         sizeof(ComplexVertex),
                         reinterpret_cast<const Byte*>(m_vertexArray.data()));
  m_indexData->initData(m_indexArray.size() * sizeof(uint32),
                        sizeof(uint32),
                        reinterpret_cast<const Byte*>(m_indexArray.data()));


  m_indexCount = m_indexArray.size();

  return true;
}
bool
Mesh::loadFromTrianglesArray(const Vector<Triangle>& triangles)
{
  auto& graphicsApi = GraphicsApi::instance();

  m_vertexArray = triangles;
  SIZE_T indicesSize = m_vertexArray.size() * 3;
  for (SIZE_T i = 0; i < indicesSize; ++i) {
    m_indexArray.push_back(static_cast<uint32>(i));
  }

  if (!m_vertexData) {
    m_vertexData = graphicsApi.createVertexBufferPtr();
  }
  if (!m_indexData) {
    m_indexData = graphicsApi.createIndexBufferPtr();
  }
  m_vertexData->initData(m_vertexArray.size() * sizeof(Triangle),
                         sizeof(ComplexVertex),
                         reinterpret_cast<const Byte*>(m_vertexArray.data()));
  m_indexData->initData(m_indexArray.size() * sizeof(uint32),
                        sizeof(uint32),
                        reinterpret_cast<const Byte*>(m_indexArray.data()));


  m_indexCount = m_indexArray.size();

  return true;
}
bool
Mesh::loadFromControlPoints(const Vector<ComplexVertex>& vertices)
{
  auto& graphicsApi = GraphicsApi::instance();
  m_controlPoints = vertices;
  if (!m_vertexData) {
    m_vertexData = graphicsApi.createVertexBufferPtr();
  }
  m_vertexData->initData(m_controlPoints.size() * sizeof(ComplexVertex),
                         sizeof(ComplexVertex),
                         reinterpret_cast<const Byte*>(m_controlPoints.data()));
  return true;
}
void
Mesh::set() const
{
  m_vertexData->set();
  m_indexData->set();
}
const WPtr<VertexBuffer>
Mesh::getVertexData() const
{
  return m_vertexData;
}
const WPtr<IndexBuffer> 
Mesh::getIndexData() const
{
  return m_indexData;
}
Mesh Mesh::cube;
Mesh Mesh::tetrahedron;
Mesh Mesh::cone;
Mesh Mesh::cylinder;
Mesh Mesh::sphere;
Mesh Mesh::capsule;
void
Mesh::initPrimitives()
{
  Vector<ComplexVertex> vertices;
  Vector<uint32> indices;
  
  vertices = 
  {
    // Front
    ComplexVertex
    {
      Vector4f(-0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f,  1.0f, 0.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( -1.0f,  0.0f,  0.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f( 0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f,  1.0f, 0.0f),
      Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f( 0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f,  1.0f, 0.0f),
      Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f(-0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f,  1.0f, 0.0f),
      Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
    },
  
    // Back
    ComplexVertex
    {
      Vector4f( 0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f, -1.0f, 0.0f),
      Vector4f(0.0f,  -1.0f,  0.0f, 0.0f),
      Vector4f(1.0f,  0.0f,  0.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f(-0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f, -1.0f, 0.0f),
      Vector4f(0.0f,  -1.0f,  0.0f, 0.0f),
      Vector4f(1.0f,  0.0f,  0.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f(-0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f, -1.0f, 0.0f),
      Vector4f(0.0f,  -1.0f,  0.0f, 0.0f),
      Vector4f(1.0f,  0.0f,  0.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f( 0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f, -1.0f, 0.0f),
      Vector4f(0.0f,  -1.0f,  0.0f, 0.0f),
      Vector4f(1.0f,  0.0f,  0.0f, 0.0f)
    },
  
    // Left
    ComplexVertex
    {
      Vector4f(-0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f,  -1.0f, 0.0f),
      Vector4f(0.0f,  1.0f,  0.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f(-0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f,  -1.0f, 0.0f),
      Vector4f(0.0f,  1.0f,  0.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f(-0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f,  -1.0f, 0.0f),
      Vector4f(0.0f,  1.0f,  0.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f(-0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f,  -1.0f, 0.0f),
      Vector4f(0.0f,  1.0f,  0.0f, 0.0f)
    },
  
    // Right
    ComplexVertex
    {
      Vector4f( 0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f,  1.0f, 0.0f),
      Vector4f(0.0f,  -1.0f,  0.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f( 0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f,  1.0f, 0.0f),
      Vector4f(0.0f,  -1.0f,  0.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f( 0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f,  1.0f, 0.0f),
      Vector4f(0.0f,  -1.0f,  0.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f( 0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f,  1.0f, 0.0f),
      Vector4f(0.0f,  -1.0f,  0.0f, 0.0f)
    },
  
    // Up
    ComplexVertex
    {
      Vector4f(-0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f,  -1.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f( 0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f, -1.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f( 0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f,  -1.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f(-0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f,  -1.0f, 0.0f)
    },
  
    // Down
    ComplexVertex
    {
      Vector4f(-0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(0.0f, -1.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f, 1.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f( 0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(0.0f, -1.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f, 1.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f( 0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f, -1.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f, 1.0f, 0.0f)
    },
    ComplexVertex
    {
      Vector4f(-0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f, -1.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(0.0f,  0.0f, 1.0f, 0.0f)
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
  
  cube.loadFromVertexArray(vertices, indices);
  //
  //
  //
  //vertices =
  //{
  //  SimpleVertex
  //  {
  //    Vector4f(0.0f,  1.09f, 0.0f, 1.0f),
  //    Vector4f(0.5f,  0.0f, 0.0f, 0.0f),
  //    Vector4f(0.82f,  0.33f, 0.47f, 0.0f)
  //  },
  //  SimpleVertex
  //  {
  //    Vector4f(0.0f, -0.54f, 1.15f, 1.0f),
  //    Vector4f(1.0f,  1.0f, 0.0f, 0.0f),
  //    Vector4f(0.82f,  0.33f, 0.47f, 0.0f)
  //  },
  //  SimpleVertex
  //  {
  //    Vector4f(1.0f, -0.54f, -0.58f, 1.0f),
  //    Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
  //    Vector4f(0.82f,  0.33f, 0.47f, 0.0f)
  //  },
  //
  //  SimpleVertex
  //  {
  //    Vector4f(0.0f,  1.09f, 0.0f, 1.0f),
  //    Vector4f(0.5f,  0.0f, 0.0f, 0.0f),
  //    Vector4f(0.0f,  0.33f, -0.94f, 0.0f)
  //  },
  //  SimpleVertex
  //  {
  //    Vector4f(1.0f, -0.54f, -0.58f, 1.0f),
  //    Vector4f(1.0f,  1.0f, 0.0f, 0.0f),
  //    Vector4f(0.0f,  0.33f, -0.94f, 0.0f)
  //  },
  //  SimpleVertex
  //  {
  //    Vector4f(-1.0f, -0.54f, -0.58f, 1.0f),
  //    Vector4f(0.0f,  1.0f,  0.0f, 0.0f),
  //    Vector4f(0.0f,  0.33f, -0.94f, 0.0f)
  //  },
  //
  //  SimpleVertex
  //  {
  //    Vector4f(0.0f,  1.09f, 0.0f, 1.0f),
  //    Vector4f(0.5f,  0.0f, 0.0f, 0.0f),
  //    Vector4f(-0.82f,  0.33f, 0.47f, 0.0f)
  //  },
  //  SimpleVertex
  //  {
  //    Vector4f(-1.0f, -0.54f, -0.58f, 1.0f),
  //    Vector4f(1.0f,  1.0f, 0.0f, 0.0f),
  //    Vector4f(-0.82f,  0.33f, 0.47f, 0.0f)
  //  },
  //  SimpleVertex
  //  {
  //    Vector4f(0.0f, -0.54f, 1.15f, 1.0f),
  //    Vector4f(1.0f,  0.0f, 0.0f, 0.0f),
  //    Vector4f(-0.82f,  0.33f, 0.47f, 0.0f)
  //  },
  //
  //  SimpleVertex
  //  {
  //    Vector4f(0.0f, -0.54f, 1.15f, 1.0f),
  //    Vector4f(0.5f,  0.0f, 0.0f, 0.0f),
  //    Vector4f(0.0f,  0.0f, -1.0f, 0.0f)
  //  },
  //  SimpleVertex
  //  {
  //    Vector4f(-1.0f, -0.54f, -0.58f, 1.0f),
  //    Vector4f(1.0f,  1.0f, 0.0f, 0.0f),
  //    Vector4f(0.0f,  0.0f, -1.0f, 0.0f)
  //  },
  //  SimpleVertex
  //  {
  //    Vector4f(1.0f, -0.54f, -0.58f, 1.0f),
  //    Vector4f(1.0f,  1.0f,  0.0f, 0.0f),
  //    Vector4f(0.0f,  0.0f, -1.0f, 0.0f)
  //  },
  //};
  //
  //indices =
  //{
  //  0, 1, 2,
  //  3, 4, 5,
  //  6, 7, 8,
  //  9, 10, 11
  //};
  //
  //tetrahedron.loadFromArray(vertices, indices);
  //
  getSpherePrimitive(1.0f, 20u, 20u, sphere);
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
  
  Vector<ComplexVertex> vertices;
  Vector<uint32> indices;
  
  for (uint32 n = 0; n <= verticalParts; ++n) {
    for (uint32 m = 0; m <= horizontalParts; ++m) {
      Vector4f pos;
      Vector4f uv;
      Vector4f normal;
      Vector4f binormal = Vector4f{0.0f, 0.0f, 0.0f, 0.0f};
      Vector4f tangent = Vector4f{ 0.0f, 0.0f, 0.0f, 0.0f };
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
  
      vertices.emplace_back(ComplexVertex{pos, uv, normal, binormal, tangent});
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
  
  outMesh.loadFromVertexArray(vertices, indices);

  return true;
}
void
Mesh::copyMeshTransformed(const Mesh& meshToCopy,
                          const Matrix4f& transformMatrix,
                          Mesh& outNewMesh)
{
  int32 indexCount = 0;
  for (auto& tri : meshToCopy.m_vertexArray) {
    Vector4f posX = transformMatrix * tri.x.position;
    Vector4f uvX = tri.x.uvCoord;
    Vector4f normX = transformMatrix * tri.x.normal;
    Vector4f binX = transformMatrix * tri.x.binormal;
    Vector4f tanX = transformMatrix * tri.x.tangent;
    ComplexVertex vertexX = ComplexVertex{posX, uvX, normX, binX, tanX};

    Vector4f posY = transformMatrix * tri.y.position;
    Vector4f uvY = tri.y.uvCoord;
    Vector4f normY = transformMatrix * tri.y.normal;
    Vector4f binY = transformMatrix * tri.y.binormal;
    Vector4f tanY = transformMatrix * tri.y.tangent;
    ComplexVertex vertexY = ComplexVertex{ posY, uvY, normY, binY, tanY };

    Vector4f posZ = transformMatrix * tri.z.position;
    Vector4f uvZ = tri.z.uvCoord;
    Vector4f normZ = transformMatrix * tri.z.normal;
    Vector4f binZ = transformMatrix * tri.z.binormal;
    Vector4f tanZ = transformMatrix * tri.z.tangent;
    ComplexVertex vertexZ = ComplexVertex{ posZ, uvZ, normZ, binZ, tanZ };

    outNewMesh.m_vertexArray.emplace_back(Triangle(vertexX, vertexY, vertexZ));
    outNewMesh.m_indexArray.push_back(indexCount++);
    outNewMesh.m_indexArray.push_back(indexCount++);
    outNewMesh.m_indexArray.push_back(indexCount++);
  }

  auto& graphicsApi = GraphicsApi::instance();
  if (!outNewMesh.m_vertexData) {
    outNewMesh.m_vertexData = graphicsApi.createVertexBufferPtr();
  }
  if (!outNewMesh.m_indexData) {
    outNewMesh.m_indexData = graphicsApi.createIndexBufferPtr();
  }
  outNewMesh.m_vertexData->initData(
    outNewMesh.m_vertexArray.size() * sizeof(ComplexVertex) * 3,
    sizeof(ComplexVertex),
    reinterpret_cast<const Byte*>(outNewMesh.m_vertexArray.data()));
  outNewMesh.m_indexData->initData(
    outNewMesh.m_indexArray.size() * sizeof(uint32),
    sizeof(uint32),
    reinterpret_cast<const Byte*>(outNewMesh.m_indexArray.data()));


  outNewMesh.m_indexCount = outNewMesh.m_indexArray.size();
}
}