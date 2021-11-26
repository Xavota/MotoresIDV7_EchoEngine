#include "eeCModel.h"
#include "eeModel.h"
#include "eeActor.h"
#include "eeCTransform.h"

namespace eeEngineSDK {
CModel::CModel()
{
}
void CModel::update(SPtr<Actor> actor)
{
  SPtr<CTransform> trans = actor->getComponent<CTransform>();
  if (trans)
  {
    m_boundSphere.setCenter(trans->getPosition());

    Vector3f scale = trans->getScale();
    float radScale = scale.x > scale.y ? scale.x : scale.y;
    radScale = radScale > scale.z ? radScale : scale.z;

    m_boundSphere.setRadious(m_originRadious * radScale);
  }
}
void CModel::setModel(SPtr<Model> model)
{
  m_model = model;
  m_boundSphere = m_model->getBoundingSphere();

  m_originRadious = m_boundSphere.getRadious();
}
SPtr<Model> CModel::getModel()
{
  return m_model;
}
const Sphere& CModel::getBoundingSphere()
{
  return m_boundSphere;
}
const BoxAAB& CModel::getBoundingBox()
{
  return m_boundBox;
}
}