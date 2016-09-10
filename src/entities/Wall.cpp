#include "Map.hpp"
#include "EntitiesFactory.hpp"
#include "TextureManager.hpp"
#include "GeometricManager.hpp"
#include "Wall.hpp"

Wall::Wall(Map *map, int posX, int posY) : AEntity(map, posX, posY, 1, AEntity::WALL)
{
  _percentDropBonus = map->getParams().bonusDensity;
  _lives = 2;
  translate(glm::vec3(posX, 0, posY));
}

Wall::~Wall()
{
}

void	Wall::kill()
{
  AEntity::kill();
  unsigned int	dropBonusRoll = std::rand() % 100;

  if (dropBonusRoll < _percentDropBonus)
    this->_map->addEntityAt(_posX, _posY, EntitiesFactory::getInstance()->generateRandomBonus(this->_map, _posX, _posY));
}

void	Wall::update(gdl::Clock const &)
{
}

void	Wall::draw(gdl::AShader &shader, gdl::Clock const &)
{
  if (_lives == 2)
    _textureManager->bind(TextureManager::STONE);
  else
    _textureManager->bind(TextureManager::COBBLESTONE);
  GeometricManager::getInstance()->draw(GeometricManager::CUBE, shader, getTransformation());
}

void	Wall::serialize(std::ostream& out) const
{
  AEntity::serialize(out);
  writeInFile<unsigned int>(_percentDropBonus, out);
}

void	Wall::unserialize(std::istream& in)
{
  AEntity::unserialize(in);
  readFromFile<unsigned int>(_percentDropBonus, in);
}
