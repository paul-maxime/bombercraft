/**
 * \file ABonus.hpp
 * Contains the bonus abstract entity.
 */

#ifndef ABONUS_HPP_
#define ABONUS_HPP_

#include <iostream>

#include "AEntity.hpp"
#include "GeometricManager.hpp"
#include "TextureManager.hpp"

class Player;

class ABonus : public AEntity
{
private:
  class SeriBonus
  {
  public:
    float			height;
    int				speed;
    double			totalTime;
  };

public:
  ABonus(Map *map, int posX, int posY, float size,
	 GeometricManager::Name geometric,
	 TextureManager::TextureName texture);
  virtual ~ABonus();

  virtual void	update(gdl::Clock const &clock);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual void	addEffect(Player &player) = 0;

  virtual void	serialize(std::ostream& out) const;
  virtual void	unserialize(std::istream& in);

private:
  GeometricManager::Name	m_geometric;
  TextureManager::TextureName	m_texture;
  float				m_height;
  int				m_speed;
  double			m_totalTime;
  glm::vec3			m_scale;
};

#endif
