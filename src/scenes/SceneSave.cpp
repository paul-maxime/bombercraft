#include <iostream>

#include "Screenshot.hpp"
#include "Utils.hpp"
#include "File.hpp"
#include "FormInputSaveBox.hpp"
#include "FontsManager.hpp"
#include "InputsManager.hpp"
#include "SaveManager.hpp"
#include "GameEngine.hpp"
#include "MatrixManager.hpp"
#include "Map.hpp"
#include "SceneGame.hpp"
#include "SceneConfirmation.hpp"
#include "SceneSave.hpp"
#include "AudioManager.hpp"

SceneSave::SceneSave(GameEngine* game, Map* map, Screenshot* screen)
  : AScene(game),
    _folder("Saves"),
    _maxSave(8),
    _topBorder(200),
    _border(80),
    _hpadding(40),
    _vpadding(60),
    _slotSize(200),
    _map(map),
    _cursor(0),
    _selected(false),
    _choice(-1),
    _screen(screen)
{
  m_isBackground = true;

  int x, y;
  _slotSize = (game->getWidth() - (2 * _border + ((_maxSave / 2) - 1) * _hpadding)) / (_maxSave / 2);
  if (_slotSize < 0)
    _slotSize = 100;

  File::createDirectory(_folder);

  _actions[PlayersKeysManager::ESCAPE] = &SceneSave::quit;
  _actions[PlayersKeysManager::DOWN] = &SceneSave::downCursor;
  _actions[PlayersKeysManager::UP] = &SceneSave::upCursor;
  _actions[PlayersKeysManager::RIGHT] = &SceneSave::rightCursor;
  _actions[PlayersKeysManager::LEFT] = &SceneSave::leftCursor;
  _background.init(TextureManager::BACKGROUND, glm::vec2(game->getWidth(), game->getHeight()));

  for (unsigned int i = 0; i < _maxSave; ++i)
    {
      x = _border + (i % (_maxSave / 2)) * (_slotSize + _hpadding);
      y = _topBorder + i / (_maxSave / 2) * (_slotSize + _vpadding);
      addSaveSlot(_folder + "/save" + Utils::toString(i + 1), x, y);
    }

  _inputs[_cursor]->setFocus(true);

  if (map)
    _header.init(FontsManager::DEFAULT, "Sauvegarder");
  else
    _header.init(FontsManager::DEFAULT, "Charger");
  _header.scale(glm::vec3(3, 3, 3));
  _header.translate(glm::vec3((game->getWidth() - _header.getWidth() * 3) / 2,
			      (_topBorder - _header.getHeight() * 3) / 2, 0));
}

SceneSave::~SceneSave()
{
  for (std::vector<AFormInput*>::iterator it = _inputs.begin(); it != _inputs.end(); ++it)
    delete (*it);
}

void	SceneSave::addSaveSlot(const std::string& file, int posX, int posY)
{
  FormInputSaveBox*	box;

  _filesName.push_back(file);
  _filesEmpty.push_back(!File::fileExist(file + ".sb"));
  box = new FormInputSaveBox(m_game, posX, posY, _slotSize, _slotSize,
			     _filesEmpty.back(), _filesName.back() + ".tga");
  box->setCallback(this, &SceneSave::onClick);
  _inputs.push_back(box);
}

void	SceneSave::load()
{
  if (_cursor < _filesEmpty.size() && !_filesEmpty[_cursor])
    {
      std::cout << "Chargement..." << std::endl;
      Map* map = SaveManager::getInstance()->load(_filesName[_cursor] + ".sb");
      SceneGame* game = new SceneGame(m_game, map);
      game->open();
      close();
    }
  _selected = false;
}

void	SceneSave::save()
{
  bool	save = false;

  if (_cursor < _filesEmpty.size() && _filesEmpty[_cursor])
    {
      save = true;
      _selected = false;
    }
  else if (_choice == -1)
    {
      SceneConfirmation* confirm = new SceneConfirmation(m_game, "La sauvegarde n'est pas vide, voulez-vous la remplacer ?", _choice);
      confirm->open();
    }
  else
    {
      if (_choice == 1)
	save = true;
      _choice = -1;
      _selected = false;
    }
  if (save)
    {
      _filesEmpty[_cursor] = false;
      std::cout << "Sauvegarde..." << std::endl;
      try
	{
	  SaveManager::getInstance()->save(_filesName[_cursor] + ".sb", *_map);
	}
      catch (const InvalidFileError&)
	{
	  File::removeFile(_filesName[_cursor] + ".sb");
	  _filesEmpty[_cursor] = true;
	  std::cout << "Erreur lors de la sauvegarde" << std::endl;
	}
      if (!_filesEmpty[_cursor])
	{
	  std::cout << "Partie sauvegardée !" << std::endl;
	  if (_screen)
	    _screen->saveBufferTGA(_filesName[_cursor]);
	}
      FormInputSaveBox* cast = dynamic_cast<FormInputSaveBox*>(_inputs[_cursor]);
      if (cast)
	{
	  cast->setEmpty(_filesEmpty[_cursor]);
	  cast->loadPreview();
	}
    }
}

void	SceneSave::quit()
{
  AudioManager::getInstance()->playSound(AudioManager::CLICK);
  close();
}

void	SceneSave::downCursor()
{
  _inputs[_cursor]->setFocus(false);
  _cursor = (_cursor + (_maxSave / 2)) % _maxSave;
  if (_cursor >= _inputs.size())
    _cursor = 0;
  _inputs[_cursor]->setFocus(true);
}

void	SceneSave::upCursor()
{
  int	tmpC;

  _inputs[_cursor]->setFocus(false);
  tmpC = _cursor - (_maxSave / 2);
  _cursor = (tmpC < 0 ? _inputs.size() + tmpC : tmpC);
  _inputs[_cursor]->setFocus(true);
}

void	SceneSave::leftCursor()
{
  _inputs[_cursor--]->setFocus(false);
  if (_cursor == static_cast<unsigned int>(-1) || _cursor % (_maxSave / 2) == (_maxSave / 2) - 1)
    _cursor += (_maxSave / 2);
  _inputs[_cursor]->setFocus(true);
}

void	SceneSave::rightCursor()
{
  _inputs[_cursor++]->setFocus(false);
  if (_cursor == _inputs.size() || _cursor % (_maxSave / 2) == 0)
    _cursor -= (_maxSave / 2);
  _inputs[_cursor]->setFocus(true);
}

void	SceneSave::onClick()
{
  _selected = true;
}

void	SceneSave::update(const gdl::Clock& clock)
{
  if (!_selected)
    {
      PlayersKeysManager* playersKeysManager = PlayersKeysManager::getInstance();
      for (std::map<PlayersKeysManager::Actions, func>::iterator it = _actions.begin(); it != _actions.end(); ++it)
	{
	  if (m_inputs->keyIsPressed(playersKeysManager->getActionsKeys(it->first)))
	    (this->*(it->second))();
	}
      for (std::vector<AFormInput*>::iterator it = _inputs.begin(); it != _inputs.end(); ++it)
	(*it)->update(clock);
    }
  else
    {
      if (_map)
	save();
      else
	load();
    }
}

void	SceneSave::draw(gdl::AShader &shader, const gdl::Clock& clock)
{
  MatrixManager* matrix = MatrixManager::getInstance();
  matrix->apply(MatrixManager::MATRIX_2D, shader);

  _background.draw(shader, clock);
  _header.draw(shader, clock);
  for (std::vector<AFormInput*>::iterator it = _inputs.begin(); it != _inputs.end(); ++it)
    (*it)->draw(shader, clock);
}
