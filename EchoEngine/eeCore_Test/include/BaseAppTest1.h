#pragma once
#include <BaseApp.h>

using eeEngineSDK::BaseApp;
using eeEngineSDK::int32;
using eeEngineSDK::SPtr;
using eeEngineSDK::Object;

class BaseAppTest1 : public BaseApp
{
 public:
  BaseAppTest1();
  ~BaseAppTest1();

  /*virtual int32
  run();

  virtual int32
  mainLoop();*/

  virtual bool
  init() override;

  /*virtual void
  processEvents();*/

  virtual void
  update(float deltaTime) override;

  virtual void
  render() override;

  virtual void
  destroy() override;


 private:
  SPtr<Object> m_triangle;
  SPtr<Object> m_cube;
};

