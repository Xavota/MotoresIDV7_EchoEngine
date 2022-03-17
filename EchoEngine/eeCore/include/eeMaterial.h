/************************************************************************/
/**
 * @file eeMaterial.h
 * @author Diego Castellanos
 * @date 18/02/22
 * @brief The material class. Holds various textures of different kinds.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
namespace TEXTURE_TYPE_INDEX {
enum E : uint8 {
  kDiffuse,
  kNormal
};
}

/**
 * @brief
 * The material class. Holds various textures of different kinds.
 */
class EE_CORE_EXPORT Material
{
 public:
  /**
   * @brief
   * Default constructor
   */
  Material() = default;
  /**
   * @brief
   * Load all textures.
   *
   * @description
   * Loads all textures of the Material.
   *
   * @param texturesMap
   * The map of textures and its indices to be set on.
   */
  Material(const Map<uint32, SPtr<Texture>>& texturesMap);
  /**
   * @brief
   * Copy constructor
   */
  ~Material() = default;

  
  /**
   * @brief
   * Load all textures.
   * 
   * @description
   * Loads all textures of the Material.
   * 
   * @param texturesMap
   * The map of textures and its indices to be set on.
   */
  void
  createMaterial(const Map<uint32, SPtr<Texture>>& texturesMap);
  
  /**
   * @brief
   * Sets a texture.
   * 
   * @description
   * Sets a texture in the material on the given index.
   * 
   * @param texture
   * The texture to set.
   * @param index
   * The index to set it on.
   */
  void
  setTexture(SPtr<Texture> texture, uint32 index);
  
  /**
   * @brief
   * Getter of the textures map.
   * 
   * @description
   * Returns the textures map where they are stored.
   * 
   * @return
   * The textures map where they are stored.
   */
  FORCEINLINE const Map<uint32, SPtr<Texture>>&
  getTexturesMap() { return m_texturesMap; }

  /**
   * The textures stored.
   */
  Map<uint32, SPtr<Texture>> m_texturesMap;
};
}
