/************************************************************************/
/**
 * @file eeInput.h
 * @author Diego Castellanos
 * @date 16/11/21
 * @brief
 * The input manager for the api.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include <memory>
#include "eePrerequisitesCore.h"
#include "eeComponent.h"

#include <eeMemoryManager.h>

namespace eeEngineSDK{
class EE_CORE_EXPORT Actor : public EnableSPtrFromThis<Actor>
{
 public:
  Actor(String name);
  ~Actor() = default;

  void
  init();

  virtual void
  update();

  template <class T>
  FORCEINLINE void
  addComponent();

  template <class T>
  FORCEINLINE SPtr<T>
  getComponent();

  void
  destroy();

  bool
  isActive();
  void
  setActive(bool active);

  void
  attachTo(SPtr<Actor> parent);

 private:
  Vector<SPtr<Component>> m_components;

  Vector<SPtr<Actor>> m_childs;

  SPtr<Actor> m_parent = nullptr;

  bool m_active = true;

  String m_name;
};
template<class T>
FORCEINLINE void
Actor::addComponent()
{
  m_components.push_back(MemoryManager::instance().newPtr<T>());
}
template<class T>
inline SPtr<T> Actor::getComponent()
{
  uint32 compCount = m_components.size();
  for (uint32 i = 0; i != compCount; ++i)
  {
    if (m_components[i]->getType() == T::CmpType)
    {
      return MemoryManager::instance().reinterpretPtr<T>(m_components[i]);
    }
  }
  return nullptr;
}
}

