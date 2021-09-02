#pragma once

#include <vector>
#include <string>
#include <memory>

namespace eeEngineSDK
{

	/*
	 * @brief Vector
	 */
	template<typename T, typename A = std::allocator<T>>
	using Vector = std::vector<T, A>;

	using String = std::string;
	using WString = std::wstring;

	template<typename T>
	using SPtr = std::shared_ptr<T>;
}