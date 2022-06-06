#include "eePrerequisitesCore.h"
#include "eeBaseAppOGLTest.h"

using eeEngineSDK::int32;

int
main()
{
  auto testApp = new BaseAppOGLTest();
  int32 r = testApp->run(nullptr);
  delete testApp;

  return r;
}