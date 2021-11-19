#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK{
enum class eCOMPONENT_TYPE
{
  NONE = -1,
  TRANSFORM,
  COUNT
};

class EE_CORE_EXPORT Component
{
public:
  Component() = default;
  ~Component() = default;

  virtual void
  Update(SPtr<Actor> /*actor*/) {}

  virtual eCOMPONENT_TYPE
  getType()
  {
    return m_type;
  }

 protected:
  eCOMPONENT_TYPE m_type = eCOMPONENT_TYPE::NONE;
};
}