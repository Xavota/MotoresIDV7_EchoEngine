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
  Material();
  /**
   * @brief
   * Load all textures.
   * 
   * @description
   * Loads all textures of the Material. Sets them to the default if nullptr.
   * 
   * @param diffuse
   * The color map.
   * @param normalMap
   * The normal map
   */
  Material(SPtr<Texture> diffuse,
           SPtr<Texture> normalMap = nullptr);
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
   * Loads all textures of the Material. Sets them to the default if nullptr.
   * 
   * @param diffuse
   * The color map.
   * @param normalMap
   * The normal map
   */
  void
  createMaterial(SPtr<Texture> diffuse = nullptr,
                 SPtr<Texture> normalMap = nullptr);

  /**
   * The color texture.
   */
  SPtr<Texture> m_diffuse = nullptr;
  /**
   * The normal texture.
   */
  SPtr<Texture> m_normalMap = nullptr;
};
}
