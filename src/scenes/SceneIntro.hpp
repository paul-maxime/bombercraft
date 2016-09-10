/**
 * \file SceneIntro.hpp
 * Defines the introduction scene.
*/

#ifndef SCENE_INTRO_HPP_
#define SCENE_INTRO_HPP_

#include <vector>
#include "AScene.hpp"
#include "Sprite.hpp"
#include "AnimatedModel.hpp"

namespace gdl
{
  class Model;
};

/**
 * \class SceneGame
 * This scene show the intro animation
 */
class SceneIntro : public AScene
{
public:
  SceneIntro(GameEngine* game);
  virtual ~SceneIntro();

  virtual void		update(gdl::Clock const &clock);
  virtual void		draw(gdl::AShader &shader, gdl::Clock const &clock);

private:
  SceneIntro(const SceneIntro &);
  SceneIntro &operator=(const SceneIntro &);

  void	scene1(const gdl::Clock& clock);
  void	scene2(const gdl::Clock& clock);
  void	scene3(const gdl::Clock& clock);
  void	scene4(const gdl::Clock& clock);
  void	scene5(const gdl::Clock& clock);

private:
  typedef void	(SceneIntro::*func)(const gdl::Clock&);

  const std::vector<int>& m_skipKeys;

  std::vector<func>	m_scenes;
  unsigned int		m_current;
  Sprite		m_background;
  Sprite		m_title;
  bool			m_showMarvin;
  AnimatedModel		m_steve;
  AnimatedModel		m_marvin;
};

#endif
