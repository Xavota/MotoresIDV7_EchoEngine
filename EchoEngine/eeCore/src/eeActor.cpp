#include "eeActor.h"
#include "eeCTransform.h"

namespace eeEngineSDK {
void
Actor::init(String name)
{
  m_name = name;
  if (!getTransform()) {
    SIZE_T cmpIndex = m_pComponents.size();
    m_pComponents.push_back(MemoryManager::instance().newPtr<CTransform>());
    m_pComponents[cmpIndex]->init(shared_from_this());
  }
}
void
Actor::update()
{
  for (auto& cmp : m_pComponents) {
    if (cmp->getActive())
      cmp->update();
  }
}
void
Actor::destroy()
{
  m_pComponents.clear();
  m_pChilds.clear();
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
Actor::attachTo(SPtr<Actor> pParent)
{
  if (m_pParent) {
    SIZE_T childsSize = m_pParent->m_pChilds.size();
    for (SIZE_T i = 0; i < childsSize; ++i) {
      if (m_pParent->m_pChilds[i]->m_name == m_name) {
        m_pParent->m_pChilds.erase(m_pParent->m_pChilds.begin() + i);
        break;
      }
    }
  }

  m_pParent = pParent;
  EE_NO_EXIST_RETURN(m_pParent);

  m_pParent->m_pChilds.push_back(shared_from_this());

  if (m_pParent->getTransform() && getTransform()) {
    getTransform()->attatchTo(m_pParent->getTransform());
  }
}
SPtr<CTransform>
Actor::getTransform()
{
  return getComponent<CTransform>();
}
}