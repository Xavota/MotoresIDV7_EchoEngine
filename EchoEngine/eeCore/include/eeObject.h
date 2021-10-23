#pragma once
#include "eePrerequisitesCore.h"
#include "eeVector3.h"
#include "eeQuaternion.h"
#include "eeModel.h"

#include <eeMatrix4.h>

namespace eeEngineSDK {
class EE_CORE_EXPORT Object
{
 public:
  Object() = default;
  virtual
  ~Object() = default;

  virtual bool
  loadFromFile(const String& fileName);
  virtual bool
  loadFromModel(SPtr<Model> model,
                Vector3f pos,
                Quaternion rot,
                Vector3f scale);

  virtual Vector3f
  getPosition();
  virtual void
  setPosition(const Vector3f& pos);

  virtual Quaternion
  getRotation();
  virtual void
  setRotation(const Quaternion& rot);

  virtual Vector3f
  getScale();
  virtual void
  setScale(const Vector3f& scale);

  virtual void
  setModel(const SPtr<Model>& model);
  virtual SPtr<Model>
  getModel();

  virtual Matrix4f
  getModelMatrix();

 protected:
  Vector3f m_position;
  Quaternion m_rotation;
  Vector3f m_scale;

  SPtr<Model> m_model;
};
}
