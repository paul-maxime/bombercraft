/**
 * \file AI.hpp
 * Contains the AI static class.
 */

#ifndef AI_HPP_
#define AI_HPP_

struct lua_State;

/**
 * \class AI
 * This static class contains every functions callable from a lua script.
 */
class AI
{
public:
  static int log(lua_State* L);
  static int getPosition(lua_State* L);
  static int getMapSize(lua_State* L);
  static int getNearestPlayer(lua_State* L);
  static int isDangerAt(lua_State* L);
  static int mapGet(lua_State* L);
  static int distanceTo(lua_State* L);
  static int getBombs(lua_State* L);
  static int placeBomb(lua_State* L);
  static int moveTo(lua_State* L);

private:
  AI();
};

#endif
