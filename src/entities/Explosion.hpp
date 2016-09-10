/*
 * \file Explosion.hpp
 * Defines the Explosion entity.
 */

#ifndef EXPLOSION_HPP_
#define EXPLOSION_HPP_

#include "AEntity.hpp"

class Explosion : public AEntity
{
private:
  float			m_step;

public:
  Explosion(Map *map, int posX, int posY);
  virtual ~Explosion();

  virtual void update(gdl::Clock const &clock);
  virtual void draw(gdl::AShader &shader, gdl::Clock const &clock);

  virtual void serialize(std::ostream& out) const;
  virtual void unserialize(std::istream& in);

private:
  Explosion(const Explosion&);
  Explosion&	operator=(const Explosion&);

  void	damage() const;
};

#endif
