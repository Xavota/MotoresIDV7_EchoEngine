/************************************************************************/
/**
 * @file eeSphere.h
 * @author Diego Castellanos
 * @date 1/10/21
 * @brief Four dimensional quaternion made by floats.
 *        It can be used for rotations in 3 dimensions.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK
{
  /**
  * @brief
  * Four dimensional quaternion made by floats.
  * It can be used for rotations in 3 dimensions.
  */
class EE_UTILITY_EXPORT Quaternion
{
 public:
  /**
  * @brief
  * The default constructor.
  */
  Quaternion();
  /**
  * @brief
  * Initializes the vector with the values given.
  *
  * @description
  * Initializes w, x, y, z with the values _w, _x, _y, _z
  * given.
  *
  * @param _w
  * The initial w for the vector.
  * @param _x
  * The initial x for the vector.
  * @param _y
  * The initial y for the vector.
  * @param _z
  * The initial z for the vector.
  */
  Quaternion(float _w, float _x, float _y, float _z);
  /**
  * @brief
  * Initializes the quaternion with euclidean angles.
  *
  * @description
  * Initializes w, x, y, z with the transformation of the euclidean
  * angles to quaternion.
  *
  * @param euclidean
  * The vector with the 3 angles (roll, pitch, yaw);
  */
  explicit
  Quaternion(const Vector3f& euclidean);
  /**
  * @brief
  * Frees the memory allocated on the quaternion.
  *
  * @description
  * Releases and deletes all the possible memory
  * allocated in the quaternion.
  */
  ~Quaternion();

  /**
  * @brief
  * The conjugated version of the quaternion.
  *
  * @description
  * Returns the same quaternion but with its imaginary part negative.
  *
  * @return
  * The same quaternion but with its imaginary part negative.
  */
  Quaternion
  getConjugate();
  /**
  * @brief
  * The conjugated version of the quaternion.
  *
  * @description
  * Transform the imaginary part of the quaternion to be negative.
  */
  void
  conjugate();
  /**
  * @brief
  * The normalization of the quaternion.
  *
  * @description
  * Returns an unitary quaternion with the same angle
  * of the original.
  *
  * @return
  * The quaternion normalized.
  */
  Quaternion
  getNormalize() const;
  /**
  * @brief
  * Normalizes the quaternion.
  *
  * @description
  * Modifies the quaternion to its unitary form, maintaining its angle
  * and returns this new quaternion.
  *
  * @return
  * The quaternion normalized.
  */
  Quaternion
  normalize();
  

  /**
  * @brief
  * The euclidean angles represented in the quaternion.
  *
  * @description
  * Returns the transformation of the quaternion to euclidean angles.
  *
  * @return
  * The transformation of the quaternion to euclidean angles.
  */
  Vector3f
  getEuclidean();
  /**
  * @brief
  * Initializes the quaternion with euclidean angles.
  *
  * @description
  * Initializes w, x, y, z with the transformation of the euclidean
  * angles to quaternion.
  *
  * @param euclidean
  * The vector with the 3 angles (roll, pitch, yaw);
  */
  void
  setEuclidean(const Vector3f& euclidean);

  /**
  * @brief
  * A rotation matrix.
  *
  * @description
  * Returns a rotation matrix with the euclidean angles.
  *
  * @return
  * A rotation matrix with the euclidean angles.
  */
  Matrix4f
  getRotationMatrix();
  /**
  * @brief
  * Initializes the quaternion with a rotation matrix.
  *
  * @description
  * Initializes the quaternion extracting the angles of the rotation
  * matrix.
  *
  * @param rotMatrix
  * The rotation matriz from where the angles will be taken.
  */
  //void
  //setFromMatrix(const Matrix4f& rotMatrix);

  /**
  * @brief
  * Rotates a vector.
  *
  * @description
  * Returns a copy of the vector but rotated using the values in the
  * quaternion.
  *
  * @param vec
  * The vector to be rotated.
  *
  * @return
  * The vector rotated.
  */
  Vector3f
  rotateVector(const Vector3f& vec);
  /**
  * @brief
  * Creates a quaternion within a 3D axis.
  *
  * @description
  * Creates a quaternion around an axis and an angle.
  *
  * @param axis
  * The axis that the quaternion will be formed.
  * @param angle
  * The angle to be rotated.
  */
  static Quaternion
  createFromAxisAngle(const Vector3f axis,
                      const float& angle);

  /**
  * @brief
  * Returns a direction vector.
  *
  * @description
  * Rotates a front vector to get the direction of the quaternion.
  *
  * @return
  * The front vector.
  */
  Vector3f
  getFrontVector();
  /**
  * @brief
  * Returns the right of the direction vector.
  *
  * @description
  * Rotates a right vector to get the right direction of the quaternion.
  *
  * @return
  * The right vector.
  */
  Vector3f
  getRightVector();
  /**
  * @brief
  * Returns the up of the direction vector.
  *
  * @description
  * Rotates an up vector to get the up direction of the quaternion.
  *
  * @return
  * The up vector.
  */
  Vector3f
  getUpVector();


  /**
  * @brief
  * Returns a string of the quaternion.
  *
  * @description
  * Return a string with the format "{ 0i, 0j, 0k, 0 }.
  *
  * @return
  * The string quaternion.
  */
  String
  toString() const;

  /**
  * @brief
  * The multiplication of two quaternions.
  *
  * @description
  * Returns the result of multipling all the imaginary and real component
  * of both quaternions.
  *
  * @param other
  * The other quaternion for the operation.
  *
  * @return
  * The multiplication of the two quaternions.
  */
  Quaternion
  operator*(const Quaternion& other);

  /**
  * @brief
  * Compares the two quaternions to see if they are equal.
  *
  * @description
  * Check if every component of the quaternion are equal to their counterpart
  * of the other vector.
  *
  * @param other
  * The other quaternion to check.
  *
  * @return
  * True if they are equal.
  */
  bool
  operator==(const Quaternion& other) const;


  union
  {
    struct
    {
      /*
      * The real component of the quaternion
      */
      float w;
      /*
      * The i component of the quaternion
      */
      float x;
      /*
      * The j component of the quaternion
      */
      float y;
      /*
      * The k component of the quaternion
      */
      float z;
    };
    /*
    * All the components of the quaternion in an array
    */
    float wxyz[4];
  };
};
}
