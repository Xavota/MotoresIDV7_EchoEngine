#include "eeCModel.h"

namespace eeEngineSDK {
CModel::CModel()
{
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