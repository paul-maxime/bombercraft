/**
 * \file LuaContext.hpp
 * Contains the lua context class.
 */

#ifndef LUA_CONTEXT_HPP_
#define LUA_CONTEXT_HPP_

#include <map>
#include <string>

struct lua_State;

/**
 * \class LuaContext
 * Wrapper for the C lua library.
 */
class LuaContext
{
public:
  /**
   * \typedef t_callback
   * Represents a lua callback function.
   */
  typedef int (*t_callback)(lua_State*);

  /**
   * Constructs a new lua context.
   */
  LuaContext();

  /**
   * Wraps an existing lua context.
   */
  LuaContext(lua_State* lua);

  /**
   * Releases the resources used by the lua context if it was allocated.
   */
  virtual ~LuaContext();

  /**
   * Calls the specified lua function.
   * Internally calls lua_pcall.
   * \param fct Function name.
   */
  void call(const std::string& fct);

  /**
   * Calls the specified lua function.
   * Internally calls lua_pcall.
   * \param fct Function name.
   * \param value Nummeric parameter to pass to the called function.
   */
  void call(const std::string& fct, double value);

  /**
   * Loads a file and executes the loaded block as a function.
   * Internally calls luaL_dofile.
   * \param filename Name of the file to executes.
   */
  void doFile(const std::string& filename);

  /**
   * Register the specified functions into the current lua context.
   * Internally calls lua_register.
   * \param functions a std::map containing the function name and
		      a C++ callback to the function.
   */
  void registerFunctions(const std::map<std::string, t_callback>& functions);

  /**
   * Internally calls lua_gettop.
   * \return the number of elements in the stack.
   */
  int getTop() const;

  /**
   * Gets the last lua error using lua_getstring and lua_gettop.
   * \return a new std::string containing the error message.
   */
  std::string getLastError() const;

  /**
   * Ensures that the arguments count is valid.
   * \param sender Name of the lua function actually checking.
   * \param count Expected argument count.
   * \throw LuaError in case of error.
   */
  void assertArguments(const std::string& sender, int count) const;

  /**
   * Returns the specified argument as a string if possible.
   * \param sender Name of the lua function receiving this param.
   * \param index Index, starting at 1, of the expected argument.
   * \return a new std::string containing the argument.
   * \throw LuaError if the argument is not a string.
   */
  std::string getString(const std::string& sender, int index) const;

  /**
   * Returns the specified argument as an int if possible.
   * \param sender Name of the lua function receiving this param.
   * \param index Index, starting at 1, of the expected argument.
   * \return an int containing the argument.
   * \throw LuaError if the argument is not an int..
   */
  int getInt(const std::string& sender, int index) const;

  /**
   * Returns the specified argument as an double if possible.
   * \param sender Name of the lua function receiving this param.
   * \param index Index, starting at 1, of the expected argument.
   * \return an double containing the argument.
   * \throw LuaError if the argument is not an double..
   */
  double getDouble(const std::string& sender, int index) const;

  /**
   * Returns the specified argument as an boolean if possible.
   * \param sender Name of the lua function receiving this param.
   * \param index Index, starting at 1, of the expected argument.
   * \return an boolean containing the argument.
   * \throw LuaError if the argument is not an boolean..
   */
  bool getBoolean(const std::string& sender, int index) const;

  /**
   * Pushes the specified number on the stack.
   * \param value Value to push.
   */
  void pushNumber(double value);

  /**
   * Pushes the specified boolean on the stack.
   * \param value Value to push.
   */
  void pushBoolean(bool value);

  /**
   * Pushs an hidden global variable into the lua state containing the data.
   * \param data Any pointer that will be saved into the lua state.
   */
  void setUserData(void* data);

  /**
   * Returns the user data specified by the setUserData() function.
   * \return a pointer to the user data.
   */
  void* getUserData() const;

private:
  lua_State*	m_lua;
  bool		m_allocated;
};

#endif
