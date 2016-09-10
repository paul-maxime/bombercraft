/**
 * \file JoystickManager.hpp
 * Contains the joysticks manager.
 */

#ifndef JOYSTICK_MANAGER_HPP_
# define JOYSTICK_MANAGER_HPP_

# include <SDL/SDL.h>
# include <vector>

enum {
  JOYSTICK_UP = 0,
  JOYSTICK_DOWN = 1,
  JOYSTICK_LEFT = 2,
  JOYSTICK_RIGHT = 3,
  JOYSTICK_CTRL = 4,
  JOYSTICK_ESCAPE = 5,
};

/**
 * \class JoystickManager
 * This singleton is used to manage joysticks
 */
class JoystickManager
{
public:
  /**
   * \return the joystick manager instance. Creates it if it doesn't exist.
   */
  static JoystickManager*	getInstance();

  /**
   * Frees the memory used by the joystick manager.
   */
  static void		destroy();

private:
  JoystickManager();
  JoystickManager(const JoystickManager&);
  virtual ~JoystickManager();
  JoystickManager&	operator=(const JoystickManager&);

  static JoystickManager*	m_instance;
  std::vector<SDL_Joystick *>	m_joysticks;
};

#endif
