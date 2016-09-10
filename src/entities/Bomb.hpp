/**
 * \file Bomb.hpp
 * Defines the bomb entity.
 */

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "AEntity.hpp"
#include "Player.hpp"

class InputsManager;
class Player;

/**
 * \class Bomb
 * The bomb entity
 * Inherits from AEntity
 */
class Bomb : public AEntity
{
private:
  class SeriBomb
  {
  public:
    int linkedWithPlayer;
    float step;
    int explodeSize;
  };
  enum directionName
    {
      TOP,
      LEFT,
      RIGHT,
      BOTTOM
    };
  float			m_step;
  InputsManager*	m_inputs;
  int			_explodeSize;

public:
  /**
   * The bomb constructor
   * \param map The map where the entity is contained
   * \param posX The initial x coordinate
   * \param posY The initial y coordinate
   * \param explodeSize The size of the explosion
   * \param owner The player that posed the bomb
   */
  Bomb(Map *map, int posX, int posY, int explodeSize = 0, Player* owner = 0);

  /**
   * The virtual destructor of the bomb
   */
  virtual ~Bomb();

  /**
   * Update the entity
   * \param clock The game's clock
   */
  virtual void	update(gdl::Clock const &clock);

  /**
   * Draw the entity on the screen
   * \param shader The shader used to draw
   * \param clock The game's clock
   */
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);

  /**
   * Push the bomb depending of the entity's movement
   * \param The entity that pushed the bomb
   */
  void		pushedBy(const AEntity* entity);

  /**
   * Explode the bomb, creating explosions
   */
  void		explode();

  /**
   * \return The explosion size
   */
  int		getExplodeSize() const;

  /**
   * Serialize the entity
   * \param out The stream to output the result
   */
  virtual void	serialize(std::ostream& out) const;

  /**
   * Unserialize the entity
   * \param in The stream to read
   */
  virtual void	unserialize(std::istream& in);

  /**
   * Restore the owner of the bomb after an unserialisation
   * \param players
   */
  void		restoreOwner(const std::vector<Player*>& players);

private:
  void		changeDirection(AEntity::Direction);

  bool		testPlace(const AEntity* entity) const;
  bool		isObstacle(const AEntity* entity) const;
  bool		explodeOnEntities(const int posX, const int posY);

private:
  Bomb(const Bomb&);
  Bomb&	operator=(const Bomb&);

  std::map<AEntity::Direction, glm::vec3> _push;

  Player*	_owner;
  int		_linkedWithPlayer;
  float		_speed;
};

#endif
