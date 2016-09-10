#ifndef SCENE_CONFIRMATION_HPP_
#define SCENE_CONFIRMATION_HPP_

#include <map>
#include <vector>
#include <string>

#include "PlayersKeysManager.hpp"
#include "AScene.hpp"
#include "Sprite.hpp"
#include "Text.hpp"

class AFormInput;

/**
 * \class SceneConfirmation
 * This scene is use to confirm the save game action
 */

class SceneConfirmation : public AScene
{
public:
  SceneConfirmation(GameEngine* game, const std::string& text, int& choice);
  virtual ~SceneConfirmation();

  void	accept();
  void	refuse();
  
  void	rightCursor();
  void	leftCursor();

  virtual void	update(const gdl::Clock& clock);
  virtual void	draw(gdl::AShader& shader, const gdl::Clock& clock);

private:
  SceneConfirmation(const SceneConfirmation&);
  SceneConfirmation&	operator=(const SceneConfirmation&);

  typedef void	(SceneConfirmation::*func)();
  std::map<PlayersKeysManager::Actions, func>		_actions;

  int				_padding;
  const glm::vec2		_buttonSize;
  glm::vec2			_size;
  Sprite			_window;
  Text				_text;
  std::vector<AFormInput*>	_inputs;
  unsigned int			_cursor;
  int				*_choice;
};

#endif
