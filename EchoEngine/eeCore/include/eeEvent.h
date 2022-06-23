/************************************************************************/
/**
 * @file eeGamepadDevice.h
 * @author Diego Castellanos
 * @date 22/06/22
 * @brief
 * The event class to store the events for all the engine.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
/**
 * @brief
 * The event class to store the events for all the engine.
 */
template<class RetType, class... Args>
class Event
{
 public:
  /**
   * @brief
   * Default constructor
   */
  Event();
  /**
   * @brief
   * Default destructor
   */
  ~Event() = default;

  /**
   * @brief
   * Subscribes a function to this event.
   *
   * @description
   * Subscribes the given function this event so it will be called when this
   * this event is triggered.
   * 
   * @param func
   * The function to be subscribed. It must have the same return type and
   * parameters as the event.
   *
   * @return
   * Weather or not the function successfully subscribed.
   */
  FORCEINLINE void
  subscribeFunction(Function<RetType(Args...)> func)  
  {
    m_subsFuncs.push_back(func);
  }

  /**
   * @brief
   * Clear all the subscribed functions.
   *
   * @description
   * Remove all the functions that have been subscribed to this event.
   */
  FORCEINLINE void
  clearSubscribedFunctions()
  {
    m_subsFuncs.clear();
  }
  
  /**
   * @brief
   * Triggers the event.
   *
   * @description
   * Executes every function that have been subscribed to this event with the
   * given arguments.
   * 
   * @param argsVals
   * The argument values for the functions the will be triggered.
   */
  FORCEINLINE void
  triggerEvent(Args... argsVals)
  {
    for (auto& fu : m_subsFuncs) {
      fu(forward<Args>(argsVals));
    }
  }


 private:
  /**
   * The functions subscribed to this event.
   */
  Vector<Function<RetType(Args...)>> m_subsFuncs;
};
}
