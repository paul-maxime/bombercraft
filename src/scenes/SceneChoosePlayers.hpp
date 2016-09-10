#ifndef SCENE_CHOOSE_PLAYERS_HPP_
#define SCENE_CHOOSE_PLAYERS_HPP_

#include <map>
#include <vector>
#include "AScene.hpp"
#include "Sprite.hpp"
#include "PlayersKeysManager.hpp"
#include "SceneChooseMap.hpp"

class AFormInput;

/**
 * \class SceneChoosePlayers
 * This scene allow to configure a game on a pre-defined map
 */

class SceneChoosePlayers : public AScene
{
public:
  SceneChoosePlayers(GameEngine* game, AScene& parent,
		     const SceneChooseMap::AsciiMapInfo& infos);
  virtual ~SceneChoosePlayers();

  virtual void	update(gdl::Clock const& clock);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const& clock);

private:
  SceneChoosePlayers(const SceneChoosePlayers&);
  SceneChoosePlayers&	operator=(const SceneChoosePlayers&);

  void	onClick();

  void	quit();
  void	downCursor();
  void	upCursor();

private:
  typedef void	(SceneChoosePlayers::*func)();

  std::map<PlayersKeysManager::Actions, func>	_actions;

  const SceneChooseMap::AsciiMapInfo	_infos;

  AScene*			_parent;
  std::vector<AFormInput*>	_inputs;
  unsigned int			_cursor;
  Sprite			_background;
};

#endif
