#include <cmath>
#include <algorithm>
#include <SdlContext.hh>

#include "TextureManager.hpp"
#include "Model3DManager.hpp"

#include "CharToEntityConverter.hpp"
#include "EntitiesFactory.hpp"
#include "AEntity.hpp"
#include "Bomb.hpp"
#include "Map.hpp"

AEntity::AEntity(Map *map, int posX, int posY, float size, AEntity::Type type)
  : _type(type),
    _size(size - 0.01),
    _dec((1 - size) / 2),
    _alive(true),
    _lives(1),
    _map(map),
    _posX(posX),
    _posY(posY),
    _isDestructible(true),
    _isCollidable(true),
    _isUpdatable(false),
    _textureManager(TextureManager::getInstance()),
    _modelManager(Model3DManager::getInstance())
{
  _actions[LEFT] = &AEntity::dirLeft;
  _actions[RIGHT] = &AEntity::dirRight;
  _actions[UP] = &AEntity::dirUp;
  _actions[DOWN] = &AEntity::dirDown;
}

AEntity::~AEntity()
{
}

float	AEntity::getSize() const
{
  return (_size);
}

int	AEntity::getPosX() const
{
  return (_posX);
}

int	AEntity::getPosY() const
{
  return (_posY);
}

int	AEntity::getLives() const
{
  return (_lives);
}

AEntity::Type	AEntity::getType() const
{
  return (_type);
}

glm::vec2	AEntity::getRealPosition() const
{
  return glm::vec2(_position.x + _dec + _size / 2,
		   _position.z + _dec + _size / 2);
}

void		AEntity::addDirection(Direction direction)
{
  _directions.push_back(direction);
}

bool	AEntity::collideWith(const AEntity* entity, const glm::vec3& direction) const
{
  return(!(_position.x + direction.x + _dec > entity->_position.x + entity->_dec + entity->_size ||
	   _position.x + direction.x + _dec + _size < entity->_position.x + entity->_dec ||
	   _position.z + direction.z + _dec > entity->_position.z + entity->_dec + entity->_size ||
	   _position.z + direction.z + _dec + _size < entity->_position.z + entity->_dec));
}

bool	AEntity::collideWith(const AEntity* entity) const
{
  glm::vec3 dir(0, 0, 0);

  return (collideWith(entity, dir));
}

void	AEntity::testCollision(glm::vec3& direction)
{
  std::list<AEntity*> tab;
  glm::vec3 dirX = direction, dirY = direction;
  bool canX = true, canY = true, conflict = false, collide;

  dirX.z = 0;
  dirY.x = 0;
  _map->getProxyEntities(tab, _posX, _posY, true);
  for (std::list<AEntity*>::iterator it = tab.begin(); it != tab.end(); ++it)
    {
      collide = false;
      if ((*it) != this &&
	  !((*it)->getType() == AEntity::BOMB &&
	    collideWith((*it))))
	{
	  if (collideWith((*it), dirY))
	    {
	      collide = true;
	      canY = false;
	      if (collideWith((*it), dirX))
		canX = false;
	    }
	  else if (collideWith((*it), dirX))
	    {
	      collide = true;
	      canX = false;
	    }
	  else if (collideWith((*it), direction))
	    {
	      collide = true;
	      conflict = true;
	    }
	  if (std::find(_collisions.begin(), _collisions.end(), (*it)) == _collisions.end() && collide)
	    _collisions.push_back((*it));
	}
    }
  if (conflict && canX && canY)
    canX = false;
  if (!canX)
    direction.x = 0;
  if (!canY)
    direction.z = 0;
}

void	AEntity::normalize(glm::vec3& direction) const
{
  if (direction.x && direction.z)
    {
      direction.x = std::sqrt(std::pow(direction.x, 2) / 2) * (direction.x < 0 ? -1 : 1);
      direction.z = std::sqrt(std::pow(direction.z, 2) / 2) * (direction.z < 0 ? -1 : 1);
    }
}

