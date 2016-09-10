/**
 * \file SceneOptions.hpp
 * Defines the options scene.
 */

#ifndef SCENE_OPTIONS_HPP_
#define SCENE_OPTIONS_HPP_

#include <vector>
#include "ASceneMenu.hpp"
#include "Sprite.hpp"
#include "PlayersKeysManager.hpp"

class AFormInput;

/**
 * \class SceneOptions
 * This scene contains the audio options
 */
class SceneOptions : public ASceneMenu
{
public:
  SceneOptions(GameEngine* game);
  virtual ~SceneOptions();

  virtual void		update(gdl::Clock const &clock);
  virtual void		draw(gdl::AShader &shader, gdl::Clock const &clock);

  void			onClick();

private:
  SceneOptions(const SceneOptions &);
  SceneOptions		&operator=(const SceneOptions &);

private:
  Sprite		_background;
};

#endif
