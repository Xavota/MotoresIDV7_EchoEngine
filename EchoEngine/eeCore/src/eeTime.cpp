#include "eeTime.h"

namespace eeEngineSDK{
float
Time::getDeltaTime()
{
  return m_deltaTime;
}
void
Time::updateDeltaTime(float dt)
{
  m_deltaTime = dt;
}
}