void		AEntity::splitMove(glm::vec3& direction)
{
  float		step = 0.15;

  while (direction.x != 0 || direction.z != 0)
    {
      glm::vec3	cpy(direction);

      if (cpy.x >= step || cpy.x <= -step)
	{
	  cpy.x = step * (cpy.x > 0 ? 1 : -1);
	  direction.x -= cpy.x;
	}
      else
	direction.x = 0;
      if (cpy.z >= step || cpy.z <= -step)
	{
	  cpy.z = step * (cpy.z > 0 ? 1 : -1);
	  direction.z -= cpy.z;
	}
      else
	direction.z = 0;
      testCollision(cpy);
      translate(cpy);
      _map->moveEntityFromTo(this, _posX, _posY, _position.x, _position.z);
      _posX = _position.x;
      _posY = _position.z;
    }
}

void	AEntity::dirLeft(glm::vec3 &direction, int &angle)
{
  direction.x -= 1;
  angle += 270;
}

void	AEntity::dirRight(glm::vec3 &direction, int &angle)
{
  direction.x += 1;
  angle += (angle < 360 ? 90 : -270);
}

void	AEntity::dirUp(glm::vec3 &direction, int &angle)
{
  direction.z -= 1;
  angle += 180;
}

void	AEntity::dirDown(glm::vec3 &direction, int &angle)
{
  direction.z += 1;
  angle += (angle == 90 ? 0 : 360);
}

void	AEntity::move(gdl::Clock const& clock, float speed)
{
  if (_collisions.size())
    _collisions.clear();
  if (_directions.size() == 0)
    return ;

  int angle = 0;
  float mult = static_cast<float>(clock.getElapsed()) * speed;
  glm::vec3 direction(0, 0, 0);
  for (std::vector<Direction>::iterator it = _directions.begin(); it != _directions.end(); ++it)
    {
      std::map<Direction, fctPtr>::iterator itAction = _actions.find(*it);
      if (itAction != _actions.end())
	(this->*itAction->second)(direction, angle);
    }
  normalize(direction);
  splitMove((direction *= mult));
  glm::vec3 rot(0, 1, 0);
  rot *= (angle / _directions.size());
  if (rot.y != _rotation.y)
    setRotation(rot);
}

char	AEntity::inChar() const
{
  CharToEntityConverter	converter;
  return (converter.convert(_type));
}

bool	AEntity::isAlive() const
{
  return (_alive);
}

void	AEntity::kill()
{
  this->_alive = false;
  this->_map->addEntityToTrash(this);
}

bool	AEntity::isDestructible() const
{
  return (this->_isDestructible);
}

bool	AEntity::isCollidable() const
{
  return (this->_isCollidable);
}

bool	AEntity::isUpdatable() const
{
  return (this->_isUpdatable);
}

void	AEntity::destroy()
{
  if (this->_isDestructible && _lives > 0)
    if (--_lives == 0)
      this->kill();
}

void		AEntity::serialize(std::ostream& out) const
{
  SeriEntities	seri;

  writeInFile<EntitiesFactory::FactoryType>(EntitiesFactory::getInstance()->convert(_type), out);
  seri.alive = _alive;
  seri.lives = _lives;
  seri.posX = _posX;
  seri.posY = _posY;
  seri.nbDirections = _directions.size();
  writeInFile<SeriEntities>(seri, out);
  for (std::vector<Direction>::const_iterator it = _directions.begin(); it != _directions.end(); ++it)
    writeInFile<Direction>((*it), out);
  AObject::serialize(out);
}

void		AEntity::unserialize(std::istream& in)
{
  SeriEntities	seri;

  readFromFile<SeriEntities>(seri, in);
  _alive = seri.alive;
  _lives = seri.lives;
  _posX = seri.posX;
  _posY = seri.posY;
  Direction dir;
  for (unsigned int i = 0; i < seri.nbDirections; ++i)
    {
      readFromFile<Direction>(dir, in);
      _directions.push_back(dir);
    }
  AObject::unserialize(in);
}
