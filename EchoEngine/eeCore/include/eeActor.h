/************************************************************************/
/**
 * @file eeActor.h
 * @author Diego Castellanos
 * @date 16/11/21
 * @brief
 * The Actor class, for the actor-component pattern.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include <memory>

#include <eeLogger.h>

#include "eePrerequisitesCore.h"
#include "eeComponent.h"

#include <eeMemoryManager.h>

namespace eeEngineSDK{
/**
 * @brief
 * The Actor class, for the actor-component pattern.
 */
class EE_CORE_EXPORT Actor : public EnableSPtrFromThis<Actor>
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  Actor() = default;
  /**
   * @brief
   * Default destructor.
   */
  ~Actor() = default;

  /**
   * @brief
   * Initializes the actor.
   *
   * @description
   * Initializes the actor, giving a name.
   *
   * @param name
   * The name of the actor
   */
  void
  init(const String& name);

  /**
   * @brief
   * Updates the actor logic.
   *
   * @description
   * Updates the actor and all of it components.
   */
  virtual void
  update();

  /**
   * @brief
   * Adds a new component.
   *
   * @description
   * Adds a component of the class of the template.
   */
  template <class T>
  FORCEINLINE WPtr<T>
  addComponent();

  /**
   * @brief
   * Gets a component if exists.
   *
   * @description
   * Gets a component of the class of the template if it exists.
   *
   * @return
   * The pointer to the component, nullptr if it doesn't exists.
   */
  template <class T>
  FORCEINLINE WPtr<T>
  getComponent();
  /**
   * @brief
   * Gets all the components.
   *
   * @description
   * Returns all the components that the actor has, including Transform.
   *
   * @return
   * All the components that the actor has, including Transform.
   */
  FORCEINLINE const Vector<SPtr<Component>>&
  getAllComponents()
  {
    return m_pComponents;
  }

  /**
   * @brief
   * Frees the memory.
   *
   * @description
   * Frees the memory allocated on the actor.
   */
  void
  destroy();

  /**
   * @brief
   * Checks if the actor is active.
   *
   * @description
   * Returns true if the actor is active on the scene.
   *
   * @return
   * Whether the actor is active or not.
   */
  bool
  isActive();
  /**
   * @brief
   * Set the actor activeness.
   *
   * @description
   * Sets if the actor is active or not.
   *
   * @param active
   * The new state of the actor. True if it's active.
   */
  void
  setActive(bool active);

  ///**
  // * @brief
  // * Attach to an actor.
  // *
  // * @description
  // * Attach the actor to a parent actor.
  // *
  // * @param parent
  // * The new parent actor, nullptr if no parent.
  // */
  //void
  //attachTo(const SPtr<Actor> pParent);
  ///**
  // * @brief
  // * Gets the parent.
  // *
  // * @description
  // * Returns the actor to witch it is attached to.
  // *
  // * @retunr
  // * The actor to witch it is attached to.
  // */
  //WPtr<Actor>
  //getParent()
  //{
  //  return m_pParent;
  //}

  /**
   * @brief
   * Gets the transform component.
   *
   * @description
   * Returns the transform component of the actor. To easy access.
   *
   * @return
   * The transform component.
   */
  WPtr<CTransform>
  getTransform();


  ///**
  // * @brief
  // * Gets the children.
  // *
  // * @description
  // * Returns the children attach to the actor.
  // *
  // * @return
  // * The transform component.
  // */
  //Vector<SPtr<Actor>>
  //getChildren()
  //{
  //  return m_pChilds;
  //}
  
  /**
   * @brief
   * Gets the actor name.
   *
   * @description
   * Returns the descriptive actor name.
   *
   * @return
   * The actor name.
   */
  String
  getName()
  {
    return m_name;
  }

 private:
  /**
   * The name of the actor.
   */
  String m_name;
  /**
   * If the actor is active or not.
   */
  bool m_active = true;

  /**
   * The list of components.
   */
  Vector<SPtr<Component>> m_pComponents;
};
template<typename T>
FORCEINLINE WPtr<T>
Actor::addComponent()
{
  auto& memoryMan = MemoryManager::instance();
  T c; // This is to disable warning "constant logic expression"
  if (c.getType() == eCOMPONENT_TYPE::kTransform) {
  auto& loggerMan = Logger::instance();
    loggerMan.consoleLog("Things can't be in more than one place, kido.");
    loggerMan.consoleLog("ERROR ADDING TRANSFORM COMPONENT TO ACTOR.");
    loggerMan.consoleLog("CANNOT ADD A TRANSFORM COMPONENT");
    return getComponent<T>();
  }
  SIZE_T cmpIndex = m_pComponents.size();
  m_pComponents.push_back(MemoryManager::instance().newPtr<T>());
  m_pComponents[cmpIndex]->init(shared_from_this());

  return memoryMan.reinterpretPtr<T>(m_pComponents[cmpIndex]);
}
template<typename T>
FORCEINLINE WPtr<T>
Actor::getComponent()
{
  auto& memoryMan = MemoryManager::instance();
  SIZE_T compCount = m_pComponents.size();
  for (uint32 i = 0; i != compCount; ++i) {
    if (m_pComponents[i]->getType() == T::CmpType) {
      return memoryMan.reinterpretPtr<T>(m_pComponents[i]);
    }
  }
  return WPtr<T>();
}
}

