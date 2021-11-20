#include "eeCRender.h"
#include "eeGraficsApi.h"

namespace eeEngineSDK {
CRender::CRender()
{
}
void CRender::update(Actor* actor)
{
  GraphicsApi::instance().addActorToRenderFrame(actor);
}
}