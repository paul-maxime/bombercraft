#include <iostream>

#include "InputsManager.hpp"
#include "MatrixManager.hpp"

#include "AudioManager.hpp"
#include "SceneOptions.hpp"
#include "SceneGame.hpp"
#include "FormInputButton.hpp"
#include "FormInputDecCounter.hpp"
#include "FormInputCheckBox.hpp"

SceneOptions::SceneOptions(GameEngine* game)
  : ASceneMenu(game, 0)
{
  AudioManager* audioManager = AudioManager::getInstance();

  m_buttons.push_back(new FormInputDecCounter(game, 100, 20, 600, 60, "Volume principal", 0, 10, audioManager->getMasterVolume()));
  m_buttons.push_back(new FormInputDecCounter(game, 100, 100, 600, 60, "Musiques", 0, 10, audioManager->getMusicVolume()));
  m_buttons.push_back(new FormInputDecCounter(game, 100, 180, 600, 60, "Bruitages", 0, 10, audioManager->getSfxVolume()));

  FormInputButton* button = new FormInputButton(game, 100, 280, 600, 60, "Retour");
  button->setCallback(this, &SceneOptions::onClick);
  m_buttons.push_back(button);

  _background.init(TextureManager::BACKGROUND, glm::vec2(game->getWidth(), game->getHeight()));
}

void	SceneOptions::onClick()
{
  AudioManager::getInstance()->playSound(AudioManager::CLICK);
  close();
}

SceneOptions::~SceneOptions()
{
}

void		SceneOptions::update(gdl::Clock const &clock)
{
  ASceneMenu::update(clock);
  AudioManager::getInstance()->saveOptions(m_buttons[0]->getValue(),
					   m_buttons[1]->getValue(),
					   m_buttons[2]->getValue());
}

void		SceneOptions::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _background.draw(shader, clock);
  ASceneMenu::draw(shader, clock);
}
