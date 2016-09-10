/*
 * \file PlayerSpeedBonus.hpp
 * Defines the Speed bonus.
 */

#ifndef BONUS_SPEED_HPP_
#define BONUS_SPEED_HPP_

#include "ABonus.hpp"

class	PlayerSpeedBonus : public ABonus
{
public:
  PlayerSpeedBonus(Map *map, int posX, int posY);
  ~PlayerSpeedBonus();

  virtual void	addEffect(Player &player);

  virtual void	serialize(std::ostream& out) const;
  virtual void	unserialize(std::istream& in);

private:
  PlayerSpeedBonus(const PlayerSpeedBonus&);
  PlayerSpeedBonus&	operator=(const PlayerSpeedBonus&);
};

#endif
