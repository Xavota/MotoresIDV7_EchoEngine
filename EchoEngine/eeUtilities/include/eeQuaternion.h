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
class Quaternion
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
  * The euclidean angles represented in the cuaternion.
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
  Quaternion&
  operator*(const Quaternion& other);


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
