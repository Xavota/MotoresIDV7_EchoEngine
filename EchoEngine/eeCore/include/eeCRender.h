/************************************************************************/
/**
 * @file eeCRender.h
 * @author Diego Castellanos
 * @date 18/11/21
 * @brief
 * The render component. Needed to render the model in the actor.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include "eeComponent.h"

namespace eeEngineSDK{
/**
* @brief
* The render component. Needed to render the model in the actor.
*/
class EE_CORE_EXPORT CRender : public Component
{
 public:
  /**
  * @brief
  * The enum for identifying the component type.
  */
  enum { CmpType = eCOMPONENT_TYPE::RENDER };

  /**
  * @brief
  * Returns the component type.
  *
  * @description
  * Returns the component type.
  *
  * @return
  * The component type.
  */
  virtual int32
  getType() override
  {
    return CmpType;
  }

  /**
  * @brief
  * Default constructor.
  */
  CRender();
  /**
  * @brief
  * Default destructor.
  */
  ~CRender() = default;

  /**
  * @brief
  * Updates the render logic.
  *
  * @description
  * Adds the actor to the render actors pool.
  */
  virtual void
  update() override;
};
}
