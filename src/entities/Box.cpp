#include "Map.hpp"
#include "TextureManager.hpp"
#include "GeometricManager.hpp"
#include "Box.hpp"
#include "EntitiesFactory.hpp"

Box::Box(Map *map, int posX, int posY) : AEntity(map, posX, posY, 1, AEntity::BOX)
{
  _percentDropBonus = map->getParams().bonusDensity;
  translate(glm::vec3(posX, 0, posY));
}

Box::~Box()
{
}

void	Box::kill()
{
  AEntity::kill();
  unsigned int	dropBonusRoll = std::rand() % 100;

  if (dropBonusRoll < _percentDropBonus)
    this->_map->addEntityAt(_posX, _posY, EntitiesFactory::getInstance()->generateRandomBonus(this->_map, _posX, _posY));
}

void	Box::update(gdl::Clock const &)
{
}

void	Box::draw(gdl::AShader &shader, gdl::Clock const &)
{
  _textureManager->bind(TextureManager::DIRT);
  GeometricManager::getInstance()->draw(GeometricManager::CUBE, shader, getTransformation());
}

void	Box::serialize(std::ostream& out) const
{
  AEntity::serialize(out);
  writeInFile<unsigned int>(_percentDropBonus, out);
}

void	Box::unserialize(std::istream& in)
{
  AEntity::unserialize(in);
  readFromFile<unsigned int>(_percentDropBonus, in);
}
