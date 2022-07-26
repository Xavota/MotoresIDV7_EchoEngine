/************************************************************************/
/**
 * @file eeComponent.h
 * @author Diego Castellanos
 * @date 16/11/21
 * @brief
 * The component class, for the actor-component pattern.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK{
/**
 * @brief
 * Types of components.
 */
namespace eCOMPONENT_TYPE {
enum E : uint32
{
  kNone = 0,
  kTransform = 1,
  kStaticMesh = 2,
  kRender = 4,
  kCamera = 8,
  kSkeletalMesh = 16,
  kAnimation = 32,
  kBounds = 64,
  kLight = 128
};
}

/**
 * @brief
 * The component class, for the actor-component pattern.
 */
class EE_CORE_EXPORT Component : public EnableSPtrFromThis<Component>
{
public:
  /**
   * @brief
   * The enum for identifying the component type.
   */
  enum { CmpType = eCOMPONENT_TYPE::kNone };

  /**
   * @brief
   * Default constructor.
   */
  Component() = default;
  /**
   * @brief
   * Default destructor.
   */
  ~Component() = default;

  /**
   * @brief
   * Returns the component type.
   *
   * @description
   * Returns the component type.
   *
   * @return
   * The component type.
   */
  FORCEINLINE virtual int32
  getType()
  {
    return CmpType;
  }

  /**
   * @brief
   * Updates the component logic.
   *
   * @description
   * Updates the everything the component needs.
   */
  virtual void
  update() {}

  /**
   * @brief
   * Get if the component is active.
   *
   * @description
   * Returns true if the component is active and can update.
   *
   * @return
   * If the component is active.
   */
  FORCEINLINE virtual bool
  getActive()
  {
    return m_active;
  }
  /**
   * @brief
   * Sets if the component is active.
   *
   * @description
   * Set if the actor can update and do stuff.
   *
   * @param active
   * If the actor can update and do stuff.
   */
  FORCEINLINE virtual void
  setActive(bool active)
  {
    m_active = active;
  }

  /**
   * @brief
   * Gets the actor to witch is attached.
   *
   * @description
   * Returns the actor to witch the component is attached.
   *
   * @return
   * The actor to witch the component is attached.
   */
  FORCEINLINE virtual WPtr<Actor>
  getActor()
  {
    return m_actor;
  }

 protected:
  /**
   * The actor to witch it's attached.
   */
  WPtr<Actor> m_actor;

  /**
   * If the actor can update and do stuff.
   */
  bool m_active = true;

 private:
  friend class Actor;
  /**
   * @brief
   * Initialize the component.
   *
   * @description
   * Initializes all the things in the component and tells it the actor attached
   * to.
   *
   * @param act
   * The actor attached to.
   */
  void
  init(WPtr<Actor> act)
  {
    m_actor = act;
  }
};
}