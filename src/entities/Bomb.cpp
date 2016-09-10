#include <iostream>
#include <algorithm>
#include <map>
#include <SdlContext.hh>

#include "Map.hpp"
#include "Bomb.hpp"
#include "Explosion.hpp"
#include "MapErrors.hpp"
#include "Player.hpp"

#include "Model3DManager.hpp"
#include "TextureManager.hpp"
#include "GeometricManager.hpp"
#include "InputsManager.hpp"

Bomb::Bomb(Map *map, int posX, int posY, int explodeSize, Player* owner)
  : AEntity(map, posX, posY, 1, AEntity::BOMB), m_step(0.0f),
    m_inputs(InputsManager::getInstance()),
    _explodeSize(explodeSize),
    _owner(owner),
    _linkedWithPlayer(-1),
    _speed(6.0f)
{
  if (owner)
    _linkedWithPlayer = _owner->getPlayerNum();
  _isUpdatable = true;
  translate(glm::vec3(posX, 0, posY));
  _push[AEntity::LEFT] = glm::vec3(0.1, 0, 0);
  _push[AEntity::RIGHT] = glm::vec3(-0.1, 0, 0);
  _push[AEntity::UP] = glm::vec3(0, 0, 0.1);
  _push[AEntity::DOWN] = glm::vec3(0, 0, -0.1);
}

Bomb::~Bomb()
{
}

int	Bomb::getExplodeSize() const
{
  return (this->_explodeSize);
}

void	Bomb::changeDirection(AEntity::Direction direction)
{
  if (std::find(_directions.begin(), _directions.end(), direction) == _directions.end())
    {
      _directions.clear();
      _directions.push_back(direction);
    }
}

void	Bomb::pushedBy(const AEntity* entity)
{
  for (std::map<AEntity::Direction, glm::vec3>::iterator it = _push.begin();
       it != _push.end();
       ++it)
    {
      if (collideWith(entity, it->second))
	{
	  changeDirection(it->first);
	  return ;
	}
    }
}

bool	Bomb::testPlace(const AEntity* entity) const
{
  if (!entity->isAlive())
    return (true);
  return (entity->getType() != AEntity::WALL &&
	  entity->getType() != AEntity::BOX &&
	  entity->getType() != AEntity::SOLID_WALL);
}

bool	Bomb::isObstacle(const AEntity* entity) const
{
  return (entity->getType() == AEntity::WALL ||
	  entity->getType() == AEntity::BOX ||
	  entity->getType() == AEntity::SOLID_WALL);
}

bool	Bomb::explodeOnEntities(const int posX, const int posY)
{
  std::list<AEntity *>			*entities;
  std::list<AEntity *>::const_iterator	it;
  bool					ret = true, canPlace = true;
  Bomb					*bomb;

  entities = this->_map->getEntitysAt(posX, posY);
  for (it = entities->begin(); it != entities->end(); ++it)
    {
      if (_owner && (*it) != _owner && (*it)->getType() == AEntity::PLAYER)
	_owner->addPoints(50);
      if ((*it)->isAlive() && (*it)->getType() != AEntity::EXPLOSION)
	{
	  if ((*it)->getType() == AEntity::BOMB)
	    {
	      if ((bomb = dynamic_cast<Bomb *>((*it))))
		{
		  if (_owner)
		    _owner->addPoints(15);
		  bomb->explode();
		}
	    }
	  else if (isObstacle((*it)))
	    {
	      if (_owner && (*it)->isDestructible())
		_owner->addPoints(10);
	      (*it)->destroy();
	      ret = false;
	    }
	}
      if (!testPlace(*it))
	canPlace = false;
    }
  if (canPlace)
    this->_map->addEntityAt(posX, posY, new Explosion(this->_map, posX, posY));
  return (ret);
}

void	Bomb::explode()
{
  int x = _position.x + _dec + _size / 2, y = _position.z + _dec + _size / 2;
  std::map<directionName, bool>	direction;

  direction[TOP] = true;
  direction[RIGHT] = true;
  direction[LEFT] = true;
  direction[BOTTOM] = true;

  this->kill();
  this->explodeOnEntities(x, y);
  for (int i = 1; i <= this->_explodeSize; ++i)
    {
      if (direction[TOP])
	direction[TOP] = this->explodeOnEntities(x, y - i);
      if (direction[RIGHT])
	direction[RIGHT] = this->explodeOnEntities(x - i, y);
      if (direction[BOTTOM])
	direction[BOTTOM] = this->explodeOnEntities(x, y + i);
      if (direction[LEFT])
	direction[LEFT] = this->explodeOnEntities(x + i, y);
    }
  if (_owner)
    _owner->restoreBomb();
}

void	Bomb::update(gdl::Clock const &clock)
{
  glm::vec3 position(_position);

  move(clock, _speed);
  if (_directions.size() && position == _position)
    _directions.clear();
  m_step += clock.getElapsed() * 1000.0f;
  if (m_step >= 1500.0f)
    this->explode();
}

void	Bomb::draw(gdl::AShader &shader, gdl::Clock const &)
{
  _textureManager->bind(TextureManager::TNT);
  GeometricManager::getInstance()->draw(GeometricManager::TNT, shader, getTransformation());
}

void	Bomb::serialize(std::ostream& out) const
{
  AEntity::serialize(out);

  SeriBomb seri;

  seri.linkedWithPlayer = _linkedWithPlayer;
  seri.step = m_step;
  seri.explodeSize = _explodeSize;
  writeInFile<SeriBomb>(seri, out);
}

void	Bomb::unserialize(std::istream& in)
{
  AEntity::unserialize(in);
  SeriBomb seri;

  readFromFile<SeriBomb>(seri, in);
  _linkedWithPlayer = seri.linkedWithPlayer;
  m_step = seri.step;
  _explodeSize = seri.explodeSize;
}

void	Bomb::restoreOwner(const std::vector<Player*>& players)
{
  if (_linkedWithPlayer >= 0)
    {
      for (std::vector<Player*>::const_iterator it = players.begin(); it != players.end(); ++it)
	{
	  if ((*it)->getPlayerNum() == _linkedWithPlayer)
	    {
	      _owner = (*it);
	      return ;
	    }
	}
    }
}
