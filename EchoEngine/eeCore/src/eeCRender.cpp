#include "eeCRender.h"
#include "eeGraficsApi.h"

namespace eeEngineSDK {
void
CRender::update()
{
  EE_NO_EXIST_RETURN(m_actor);
  GraphicsApi::instance().addActorToRenderFrame(m_actor);
}
}