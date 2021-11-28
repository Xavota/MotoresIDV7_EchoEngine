#include "eeActor.h"
#include "eeCTransform.h"

namespace eeEngineSDK {
Actor::Actor(String name)
{
  m_name = name;
}
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
    cmp->update(shared_from_this());
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
void Actor::attachTo(SPtr<Actor> parent)
{
  if (m_parent)
  {
    int32 childsSize = m_parent->m_childs.size();
    for (int i = 0; i < childsSize; ++i)
    {
      if (m_parent->m_childs[i]->m_name == m_name)
      {
        m_parent->m_childs.erase(m_parent->m_childs.begin() + i);
        break;
      }
    }
  }

  m_parent = parent;
  m_parent->m_childs.push_back(shared_from_this());

  if (m_parent->getComponent<CTransform>() && getComponent<CTransform>())
  {
    getComponent<CTransform>()->attatchTo(m_parent->getComponent<CTransform>());
  }
}
}