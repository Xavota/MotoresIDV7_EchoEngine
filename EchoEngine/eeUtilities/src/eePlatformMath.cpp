#include "eePlatformMath.h"

namespace eeEngineSDK
{
const float PlatformMath::kPI = 3.14159265f;
const float PlatformMath::kPIover180 = 0.01745329f;
const float PlatformMath::k180overPI = 57.29577951f;

float PlatformMath::cos(const float& _radian)
{
	return std::cosf(_radian);
}
float PlatformMath::sin(const float& _radian)
{
	return std::sinf(_radian);
}
float PlatformMath::tan(const float& _radian)
{
	return std::tanf(_radian);
}
float PlatformMath::sec(const float& _radian)
{
	return 1 / cos(_radian);
}
float PlatformMath::csc(const float& _radian)
{
	return 1 / sin(_radian);
}
float PlatformMath::cot(const float& _radian)
{
	return 1 / tan(_radian);
}
float PlatformMath::acos(const float& _radian)
{
	return std::acosf(_radian);
}
float PlatformMath::asin(const float& _radian)
{
	return std::asinf(_radian);
}
float PlatformMath::atan(const float& _radian)
{
	return std::atanf(_radian);
}
float PlatformMath::asec(const float& _radian)
{
	return acos(1 / _radian);
}
float PlatformMath::acsc(const float& _radian)
{
	return asin(1 / _radian);
}
float PlatformMath::acot(const float& _radian)
{
	return acot(1 / _radian);
}
float PlatformMath::radToDeg(const float& _radian)
{
	return _radian * k180overPI;
}
float PlatformMath::degToRad(const float& _degree)
{
	return _degree * kPIover180;
}
float PlatformMath::fmod(const float& _lval, const float& _rval)
{
	return _lval - static_cast<int32>(_lval / _rval) * _rval;
}
float PlatformMath::sqrt(const float& _val)
{
	return pow(_val, 0.5f);
}
float PlatformMath::pow(const float& _base, const float& _power)
{
	return std::powf(_base, _power);
}
float PlatformMath::round(const float _val)
{
	return static_cast<int32>(_val + 0.5f);
}
float PlatformMath::floor(const float _val)
{
	return static_cast<int32>(_val);
}
float PlatformMath::ceil(const float _val)
{
	return (_val - static_cast<int32>(_val)) > 0 ? static_cast<int32>(_val + 1) : _val;
}
float PlatformMath::abs(const float _val)
{
	return sqrt(_val * _val);
}
}