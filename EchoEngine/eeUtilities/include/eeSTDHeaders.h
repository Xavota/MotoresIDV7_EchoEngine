#pragma once
#include <cassert>

#include <vector>
#include <string>
#include <memory>
#include <cmath>

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
//template<typename T, typename O>
//using Move = std::move<T,O>;

//template<typename _Inlt, typename _Outlt>
//using Copy = std::copy<_Inlt, _Outlt>;
}