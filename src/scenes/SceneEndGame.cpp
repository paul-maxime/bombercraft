#include <algorithm>

#include "InputsManager.hpp"
#include "MatrixManager.hpp"
#include "ScoreManager.hpp"

#include "SceneSaveScore.hpp"
#include "SceneEndGame.hpp"
#include "SceneGame.hpp"

#include "FormInputButton.hpp"
#include "FormInputString.hpp"

#include "Map.hpp"

SceneEndGame::SceneEndGame(GameEngine* game, SceneGame* parent)
  : ASceneMenu(game, 1),
    m_parent(parent),
    bestPlayerScore(ScoreManager::getInstance()->getBestPlayerScore()),
    _saved(false)
{
  FormInputButton*	button;
  int			nbIA = 0;

  for (std::vector<Player *>::const_iterator it = m_parent->getMap()->getPlayers().begin();
       it != m_parent->getMap()->getPlayers().end();
       ++it)
    if (!(*it)->isIA())
      ++nbIA;
  _background.init(TextureManager::SCORE_BACKGROUND, glm::vec2(500, nbIA * 50 + 50));
  _background.translate(glm::vec3(165, 35, 0.0f));

  button = new FormInputButton(game, 170, 420, 500, 60, "Sauvegarder les scores");
  button->setCallback(this, &SceneEndGame::onSaveScoreClick);
  button->setFocus(false);
  m_buttons.push_back(button);

  button = new FormInputButton(game, 170, 500, 500, 60, "Retour au menu");
  button->setCallback(this, &SceneEndGame::onMenuReturnClick);
  button->setFocus(true);
  m_buttons.push_back(button);

  // m_gameOver.init(TextureManager::GAME_OVER, glm::vec2(543, 94));
  // m_gameOver.translate(glm::vec3(128, 80, 0.0f));
}

SceneEndGame::~SceneEndGame()
{
}

void SceneEndGame::onMenuReturnClick()
{
  m_parent->close();
  this->close();
}

void SceneEndGame::onSaveScoreClick()
{
  if (!_saved)
    {
      SceneSaveScore *saveScore = new SceneSaveScore(m_game, m_parent->getMap()->getPlayers(), _saved);
      saveScore->open();
    }
}

void SceneEndGame::update(gdl::Clock const &clock)
{
  ASceneMenu::update(clock);
}

void		SceneEndGame::drawText(const std::string &value, const int posX, const int posY,
				       gdl::AShader &shader, gdl::Clock const &clock)
{
  Text text(FontsManager::DEFAULT, value);

  text.setTranslation(glm::vec3(posX, posY, 0.0f));
  text.setScale(glm::vec3(1.0f, 1.0f, 1.0f));
  text.draw(shader, clock);
}

void		SceneEndGame::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  int	count = 0;

  _background.draw(shader, clock);
  ASceneMenu::draw(shader, clock);

  if (bestPlayerScore)
    this->drawText("Le meilleur score est " + Utils::toString(bestPlayerScore->point) +
		   " par " + bestPlayerScore->name + " !", 170, 40, shader, clock);
  for (std::vector<Player *>::const_iterator it = m_parent->getMap()->getPlayers().begin();
       it != m_parent->getMap()->getPlayers().end();
       ++it)
    if (!(*it)->isIA())
      this->drawText((*it)->getName() + " : " + Utils::toString((*it)->getPoints()) + " points",
		     170, 50 + ++count * 50, shader, clock);
}
