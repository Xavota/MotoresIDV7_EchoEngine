#include "eeActor.h"
#include "eeCTransform.h"

namespace eeEngineSDK {
void
Actor::init()
{
  addComponent<CTransform>();
}
void
Actor::update()
{
  for (SPtr<Component> cmp : m_components)
  {
    cmp->update(this);
  }
}
void
Actor::destroy()
{
}
bool Actor::isActive()
{
  return m_active;
}
void Actor::setActive(bool active)
{
  m_active = active;
}
}