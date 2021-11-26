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
void Actor::AtttchTo(SPtr<Actor> parent)
{
  if (!m_parent)
  {
    m_parent = parent;
    m_parent->m_childs.push_back(shared_from_this());
  }
  else
  {
    int32 childsSize = m_parent->m_childs.size();
    for (int i = 0; i < childsSize; ++i)
    {
      if (m_parent->m_childs[i]->m_name == m_name)
      {
        m_parent->m_childs.erase(m_parent->m_childs.begin() + i);
      }
    }

    m_parent = parent;
    m_parent->m_childs.push_back(shared_from_this());
  }
}
}