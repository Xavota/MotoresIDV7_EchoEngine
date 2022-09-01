#include "eeActor.h"
#include "eeCTransform.h"

namespace eeEngineSDK {
void
Actor::init(const String& name)
{
  m_name = name;
  if (getTransform().expired()) {
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
  //m_pChilds.clear();
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
//void
//Actor::attachTo(const SPtr<Actor> pParent)
//{
//  if (!m_pParent.expired()) {
//    auto spParent = m_pParent.lock();
//    SIZE_T childsSize = spParent->m_pChilds.size();
//    for (SIZE_T i = 0; i < childsSize; ++i) {
//      if (spParent->m_pChilds[i]->m_name == m_name) {
//        spParent->m_pChilds.erase(spParent->m_pChilds.begin() + i);
//        break;
//      }
//    }
//  }
//
//  m_pParent = pParent;
//  if (m_pParent.expired()) return;
//  auto spParent = m_pParent.lock();
//
//  spParent->m_pChilds.push_back(shared_from_this());
//
//  if (!spParent->getTransform().expired() && !getTransform().expired()) {
//    getTransform().lock()->attatchTo(spParent->getTransform());
//  }
//}
WPtr<CTransform>
Actor::getTransform()
{
  return getComponent<CTransform>();
}
}