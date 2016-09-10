#include <algorithm>
#include <iostream>

#include "InputsManager.hpp"
#include "MatrixManager.hpp"
#include "ScoreManager.hpp"

#include "SceneSaveScore.hpp"
#include "FormInputString.hpp"
#include "FormInputButton.hpp"
#include "Utils.hpp"

SceneSaveScore::SceneSaveScore(GameEngine* game, const std::vector<Player *>& players, bool &saved)
  : ASceneMenu(game, 0),
    _players(players),
    _saved(saved)
{
  FormInputString* stringInput;
  FormInputButton* button;
  int count = 0;

  _background.init(TextureManager::BACKGROUND, glm::vec2(game->getWidth(), game->getHeight()));

  for (std::vector<Player *>::const_iterator it = _players.begin(); it != _players.end(); ++it)
    if (!(*it)->isIA())
      {
	stringInput = new FormInputString(game, 100, 10 + count * 80 , 600, 60,
					  (*it)->getName(), Utils::toString(count) + " [ " +
					  Utils::toString((*it)->getPoints()) + "pts ] : ");
	stringInput->setFocus(false);
	m_buttons.push_back(stringInput);
	m_stringInputs.push_back(stringInput);
	++count;
      }

  button = new FormInputButton(game, 100, 10 + count * 80, 600, 60, "Sauvegarder");
  button->setCallback(this, &SceneSaveScore::onSaveClick);
  button->setFocus(false);
  m_buttons.push_back(button);
}

SceneSaveScore::~SceneSaveScore()
{
}

void SceneSaveScore::onSaveClick()
{
  Player	*player;
  int		count = 0;

  for (std::vector<FormInputString *>::iterator it = m_stringInputs.begin();
       it != m_stringInputs.end();
       ++it)
    {
      while (_players[count]->isIA())
	++count;
      player = _players[count++];
      player->setName((*it)->getString());
    }
  ScoreManager::getInstance()->addScores(_players);
  _saved = true;
  std::cout << "Score bien enregistré" << std::endl;
  this->close();
}

void		SceneSaveScore::update(gdl::Clock const &clock)
{
  ASceneMenu::update(clock);
}

void		SceneSaveScore::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _background.draw(shader, clock);
  ASceneMenu::draw(shader, clock);
  for (std::vector<AFormInput *>::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it)
    (*it)->draw(shader, clock);
}
