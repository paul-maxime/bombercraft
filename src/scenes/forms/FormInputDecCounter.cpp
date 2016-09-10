#include <string>

#include "TextureManager.hpp"
#include "InputsManager.hpp"
#include "PlayersKeysManager.hpp"

#include "FormInputDecCounter.hpp"
#include "GameEngine.hpp"
#include "Text.hpp"
#include "Utils.hpp"

FormInputDecCounter::FormInputDecCounter(GameEngine *game,
					 const int posX, const int posY,
					 const int sizeX, const int sizeY,
					 const std::string &value,
					 const int minValue, const int maxValue, const int currentValue)
  : AFormInput(game, posX, posY, sizeX, sizeY,
	       TextureManager::MENU_INPUT,
	       TextureManager::MENU_INPUT_FOCUSED),
    _value(value),
    _heigthPadding(10),
    _currentValue(currentValue),
    _minValue(minValue),
  _maxValue(maxValue),
  _time(0)
{
}

FormInputDecCounter::~FormInputDecCounter()
{

}

void	FormInputDecCounter::update(gdl::Clock const &clock)
{
  float elapsed;

  if (_time > 0)
    {
      elapsed = clock.getElapsed();
      if (elapsed > _time)
	elapsed = _time;
      _time -= elapsed;
    }
  if (_time <= 0 && _focused &&
      m_inputs->keyIsHold(PlayersKeysManager::getInstance()->getActionsKeys(PlayersKeysManager::RIGHT)))
    {
      ++_currentValue;
      if (_currentValue > _maxValue)
	_currentValue = _maxValue;
      _time = 0.1;
    }
  if (_time <= 0 && _focused &&
      m_inputs->keyIsHold(PlayersKeysManager::getInstance()->getActionsKeys(PlayersKeysManager::LEFT)))
    {
      --_currentValue;
      if (_currentValue < _minValue)
	_currentValue = _minValue;
      _time = 0.1;
    }
}

void	FormInputDecCounter::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  Text		textValue;
  Text		text;
  float		scaleX;

  scaleX = 1.25f;
  textValue.init(FontsManager::DEFAULT,
		 std::string(" <  ") + Utils::toString(_currentValue) + std::string("  > "));
  textValue.setTranslation(glm::vec3(_posX + 5, _posY + _heigthPadding, 0.0f));
  textValue.setScale(glm::vec3(scaleX, 1.253f, 1.0f));

  text.init(FontsManager::DEFAULT, _value);
  text.setTranslation(glm::vec3(_posX + (1.0 * _sizeX - text.getWidth() * scaleX) / 2.0,
				_posY + _heigthPadding, 0.0f));
  text.setScale(glm::vec3(1.25f, 1.253f, 1.0f));

  _sprite.draw(shader, clock);
  text.draw(shader, clock);
  textValue.draw(shader, clock);
}

int	FormInputDecCounter::getValue() const
{
  return _currentValue;
}

void	FormInputDecCounter::changeMaxValue(int maxValue)
{
  _maxValue = maxValue;
  if (_currentValue > _maxValue)
    _currentValue = _maxValue;
}
