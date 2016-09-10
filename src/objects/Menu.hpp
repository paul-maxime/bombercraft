/**
 * \file Menu.hpp
 * Defines the menu object.
 */

#ifndef MENU_HPP_
#define MENU_HPP_

#include <Texture.hh>
#include <Geometry.hh>
#include "PlayersKeysManager.hpp"
#include "TextureManager.hpp"
#include "InputsManager.hpp"
#include "AObject.hpp"

namespace gdl
{
  class Model;
}

class SceneMenu;

class Menu : public AObject
{
private:
  TextureManager::TextureName		_texture;
  float					_time;
  glm::vec3				_direction;
  SceneMenu*				_menu;
  InputsManager*			_inputs;
  int					_position;
  int					_choice;
  gdl::Model*				_model;
  std::map<PlayersKeysManager::Actions, void (Menu::*)()>	_keys_actions;

public:
  Menu() : _inputs(InputsManager::getInstance()) {}
  virtual ~Menu() {}

  virtual bool initialize(SceneMenu* menu);
  virtual void update(gdl::Clock const &clock);
  virtual void draw(gdl::AShader &shader, gdl::Clock const &clock);
  int getChoice() const;

private:
  void key_left();
  void key_right();
  void key_up();
  void key_down();
};

#endif
