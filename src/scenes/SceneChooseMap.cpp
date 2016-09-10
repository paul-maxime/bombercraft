#include "EntitiesFactory.hpp"
#include "SceneChooseMap.hpp"
#include "SceneChoosePlayers.hpp"
#include "File.hpp"
#include "GameEngine.hpp"
#include "MatrixManager.hpp"
#include "SceneGame.hpp"
#include "InputsManager.hpp"
#include "AudioManager.hpp"

#include "FormInputMapBox.hpp"

SceneChooseMap::SceneChooseMap(GameEngine* game, AScene& parent)
  : AScene(game),
    _parent(&parent),
    _folder("Maps"),
    _cursor(0)
{
  _actions[PlayersKeysManager::ESCAPE] = &SceneChooseMap::quit;
  _actions[PlayersKeysManager::LEFT] = &SceneChooseMap::leftCursor;
  _actions[PlayersKeysManager::RIGHT] = &SceneChooseMap::rightCursor;

  _background.init(TextureManager::BACKGROUND, glm::vec2(game->getWidth(), game->getHeight()));

  addMaps();

  if (_inputs.size())
    _inputs[_cursor]->setFocus(true);
}

SceneChooseMap::~SceneChooseMap()
{
  for (std::vector<AFormInput*>::iterator it = _inputs.begin(); it != _inputs.end(); ++it)
    delete (*it);
}

void	SceneChooseMap::addMaps()
{
  std::vector<std::string>	files;

  File::getAllFiles(_folder, ".map", files);
  for (std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it)
    {
      AsciiMapInfo infos;

      infos.width = infos.height = 0;
      if (loadMap(_folder + "/" + *it, infos))
	{
	  FormInputMapBox* input = new FormInputMapBox(m_game, infos);

	  _maps.push_back(infos);
	  input->setCallback(this, &SceneChooseMap::launchGame);
	  _inputs.push_back(input);
	}
    }
}

bool	SceneChooseMap::loadMap(const std::string& file, AsciiMapInfo& infos) const
{
  std::ifstream in(file.c_str());

  if (!in.is_open())
    std::cerr << file << ": Cannot open map" << std::endl;
  else
    {
      std::string line;

      while (in >> line)
	{
	  if (checkMapLine(file, line, infos))
	    infos.content.append(line);
	  else
	    {
	      in.close();
	      return (false);
	    }
	}
      std::string sub(infos.content.substr(infos.content.size() - infos.width));
      for (std::string::const_iterator it = sub.begin(); it != sub.end(); ++it)
	{
	  if (_converter.convert((*it)) != EntitiesFactory::SOLID_WALL)
	    {
	      std::cerr << file << ": The map must have a border of solid wall" << std::endl;
	      return (false);
	    }
	}
      if (infos.height < 3 || infos.height > 1000 || infos.width < 3 || infos.width > 1000)
	std::cerr << file << ": Map height and width have to be greater than 3 and less than 1000" << std::endl;
      else if (infos.spawns.size() < 2)
	std::cerr << file << ": A map need at least 2 player spawn points" << std::endl;
      else
	{
	  in.close();
	  return (true);
	}
    }
  in.close();
  return (false);
}

bool	SceneChooseMap::checkMapLine(const std::string& file, const std::string& line,
				     AsciiMapInfo& infos) const
{
  EntitiesFactory::FactoryType	type;

  if (!line.size())
    {
      std::cerr << file << ": Has empty line" << std::endl;
      return (false);
    }
  if (infos.width && line.size() != infos.width)
    {
      std::cerr << file << ": All line must have the same size" << std::endl;
      return (false);
    }
  for (std::string::const_iterator it = line.begin(); it != line.end(); ++it)
    {
      if ((type = _converter.convert((*it))) == EntitiesFactory::UNKNOWN)
	{
	  std::cerr << file << ": '" << (*it) << "' is not a valid entity" << std::endl;
	  return (false);
	}
      if ((!infos.height || it == line.begin() || it + 1 == line.end()) &&
	  type != EntitiesFactory::SOLID_WALL)
	{
	  std::cerr << file << ": The map must have a border of solid wall" << std::endl;
	  return (false);
	}
      if (type == EntitiesFactory::PLAYER || type == EntitiesFactory::LUA_PLAYER)
	infos.spawns.push_back(glm::vec2(it - line.begin(), infos.height));
    }
  if (!infos.width)
    infos.width = line.size();
  ++infos.height;
  return true;
}

void	SceneChooseMap::quit()
{
  AudioManager::getInstance()->playSound(AudioManager::CLICK);
  close();
}

void	SceneChooseMap::leftCursor()
{
  if (_inputs.size())
    {
      AudioManager::getInstance()->playSound(AudioManager::CLICK);
      _inputs[_cursor--]->setFocus(false);
      if (_cursor == static_cast<unsigned int>(-1))
	_cursor = _inputs.size() - 1;
      _inputs[_cursor]->setFocus(true);
    }
}

void	SceneChooseMap::rightCursor()
{
  if (_inputs.size())
    {
      AudioManager::getInstance()->playSound(AudioManager::CLICK);
      _inputs[_cursor++]->setFocus(false);
      if (_cursor == _inputs.size())
	_cursor = 0;
      _inputs[_cursor]->setFocus(true);
    }
}

void	SceneChooseMap::launchGame()
{
  if (_maps.size())
    {
      AudioManager::getInstance()->playSound(AudioManager::CLICK);
      SceneChoosePlayers* choosePlayers =
	new SceneChoosePlayers(m_game, *this, _maps[_cursor]);

      _parent->close();
      choosePlayers->open();
    }
}

void	SceneChooseMap::update(const gdl::Clock& clock)
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

void	SceneChooseMap::draw(gdl::AShader &shader, const gdl::Clock& clock)
{
  MatrixManager* matrix = MatrixManager::getInstance();
  matrix->apply(MatrixManager::MATRIX_2D, shader);

  _background.draw(shader, clock);
  for (std::vector<AFormInput*>::iterator it = _inputs.begin(); it != _inputs.end(); ++it)
    (*it)->draw(shader, clock);
}
