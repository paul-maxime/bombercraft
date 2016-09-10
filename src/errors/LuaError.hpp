#ifndef LUA_ERROR_HPP_
#define LUA_ERROR_HPP_

#include <stdexcept>
#include <string>

class LuaError : public std::runtime_error
{
public:
  LuaError(const std::string& sender, const std::string& error);
  virtual ~LuaError() throw();
};

#endif
