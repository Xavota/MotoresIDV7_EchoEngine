/************************************************************************/
/**
 * @file eeObject.h
 * @author Diego Castellanos
 * @date 08/10/21
 * @brief
 * The object to be rendered, contains a model and world transformations.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include "eeVector3.h"
#include "eeQuaternion.h"
#include "eeModel.h"

#include <eeMatrix4.h>

namespace eeEngineSDK {
/**
 * @brief
 * The object to be rendered, contains a model and world transformations.
 */
class EE_CORE_EXPORT Object
{
 public:
  /**
   * @brief
   * Default constructor
   */
  Object() = default;
  /**
   * @brief
   * Default destructor
   */
  virtual
  ~Object() = default;

  /**
   * @brief
   * Initializes the object.
   *
   * @description
   * Initializes the object from a file and transformations.
   *
   * @param fileName
   * The name of the file containing the model.
   * @param pos
   * The position of the object.
   * @param rot
   * The rotation of the object.
   * @param scale
   * The scale of the object.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  virtual bool
  loadFromFile(const String& fileName,
               Vector3f pos,
               Quaternion rot,
               Vector3f scale);
  /**
   * @brief
   * Initializes the object.
   *
   * @description
   * Initializes the object from a model and transformations.
   *
   * @param model
   * The model for the object.
   * @param pos
   * The position of the object.
   * @param rot
   * The rotation of the object.
   * @param scale
   * The scale of the object.
   *
   * @return
   * Weather it succeed or failed to initialize.
   */
  virtual bool
  loadFromModel(SPtr<Model> model,
                Vector3f pos,
                Quaternion rot,
                Vector3f scale);

  /**
   * @brief
   * Getter for the position.
   *
   * @description
   * Returns the position of the object.
   *
   * @return
   * The position of the object.
   */
  virtual Vector3f
  getPosition();
  /**
   * @brief
   * Setter for the position.
   *
   * @description
   * Sets a new position for the object
   *
   * @param
   * The new position for the object.
   */
  virtual void
  setPosition(const Vector3f& pos);

  /**
   * @brief
   * Getter for the rotation.
   *
   * @description
   * Returns the rotation of the object.
   *
   * @return
   * The rotation of the object.
   */
  virtual Quaternion
  getRotation();
  /**
   * @brief
   * Setter for the rotation.
   *
   * @description
   * Sets a new rotation for the object
   *
   * @param
   * The new rotation for the object.
   */
  virtual void
  setRotation(const Quaternion& rot);

  /**
   * @brief
   * Getter for the scale.
   *
   * @description
   * Returns the scale of the object.
   *
   * @return
   * The scale of the object.
   */
  virtual Vector3f
  getScale();
  /**
   * @brief
   * Setter for the scale.
   *
   * @description
   * Sets a new scale for the object
   *
   * @param
   * The new scale for the object.
   */
  virtual void
  setScale(const Vector3f& scale);

  /**
   * @brief
   * Getter for the model.
   *
   * @description
   * Returns the model of the object.
   *
   * @return
   * The model of the object.
   */
  virtual void
  setModel(const SPtr<Model>& model);
  /**
   * @brief
   * Setter for the model.
   *
   * @description
   * Sets a new model for the object
   *
   * @param
   * The new model for the object.
   */
  virtual SPtr<Model>
  getModel();

  /**
   * @brief
   * Getter for the model matrix.
   *
   * @description
   * Returns the model matrix of the transformations.
   *
   * @return
   * The model matrix of the transformations.
   */
  virtual Matrix4f
  getModelMatrix();

  /**
   * @brief
   * Getter for the model buffer.
   *
   * @description
   * Returns the model buffer of the transformations.
   *
   * @return
   * The model buffer of the transformations.
   */
  virtual SPtr<ConstantBuffer>
  getModelBuffer()
  {
    return m_modelMatrixBuff;
  }

 protected:
  /**
   * The position of the object.
   */
  Vector3f m_position;
  /**
   * The rotation of the object.
   */
  Quaternion m_rotation;
  /**
   * The scale of the object.
   */
  Vector3f m_scale;

  /**
   * The model of the object.
   */
  SPtr<Model> m_model;

  /**
   * The constant buffer for the model matrix of the object.
   */
  SPtr<ConstantBuffer> m_modelMatrixBuff;
};
}
