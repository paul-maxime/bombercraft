#include <iostream>
#include <string>

#include "TextureManager.hpp"
#include "InputsManager.hpp"
#include "PlayersKeysManager.hpp"

#include "FormInputCheckBox.hpp"
#include "Text.hpp"
#include "GameEngine.hpp"

FormInputCheckBox::FormInputCheckBox(GameEngine *game,
				     const int posX, const int posY,
				     const int sizeX, const int sizeY,
				     const std::string &value,
				     bool checked)
  : AFormInput(game, posX, posY, sizeX, sizeY,
	       TextureManager::MENU_INPUT,
	       TextureManager::MENU_INPUT_FOCUSED),
    _value(value),
    _heigthPadding(10),
    _checked(checked)
{
  _checkBox.init(TextureManager::CHECKBOX_CHECKED, glm::vec2(sizeY - 10, sizeY - 10));
  _checkBox.translate(glm::vec3(posX + 5, posY + 5, 0.0f));
  _checkBox.setTexture(_checked ? TextureManager::CHECKBOX_CHECKED : TextureManager::CHECKBOX_NOT_CHECKED);

  _text.init(FontsManager::DEFAULT, _value);
  placeText();
}

FormInputCheckBox::~FormInputCheckBox()
{

}

void	FormInputCheckBox::placeText()
{
  float		scaleX;

  scaleX = 1.25f;
  _text.setTranslation(glm::vec3(_posX + (1.0 * _sizeX - _text.getWidth() * scaleX) / 2.0,
				 _posY + _heigthPadding, 0.0f));
  _text.setScale(glm::vec3(1.25f, 1.253f, 1.0f));
}

void	FormInputCheckBox::update(gdl::Clock const &)
{
  if (_focused && (m_inputs->keyIsPressed(SDLK_RETURN) || m_inputs->keyIsPressed(SDLK_SPACE) ||
		   m_inputs->keyIsPressed(PlayersKeysManager::getInstance()->getActionsKeys(PlayersKeysManager::ACTION))))
    {
      _checked = !_checked;
      _checkBox.setTexture(_checked ? TextureManager::CHECKBOX_CHECKED : TextureManager::CHECKBOX_NOT_CHECKED);
    }
}

void	FormInputCheckBox::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _sprite.draw(shader, clock);
  _checkBox.draw(shader, clock);
  _text.draw(shader, clock);
}

int	FormInputCheckBox::getValue() const
{
  return (_checked);
}
