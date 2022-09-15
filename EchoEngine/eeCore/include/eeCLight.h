/************************************************************************/
/**
 * @file eeCLight.h
 * @author Diego Castellanos
 * @date 08/04/22
 * @brief
 * The Light component.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"
#include "eeComponent.h"

#include <eeMath.h>
#include <eeVector3.h>
#include <eeColor.h>

namespace eeEngineSDK {
/**
 * @brief
 * The type of light it's holding.
 */
namespace eLIGHT_TYPE {
enum E : uint8 
{
  kDirectional,
  kPoint,
  kSpot
};
}
class EE_CORE_EXPORT CLight : public Component
{
 public:
  /**
   * @brief
   * The enum for identifying the component type.
   */
  enum { CmpType = eCOMPONENT_TYPE::kLight };

  /**
   * @brief
   * Default constructor.
   */
  CLight() = default;
  /**
   * @brief
   * Custom constructor.
   * 
   * @description
   * Constructs the light with parameters.
   *
   * @param type
   * The light type.
   * @param newColor
   * The light color.
   * @param innerAngle
   * The light inner angle.
   * @param outerAngle
   * The light outer angle.
   */
  CLight(eLIGHT_TYPE::E type,
         Color newColor = Color(1.0f, 1.0f, 1.0f, 1.0f),
         float intensity = 1.0f,
         float innerAngle = Math::kPI * 0.25f,
         float outerAngle = Math::kPI * 0.5f);
  /**
   * @brief
   * Default destructor.
   */
  ~CLight() = default;

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
  int8
  getType() override
  {
    return CmpType;
  }
  
  /**
   * @brief
   * Initialize the light.
   * 
   * @description
   * Constructs the light with parameters.
   *
   * @param type
   * The light type.
   * @param newColor
   * The light color.
   * @param innerAngle
   * The light inner angle.
   * @param outerAngle
   * The light outer angle.
   */
  void
  init(eLIGHT_TYPE::E type,
       Color newColor = Color(1.0f, 1.0f, 1.0f, 1.0f),
       float intensity = 1.0f,
       float innerAngle = Math::kPI * 0.25f,
       float outerAngle = Math::kPI * 0.5f);

  /**
   * @brief
   * Updates the light logic.
   *
   * @description
   * Updates the position and direction of the light to match the actor to whom
   * it is attached.
   */
  void
  update() override;
  
  /**
   * @brief
   * Getter of the light type.
   *
   * @description
   * Returns the light type.
   *
   * @return
   * The light type.
   */
  FORCEINLINE eLIGHT_TYPE::E
  getLightType()
  {
    return m_type;
  }
  /**
   * @brief
   * Setter of the light type.
   *
   * @description
   * Sets the light type.
   *
   * @param type
   * The light type.
   */
  FORCEINLINE void
  setLightType(eLIGHT_TYPE::E type)
  {
    m_type = type;
  }

  /**
   * @brief
   * Getter of the light position
   *
   * @description
   * Returns the light position, that matches its actor.
   *
   * @return
   * The light position.
   */
  FORCEINLINE Vector3f
  getPosition()
  {
    return m_position;
  }
  /**
   * @brief
   * Getter of the light direction
   *
   * @description
   * Returns the light direction, that matches its actor.
   *
   * @return
   * The light direction.
   */
  FORCEINLINE Vector3f
  getDirection()
  {
    return m_direction;
  }

  /**
   * @brief
   * Getter of the light intensity.
   *
   * @description
   * Returns the light intensity.
   *
   * @return
   * The light intensity.
   */
  FORCEINLINE float
  getIntensity()
  {
    return m_intensity;
  }
  /**
   * @brief
   * Setter of the light intensity.
   *
   * @description
   * Sets the light intensity.
   *
   * @param intensity
   * The light intensity.
   */
  FORCEINLINE void
  setIntensity(float intensity)
  {
    m_intensity = intensity;
  }
  
  /**
   * @brief
   * Getter of the light inner angle.
   *
   * @description
   * Returns the light inner angle.
   *
   * @return
   * The light inner angle.
   */
  FORCEINLINE float
  getInnerAngle()
  {
    return m_innerAngle;
  }
  /**
   * @brief
   * Setter of the light inner angle.
   *
   * @description
   * Sets the light inner angle.
   *
   * @param angle
   * The light inner angle.
   */
  FORCEINLINE void
  setInnerAngle(float angle)
  {
    m_innerAngle = angle;
  }
  /**
   * @brief
   * Getter of the outer inner angle.
   *
   * @description
   * Returns the outer inner angle.
   *
   * @return
   * The light outer angle.
   */
  FORCEINLINE float
  getOuterAngle()
  {
    return m_outerAngle;
  }
  /**
   * @brief
   * Setter of the outer inner angle.
   *
   * @description
   * Sets the outer inner angle.
   *
   * @param angle
   * The light outer angle.
   */
  FORCEINLINE void
  setOuterAngle(float angle)
  {
    m_outerAngle = angle;
  }
  
  /**
   * @brief
   * Getter of the light color.
   *
   * @description
   * Returns the light color.
   *
   * @return
   * The light color.
   */
  FORCEINLINE Color
  getColor()
  {
    return m_color;
  }
  /**
   * @brief
   * Setter of the light color.
   *
   * @description
   * Sets the light color.
   *
   * @param newColor
   * The light color.
   */
  FORCEINLINE void
  setColor(const Color& newColor)
  {
    m_color = newColor;
  }

 private:
  /**
   * The type of the light.
   */
  eLIGHT_TYPE::E m_type = eLIGHT_TYPE::kDirectional;
  
  /**
   * The position of the light.
   */
  Vector3f m_position = Vector3f(0.0f, 0.0f, 0.0f);
  /**
   * The direction of the light.
   */
  Vector3f m_direction = Vector3f(0.0f, 0.0f, 1.0f);
  /**
   * The intensity of the light.
   */
  float m_intensity = 1.0f;

  // For spot light
  /**
   * The angle of the inner radius of the spot light.
   */
  float m_innerAngle = Math::kPI * 0.25f;
  /**
   * The angle of the outer radius of the spot light. 
   */
  float m_outerAngle = Math::kPI * 0.5f;

  /**
   * The color of the light.
   */
  Color m_color = Color(1.0f, 1.0f, 1.0f, 1.0f);
};
}
