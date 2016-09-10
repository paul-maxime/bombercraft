/**
 * \file LuaPlayer.hpp
 * Defines the Lua Player entity.
 */

#ifndef LUA_PLAYER_HPP_
#define LUA_PLAYER_HPP_

#include "Player.hpp"
#include "LuaContext.hpp"

class ObstacleMap;

/**
 * \class LuaPlayer
 * Represents an AI Player controlled by a lua script.
 */
class LuaPlayer : public Player
{
public:
  LuaPlayer(Map* map, int posX, int posY);
  virtual ~LuaPlayer();

  const Map*		getMap() const;
  const ObstacleMap*	getObstacleMap() const;
  const Player*		getNearestPlayer() const;

  void		moveTo(int x, int y, bool run);
  void		applyMovement();
  void		applyMoveTo(int posX, int posY, int destX, int destY);

  virtual void	applyInputs();
  virtual void	update(gdl::Clock const &clock);

  virtual void	serialize(std::ostream& out) const;
  virtual void	unserialize(std::istream& in);

private:
  ObstacleMap*	m_aiMap;
  LuaContext	m_lua;
  int		m_moveX;
  int		m_moveY;
  bool		m_runAway;
};

#endif
