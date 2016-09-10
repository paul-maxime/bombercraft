#include "SceneNewGame.hpp"
#include "MatrixManager.hpp"
#include "InputsManager.hpp"
#include "SceneNewMap.hpp"
#include "SceneChooseMap.hpp"
#include "FormInputButton.hpp"
#include "AudioManager.hpp"

SceneNewGame::SceneNewGame(GameEngine *game)
  : ASceneMenu(game, 0),
    _buttonSize(glm::vec2(250, 63)),
    _padding(20)
{
  int decx = (game->getWidth() - _buttonSize.x) / 2,
    decy = (game->getHeight() - _buttonSize.y * 2 - _padding) / 2;
  FormInputButton* button = new FormInputButton(game, decx, decy, _buttonSize.x,
					       _buttonSize.y, "Choisir la carte");
  button->setCallback(this, &SceneNewGame::chooseMap);
  m_buttons.push_back(button);

  button = new FormInputButton(game, decx, decy + _buttonSize.y + _padding,
			       _buttonSize.x, _buttonSize.y, "Carte custom");
  button->setCallback(this, &SceneNewGame::customMap);
  m_buttons.push_back(button);

  _background.init(TextureManager::BACKGROUND, glm::vec2(game->getWidth(), game->getHeight()));
}

SceneNewGame::~SceneNewGame()
{
}

void	SceneNewGame::chooseMap()
{
  SceneChooseMap* chooseMap = new SceneChooseMap(m_game, *this);
  AudioManager::getInstance()->playSound(AudioManager::CLICK);
  chooseMap->open();
}

void	SceneNewGame::customMap()
{
  SceneNewMap* customMap = new SceneNewMap(m_game, *this);
  AudioManager::getInstance()->playSound(AudioManager::CLICK);
  customMap->open();
}

void		SceneNewGame::update(gdl::Clock const &clock)
{
  ASceneMenu::update(clock);
}

void		SceneNewGame::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _background.draw(shader, clock);
  ASceneMenu::draw(shader, clock);
}
