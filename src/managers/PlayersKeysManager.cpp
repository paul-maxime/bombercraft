#include	"PlayersKeysManager.hpp"
#include	"InputsManager.hpp"

PlayersKeysManager* PlayersKeysManager::m_instance = NULL;

PlayersKeysManager* PlayersKeysManager::getInstance()
{
  if (!m_instance)
    m_instance = new PlayersKeysManager();
  return (m_instance);
}

PlayersKeysManager::PlayersKeysManager()
{
  _playersOrder.push_back(0);
  _playersOrder.push_back(1);
  _playersOrder.push_back(2);
  _playersOrder.push_back(3);
  _playersOrder.push_back(4);
  _playersOrder.push_back(5);
  _playersKeys.push_back(createPlayerKeys(SDLK_z, SDLK_s, SDLK_q, SDLK_d, SDLK_SPACE, SDLK_ESCAPE));
  _playersKeys.push_back(createPlayerKeys(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT, SDLK_RCTRL, SDLK_ESCAPE));
  _playersKeys.push_back(createPlayerKeys(-100, -101, -102, -103, -104, -105));
  _playersKeys.push_back(createPlayerKeys(-200, -201, -202, -203, -204, -205));
  _playersKeys.push_back(createPlayerKeys(-300, -301, -302, -303, -304, -305));
  _playersKeys.push_back(createPlayerKeys(-400, -401, -402, -403, -404, -405));
  generateActionsList();
}

PlayersKeysManager::~PlayersKeysManager()
{
}

PlayersKeysManager::PlayerKeys *PlayersKeysManager::getPlayerKeys(int id) const
{
  if (id >= 0 && id < 6)
    return this->_playersKeys[_playersOrder[id]];
  return 0;
}

void PlayersKeysManager::generateActionsList()
{
  for (int i = 0; i < 6; ++i)
    {
      std::vector<int> actions;
      for (std::vector<PlayersKeysManager::PlayerKeys *>::const_iterator it = _playersKeys.begin();
	   it != _playersKeys.end(); ++it)
	{
	  int tab[] = {(*it)->up, (*it)->down, (*it)->right, (*it)->left, (*it)->action, (*it)->escape};
	  actions.push_back(tab[i]);
	}
      _actionsKeys.push_back(actions);
    }
}

const std::vector<int> &PlayersKeysManager::getActionsKeys(PlayersKeysManager::Actions action) const
{
  return _actionsKeys[action];
}

void	PlayersKeysManager::setOrder(int id, int value)
{
  _playersOrder[id] = value;
}

const std::vector<int> &PlayersKeysManager::getOrder() const
{
  return _playersOrder;
}

PlayersKeysManager::PlayerKeys	*PlayersKeysManager::createPlayerKeys(keycode up, keycode down,
								      keycode left, keycode right,
								      keycode action, keycode escape) const
{
  PlayersKeysManager::PlayerKeys	*playerKeys;

  playerKeys = new PlayerKeys;
  playerKeys->up = up;
  playerKeys->down = down;
  playerKeys->left = left;
  playerKeys->right = right;
  playerKeys->action = action;
  playerKeys->escape = escape;
  return playerKeys;
}

int		PlayersKeysManager::playersKeysSize() const
{
  return this->_playersKeys.size();
}
