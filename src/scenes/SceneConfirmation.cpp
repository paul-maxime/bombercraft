#include "TextureManager.hpp"
#include "FontsManager.hpp"
#include "InputsManager.hpp"
#include "MatrixManager.hpp"
#include "SceneConfirmation.hpp"
#include "FormInputButton.hpp"

SceneConfirmation::SceneConfirmation(GameEngine* game, const std::string& text, int& choice)
  : AScene(game),
    _padding(30),
    _buttonSize(glm::vec2(100, 63)),
    _cursor(0),
    _choice(&choice)
{
  _actions[PlayersKeysManager::ESCAPE] = &SceneConfirmation::refuse;
  _actions[PlayersKeysManager::LEFT] = &SceneConfirmation::leftCursor;
  _actions[PlayersKeysManager::RIGHT] = &SceneConfirmation::rightCursor;

  _text.init(FontsManager::DEFAULT, text);
  _size.x = _text.getWidth() + _padding * 2;
  if (_size.x < _buttonSize.x * 2 + _padding * 3)
    _size.x = _buttonSize.x * 2 + _padding * 3;
  _size.y = _text.getHeight() + _padding * 3 + _buttonSize.y;

  int x = (game->getWidth() - _size.x) / 2, y = (game->getHeight() - _size.y) / 2;
  _text.translate(glm::vec3(x + _padding, y + _padding, 0));
  _window.init(TextureManager::DIRT, _size);
  _window.translate(glm::vec3(x, y, 0));

  int decx = x + (_size.x - (_buttonSize.x * 2 + _padding)) / 2,
    decy = y + _text.getHeight() + _padding * 2;
  FormInputButton* button = new FormInputButton(game, decx, decy, _buttonSize.x, _buttonSize.y, "Oui");
  button->setCallback(this, &SceneConfirmation::accept);
  _inputs.push_back(button);

  button = new FormInputButton(game, decx + _padding + _buttonSize.x, decy, _buttonSize.x, _buttonSize.y, "Non");
  button->setCallback(this, &SceneConfirmation::refuse);
  _inputs.push_back(button);

  _inputs[++_cursor]->setFocus(true);
}

SceneConfirmation::~SceneConfirmation()
{
  for (std::vector<AFormInput*>::iterator it = _inputs.begin(); it != _inputs.end(); ++it)
    delete (*it);
}

void	SceneConfirmation::accept()
{
  *_choice = 1;
  close();
}

void	SceneConfirmation::refuse()
{
  *_choice = 0;
  close();
}

void	SceneConfirmation::leftCursor()
{
  _inputs[_cursor++]->setFocus(false);
  if (_cursor == _inputs.size())
    _cursor = 0;
  _inputs[_cursor]->setFocus(true);
}

void	SceneConfirmation::rightCursor()
{
  _inputs[_cursor--]->setFocus(false);
  if (_cursor == static_cast<unsigned int>(-1))
    _cursor = _inputs.size() - 1;
  _inputs[_cursor]->setFocus(true);
}

void		SceneConfirmation::update(gdl::Clock const &clock)
{
  PlayersKeysManager* playersKeysManager = PlayersKeysManager::getInstance();
  for (std::map<PlayersKeysManager::Actions, func>::iterator it = _actions.begin(); it != _actions.end(); ++it)
    {
      if (m_inputs->keyIsPressed(playersKeysManager->getActionsKeys(it->first)))
	(this->*(it->second))();
    }
  for (std::vector<AFormInput *>::iterator it = _inputs.begin(); it != _inputs.end(); ++it)
    (*it)->update(clock);
}

void		SceneConfirmation::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  MatrixManager* matrix = MatrixManager::getInstance();
  matrix->apply(MatrixManager::MATRIX_2D, shader);

  _window.draw(shader, clock);
  for (std::vector<AFormInput *>::iterator it = _inputs.begin(); it != _inputs.end(); ++it)
    (*it)->draw(shader, clock);
  _text.draw(shader, clock);
}
