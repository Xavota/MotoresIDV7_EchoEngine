#include "eeMaterial.h"
#include "eeResourceManager.h"
#include "eeGraficsApi.h"

namespace eeEngineSDK {
Material::Material(const Map<uint32, SPtr<Texture>>& texturesMap)
{
  createMaterial(texturesMap);
}
void
Material::createMaterial(const Map<uint32, SPtr<Texture>>& texturesMap)
{
  m_texturesMap = texturesMap;
}
void
Material::setTexture(SPtr<Texture> texture, uint32 index)
{
  m_texturesMap[index] = texture;
}
}