/**
 * \file Player.hpp
 * Defines the Player entity.
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "PlayersKeysManager.hpp"
#include "Model3DManager.hpp"
#include "AEntity.hpp"

namespace gdl
{
  class Model;
}

class InputsManager;
class MatrixManager;

class Player : public AEntity
{
private:
  class SeriPlayer
  {
  public:
    int					playerNum;
    int					idPlayerKeys;
    float				speed;
    float				immunity;
    Model3DManager::AnimationName	animation;
    float				animationTime;
    int					explosionRange;
    int					nbBomb;
    int					maxBomb;
    bool				canPushBomb;
    int					points;
    int					startPosX;
    int					startPosY;
  };

public:
  Player(Map *map, int posX, int posY, int idPlayerKeys = -1);
  virtual ~Player();

  virtual void	destroy();

  void		setViewPoint(gdl::AShader &shader, int& x, int& y) const;

  int		getPlayerNum() const;
  bool		isIA() const;

  /*
  ** getters
  */
  int			getBombs() const;
  int			getPoints() const;
  const std::string	&getName() const;

  /*
  ** setters
  */
  void		setName(const std::string &newName);

  void		placeBomb();
  void		restoreBomb();

  void		changeAnimation(gdl::Clock const &clock);

  void		pushBombs();

  /*
  ** that function takes all bonus at the current current player position.
  */
  void		takeBonus();

  /*
  ** speed and explosionRange modifier : actually used by the bonus
  */
  void		addToSpeed(float speed);
  void		addToExplosionSize(int toAdd);
  void		addBomb(int toAdd);
  void		addPoints(int toadd);
  void		setCanPushBomb(bool canPush);

  float		distanceTo(const Player& player) const;

  virtual void	applyInputs();

  virtual void	update(gdl::Clock const &clock);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);

  virtual void	serialize(std::ostream& out) const;
  virtual void	unserialize(std::istream& in);

private:
  Player(const Player&);
  Player&	operator=(const Player&);

  bool					_drawOnce;
  InputsManager*			_inputs;
  PlayersKeysManager::PlayerKeys*	_keysCode;
  int					_idPlayerKeys;
  float					_speed;
  gdl::Model*				_model;
  MatrixManager*			_camera;
  Model3DManager::AnimationName		_animation;
  float					_animationTime;
  glm::vec4				_color;
  int					_explosionRange;
  int					_nbBomb;
  int					_maxBomb;
  bool					_canPushBomb;
  int					_playerNum;
  float					_immunity;
  glm::vec2				_viewLocation;
  int					_points;
  std::string				_name;

  /*
  ** initiale position for respawn
  */
  int					_startPosX;
  int					_startPosY;
};

#endif
