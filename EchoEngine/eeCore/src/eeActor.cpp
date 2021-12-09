#include "eeActor.h"
#include "eeCTransform.h"

namespace eeEngineSDK {
void
Actor::init(String name)
{
  m_name = name;
  if (!getTransform())
  {
    int32 cmpIndex = static_cast<int32>(m_components.size());
    m_components.push_back(MemoryManager::instance().newPtr<CTransform>());
    m_components[cmpIndex]->init(shared_from_this());
  }
}
void
Actor::update()
{
  for (SPtr<Component> cmp : m_components)
  {
    if (cmp->getActive())
      cmp->update();
  }
}
void
Actor::destroy()
{
  m_components.clear();
  m_childs.clear();
}
bool
Actor::isActive()
{
  return m_active;
}
void
Actor::setActive(bool active)
{
  m_active = active;
}
void
Actor::attachTo(SPtr<Actor> parent)
{
  if (m_parent)
  {
    uint32 childsSize = static_cast<uint32>(m_parent->m_childs.size());
    for (uint32 i = 0; i < childsSize; ++i)
    {
      if (m_parent->m_childs[i]->m_name == m_name)
      {
        m_parent->m_childs.erase(m_parent->m_childs.begin() + i);
        break;
      }
    }
  }

  m_parent = parent;
  EE_NO_EXIST_RETURN(m_parent);

  m_parent->m_childs.push_back(shared_from_this());

  if (m_parent->getTransform() && getTransform())
  {
    getTransform()->attatchTo(m_parent->getTransform());
  }
}
SPtr<CTransform>
Actor::getTransform()
{
  return getComponent<CTransform>();
}
}