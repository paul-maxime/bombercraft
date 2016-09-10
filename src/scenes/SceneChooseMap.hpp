#ifndef SCENE_CHOOSE_MAP_HPP_
#define SCENE_CHOOSE_MAP_HPP_

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <istream>
#include <fstream>

#include "AScene.hpp"
#include "Sprite.hpp"
#include "PlayersKeysManager.hpp"
#include "CharToEntityConverter.hpp"

class AFormInput;

/**
 * \class ScheneChooseMap
 * This scene allow to choose a pre-defined map
 */

class SceneChooseMap : public AScene
{
public:
  class	AsciiMapInfo
  {
  public:
    std::string			content;
    unsigned int		width;
    unsigned int		height;
    std::vector<glm::vec2>	spawns;
  };
public:
  SceneChooseMap(GameEngine* game, AScene& parent);
  ~SceneChooseMap();

  virtual void	update(const gdl::Clock& clock);
  virtual void	draw(gdl::AShader& shader, const gdl::Clock& clock);

private:
  SceneChooseMap(const SceneChooseMap&);
  SceneChooseMap&	operator=(const SceneChooseMap);

  void			addMaps();
  bool			loadMap(const std::string& file, AsciiMapInfo& infos) const;
  bool			checkMapLine(const std::string& file, const std::string& line,
				     AsciiMapInfo& infos) const;

  void			quit();
  void			leftCursor();
  void			rightCursor();

  void			launchGame();

private:
  typedef void	(SceneChooseMap::*func)();

  CharToEntityConverter		_converter;

  AScene*			_parent;

  std::map<PlayersKeysManager::Actions, func>	_actions;

  Sprite			_background;
  const std::string		_folder;
  unsigned int			_cursor;
  std::vector<AFormInput*>	_inputs;
  std::vector<AsciiMapInfo>	_maps;
};

#endif
