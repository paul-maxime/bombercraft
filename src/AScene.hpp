/**
 * \file AScene.hpp
 * Contains the Scene abstract class.
 */

#ifndef A_SCENE_HPP_
#define A_SCENE_HPP_

#include "IDrawable.hpp"

class InputsManager;

class GameEngine;

/**
 * \class AScene
 * A game scene, like a menu, the intro or the game itself.
 * Inherits from IDrawable.
 */
class AScene : public IDrawable
{
public:
  /**
   * Public constructor.
   * \param game The game engine containing the current scene.
   */
  AScene(GameEngine* game);

  /**
   * Virtual destructor.
   */
  virtual ~AScene();

  /**
   * Adds the current scene into the scene container.
   * \throw runtime_error if the scene is already opened.
   */
  void open();

  /**
   * Marks the scene as closing.
   */
  void close();

  /**
   * \return true if the scene has been marked for closing, false otherwise.
   */
  bool isClosed() const;

  /**
   * \return true if this scene can be drawn even in the background.
   */
  bool isBackground() const;

  /**
   * Updates the internal scene state.
   * Inherited from IDrawable.
   * \param clock Main clock, used to retrieve the elapsed time.
   */
  virtual void update(const gdl::Clock& clock) = 0;

  /**
   * Draws the scene on the screen.
   * Inherited from IDrawable.
   * \param shader The shader which should be used to draw the scene.
   * \param clock Main clock, used to retrieve the elapsed time.
   */
  virtual void draw(gdl::AShader& shader, const gdl::Clock& clock) = 0;

protected:
  GameEngine*		m_game;
  InputsManager*	m_inputs;
  bool			m_isBackground;

private:
  AScene(const AScene&);
  AScene& operator=(const AScene&);

  bool		m_opened;
  bool		m_closing;
};

#endif
