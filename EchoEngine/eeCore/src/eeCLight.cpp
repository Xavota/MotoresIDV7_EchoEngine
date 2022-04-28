#include "eeCLight.h"

#include <eeActor.h>
#include <eeCTransform.h>

namespace eeEngineSDK {
CLight::CLight(eLIGHT_TYPE::E type,
               Color newColor,
               float intensity,
               float innerAngle,
               float outerAngle) :
 m_type(type),
 m_color(newColor),
 m_intensity(intensity),
 m_innerAngle(innerAngle),
 m_outerAngle(outerAngle)
{}
void
CLight::update()
{
  SPtr<CTransform> trans = getActor()->getTransform();
  m_position = trans->getPosition();
  m_direction = trans->getRotation().getFrontVector();
}
}