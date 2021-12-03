/************************************************************************/
/**
 * @file eeInput.h
 * @author Diego Castellanos
 * @date 28/11/21
 * @brief
 * The input manager for the api.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eeComponent.h"

namespace eeEngineSDK{
class EE_CORE_EXPORT CSkeletalMesh : public Component
{
public:
  enum { CmpType = eCOMPONENT_TYPE::SKELETAL_MESH };

  virtual int32
  getType() override
  {
    return CmpType;
  }

  CSkeletalMesh() = default;
  ~CSkeletalMesh() = default;

  void
  update(SPtr<Actor> actor) override;

  SPtr<SkeletalMesh>
  getSkeletal();
  void
  setSkeletal(SPtr<SkeletalMesh> skeletal);

 private:
  SPtr<SkeletalMesh> m_skMesh;
};
}
