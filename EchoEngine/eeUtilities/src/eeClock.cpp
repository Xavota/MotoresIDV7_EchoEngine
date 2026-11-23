#include "eeClock.h"

namespace eeEngineSDK {
Clock::Clock()
{
  m_start = std::chrono::high_resolution_clock::now();
}
float
Clock::geTimeElapsed()
{
  return m_deltaTime;
}
void
Clock::update()
{
  auto end = std::chrono::high_resolution_clock::now();
  m_deltaTime = std::chrono::duration<float>(end - m_start).count();
  m_start = std::chrono::high_resolution_clock::now();
}
float
Clock::restart()
{
  m_start = std::chrono::high_resolution_clock::now();
  float returnDeltaTime = m_deltaTime;
  m_deltaTime = 0.0f;
  return returnDeltaTime;
}
}