/************************************************************************/
/**
 * @file eeScene.h
 * @author Diego Castellanos
 * @date 24/11/21
 * @brief
 * The scene, contains the actors graph.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK{
namespace RENDER_ACTOR_FLAGS {
enum E : uint8{
  kNone = 0,
  kStaticMesh = 1,
  kSkeletalMesh = 2
};
}
/**
 * @brief
 * The scene, contains the actors graph.
 */
class EE_CORE_EXPORT Scene
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  Scene() = default;
  /**
   * @brief
   * Default destructor.
   */
  ~Scene() = default;

  /**
   * @brief
   * Gets all actors of the scene inside the camera.
   *
   * @description
   * Gets all actors of the scene that are inside the frustum of the camera and
   * have a model and a render component.
   *
   * @param camera
   * The camera to check the frustum.
   * @param flags
   * Flags for the type of actor needed.
   *
   * @return
   * All actors inside.
   */
  Vector<SPtr<Actor>>
  getAllRenderableActorsInside(SPtr<CCamera> camera,
                               RENDER_ACTOR_FLAGS::E flags);
  /**
   * @brief
   * Gets all actors of the scene inside the camera.
   *
   * @description
   * Gets all actors of the scene that are inside the frustum of the camera and
   * have a model and a render component.
   *
   * @param camera
   * The camera to check the frustum.
   * @param flags
   * Flags for the type of actor needed.
   * @param outRenderActors
   * The actors that can be rendered.
   */
  void
  getAllRenderableActorsInsideHelper(SPtr<CCamera> camera,
                                     Vector<SPtr<Actor>> actors,
                                     RENDER_ACTOR_FLAGS::E flags,
                                     Vector<SPtr<Actor>>& outRenderActors);

  /**
   * @brief
   * Adds a new actor to the scene.
   *
   * @description
   * Adds a new actor to the scene and initializes it, with a name to identify
   * it.
   *
   * @param name
   * The name to identify the actor.
   *
   * @return
   * The ptr to the new actor.
   */
  SPtr<Actor>
  addActor(String name);
  /**
   * @brief
   * Gets an actor by its name.
   *
   * @description
   * Returns an actor by its identifying name.
   *
   * @param name
   * The name of the looking actor.
   *
   * @return
   * The looked actor, nullptr if couldn't found it.
   */
  SPtr<Actor>
  getActor(String name);
  
  /**
   * @brief
   * Sets an actor child.
   *
   * @description
   * Sets an actor to be the child of another.
   *
   * @param parentName
   * The name of the parent actor.
   * @param childName
   * The name of the child actor.
   *
   * @return
   * True if it could do it.
   */
  bool
  setActorChild(String parentName, String childName);

  /**
   * @brief
   * Initializes the scene.
   *
   * @description
   * Initializes everything the scene needs.
   */
  void
  init();

  /**
   * @brief
   * Updates the scene.
   *
   * @description
   * Updates the scene and all the active actors.
   */
  void
  update();

  /**
   * @brief
   * Releases the memory.
   *
   * @description
   * Cleans all the allocated memory.
   */
  void
  release();

  /**
   * @brief
   * Gets if the scene is active.
   *
   * @description
   * Returns true if the scene is active to be updated and rendered.
   *
   * @return
   * True if the scene is active to be updated and rendered.
   */
  bool
  isActive();
  /**
   * @brief
   * Sets if the scene is active.
   *
   * @description
   * Sets true if the scene is active to be updated and rendered.
   *
   * @param active
   * True if the scene is active to be updated and rendered.
   */
  void
  setActive(bool active);

  /**
   * @brief
   * Gets if the scene is off active.
   *
   * @description
   * Returns true if the scene is active to be updated but not rendered.
   *
   * @return
   * True if the scene is active to be updated but not rendered.
   */
  bool
  isOffActive();
  /**
   * @brief
   * Sets if the scene is off active.
   *
   * @description
   * Sets true if the scene is active to be updated but not rendered.
   *
   * @param active
   * True if the scene is active to be updated but not rendered.
   */
  void
  setOffActive(bool active);
  
  /**
   * @brief
   * Gets all the actors.
   *
   * @description
   * Returns the maps of actors.
   *
   * @return
   * All actors.
   */
  const Map<String, SPtr<Actor>>&
  getAllActors()
  {
    return m_actors;
  }
  /**
   * @brief
   * Gets all the actors.
   *
   * @description
   * Returns an vector of all the actors, with out its names.
   *
   * @return
   * All actors.
   */
  void
  getAllActorsVector(Vector<SPtr<Actor>>& acts)
  {
    for (auto& act : m_actors) {
      acts.emplace_back(act.second);
    }
  }

 private:
  /**
   * The actors in the scene.
   */
  Map<String, SPtr<Actor>> m_actors;

  /**
   * If the scene is active to be updated and rendered.
   */
  bool m_active = false;
  /**
   * If the scene is active to be updated but not rendered.
   */
  bool m_offActive = false;
};
}
