#ifndef ENTITIES_FACTORY_HPP_
#define ENTITIES_FACTORY_HPP_

#include <map>

#include "AEntity.hpp"

class Player;
class Map;

class EntitiesFactory
{
public:
  enum FactoryType
    {
      UNKNOWN,
      BOMB,
      BONUS,
      PLAYER_SPEED_BONUS,
      BOMB_QUANTITY_BONUS,
      BOMB_RANGE_BONUS,
      BOMB_PUSH_BONUS,
      BOX,
      EXPLOSION,
      FLOOR,
      PLAYER,
      LUA_PLAYER,
      SOLID_WALL,
      WALL
    };

  static EntitiesFactory*	getInstance();
  static void			destroy();

  AEntity*			generateEntity(Map *map, int posX, int posY, FactoryType type);
  AEntity*			generateRandomBonus(Map* map, int posX, int posY);
  FactoryType			convert(AEntity::Type type) const;

private:
  EntitiesFactory();
  virtual ~EntitiesFactory();
  EntitiesFactory(const EntitiesFactory&);
  EntitiesFactory	&operator=(const EntitiesFactory&);

  template<typename T>
  AEntity*	generateAnyEntity(Map* map, int posX, int posY)
  {
    return new T(map, posX, posY);
  }

  typedef	AEntity* (EntitiesFactory::*generateAEntity)(Map*, int, int);

  std::map<FactoryType, generateAEntity>	m_generateAEntity;
  std::map<AEntity::Type, FactoryType>		m_convert;
  std::vector<FactoryType>			m_bonus;
  static EntitiesFactory*	m_instance;
};

#endif
