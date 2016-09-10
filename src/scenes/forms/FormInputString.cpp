#include <iostream>
#include <string>

#include "TextureManager.hpp"
#include "InputsManager.hpp"

#include "FormInputString.hpp"
#include "Text.hpp"
#include "GameEngine.hpp"

FormInputString::FormInputString(GameEngine *game,
				 const int posX, const int posY,
				 const int sizeX, const int sizeY,
				 const std::string &value, const std::string &label)
  : AFormInput(game, posX, posY, sizeX, sizeY,
	       TextureManager::MENU_INPUT,
	       TextureManager::MENU_INPUT_FOCUSED),
    _value(value)
{
  _label.init(FontsManager::DEFAULT, label);
  _label.setTranslation(glm::vec3(_posX + 10, _posY + 10, 0.0f));
  _label.setScale(glm::vec3(1.25f, 1.253f, 1.0f));
}

FormInputString::~FormInputString()
{

}

void	FormInputString::update(gdl::Clock const &)
{
  if (_focused)
    {
      for (int i = SDLK_a; i <= SDLK_z; ++i)
	if (InputsManager::getInstance()->keyIsPressed(i))
	  _value += static_cast<char>(i);
      for (int i = SDLK_0; i <= SDLK_9; ++i)
	if (InputsManager::getInstance()->keyIsPressed(i))
	  _value += static_cast<char>(i);
      if (InputsManager::getInstance()->keyIsPressed(SDLK_BACKSPACE))
	if (_value.size() > 0)
	  _value.erase(_value.size() - 1, std::string::npos);
    }
}

void	FormInputString::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  Text		text;

  _sprite.draw(shader, clock);
  if (_value.size() > 0)
    {
      text.init(FontsManager::DEFAULT, _value);
      text.setTranslation(glm::vec3(_posX + 40 + _label.getWidth(), _posY + 10, 0.0f));
      text.setScale(glm::vec3(1.25f, 1.253f, 1.0f));
      text.draw(shader, clock);
    }
  _label.draw(shader, clock);
}

const std::string	&FormInputString::getString() const
{
  return (_value);
}
