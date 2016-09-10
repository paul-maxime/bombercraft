#include <iostream>

#include "InputsManager.hpp"
#include "MatrixManager.hpp"
#include "AudioManager.hpp"

#include "SceneNewMap.hpp"
#include "SceneChooseCmd.hpp"
#include "SceneGame.hpp"
#include "FormInputButton.hpp"
#include "FormInputDecCounter.hpp"
#include "FormInputCheckBox.hpp"

SceneNewMap::SceneNewMap(GameEngine* game, AScene& parent)
  : ASceneMenu(game, 0),
    _parent(&parent)
{
  GameEngine::MapParameters& params = m_game->getMapParams();
  m_buttons.push_back(new FormInputDecCounter(game, 100, 20, 600, 50, "Nombre de joueurs", 1,
					    PlayersKeysManager::getInstance()->playersKeysSize(), params.nbPlayers));
  m_buttons.push_back(new FormInputDecCounter(game, 100, 80, 600, 50, "Nombre d'IA", 0, 1000, params.nbIAPlayers));
  m_buttons.push_back(new FormInputDecCounter(game, 100, 140, 600, 50, "Longueur de la carte", 1, 1000, params.sizeX));
  m_buttons.push_back(new FormInputDecCounter(game, 100, 200, 600, 50, "Largeur de la carte", 1, 1000, params.sizeY));
  m_buttons.push_back(new FormInputDecCounter(game, 100, 260, 600, 50, "Densite des murs", 0, 100, params.wallDensity));
  m_buttons.push_back(new FormInputDecCounter(game, 100, 320, 600, 50, "Densite de la terre", 0, 100, params.objectsDensity));
  m_buttons.push_back(new FormInputDecCounter(game, 100, 380, 600, 50, "Densite des bonus", 0, 100, params.bonusDensity));
  m_buttons.push_back(new FormInputCheckBox(game, 100, 440, 600, 60, "Ajouter une grille de murs?", params.wallGrid));

  FormInputButton* button = new FormInputButton(game, 100, 520, 600, 50, "Suite");
  button->setCallback(this, &SceneNewMap::onClick);
  m_buttons.push_back(button);

  _background.init(TextureManager::BACKGROUND, glm::vec2(game->getWidth(), game->getHeight()));
}

SceneNewMap::~SceneNewMap()
{
}

void		SceneNewMap::quit()
{
  AudioManager::getInstance()->playSound(AudioManager::CLICK);
  close();
}

void		SceneNewMap::update(gdl::Clock const &clock)
{
  ASceneMenu::update(clock);
}

void		SceneNewMap::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _background.draw(shader, clock);
  ASceneMenu::draw(shader, clock);
}

void		SceneNewMap::onClick()
{
  GameEngine::MapParameters& params = m_game->getMapParams();
  params.nbPlayers = m_buttons[0]->getValue();
  params.nbIAPlayers = m_buttons[1]->getValue();
  params.sizeX = m_buttons[2]->getValue() + 2;
  params.sizeY = m_buttons[3]->getValue() + 2;
  params.wallDensity = m_buttons[4]->getValue();
  params.objectsDensity = m_buttons[5]->getValue();
  params.bonusDensity = m_buttons[6]->getValue();
  params.wallGrid = m_buttons[7]->getValue();
  close();
  _parent->close();
  AudioManager::getInstance()->playSound(AudioManager::CLICK);
  AScene* scene = new SceneChooseCmd(m_game);
  scene->open();
}
