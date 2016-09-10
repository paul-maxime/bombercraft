/**
 * \file SceneCredit.hpp
 * Defines the menu scene.
 */

#ifndef SCENE_CREDIT_HPP_
#define SCENE_CREDIT_HPP_

#include "AScene.hpp"
#include "Sprite.hpp"

class Credit;

/**
 * \class SceneCredit
 * This scene show the credits
 */

class SceneCredit : public AScene
{
private:
  Sprite	_background;
  Sprite	_created_by;
  Sprite	_duval_h;
  Sprite	_caudou_j;
  Sprite	_drain_a;
  Sprite	_leduc_p;
  Sprite	_morphe_h;

public:
  SceneCredit(GameEngine* game);
  virtual ~SceneCredit();
  virtual void update(gdl::Clock const &clock);
  virtual void draw(gdl::AShader &shader, gdl::Clock const &clock);
};

#endif
