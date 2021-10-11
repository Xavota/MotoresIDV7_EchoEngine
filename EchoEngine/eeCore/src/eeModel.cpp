#include "eeModel.h"

namespace eeEngineSDK {
bool
Model::loadFromFile(const String& fileName)
{
  return false;
}

bool
Model::loadFromMeshes(const Vector<Mesh>& meshes)
{
  return false;
}

bool
Model::loadFromMeshes(const Pair<Mesh, uint8>& meshes, 
                      Vector<Texture*> textures)
{
  return false;
}
}