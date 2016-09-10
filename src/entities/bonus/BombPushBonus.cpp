#include "EntitiesFactory.hpp"
#include "BombPushBonus.hpp"
#include "Player.hpp"

BombPushBonus::BombPushBonus(Map *map, int posX, int posY)
  : ABonus(map, posX, posY, 1, GeometricManager::TNT, TextureManager::PISTON)
{
  _isDestructible = false;
}

BombPushBonus::~BombPushBonus()
{
}

void	BombPushBonus::addEffect(Player& player)
{
  player.setCanPushBomb(true);
}

void	BombPushBonus::serialize(std::ostream& out) const
{
  writeInFile<EntitiesFactory::FactoryType>(EntitiesFactory::BOMB_PUSH_BONUS, out);
  ABonus::serialize(out);
}

void	BombPushBonus::unserialize(std::istream& in)
{
  EntitiesFactory::FactoryType	type;
  readFromFile<EntitiesFactory::FactoryType>(type, in);
  ABonus::unserialize(in);
}
