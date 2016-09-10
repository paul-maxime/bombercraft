#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TextureManager.hpp"
#include "Model3DManager.hpp"
#include "FontsManager.hpp"
#include "MatrixManager.hpp"
#include "InputsManager.hpp"
#include "ScoreManager.hpp"

#include "GameEngine.hpp"
#include "SceneIntro.hpp"
#include "SceneLoading.hpp"
#include "SceneGame.hpp"
#include "Options.hpp"

GameEngine::GameEngine(const Options& options)
  : _options(options), _width(800), _height(600)
{
}

GameEngine::~GameEngine()
{
  TextureManager::destroy();
  Model3DManager::destroy();
  FontsManager::destroy();
  MatrixManager::destroy();
  InputsManager::destroy();
  _context.stop();
}

bool GameEngine::initialize()
{
  int flags = SDL_WINDOW_OPENGL;
  _mapParams.nbPlayers = 1;
  _mapParams.nbIAPlayers = 5;
  _mapParams.sizeX = 40;
  _mapParams.sizeY = 40;
  _mapParams.wallDensity = 10;
  _mapParams.objectsDensity = 30;
  _mapParams.bonusDensity = 20;
  _mapParams.wallGrid = true;
  if (_options.isFullscreen())
    flags |= SDL_WINDOW_FULLSCREEN;

  if (!_context.start(_width, _height, "Bombercraft v.release 1.0",
		      SDL_INIT_VIDEO | SDL_INIT_JOYSTICK, flags))
    return false;

  SDL_JoystickEventState(SDL_ENABLE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if (!_shader.load("./data/shaders//basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./data/shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return false;

  ScoreManager::getInstance();
  FontsManager::getInstance();
  _inputs = InputsManager::getInstance();

  AScene* menu = new SceneLoading(this);
  menu->open();

  MatrixManager* matrix = MatrixManager::getInstance();
  matrix->perspective(60.0f, _width, _height);
  matrix->ortho(_width, _height);

  return true;
}

bool GameEngine::update()
{
  if (_inputs->hasQuit())
    return false;
  _context.updateClock(_clock);
  _inputs->listening();
  _scenes.update(_clock);
  return !_scenes.isEmpty();
}

void GameEngine::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _scenes.draw(_shader, _clock);
  _context.flush();
}

SceneContainer& GameEngine::getScenes()
{
  return _scenes;
}

int	GameEngine::getWidth() const
{
  return _width;
}

int	GameEngine::getHeight() const
{
  return _height;
}

GameEngine::MapParameters& GameEngine::getMapParams()
{
  return _mapParams;
}
