/************************************************************************/
/**
 * @file eInputLayout.h
 * @author Diego Castellanos
 * @date 14/10/21
 * @brief
 * The input layout for the shaders.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
/**
 * @brief
 * The input layout for the shaders.
 */
class EE_CORE_EXPORT InputLayout
{
 public: 
  /**
   * @brief
   * Default constructor
   */
  InputLayout() = default;
  /**
   * @brief
   * Default destructor
   */
  virtual 
  ~InputLayout() = default;
};
}
