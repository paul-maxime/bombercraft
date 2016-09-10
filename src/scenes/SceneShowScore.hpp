/**
 * \file SceneShowScore.hpp
 * Defines the show score scene.
 */

#ifndef SCENE_SHOW_SCORE_HPP_
#define SCENE_SHOW_SCORE_HPP_

#include <vector>

#include "AScene.hpp"
#include "Sprite.hpp"
#include "ScoreManager.hpp"
#include "ASceneMenu.hpp"

class AFormCallback;
class AFormInput;

/**
 * \¢lass SceneShowScore
 * This scene show the saved score
 */
class SceneShowScore : public ASceneMenu
{
public:
  SceneShowScore(GameEngine* game);
  virtual ~SceneShowScore();

  virtual void		update(gdl::Clock const &clock);
  virtual void		draw(gdl::AShader &shader, gdl::Clock const &clock);

private:
  SceneShowScore(const SceneShowScore &);
  SceneShowScore		&operator=(const SceneShowScore &);

  void				prepareScores();
  void				drawText(const std::string &value, const int posX, const int posY,
					 gdl::AShader &shader, gdl::Clock const &clock);

private:
  const std::vector<ScoreManager::gameScore *>			_gameScores;
  Sprite							_background;
  const ScoreManager::playerScore				*bestPlayerScore;
};

#endif
