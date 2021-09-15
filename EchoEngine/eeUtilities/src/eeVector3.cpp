#include "eeVector3.h"

namespace eeEngineSDK
{
  const Vector3f Vector3f::ZERO = Vector3f(0.0f, 0.0f, 0.0f);
  const Vector3f Vector3f::FORWARD = Vector3f(0.0f, 0.0f, 1.0f);
  const Vector3f Vector3f::RIGHT = Vector3f(1.0f, 0.0f, 0.0f);
  const Vector3f Vector3f::UP = Vector3f(0.0f, 1.0f, 0.0f);

  const Vector3i Vector3i::ZERO = Vector3i(0, 0, 0);
  const Vector3i Vector3i::FORWARD = Vector3i(0, 0, 1);
  const Vector3i Vector3i::RIGHT = Vector3i(1, 0, 0);
  const Vector3i Vector3i::UP = Vector3i(0, 1, 0);

  const Vector3u Vector3u::ZERO = Vector3u(0u, 0u, 0u);
  const Vector3u Vector3u::FORWARD = Vector3u(0u, 0u, 1u);
  const Vector3u Vector3u::RIGHT = Vector3u(1u, 0u, 0u);
  const Vector3u Vector3u::UP = Vector3u(0u, 1u, 0u);
}