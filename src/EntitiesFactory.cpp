#include "Player.hpp"
#include "LuaPlayer.hpp"
#include "Bomb.hpp"
#include "Box.hpp"
#include "Explosion.hpp"
#include "SolidWall.hpp"
#include "Wall.hpp"
#include "Map.hpp"
#include "PlayerSpeedBonus.hpp"
#include "BombQuantityBonus.hpp"
#include "BombRangeBonus.hpp"
#include "BombPushBonus.hpp"
#include "EntitiesFactory.hpp"

EntitiesFactory* EntitiesFactory::m_instance = NULL;

EntitiesFactory::EntitiesFactory()
{
  m_generateAEntity[EntitiesFactory::PLAYER] = &EntitiesFactory::generateAnyEntity<Player>;
  m_generateAEntity[EntitiesFactory::LUA_PLAYER] = &EntitiesFactory::generateAnyEntity<LuaPlayer>;
  m_generateAEntity[EntitiesFactory::BOMB] = &EntitiesFactory::generateAnyEntity<Bomb>;
  m_generateAEntity[EntitiesFactory::BOX] = &EntitiesFactory::generateAnyEntity<Box>;
  m_generateAEntity[EntitiesFactory::EXPLOSION] = &EntitiesFactory::generateAnyEntity<Explosion>;
  m_generateAEntity[EntitiesFactory::SOLID_WALL] = &EntitiesFactory::generateAnyEntity<SolidWall>;
  m_generateAEntity[EntitiesFactory::WALL] = &EntitiesFactory::generateAnyEntity<Wall>;
  m_generateAEntity[EntitiesFactory::PLAYER_SPEED_BONUS] = &EntitiesFactory::generateAnyEntity<PlayerSpeedBonus>;
  m_generateAEntity[EntitiesFactory::BOMB_QUANTITY_BONUS] = &EntitiesFactory::generateAnyEntity<BombQuantityBonus>;
  m_generateAEntity[EntitiesFactory::BOMB_RANGE_BONUS] = &EntitiesFactory::generateAnyEntity<BombRangeBonus>;
  m_generateAEntity[EntitiesFactory::BOMB_PUSH_BONUS] = &EntitiesFactory::generateAnyEntity<BombPushBonus>;

  m_bonus.push_back(EntitiesFactory::PLAYER_SPEED_BONUS);
  m_bonus.push_back(EntitiesFactory::BOMB_QUANTITY_BONUS);
  m_bonus.push_back(EntitiesFactory::BOMB_RANGE_BONUS);
  m_bonus.push_back(EntitiesFactory::BOMB_PUSH_BONUS);

  m_convert[AEntity::PLAYER] = EntitiesFactory::PLAYER;
  m_convert[AEntity::BOMB] = EntitiesFactory::BOMB;
  m_convert[AEntity::BOX] = EntitiesFactory::BOX;
  m_convert[AEntity::EXPLOSION] = EntitiesFactory::EXPLOSION;
  m_convert[AEntity::SOLID_WALL] = EntitiesFactory::SOLID_WALL;
  m_convert[AEntity::WALL] = EntitiesFactory::WALL;
  m_convert[AEntity::BONUS] = EntitiesFactory::BONUS;
}

EntitiesFactory::~EntitiesFactory()
{
}

EntitiesFactory*	EntitiesFactory::getInstance()
{
  if (!m_instance)
    m_instance = new EntitiesFactory();
  return (m_instance);
}

void			EntitiesFactory::destroy()
{
  if (m_instance)
    {
      delete (m_instance);
      m_instance = NULL;
    }
}

AEntity*	EntitiesFactory::generateEntity(Map* map, int posX, int posY,
						EntitiesFactory::FactoryType type)
{
  if (m_generateAEntity.find(type) == m_generateAEntity.end())
    return (NULL);
  return (this->*(m_generateAEntity[type]))(map, posX, posY);
}

AEntity*	EntitiesFactory::generateRandomBonus(Map* map, int posX, int posY)
{
  unsigned int	bonusRoll = std::rand() % m_bonus.size();

  return (generateEntity(map, posX, posY, m_bonus[bonusRoll]));
}

EntitiesFactory::FactoryType	EntitiesFactory::convert(AEntity::Type type) const
{
  if (m_convert.find(type) == m_convert.end())
    return (EntitiesFactory::UNKNOWN);
  return (m_convert.at(type));
}
