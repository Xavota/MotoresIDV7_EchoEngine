/************************************************************************/
/**
 * @file eeLUAUtilities.h
 * @author Diego Castellanos
 * @date 07/06/22
 * @brief
 * The LUA interface to do task from and with LUA files.
 *
 * @bug Not bug Known.
 */
 /************************************************************************/

#pragma once
#include "eePrerequisitesCore.h"

class lua_State;

namespace eeEngineSDK {
using luaFuncFormat = int (*) (lua_State* L);

/**
 * @brief
 * The LUA interface to do task from and with LUA files.}
 */
class LUAUtilities
{
 public:
  /**
   * @brief
   * Default constructor
   */
   LUAUtilities() = default;
  /**
   * @brief
   * Default destructor
   */
  virtual
  ~LUAUtilities() = default;

  /**
   * @brief
   * Creates a new LUA state.
   *
   * @description
   * Creates a new LUA state and stores it with the id name.
   *
   * @param idName
   * The name of the state to identify it for further use.
   *
   * @return
   * Weather it succeed or failed to open.
   */
  bool
  createState(const String& idName);

  /**
   * @brief
   * Does a new LUA file.
   *
   * @description
   * Opens the LUA file and places it in the stack.
   *
   * @param idName
   * The name of the state to open the file on.
   * @param fileName
   * The path of the LUA file to open.
   *
   * @return
   * Weather it succeed or failed to open.
   */
  bool
  doFileInState(const String& idName, const String& fileName);

  /**
   * @brief
   * Registers a new function in the state.
   *
   * @description
   * Registers a new c++ function in the state with the given name.
   *
   * @param idName
   * The name of the state to register the function on.
   * @param funcName
   * The name of the function to register. The name that will be used in LUA.
   * @param funcPtr
   * The pointer to the function to register. It has to be with the format
   * int foo(lua_State*)
   */
  void
  registerFunctionInState(const String& idName,
                          const String& funcName,
                          luaFuncFormat funcPtr);

  /**
   * @brief
   * Look a function in the LUA file.
   *
   * @description
   * Search a function in LUA files and stores it in the state stack.
   *
   * @param idName
   * The name of the state to look for the function.
   * @param funcName
   * The name of the function looking for. The name of a LUA function.
   */
  void
  stackFunctionInState(const String& idName,
                       const String& funcName);

  /**
   * @brief
   * Calls the first function in the stack.
   *
   * @description
   * Calls the first function in the stack of the state.
   *
   * @param idName
   * The name of the state to call the function.
   * @param argsCount
   * The number of arguments the calling function has.
   * @param returnCount
   * The number of returns the calling function has.
   */
  void
  callStackedFunctionInState(const String& idName,
                             int32 argsCount,
                             int32 returnCount);

  /**
   * @brief
   * Gets an integer value.
   *
   * @description
   * Gets an integer value from the state stack using the index of the argument.
   *
   * @param idName
   * The name of the state to get the integer.
   * @param argsIndex
   * The index of the integer argument looking for.
   * 
   * @return
   * The integer value on that index.
   */
  int64
  getIntegerFromState(const String& idName,
                      int32 argIndex);
  /**
   * @brief
   * Gets a string value.
   *
   * @description
   * Gets a string value from the state stack using the index of the argument.
   *
   * @param idName
   * The name of the state to get the integer.
   * @param argsIndex
   * The index of the string argument looking for.
   * 
   * @return
   * The string value on that index.
   */
  String
  getStringFromState(const String& idName,
                     int32 argIndex);

  /**
   * @brief
   * Push an integer value.
   *
   * @description
   * Push an integer value to the state stack.
   *
   * @param idName
   * The name of the state to push the integer.
   * @param argValue
   * The integer value to push.
   */
  void
  pushIntegerFromState(const String& idName,
                       int64 argValue);
  /**
   * @brief
   * Push a string value.
   *
   * @description
   * Push a string value to the state stack.
   *
   * @param idName
   * The name of the state to push the integer.
   * @param argValue
   * The string value to push.
   */
  void
  pushStringFromState(const String& idName,
                      const String& argValue);

 private:
  /**
   * The LUA states stored with its names. Each represent a different file.
   */
  Map<String, lua_State*> m_luaFiles;
};
}
