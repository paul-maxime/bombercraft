#include "EntitiesFactory.hpp"
#include "BombRangeBonus.hpp"
#include "Player.hpp"

BombRangeBonus::BombRangeBonus(Map *map, int posX, int posY)
  : ABonus(map, posX, posY, 1, GeometricManager::CUBE, TextureManager::REDSTONE_BLOCK)
{
  _isDestructible = false;
}

BombRangeBonus::~BombRangeBonus()
{
}

void	BombRangeBonus::addEffect(Player &player)
{
  player.addToExplosionSize(1);
}

void	BombRangeBonus::serialize(std::ostream& out) const
{
  writeInFile<EntitiesFactory::FactoryType>(EntitiesFactory::BOMB_RANGE_BONUS, out);
  ABonus::serialize(out);
}

void	BombRangeBonus::unserialize(std::istream& in)
{
  EntitiesFactory::FactoryType	type;
  readFromFile<EntitiesFactory::FactoryType>(type, in);
  ABonus::unserialize(in);
}
