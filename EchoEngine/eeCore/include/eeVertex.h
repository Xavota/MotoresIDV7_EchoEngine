/************************************************************************/
/**
 * @file eeSimplexVertex.h
 * @author Diego Castellanos
 * @date 05/10/21
 * @brief
 * The pixel shader for the graphic memory to paint every pixel.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include "eeVector2.h"
#include "eeVector3.h"
#include "eeVector4.h"

namespace eeEngineSDK {
/**
 * @brief
 * The simplest vertex info, just contains a position.
 */
struct SimplexVertex
{
  /**
   * The position of the vertex.
   */
  Vector4f position = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
};
/**
 * @brief
 * A simpler vertex info, contains a position, uvCoord and normal.
 */
struct SimpleVertex
{
  /**
   * The position of the vertex.
   */
  Vector4f position = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
  /**
   * The texture coordinates of the vertex.
   */
  Vector4f uvCoord = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
  /**
   * The normal direction of the vertex.
   */
  Vector4f normal = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
};
/**
 * @brief
 * A complex vertex info, contains a position, uvCoord, normal, binormal and
 * tangent.
 */
struct ComplexVertex
{
  /**
   * The position of the vertex.
   */
  Vector4f position = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
  /**
   * The texture coordinates of the vertex.
   */
  Vector4f uvCoord = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
  /**
   * The normal direction of the vertex.
   */
  Vector4f normal = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);

  /**
   * The binormal direction of the vertex.
   */
  Vector4f binormal = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
  /**
   * The tangent direction of the vertex.
   */
  Vector4f tangent = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
};
/**
 * @brief
 * A simple vertex info with animation info, contains a position, uvCoord,
 * normal, binormal, tangent, and bones info.
 */
struct SimpleAnimVertex
{
  /**
   * The position of the vertex.
   */
  Vector4f position = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
  /**
   * The texture coordinates of the vertex.
   */
  Vector4f uvCoord = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
  /**
   * The normal direction of the vertex.
   */
  Vector4f normal = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);

  /**
   * The indices of the bones that affects the vertex.
   */
  Vector4i boneIndices = Vector4i(0, 0, 0, 0);
  /**
   * The weights for the bones that affects the vertex.
   */
  Vector4f boneWeights = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
};
/**
 * @brief
 * A simple vertex info with animation info of any size, contains a position,
 * uvCoord, normal, binormal, tangent, and bones info.
 */
template <uint32 size>
struct SimpleBigAnimVertex
{
  /**
   * The position of the vertex.
   */
  Vector4f position = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
  /**
   * The texture coordinates of the vertex.
   */
  Vector4f uvCoord = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);;
  /**
   * The normal direction of the vertex.
   */
  Vector4f normal = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);;

  /**
   * The indices of the bones that affects the vertex.
   */
  int32 boneIndices[size];
  /**
   * The weights for the bones that affects the vertex.
   */
  float boneWeights[size];
};
/**
 * @brief
 * A complex vertex info with animation info, contains a position, uvCoord,
 * normal, binormal, tangent, and bones info.
 */
struct ComplexAnimVertex
{
  /**
   * The position of the vertex.
   */
  Vector4f position = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);;
  /**
   * The texture coordinates of the vertex.
   */
  Vector4f uvCoord = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);;
  /**
   * The normal direction of the vertex.
   */
  Vector4f normal = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);;

  /**
   * The binormal direction of the vertex.
   */
  Vector4f binormal = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
  /**
   * The tangent direction of the vertex.
   */
  Vector4f tangent = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);

  /**
   * The indices of the bones that affects the vertex.
   */
  Vector4i boneIndices = Vector4i(0, 0, 0, 0);
  /**
   * The weights for the bones that affects the vertex.
   */
  Vector4f boneWeights = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
};
/**
 * @brief
 * A complex vertex info with animation info of any size, contains a position,
 * uvCoord, normal, binormal, tangent, and bones info.
 */
template <uint32 size>
struct ComplexBigAnimVertex
{
  /**
   * The position of the vertex.
   */
  Vector4f position = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
  /**
   * The texture coordinates of the vertex.
   */
  Vector4f uvCoord = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
  /**
   * The normal direction of the vertex.
   */
  Vector4f normal = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);

  /**
   * The binormal direction of the vertex.
   */
  Vector4f binormal = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
  /**
   * The tangent direction of the vertex.
   */
  Vector4f tangent = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);

  /**
   * The indices of the bones that affects the vertex.
   */
  int32 boneIndices[size];
  /**
   * The weights for the bones that affects the vertex.
   */
  float boneWeights[size];
};
}
