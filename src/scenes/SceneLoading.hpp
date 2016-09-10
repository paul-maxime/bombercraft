/**
 * \file SceneIntro.hpp
 * Defines the introduction scene.
*/

#ifndef SCENE_LOADING_HPP_
#define SCENE_LOADING_HPP_

#include <pthread.h>

#include "AScene.hpp"
#include "Sprite.hpp"

class Loading;

/**
 * \class SceneLoading
 * This scene load all the utils manager and aff a background
 */
class SceneLoading : public AScene
{
public:
  SceneLoading(GameEngine* game);
  virtual ~SceneLoading();

  virtual void	update(gdl::Clock const &clock);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);

private:
  SceneLoading(const SceneLoading &);
  SceneLoading &operator=(const SceneLoading &);
  void loading();

private:
  std::string		m_text;
  bool			m_end;
  bool			m_background_ready;
  Sprite		m_background;
};

#endif
