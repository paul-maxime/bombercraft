/**
 * \file SceneNewGame.hpp
 * Defines the new-game scene
 */

#ifndef SCENE_NEW_GAME_HPP_
#define SCENE_NEW_GAME_HPP_

#include <map>
#include <vector>

#include "ASceneMenu.hpp"
#include "Sprite.hpp"
#include "PlayersKeysManager.hpp"

class AFormInput;

/**
 * \class SceneNewGame
 * This class allow too choose the game mode
 */
class SceneNewGame : public ASceneMenu
{
public:
  SceneNewGame(GameEngine* game);
  ~SceneNewGame();

  void	chooseMap();
  void	customMap();

  virtual void	update(const gdl::Clock& clock);
  virtual void	draw(gdl::AShader& shader, const gdl::Clock& clock);

private:
  SceneNewGame(const SceneNewGame&);
  SceneNewGame&	operator=(const SceneNewGame&);

  const glm::vec2		_buttonSize;
  const int			_padding;
  Sprite			_background;
};

#endif
