#include <algorithm>
#include <iostream>
#include <vector>

#include "InputsManager.hpp"
#include "MatrixManager.hpp"
#include "ScoreManager.hpp"
#include "AudioManager.hpp"

#include "ScoreManager.hpp"
#include "SceneShowScore.hpp"
#include "FormInputScore.hpp"
#include "Utils.hpp"

SceneShowScore::SceneShowScore(GameEngine* game)
  : ASceneMenu(game, 0),
    _gameScores(ScoreManager::getInstance()->getScores()),
    bestPlayerScore(ScoreManager::getInstance()->getBestPlayerScore())
{
  _background.init(TextureManager::BACKGROUND, glm::vec2(game->getWidth(), game->getHeight()));
  this->prepareScores();
}

SceneShowScore::~SceneShowScore()
{
}

void		SceneShowScore::prepareScores()
{
  FormInputScore* button;
  int	count = 0;

  for (std::vector<AFormInput *>::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it)
    delete (*it);
  m_buttons.clear();

  for (std::vector<ScoreManager::gameScore *>::const_iterator gameScore = _gameScores.begin();
       gameScore != _gameScores.end();
       ++gameScore)
    {
      for (std::vector<ScoreManager::playerScore *>::const_iterator player = (*gameScore)->playerScores.begin();
	   player != (*gameScore)->playerScores.end() && count < 7;
	   ++player)
	{
	  button = new FormInputScore(m_game, 20, 10 + 80 * count++, 300, 60,
				      (*player)->name + " : " + Utils::toString((*player)->point),
				      *player);
	  button->setFocus(false);
	  m_buttons.push_back(button);
	}
    }
}

void		SceneShowScore::update(gdl::Clock const &clock)
{
  ASceneMenu::update(clock);
  if (m_inputs->keyIsPressed(SDLK_DELETE) ||
      m_inputs->keyIsPressed(PlayersKeysManager::getInstance()->getActionsKeys(PlayersKeysManager::ACTION)))
    this->prepareScores();
}

void		SceneShowScore::drawText(const std::string &value, const int posX, const int posY,
					 gdl::AShader &shader, gdl::Clock const &clock)
{
  Text text(FontsManager::DEFAULT, value);

  text.setTranslation(glm::vec3(posX, posY, 0.0f));
  text.setScale(glm::vec3(1.0f, 1.0f, 1.0f));
  text.draw(shader, clock);
}

void		SceneShowScore::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _background.draw(shader, clock);
  ASceneMenu::draw(shader, clock);
  if (ScoreManager::getInstance()->nbScore() > 7)
    this->drawText("Il y a " + Utils::toString(ScoreManager::getInstance()->nbScore() - 7)
		   + " scores non affiches", 20, 560, shader, clock);
  if (bestPlayerScore)
    this->drawText("Le meilleur score est " + Utils::toString(bestPlayerScore->point) +
		   " par : \n" + bestPlayerScore->name, 350, 40, shader, clock);
  else
    this->drawText("Aucun score disponible", 350, 40, shader, clock);
  this->drawText("Nombre total de partie : " + Utils::toString(ScoreManager::getInstance()->nbGame()),
		 350, 150, shader, clock);
  this->drawText("Nombre total de score : " + Utils::toString(ScoreManager::getInstance()->nbScore()),
		 350, 180, shader, clock);
  this->drawText("Score moyen : " + Utils::toString(ScoreManager::getInstance()->getScoreAvg()),
  		 350, 210, shader, clock);
}
