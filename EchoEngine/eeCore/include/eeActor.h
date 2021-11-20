#pragma once
#include <memory>
#include "eePrerequisitesCore.h"
#include "eeComponent.h"

namespace eeEngineSDK{
class EE_CORE_EXPORT Actor
{
 public:
  Actor() = default;
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

 private:
  Vector<SPtr<Component>> m_components;
};
template<class T>
FORCEINLINE void
Actor::addComponent()
{
  m_components.push_back(std::make_shared<T>());
}
template<class T>
inline SPtr<T> Actor::getComponent()
{
  uint32 compCount = m_components.size();
  for (uint32 i = 0; i != compCount; ++i)
  {
    if (m_components[i]->getType() == T::CmpType)
    {
      return std::reinterpret_pointer_cast<T>(m_components[i]);
    }
  }
  return nullptr;
}
}

