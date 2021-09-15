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


FORCEINLINE float PlatformMath::cos(const float& _radian)
{
	return std::cosf(_radian);
}
FORCEINLINE float PlatformMath::sin(const float& _radian)
{
	return std::sinf(_radian);
}
FORCEINLINE float PlatformMath::tan(const float& _radian)
{
	return std::tanf(_radian);
}
FORCEINLINE float PlatformMath::sec(const float& _radian)
{
	return 1 / cos(_radian);
}
FORCEINLINE float PlatformMath::csc(const float& _radian)
{
	return 1 / sin(_radian);
}
FORCEINLINE float PlatformMath::cot(const float& _radian)
{
	return 1 / tan(_radian);
}
FORCEINLINE float PlatformMath::acos(const float& _radian)
{
	return std::acosf(_radian);
}
FORCEINLINE float PlatformMath::asin(const float& _radian)
{
	return std::asinf(_radian);
}
FORCEINLINE float PlatformMath::atan(const float& _radian)
{
	return std::atanf(_radian);
}
FORCEINLINE float PlatformMath::asec(const float& _radian)
{
	return acos(1 / _radian);
}
FORCEINLINE float PlatformMath::acsc(const float& _radian)
{
	return asin(1 / _radian);
}
FORCEINLINE float PlatformMath::acot(const float& _radian)
{
	return atan(1 / _radian);
}
FORCEINLINE float PlatformMath::radToDeg(const float& _radian)
{
	return _radian * k180overPI;
}
FORCEINLINE float PlatformMath::degToRad(const float& _degree)
{
	return _degree * kPIover180;
}
FORCEINLINE float PlatformMath::fmod(const float& _lval, const float& _rval)
{
	return _lval - static_cast<float>(static_cast<int32>(_lval / _rval)) * _rval;
}
FORCEINLINE float PlatformMath::sqrt(const float& _val)
{
	return pow(_val, 0.5f);
}
FORCEINLINE float PlatformMath::pow(const float& _base, const float& _power)
{
	return std::powf(_base, _power);
}
FORCEINLINE float PlatformMath::round(const float _val)
{
	return static_cast<float>(static_cast<int32>(_val + 0.5f));
}
FORCEINLINE float PlatformMath::floor(const float _val)
{
	return static_cast<float>(static_cast<int32>(_val));
}
FORCEINLINE float PlatformMath::ceil(const float _val)
{
	return (_val - static_cast<int32>(_val)) > 0 ? static_cast<float>(static_cast<int32>(_val + 1)) : _val;
}
FORCEINLINE float PlatformMath::abs(const float _val)
{
	return sqrt(_val * _val);
}
}