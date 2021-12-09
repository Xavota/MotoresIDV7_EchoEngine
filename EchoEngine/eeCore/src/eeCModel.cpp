#include "eeCModel.h"
#include "eeModel.h"
#include "eeActor.h"
#include "eeCTransform.h"

namespace eeEngineSDK {
CModel::CModel()
{
}
void
CModel::update()
{
  EE_NO_EXIST_RETURN(m_actor);

  SPtr<CTransform> trans = m_actor->getTransform();

  m_boundSphere.setCenter(trans->getGlobalPosition());

  Vector3f scale = trans->getGlobalScale();
  float radScale = scale.x > scale.y ? scale.x : scale.y;
  radScale = radScale > scale.z ? radScale : scale.z;

  m_boundSphere.setRadious(m_originRadious * radScale);

}
void
CModel::setModel(SPtr<Model> model)
{
  m_model = model;
  EE_NO_EXIST_RETURN(m_model);

  m_boundSphere = m_model->getBoundingSphere();

  m_originRadious = m_boundSphere.getRadious();
}
SPtr<Model>
CModel::getModel()
{
  return m_model;
}
const
Sphere& CModel::getBoundingSphere()
{
  return m_boundSphere;
}
const
BoxAAB& CModel::getBoundingBox()
{
  return m_boundBox;
}
}