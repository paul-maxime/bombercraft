#include <stdexcept>
#include <Clock.hh>
#include <Model.hh>

#include "TextureManager.hpp"
#include "Model3DManager.hpp"
#include "InputsManager.hpp"
#include "MatrixManager.hpp"
#include "AudioManager.hpp"

#include "CorruptedFileError.hpp"
#include "Map.hpp"
#include "Bomb.hpp"
#include "Player.hpp"
#include "ABonus.hpp"
#include "Utils.hpp"

Player::Player(Map *map, int posX, int posY, int idPlayerKeys)
  : AEntity(map, posX, posY, 0.4, AEntity::PLAYER),
    _drawOnce(false),
    _inputs(InputsManager::getInstance()),
    _keysCode(PlayersKeysManager::getInstance()->getPlayerKeys(idPlayerKeys)),
    _idPlayerKeys(idPlayerKeys),
    _speed(6.0f),
    _model(_modelManager->create(Model3DManager::STEVE)),
    _camera(MatrixManager::getInstance()),
    _animation(Model3DManager::STANDING),
    _animationTime(0),
    _explosionRange(1),
    _nbBomb(1),
    _maxBomb(1),
    _canPushBomb(false),
    _immunity(0),
  _viewLocation(0),
  _points(0),
  _name(std::string("Player ") + Utils::toString(idPlayerKeys))
{
  _startPosX = posX;
  _startPosY = posY;
  _playerNum = _map->getPlayers().size();
  _lives = 3;
  _isUpdatable = true;
  scale(glm::vec3(0.07, 0.07, 0.07));
  translate(glm::vec3(_posX, -0.5, _posY));

  float r = static_cast<float>(std::rand() % 255) / 255.0f;
  float g = static_cast<float>(std::rand() % 255) / 255.0f;
  float b = static_cast<float>(std::rand() % 255) / 255.0f;

  _color = glm::vec4(r, g, b, 1.0f);
}

Player::~Player()
{
}

void	Player::destroy()
{
  if (_immunity <= 0)
    {
      AudioManager::getInstance()->playSound(AudioManager::DAMAGE);
      AEntity::destroy();
      if (_lives > 0)
	{
	  _map->moveEntityFromTo(this, _posX, _posY, _startPosX, _startPosY);
	  setTranslation(glm::vec3(_startPosX, -0.5, _startPosY));
	  _posX = _startPosX;
	  _posY = _startPosY;
	}

      if (_lives > 0)
	_immunity = 600.0f;
    }
}

void	Player::setViewPoint(gdl::AShader &shader, int& x, int& y) const
{
  x = _viewLocation.x;
  y = _viewLocation.y;
  _camera->lookAt(glm::vec3(_viewLocation.x, 11, _viewLocation.y + 6),
		  glm::vec3(_viewLocation.x, 0, _viewLocation.y));
  _camera->apply(MatrixManager::MATRIX_3D, shader);
}

int	Player::getPlayerNum() const
{
  return (_playerNum);
}

bool	Player::isIA() const
{
  return (_idPlayerKeys == -1);
}

int	Player::getBombs() const
{
  return (_nbBomb);
}

int	Player::getPoints() const
{
  return (_points);
}

const std::string	&Player::getName() const
{
  return _name;
}

void		Player::setName(const std::string &newName)
{
  _name = newName;
}

void	Player::restoreBomb()
{
  if (_nbBomb + 1 <= _maxBomb)
    _nbBomb += 1;
}

void	Player::addBomb(int toAdd)
{
  _maxBomb += toAdd;
  _nbBomb += toAdd;
}

void	Player::addPoints(int toAdd)
{
  this->_points += toAdd;
}

void	Player::setCanPushBomb(bool canPush)
{
  _canPushBomb = canPush;
}

float	Player::distanceTo(const Player& player) const
{
  return std::abs(player._position.x - _position.x) +
    std::abs(player._position.z - _position.z);
}

void	Player::placeBomb()
{
  if (_nbBomb > 0)
    {
      glm::vec2 pos = getRealPosition();
      int x = pos.x, y = pos.y;
      std::list<AEntity *>* tab = _map->getEntitysAt(x, y);
      Bomb *bomb;

      for (std::list<AEntity *>::iterator it = tab->begin(); it != tab->end(); ++it)
	{
	  if ((*it)->getType() == BOMB)
	    return ;
	}
      bomb = new Bomb(_map, x, y, _explosionRange, this);
      _map->addEntityAt(x, y, bomb);
      _nbBomb -= 1;
    }
}

void	Player::changeAnimation(gdl::Clock const &clock)
{
  Model3DManager::AnimationName	save = _animation;

  if (_animation == Model3DManager::START_RUN &&
      _modelManager->endAnimation(Model3DManager::STEVE, _animation, _animationTime))
    _animation = Model3DManager::RUNNING;
  else if (_animation == Model3DManager::STOP_RUN &&
	   _modelManager->endAnimation(Model3DManager::STEVE, _animation, _animationTime))
    _animation = Model3DManager::STANDING;
  if (_animation != Model3DManager::START_RUN &&
      _animation != Model3DManager::RUNNING &&
      _directions.size())
    _animation = Model3DManager::START_RUN;
  else if (_animation != Model3DManager::STOP_RUN &&
	   _animation != Model3DManager::STANDING &&
	   !_directions.size())
    _animation = Model3DManager::STOP_RUN;
  if (save != _animation)
    {
      _animationTime = 0;
      _modelManager->setAnimation(_model, Model3DManager::STEVE, _animation);
    }
  _animationTime += clock.getElapsed();
}

