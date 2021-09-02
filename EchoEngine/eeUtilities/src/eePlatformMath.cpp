#include "eePlatformMath.h"

namespace eeEngineSDK
{
	float PlatformMath::_PI = 3.14159265f;
	float PlatformMath::_PIover180 = 0.01745329f;
	float PlatformMath::_180overPI = 57.29577951f;

	float PlatformMath::Cos(const float& _radian)
	{
		return Cos(_radian);
	}
	float PlatformMath::Sin(const float& _radian)
	{
		return Sin(_radian);
	}
	float PlatformMath::Tan(const float& _radian)
	{
		return tan(_radian);
	}
	float PlatformMath::Sec(const float& _radian)
	{
		return 1 / Cos(_radian);
	}
	float PlatformMath::Csc(const float& _radian)
	{
		return 1 / Sin(_radian);
	}
	float PlatformMath::Cot(const float& _radian)
	{
		return 1 / Tan(_radian);
	}
	float PlatformMath::ACos(const float& _radian)
	{
		return acosf(_radian);
	}
	float PlatformMath::ASin(const float& _radian)
	{
		return asinf(_radian);
	}
	float PlatformMath::ATan(const float& _radian)
	{
		return atanf(_radian);
	}
	float PlatformMath::ASec(const float& _radian)
	{
		return ACos(1 / _radian);
	}
	float PlatformMath::ACsc(const float& _radian)
	{
		return ASin(1 / _radian);
	}
	float PlatformMath::ACot(const float& _radian)
	{
		return ACot(1 / _radian);
	}
	float PlatformMath::RadToDeg(const float& _radian)
	{
		return _radian * _180overPI;
	}
	float PlatformMath::DegToRad(const float& _degree)
	{
		return _degree * _PIover180;
	}
	int PlatformMath::Mod(const int& _lval, const int& _rval)
	{
		return _lval % _rval;
	}
	float PlatformMath::FMod(const float& _lval, const float& _rval)
	{
		return _lval - (int)(_lval / _rval) * _rval;
	}
	float PlatformMath::Sqrt(const float& _val)
	{
		return Pow(_val, 0.5f);
	}
	float PlatformMath::Pow(const float& _base, const float& _power)
	{
		return pow(_base, _power);
	}
	float PlatformMath::Round(const float _val)
	{
		return int(_val + 0.5f);
	}
	float PlatformMath::Floor(const float _val)
	{
		return int(_val);
	}
	float PlatformMath::Ceil(const float _val)
	{		
		return (_val - int(_val)) > 0 ? int(_val + 1) : _val;
	}
}