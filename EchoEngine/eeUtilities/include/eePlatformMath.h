#pragma once

#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK
{
class EE_UTILITY_EXPORT PlatformMath
{
public:
	PlatformMath() = default;
	~PlatformMath() = default;

	/****************************************************/
	/*
	 *    Trigonometric
	 */
	 /****************************************************/
	static FORCEINLINE float
		cos(const float& _radian);
	static FORCEINLINE float
		sin(const float& _radian);
	static FORCEINLINE float
		tan(const float& _radian);
	static FORCEINLINE float
		sec(const float& _radian);
	static FORCEINLINE float
		csc(const float& _radian);
	static FORCEINLINE float
		cot(const float& _radian);
	static FORCEINLINE float
		acos(const float& _radian);
	static FORCEINLINE float
		asin(const float& _radian);
	static FORCEINLINE float
		atan(const float& _radian);
	static FORCEINLINE float
		asec(const float& _radian);
	static FORCEINLINE float
		acsc(const float& _radian);
	static FORCEINLINE float
		acot(const float& _radian);
	static FORCEINLINE float
		radToDeg(const float& _radian);
	static FORCEINLINE float
		degToRad(const float& _degree);
	static FORCEINLINE float
		fmod(const float& _lval, const float& _rval);
	static FORCEINLINE float
		sqrt(const float& _val);
	static FORCEINLINE float
		pow(const float& _base, const float& _power);
	static FORCEINLINE float
		round(const float _val);
	static FORCEINLINE float
		floor(const float _val);
	static FORCEINLINE float
		ceil(const float _val);
	static FORCEINLINE float
		abs(const float _val);



	static const float kPI;
	static const float kPIover180;
	static const float k180overPI;
};
}