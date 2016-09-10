#include "InputsManager.hpp"

InputsManager*	InputsManager::_instance = NULL;

InputsManager::InputsManager() : _quit(false)
{
  JoystickManager::getInstance();
  event_fct[SDL_KEYDOWN] = &InputsManager::event_keyPressed;
  event_fct[SDL_KEYUP] = &InputsManager::event_keyReleased;
  event_fct[SDL_MOUSEBUTTONDOWN] = &InputsManager::event_mouseButtonPressed;
  event_fct[SDL_MOUSEBUTTONUP] = &InputsManager::event_mouseButtonReleased;
  event_fct[SDL_JOYBUTTONDOWN] = &InputsManager::event_joyButtonPressed;
  event_fct[SDL_JOYBUTTONUP] = &InputsManager::event_joyButtonReleased;
  event_fct[SDL_JOYAXISMOTION] = &InputsManager::event_joyAxisMove;
}

InputsManager::~InputsManager()
{
}

InputsManager*	InputsManager::getInstance()
{
  if (!_instance)
    _instance = new InputsManager();
  return (_instance);
}

void InputsManager::destroy()
{
  if (_instance)
    {
      delete (_instance);
      _instance = NULL;
    }
}

/**********/
/* PUBLIC */
/**********/

std::vector<int>	InputsManager::keyPressed() const
{
  return codeContent(keyPressedVector);
}

bool	InputsManager::keyIsPressed(int code) const
{
  return checkIn(keyPressedVector, code);
}

bool	InputsManager::keyIsPressed(const std::vector<int>& codes) const
{
  return checkIn(keyPressedVector, codes);
}


std::vector<int>	InputsManager::keyHold() const
{
  return codeContent(keyHoldVector);
}

bool	InputsManager::keyIsHold(int code) const
{
  return checkIn(keyHoldVector, code);
}

bool	InputsManager::keyIsHold(const std::vector<int>& codes) const
{
  return checkIn(keyHoldVector, codes);
}


std::vector<int>	InputsManager::keyReleased() const
{
  return codeContent(keyReleasedVector);
}

bool	InputsManager::keyIsReleased(int code) const
{
  return checkIn(keyReleasedVector, code);
}

bool	InputsManager::keyIsReleased(const std::vector<int>& codes) const
{
  return checkIn(keyReleasedVector, codes);
}


bool	InputsManager::mouseIsPressed(int code) const
{
  return checkIn(mousePressedVector, code);
}

EventMouse	InputsManager::mouseInfoPressed(int code) const
{
  return getInfoByCode(mousePressedVector, code);
}


bool	InputsManager::mouseIsHold(int code) const
{
  return checkIn(mouseHoldVector, code);
}

EventMouse	InputsManager::mouseInfoHold(int code) const
{
  return getInfoByCode(mouseHoldVector, code);
}


bool	InputsManager::mouseIsReleased(int code) const
{
  return checkIn(mouseReleasedVector, code);
}

EventMouse	InputsManager::mouseInfoReleased(int code) const
{
  return getInfoByCode(mouseReleasedVector, code);
}


int	InputsManager::mouseIsWheeled() const
{
  return mouseWheel.move;
}

EventWheel	InputsManager::mouseInfoWheeled() const
{
  EventWheel	 emptyStruct;

  if (mouseWheel.move)
    return mouseWheel;
  else
    return emptyStruct;
}

bool	InputsManager::hasFocus() const
{
  return focus;
}

bool	InputsManager::gainedFocus() const
{
  return (prevFocus != focus && focus == true);
}

bool	InputsManager::lostFocus() const
{
  return (prevFocus != focus && focus == false);
}

void		InputsManager::event_keyPressed(const SDL_Event& event)
{
  EventInput	newInput;

  if (!keyIsHold(event.key.keysym.sym) && !keyIsPressed(event.key.keysym.sym))
    {
      newInput.code = event.key.keysym.sym;
      keyPressedVector.push_back(newInput);
    }
}

void		InputsManager::event_keyReleased(const SDL_Event& event)
{
  EventInput	newInput;

  if (keyIsHold(event.key.keysym.sym) || keyIsPressed(event.key.keysym.sym))
    {
      newInput.code = event.key.keysym.sym;
      keyReleasedVector.push_back(newInput);
      extractByCode(keyPressedVector, event.key.keysym.sym);
      extractByCode(keyHoldVector, event.key.keysym.sym);
    }
}

void		InputsManager::event_mouseButtonPressed(const SDL_Event& event)
{
  EventMouse	newMouse;

  if (!mouseIsPressed(event.button.button) && !mouseIsHold(event.button.button))
    {
      newMouse.code = event.button.button;
      newMouse.x = event.button.x;
      newMouse.y = event.button.y;
      mousePressedVector.push_back(newMouse);
    }
}

void		InputsManager::event_mouseButtonReleased(const SDL_Event& event)
{
  EventMouse	newMouse;

  if (mouseIsPressed(event.button.button) || mouseIsHold(event.button.button))
    {
      newMouse.code = event.button.button;
      newMouse.x = event.button.x;
      newMouse.y = event.button.y;
      mouseReleasedVector.push_back(newMouse);
      extractByCode(mousePressedVector, event.button.button);
      extractByCode(mouseHoldVector, event.button.button);
    }
}

void	InputsManager::event_joyButtonPressed(const SDL_Event& event)
{
  EventInput	newInput;

  newInput.code = 0;
  if (event.jbutton.button == 0)
    newInput.code = -(JOYSTICK_CTRL + 100 * (event.jbutton.which + 1));
  if (event.jbutton.button == 1)
    newInput.code = -(JOYSTICK_ESCAPE + 100 * (event.jbutton.which + 1));
  if (newInput.code && !keyIsHold(newInput.code) && !keyIsPressed(newInput.code))
    keyPressedVector.push_back(newInput);
}

