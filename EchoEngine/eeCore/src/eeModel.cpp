#include "eeModel.h"

namespace eeEngineSDK {
bool
Model::loadFromFile(const String& /*fileName*/)
{
  return false;
}
bool
Model::loadFromMeshes(Vector<SPtr<Mesh>> meshes)
{
  if (meshes.empty())
  {
    std::cout << "Empty info loading model" << std::endl;
    return false;
  }

  for (SPtr<Mesh> m : meshes)
  {
    //m_meshes.push_back(MakePair<Mesh&, uint8>(m, 0u));
    m_meshes.push_back(Pair<SPtr<Mesh>, uint8>(m, static_cast<uint8>(0u)));
  }
  return false;
}
bool
Model::loadFromMeshes(const Vector<Pair<SPtr<Mesh>, uint8>>& meshes,
                      const Vector<SPtr<Texture>>& textures)
{
  if (meshes.empty())
  {
    std::cout << "Empty info loading model" << std::endl;
    return false;
  }

  m_meshes = meshes;
  m_textures = textures;
  return false;
}
}