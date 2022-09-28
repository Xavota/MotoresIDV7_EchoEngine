/************************************************************************/
/**
 * @file eeOmniverseApi.h
 * @author Diego Castellanos
 * @date 08/09/22
 * @brief
 * The omniverse class for the functions needed to connect, edit and all.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerrequisitesOmniverse.h"

#include <eeOmniverseManager.h>

#include <OmniClient.h>
#include <OmniUsdLive.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/metrics.h>
#include <pxr/base/gf/matrix4f.h>
#include <pxr/base/gf/rotation.h>
#include <pxr/base/gf/vec2f.h>
#include <pxr/usd/usdUtils/pipeline.h>
#include <pxr/usd/usdUtils/sparseValueWriter.h>
#include <pxr/usd/usdShade/material.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usdGeom/primvar.h>
#include <pxr/usd/usdShade/input.h>
#include <pxr/usd/usdShade/output.h>
#include <pxr/usd/usdGeom/xform.h>
#include <pxr/usd/usdGeom/cube.h>
#include <pxr/usd/usdShade/materialBindingAPI.h>
#include <pxr/usd/usdLux/distantLight.h>
#include <pxr/usd/usdLux/domeLight.h>
#include <pxr/usd/usdShade/shader.h>
#include <pxr/usd/usd/modelAPI.h>

#include <eeTransform.h>

PXR_NAMESPACE_USING_DIRECTIVE


namespace eeEngineSDK {
/**
 * @brief
 * The omniverse class for the functions needed to connect, edit and all.
 */
class EE_OMNIVERSE_EXPORT OmniverseApi : public OmniverseManager
{
 public:
  /**
   * @brief
   * Default constructor
   */
  OmniverseApi() = default;
  /**
   * @brief
   * Default destructor.
   */
  ~OmniverseApi();

  /**
  * @brief
  * Starts the omniverse application.
  *
  * @description
  * Starts the omniverse application.
  */
  bool
  init(bool doLiveEdit) override;

  /**
  * @brief
  * Stops the omniverse application.
  *
  * @description
  * Stops the omniverse application.
  */
  void
  destroy() override;

  /**
  * @brief
  * Creates a stage .usd file.
  *
  * @description
  * Creates a stage file, .usd file, and loads it to use.
  *
  * @param stageUrl
  * The url of the new stage.
  */
  void
  createStage(const String& stageUrl) override;
  /**
  * @brief
  * Opens a stage .usd file.
  *
  * @description
  * Opens a stage file, .usd file, and loads it to use.
  *
  * @param stageUrl
  * The url of the new stage.
  */
  void
  openStage(const String& stageUrl) override;
  /**
  * @brief
  * Closes the active stage.
  *
  * @description
  * Closes the active stage.
  */
  void
  closeStage() override;
  /**
  * @brief
  * Saves the active stage to the .usd file.
  *
  * @description
  * Saves the active stage to the .usd file.
  */
  void
  saveStage() override;

  /**
  * @brief
  * Gets an absolute path for omniverse.
  *
  * @description
  * Returns the user local folder path for the omniverse storage.
  *
  * @return
  * The user local folder path for the omniverse storage.
  */
  String
  getUserLocalPath() override;

  /**
  * @brief
  * Transform the scene graph into a usd stage.
  *
  * @description
  * Inserts everything in the scene into the usd stage file.
  *
  * @param scenegraph
  * The scene that will be inserted in the stage.
  *
  * @return
  * If it succeeded on inserting the scene on the stage.
  */
  bool
  setScenegraphOnStage(WPtr<Scene> scenegraph) override;
  /**
  * @brief
  * Returns the scenegraph inside the stage.
  *
  * @description
  * Inserts everything in the stage file into the scene.
  *
  * @param scenegraph
  * The scene that will get the stage.
  */
  void
  getScenegraphFromStage(WPtr<Scene> scenegraph) override;


 private:
  /**
  * Globals for Omniverse Connection and base Stage
  */
  UsdStageRefPtr m_stage;
  /**
  * The root path of the stage
  */
  SdfPath m_rootPrimPath;
  /**
  * The scenegraph that is currently using.
  */
  WPtr<Scene> m_openedScenegraph;
  /**
  * The name of the stage file, which is the name of the active scene.
  */
  String m_stageFileName;
};
}