#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
class ResourceManager
{
 public:
  ResourceManager();
  ~ResourceManager();

  bool
  loadTextureFromFile(const String& fileName);
};
}
