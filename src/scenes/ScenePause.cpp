#include <algorithm>

#include "InputsManager.hpp"
#include "MatrixManager.hpp"
#include "AudioManager.hpp"
#include "ScenePause.hpp"
#include "SceneGame.hpp"
#include "SceneOptions.hpp"
#include "SceneSave.hpp"
#include "FormCallback.hpp"
#include "FormInputButton.hpp"

ScenePause::ScenePause(GameEngine* game, SceneGame* parent)
  : ASceneMenu(game, 0),
    m_parent(parent)
{
  m_preview.saveScreenBuffer(game->getWidth(), game->getHeight());

  FormInputButton* button = new FormInputButton(game, 170, 150, 500, 60, "Continuer");
  button->setCallback(this, &ScenePause::onResumeClick);
  button->setFocus(true);
  m_buttons.push_back(button);
  button = new FormInputButton(game, 170, 240, 500, 60, "Options");
  button->setCallback(this, &ScenePause::onOptionsClick);
  m_buttons.push_back(button);
  button = new FormInputButton(game, 170, 330, 500, 60, "Sauvegarder");
  button->setCallback(this, &ScenePause::onSaveClick);
  m_buttons.push_back(button);
  button = new FormInputButton(game, 170, 420, 500, 60, "Retour au menu");
  button->setCallback(this, &ScenePause::onMenuClick);
  m_buttons.push_back(button);
}

ScenePause::~ScenePause()
{
}

void ScenePause::update(gdl::Clock const &clock)
{
  ASceneMenu::update(clock);
}

void		ScenePause::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  ASceneMenu::draw(shader, clock);
}

void ScenePause::onResumeClick()
{
  close();
}

void ScenePause::onOptionsClick()
{
  AudioManager::getInstance()->playSound(AudioManager::CLICK);
  SceneOptions* options = new SceneOptions(m_game);
  options->open();
}

void ScenePause::onSaveClick()
{
  AudioManager::getInstance()->playSound(AudioManager::CLICK);
  SceneSave* save = new SceneSave(m_game, m_parent->getMap(), &m_preview);
  save->open();
}

void ScenePause::onMenuClick()
{
  m_parent->close();
  close();
}
