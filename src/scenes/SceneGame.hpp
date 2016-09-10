/**
 * \file SceneGame.hpp
 * Defines the game scene.
 */

#ifndef SCENE_GAME_HPP_
#define SCENE_GAME_HPP_

#include <string>
#include <vector>

#include "AScene.hpp"
#include "Plane.hpp"
#include "PlayersKeysManager.hpp"

class AFormCallback;
class Map;
class Player;

/**
 * \class SceneGame
 * Represents the main game scene, which contains the players and the map.
 */
class SceneGame : public AScene
{
private:
  /**
   * \class PlayerPosition
   * Describes a player screen as a part of the main screen.
   */
  class		PlayerPosition
  {
  public:
    Player*	player;		//< Player entity represented by this structure.
    int		oriX;		//< X position of the visible player screen (unit).
    int		oriY;		//< Y position of the visible player screen (unit).
    int		posY;		//< Y position used to draw the UI interface.
    int		viewPortOriX;	//< X position of the full player screen (glViewport).
    int		viewPortOriY;	//< Y position of the full player screen (glViewport).
  };

public:
  /**
   * Public constructor.
   * \param game The game engine containing the current scene.
   * \param load An optional file name to load.
   */
  SceneGame(GameEngine* game, Map* loadMap = NULL);

  /**
   * Virtual destructor.
   */
  virtual ~SceneGame();

  /**
   * Return a pointer to the map currently in use
   */
  Map*		getMap() const;

  /**
   * Updates the internal scene state.
   * Inherited from AScene.
   * \param clock Main clock, used to retrieve the elapsed time.
   */
  virtual void	update(gdl::Clock const &clock);

  /**
   * Draws the scene on the screen.
   * Inherited from AScene.
   * \param shader The shader which should be used to draw the scene.
   * \param clock Main clock, used to retrieve the elapsed time.
   */
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);

private:
  /*
   * Keyboard events.
   */
  void		onKeyEscape();
  void		onKeyF3();

  /**
   * Starts the split-screen OpenGL directives.
   */
  void		splitBegin() const;

  /**
   * Splits the screen in order to draw the specific player.
   * \param player Player which will be drawn.
   */
  void		splitScreen(const SceneGame::PlayerPosition &player) const;

  /**
   * Stops the split-screen OpenGL directives.
   */
  void		splitEnd() const;

  /**
   * Draws the player 3d view.
   * \param player Player which will be drawn.
   * \param shader The shader which should be used to draw the scene.
   * \param clock Main clock, used to retrieve the elapsed time.
   */
  void		drawPlayerView(const SceneGame::PlayerPosition &player,
			       gdl::AShader &shader, gdl::Clock const &clock) const;

  /**
   * Draws the player 2d interface.
   * \param player Player which will be drawn.
   * \param shader The shader which should be used to draw the scene.
   * \param clock Main clock, used to retrieve the elapsed time.
   */
  void		drawPlayerStatus(const SceneGame::PlayerPosition &player,
				 gdl::AShader &shader, gdl::Clock const &clock) const;

  /**
   * Draws the current FPS on the screen.
   * \param shader The shader which should be used to draw the scene.
   * \param clock Main clock, used to retrieve the elapsed time.
   */
  void		drawFPS(gdl::AShader &shader, gdl::Clock const &clock) const;

  /**
   * \return the quantity of human players alive.
   */
  int		nbHumanPlayersAlive() const;

  /**
   * Shows the end-screen scene, when everyone's dead.
   */
  void		endGame();

  Map *						_map;
  std::vector<SceneGame::PlayerPosition *>	_players;
  Plane *					_floor;
  bool						_showFps;
  MatrixManager *				_matrix;
  int						_unitWidth;
  int						_unitHeigth;
  unsigned long					_maxPlayerPeerLine;

  std::map<int, AFormCallback *>		m_keys;
};

#endif
