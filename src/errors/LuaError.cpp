#include "LuaError.hpp"

LuaError::LuaError(const std::string& sender, const std::string& error)
  : std::runtime_error("LuaContext::" + sender + error)
{
}

LuaError::~LuaError() throw()
{
}
