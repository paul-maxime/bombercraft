#include <map>
#include <iostream>

#include "MatrixManager.hpp"
#include "AudioManager.hpp"
#include "GameEngine.hpp"
#include "Menu.hpp"

#include "SceneMenu.hpp"
#include "SceneNewGame.hpp"
#include "SceneCredit.hpp"
#include "SceneOptions.hpp"
#include "SceneSave.hpp"
#include "SceneShowScore.hpp"

SceneMenu::SceneMenu(GameEngine* game)
  : AScene(game)
{
  _menu.initialize(this);
  AudioManager::getInstance()->playMusic(AudioManager::MENU);
  m_title.init(TextureManager::TITLE);
  m_title.setTranslation(glm::vec3(61.0f, 25.0f, 0.0f));
  m_background.init(TextureManager::INTRO_BACKGROUND, glm::vec2(game->getWidth(), game->getHeight()));

  _options[0] = &SceneMenu::chooseNewMap;
  _options[1] = &SceneMenu::chooseCredit;
  _options[2] = &SceneMenu::chooseScore;
  _options[3] = &SceneMenu::chooseOptions;
  _options[4] = &SceneMenu::chooseSave;
  _options[5] = &SceneMenu::chooseClose;
}

void SceneMenu::update(gdl::Clock const &clock)
{
  if (m_inputs->keyIsPressed(PlayersKeysManager::getInstance()->getActionsKeys(PlayersKeysManager::ESCAPE)))
    {
      close();
      return;
    }
  if (m_inputs->keyIsPressed(SDLK_KP_ENTER) ||
      m_inputs->keyIsPressed(SDLK_RETURN) ||
      m_inputs->keyIsPressed(SDLK_SPACE) ||
      m_inputs->keyIsPressed(PlayersKeysManager::getInstance()->getActionsKeys(PlayersKeysManager::ACTION)))
    choose(_menu.getChoice());
  _menu.update(clock);
}

void SceneMenu::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  MatrixManager* matrix = MatrixManager::getInstance();
  matrix->lookAt(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0));

  matrix->apply(MatrixManager::MATRIX_2D, shader);
  m_background.draw(shader, clock);
  m_title.draw(shader, clock);

  matrix->apply(MatrixManager::MATRIX_3D, shader);
  _menu.draw(shader, clock);
}

AScene* SceneMenu::chooseNewMap()
{
  return (new SceneNewGame(m_game));
}

AScene* SceneMenu::chooseCredit()
{
  return (new SceneCredit(m_game));
}

AScene* SceneMenu::chooseOptions()
{
  return (new SceneOptions(m_game));
}

AScene* SceneMenu::chooseSave()
{
  return (new SceneSave(m_game, NULL, NULL));
}

AScene* SceneMenu::chooseScore()
{
  return (new SceneShowScore(m_game));
}

AScene* SceneMenu::chooseClose()
{
  close();
  return (NULL);
}

void SceneMenu::choose(int choice)
{
  AScene* scene = NULL;

  if (choice >= 0 && choice < 6)
    scene = (this->*_options[choice])();
  if (scene)
    {
      AudioManager::getInstance()->playSound(AudioManager::CLICK);
      scene->open();
    }
}
