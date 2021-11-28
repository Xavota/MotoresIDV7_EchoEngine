/************************************************************************/
/**
 * @file eeInput.h
 * @author Diego Castellanos
 * @date 16/11/21
 * @brief
 * The input manager for the api.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK{
namespace eCOMPONENT_TYPE {
enum E
{
  NONE = -1,
  TRANSFORM,
  MODEL,
  RENDER,
  CAMERA,
  SKELETAL_MESH,
  COUNT
};
}

class EE_CORE_EXPORT Component : public std::enable_shared_from_this<Component>
{
public:
  enum { CmpType = eCOMPONENT_TYPE::NONE };

  Component() = default;
  ~Component() = default;

  virtual void
  update(SPtr<Actor> /*actor*/) {}

  virtual int32
  getType()
  {
    return CmpType;
  }

 protected:
};
}