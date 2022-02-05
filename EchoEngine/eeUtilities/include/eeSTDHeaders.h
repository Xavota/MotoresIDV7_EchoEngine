/************************************************************************/
/**
 * @file eeSTDHeathers.h
 * @author Diego Castellanos
 * @date 03/09/21
 * @brief All the includes and wraps for the std library.
 *
 * @bug Not bug Known.
 */
/************************************************************************/

#pragma once
#include <cassert>

#include <iostream>

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <cmath>
#include <fstream>
#include <chrono>

#include "eePlatformTypes.h"

namespace eeEngineSDK
{
/*
 * @brief Dynamic Array of objects
 */
template<typename T, typename A = std::allocator<T>>
using Vector = std::vector<T, A>;
/*
 * @brief Library with a key and value
 */
template<typename T, typename U>
using Map = std::map<T, U>;
/*
 * @brief Variable with a key and a value
 */
template<typename T, typename U>
using Pair = std::pair<T, U>;

/*
 * @brief Basic const char*
 */
using String = std::string;
/*
 * @brief Wide const char*
 */
using WString = std::wstring;

/*
 * @brief Smart pointer
 */
template<typename T>
using SPtr = std::shared_ptr<T>;
/*
 * @brief For parenting on smart pointer use. Enable getting a SPtr from 'this'.
 */
template<typename T>
using EnableSPtrFromThis = std::enable_shared_from_this<T>;

/*
 * @brief File stream
 */
using FStream = std::fstream;
/*
 * @brief Input file stream
 */
using IFStream = std::ifstream;
/*
 * @brief Output file stream
 */
using OFStream = std::ofstream;
}