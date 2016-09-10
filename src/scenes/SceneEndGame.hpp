#ifndef SCENEENDGAME_H_
# define SCENEENDGAME_H_

#include "AScene.hpp"
#include "FormInputButton.hpp"
#include "ScoreManager.hpp"
#include "PlayersKeysManager.hpp"
#include "ASceneMenu.hpp"

class AFormInput;
class SceneGame;

/**
 * \class SceneEndGame
 * This scene show the end of a game
 */

class SceneEndGame : public ASceneMenu
{
public:
  SceneEndGame(GameEngine* game, SceneGame* parent);
  virtual ~SceneEndGame();

  virtual void		update(gdl::Clock const &clock);
  virtual void		draw(gdl::AShader &shader, gdl::Clock const &clock);

private:
  void				onMenuReturnClick();
  void				onSaveScoreClick();

  Sprite			m_gameOver;
  SceneGame			*m_parent;

  void		drawText(const std::string &value, const int posX, const int posY,
			 gdl::AShader &shader, gdl::Clock const &clock);

  const ScoreManager::playerScore				*bestPlayerScore;
  bool								_saved;
  Sprite							_background;
};

#endif /* !SCENEENDGAME_H_ */
