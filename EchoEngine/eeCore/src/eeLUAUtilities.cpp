#include "eeLUAUtilities.h"

#include <lua.hpp>


namespace eeEngineSDK {
bool
LUAUtilities::createState(const String& idName)
{
  if (m_luaFiles.find(idName) != m_luaFiles.end()) {
    lua_close(m_luaFiles[idName]);
  }
  m_luaFiles[idName] = luaL_newstate();

  luaL_openlibs(m_luaFiles[idName]);
  return false;
}
bool
LUAUtilities::doFileInState(const String& idName, const String& fileName)
{
  return luaL_dofile(m_luaFiles[idName], fileName.c_str());
}
void
LUAUtilities::registerFunctionInState(const String& idName,
                                      const String& funcName,
                                      luaFuncFormat funcPtr)
{
  lua_register(m_luaFiles[idName], funcName.c_str(), funcPtr);
}
void
LUAUtilities::stackFunctionInState(const String& idName,
                                   const String& funcName)
{
  lua_getglobal(m_luaFiles[idName], funcName.c_str());
}
void
LUAUtilities::callStackedFunctionInState(const String& idName,
                                         int32 argsCount,
                                         int32 returnCount)
{
  lua_pcall(m_luaFiles[idName], argsCount, returnCount, 0);
}

int64
LUAUtilities::getIntegerFromState(const String& idName, int32 argIndex)
{
  return lua_tointeger(m_luaFiles[idName], argIndex);
}
String
LUAUtilities::getStringFromState(const String& idName, int32 argIndex)
{
  return lua_tostring(m_luaFiles[idName], argIndex);
}

void
LUAUtilities::pushIntegerFromState(const String& idName, int64 argValue)
{
  lua_pushinteger(m_luaFiles[idName], argValue);
}
void
LUAUtilities::pushStringFromState(const String& idName, const String& argValue)
{
  lua_pushstring(m_luaFiles[idName], argValue.c_str());
}
}