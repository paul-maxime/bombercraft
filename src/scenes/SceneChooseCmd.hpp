/**
 * \file SceneChooseCmd.hpp
 */

#ifndef SCENE_CHOOSE_CMD_HPP_
#define SCENE_CHOOSE_CMD_HPP_

#include "ASceneMenu.hpp"
#include "Sprite.hpp"
#include "SceneChooseMap.hpp"
#include "PlayersKeysManager.hpp"

class AFormInput;

/**
 * \class SceneChooseCmd
 * This scene allow to choose the game controller
*/

class SceneChooseCmd : public ASceneMenu
{
public:
  SceneChooseCmd(GameEngine* game, SceneChooseMap::AsciiMapInfo* infos = NULL);
  virtual ~SceneChooseCmd();
  virtual void update(gdl::Clock const &clock);
  virtual void draw(gdl::AShader &shader, gdl::Clock const &clock);

private:
  SceneChooseCmd(const SceneChooseCmd &);
  SceneChooseCmd	&operator=(const SceneChooseCmd &);

  void	onClick();

  typedef void	(SceneChooseCmd::*func)();

  SceneChooseMap::AsciiMapInfo*	_infos;
  Sprite			_background;
};

#endif
