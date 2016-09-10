#include "EntitiesFactory.hpp"
#include "PlayerSpeedBonus.hpp"
#include "Player.hpp"

PlayerSpeedBonus::PlayerSpeedBonus(Map *map, int posX, int posY)
  : ABonus(map, posX, posY, 1, GeometricManager::CUBE, TextureManager::BEACON)
{
  _isDestructible = false;
}

PlayerSpeedBonus::~PlayerSpeedBonus()
{
}

void	PlayerSpeedBonus::addEffect(Player &player)
{
  player.addToSpeed(1.0f);
}

void	PlayerSpeedBonus::serialize(std::ostream& out) const
{
  writeInFile<EntitiesFactory::FactoryType>(EntitiesFactory::PLAYER_SPEED_BONUS, out);
  ABonus::serialize(out);
}

void	PlayerSpeedBonus::unserialize(std::istream& in)
{
  EntitiesFactory::FactoryType	type;
  readFromFile<EntitiesFactory::FactoryType>(type, in);
  ABonus::unserialize(in);
}
