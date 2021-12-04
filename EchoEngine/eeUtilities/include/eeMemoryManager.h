/************************************************************************/
/**
 * @file eeInput.h
 * @author Diego Castellanos
 * @date 03/12/21
 * @brief
 * The input manager for the api.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesUtilities.h"
#include "eeModule.h"

namespace eeEngineSDK{
class EE_UTILITY_EXPORT MemoryManager : public Module<MemoryManager>
{
 public:
  MemoryManager() = default;
  ~MemoryManager() = default;

  template<class T>
  FORCEINLINE SPtr<T>
  newPtr();

  template<class T, class U>
  FORCEINLINE SPtr<T>
  reinterpretPtr(SPtr<U> ptr);

  template<class T>
  FORCEINLINE bool
  safeRelease(SPtr<T> ptr);

 private:
};
template<class T>
FORCEINLINE SPtr<T>
MemoryManager::newPtr()
{
  return std::make_shared<T>();
}
template<class T, class U>
FORCEINLINE SPtr<T>
MemoryManager::reinterpretPtr(SPtr<U> ptr)
{
  return std::reinterpret_pointer_cast<T>(ptr);
}
template<class T>
FORCEINLINE bool
MemoryManager::safeRelease(SPtr<T> ptr)
{
  if (ptr)
  {
    ptr->release();

    return true;
  }
  return false;
}
}
