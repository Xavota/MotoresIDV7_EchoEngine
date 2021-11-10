#include "eePrerequisitesCore.h"
#include "eeBaseAppTest1.h"

using eeEngineSDK::BaseApp;
using eeEngineSDK::int32;

int main()
{
  BaseApp::startUp<BaseAppTest1>();
  int32 r = BaseApp::instance().run();
  BaseApp::shutDown();

  //int a;
  //std::cin >> a;

  return r;
}