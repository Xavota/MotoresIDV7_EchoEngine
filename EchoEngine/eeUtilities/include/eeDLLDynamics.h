/************************************************************************/
/**
 * @file eeDLLDynamics.h
 * @author Diego Castellanos
 * @date 15/09/21
 * @brief Loads dll from files and makes it easy to extract values from it.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK {
/**
 * @brief
 * A function type, for further use in dll function extraction.
 */
using functionType = const void* (*)();

/**
 * @brief
 * Loads dll from files and makes it easy to extract values from it.
 */
class EE_UTILITY_EXPORT DLLDynamics
{
 public:
  /**
   * @brief
   * The default constructor.
   */
  DLLDynamics() = default;
  /**
   * @brief
   * The default destructor.
   */
  ~DLLDynamics() = default;

  /**
   * @brief
   * Initializes the dll.
   * 
   * @description
   * Initializes the dll from a dll file.
   *
   * @param dllPath
   * The file path of the dll.
   * 
   * @return
   * If it succeeded or failed to initialize
   */
  bool
  initialize(const String& dllPath);

  /**
   * @brief
   * Gets a function from the loaded dll.
   *
   * @description
   * Looks for a value inside the dll and loads it like a function.
   *
   * @param functName
   * The name of the function to look.
   *
   * @return
   * The located function ready to execute, nullptr if not found.
   */
  functionType
  getFunction(const String& functName);

 private:
  /*
   * The loaded instance of a dll.
   */
  void* m_dllInstance = nullptr;

};
}
