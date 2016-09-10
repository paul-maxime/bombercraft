#include <stdexcept>
#include <lua.hpp>
#include "LuaContext.hpp"
#include "LuaError.hpp"
#include "Utils.hpp"

LuaContext::LuaContext()
  : m_lua(0),
    m_allocated(true)
{
  m_lua = luaL_newstate();
  if (!m_lua)
    throw std::bad_alloc();
}

LuaContext::LuaContext(lua_State *lua)
  : m_lua(lua),
    m_allocated(false)
{
}

LuaContext::~LuaContext()
{
  if (m_allocated && m_lua)
    lua_close(m_lua);
}

void LuaContext::call(const std::string& fct)
{
  lua_getglobal(m_lua, fct.c_str());
  if (lua_pcall(m_lua, 0, LUA_MULTRET, 0))
    throw LuaError("call", "(" + fct + "): " + getLastError());
}

void LuaContext::call(const std::string& fct, double value)
{
  lua_getglobal(m_lua, fct.c_str());
  lua_pushnumber(m_lua, value);
  if (lua_pcall(m_lua, 1, LUA_MULTRET, 0))
    throw LuaError("call", "(" + fct + ", " + Utils::toString(value) + "): " + getLastError());
}

void LuaContext::doFile(const std::string& filename)
{
  if (luaL_dofile(m_lua, filename.c_str()))
    throw LuaError("doFile", "(" + filename + "): " + getLastError());
}

void LuaContext::registerFunctions(const std::map<std::string, t_callback>& functions)
{
  std::map<std::string, t_callback>::const_iterator it;

  for (it = functions.begin(); it != functions.end(); ++it)
    lua_register(m_lua, it->first.c_str(), it->second);
}

int LuaContext::getTop() const
{
  return lua_gettop(m_lua);
}

std::string LuaContext::getLastError() const
{
  const char* cstr(lua_tostring(m_lua, lua_gettop(m_lua)));
  if (cstr)
    return std::string(cstr);
  return std::string("unknown error");
}

void LuaContext::assertArguments(const std::string& sender, int count) const
{
  int argc = lua_gettop(m_lua);
  if (lua_gettop(m_lua) != count)
    throw LuaError("assert", "(" + sender + "): expected " +
		   Utils::toString(count) + " arguments, got " +
		   Utils::toString(argc));
}

std::string LuaContext::getString(const std::string& sender, int index) const
{
  const char* cstr;
  if (!lua_isstring(m_lua, index) || !(cstr = lua_tostring(m_lua, index)))
    throw LuaError("getString", "(" + sender + ", " +
		   Utils::toString(index) +
		   "): expected a string value");
  return std::string(cstr);
}

int LuaContext::getInt(const std::string& sender, int index) const
{
  int value;
  if (!lua_isstring(m_lua, index))
    throw LuaError("getInt", "(" + sender + ", " +
		   Utils::toString(index) +
		   "): expected a numeric value");
  value = lua_tonumber(m_lua, index);
  return value;
}

double LuaContext::getDouble(const std::string& sender, int index) const
{
  double value;
  if (!lua_isnumber(m_lua, index))
    throw LuaError("getDouble", "(" + sender + ", " +
		   Utils::toString(index) +
		   "): expected a numeric value");
  value = lua_tonumber(m_lua, index);
  return value;
}

bool LuaContext::getBoolean(const std::string& sender, int index) const
{
  bool value;
  if (!lua_isboolean(m_lua, index))
    throw LuaError("getBoolean", "(" + sender + ", " +
		   Utils::toString(index) +
		   "): expected a boolean value");
  value = lua_toboolean(m_lua, index);
  return value;
}

void LuaContext::pushNumber(double value)
{
  lua_pushnumber(m_lua, value);
}

void LuaContext::pushBoolean(bool value)
{
  lua_pushboolean(m_lua, value);
}

void LuaContext::setUserData(void* data)
{
  lua_pushlightuserdata(m_lua, data);
  lua_setglobal(m_lua, "__luacontext_data");
}

void* LuaContext::getUserData() const
{
  lua_getglobal(m_lua, "__luacontext_data");
  void *ptr = lua_touserdata(m_lua, lua_gettop(m_lua));
  if (!ptr)
    throw LuaError("getUserData", "no user data in the current context");
  lua_pop(m_lua, 1);
  return ptr;
}
