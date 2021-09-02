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
		static float
			Cos(const float& _radian);
		static float
			Sin(const float& _radian);
		static float
			Tan(const float& _radian);
		static float
			Sec(const float& _radian);
		static float
			Csc(const float& _radian);
		static float
			Cot(const float& _radian);
		static float
			ACos(const float& _radian);
		static float
			ASin(const float& _radian);
		static float
			ATan(const float& _radian);
		static float
			ASec(const float& _radian);
		static float
			ACsc(const float& _radian);
		static float
			ACot(const float& _radian);
		static float
			RadToDeg(const float& _radian);
		static float
			DegToRad(const float& _degree);
		static int
			Mod(const int& _lval, const int& _rval);
		static float
			FMod(const float& _lval, const float& _rval);
		static float
			Sqrt(const float& _val);
		static float
			Pow(const float& _base, const float& _power);
		static float 
			Round(const float _val);
		static float
			Floor(const float _val);
		static float
			Ceil(const float _val);



		static float _PI;
		static float _PIover180;
		static float _180overPI;
	};
}