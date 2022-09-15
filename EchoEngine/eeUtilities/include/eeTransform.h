#pragma once
#include "eePrerequisitesUtilities.h"

#include <eeVector3.h>
#include <eeQuaternion.h>
#include <eeMatrix4.h>

namespace eeEngineSDK {
class EE_UTILITY_EXPORT Transform
{
 public:
  /**
   * @brief
   * Default constructor
   */
  Transform() :
    m_position(0.0f, 0.0f, 0.0f),
    m_rotation(Vector3f(0.0f, 0.0f, 0.0f)),
    m_scale(1.0f, 1.0f, 1.0f)
  {}
  /**
   * @brief
   * Custom constructor
   *
   * @description
   * Creates a triangles with 3 vertex points.
   *
   * @param _x
   * The first vertex of the triangle.
   * @param _y
   * The second vertex of the triangle.
   * @param _z
   * The third vertex of the triangle.
   */
  Transform(const Vector3f & position,
            const Quaternion & rotation,
            const Vector3f & scale) :
    m_position(position),
    m_rotation(rotation),
    m_scale(scale)
  {}
  /**
   * @brief
   * Default destructor.
   */
  ~Transform() = default;

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
  Matrix4f
  getModelMatrix();

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
  Vector3f
  getPosition() const;
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
  void
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
  Quaternion
  getRotation() const;
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
  void
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
  Vector3f
  getScale() const;
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
  void
  setScale(const Vector3f& scale);

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
};
}