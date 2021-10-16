#include "eeModel.h"

namespace eeEngineSDK {
bool
Model::loadFromFile(const String& fileName)
{
  return false;
}
bool
Model::loadFromMeshes(Vector<Mesh> meshes)
{
  for (Mesh m : meshes)
  {
    //m_meshes.push_back(MakePair<Mesh&, uint8>(m, 0u));
    m_meshes.push_back(Pair<Mesh&, uint8>(m, static_cast<uint8>(0u)));
  }
  return false;
}
bool
Model::loadFromMeshes(const Vector<Pair<Mesh&, uint8>>& meshes, 
                      Vector<Texture*>& textures)
{
  m_meshes = meshes;
  m_textures = textures;
  return false;
}
}