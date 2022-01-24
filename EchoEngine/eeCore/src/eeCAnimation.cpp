#include "eeCAnimation.h"
#include "eeActor.h"
#include "eeCSkeletalMesh.h"
#include "eeSkeletalMesh.h"
#include "eeSkeletal.h"
#include "eeAnimation.h"
#include <eeTime.h>

namespace eeEngineSDK{
void
CAnimation::update()
{
  EE_NO_EXIST_RETURN(m_actor);
  EE_NO_EXIST_RETURN(m_anim);

  SPtr<CSkeletalMesh> skMesh = m_actor->getComponent<CSkeletalMesh>();
  EE_NO_EXIST_RETURN(skMesh);
  EE_NO_EXIST_RETURN(skMesh->getModel());
  SPtr<Skeletal> skeleton = skMesh->getModel()->getSkeletal();
  EE_NO_EXIST_RETURN(skeleton);

  auto bonesPerMesh =
  static_cast<int32>(skeleton->getBonesData().size());
  m_animTime += Time::instance().getDeltaTime();
  for (int32 i = 0; i < bonesPerMesh; ++i) {
    m_anim->boneTransform(i, skeleton, m_animTime);
  }
}
SPtr<Animation>
CAnimation::getAnimation()
{
  return m_anim;
}
void
CAnimation::setAnimation(SPtr<Animation> anim)
{
  EE_NO_EXIST_RETURN(anim);
  m_anim = anim;
}
}