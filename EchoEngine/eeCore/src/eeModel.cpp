#include "eeModel.h"

namespace eeEngineSDK {
bool
Model::loadFromFile(const String& /*fileName*/)
{
  return true;
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
  return true;
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
  return true;
}
Vector<Pair<SPtr<Mesh>, uint8>> Model::getMeshes()
{
  return m_meshes;
}
Vector<SPtr<Texture>> Model::getTextures()
{
  return m_textures;
}
}