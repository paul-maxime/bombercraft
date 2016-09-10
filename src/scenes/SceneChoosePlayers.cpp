#include "InputsManager.hpp"
#include "MatrixManager.hpp"
#include "AudioManager.hpp"

#include "SceneChoosePlayers.hpp"
#include "SceneChooseCmd.hpp"
#include "SceneGame.hpp"
#include "FormInputButton.hpp"
#include "FormInputDecCounter.hpp"

SceneChoosePlayers::SceneChoosePlayers(GameEngine* game, AScene& parent,
				       const SceneChooseMap::AsciiMapInfo& infos)
  : AScene(game),
    _infos(infos),
    _parent(&parent),
    _cursor(0)
{
  _actions[PlayersKeysManager::ESCAPE] = &SceneChoosePlayers::quit;
  _actions[PlayersKeysManager::DOWN] = &SceneChoosePlayers::downCursor;
  _actions[PlayersKeysManager::UP] = &SceneChoosePlayers::upCursor;

  unsigned int nbPlayersKeys = PlayersKeysManager::getInstance()->playersKeysSize();
  int bigger = infos.spawns.size() > nbPlayersKeys ? nbPlayersKeys : infos.spawns.size();
  _inputs.push_back(new FormInputDecCounter(game, 100, 20, 600, 50, "Nombre de joueurs",
					    1, bigger, 1));
  _inputs.push_back(new FormInputDecCounter(game, 100, 80, 600, 50, "Nombre d'IA",
					    0, bigger - 1, 0));

  FormInputButton* button = new FormInputButton(game, 100, 520, 600, 50, "Suite");
  button->setCallback(this, &SceneChoosePlayers::onClick);
  _inputs.push_back(button);

  _background.init(TextureManager::BACKGROUND, glm::vec2(game->getWidth(), game->getHeight()));

  _inputs[_cursor]->setFocus(true);
}

SceneChoosePlayers::~SceneChoosePlayers()
{
  for (std::vector<AFormInput *>::iterator it = _inputs.begin(); it != _inputs.end(); ++it)
    delete (*it);
}

void	SceneChoosePlayers::quit()
{
  AudioManager::getInstance()->playSound(AudioManager::CLICK);
  close();
}

void	SceneChoosePlayers::downCursor()
{
  AudioManager::getInstance()->playSound(AudioManager::CLICK);
  _inputs[_cursor++]->setFocus(false);
  if (_cursor == _inputs.size())
    _cursor = 0;
  _inputs[_cursor]->setFocus(true);
}

void	SceneChoosePlayers::upCursor()
{
  AudioManager::getInstance()->playSound(AudioManager::CLICK);
  _inputs[_cursor--]->setFocus(false);
  if (_cursor == static_cast<unsigned int>(-1))
    _cursor = _inputs.size() - 1;
  _inputs[_cursor]->setFocus(true);
}

void		SceneChoosePlayers::update(gdl::Clock const &clock)
{
  unsigned int nbPlayersKeys = PlayersKeysManager::getInstance()->playersKeysSize();
  unsigned int total = _inputs[0]->getValue() + _inputs[1]->getValue();
  unsigned int diff = _inputs[0]->getValue() + (_infos.spawns.size() - total);
  unsigned int bigger = diff > nbPlayersKeys ? nbPlayersKeys : diff;

  FormInputDecCounter* cast;
  if ((cast = dynamic_cast<FormInputDecCounter*>(_inputs[0])))
    cast->changeMaxValue(bigger);
  if ((cast = dynamic_cast<FormInputDecCounter*>(_inputs[1])))
    cast->changeMaxValue(_inputs[1]->getValue() + (_infos.spawns.size() - total));

  PlayersKeysManager* playersKeysManager = PlayersKeysManager::getInstance();
  for (std::map<PlayersKeysManager::Actions, func>::iterator it = _actions.begin(); it != _actions.end(); ++it)
    {
      if (m_inputs->keyIsPressed(playersKeysManager->getActionsKeys(it->first)))
	(this->*(it->second))();
    }
  for (std::vector<AFormInput *>::iterator it = _inputs.begin(); it != _inputs.end(); ++it)
    (*it)->update(clock);
}

void		SceneChoosePlayers::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  MatrixManager* matrix = MatrixManager::getInstance();
  matrix->apply(MatrixManager::MATRIX_2D, shader);

  _background.draw(shader, clock);
  for (std::vector<AFormInput *>::iterator it = _inputs.begin(); it != _inputs.end(); ++it)
    (*it)->draw(shader, clock);
}

void		SceneChoosePlayers::onClick()
{
  GameEngine::MapParameters& params = m_game->getMapParams();
  params.nbPlayers = _inputs[0]->getValue();
  params.nbIAPlayers = _inputs[1]->getValue();
  params.sizeX = _infos.width;
  params.sizeY = _infos.height;
  params.bonusDensity = 30;

  close();
  _parent->close();
  AudioManager::getInstance()->playSound(AudioManager::CLICK);
  AScene* scene = new SceneChooseCmd(m_game, new SceneChooseMap::AsciiMapInfo(_infos));
  scene->open();
}