/*
** modify the current speed and test the new speed value
*/
void	Player::addToSpeed(float speed)
{
  this->_speed += speed;

  if (this->_speed < 4.0f)
    this->_speed = 4.0f;
  if (this->_speed > 10.0f)
    this->_speed = 10.0f;
}

/*
** modify the current explosion sier and test the new value
*/
void	Player::addToExplosionSize(int toAdd)
{
  this->_explosionRange += toAdd;

  if (this->_explosionRange < 1)
    this->_explosionRange = 1;
}

void	Player::pushBombs()
{
  Bomb*	bomb;

  if (_canPushBomb)
    {
      for (std::vector<AEntity*>::iterator it = _collisions.begin(); it != _collisions.end(); ++it)
	{
	  if ((*it)->getType() == AEntity::BOMB && (bomb = dynamic_cast<Bomb*>(*it)))
	    {
	      bomb->pushedBy(this);
	      AudioManager::getInstance()->playSound(AudioManager::PUSH);
	    }
	}
    }
}

void	Player::takeBonus()
{
  std::list<AEntity *>		entities;
  ABonus			*bonus;

  _map->getProxyEntities(entities, _posX, _posY, false);
  for (std::list<AEntity *>::const_iterator it = entities.begin(); it != entities.end(); ++it)
    {
      if ((*it)->getType() == AEntity::BONUS && collideWith((*it)))
	{
	  if ((bonus = dynamic_cast<ABonus *>(*it)) == NULL)
	    throw std::runtime_error("A bonus is not a bonus, wtf ?");
	  bonus->addEffect(*this);
	  bonus->kill();
	  AudioManager::getInstance()->playSound(AudioManager::BONUS);
	}
    }
}

void	Player::applyInputs()
{
  if (_keysCode == NULL)
    return;
  if (_inputs->keyIsHold(_keysCode->up))
    addDirection(AEntity::UP);
  if (_inputs->keyIsHold(_keysCode->down))
    addDirection(AEntity::DOWN);
  if (_inputs->keyIsHold(_keysCode->left))
    addDirection(AEntity::LEFT);
  if (_inputs->keyIsHold(_keysCode->right))
    addDirection(AEntity::RIGHT);
  if (_inputs->keyIsPressed(_keysCode->action))
    placeBomb();
}

void	Player::update(gdl::Clock const &clock)
{
  if (!isAlive())
    return ;
  if (_immunity > 0)
    {
      _immunity -= clock.getElapsed() * 1000.0f;
      if (_immunity < 0)
	_immunity = 0;
    }
  _directions.clear();
  applyInputs();
  move(clock, _speed);
  pushBombs();
  takeBonus();
  changeAnimation(clock);
  _viewLocation.x += (_position.x - _viewLocation.x) * clock.getElapsed() * 3.0f;
  _viewLocation.y += (_position.z - _viewLocation.y) * clock.getElapsed() * 3.0f;
  _drawOnce = true;
}

void	Player::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  if (!isAlive())
    return ;
  if (!(static_cast<int>(_immunity) % 2))
    {
      shader.setUniform("color", _color);
      if (_drawOnce)
	{
	  _model->draw(shader, getTransformation(), clock.getElapsed() *
		       _modelManager->getAnimationSpeed(Model3DManager::STEVE, _animation));
	  _drawOnce = false;
	}
      else
	_model->draw(shader, getTransformation(), 0);
      shader.setUniform("color", glm::vec4(1));
    }
}

void		Player::serialize(std::ostream& out) const
{
  AEntity::serialize(out);

  SeriPlayer	seri;

  seri.playerNum = _playerNum;
  seri.idPlayerKeys = _idPlayerKeys;
  seri.speed = _speed;
  seri.immunity = _immunity;
  seri.animation = _animation;
  seri.animationTime = _animationTime;
  seri.explosionRange = _explosionRange;
  seri.nbBomb = _nbBomb;
  seri.maxBomb = _maxBomb;
  seri.canPushBomb = _canPushBomb;
  seri.points = _points;
  seri.startPosX = _startPosX;
  seri.startPosY = _startPosY;
  writeInFile<SeriPlayer>(seri, out);
  serializeVec4(_color, out);
}

void		Player::unserialize(std::istream& in)
{
  AEntity::unserialize(in);
  SeriPlayer	seri;

  readFromFile<SeriPlayer>(seri, in);
  _playerNum = seri.playerNum;
  _idPlayerKeys = seri.idPlayerKeys;
  _speed = seri.speed;
  _immunity = seri.immunity;
  _animation = seri.animation;
  _animationTime = seri.animationTime;
  _explosionRange = seri.explosionRange;
  _nbBomb = seri.nbBomb;
  _maxBomb = seri.maxBomb;
  _canPushBomb = seri.canPushBomb;
  _points = seri.points;
  _startPosX = seri.startPosX;
  _startPosY = seri.startPosY;
  if (_idPlayerKeys >= 0 &&
      !(_keysCode = PlayersKeysManager::getInstance()->getPlayerKeys(_idPlayerKeys)))
    throw CorruptedFileError("Invalid player data");
  unserializeVec4(_color, in);
  _name = std::string("Player ") + Utils::toString(_idPlayerKeys);
}
