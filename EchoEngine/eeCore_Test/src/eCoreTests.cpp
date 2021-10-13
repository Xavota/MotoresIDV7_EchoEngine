#include "eePrerequisitesCore.h"
#include "BaseApp.h"

using eeEngineSDK::BaseApp;
using eeEngineSDK::int32;

int main()
{
  BaseApp::startUp();
  int32 r = BaseApp::instance().run();
  BaseApp::shutDown();

  return r;
}