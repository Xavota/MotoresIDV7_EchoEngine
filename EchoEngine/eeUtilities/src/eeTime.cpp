#include "eeTime.h"

namespace eeEngineSDK {
Time::Time()
{
  m_start = std::chrono::high_resolution_clock::now();
}
float
Time::getDeltaTime()
{
  return m_deltaTime;
}
void
Time::update()
{
  auto end = std::chrono::high_resolution_clock::now();
  m_deltaTime = std::chrono::duration<float>(end - m_start).count();
  m_start = std::chrono::high_resolution_clock::now();
}
}
