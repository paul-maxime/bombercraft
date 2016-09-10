#include <iostream>

#include "AI.hpp"
#include "LuaContext.hpp"
#include "LuaPlayer.hpp"
#include "Map.hpp"
#include "ObstacleMap.hpp"

int AI::log(lua_State* L)
{
  LuaContext lua(L);
  lua.assertArguments("aiLog", 1);
  std::cout << lua.getString("aiLog", 1) << std::endl;
  return 0;
}

int AI::getPosition(lua_State* L)
{
  LuaContext lua(L);
  lua.assertArguments("getPosition", 0);
  LuaPlayer* player = reinterpret_cast<LuaPlayer*>(lua.getUserData());
  lua.pushNumber(player->getRealPosition().x);
  lua.pushNumber(player->getRealPosition().y);
  return 2;
}

int AI::getMapSize(lua_State* L)
{
  LuaContext lua(L);
  lua.assertArguments("getMapSize", 0);
  LuaPlayer* player = reinterpret_cast<LuaPlayer*>(lua.getUserData());
  lua.pushNumber(player->getMap()->getWidth());
  lua.pushNumber(player->getMap()->getHeight());
  return 2;
}

int AI::getNearestPlayer(lua_State* L)
{
  LuaContext lua(L);
  lua.assertArguments("getNearestPlayer", 0);
  LuaPlayer* player = reinterpret_cast<LuaPlayer*>(lua.getUserData());
  const Player* near = player->getNearestPlayer();
  if (near)
    {
      lua.pushNumber(near->getRealPosition().x);
      lua.pushNumber(near->getRealPosition().y);
    }
  else
    {
      lua.pushNumber(-1);
      lua.pushNumber(-1);
    }
  return 2;
}

int AI::isDangerAt(lua_State* L)
{
  LuaContext lua(L);
  lua.assertArguments("isDangerAt", 2);
  LuaPlayer* player = reinterpret_cast<LuaPlayer*>(lua.getUserData());
  int x = lua.getInt("isDangerAt", 1);
  int y = lua.getInt("isDangerAt", 2);
  lua.pushBoolean(player->getObstacleMap()->isDangerAt(x, y));
  return 1;
}

int AI::mapGet(lua_State* L)
{
  LuaContext lua(L);
  lua.assertArguments("mapGet", 2);
  int x = lua.getInt("mapGet", 1);
  int y = lua.getInt("mapGet", 2);
  LuaPlayer* player = reinterpret_cast<LuaPlayer*>(lua.getUserData());
  lua.pushNumber(player->getObstacleMap()->get(x, y));
  return 1;
}

int AI::distanceTo(lua_State* L)
{
  LuaContext lua(L);
  lua.assertArguments("distanceTo", 2);
  float x = lua.getDouble("distanceTo", 1);
  float y = lua.getDouble("distanceTo", 2);
  LuaPlayer* player = reinterpret_cast<LuaPlayer*>(lua.getUserData());
  float distance = std::abs(player->getRealPosition().x - x) +
    std::abs(player->getRealPosition().y - y);
  lua.pushNumber(distance);
  return 1;
}

int AI::getBombs(lua_State* L)
{
  LuaContext lua(L);
  lua.assertArguments("getBombs", 0);
  LuaPlayer* player = reinterpret_cast<LuaPlayer*>(lua.getUserData());
  lua.pushNumber(player->getBombs());
  return 1;
}

int AI::placeBomb(lua_State* L)
{
  LuaContext lua(L);
  lua.assertArguments("placeBomb", 0);
  LuaPlayer* player = reinterpret_cast<LuaPlayer*>(lua.getUserData());
  player->placeBomb();
  return 0;
}

int AI::moveTo(lua_State* L)
{
  LuaContext lua(L);
  lua.assertArguments("moveTo", 3);
  float x = lua.getDouble("moveTo", 1);
  float y = lua.getDouble("moveTo", 2);
  bool run = lua.getBoolean("moveTo", 3);
  LuaPlayer* player = reinterpret_cast<LuaPlayer*>(lua.getUserData());
  player->moveTo(x, y, run);
  return 0;
}
