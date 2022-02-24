/************************************************************************/
/**
 * @file eeMemoryManager.h
 * @author Diego Castellanos
 * @date 03/12/21
 * @brief
 * For managing the memory allocation and release.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eeModule.h"

namespace eeEngineSDK{
/**
 * @brief
 * For managing the memory allocation and release.
 */
class EE_UTILITY_EXPORT MemoryManager : public Module<MemoryManager>
{
 public:
  /**
   * @brief
   * The default constructor.
   */
  MemoryManager() = default;
  /**
   * @brief
   * The default destructor.
   */
  ~MemoryManager() = default;

  /**
   * @brief
   * Creates a smart ptr.
   *
   * @description
   * Creates a new smart pointer of the template class.
   *
   * @param _Args
   * The arguments of the constructor for the object.
   *
   * @return
   * The instance of the new SPtr.
   */
  template<class T, class... _Types>
  FORCEINLINE SPtr<T>
  newPtr(_Types&&... _Args);

  /**
   * @brief
   * Reinterpret a smart ptr.
   *
   * @description
   * Reinterprets a SPtr changing it for other type of class, indicated in the
   * template class.
   *
   * @param ptr
   * The SPtr to reinterpret.
   *
   * @return
   * The instance of a SPtr reinterpreted.
   */
  template<class T, class U>
  FORCEINLINE SPtr<T>
  reinterpretPtr(SPtr<U> ptr);

  /**
   * @brief
   * Releases the memory.
   *
   * @description
   * Releases the memory of certain types of classes.
   *
   * @param ptr
   * The object to be released.
   *
   * @return
   * True if it succeeded to release.
   */
  template<class T>
  FORCEINLINE bool
  safeRelease(SPtr<T> ptr);

  /**
   * @brief
   * Releases the memory.
   *
   * @description
   * Releases the memory of a raw pointer.
   *
   * @param ptr
   * The object to be released.
   *
   * @return
   * True if it succeeded to release.
   */
  template<class T>
  FORCEINLINE bool
  rawSafeRelease(T** ptr);

 private:
};
template<class T, class... _Types>
FORCEINLINE SPtr<T>
MemoryManager::newPtr(_Types&&... _Args)
{
  return std::make_shared<T>(std::forward<_Types>(_Args)...);
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
  if (ptr) {
    ptr->release();
    return true;
  }
  return false;
}
template<class T>
inline bool MemoryManager::rawSafeRelease(T** ptr)
{
  if (*ptr)
  {
    delete *ptr;
    *ptr = nullptr;
    return true;
  }
  return false;
}
}
