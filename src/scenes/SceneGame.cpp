#include <algorithm>
#include <stdexcept>
#include <glm/gtc/matrix_transform.hpp>

#include "AudioManager.hpp"
#include "InputsManager.hpp"
#include "TextureManager.hpp"
#include "MatrixManager.hpp"

#include "SceneGame.hpp"
#include "ScenePause.hpp"
#include "SceneEndGame.hpp"
#include "AFormCallback.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Text.hpp"
#include "Sprite.hpp"

SceneGame::SceneGame(GameEngine* game, Map* loadMap)
  : AScene(game),
    _showFps(false),
    _matrix(MatrixManager::getInstance()),
    _maxPlayerPeerLine(2)
{
  int nbUnitX;
  int nbUnitY;

  AudioManager::getInstance()->playMusic(AudioManager::GAME);
  m_isBackground = true;
  if (loadMap)
    {
      _map = loadMap;
      std::vector<Player*> players;
      _map->getOrderedRealPlayers(players);
      for (std::vector<Player*>::const_iterator it = players.begin(); it != players.end(); ++it)
	{
	  if (!(*it)->isIA())
	    {
	      SceneGame::PlayerPosition	*playerPositions = new SceneGame::PlayerPosition;

	      playerPositions->player = (*it);
	      _players.push_back(playerPositions);
	    }
	}
    }
  else
    {
      _map = new Map();
      _map->generate(game->getMapParams());

      PlayersKeysManager* keys = PlayersKeysManager::getInstance();
      for (int i = 0; i < game->getMapParams().nbPlayers && i < keys->playersKeysSize(); ++i)
	{
	  SceneGame::PlayerPosition	*playerPositions = new SceneGame::PlayerPosition;

	  playerPositions->player = _map->addPlayer(i);
	  if (!playerPositions->player)
	    throw std::runtime_error("Not enough place for a new player");
	  _players.push_back(playerPositions);
	}
    }
  nbUnitX = (_players.size() > _maxPlayerPeerLine) ? _maxPlayerPeerLine : _players.size();
  nbUnitY = _players.size() / nbUnitX + ((_players.size() % nbUnitX != 0) ? 1 : 0);
  _unitWidth = m_game->getWidth() / nbUnitX;
  _unitHeigth = m_game->getHeight() / nbUnitY;

  for (std::vector<SceneGame::PlayerPosition *>::iterator it = _players.begin();
       it != _players.end();
       ++it)
    {
      (*it)->oriX = _unitWidth * ((it - _players.begin()) % nbUnitX);
      (*it)->oriY = m_game->getHeight() - ((((it - _players.begin()) / nbUnitX) + 1) * _unitHeigth);
      (*it)->viewPortOriX = (*it)->oriX - (m_game->getWidth() / 2) + (_unitWidth / 2);
      (*it)->viewPortOriY = (*it)->oriY - (m_game->getHeight() / 2) + (_unitHeigth / 2);
      (*it)->posY = ((((it - _players.begin()) / nbUnitX) + 1) * _unitHeigth) - _unitHeigth;
    }

  _floor = new Plane(_map->getWidth(), _map->getHeight());

  const std::vector<int> actions = PlayersKeysManager::getInstance()->getActionsKeys(PlayersKeysManager::ESCAPE);
  for (std::vector<int>::const_iterator it = actions.begin(); it != actions.end(); ++it)
    m_keys[*it] = new FormCallback<SceneGame>(this, &SceneGame::onKeyEscape);
  m_keys[SDLK_F3] = new FormCallback<SceneGame>(this, &SceneGame::onKeyF3);
}

SceneGame::~SceneGame()
{
  delete _map;
  delete _floor;
  for (std::vector<SceneGame::PlayerPosition *>::iterator it = _players.begin();
       it != _players.end();
       ++it)
    {
      delete (*it)->player;
      delete (*it);
    }
  AudioManager::getInstance()->playMusic(AudioManager::MENU);
}

Map*	SceneGame::getMap() const
{
  return (_map);
}

void SceneGame::update(gdl::Clock const &clock)
{
  std::for_each(m_keys.begin(), m_keys.end(), &AFormCallback::call);

  if (_map->nbIAplayersAlive() + nbHumanPlayersAlive() <= 1 ||
      nbHumanPlayersAlive() == 0)
    {
      endGame();
      return ;
    }

  _map->update(clock);
}

void SceneGame::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  splitBegin();

  for (std::vector<SceneGame::PlayerPosition *>::iterator it = _players.begin();
       it != _players.end();
       ++it)
    drawPlayerView(*(*it), shader, clock);

  splitEnd();

  MatrixManager::getInstance()->apply(MatrixManager::MATRIX_2D, shader);

  for (std::vector<SceneGame::PlayerPosition *>::iterator it = _players.begin();
       it != _players.end();
       ++it)
    drawPlayerStatus(*(*it), shader, clock);

  drawFPS(shader, clock);
}

