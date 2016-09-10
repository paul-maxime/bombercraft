/**
 * \file SolidWall.hpp
 * Defines the solid wall entity.
 */

#ifndef	SOLID_WALL_HPP_
#define	SOLID_WALL_HPP_

#include "AEntity.hpp"
#include "Cube.hpp"

class SolidWall : public AEntity
{
public:
  SolidWall(Map *map, int posX, int posY);
  virtual ~SolidWall();


  virtual void	update(gdl::Clock const &clock);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);

private:
  SolidWall(const SolidWall &);
  SolidWall &operator=(const SolidWall &);
};

#endif
