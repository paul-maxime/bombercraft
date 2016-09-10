/**
 * \file SceneSaveScore.hpp
 * Defines the save score scene.
 */

#ifndef SCENE_SAVE_SCORE_HPP_
#define SCENE_SAVE_SCORE_HPP_

#include <vector>

#include "Player.hpp"
#include "ASceneMenu.hpp"
#include "Sprite.hpp"
#include "FormInputString.hpp"
#include "PlayersKeysManager.hpp"

class AFormCallback;
class AFormInput;

/**
 * \class SceneSaveScore
 * This scene allow to save score after a game
 */
class SceneSaveScore : public ASceneMenu
{
public:
  SceneSaveScore(GameEngine* game, const std::vector<Player *>& players, bool &saved);
  virtual ~SceneSaveScore();

  virtual void		update(gdl::Clock const &clock);
  virtual void		draw(gdl::AShader &shader, gdl::Clock const &clock);

private:
  SceneSaveScore(const SceneSaveScore &);
  SceneSaveScore		&operator=(const SceneSaveScore &);

  void				onSaveClick();

private:
  std::vector<FormInputString *>				m_stringInputs;
  const std::vector<Player *>&					_players;
  Sprite							_background;
  bool&								_saved;
};


#endif
