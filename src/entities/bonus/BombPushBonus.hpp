#ifndef BOMB_PUSH_BONUS_HPP_
#define BOMB_PUSH_BONUS_HPP_

#include "ABonus.hpp"

class Player;

class BombPushBonus : public ABonus
{
public:
  BombPushBonus(Map* map, int posX, int posY);
  ~BombPushBonus();

  virtual void	addEffect(Player& player);

  virtual void	serialize(std::ostream& out) const;
  virtual void	unserialize(std::istream& in);

private:
  BombPushBonus(const BombPushBonus&);
  BombPushBonus&	operator=(const BombPushBonus&);
};

#endif
