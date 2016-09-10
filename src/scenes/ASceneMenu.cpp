#include <algorithm>
#include <iostream>
#include <vector>

#include "InputsManager.hpp"
#include "MatrixManager.hpp"
#include "ScoreManager.hpp"
#include "AudioManager.hpp"

#include "ScoreManager.hpp"
#include "ASceneMenu.hpp"
#include "FormInputScore.hpp"
#include "Utils.hpp"

ASceneMenu::ASceneMenu(GameEngine* game, unsigned int menuIndex)
  : AScene(game),
    m_buttonIndex(menuIndex)
{
}

ASceneMenu::~ASceneMenu()
{
  for (std::vector<AFormInput *>::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it)
    delete (*it);
}

void		ASceneMenu::update(gdl::Clock const &clock)
{
  std::for_each(m_keys.begin(), m_keys.end(), &AFormCallback::call2);
  for (std::vector<AFormInput *>::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it)
    (*it)->update(clock);

  m_keys.clear();
  m_keys[PlayersKeysManager::ESCAPE] = new FormCallback<ASceneMenu>(this, &ASceneMenu::onKeyEscape);

  if (m_buttons.size())
    {
      if (m_buttonIndex >= m_buttons.size())
	m_buttonIndex = 0;
      m_buttons[m_buttonIndex]->setFocus(true);
      m_keys[PlayersKeysManager::DOWN] = new FormCallback<ASceneMenu>(this, &ASceneMenu::onKeyArrowDown);
      m_keys[PlayersKeysManager::UP] = new FormCallback<ASceneMenu>(this, &ASceneMenu::onKeyArrowUp);
    }
}

void		ASceneMenu::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  MatrixManager* matrix = MatrixManager::getInstance();

  matrix->apply(MatrixManager::MATRIX_2D, shader);
  for (std::vector<AFormInput *>::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it)
    (*it)->draw(shader, clock);
}

void ASceneMenu::onKeyEscape()
{
  AudioManager::getInstance()->playSound(AudioManager::CLICK);
  close();
}

void ASceneMenu::onKeyArrowDown()
{
  AudioManager::getInstance()->playSound(AudioManager::CLICK);
  m_buttons[m_buttonIndex++]->setFocus(false);
  if (m_buttonIndex == m_buttons.size())
    m_buttonIndex = 0;
  m_buttons[m_buttonIndex]->setFocus(true);
}

void ASceneMenu::onKeyArrowUp()
{
  AudioManager::getInstance()->playSound(AudioManager::CLICK);
  m_buttons[m_buttonIndex--]->setFocus(false);
  if (m_buttonIndex == static_cast<unsigned int>(-1))
    m_buttonIndex = m_buttons.size() - 1;
  m_buttons[m_buttonIndex]->setFocus(true);
}
