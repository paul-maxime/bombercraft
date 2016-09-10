#include "TextureManager.hpp"
#include "GeometricManager.hpp"
#include "SolidWall.hpp"

SolidWall::SolidWall(Map *map, int posX, int posY) : AEntity(map, posX, posY, 1, AEntity::SOLID_WALL)
{
  _isDestructible = false;
  translate(glm::vec3(posX, 0, posY));
}

SolidWall::~SolidWall()
{
}

void	SolidWall::update(gdl::Clock const &)
{
}

void	SolidWall::draw(gdl::AShader &shader, gdl::Clock const &)
{
  _textureManager->bind(TextureManager::BEDROCK);
  GeometricManager::getInstance()->draw(GeometricManager::CUBE, shader, getTransformation());
}
