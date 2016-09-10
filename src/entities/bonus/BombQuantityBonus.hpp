#ifndef BOMBQUANTITYBONUS_HPP_
#define BOMBQUANTITYBONUS_HPP_

#include "ABonus.hpp"

class BombQuantityBonus : public ABonus
{
public:
  BombQuantityBonus(Map *map, int posX, int posY);
  ~BombQuantityBonus();

  virtual void	addEffect(Player &player);

  virtual void	serialize(std::ostream& out) const;
  virtual void	unserialize(std::istream& in);
private:
  BombQuantityBonus(const BombQuantityBonus&);
  BombQuantityBonus&	operator=(const BombQuantityBonus&);
};


#endif
