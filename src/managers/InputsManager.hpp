/**
 * \file InputsManager.hpp
 * Contains the inputs manager.
 */

#ifndef INPUTS_MANAGER_HPP_
#define INPUTS_MANAGER_HPP_

#include <SDL.h>
#include <vector>
#include <map>

#include "JoystickManager.hpp"

class		EventInput
{
public:
  int		code;
};

class		EventMouse
{
public:
  int		code;
  int		x;
  int		y;
};

class		EventWheel
{
public:
  int		move;
  int		x;
  int		y;
};

class	InputsManager
{
public:
  static InputsManager*		getInstance();
  static void			destroy();

public:
  void				listening();
  bool				hasQuit() const;

  std::vector<int>		keyPressed() const;
  bool				keyIsPressed(int code) const;
  bool				keyIsPressed(const std::vector<int>& codes) const;

  std::vector<int>		keyHold() const;
  bool				keyIsHold(int code) const;
  bool				keyIsHold(const std::vector<int>& codes) const;

  std::vector<int>		keyReleased() const;
  bool				keyIsReleased(int code) const;
  bool				keyIsReleased(const std::vector<int>& codes) const;

  bool				mouseIsPressed(int code) const;
  EventMouse			mouseInfoPressed(int code) const;

  bool				mouseIsHold(int code) const;
  EventMouse			mouseInfoHold(int code) const;

  bool				mouseIsReleased(int code) const;
  EventMouse			mouseInfoReleased(int code) const;

  int				mouseIsWheeled() const;
  EventWheel			mouseInfoWheeled() const;

  bool				hasFocus() const;
  bool				gainedFocus() const;
  bool				lostFocus() const;

private:
  InputsManager();
  virtual ~InputsManager();

  InputsManager&	operator=(const InputsManager&);

  static InputsManager*	_instance;

  int			inVector(const std::vector<EventInput>& tab, int code) const;
  int			inVector(const std::vector<EventMouse>& tab, int code) const;

  void			extractByCode(std::vector<EventInput>& tab, int code);
  void			extractByCode(std::vector<EventMouse>& tab, int code);

  std::vector<int>	codeContent(const std::vector<EventInput>& tab) const;

  EventMouse		getInfoByCode(const std::vector<EventMouse>& tab, int code) const;

  bool			checkIn(const std::vector<EventInput>& tab, int code) const;
  bool			checkIn(const std::vector<EventInput>& tab, const std::vector<int>& codes) const;
  bool			checkIn(const std::vector<EventMouse>& tab, int code) const;

  void			event_keyPressed(const SDL_Event& event);
  void			event_keyReleased(const SDL_Event& event);
  void			event_mouseButtonPressed(const SDL_Event& event);
  void			event_mouseButtonReleased(const SDL_Event& event);
  void			event_joyButtonPressed(const SDL_Event& event);
  void			event_joyButtonReleased(const SDL_Event& event);
  void			event_joyAxisMove(const SDL_Event& event);

  void			prepare_listening();

  typedef void (InputsManager::*fctPtr)(const SDL_Event& event);
  std::map<Uint32, fctPtr>	event_fct;
  std::vector<EventInput>	keyPressedVector, keyHoldVector, keyReleasedVector;
  std::vector<EventMouse>	mousePressedVector, mouseHoldVector, mouseReleasedVector;
  EventWheel			mouseWheel;
  bool				prevFocus;
  bool				focus;
  bool				_quit;
};

#endif
