#include "eeCModel.h"

namespace eeEngineSDK {
CModel::CModel()
{
  m_type = eCOMPONENT_TYPE::MODEL;
}
void CModel::setModel(SPtr<Model> model)
{
  m_model = model;
}
SPtr<Model> CModel::getModel()
{
  return m_model;
}
}