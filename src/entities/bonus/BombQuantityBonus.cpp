#include "EntitiesFactory.hpp"
#include "BombQuantityBonus.hpp"
#include "Player.hpp"

BombQuantityBonus::BombQuantityBonus(Map *map, int posX, int posY)
  : ABonus(map, posX, posY, 1, GeometricManager::TNT, TextureManager::TNT)
{
  _isDestructible = false;
}

BombQuantityBonus::~BombQuantityBonus()
{
}

void	BombQuantityBonus::addEffect(Player &player)
{
  player.addBomb(1);
}

void	BombQuantityBonus::serialize(std::ostream& out) const
{
  writeInFile<EntitiesFactory::FactoryType>(EntitiesFactory::BOMB_QUANTITY_BONUS, out);
  ABonus::serialize(out);
}

void	BombQuantityBonus::unserialize(std::istream& in)
{
  EntitiesFactory::FactoryType	type;
  readFromFile<EntitiesFactory::FactoryType>(type, in);
  ABonus::unserialize(in);
}
