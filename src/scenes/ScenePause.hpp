/*
 * \file ScenePause.hpp
 * Describes the pause menu scene.
 */

#ifndef SCENE_PAUSE_HPP_
#define SCENE_PAUSE_HPP_

#include <map>
#include <vector>
#include "ASceneMenu.hpp"
#include "Screenshot.hpp"
#include "PlayersKeysManager.hpp"

class AFormInput;
class AFormCallback;
class SceneGame;

/**
 * \class ScenePause
 * This scene contains the pause in-game
 */
class ScenePause : public ASceneMenu
{
public:
  ScenePause(GameEngine* game, SceneGame* parent);
  virtual ~ScenePause();

  virtual void		update(gdl::Clock const &clock);
  virtual void		draw(gdl::AShader &shader, gdl::Clock const &clock);

private:
  void			onResumeClick();
  void			onOptionsClick();
  void			onSaveClick();
  void			onMenuClick();

  SceneGame *		m_parent;
  Screenshot		m_preview;
};

#endif
