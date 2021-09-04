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
			Cos(const float& _radian);
		static FORCEINLINE float
			Sin(const float& _radian);
		static FORCEINLINE float
			Tan(const float& _radian);
		static FORCEINLINE float
			Sec(const float& _radian);
		static FORCEINLINE float
			Csc(const float& _radian);
		static FORCEINLINE float
			Cot(const float& _radian);
		static FORCEINLINE float
			ACos(const float& _radian);
		static FORCEINLINE float
			ASin(const float& _radian);
		static FORCEINLINE float
			ATan(const float& _radian);
		static FORCEINLINE float
			ASec(const float& _radian);
		static FORCEINLINE float
			ACsc(const float& _radian);
		static FORCEINLINE float
			ACot(const float& _radian);
		static FORCEINLINE float
			RadToDeg(const float& _radian);
		static FORCEINLINE float
			DegToRad(const float& _degree);
		static FORCEINLINE float
			FMod(const float& _lval, const float& _rval);
		static FORCEINLINE float
			Sqrt(const float& _val);
		static FORCEINLINE float
			Pow(const float& _base, const float& _power);
		static FORCEINLINE float
			Round(const float _val);
		static FORCEINLINE float
			Floor(const float _val);
		static FORCEINLINE float
			Ceil(const float _val);



		static const float kPI;
		static const float kPIover180;
		static const float k180overPI;
	};
}