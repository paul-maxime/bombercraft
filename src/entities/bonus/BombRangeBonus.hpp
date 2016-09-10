#ifndef BOMBRANGEBONUS_HPP_
#define BOMBRANGEBONUS_HPP_

#include "ABonus.hpp"

class BombRangeBonus : public ABonus
{
public:
  BombRangeBonus(Map *map, int posX, int posY);
  ~BombRangeBonus();

  virtual void	addEffect(Player &player);

  virtual void	serialize(std::ostream& out) const;
  virtual void	unserialize(std::istream& in);

private:
  BombRangeBonus(const BombRangeBonus&);
  BombRangeBonus&	operator=(const BombRangeBonus&);
};

#endif
