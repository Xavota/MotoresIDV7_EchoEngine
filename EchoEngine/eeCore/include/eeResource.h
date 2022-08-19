/************************************************************************/
/**
 * @file eeResource.h
 * @author Diego Castellanos
 * @date 16/08/22
 * @brief
 * Resource parent class, for storing name and other needed variables.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
/**
 * @brief
 * Resource parent class, for storing name and other needed variables.
 */
class EE_CORE_EXPORT Resource
{
 public:
  /**
   * @brief
   * Default constructor.
   */
  Resource() = default;
  /**
   * @brief
   * Default destructor.
   */
  virtual
  ~Resource() = default;
  
  /**
   * @brief
   * Getter for the resource name.
   *
   * @description
   * Returns the resource name.
   *
   * @return
   * The resource name.
   */
  String
  getResourceName()
  {
    return m_resourceName;
  }
  /**
   * @brief
   * Setter for the resource name.
   *
   * @description
   * Sets the new resource name.
   *
   * @param newName
   * The new resource name.
   */
  void
  setResourceName(const String& newName)
  {
    m_resourceName = newName;
  }

 protected:
  /**
   * The name of the resource
   */
  String m_resourceName;
};
}