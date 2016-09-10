/**
 * \file SceneSave.hpp
 * Defines the save scene.
 */

#ifndef SCENE_SAVE_HPP_
#define SCENE_SAVE_HPP_

#include <map>
#include <vector>

#include "AScene.hpp"
#include "Sprite.hpp"
#include "Text.hpp"

class AFormInput;
class Map;
class Screenshot;

/**
 * \class SceneSave
 * This scene allow to save a game
 */
class SceneSave : public AScene
{
public:
  SceneSave(GameEngine* game, Map* map, Screenshot* screen);
  virtual ~SceneSave();

  void		onClick();

  virtual void	update(const gdl::Clock& clock);
  virtual void	draw(gdl::AShader& shader, const gdl::Clock& clock);

private:
  SceneSave(const SceneSave&);
  SceneSave& operator=(const SceneSave&);

  void	addSaveSlot(const std::string& file, int posX, int posY);

  void	quit();
  void	downCursor();
  void	upCursor();
  void	leftCursor();
  void	rightCursor();

  void	load();
  void	save();

private:
  typedef void	(SceneSave::*func)();

  std::map<PlayersKeysManager::Actions, func>	_actions;

  const std::string		_folder;
  const unsigned int		_maxSave;
  const unsigned int		_topBorder;
  const unsigned int		_border;
  const unsigned int		_hpadding;
  const unsigned int		_vpadding;
  int				_slotSize;
  Map*				_map;
  Sprite			_background;
  std::vector<AFormInput*>	_inputs;
  std::vector<bool>		_filesEmpty;
  std::vector<std::string>	_filesName;
  unsigned int			_cursor;
  bool				_selected;
  int				_choice;
  Text				_header;
  Screenshot*			_screen;
};

#endif
