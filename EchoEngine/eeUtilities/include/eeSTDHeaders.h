#pragma once
#include <cassert>

#include <iostream>

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

//using Cout = std::cout;
//const std::ostream& Cout = std::cout;
//const std::basic_ostream& Endl = std::endl;
}