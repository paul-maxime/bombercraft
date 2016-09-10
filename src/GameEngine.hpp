/**
 * \file GameEngine.hpp
 * Contains the GameEngine class.
 */

#ifndef GAME_ENGINE_HPP_
#define GAME_ENGINE_HPP_

#include <Game.hh>
#include <SdlContext.hh>
#include <BasicShader.hh>

#include "SceneContainer.hpp"

class Options;
class InputsManager;

/**
 * \class GameEngine
 * Main game class, contains the whole game logic.
 */
class GameEngine : public gdl::Game
{
public:
  /**
   * \class MapParameters
   * Contains the informations about map generation.
   */
  class		MapParameters
  {
  public:
    int		nbPlayers;
    int		nbIAPlayers;
    int		sizeX;
    int		sizeY;
    int		wallDensity;
    int		objectsDensity;
    int		bonusDensity;
    bool	wallGrid;
  };

public:
  /**
   * Public constructor.
   * \param options The program parameters.
   */
  GameEngine(const Options& options);

  /**
   * Virtual destructor.
   */
  virtual ~GameEngine();

  /**
   * Initialize the game engine.
   * Loads an SDL context, the shaders, the first menu,
   * the textures and the models.
   * \return true on success, false on error.
   */
  virtual bool initialize();

  /**
   * Updates the game logic : clock, inputs and scenes.
   * @return true if we want to continue the game execution, false otherwise.
   */
  virtual bool update();

  /**
   * Clears the screen the draws the scenes.
   */
  virtual void draw();

  /**
   * \return The SceneContainer handling the opened scenes.
   */
  SceneContainer&	getScenes();

  /**
  ** \return screen width.
  */
  int	getWidth() const;

  /**
  ** \return screen height.
  */
  int	getHeight() const;

  /**
   * \return the map generation parameters.
   */
  MapParameters&	getMapParams();

private:
  gdl::SdlContext	_context;
  const Options&	_options;

  gdl::Clock		_clock;
  gdl::Input		_input;
  gdl::BasicShader	_shader;

  SceneContainer	_scenes;
  InputsManager		*_inputs;
  int			_width;
  int			_height;

  MapParameters		_mapParams;
};

#endif
