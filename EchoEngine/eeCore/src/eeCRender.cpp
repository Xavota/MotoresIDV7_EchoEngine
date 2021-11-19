#include "eeCRender.h"
#include "eeGraficsApi.h"

namespace eeEngineSDK {
CRender::CRender()
{
  m_type = eCOMPONENT_TYPE::RENDER;
}
void CRender::update(Actor* actor)
{
  GraphicsApi::instance().addActorToRenderFrame(actor);
}
}