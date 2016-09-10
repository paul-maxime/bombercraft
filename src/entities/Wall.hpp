/*
 * \file Wall.hpp
 * Defines the Wall entity.
 */

#ifndef WALL_HPP_
#define WALL_HPP_

#include "AEntity.hpp"

class Wall : public AEntity
{
public:
  Wall(Map *map, int posX, int posY);
  virtual ~Wall();

  virtual void	kill();
  virtual void	update(gdl::Clock const &clock);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);

  virtual void serialize(std::ostream& out) const;
  virtual void unserialize(std::istream& in);

private:
  Wall(const Wall&);
  Wall&	operator=(const Wall&);


private:
  unsigned int	_percentDropBonus;
};

#endif
