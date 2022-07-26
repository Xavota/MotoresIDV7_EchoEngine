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
  if (m_actor.expired()) return;
  if (m_anim.expired()) return;

  auto skMesh = m_actor.lock()->getComponent<CSkeletalMesh>().lock();
  if (!skMesh) return;
  if (skMesh->getModel().expired()) return;
  auto skeleton = skMesh->getModel().lock()->getSkeletal().lock();
  if (!skeleton) return;

  SIZE_T bonesPerMesh = skeleton->getBonesData().size();
  m_animTime += Time::instance().getDeltaTime();
  for (SIZE_T i = 0; i < bonesPerMesh; ++i) {
    m_anim.lock()->boneTransform(i, skeleton, m_animTime);
  }
}
WPtr<Animation>
CAnimation::getAnimation()
{
  return m_anim;
}
void
CAnimation::setAnimation(WPtr<Animation> anim)
{
  if (anim.expired()) return;
  m_anim = anim;
}
}