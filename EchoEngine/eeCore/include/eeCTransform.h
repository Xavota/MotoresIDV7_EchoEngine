/************************************************************************/
/**
 * @file eeCTransform.h
 * @author Diego Castellanos
 * @date 17/11/21
 * @brief
 * The transform component.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include "eeComponent.h"
#include "eeVector3.h"
#include "eeMatrix4.h"
#include "eeQuaternion.h"

namespace eeEngineSDK {
/**
 * @brief
 * The transform component.
 */
class EE_CORE_EXPORT CTransform : public Component
{
 public:
  /**
   * @brief
   * The enum for identifying the component type.
   */
  enum { CmpType = eCOMPONENT_TYPE::kTransform };

  /**
   * @brief
   * Default constructor.
   */
  CTransform();
  /**
   * @brief
   * Default destructor.
   */
  ~CTransform() = default;

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
   * Updates the transform logic.
   *
   * @description
   * Updates the model matrix buffer if it needs to.
   */
  void
  update() override;

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

  /**
   * @brief
   * Getter for the position.
   *
   * @description
   * Returns the local position of the object.
   *
   * @return
   * The position of the object.
   */
  virtual Vector3f
  getPosition();
  /**
   * @brief
   * Getter for the position.
   *
   * @description
   * Returns the world position of the object.
   *
   * @return
   * The position of the object.
   */
  virtual Vector3f
  getGlobalPosition();
  /**
   * @brief
   * Setter for the position.
   *
   * @description
   * Sets a new position for the object
   *
   * @param pos
   * The new position for the object.
   */
  virtual void
  setPosition(const Vector3f& pos);

  /**
   * @brief
   * Getter for the rotation.
   *
   * @description
   * Returns the local rotation of the object.
   *
   * @return
   * The rotation of the object.
   */
  virtual Quaternion
  getRotation();
  /**
   * @brief
   * Getter for the rotation.
   *
   * @description
   * Returns the world rotation of the object.
   *
   * @return
   * The rotation of the object.
   */
  virtual Quaternion
  getGlobalRotation();
  /**
   * @brief
   * Setter for the rotation.
   *
   * @description
   * Sets a new rotation for the object
   *
   * @param rot
   * The new rotation for the object.
   */
  virtual void
  setRotation(const Quaternion& rot);

  /**
   * @brief
   * Getter for the scale.
   *
   * @description
   * Returns the local scale of the object.
   *
   * @return
   * The scale of the object.
   */
  virtual Vector3f
  getScale();
  /**
   * @brief
   * Getter for the global scale.
   *
   * @description
   * Returns the world scale of the object.
   *
   * @return
   * The scale of the object.
   */
  virtual Vector3f
  getGlobalScale();
  /**
   * @brief
   * Setter for the scale.
   *
   * @description
   * Sets a new scale for the object
   *
   * @param scale
   * The new scale for the object.
   */
  virtual void
  setScale(const Vector3f& scale);


  /**
   * @brief
   * Attach the transform to a parent transform.
   *
   * @description
   * Attach the transform to a parent transform to adopt the transformations.
   *
   * @param transformParent
   * The new parent transform.
   */
  virtual void
  attatchTo(SPtr<CTransform> transformParent);

 private:
  /**
   * The position of the actor.
   */
  Vector3f m_position;
  /**
   * The rotation of the actor.
   */
  Quaternion m_rotation;
  /**
   * The scale of the actor.
   */
  Vector3f m_scale;

  /**
   * The constant buffer for the model matrix of the object.
   */
  SPtr<ConstantBuffer> m_modelMatrixBuff;


  /**
   * The dirty flag of the model matrix.
   */
  bool m_dirtyModelMatrix = true;

  /**
   * The transform component children.
   */
  Vector<SPtr<CTransform>> m_childs;
  /**
   * The transform component parent.
   */
  SPtr<CTransform> m_parent;
  /**
   * The child index on the parent transform.
   */
  int32 m_childIndex = -1;
};
}
