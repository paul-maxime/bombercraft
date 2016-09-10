#include <iostream>

#include "JoystickManager.hpp"

JoystickManager* JoystickManager::m_instance = NULL;

JoystickManager* JoystickManager::getInstance()
{
  if (!m_instance)
    m_instance = new JoystickManager();
  return (m_instance);
}

void JoystickManager::destroy()
{
  if (m_instance)
    {
      delete (m_instance);
      m_instance = NULL;
    }
}

JoystickManager::JoystickManager()
{
  int nb = SDL_NumJoysticks();
  for (int i = 0; i < nb; ++i)
    m_joysticks.push_back(SDL_JoystickOpen(i));
}

JoystickManager::~JoystickManager()
{
  for (std::vector<SDL_Joystick *>::iterator it = m_joysticks.begin(); it != m_joysticks.end(); ++it)
    SDL_JoystickClose(*it);
}
