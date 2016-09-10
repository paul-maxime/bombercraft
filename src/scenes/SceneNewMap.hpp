/**
 * \file SceneNewMap.hpp
 * Defines the new-map scene.
 */

#ifndef SCENE_NEW_MAP_HPP_
#define SCENE_NEW_MAP_HPP_

#include <map>
#include <vector>
#include "AScene.hpp"
#include "Sprite.hpp"
#include "PlayersKeysManager.hpp"
#include "ASceneMenu.hpp"

class AFormInput;

/**
 * \class SceneNewMap
 * This scene allow too configure a map
 */
class SceneNewMap : public ASceneMenu
{
public:
  SceneNewMap(GameEngine* game, AScene& parent);
  virtual ~SceneNewMap();

  virtual void		update(gdl::Clock const &clock);
  virtual void		draw(gdl::AShader &shader, gdl::Clock const &clock);

private:
  SceneNewMap(const SceneNewMap &);
  SceneNewMap&		operator=(const SceneNewMap &);

  void	onClick();
  void	quit();

private:
  AScene*		_parent;
  Sprite		_background;
};

#endif
