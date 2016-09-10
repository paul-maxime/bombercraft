#ifndef PLAYERSKEYSMANAGER_H_
# define PLAYERSKEYSMANAGER_H_

# include	<vector>
# include	"AEntity.hpp"

class PlayersKeysManager
{
public:

  typedef int	keycode;

  /**
  ** this structure contains every keys that a player can use.
  */
  class		PlayerKeys
  {
  public:
    keycode	up;
    keycode	down;
    keycode	right;
    keycode	left;
    keycode	action;
    keycode	escape;
  };

  enum	Actions
    {
      UP = 0,
      DOWN,
      RIGHT,
      LEFT,
      ACTION,
      ESCAPE
    };

private:
  /**
  ** Every PlayerKeys are stored in this vector
  */
  std::vector<PlayerKeys *>		_playersKeys;
  std::vector<int>			_playersOrder;
  std::vector< std::vector<int> >	_actionsKeys;

public:
  PlayersKeysManager();
  virtual ~PlayersKeysManager();

  /**
   * \return the PlayersKeysManager instance. Creates it if it doesn't exist.
   */
  static PlayersKeysManager*	getInstance();

  /**
  ** this function return a PlayerKeys by given an id
  */
  PlayersKeysManager::PlayerKeys	*getPlayerKeys(int id) const;

  /*
  ** this function return the keycode for all player to the same action
  */
  const std::vector<int>		&getActionsKeys(Actions action) const;

  /**
   ** set the order of the controllers
   */
  void	setOrder(int, int);

  /**
  ** getter for the order
  */
  const std::vector<int> &getOrder() const;

  /**
  ** return the number of PlayerKeys available
  */
  int			playersKeysSize() const;

private:
  /**
  ** create a new PlayerKeys and assign the keycodes by those given as parameters
  */
  PlayerKeys	*createPlayerKeys(keycode up, keycode down, keycode left,
				  keycode right, keycode action, keycode escape) const;
  /**
   ** generate vector for the menu navigation
   */
  void generateActionsList();

private:
  static PlayersKeysManager	*m_instance;
  PlayersKeysManager(const PlayersKeysManager &);
  PlayersKeysManager &operator=(const PlayersKeysManager &);
};

#endif /* !PLAYERSKEYSMANAGER_H_ */
