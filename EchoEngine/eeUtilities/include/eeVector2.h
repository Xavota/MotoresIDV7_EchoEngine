#pragma once

#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK
{
	template<typename T>
	class eeVector2
	{
	public:
		eeVector2();
		eeVector2(T _X, T _Y);
		~eeVector2();

		float
			Dot(eeVector2 other);
		eeVector2
			Cross(eeVector2 other);

		float 
			Distance(eeVector2 other);

		eeVector2 
			operator+(eeVector2 other);
		eeVector2
			operator-(eeVector2 other);
		eeVector2
			operator*(eeVector2 other);
		eeVector2
			operator/(eeVector2 other);
		eeVector2
			operator%(eeVector2 other);

		eeVector2
			operator=(eeVector2 other);

		eeVector2
			operator+=(eeVector2 other);
		eeVector2
			operator-=(eeVector2 other);
		eeVector2
			operator*=(eeVector2 other);
		eeVector2
			operator/=(eeVector2 other);
		eeVector2
			operator%=(eeVector2 other);

		bool
			operator==(eeVector2 other);
		bool
			operator>(eeVector2 other);
		bool
			operator>=(eeVector2 other);
		bool
			operator<(eeVector2 other);
		bool
			operator<=(eeVector2 other);
	public:
		T x, y;
	};

	template<typename T>
	inline eeVector2<T>::eeVector2()
	{
		
	}
	template
	eeVector2<int>::eeVector2()
	{

	}
	template<typename T>
	inline eeVector2<T>::eeVector2(T _X, T _Y)
	{
	}
	template<typename T>
	inline eeVector2<T>::~eeVector2()
	{
	}
	template<typename T>
	inline float eeVector2<T>::Dot(eeVector2 other)
	{
		return 0.0f;
	}
	template<typename T>
	inline eeVector2<T> eeVector2<T>::Cross(eeVector2 other)
	{
		return eeVector2();
	}
	template<typename T>
	inline float eeVector2<T>::Distance(eeVector2 other)
	{
		return 0.0f;
	}
	template<typename T>
	inline eeVector2<T> eeVector2<T>::operator+(eeVector2 other)
	{
		return eeVector2();
	}
	template<typename T>
	inline eeVector2<T> eeVector2<T>::operator-(eeVector2 other)
	{
		return eeVector2();
	}
	template<typename T>
	inline eeVector2<T> eeVector2<T>::operator*(eeVector2 other)
	{
		return eeVector2();
	}
	template<typename T>
	inline eeVector2<T> eeVector2<T>::operator/(eeVector2 other)
	{
		return eeVector2();
	}
	template<typename T>
	inline eeVector2<T> eeVector2<T>::operator%(eeVector2 other)
	{
		return eeVector2();
	}
	template<typename T>
	inline eeVector2<T> eeVector2<T>::operator=(eeVector2 other)
	{
		return eeVector2();
	}
	template<typename T>
	inline eeVector2<T> eeVector2<T>::operator+=(eeVector2 other)
	{
		return eeVector2();
	}
	template<typename T>
	inline eeVector2<T> eeVector2<T>::operator-=(eeVector2 other)
	{
		return eeVector2();
	}
	template<typename T>
	inline eeVector2<T> eeVector2<T>::operator*=(eeVector2 other)
	{
		return eeVector2();
	}
	template<typename T>
	inline eeVector2<T> eeVector2<T>::operator/=(eeVector2 other)
	{
		return eeVector2();
	}
	template<typename T>
	inline eeVector2<T> eeVector2<T>::operator%=(eeVector2 other)
	{
		return eeVector2();
	}
	template<typename T>
	inline bool eeVector2<T>::operator==(eeVector2 other)
	{
		return false;
	}
	template<typename T>
	inline bool eeVector2<T>::operator>(eeVector2 other)
	{
		return false;
	}
	template<typename T>
	inline bool eeVector2<T>::operator>=(eeVector2 other)
	{
		return false;
	}
	template<typename T>
	inline bool eeVector2<T>::operator<(eeVector2 other)
	{
		return false;
	}
	template<typename T>
	inline bool eeVector2<T>::operator<=(eeVector2 other)
	{
		return false;
	}
}
