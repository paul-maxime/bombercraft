#include <iostream>
#include <string>

#include "InputsManager.hpp"
#include "TextureManager.hpp"

#include "Text.hpp"
#include "GameEngine.hpp"
#include "FormInputButton.hpp"

FormInputButton::FormInputButton(GameEngine *game,
				 const int posX, const int posY,
				 const int sizeX, const int sizeY,
				 const std::string &value)
  : AFormInput(game, posX, posY, sizeX, sizeY,
	       TextureManager::MENU_INPUT,
	       TextureManager::MENU_INPUT_FOCUSED),
    _value(value),
    _heigthPadding(10),
    _callback(0)
{
  _text.init(FontsManager::DEFAULT, _value);
  placeText();
}

FormInputButton::~FormInputButton()
{
  if (_callback)
    delete _callback;
}

void FormInputButton::placeText()
{
  float	scaleX;

  scaleX = 1.25f;
  _text.setTranslation(glm::vec3(_posX + (1.0 * _sizeX - _text.getWidth() * scaleX) / 2.0,
				 _posY + _heigthPadding, 0.0f));
  _text.setScale(glm::vec3(1.25f, 1.253f, 1.0f));
}

void FormInputButton::update(gdl::Clock const &)
{
  if (_focused && (m_inputs->keyIsPressed(SDLK_RETURN) ||
		   m_inputs->keyIsPressed(PlayersKeysManager::getInstance()->getActionsKeys(PlayersKeysManager::ACTION))))
    {
      if (_callback) (*_callback)();
    }
}

void FormInputButton::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _sprite.draw(shader, clock);
  _text.draw(shader, clock);
}
