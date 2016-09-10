#include <SdlContext.hh>
#include <Model.hh>

#include "Model3DManager.hpp"
#include "SceneMenu.hpp"
#include "Menu.hpp"

bool Menu::initialize(SceneMenu* menu)
{
  _menu = menu;
  _time = 0;
  _position = 0;
  _choice = 0;
  _direction = glm::vec3(0, 0, 0);
  _texture = TextureManager::MAIN_MENU;
  _model = Model3DManager::getInstance()->create(Model3DManager::MENU);
  _model->setCurrentAnim(0);
  scale(glm::vec3(0.05, 0.05, 0.05));
  translate(glm::vec3(0, -3, 0));
  setCenter(glm::vec3(0, 50, 0));
  rotate(glm::vec3(0, -2, 0), 90.f);
  _keys_actions[PlayersKeysManager::LEFT] = &Menu::key_left;
  _keys_actions[PlayersKeysManager::RIGHT] = &Menu::key_right;
  _keys_actions[PlayersKeysManager::UP] = &Menu::key_up;
  _keys_actions[PlayersKeysManager::DOWN] = &Menu::key_down;
  return (true);
}

int Menu::getChoice() const
{
  if (_time <= 0)
    {
      if (_position == 1)
	return (4);
      if (_position == -1)
	return (5);
      return (_choice);
    }
  return (-1);
}

void Menu::key_left()
{
  if (!_position)
    {
      _direction = glm::vec3(0, 1, 0);
      _time = 0.75;
      _choice = (_choice - 1) + 4 * (!_choice);
    }
}

void Menu::key_right()
{
  if (!_position)
    {
      _direction = glm::vec3(0, -1, 0);
      _time = 0.75;
      _choice = (_choice + 1) % 4;
    }
}

void Menu::key_up()
{
  if (_position <= 0)
    {
      _direction = glm::vec3(-1, _choice, 0);
      _time = 0.75;
      _choice = 0;
      ++_position;
    }
}

void Menu::key_down()
{
  if (_position >= 0)
    {
      _direction = glm::vec3(1, _choice, 0);
      _time = 0.75;
      _choice = 0;
      --_position;
    }  
}

void Menu::update(gdl::Clock const &clock)
{
  if (_time > 0)
    {
      float elapsed = clock.getElapsed();
      if (elapsed > _time)
	elapsed = _time;
      rotate(_direction, (elapsed / 0.75) * 90.0f);
      _time -= elapsed;
    }
  if (_time <= 0)
    {
      PlayersKeysManager* playersKeysManager = PlayersKeysManager::getInstance();
      for (std::map<PlayersKeysManager::Actions, void (Menu::*)()>::iterator it = _keys_actions.begin();
	     it != _keys_actions.end(); ++it)
	{
	  if (_inputs->keyIsHold(playersKeysManager->getActionsKeys(it->first)))
	    {
	      (this->*(it->second))();
	      return;
	    }
	}
    }
}

void Menu::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  TextureManager::getInstance()->bind(_texture);
  _model->draw(shader, getTransformation(), clock.getElapsed() * 2);
}
