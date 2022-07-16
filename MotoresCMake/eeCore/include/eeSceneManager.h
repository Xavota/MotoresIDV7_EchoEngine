/************************************************************************/
/**
 * @file eeSceneManager.h
 * @author Diego Castellanos
 * @date 24/11/21
 * @brief
 * The manager for all the scenes.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeModule.h>

#include "eeScene.h"
#include "eeOctree.h"

namespace eeEngineSDK{
/**
 * @brief
 * The manager for all the scenes.
 */
class EE_CORE_EXPORT SceneManager : public Module<SceneManager>
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  SceneManager() = default;
  /**
   * @brief
   * Default destructor.
   */
  ~SceneManager();

  /**
   * @brief
   * Updates the manager.
   *
   * @description
   * Updates the manager and all the scenes.
   */
  void
  update();

  /**
   * @brief
   * Adds a new scene.
   *
   * @description
   * Adds and initializes a new scene with its identifying name.
   *
   * @param name
   * The identifying name of the new scene.
   *
   * @return
   * The ptr to the new scene.
   */
  SPtr<Scene>
  addScene(const String& name);
  /**
   * @brief
   * Gets a scene.
   *
   * @description
   * Gets scene with its identifying name.
   *
   * @param name
   * The identifying name of the looking scene.
   *
   * @return
   * The ptr to the scene, nullptr if not found.
   */
  SPtr<Scene>
  getScene(const String& name);

  /**
   * @brief
   * Gets all actors of all active scenes inside the camera.
   *
   * @description
   * Gets all actors of all active scenes that are inside the frustum of the
   * camera and have a model and a render component.
   *
   * @param camera
   * The camera to check the frustum.
   *
   * @return
   * All actors inside.
   */
  Vector<SPtr<Actor>>
  getAllRenderableActorsInside(SPtr<CCamera> camera,
                       RENDER_ACTOR_FLAGS::E flags = RENDER_ACTOR_FLAGS::kNone);

  /**
   * @brief
   * Gets all scenes.
   *
   * @description
   * Returns the maps of scenes.
   *
   * @return
   * All scenes.
   */
  FORCEINLINE const Map<String, SPtr<Scene>>&
  getAllScenes()
  {
    return m_scenes;
  }
  /**
   * @brief
   * Gets all actors with the given components.
   *
   * @description
   * Returns an array of actors that have at least one component on the flags
   * list.
   * 
   * @param flags
   * The component list in form of flags.
   *
   * @return
   * An array of actors that have at least one component on the flags list.
   */
  Vector<SPtr<Actor>>
  getAllActorsByComponentFlags(uint32 flags);

  /**
   * @brief
   * Partitions the scenes.
   *
   * @description
   * Partitions the scenes using an Octree to make separate the triangles in
   * nodes.
   */
  void
  partitionScenes();
  /**
   * @brief
   * Getter for the meshes generated by the partition of the scene.
   *
   * @description
   * Returns the meshes that where created by the partition of the scenes.
   * 
   * @param meshesVec
   * The output vector of meshes.
   */
  void
  getPartitionedSceneMeshes(Vector<SPtr<StaticMesh>>& outMeshesVec);


 private:
  /**
   * All the scenes.
   */
  Map<String, SPtr<Scene>> m_scenes;
  /**
   * The partition of the space on the scene.
   */
  Octree m_spacePartition;
};
}