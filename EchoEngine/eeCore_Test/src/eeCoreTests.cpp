#include "eePrerequisitesCore.h"
#include "eeBaseAppTest1.h"

using eeEngineSDK::BaseApp;
using eeEngineSDK::int32;

int
main()
{
  auto testApp = new BaseAppTest1();
  int32 r = testApp->run(nullptr);
  delete testApp;

  return r;
}