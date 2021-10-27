#pragma once
#include "eePrerequisitesCore.h"
#include "eeVector2.h"
#include "eeVector3.h"
#include "eeVector4.h"

namespace eeEngineSDK {
struct SimplexVertex
{
  Vector4f position;
};
struct SimpleVertex
{
  Vector3f position;
  Vector2f uvCoord;
  Vector3f normal;
};
struct ComplexVertex
{
  Vector3f position;
  Vector2f uvCoord;
  Vector3f normal;

  Vector3f binormal;
  Vector3f tangent;
};
struct SimpleAnimVertex
{
  Vector3f position;
  Vector2f uvCoord;
  Vector3f normal;

  Vector4i boneIndices;
  Vector4f boneWeights;
};
template <uint32 size>
struct SimpleBigAnimVertex
{
  Vector3f position;
  Vector2f uvCoord;
  Vector3f normal;

  int32 boneIndices[size];
  float boneWeights[size];
};
struct ComplexAnimVertex
{
  Vector3f position;
  Vector2f uvCoord;
  Vector3f normal;

  Vector3f binormal;
  Vector3f tangent;

  Vector4i boneIndices;
  Vector4f boneWeights;
};
template <uint32 size>
struct ComplexBigAnimVertex
{
  Vector3f position;
  Vector2f uvCoord;
  Vector3f normal;

  Vector3f binormal;
  Vector3f tangent;

  int32 boneIndices[size];
  float boneWeights[size];
};
}
