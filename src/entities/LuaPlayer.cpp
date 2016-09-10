#include <map>
#include <string>

#include "EntitiesFactory.hpp"
#include "LuaPlayer.hpp"
#include "LuaError.hpp"
#include "Map.hpp"
#include "Bomb.hpp"
#include "Pathfinding.hpp"
#include "ObstacleMap.hpp"
#include "AI.hpp"

LuaPlayer::LuaPlayer(Map* map, int posX, int posY)
  : Player(map, posX, posY),
    m_aiMap(0),
    m_moveX(-1),
    m_moveY(-1),
    m_runAway(false)
{
  m_lua.doFile("data/ai/ai.lua");
  m_lua.setUserData(this);
  std::map<std::string, LuaContext::t_callback> fcts;
  fcts["aiLog"] = &AI::log;
  fcts["aiGetPosition"] = &AI::getPosition;
  fcts["aiGetMapSize"] = &AI::getMapSize;
  fcts["aiGetNearestPlayer"] = &AI::getNearestPlayer;
  fcts["aiIsDangerAt"] = &AI::isDangerAt;
  fcts["aiMapGet"] = &AI::mapGet;
  fcts["aiDistanceTo"] = &AI::distanceTo;
  fcts["aiGetBombs"] = &AI::getBombs;
  fcts["aiPlaceBomb"] = &AI::placeBomb;
  fcts["aiMoveTo"] = &AI::moveTo;
  m_lua.registerFunctions(fcts);
}

LuaPlayer::~LuaPlayer()
{
}

const Map* LuaPlayer::getMap() const
{
  return _map;
}

const ObstacleMap* LuaPlayer::getObstacleMap() const
{
  return m_aiMap;
}

const Player* LuaPlayer::getNearestPlayer() const
{
  std::vector<Player*>::const_iterator it;
  int bestDistance(-1);
  const Player* bestPlayer(0);
  for (it =_map->getPlayers().begin(); it != _map->getPlayers().end(); ++it)
    {
      const Player* player = *it;
      int distance = distanceTo(*player);
      if (player != this && player->isAlive() > 0 &&
	  (bestDistance == -1 || distance < bestDistance))
	{
	  bestDistance = distance;
	  bestPlayer = player;
	}
    }
  return bestPlayer;
}

void LuaPlayer::moveTo(int x, int y, bool run)
{
  m_moveX = x;
  m_moveY = y;
  m_runAway = run;
}

void LuaPlayer::applyMovement()
{
  int posX = getRealPosition().x;
  int posY = getRealPosition().y;

  int destX = m_moveX;
  int destY = m_moveY;

  Pathfinding path(m_aiMap,
		   Pathfinding::Node(posX, posY),
		   Pathfinding::Node(m_moveX, m_moveY),
		   m_runAway);

  if (path.isSolved())
    {
      const Pathfinding::Node& to = path.getDestination();
      m_moveX = to.first;
      m_moveY = to.second;
      const Pathfinding::Node* next = path.next(Pathfinding::Node(posX, posY));
      if (next)
	applyMoveTo(posX, posY, next->first, next->second);
    }
  else
    applyMoveTo(posX, posY, destX, destY);
}

void LuaPlayer::applyMoveTo(int posX, int posY, int destX, int destY)
{
  if (posX > destX && !(m_aiMap->get(posX - 1, posY) & ObstacleMap::EXPLOSION))
    addDirection(AEntity::LEFT);
  else if (posX < destX && !(m_aiMap->get(posX + 1, posY) & ObstacleMap::EXPLOSION))
    addDirection(AEntity::RIGHT);
  if (posY > destY && !(m_aiMap->get(posX, posY - 1) & ObstacleMap::EXPLOSION))
    addDirection(AEntity::UP);
  else if (posY < destY && !(m_aiMap->get(posX , posY + 1) & ObstacleMap::EXPLOSION))
    addDirection(AEntity::DOWN);
}

void LuaPlayer::applyInputs()
{
  int posX = getRealPosition().x;
  int posY = getRealPosition().y;

  m_aiMap = new ObstacleMap(_map, posX, posY, 20);

  try
    {
      m_lua.call("main");
    }
  catch (const LuaError& e)
    {
      std::cerr << e.what() << std::endl;
      kill();
    }

  if (m_moveX != -1 && m_moveY != -1)
    applyMovement();

  delete m_aiMap;
}

void LuaPlayer::update(gdl::Clock const &clock)
{
  if (!isAlive())
    return;
  Player::update(clock);
  try
    {
      m_lua.call("update", clock.getElapsed());
    }
  catch (const LuaError& e)
    {
      std::cerr << e.what() << std::endl;
      kill();
    }
}

void LuaPlayer::serialize(std::ostream& out) const
{
  writeInFile<EntitiesFactory::FactoryType>(EntitiesFactory::LUA_PLAYER, out);
  Player::serialize(out);
}

void LuaPlayer::unserialize(std::istream& in)
{
  EntitiesFactory::FactoryType	type;
  readFromFile<EntitiesFactory::FactoryType>(type, in);
  Player::unserialize(in);
}
