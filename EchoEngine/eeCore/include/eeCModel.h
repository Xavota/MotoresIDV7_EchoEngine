/************************************************************************/
/**
 * @file eeCModel.h
 * @author Diego Castellanos
 * @date 18/11/21
 * @brief
 * The model component.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include <eeSphere.h>
#include <eeBox.h>
#include "eeComponent.h"

namespace eeEngineSDK{
/**
 * @brief
 * The Model component.
 */
class EE_CORE_EXPORT CModel : public Component
{
 public:
  /**
   * @brief
   * The enum for identifying the component type.
   */
  enum { CmpType = eCOMPONENT_TYPE::kModel };

  /**
   * @brief
   * Default constructor.
   */
  CModel() = default;
  /**
   * @brief
   * Default destructor.
   */
  ~CModel() = default;

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
  int32
  getType() override
  {
    return CmpType;
  }

  /**
   * @brief
   * Updates the model logic.
   *
   * @description
   * Updates the model's bounds with the transforms of the actor.
   */
  void
  update() override;

  /**
   * @brief
   * Setter for the model resource.
   *
   * @description
   * Sets the model resource for the component.
   *
   * @param model
   * The new model resource.
   */
  virtual void
  setModel(SPtr<Model> model);

  /**
   * @brief
   * Getter for the model resource.
   *
   * @description
   * Gets the model resource of the component.
   *
   * @return
   * The model resource of the component.
   */
  virtual SPtr<Model>
  getModel();

  /**
   * @brief
   * Getter for the bounding sphere.
   *
   * @description
   * Returns the bounding sphere surrounding the model.
   *
   * @return
   * The bounding sphere surrounding the model.
   */
  const Sphere&
  getBoundingSphere();
  /**
   * @brief
   * Getter for the bounding box.
   *
   * @description
   * Returns the bounding box surrounding the model.
   *
   * @return
   * The bounding box surrounding the model.
   */
  const BoxAAB&
  getBoundingBox();

 private:
  /**
   * The model resource.
   */
  SPtr<Model> m_model;

  /**
   * The bounding sphere.
   */
  Sphere m_boundSphere;
  /**
   * The original radius of the bounding sphere. For recalculation.
   */
  float m_originRadious = 0.0f;
  /**
   * The bounding box.
   */
  BoxAAB m_boundBox;
};
}
