#include "eeCAnimation.h"
#include "eeActor.h"
#include "eeCSkeletalMesh.h"
#include "eeSkeletalMesh.h"
#include "eeAnimation.h"
#include "eeTime.h"

namespace eeEngineSDK{
void
CAnimation::update(SPtr<Actor> actor)
{
  SPtr<CSkeletalMesh> skMesh = actor->getComponent<CSkeletalMesh>();
  if (skMesh)
  {
    int32 bonesPerMesh = skMesh->getSkeletal()->getBonesData().size();
    for (int32 i = 0; i < bonesPerMesh; ++i)
    {
      m_anim->boneTransform(Time::instance().getDeltaTime(),
                            i,
                            skMesh->getSkeletal());
    }
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
  m_anim = anim;
}
}