void SceneGame::onKeyEscape()
{
  ScenePause* pause = new ScenePause(m_game, this);
  pause->open();
}

void SceneGame::onKeyF3()
{
  _showFps = !_showFps;
}

void SceneGame::splitBegin() const
{
  glEnable(GL_SCISSOR_TEST);
}

void SceneGame::splitEnd() const
{
  glDisable(GL_SCISSOR_TEST);
  glViewport(0, 0, m_game->getWidth(), m_game->getHeight());
}

void SceneGame::splitScreen(const SceneGame::PlayerPosition &playerPos) const
{
  glViewport(playerPos.viewPortOriX, playerPos.viewPortOriY, m_game->getWidth(), m_game->getHeight());
  glScissor(playerPos.oriX, playerPos.oriY, _unitWidth, _unitHeigth);
}

void SceneGame::drawPlayerView(const SceneGame::PlayerPosition &player,
			       gdl::AShader &shader, gdl::Clock const &clock) const
{
  splitScreen(player);

  int posX, posY;
  player.player->setViewPoint(shader, posX, posY);
  _map->draw(shader, clock, posX, posY, 15);

  TextureManager::getInstance()->bind(TextureManager::GRASS, true);
  _floor->draw(shader, glm::translate(glm::mat4(1), glm::vec3(-0.5, -0.5, -0.5)));
}

void SceneGame::drawPlayerStatus(const SceneGame::PlayerPosition &player,
				 gdl::AShader &shader, gdl::Clock const &clock) const
{
  Sprite livesSprite(TextureManager::LIVE, glm::vec2(32, 32));
  livesSprite.translate(glm::vec3(player.oriX + 5, player.posY + 5, 0.0f));
  livesSprite.draw(shader, clock);

  Text livesText(FontsManager::DEFAULT, Utils::toString(player.player->getLives()));
  livesText.setTranslation(glm::vec3(player.oriX + 42, player.posY + 10, 0.0f));
  livesText.setScale(glm::vec3(0.8f, 0.8f, 1.0f));
  livesText.draw(shader, clock);

  Sprite bombsSprite(TextureManager::BOMBS, glm::vec2(32, 32));
  bombsSprite.translate(glm::vec3(player.oriX + 55, player.posY + 5, 0.0f));
  bombsSprite.draw(shader, clock);

  Text bombsText(FontsManager::DEFAULT, Utils::toString(player.player->getBombs()));
  bombsText.setTranslation(glm::vec3(player.oriX + 92, player.posY + 10, 0.0f));
  bombsText.setScale(glm::vec3(0.8f, 0.8f, 1.0f));
  bombsText.draw(shader, clock);

  Text pointsText(FontsManager::DEFAULT, Utils::toString(player.player->getPoints()));
  pointsText.setTranslation(glm::vec3(player.oriX + 129, player.posY + 10, 0.0f));
  pointsText.setScale(glm::vec3(0.8f, 0.8f, 1.0f));
  pointsText.draw(shader, clock);

  Sprite endGameSprite;
  if (!player.player->isAlive())
    {
      endGameSprite.init(TextureManager::LOSE, glm::vec2(280, 116));
      endGameSprite.translate(glm::vec3(player.oriX + (_unitWidth / 2) - 140,
					player.posY + (_unitHeigth / 2) - 58, 0.0f));
      endGameSprite.draw(shader, clock);
    }
  else if (_map->nbIAplayersAlive() == 0 && nbHumanPlayersAlive() == 1)
    {
      endGameSprite.init(TextureManager::WIN, glm::vec2(210, 116));
      endGameSprite.translate(glm::vec3(player.oriX + (_unitWidth / 2) - 105,
					player.posY + (_unitHeigth / 2) - 58, 0.0f));
      endGameSprite.draw(shader, clock);
    }
}

void SceneGame::drawFPS(gdl::AShader &shader, gdl::Clock const &clock) const
{
  if (_showFps)
    {
      int fps = static_cast<int>(1.0f / clock.getElapsed());
      Text text(FontsManager::DEFAULT, Utils::toString(fps) + " fps");

      text.translate(glm::vec3(8, 40, 0));
      shader.setUniform("color", glm::vec4(0, 0, 0, 1));
      text.draw(shader, clock);
      shader.setUniform("color", glm::vec4(1));
      text.translate(glm::vec3(-3, -3, 0));
      text.draw(shader, clock);
    }
}

int SceneGame::nbHumanPlayersAlive() const
{
  int count = 0;
  for (std::vector<SceneGame::PlayerPosition *>::const_iterator it = _players.begin();
       it != _players.end();
       ++it)
    if ((*it)->player->isAlive())
      ++count;
  return count;
}

void SceneGame::endGame()
{
  SceneEndGame* sceneEndGame = new SceneEndGame(m_game, this);
  sceneEndGame->open();
}