void	InputsManager::event_joyButtonReleased(const SDL_Event& event)
{
  EventInput	newInput;

  newInput.code = 0;
  if (event.jbutton.button == 0)
    newInput.code = -(JOYSTICK_CTRL + 100 * (event.jbutton.which + 1));
  if (event.jbutton.button == 1)
    newInput.code = -(JOYSTICK_ESCAPE + 100 * (event.jbutton.which + 1));
  if (newInput.code && (keyIsHold(newInput.code) || keyIsPressed(newInput.code)))
    {
      keyReleasedVector.push_back(newInput);
      extractByCode(keyPressedVector, newInput.code);
      extractByCode(keyHoldVector, newInput.code);
    }
}

void	InputsManager::event_joyAxisMove(const SDL_Event& event)
{
  EventInput newInput;
  int left, right;

  if (event.jaxis.axis == 0)
    {
      left = -(JOYSTICK_LEFT + 100 * (event.jaxis.which + 1));
      right = -(JOYSTICK_RIGHT + 100 * (event.jaxis.which + 1));
    }
  else if (event.jaxis.axis == 1)
    {
      left = -(JOYSTICK_UP + 100 * (event.jaxis.which + 1));
      right = -(JOYSTICK_DOWN + 100 * (event.jaxis.which + 1));
    }
  else
    return;

  if (event.jaxis.value < -10000 || event.jaxis.value > 10000)
    {
      int code = left;
      if (event.jaxis.value > 10000)
	code = right;
      newInput.code = code;
      if (!keyIsHold(code) && !keyIsPressed(code))
	keyPressedVector.push_back(newInput);
    }
  else
    {
      if (keyIsHold(left) || keyIsPressed(left))
	{
	  newInput.code = left;
	  keyReleasedVector.push_back(newInput);
	  extractByCode(keyPressedVector, left);
	  extractByCode(keyHoldVector, left);
	}
      if (keyIsHold(right) || keyIsPressed(right))
	{
	  newInput.code = right;
	  keyReleasedVector.push_back(newInput);
	  extractByCode(keyPressedVector, right);
	  extractByCode(keyHoldVector, right);
	}
    }
}

void	InputsManager::prepare_listening()
{
  keyHoldVector.insert(keyHoldVector.begin(),
		       keyPressedVector.begin(),
		       keyPressedVector.end());
  mouseHoldVector.insert(mouseHoldVector.begin(),
			 mousePressedVector.begin(),
			 mousePressedVector.end());
  keyPressedVector.clear();
  keyReleasedVector.clear();
  mousePressedVector.clear();
  mouseReleasedVector.clear();
  mouseWheel.move = 0;
  prevFocus = focus;
}

void		InputsManager::listening()
{
  SDL_Event		event;

  prepare_listening();
  while (SDL_PollEvent(&event))
    {
      std::map<Uint32, fctPtr>::iterator it = event_fct.find(event.type);
      if (it != event_fct.end())
	(this->*it->second)(event);
      else if (event.type == SDL_QUIT)
	_quit = true;
    }
}

bool		InputsManager::hasQuit() const
{
  return (_quit);
}

/***********/
/* PRIVATE */
/***********/

int	InputsManager::inVector(const std::vector<EventInput>& tab, int code) const
{
  for (std::vector<EventInput>::const_iterator it = tab.begin(); it != tab.end(); ++it)
    {
      if ((*it).code == code)
	return (it - tab.begin());
    }
  return (-1);
}

int	InputsManager::inVector(const std::vector<EventMouse>& tab, int code) const
{
  for (std::vector<EventMouse>::const_iterator it = tab.begin(); it != tab.end(); ++it)
    {
      if ((*it).code == code)
	return (it - tab.begin());
    }
  return (-1);
}

void	InputsManager::extractByCode(std::vector<EventInput>& tab, int code)
{
  for (std::vector<EventInput>::iterator it = tab.begin(); it != tab.end(); ++it)
    {
      if ((*it).code == code)
	{
	  tab.erase(it);
	  return ;
	}
    }
}

void	InputsManager::extractByCode(std::vector<EventMouse>& tab, int code)
{
  for (std::vector<EventMouse>::iterator it = tab.begin(); it != tab.end(); ++it)
    {
      if ((*it).code == code)
	{
	  tab.erase(it);
	  return ;
	}
    }
}

std::vector<int>		InputsManager::codeContent(const std::vector<EventInput>& tab) const
{
  std::vector<int>	ret;

  for(std::vector<EventInput>::const_iterator it = tab.begin(); it != tab.end(); ++it)
    ret.push_back((*it).code);
  return ret;
}

EventMouse	InputsManager::getInfoByCode(const std::vector<EventMouse>& tab, int code) const
{
  EventMouse	emptyStruct;

  for(std::vector<EventMouse>::const_iterator it = tab.begin(); it != tab.end(); ++it)
    {
      if ((*it).code == code)
	return (*it);
    }
  return emptyStruct;
}

bool	InputsManager::checkIn(const std::vector<EventInput>& tab, int code) const
{
  return (inVector(tab, code) >= 0);
}

bool	InputsManager::checkIn(const std::vector<EventInput>& tab, const std::vector<int>& codes) const
{
  for (std::vector<int>::const_iterator it = codes.begin(); it != codes.end(); ++it)
    {
      if (inVector(tab, (*it)) >= 0)
	return true;
    }
  return false;
}

bool	InputsManager::checkIn(const std::vector<EventMouse>& tab, int code) const
{
  return (inVector(tab, code) >= 0);
}
