#include <iostream>
#include <string>

#include "InputsManager.hpp"
#include "TextureManager.hpp"

#include "Text.hpp"
#include "GameEngine.hpp"
#include "FormInputScore.hpp"

FormInputScore::FormInputScore(GameEngine *game,
			       const int posX, const int posY,
			       const int sizeX, const int sizeY,
			       const std::string &value,
			       const ScoreManager::playerScore *playerScore)
  : FormInputButton(game, posX, posY, sizeX, sizeY, value),
    _playerScore(playerScore)
{
}

FormInputScore::~FormInputScore()
{
}

void FormInputScore::update(gdl::Clock const &)
{
  if (_focused && m_inputs->keyIsPressed(SDLK_RETURN))
    if (_callback)
      (*_callback)();
  if (_focused && (m_inputs->keyIsPressed(SDLK_DELETE) ||
		   m_inputs->keyIsPressed(PlayersKeysManager::getInstance()->getActionsKeys(PlayersKeysManager::ACTION))))
    ScoreManager::getInstance()->delPlayerScore(_playerScore);
}

void FormInputScore::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _sprite.draw(shader, clock);
  _text.draw(shader, clock);
}
