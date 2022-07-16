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

#define STD
//#define BOOST

#include <cassert>

#if defined(STD)
#include <vector>
#include <map>
#include <memory>
#include <cmath>
#include <functional>
#elif defined(BOOST)
#include <boost/container/vector.hpp>
#include <boost/container/flat_map.hpp>
//#include <boost/compressed_pair.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
//#include <boost/filesystem/fstream.hpp>
//#include <boost/iostreams/>
#include <boost/function.hpp>
#endif

#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

//#include <stringapiset.h>

#include "eePlatformTypes.h"

namespace eeEngineSDK
{
#if defined(STD)
using std::vector;
using std::map;
//using std::pair;
using std::shared_ptr;
using std::weak_ptr;
using std::enable_shared_from_this;
//using std::fstream;
//using std::ifstream;
//using std::ofstream;
using std::function;

/*
 * @brief Dynamic Array of objects
 */
template<typename T, typename A = std::allocator<T>>
using Vector = vector<T, A>;
/*
 * @brief Library with a key and value
 */
template<typename T, typename U>
using Map = map<T, U>;
///*
// * @brief Variable with a key and a value
// */
//template<typename T, typename U>
//using Pair = pair<T, U>;
/*
 * @brief Smart pointer
 */
template<typename T>
using SPtr = shared_ptr<T>;
template<typename T>
using WPtr = weak_ptr<T>;
/*
 * @brief For parenting on smart pointer use. Enable getting a SPtr from 'this'.
 */
template<typename T>
using EnableSPtrFromThis = enable_shared_from_this<T>;

///*
// * @brief File stream
// */
//using FStream = fstream;
///*
// * @brief Input file stream
// */
//using IFStream = ifstream;
///*
// * @brief Output file stream
// */
//using OFStream = ofstream;

template<class FType>
using Function = function<FType>;
#elif defined(BOOST)
using boost::container::vector;
using boost::container::flat_map;
//using boost::compressed_pair;
using boost::shared_ptr;
using boost::weak_ptr;
using boost::enable_shared_from_this;
//using boost::filesystem::basic_fstream;
//using boost::filesystem::basic_ifstream;
//using boost::filesystem::basic_ofstream;
using boost:function;

/*
 * @brief Dynamic Array of objects
 */
template<typename T>
using Vector = vector<T>;
/*
 * @brief Library with a key and value
 */
template<typename T, typename U>
using Map = flat_map<T, U>;
///*
// * @brief Variable with a key and a value
// */
//template<typename T, typename U>
//using Pair = compressed_pair<T, U>;
/*
 * @brief Smart pointer
 */
template<typename T>
using SPtr = shared_ptr<T>;
template<typename T>
using WPtr = weak_ptr<T>;
/*
 * @brief For parenting on smart pointer use. Enable getting a SPtr from 'this'.
 */
template<typename T>
using EnableSPtrFromThis = enable_shared_from_this<T>;

///*
// * @brief File stream
// */
//using FStream = basic_fstream;
///*
// * @brief Input file stream
// */
//using IFStream = basic_ifstream;
///*
// * @brief Output file stream
// */
//using OFStream = basic_ofstream;

template<class RetType, class... Args>
using Function = function<RetType(Args)>;
#endif

using std::pair;
using std::string;
using std::wstring;
using std::forward;
using std::fstream;
using std::ifstream;
using std::ofstream;
/*
 * @brief Variable with a key and a value
 */
template<typename T, typename U>
using Pair = pair<T, U>;
/*
 * @brief Basic const char*
 */
using String = string;
/*
 * @brief Wide const char*
 */
using WString = wstring;
/*
 * @brief File stream
 */
using FStream = fstream;
/*
 * @brief Input file stream
 */
using IFStream = ifstream;
/*
 * @brief Output file stream
 */
using OFStream = ofstream;






}