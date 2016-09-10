/**
 * \file SceneMenu.hpp
 * Defines the menu scene.
 */

#ifndef SCENE_MENU_HPP_
#define SCENE_MENU_HPP_

#include <map>

#include "AScene.hpp"
#include "Menu.hpp"
#include "Sprite.hpp"

class Menu;

/**
 * \class SceneMenu
 * This scene contains the main menu
 */
class SceneMenu : public AScene
{
private:
  Menu		_menu;
  Sprite	m_title;
  Sprite	m_background;

public:
  /**
   * Public constructor.
   * \param game The game engine containing the current scene.
   */
  SceneMenu(GameEngine* game);

  /**
   * Virtual destructor.
   */
  virtual ~SceneMenu() {}

  /**
   * Updates the internal scene state.
   * Inherited from IDrawable.
   * /param clock Main clock, used to retrieve the elapsed time.
   */
  virtual void update(gdl::Clock const &clock);

  /**
   * Draws the scene on the screen.
   * Inherited from IDrawable.
   * /param shader The shader which should be used to draw the scene.
   * /param clock Main clock, used to retrieve the elapsed time.
   */
  virtual void draw(gdl::AShader &shader, gdl::Clock const &clock);

  /**
   * Open the choosen scene.
   */
  void choose(int choice);

private:
  AScene* chooseNewMap();
  AScene* chooseCredit();
  AScene* chooseOptions();
  AScene* chooseSave();
  AScene* chooseClose();
  AScene* chooseScore();

  std::map<int, AScene* (SceneMenu::*)()> _options;

};

#endif
