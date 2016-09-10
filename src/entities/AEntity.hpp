/*
 * \file AEntity.hpp
 * Defines the abstract Entity class.
 */

#ifndef AENTITY_HPP_
#define AENTITY_HPP_

#include <vector>
#include <map>
#include "AObject.hpp"

class Model3DManager;
class TextureManager;
class Map;

/**
 * \class AEntity
 * The abstract class whome inherit all entities
 * Inherits from AObject
 */
class AEntity : public AObject
{
public:
  enum	Type
    {
      BOMB,
      BONUS,
      BOX,
      EXPLOSION,
      FLOOR,
      PLAYER,
      SOLID_WALL,
      WALL
    };

  enum	Direction
    {
      LEFT,
      RIGHT,
      UP,
      DOWN
    };

private:
  class SeriEntities
  {
  public:
    bool alive;
    int lives;
    int posX;
    int posY;
    unsigned int nbDirections;
  };

public:
  /**
   * The entity constructor
   * \param map The map where the entity is contained
   * \param posX The initial x coordinate
   * \param posY The initial y coordinate
   * \param size The size of the entity
   * \param Type The entity Type
   */
  AEntity(Map *map, int posX, int posY, float size, Type type);

  /**
   * The virtual destructor
   */
  virtual ~AEntity();

  /**
   * Update the entity (abstract)
   * \param clock The game's clock
   */
  virtual void	update(gdl::Clock const &clock) = 0;

  /**
   * Draw the entity on the screen (abstract)
   * \param shader The shader used to draw
   * \param clock The game's clock
   */
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock) = 0;

  /**
   * \return The char representation of the entity
   */
  char		inChar() const;

  /**
   * \return True if the entity is alive
   */
  bool		isAlive() const;

  /**
   * Called when the entity take damage
   */
  virtual void	destroy();

  /**
   * Remove an entity from the map
   */
  virtual void	kill();

  /**
   * \return True if the entity is destructible
   */
  bool		isDestructible() const;

  /**
   * \return True if the entity is updatable
   */
  bool		isUpdatable() const;

  /**
   * \return True if the entity is collidable
   */
  bool		isCollidable() const;

  /**
   * \return The entity's size
   */
  float		getSize() const;

  /**
   * \return The entity x coordinate on the map
   */
  int		getPosX() const;

  /**
   * \return The entity y coordinate on the map
   */
  int		getPosY() const;

  /**
   * \return The number of lifes left of the entity
   */
  int		getLives() const;

  /**
   * \return The type of the entity
   */
  Type		getType() const;

  /**
   * \return The real position of the entity (outside of the map)
   */
  glm::vec2	getRealPosition() const;

  /**
   * Add a move direction to the entity
   * \param direction The new direction
   */
  void		addDirection(Direction direction);

  /**
   * Remove a move direction of the entity
   * \param direction The direction to remove
   */
  void		removeDirection(Direction direction);

  /**
   * Tell if the entity will collide with the specified entity with the specified direction
   * \param entity The entity to test the collision with
   * \param direction The direction the current entity will use
   * \return True if the entities will collide
   */
  bool		collideWith(const AEntity* entity, const glm::vec3& direction) const;

  /**
   * Tell if the entity is in collision with the specified entity
   * \param entity The entity to test the collision with
   * \return True if the entities collide
   */
  bool		collideWith(const AEntity* entity) const;

  /**
   * Test all the possible collisions with the nearby entity with the given direction
   * Adjust the direction to avoid collision
   * \param direction The direction where the entity is heading
   */
  void		testCollision(glm::vec3& direction);

  /**
   * Normalize the given direction so diagonal movements don't look wierd
   * \param direction The direction to normalize
   */
  void		normalize(glm::vec3& direction) const;

  /**
   * Test a movement bit by bit in order to avoid error and adjust it to avoid collision
   * \param direction The movement to test
   */
  void		splitMove(glm::vec3& direction);

  /**
   * Move the entity on the map and the screen
   * \param clock The game's clock
   * \param speed The entity's speed
   */
  void		move(gdl::Clock const& clock, float speed);

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

private:
  AEntity(const AEntity&);
  AEntity&	operator=(const AEntity&);

  const Type			_type;

  void dirLeft(glm::vec3 &direction, int &angle);
  void dirRight(glm::vec3 &direction, int &angle);
  void dirUp(glm::vec3 &direction, int &angle);
  void dirDown(glm::vec3 &direction, int &angle);

  typedef void (AEntity::*fctPtr)(glm::vec3 &direction, int &angle);

  std::map<Direction, fctPtr>	_actions;

protected:
  const float			_size;
  const float			_dec;

  bool				_alive;
  int				_lives;
  Map				*_map;
  int				_posX;
  int				_posY;
  bool				_isDestructible;
  bool				_isCollidable;
  bool				_isUpdatable;
  TextureManager		*_textureManager;
  Model3DManager		*_modelManager;
  std::vector<Direction>	_directions;
  std::vector<AEntity*>		_collisions;
};

#endif /* !AENTITY_HPP_ */
