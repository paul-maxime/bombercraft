/**
 * \file Box.hpp
 * Defines the box entity.
 */

#ifndef BOX_HPP_
#define BOX_HPP_

#include "AEntity.hpp"

/**
 * \class Box
 * A destructible block containing a bonus
 * Inherits from AEntity
 */
class Box : public AEntity
{
public:
  /**
   * The box constructor
   * \param map The map where the entity is contained
   * \param posX The initial x coordinate
   * \param posY The initial y coordinate
   */
  Box(Map *map, int posX, int posY);

  /**
   * The virtual destructor of the bomb
   */
  virtual ~Box();

  /**
   * Overload of the AEntity kill function
   */
  virtual void	kill();

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
   * Serialize the entity
   * \param out The stream to output the result
   */
  virtual void serialize(std::ostream& out) const;

  /**
   * Unserialize the entity
   * \param in The stream to read
   */
  virtual void unserialize(std::istream& in);

private:
  Box(const Box&);
  Box&	operator=(const Box&);

private:
  unsigned int	_percentDropBonus;
};

#endif
