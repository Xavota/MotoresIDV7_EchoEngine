#include "eeMaterial.h"
#include "eeResourceManager.h"

namespace eeEngineSDK {
Material::Material()
{
  auto& resourceMan = ResourceManager::instance();

  m_diffuse = resourceMan.getResourceTexture("DefaultDiffuse");
  m_normalMap = resourceMan.getResourceTexture("DefaultNormalMap");
}
Material::Material(SPtr<Texture> diffuse,
                   SPtr<Texture> normalMap)
{
  createMaterial(diffuse, normalMap);
}
void
Material::createMaterial(SPtr<Texture> diffuse,
                         SPtr<Texture> normalMap)
{
  auto& resourceMan = ResourceManager::instance();

  if (diffuse) {
    m_diffuse = diffuse;
  }
  else {
    m_diffuse = resourceMan.getResourceTexture("DefaultDiffuse");
  }

  if (normalMap) {
    m_normalMap = normalMap;
  }
  else {
    m_normalMap = resourceMan.getResourceTexture("DefaultNormalMap");
  }
}
}