#pragma once
#include "eePrerequisitesCore.h"
#include "eeVector3.h"
#include "eeQuaternion.h"
#include "eeModel.h"

namespace eeEngineSDK {
class EE_CORE_EXPORT Object
{
 public:
  Object() = default;
  ~Object() = default;

  bool
  loadFromFile(const String& fileName);
  bool
  loadFromModel(SPtr<Model> model,
                Vector3f pos,
                Quaternion rot,
                Vector3f scale);

  Vector3f
  getPosition();
  void
  setPosition(const Vector3f& pos);

  Quaternion
  getRotation();
  void
  setRotation(const Quaternion& rot);

  Vector3f
  getScale();
  void
  setScale(const Vector3f& scale);

  void
  setModel(SPtr<Model>& model);

 private:
  Vector3f m_position;
  Quaternion m_rotation;
  Vector3f m_scale;

  SPtr<Model> m_model;
};
}
